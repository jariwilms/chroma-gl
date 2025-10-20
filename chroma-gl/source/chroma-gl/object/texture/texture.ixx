export module opengl.object.texture;

import std;
import opengl;
import opengl.context.state.texture;
import opengl.object;
import opengl.object.buffer;

export namespace gl
{
    enum class texture_filter_e
    {
        none     , 
        nearest  , 
        bilinear , 
        trilinear, 
    };
    
    auto map_texture_minification_filter (gl::texture_filter_e filter) -> gl::texture_minification_filter_e
    {
        switch (filter)
        {
            using enum gl::texture_filter_e;

            case none     : return gl::texture_minification_filter_e::nearest               ;
            case nearest  : return gl::texture_minification_filter_e::nearest_mipmap_nearest;
            case bilinear : return gl::texture_minification_filter_e::linear_mipmap_nearest ;
            case trilinear: return gl::texture_minification_filter_e::linear_mipmap_linear  ;

            default: throw std::invalid_argument{ "invalid filter" };
        }
    }
    auto map_texture_magnification_filter(gl::texture_filter_e filter) -> gl::texture_magnification_filter_e
    {
        switch (filter)
        {
            using enum gl::texture_filter_e;

            case none     : return gl::texture_magnification_filter_e::nearest;
            case nearest  : return gl::texture_magnification_filter_e::nearest;
            case bilinear : return gl::texture_magnification_filter_e::linear ;
            case trilinear: return gl::texture_magnification_filter_e::linear ;

            default: throw std::invalid_argument{ "invalid filter" };
        }
    }
    auto map_texture_format_size         (gl::texture_format_e texture_format) -> gl::size_t
    {
        switch (texture_format)
        {
            using enum gl::texture_format_e;

            case r_int8_n                    : return  1u;
            case r_int16_n                   : return  2u;
            case r_uint8_n                   : return  1u;
            case r_uint16_n                  : return  2u;
            case r_float16                   : return  2u;
            case r_float32                   : return  4u;

            case rg_int8_n                   : return  2u;
            case rg_int16_n                  : return  4u;
            case rg_uint8_n                  : return  2u;
            case rg_uint16_n                 : return  4u;
            case rg_float16                  : return  4u;
            case rg_float32                  : return  8u;

            case rgb_int8_n                  : return  3u;
            case rgb_int16_n                 : return  6u;
            case rgb_uint8_n                 : return  3u;
            case rgb_uint16_n                : return  6u;
            case rgb_float16                 : return  6u;
            case rgb_float32                 : return 12u;

            case rgba_int8_n                 : return  4u;
            case rgba_int16_n                : return  8u;
            case rgba_uint8_n                : return  4u;
            case rgba_uint16_n               : return  8u;
            case rgba_float16                : return  8u;
            case rgba_float32                : return 16u;

            case srgb_uint8                  : return  3u;
            case srgba_uint8                 : return  4u;

            case depth_uint16_n              : return  2u;
            case depth_uint24_n              : return  3u;
            case depth_float32               : return  4u;
            case stencil_uint8               : return  1u;
            case depth_stencil_uint24_n_uint8: return  4u;
            case depth_stencil_float32_uint8 : return  5u;

            default                          : throw std::invalid_argument{ "invalid format" };
        }
    }
    auto map_texture_target              (gl::uint32_t dimensions) -> gl::texture_target_e
    {
        switch (dimensions)
        {
            case 1u: return gl::texture_target_e::_1d;
            case 2u: return gl::texture_target_e::_2d;
            case 3u: return gl::texture_target_e::_3d;

            default: throw std::invalid_argument{ "invalid dimensions" };
        }
    }


    
    template<gl::uint32_t Dimensions>
    class texture_n : public gl::object
    {
    public:
        using format_e = gl::texture_format_e;
        using vector_t = gl::vector_t<gl::uint32_t, Dimensions>;
        using region_t = gl::region_t<gl::uint32_t, Dimensions>;

        texture_n(format_e format, const vector_t& dimensions,                              gl::bool_t allocate_mipmaps = gl::true_)
            : gl::object{ gl::create_texture(gl::map_texture_target(Dimensions)) }
            , format_{ format }, dimensions_{ dimensions }, mipmap_levels_{ 1u }
        {
            if (allocate_mipmaps) mipmap_levels_ = gl::mipmap_levels(dimensions_);

            if constexpr (Dimensions == gl::uint32_t{ 1u }) gl::texture_storage_1d(handle(), format_, dimensions_, mipmap_levels_);
            if constexpr (Dimensions == gl::uint32_t{ 2u }) gl::texture_storage_2d(handle(), format_, dimensions_, mipmap_levels_);
            if constexpr (Dimensions == gl::uint32_t{ 3u }) gl::texture_storage_3d(handle(), format_, dimensions_, mipmap_levels_);
        }
        texture_n(format_e format, const vector_t& dimensions, const state::texture& state, gl::bool_t allocate_mipmaps = gl::true_)
            : texture_n{ format, dimensions, allocate_mipmaps }
        {
            apply(state);
        }
        texture_n(texture_n&&) noexcept = default;
       ~texture_n()
        {
           gl::delete_texture(handle());
        }

        void bind           (gl::binding_t slot)
        {
            gl::bind_texture_unit(handle(), slot);
        }

