export module opengl.image;

import std;
import opengl.config;
import opengl.types;
import vendor.stb;

export namespace gl
{
    class image
    {
    public:
        enum class format_e
        {
            r8         , rg8         , rgb8       , rgba8       , 
            r16        , rg16        , rgb16      , rgba16      , 
            rgb16_float, rgba16_float, rgb32_float, rgba32_float, 
        };
        enum class extension_e
        {
            bmp,
            hdr,
            jpg,
            png,
        };

        template<std::ranges::range R>
        explicit image(format_e format, const gl::vector2u& dimensions, R&& range)
            : format_{ format }, dimensions_{ dimensions }, data_{ std::from_range, std::forward<R>(range) } {}

        template<extension_e E>
        static auto encode(const gl::image& image) -> auto
        {
            stb::set_flip_vertically_on_write(config::flip_images);

            const auto channels   = map_channels(format_);
            const auto dimensions = image.dimensions();
            const auto data       = image.data();
            
            using enum extension_e;
            if constexpr (E == bmp) return stb::write_bmp_to_function(data, channels, dimensions);
            if constexpr (E == jpg) return stb::write_jpg_to_function(data, channels, dimensions);
            if constexpr (E == png) return stb::write_png_to_function(data, channels, dimensions);
            if constexpr (E == hdr) return stb::write_hdr_to_function(data, channels, dimensions);
        }
        static auto decode(format_e format, std::span<const gl::byte_t> data) -> gl::image
        {
            stb::set_flip_vertically_on_load(gl::config::flip_images);
            
            const auto channels  = map_channels(format);
            const auto stb_image = std::invoke([&](format_e format)
                {
                    switch (format)
                    {
                        using enum format_e;

                        case r8         : case rg8         : case rgb8       : case rgba8       : return stb::load_from_memory<gl::uint8_t  >(channels, data);
                        case r16        : case rg16        : case rgb16      : case rgba16      : return stb::load_from_memory<gl::uint16_t >(channels, data);
                        case rgb16_float: case rgba16_float: case rgb32_float: case rgba32_float: return stb::load_from_memory<gl::float32_t>(channels, data);

                        default: throw std::invalid_argument{ "Invalid format!" };
                    };
                }, format);

            return gl::image{ format, stb_image.dimensions, std::move(stb_image.data) };
        }

        auto format    () const -> format_e
        {
            return format_;
        }
        auto dimensions() const -> const gl::vector2u&
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
                        
                case r8   : case r16   :                                       return gl::uint32_t{ 1u };
                case rg8  : case rg16  :                                       return gl::uint32_t{ 2u };
                case rgb8 : case rgb16 : case rgb16_float : case rgb32_float : return gl::uint32_t{ 3u };
                case rgba8: case rgba16: case rgba16_float: case rgba32_float: return gl::uint32_t{ 4u };

                default: throw std::invalid_argument{ "Invalid format!" };
            }
        }

        format_e                format_;
        gl::vector2u            dimensions_;
        std::vector<gl::byte_t> data_;
    };
}
