export module opengl.object.texture;

import std;
import opengl;
import opengl.object;
import opengl.object.buffer;

export namespace gl
{
    template<gl::uint32_t Dimensions>
    class texture_n : public gl::object
    {
    public:
        using format_e = gl::texture_format_e;
        using vector_t = gl::vector_t<gl::uint32_t, Dimensions>;
        using region_t = gl::region_t<gl::uint32_t, Dimensions>;

        explicit
        texture_n(format_e format, const vector_t& dimensions,                                         gl::bool_t allocate_mipmaps = gl::true_)
            : gl::object{ gl::create_texture(gl::map_texture_target(Dimensions)) }
            , format_{ format }, dimensions_{ dimensions }, mipmap_levels_{ 1u }
        {
            if (allocate_mipmaps) mipmap_levels_ = gl::mipmap_levels(dimensions_);

            if constexpr (Dimensions == gl::uint32_t{ 1u }) gl::texture_storage_1d(handle(), format_, dimensions_, mipmap_levels_);
            if constexpr (Dimensions == gl::uint32_t{ 2u }) gl::texture_storage_2d(handle(), format_, dimensions_, mipmap_levels_);
            if constexpr (Dimensions == gl::uint32_t{ 3u }) gl::texture_storage_3d(handle(), format_, dimensions_, mipmap_levels_);
        }
        explicit
        texture_n(format_e format, const vector_t& dimensions, const gl::texture_state& texture_state, gl::bool_t allocate_mipmaps = gl::true_)
            : texture_n{ format, dimensions, allocate_mipmaps }
        {
            apply(texture_state);
        }
        texture_n(texture_n&&) noexcept = default;
       ~texture_n()
        {
           gl::delete_texture(handle());
        }

        void bind            (gl::binding_t slot)
        {
            gl::bind_texture_unit(handle(), slot);
        }

        void upload          (                                                 gl::texture_data_descriptor texture_data_descriptor, std::span<const gl::byte_t> memory)
        {
            upload(gl::uint32_t{ 0u }, dimensions_, texture_data_descriptor, memory);
        }
        void upload          (gl::uint32_t image_level, region_t image_region, gl::texture_data_descriptor texture_data_descriptor, std::span<const gl::byte_t> memory)
        {
            if constexpr (Dimensions == gl::uint32_t{ 1u }) gl::texture_sub_image_1d(handle(), image_level, image_region, texture_data_descriptor, memory);
            if constexpr (Dimensions == gl::uint32_t{ 2u }) gl::texture_sub_image_2d(handle(), image_level, image_region, texture_data_descriptor, memory);
            if constexpr (Dimensions == gl::uint32_t{ 3u }) gl::texture_sub_image_3d(handle(), image_level, image_region, texture_data_descriptor, memory);
        }
        void generate_mipmaps()
        {
            gl::generate_texture_mipmaps(handle());
        }
        
        template<gl::texture_parameter_e Parameter>
        void apply           (auto value)
        {
            gl::texture_parameter<Parameter>(handle(), value);
        }
        void apply           (const gl::texture_state& texture_state)
        {
            using enum gl::texture_parameter_e;

            apply<base_level          >(texture_state.base_level          );
            apply<maximum_level       >(texture_state.maximum_level       );
            apply<border_color        >(texture_state.border_color        );
            apply<compare_function    >(texture_state.compare_function    );
            apply<compare_mode        >(texture_state.compare_mode        );
            apply<minification_filter >(texture_state.minification_filter );
            apply<magnification_filter>(texture_state.magnification_filter);
            apply<wrapping_r          >(texture_state.wrapping_r          );
            apply<wrapping_s          >(texture_state.wrapping_s          );
            apply<wrapping_t          >(texture_state.wrapping_t          );
            apply<swizzle_r           >(texture_state.swizzle_r           );
            apply<swizzle_g           >(texture_state.swizzle_g           );
            apply<swizzle_b           >(texture_state.swizzle_b           );
            apply<swizzle_a           >(texture_state.swizzle_a           );
            apply<maximum_anisotropy  >(texture_state.maximum_anisotropy  );
            apply<minimum_lod         >(texture_state.minimum_lod         );
            apply<maximum_lod         >(texture_state.maximum_lod         );
            apply<lod_bias            >(texture_state.lod_bias            );
        }