        template<gl::texture_parameter_e Parameter>
        void apply          (auto value)
        {
            gl::texture_parameter<Parameter>(handle(), value);
        }
        void apply          (const state::texture& state)
        {
            using enum gl::texture_parameter_e;

            apply<base_level          >(state.base_level          );
            apply<maximum_level       >(state.maximum_level       );
            apply<border_color        >(state.border_color        );
            apply<compare_function    >(state.compare_function    );
            apply<compare_mode        >(state.compare_mode        );
            apply<minification_filter >(state.minification_filter );
            apply<magnification_filter>(state.magnification_filter);
            apply<wrapping_r          >(state.wrapping_r          );
            apply<wrapping_s          >(state.wrapping_s          );
            apply<wrapping_t          >(state.wrapping_t          );
            apply<swizzle_r           >(state.swizzle_r           );
            apply<swizzle_g           >(state.swizzle_g           );
            apply<swizzle_b           >(state.swizzle_b           );
            apply<swizzle_a           >(state.swizzle_a           );
            apply<maximum_anisotropy  >(state.maximum_anisotropy  );
            apply<minimum_lod         >(state.minimum_lod         );
            apply<maximum_lod         >(state.maximum_lod         );
            apply<lod_bias            >(state.lod_bias            );
        }
        
        void transfer       (                                                 gl::pixel_buffer_data pixel_buffer_data, std::span<const gl::byte_t> memory)
        {
            transfer(gl::uint32_t{ 0u }, dimensions_, pixel_buffer_data, memory);
        }
        void transfer       (gl::uint32_t image_level, region_t image_region, gl::pixel_buffer_data pixel_buffer_data, std::span<const gl::byte_t> memory)
        {
            if constexpr (Dimensions == gl::uint32_t{ 1u }) gl::texture_sub_image_1d(handle(), pixel_buffer_data.texture_base_format, pixel_buffer_data.pixel_data_type, image_level, image_region, memory);
            if constexpr (Dimensions == gl::uint32_t{ 2u }) gl::texture_sub_image_2d(handle(), pixel_buffer_data.texture_base_format, pixel_buffer_data.pixel_data_type, image_level, image_region, memory);
            if constexpr (Dimensions == gl::uint32_t{ 3u }) gl::texture_sub_image_3d(handle(), pixel_buffer_data.texture_base_format, pixel_buffer_data.pixel_data_type, image_level, image_region, memory);
        }
        void transfer       (gl::uint32_t image_level, region_t image_region, gl::pixel_unpack_buffer& pixel_unpack_buffer                               )
        {
            pixel_unpack_buffer.bind();
            transfer(image_level, image_region, pixel_unpack_buffer.pixel_buffer_data(), std::span<const gl::byte_t>{});
        }
        void generate_mipmap()
        {
            gl::generate_texture_mipmap(handle());
        }

        auto format         () const -> format_e
        {
            return format_;
        }
        auto dimensions     () const -> const gl::vector_3u&
        {
            return dimensions_;
        }
        auto mipmap_levels  () const -> gl::uint32_t
        {
            return mipmap_levels_;
        }

        auto operator=      (texture_n&&) noexcept -> texture_n& = default;

    private:
        format_e     format_;
        vector_t     dimensions_;
        gl::uint32_t mipmap_levels_;
    };
    template<gl::uint32_t Dimensions>
    class compressed_texture_n : public gl::texture_n<Dimensions>
    {
    public:
        using format_e = gl::texture_compressed_format_e;
        using vector_t = gl::texture_n<Dimensions>::vector_t;
        using region_t = gl::texture_n<Dimensions>::region_t;

        compressed_texture_n(format_e format, const vector_t& dimensions, gl::bool_t allocate_mipmaps = gl::true_)
            : gl::texture_n<Dimensions>{ static_cast<gl::texture_n<Dimensions>::format_e>(format), dimensions, allocate_mipmaps } {}

        void transfer(                                                 gl::compressed_pixel_buffer_data compressed_pixel_buffer_data, std::span<const gl::byte_t> memory)
        {
            transfer(gl::uint32_t{ 0u }, this->dimensions(), compressed_pixel_buffer_data, memory);
        }
        void transfer(gl::uint32_t image_level, region_t image_region, gl::compressed_pixel_buffer_data compressed_pixel_buffer_data, std::span<const gl::byte_t> memory)
        {
            if constexpr (Dimensions == gl::uint32_t{ 1u }) gl::compressed_texture_sub_image_1d(this->handle(), compressed_pixel_buffer_data.texture_compressed_base_format, image_level, image_region, memory);
            if constexpr (Dimensions == gl::uint32_t{ 2u }) gl::compressed_texture_sub_image_2d(this->handle(), compressed_pixel_buffer_data.texture_compressed_base_format, image_level, image_region, memory);
            if constexpr (Dimensions == gl::uint32_t{ 3u }) gl::compressed_texture_sub_image_3d(this->handle(), compressed_pixel_buffer_data.texture_compressed_base_format, image_level, image_region, memory);
        }
        void transfer(gl::uint32_t image_level, region_t image_region, gl::pixel_unpack_buffer& pixel_unpack_buffer                                                     )
        {
            pixel_unpack_buffer.bind();
            transfer(image_level, image_region, pixel_unpack_buffer.pixel_buffer_data(), std::span<const gl::byte_t>{});
        }
    };

    using texture_1d            = gl::texture_n           <1u>;
    using texture_2d            = gl::texture_n           <2u>;
    using texture_3d            = gl::texture_n           <3u>;
    using compressed_texture_1d = gl::compressed_texture_n<1u>;
    using compressed_texture_2d = gl::compressed_texture_n<2u>;
    using compressed_texture_3d = gl::compressed_texture_n<3u>;
}
