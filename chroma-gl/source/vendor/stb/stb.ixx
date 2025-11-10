export module stb;

import std;
import <stb/stb_image.h>;
import <stb/stb_image_write.h>;

       namespace stb
{
    template<typename T>
    void write_function(void* context, void* data, std::int32_t size)
    {
        auto* vector  = std::bit_cast<std::vector<T>*>(context);
        auto* pointer = std::bit_cast<const T*>(data);
        auto  span    = std::span<const T>{ pointer, static_cast<std::size_t>(size) };

        vector->append_range(span);
    }
    void free_image    (void* pointer)
    {
        ::stbi_image_free(pointer);
    }
}
export namespace stb
{
    using bool_t    = bool         ;
    using byte_t    = std::uint8_t ;
    using int8_t    = std::int8_t  ;
    using int16_t   = std::int16_t ;
    using int32_t   = std::int32_t ;
    using int64_t   = std::int64_t ;
    using uint8_t   = std::uint8_t ;
    using uint16_t  = std::uint16_t;
    using uint32_t  = std::uint32_t;
    using uint64_t  = std::uint64_t;
    using float32_t = float        ;

    struct image_data
    {
        stb::uint32_t                  channels;
        std::array <stb::uint32_t, 2u> dimensions;
        std::vector<stb::byte_t      > data;
    };



    void set_flip_vertically_on_load (bool value)
    {
        ::stbi_set_flip_vertically_on_load(value);
    }
    void set_flip_vertically_on_write(bool value)
    {
        ::stbi_flip_vertically_on_write(value);
    }

    template<typename T>
    auto load_from_memory            (stb::uint32_t required_channels, std::span<const stb::byte_t> data) -> stb::image_data
    {
        auto* pointer    = static_cast<stb::byte_t*>(nullptr);
        auto  size       = std::size_t{};
        auto  dimensions = std::array<std::int32_t, 2u>{};
        auto  channels   = std::int32_t {};

        if constexpr (std::is_same_v<T, stb::byte_t  >)
        {
            pointer = std::bit_cast<stb::byte_t*>(::stbi_load_from_memory(data.data(), static_cast<std::int32_t>(data.size_bytes()), &dimensions[0u], &dimensions[1u], &channels, required_channels));
            size    = sizeof(stb::byte_t) * required_channels * dimensions[0u] * dimensions[1u];
        }
        if constexpr (std::is_same_v<T, stb::uint16_t >)
        {
            pointer = std::bit_cast<stb::byte_t*>(::stbi_load_16_from_memory(data.data(), static_cast<std::int32_t>(data.size_bytes()), &dimensions[0u], &dimensions[1u], &channels, required_channels));
            size    = sizeof(stb::uint16_t) * required_channels * dimensions[0u] * dimensions[1u];
        }
        if constexpr (std::is_same_v<T, stb::float32_t>)
        {
            pointer = std::bit_cast<stb::byte_t*>(::stbi_loadf_from_memory(data.data(), static_cast<std::int32_t>(data.size_bytes()), &dimensions[0u], &dimensions[1u], &channels, required_channels));
            size    = sizeof(stb::float32_t) * required_channels * dimensions[0u] * dimensions[1u];
        }

        const auto span       = std::span<stb::byte_t>{ pointer, size };
        const auto image_data = stb::image_data
        {
            .channels   = static_cast<stb::uint32_t>(channels  )                  , 
            .dimensions = std::bit_cast<std::array<stb::uint32_t, 2u>>(dimensions), 
            .data       = std::vector<stb::byte_t>{ std::from_range, span }       , 
        };

        stb::free_image(pointer);
        return image_data;
    }

    auto write_bmp_to_function       (std::span<const stb::byte_t> data, stb::uint32_t channels, const std::array<stb::uint32_t, 2u>& dimensions) -> std::vector<stb::byte_t>
    {
        auto vector = std::vector<stb::byte_t>{};
        ::stbi_write_bmp_to_func(
            stb::write_function<stb::byte_t>      ,
            &vector, dimensions[0u], dimensions[1u],
            channels, data.data()                 );

        return vector;
    }
    auto write_hdr_to_function       (std::span<const stb::byte_t> data, stb::uint32_t channels, const std::array<stb::uint32_t, 2u>& dimensions) -> std::vector<stb::float32_t>
    {
        auto vector = std::vector<stb::float32_t>{};
        ::stbi_write_hdr_to_func(
            stb::write_function<stb::float32_t>               , 
            &vector, dimensions[0u], dimensions[1u], channels, 
            std::bit_cast<const stb::float32_t*>(data.data()));

        return vector;
    }
    auto write_jpg_to_function       (std::span<const stb::byte_t> data, stb::uint32_t channels, const std::array<stb::uint32_t, 2u>& dimensions) -> std::vector<stb::byte_t>
    {
        auto vector = std::vector<stb::byte_t>{};
        ::stbi_write_jpg_to_func(
            stb::write_function<stb::byte_t>                ,
            &vector, dimensions[0u], dimensions[1u], channels, 
            data.data(), std::int32_t{ 100u }               );

        return vector;
    }
    auto write_png_to_function       (std::span<const stb::byte_t> data, stb::uint32_t channels, const std::array<stb::uint32_t, 2u>& dimensions) -> std::vector<stb::byte_t>
    {
        auto vector = std::vector<stb::byte_t>{};
        ::stbi_write_png_to_func(
            stb::write_function<stb::byte_t>                ,
            &vector, dimensions[0u], dimensions[1u], channels, 
            data.data(), channels * dimensions[0u]          );

        return vector;
    }
}
