export module vendor.stb;

import std;
import <stb/stb_image.h>;
import <stb/stb_image_write.h>;
import opengl.types;
import opengl.utility;

       namespace stb
{
    template<typename T>
    void write_function(gl::void_t* context, gl::void_t* data, gl::int32_t size)
    {
        auto* vector  = std::bit_cast<std::vector<T>*>(context);
        auto* pointer = std::bit_cast<const T*>(data);
        auto  span    = std::span<const T>{ pointer, static_cast<gl::uint64_t>(size) };

        vector->append_range(span);
    }
    void free_image    (gl::byte_t* pointer)
    {
        ::stbi_image_free(pointer);
    }
}
export namespace stb
{
    struct image_data
    {
        gl::uint32_t            channels;
        gl::vector2u            dimensions;
        std::vector<gl::byte_t> data;
    };

    void set_flip_vertically_on_load (gl::bool_t value)
    {
        ::stbi_set_flip_vertically_on_load(value);
    }
    void set_flip_vertically_on_write(gl::bool_t value)
    {
        ::stbi_flip_vertically_on_write(value);
    }

    template<typename T>
    auto load_from_memory            (gl::uint32_t required_channels, std::span<const gl::byte_t> data) -> stb::image_data
    {
        auto* pointer    = std::bit_cast<gl::byte_t*>(nullptr);
        auto  size       = gl::uint64_t{};
        auto  dimensions = gl::vector2i{};
        auto  channels   = gl::int32_t {};

        if constexpr (std::is_same_v<T, gl::uint8_t  >)
        {
            pointer = std::bit_cast<gl::byte_t*>(::stbi_load_from_memory(data.data(), static_cast<gl::int32_t>(data.size_bytes()), &dimensions.x, &dimensions.y, &channels, required_channels));
            size    = sizeof(gl::uint8_t) * required_channels * dimensions.x * dimensions.y;
        }
        if constexpr (std::is_same_v<T, gl::uint16_t >)
        {
            pointer = std::bit_cast<gl::byte_t*>(::stbi_load_16_from_memory(data.data(), static_cast<gl::int32_t>(data.size_bytes()), &dimensions.x, &dimensions.y, &channels, required_channels));
            size    = sizeof(gl::uint16_t) * required_channels * dimensions.x * dimensions.y;
        }
        if constexpr (std::is_same_v<T, gl::float32_t>)
        {
            pointer = std::bit_cast<gl::byte_t*>(::stbi_loadf_from_memory(data.data(), static_cast<gl::int32_t>(data.size_bytes()), &dimensions.x, &dimensions.y, &channels, required_channels));
            size    = sizeof(gl::float32_t) * required_channels * dimensions.x * dimensions.y;
        }

        const auto span       = std::span<gl::byte_t>{ pointer, size };
        const auto image_data = stb::image_data
        {
            .channels   = std::bit_cast<gl::uint32_t>(channels  )         , 
            .dimensions = std::bit_cast<gl::vector2u>(dimensions)         , 
            .data       = std::vector<gl::byte_t>{ std::from_range, span }, 
        };

        stb::free_image(pointer);
        return image_data;
    }

    auto write_bmp_to_function       (std::span<const gl::byte_t> data, gl::uint32_t channels, const gl::vector2u& dimensions) -> std::vector<gl::byte_t>
    {
        auto vector = std::vector<gl::byte_t>{};
        ::stbi_write_bmp_to_func(
            stb::write_function<gl::byte_t>    , 
            &vector, dimensions.x, dimensions.y, 
            channels, data.data()             );

        return vector;
    }
    auto write_hdr_to_function       (std::span<const gl::byte_t> data, gl::uint32_t channels, const gl::vector2u& dimensions) -> std::vector<gl::float32_t>
    {
        auto vector = std::vector<gl::float32_t>{};
        ::stbi_write_hdr_to_func(
            stb::write_function<gl::float32_t>               , 
            &vector, dimensions.x, dimensions.y, channels    , 
            std::bit_cast<const gl::float32_t*>(data.data()));

        return vector;
    }
    auto write_jpg_to_function       (std::span<const gl::byte_t> data, gl::uint32_t channels, const gl::vector2u& dimensions) -> std::vector<gl::byte_t>
    {
        auto vector = std::vector<gl::byte_t>{};
        ::stbi_write_jpg_to_func(
            stb::write_function<gl::byte_t>              , 
            &vector, dimensions.x, dimensions.y, channels, 
            data.data(), gl::int32_t{ 100u }            );

        return vector;
    }
    auto write_png_to_function       (std::span<const gl::byte_t> data, gl::uint32_t channels, const gl::vector2u& dimensions) -> std::vector<gl::byte_t>
    {
        auto vector = std::vector<gl::byte_t>{};
        ::stbi_write_png_to_func(
            stb::write_function<gl::byte_t>              , 
            &vector, dimensions.x, dimensions.y, channels, 
            data.data(), channels * dimensions.x        );

        return vector;
    }
}
