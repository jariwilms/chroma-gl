export module chroma_gl:object.cubemap;

import std;
import opengl;
import :object;
import :object.buffer;
import :object.texture;

export namespace gl
{
    class cubemap : public gl::texture
    {
    public:
        using format_e = gl::texture_format_e;
        using face_e   = gl::cubemap_face_e;

        explicit
        cubemap(format_e format, const gl::vector_1u& dimensions, gl::bool_t allocate_mipmaps = gl::true_)
            : gl::texture{ gl::texture_target_e::cubemap }
            , format_{ format }, dimensions_{ dimensions.x }, mipmap_levels_{ 1u }
        {
            if (allocate_mipmaps) mipmap_levels_ = gl::mipmap_levels(dimensions_);

            gl::texture_storage_2d(handle(), format_, dimensions_, mipmap_levels_);
        }
        
        void upload          (face_e face,                                                  gl::texture_data_descriptor texture_data_descriptor,                 std::span<const gl::byte_t>      memory)
        {
            upload(face, gl::uint32_t{ 0u }, dimensions_, texture_data_descriptor, memory);
        }
        void upload          (face_e face, gl::uint32_t image_level, gl::area_t image_area, gl::texture_data_descriptor texture_data_descriptor,                 std::span<const gl::byte_t>      memory)
        {
            const auto image_volume = gl::volume_t{ gl::vector_3u{ image_area.origin, gl::to_underlying(face - face_e::positive_x) }, gl::vector_3u{ image_area.extent, 1u }, };
            gl::texture_sub_image_3d(handle(), image_level, image_volume, texture_data_descriptor, memory);
        }
        void upload          (                                                              gl::texture_data_descriptor texture_data_descriptor, std::span<const std::span<const gl::byte_t>, 6u> memory)
        {
            for (const auto [face_index, face_memory] : std::views::enumerate(memory))
            {
                upload(face_e::positive_x + face_index, texture_data_descriptor, face_memory);
            }
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
        void apply           (const gl::state::texture& state)
        {
            apply<gl::texture_parameter_e::base_level          >(state.base_level          );
            apply<gl::texture_parameter_e::maximum_level       >(state.maximum_level       );
            apply<gl::texture_parameter_e::border_color        >(state.border_color        );
            apply<gl::texture_parameter_e::compare_function    >(state.compare_function    );
            apply<gl::texture_parameter_e::compare_mode        >(state.compare_mode        );
            apply<gl::texture_parameter_e::minification_filter >(state.minification_filter );
            apply<gl::texture_parameter_e::magnification_filter>(state.magnification_filter);
            apply<gl::texture_parameter_e::wrapping_r          >(state.wrapping_r          );
            apply<gl::texture_parameter_e::wrapping_s          >(state.wrapping_s          );
            apply<gl::texture_parameter_e::wrapping_t          >(state.wrapping_t          );
            apply<gl::texture_parameter_e::swizzle_r           >(state.swizzle_r           );
            apply<gl::texture_parameter_e::swizzle_g           >(state.swizzle_g           );
            apply<gl::texture_parameter_e::swizzle_b           >(state.swizzle_b           );
            apply<gl::texture_parameter_e::swizzle_a           >(state.swizzle_a           );
            apply<gl::texture_parameter_e::maximum_anisotropy  >(state.maximum_anisotropy  );
            apply<gl::texture_parameter_e::minimum_lod         >(state.minimum_lod         );
            apply<gl::texture_parameter_e::maximum_lod         >(state.maximum_lod         );
            apply<gl::texture_parameter_e::lod_bias            >(state.lod_bias            );
        }

        auto format          () const -> format_e
        {
            return format_;
        }
        auto dimensions      () const -> const gl::vector_2u&
        {
            return dimensions_;
        }
        auto mipmap_levels   () const -> gl::uint32_t
        {
            return mipmap_levels_;
        }

    private:
        format_e      format_;
        gl::vector_2u dimensions_;
        gl::uint32_t  mipmap_levels_;
    };
    class cubemap_array : public gl::texture
    {
    public:
        using format_e = gl::texture_format_e;
        using face_e   = gl::cubemap_face_e;

        explicit
        cubemap_array(gl::count_t element_count, format_e format, const gl::vector_1u& dimensions, gl::bool_t allocate_mipmaps = gl::true_)
            : gl::texture{ gl::texture_target_e::cubemap_array }
            , element_count_{ element_count }, format_{ format }, dimensions_{ dimensions.x }, mipmap_levels_{ 1u }
        {
            if (allocate_mipmaps) mipmap_levels_ = gl::mipmap_levels(dimensions_);

            gl::texture_storage_3d(handle(), format_, gl::vector_3u{ dimensions_, element_count_ }, mipmap_levels_);
        }

        void upload          (gl::index_t index, face_e face,                                                  gl::texture_data_descriptor texture_data_descriptor,                 std::span<const gl::byte_t>      memory)
        {
            upload(index, face, gl::uint32_t{ 0u }, dimensions_, texture_data_descriptor, memory);
        }
        void upload          (gl::index_t index, face_e face, gl::uint32_t image_level, gl::area_t image_area, gl::texture_data_descriptor texture_data_descriptor,                 std::span<const gl::byte_t>      memory)
        {
            const auto face_origin  = index * 6u + gl::to_underlying(face - face_e::positive_x);
            const auto image_volume = gl::volume_t{ gl::vector_3u{ image_area.origin, face_origin }, gl::vector_3u{ image_area.extent, 1u } };
            gl::texture_sub_image_3d(handle(), image_level, image_volume, texture_data_descriptor, memory);
        }
        void upload          (gl::index_t index,                                                               gl::texture_data_descriptor texture_data_descriptor, std::span<const std::span<const gl::byte_t>, 6u> memory)
        {
            for (const auto [face_index, face_memory] : std::views::enumerate(memory))
            {
                upload(index, face_e::positive_x + face_index, texture_data_descriptor, face_memory);
            }
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
        void apply           (const gl::state::texture& state)
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

        auto count           () const -> gl::count_t
        {
            return element_count_;
        }
        auto format          () const -> format_e
        {
            return format_;
        }
        auto dimensions      () const -> const vector_2u&
        {
            return dimensions_;
        }
        auto mipmap_levels   () const -> gl::uint32_t
        {
            return mipmap_levels_;
        }

    private:
        gl::count_t  element_count_;
        format_e     format_;
        vector_2u    dimensions_;
        gl::uint32_t mipmap_levels_;
    };
}