        auto format          () const -> format_e
        {
            return format_;
        }
        auto dimensions      () const -> const vector_t&
        {
            return dimensions_;
        }
        auto mipmap_levels   () const -> gl::uint32_t
        {
            return mipmap_levels_;
        }

        auto operator=       (texture_n&&) noexcept -> texture_n& = default;

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

        explicit
        compressed_texture_n(format_e format, const vector_t& dimensions, gl::bool_t allocate_mipmaps = gl::true_)
            : gl::texture_n<Dimensions>{ static_cast<gl::texture_n<Dimensions>::format_e>(format), dimensions, allocate_mipmaps } {}

        void upload(                                                 gl::compressed_texture_data_descriptor compressed_texture_data_descriptor, std::span<const gl::byte_t> memory)
        {
            upload(gl::uint32_t{ 0u }, gl::texture_n<Dimensions>::dimensions(), compressed_texture_data_descriptor.base_format, memory);
        }
        void upload(gl::uint32_t image_level, region_t image_region, gl::compressed_texture_data_descriptor compressed_texture_data_descriptor, std::span<const gl::byte_t> memory)
        {
            if constexpr (Dimensions == gl::uint32_t{ 1u }) gl::compressed_texture_sub_image_1d(gl::texture_n<Dimensions>::handle(), image_level, image_region, compressed_texture_data_descriptor.base_format, memory);
            if constexpr (Dimensions == gl::uint32_t{ 2u }) gl::compressed_texture_sub_image_2d(gl::texture_n<Dimensions>::handle(), image_level, image_region, compressed_texture_data_descriptor.base_format, memory);
            if constexpr (Dimensions == gl::uint32_t{ 3u }) gl::compressed_texture_sub_image_3d(gl::texture_n<Dimensions>::handle(), image_level, image_region, compressed_texture_data_descriptor.base_format, memory);
        }
    };
    template<gl::uint32_t Dimensions>
    class multisampled_texture_n : public gl::object
    {
    public:
        using format_e = gl::texture_format_e;
        using vector_t = gl::vector_t<gl::uint32_t, Dimensions>;

        explicit
        multisampled_texture_n(format_e format, const vector_t& dimensions, gl::uint32_t sample_count, gl::bool_t use_fixed_sample_locations = gl::true_)
            : gl::object{ gl::create_texture(gl::map_texture_target_multisample(Dimensions)) }
            , format_{ format }, dimensions_{ dimensions }, sample_count_{ sample_count }, has_fixed_sample_locations_{ use_fixed_sample_locations }
        {
            if constexpr (Dimensions == gl::uint32_t{ 2u }) gl::texture_storage_2d_multisample(handle(), format_, dimensions_, sample_count, has_fixed_sample_locations_);
            if constexpr (Dimensions == gl::uint32_t{ 3u }) gl::texture_storage_3d_multisample(handle(), format_, dimensions_, sample_count, has_fixed_sample_locations_);
        }
        multisampled_texture_n(multisampled_texture_n&&) noexcept = default;
       ~multisampled_texture_n()
        {
            gl::delete_texture(handle());
        }

        void bind                      (gl::binding_t slot)
        {
            gl::bind_texture_unit(handle(), slot);
        }

        auto format                    () const -> format_e
        {
            return format_;
        }
        auto dimensions                () const -> const gl::vector_3u&
        {
            return dimensions_;
        }
        auto sample_count              () const -> gl::count_t
        {
            return sample_count_;
        }
        auto has_fixed_sample_locations() const -> gl::bool_t
        {
            return has_fixed_sample_locations_;
        }

        auto operator=                 (multisampled_texture_n&&) noexcept -> multisampled_texture_n& = default;

    private:
        format_e     format_;
        vector_t     dimensions_;
        gl::uint32_t sample_count_;
        gl::bool_t   has_fixed_sample_locations_;
    };



    using texture_1d              = gl::texture_n             <1u>;
    using texture_2d              = gl::texture_n             <2u>;
    using texture_3d              = gl::texture_n             <3u>;
    using compressed_texture_1d   = gl::compressed_texture_n  <1u>;
    using compressed_texture_2d   = gl::compressed_texture_n  <2u>;
    using compressed_texture_3d   = gl::compressed_texture_n  <3u>;
    using multisampled_texture_2d = gl::multisampled_texture_n<2u>;
    using multisampled_texture_3d = gl::multisampled_texture_n<3u>;
}
