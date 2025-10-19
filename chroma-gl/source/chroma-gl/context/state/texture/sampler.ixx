export module opengl.context.state.sampler;

import std;
import opengl;

export namespace gl::state
{
    struct sampler
    {
        gl::vector4f                       border_color         = { 0.0f, 0.0f, 0.0f, 0.0f }                               ;
        gl::texture_compare_mode_e         compare_mode         = gl::texture_compare_mode_e        ::none                 ;
        gl::texture_compare_function_e     compare_function     = gl::texture_compare_function_e    ::less_equal           ;
        gl::texture_minification_filter_e  minification_filter  = gl::texture_minification_filter_e ::nearest_mipmap_linear;
        gl::texture_magnification_filter_e magnification_filter = gl::texture_magnification_filter_e::linear               ;
        gl::texture_wrapping_e             wrapping_s           = gl::texture_wrapping_e            ::repeat               ;
        gl::texture_wrapping_e             wrapping_t           = gl::texture_wrapping_e            ::repeat               ;
        gl::texture_wrapping_e             wrapping_r           = gl::texture_wrapping_e            ::repeat               ;
        gl::float32_t                      maximum_anisotropy   =     1.0f                                                 ;
        gl::float32_t                      minimum_lod          = -1000.0f                                                 ;
        gl::float32_t                      maximum_lod          =  1000.0f                                                 ;
        gl::float32_t                      lod_bias             =     0.0f                                                 ;
    };
}
