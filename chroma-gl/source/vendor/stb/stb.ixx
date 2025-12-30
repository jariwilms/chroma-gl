export module stb;

import std;
import <stb/stb_image.h>;
import <stb/stb_image_write.h>;

export namespace stb
{
    using void_t    = void         ;
    using bool_t    = bool         ;
    using int8_t    = std::int8_t  ;
    using int16_t   = std::int16_t ;
    using int32_t   = std::int32_t ;
    using int64_t   = std::int64_t ;
    using uint8_t   = std::uint8_t ;
    using uint16_t  = std::uint16_t;
    using uint32_t  = std::uint32_t;
    using uint64_t  = std::uint64_t;
    using float32_t = float        ;
    using float64_t = double       ;
    
    using byte_t    = std::uint8_t ;
    using size_t    = std::size_t  ;

    template<typename T>
    struct vector
    {
        T x;
        T y;
    };
    using vector_2i = stb::vector<stb::int32_t >;
    using vector_2u = stb::vector<stb::uint32_t>;
}
       namespace stb
{
    template<typename T>
    void write_function(stb::void_t* context, stb::void_t* data, stb::int32_t size)
    {
        auto* vector  = reinterpret_cast<std::vector<T>*>(context);
        auto* pointer = reinterpret_cast<const T*>(data);
        auto  span    = std::span<const T>{ pointer, static_cast<stb::size_t>(size) };

        vector->append_range(span);
    }
    void free_image    (stb::void_t* pointer)
    {
        ::stbi_image_free(pointer);
    }
}
export namespace stb
{
    struct image
    {
        stb::uint32_t            channels;
        stb::vector_2u           dimensions;
        std::vector<stb::byte_t> memory;
    };

    void set_flip_vertically_on_load (stb::bool_t value)
    {
        ::stbi_set_flip_vertically_on_load(value);
    }
    void set_flip_vertically_on_write(stb::bool_t value)
    {
        ::stbi_flip_vertically_on_write(value);
    }

    template<typename T>
    auto load_from_memory            (stb::uint32_t required_channels, std::span<const stb::byte_t> memory) -> stb::image
    {
        auto* pointer    = static_cast<stb::byte_t*>(nullptr);
        auto  size       = stb::size_t{};
        auto  dimensions = stb::vector_2i{};
        auto  channels   = std::int32_t{};

        if constexpr (std::is_same_v<T, stb::byte_t   >)
        {
            pointer = std::bit_cast<stb::byte_t*>(::stbi_load_from_memory(memory.data(), static_cast<std::int32_t>(memory.size_bytes()), &dimensions.x, &dimensions.y, &channels, required_channels));
            size    = sizeof(stb::byte_t) * required_channels * dimensions.x * dimensions.y;
        }
        if constexpr (std::is_same_v<T, stb::uint16_t >)
        {
            pointer = std::bit_cast<stb::byte_t*>(::stbi_load_16_from_memory(memory.data(), static_cast<std::int32_t>(memory.size_bytes()), &dimensions.x, &dimensions.y, &channels, required_channels));
            size    = sizeof(stb::uint16_t) * required_channels * dimensions.x * dimensions.y;
        }
        if constexpr (std::is_same_v<T, stb::float32_t>)
        {
            pointer = std::bit_cast<stb::byte_t*>(::stbi_loadf_from_memory(memory.data(), static_cast<std::int32_t>(memory.size_bytes()), &dimensions.x, &dimensions.y, &channels, required_channels));
            size    = sizeof(stb::float32_t) * required_channels * dimensions.x * dimensions.y;
        }

        const auto span  = std::span<stb::byte_t>{ pointer, size };
        const auto image = stb::image
        {
            .channels   = static_cast<stb::uint32_t>   (channels  )        , 
            .dimensions = std::bit_cast<stb::vector_2u>(dimensions)        , 
            .memory     = std::vector<stb::byte_t>{ std::from_range, span }, 
        };

        stb::free_image(pointer);
        return image;
    }

    auto write_bmp                   (stb::vector_2u dimensions, stb::uint32_t channels, std::span<stb::byte_t const> memory) -> std::vector<stb::byte_t>
    {
        auto vector = std::vector<stb::byte_t>{};
        ::stbi_write_bmp_to_func(
            stb::write_function<stb::byte_t>   , 
            &vector, dimensions.x, dimensions.y, 
            channels, memory.data()           );

        return vector;
    }
    auto write_hdr                   (stb::vector_2u dimensions, stb::uint32_t channels, std::span<stb::byte_t const> memory) -> std::vector<stb::float32_t>
    {
        auto vector = std::vector<stb::float32_t>{};
        ::stbi_write_hdr_to_func(
            stb::write_function<stb::float32_t>                 , 
            &vector, dimensions.x, dimensions.y, channels       , 
            std::bit_cast<const stb::float32_t*>(memory.data()));

        return vector;
    }
    auto write_jpg                   (stb::vector_2u dimensions, stb::uint32_t channels, std::span<stb::byte_t const> memory) -> std::vector<stb::byte_t>
    {
        auto vector = std::vector<stb::byte_t>{};
        ::stbi_write_jpg_to_func(
            stb::write_function<stb::byte_t>             , 
            &vector, dimensions.x, dimensions.y, channels, 
            memory.data(), std::int32_t{ 100u }         );

        return vector;
    }
    auto write_png                   (stb::vector_2u dimensions, stb::uint32_t channels, std::span<stb::byte_t const> memory) -> std::vector<stb::byte_t>
    {
        auto vector = std::vector<stb::byte_t>{};
        ::stbi_write_png_to_func(
            stb::write_function<stb::byte_t>             , 
            &vector, dimensions.x, dimensions.y, channels, 
            memory.data(), channels * dimensions.x      );

        return vector;
    }
}
