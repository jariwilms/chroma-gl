export module chroma_gl:io.image;

import std;
import stb;
import opengl;
import :config;

export namespace gl
{
    class image
    {
    public:
        enum class format_e
        {
            r_uint8     , 
            r_uint16    , 
            
            rg_uint8    , 
            rg_uint16   , 
            
            rgb_uint8   , 
            rgb_uint16  , 
            rgb_float16 , 
            rgb_float32 , 
            
            rgba_uint8  , 
            rgba_uint16 , 
            rgba_float16, 
            rgba_float32, 
        };
        enum class extension_e
        {
            bmp, 
            hdr, 
            jpg, 
            png, 
        };

        template<std::ranges::range R>
        explicit image(format_e format, const gl::vector_2u& dimensions, R&& source)
            : format_{ format }, dimensions_{ dimensions }, data_{ std::from_range, std::forward<R>(source) } {}

        template<extension_e E>
        static auto encode(format_e format, const gl::image& image) -> auto
        {
            stb::set_flip_vertically_on_write(config::flip_images_vertically);

            const auto channels   = map_channels(format);
            const auto dimensions = image.dimensions();
            const auto data       = image.data();
            
            using enum extension_e;
            if constexpr (E == bmp) return stb::write_bmp(data, channels, std::bit_cast<std::array<stb::uint32_t, 2u>>(dimensions));
            if constexpr (E == hdr) return stb::write_hdr(data, channels, std::bit_cast<std::array<stb::uint32_t, 2u>>(dimensions));
            if constexpr (E == jpg) return stb::write_jpg(data, channels, std::bit_cast<std::array<stb::uint32_t, 2u>>(dimensions));
            if constexpr (E == png) return stb::write_png(data, channels, std::bit_cast<std::array<stb::uint32_t, 2u>>(dimensions));
        }
        static auto decode(format_e format, std::span<const gl::byte_t> data) -> gl::image
        {
            stb::set_flip_vertically_on_load(gl::config::flip_images_vertically);
            
            const auto channels   = map_channels(format);
            const auto stb_image  = std::invoke([&](format_e format)
                {
                    switch (format)
                    {
                        using enum format_e;

                        case r_uint8    : case rg_uint8    : case rgb_uint8  : case rgba_uint8  : return stb::load_from_memory<gl::uint8_t  >(channels, data);
                        case r_uint16   : case rg_uint16   : case rgb_uint16 : case rgba_uint16 : return stb::load_from_memory<gl::uint16_t >(channels, data);
                        case rgb_float16: case rgba_float16: case rgb_float32: case rgba_float32: return stb::load_from_memory<gl::float32_t>(channels, data);

                        default         : throw std::invalid_argument{ "invalid format" };
                    };
                }, format);
            const auto dimensions = std::bit_cast<gl::vector_2u>(stb_image.dimensions);

            return gl::image{ format, dimensions, std::move(stb_image.data) };
        }

        auto format    () const -> format_e
        {
            return format_;
        }
        auto dimensions() const -> const gl::vector_2u&
        {
            return dimensions_;
        }
        auto data      () const -> std::span<const gl::byte_t>
        {
            return data_;
        }

    private:
        static auto map_channels(format_e format) -> gl::uint32_t
        {
            switch (format)
            {
                using enum format_e;
                        
                case r_uint8   : case r_uint16   :                                       return gl::uint32_t{ 1u };
                case rg_uint8  : case rg_uint16  :                                       return gl::uint32_t{ 2u };
                case rgb_uint8 : case rgb_uint16 : case rgb_float16 : case rgb_float32 : return gl::uint32_t{ 3u };
                case rgba_uint8: case rgba_uint16: case rgba_float16: case rgba_float32: return gl::uint32_t{ 4u };

                default        : throw std::invalid_argument{ "invalid format" };
            }
        }

        format_e                format_;
        gl::vector_2u           dimensions_;
        std::vector<gl::byte_t> data_;
    };
}
