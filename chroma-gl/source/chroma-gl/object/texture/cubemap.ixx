export module opengl.object.cubemap;

import std;
import opengl;
import opengl.object;
import opengl.object.buffer;
import opengl.object.texture;

export namespace gl
{
    class cubemap : public gl::object
    {
    public:
        using format_e = gl::texture_format_e;
        using face_e   = gl::cubemap_face_e;

        explicit
        cubemap(format_e format, const gl::vector_1u& dimensions, gl::bool_t allocate_mipmaps = gl::true_)
            : gl::object{ gl::create_texture(gl::texture_target_e::cubemap) }
            , format_{ format }, dimensions_{ dimensions.x }, mipmap_levels_{ 1u }
        {
            if (allocate_mipmaps) mipmap_levels_ = gl::mipmap_levels(dimensions_);

            gl::texture_storage_2d(handle(), format_, dimensions_, mipmap_levels_);
        }
        
        void transfer        (face_e face,                                                  gl::texture_data_descriptor texture_data_descriptor,                 std::span<const gl::byte_t>      memory)
        {
            transfer(face, gl::uint32_t{ 0u }, dimensions_, texture_data_descriptor, memory);
        }
        void transfer        (face_e face, gl::uint32_t image_level, gl::area_t image_area, gl::texture_data_descriptor texture_data_descriptor,                 std::span<const gl::byte_t>      memory)
        {
            const auto image_volume = gl::volume_t{ gl::vector_3u{ image_area.extent, 1u }, gl::vector_3u{ image_area.origin, gl::to_underlying(face - face_e::positive_x) } };
            gl::texture_sub_image_3d(handle(), image_level, image_volume, texture_data_descriptor, memory);
        }
        void transfer        (                                                              gl::texture_data_descriptor texture_data_descriptor, std::span<const std::span<const gl::byte_t>, 6u> memory)
        {
            for (const auto [index, face_memory] : std::views::enumerate(memory))
            {
                transfer(face_e::positive_x + index, texture_data_descriptor, face_memory);
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
        auto dimensions      () const -> const gl::vector_2u&
        {
            return dimensions_;
        }
        auto mipmap_levels   () const -> gl::uint8_t
        {
            return mipmap_levels_;
        }

    private:
        format_e      format_;
        gl::vector_2u dimensions_;
        gl::uint8_t   mipmap_levels_;
    };
}
