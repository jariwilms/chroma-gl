export module opengl:parameters;

import std;
import :flags;
import :types;

export namespace gl
{
    template<gl::sampler_parameter_e P>
    struct sampler_parameter_argument;
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::border_color        > { using type = std::variant<gl::vector_4i, gl::vector_4u, gl::vector_4f>; };
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::compare_function    > { using type = gl::texture_compare_function_e                           ; };
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::compare_mode        > { using type = gl::texture_compare_mode_e                               ; };
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::lod_bias            > { using type = gl::float32_t                                            ; };
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::magnification_filter> { using type = gl::texture_magnification_filter_e                       ; };
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::maximum_anisotropy  > { using type = gl::float32_t                                            ; };
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::maximum_lod         > { using type = gl::float32_t                                            ; };
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::minification_filter > { using type = gl::texture_minification_filter_e                        ; };
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::minimum_lod         > { using type = gl::float32_t                                            ; };
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::wrapping_r          > { using type = gl::texture_wrapping_e                                   ; };
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::wrapping_s          > { using type = gl::texture_wrapping_e                                   ; };
    template<> struct gl::sampler_parameter_argument<gl::sampler_parameter_e::wrapping_t          > { using type = gl::texture_wrapping_e                                   ; };
    template<gl::sampler_parameter_e P>
    using sampler_parameter_argument_t = gl::sampler_parameter_argument<P>::type;

    

    template<gl::texture_parameter_e P>
    struct texture_parameter_argument;
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::base_level          > { using type = gl::uint32_t                                             ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::border_color        > { using type = std::variant<gl::vector_4i, gl::vector_4u, gl::vector_4f>; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::compare_function    > { using type = gl::texture_compare_function_e                           ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::compare_mode        > { using type = gl::texture_compare_mode_e                               ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::depth_stencil_mode  > { using type = gl::depth_stencil_texture_mode_e                         ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::lod_bias            > { using type = gl::float32_t                                            ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::magnification_filter> { using type = gl::texture_magnification_filter_e                       ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::maximum_anisotropy  > { using type = gl::float32_t                                            ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::maximum_level       > { using type = gl::uint32_t                                             ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::maximum_lod         > { using type = gl::float32_t                                            ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::minification_filter > { using type = gl::texture_minification_filter_e                        ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::minimum_lod         > { using type = gl::float32_t                                            ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::swizzle_a           > { using type = gl::texture_swizzle_e                                    ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::swizzle_b           > { using type = gl::texture_swizzle_e                                    ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::swizzle_g           > { using type = gl::texture_swizzle_e                                    ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::swizzle_r           > { using type = gl::texture_swizzle_e                                    ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::swizzle_rgba        > { using type = gl::texture_swizzle_e                                    ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::wrapping_r          > { using type = gl::texture_wrapping_e                                   ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::wrapping_s          > { using type = gl::texture_wrapping_e                                   ; };
    template<> struct gl::texture_parameter_argument<gl::texture_parameter_e::wrapping_t          > { using type = gl::texture_wrapping_e                                   ; };
    template<gl::texture_parameter_e P>
    using texture_parameter_argument_t = gl::texture_parameter_argument<P>::type;



    template<gl::patch_parameter_e P>
    struct patch_parameter_argument;
    template<> struct gl::patch_parameter_argument<gl::patch_parameter_e::patch_default_inner_level> { using type = std::array<gl::float32_t, 4u>; };
    template<> struct gl::patch_parameter_argument<gl::patch_parameter_e::patch_default_outer_level> { using type = std::array<gl::float32_t, 4u>; };
    template<> struct gl::patch_parameter_argument<gl::patch_parameter_e::patch_vertices           > { using type = gl::uint32_t                 ; };
    template<gl::patch_parameter_e P>
    using patch_parameter_argument_t = gl::patch_parameter_argument<P>::type;



    template<gl::point_parameter_e P>
    struct point_parameter_argument;
    template<> struct gl::point_parameter_argument<gl::point_parameter_e::fade_threshold_size     > { using type = float32_t         ; };
    template<> struct gl::point_parameter_argument<gl::point_parameter_e::sprite_coordinate_origin> { using type = gl::point_origin_e; };
    template<gl::point_parameter_e P>
    using point_parameter_argument_t = gl::point_parameter_argument<P>::type;



    template<gl::frame_buffer_attachment_e A>
    struct frame_buffer_attachment_argument;
    template<> struct gl::frame_buffer_attachment_argument<gl::frame_buffer_attachment_e::color_0      > { using type = std::variant<gl::vector_4i, gl::vector_4u, gl::vector_4f>; };
    template<> struct gl::frame_buffer_attachment_argument<gl::frame_buffer_attachment_e::color_1      > { using type = std::variant<gl::vector_4i, gl::vector_4u, gl::vector_4f>; };
    template<> struct gl::frame_buffer_attachment_argument<gl::frame_buffer_attachment_e::color_2      > { using type = std::variant<gl::vector_4i, gl::vector_4u, gl::vector_4f>; };
    template<> struct gl::frame_buffer_attachment_argument<gl::frame_buffer_attachment_e::color_3      > { using type = std::variant<gl::vector_4i, gl::vector_4u, gl::vector_4f>; };
    template<> struct gl::frame_buffer_attachment_argument<gl::frame_buffer_attachment_e::color_4      > { using type = std::variant<gl::vector_4i, gl::vector_4u, gl::vector_4f>; };
    template<> struct gl::frame_buffer_attachment_argument<gl::frame_buffer_attachment_e::color_5      > { using type = std::variant<gl::vector_4i, gl::vector_4u, gl::vector_4f>; };
    template<> struct gl::frame_buffer_attachment_argument<gl::frame_buffer_attachment_e::color_6      > { using type = std::variant<gl::vector_4i, gl::vector_4u, gl::vector_4f>; };
    template<> struct gl::frame_buffer_attachment_argument<gl::frame_buffer_attachment_e::color_7      > { using type = std::variant<gl::vector_4i, gl::vector_4u, gl::vector_4f>; };
    template<> struct gl::frame_buffer_attachment_argument<gl::frame_buffer_attachment_e::depth        > { using type = std::variant<gl::int32_t  , gl::uint32_t , gl::float32_t>; };
    template<> struct gl::frame_buffer_attachment_argument<gl::frame_buffer_attachment_e::stencil      > { using type = std::variant<gl::int32_t  , gl::uint32_t , gl::float32_t>; };
    template<> struct gl::frame_buffer_attachment_argument<gl::frame_buffer_attachment_e::depth_stencil> { using type = std::tuple  <gl::float32_t, gl::int32_t                >; };
    template<gl::frame_buffer_attachment_e A>
    using frame_buffer_attachment_argument_t = gl::frame_buffer_attachment_argument<A>::type;
}
