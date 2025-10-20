export module opengl.context.state.texture;

import std;
import opengl;

export namespace gl::state
{
    struct texture
    {
        gl::uint32_t                                              base_level           =     0u                                                   ;
        gl::uint32_t                                              maximum_level        =  1000u                                                   ;
        std::variant<gl::vector_4i, gl::vector_4u, gl::vector_4f> border_color         = gl::vector_4f{ 0.0f, 0.0f, 0.0f, 0.0f }                  ;
        gl::texture_compare_function_e                            compare_function     = gl::texture_compare_function_e    ::less_equal           ;
        gl::texture_compare_mode_e                                compare_mode         = gl::texture_compare_mode_e        ::none                 ;
        gl::texture_minification_filter_e                         minification_filter  = gl::texture_minification_filter_e ::nearest_mipmap_linear;
        gl::texture_magnification_filter_e                        magnification_filter = gl::texture_magnification_filter_e::linear               ;
        gl::texture_wrapping_e                                    wrapping_r           = gl::texture_wrapping_e            ::repeat               ;
        gl::texture_wrapping_e                                    wrapping_s           = gl::texture_wrapping_e            ::repeat               ;
        gl::texture_wrapping_e                                    wrapping_t           = gl::texture_wrapping_e            ::repeat               ;
        gl::texture_swizzle_e                                     swizzle_r            = gl::texture_swizzle_e             ::red                  ;
        gl::texture_swizzle_e                                     swizzle_g            = gl::texture_swizzle_e             ::green                ;
        gl::texture_swizzle_e                                     swizzle_b            = gl::texture_swizzle_e             ::blue                 ;
        gl::texture_swizzle_e                                     swizzle_a            = gl::texture_swizzle_e             ::alpha                ;
        gl::float32_t                                             maximum_anisotropy   =     1.0f                                                 ;
        gl::float32_t                                             minimum_lod          = -1000.0f                                                 ;
        gl::float32_t                                             maximum_lod          =  1000.0f                                                 ;
        gl::float32_t                                             lod_bias             =     0.0f                                                 ;
    };
}
