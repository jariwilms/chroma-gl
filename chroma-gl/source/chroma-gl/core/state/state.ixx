export module opengl.state;

import std;
import opengl.flags;
import opengl.types;

export namespace gl
{
    std::unordered_map<gl::query_target_e, gl::bool_t> query_target_state
    {
        { gl::query_target_e::any_samples_passed                        , gl::false_ }, 
        { gl::query_target_e::any_samples_passed_conservative           , gl::false_ }, 
        { gl::query_target_e::clipping_input_primitives                 , gl::false_ }, 
        { gl::query_target_e::clipping_output_primitives                , gl::false_ }, 
        { gl::query_target_e::compute_shader_invocations                , gl::false_ }, 
        { gl::query_target_e::fragment_shader_invocations               , gl::false_ }, 
        { gl::query_target_e::geometry_shader_invocations               , gl::false_ }, 
        { gl::query_target_e::geometry_shader_primitives_emitted        , gl::false_ }, 
        { gl::query_target_e::primitives_generated                      , gl::false_ }, 
        { gl::query_target_e::primitives_submitted                      , gl::false_ }, 
        { gl::query_target_e::samples_passed                            , gl::false_ }, 
        { gl::query_target_e::tessellation_control_shader_patches       , gl::false_ }, 
        { gl::query_target_e::tessellation_evaluation_shader_invocations, gl::false_ }, 
        { gl::query_target_e::time_elapsed                              , gl::false_ }, 
        { gl::query_target_e::timestamp                                 , gl::false_ }, 
        { gl::query_target_e::transform_feedback_overflow               , gl::false_ }, 
        { gl::query_target_e::transform_feedback_primitives_written     , gl::false_ }, 
        { gl::query_target_e::transform_feedback_stream_overflow        , gl::false_ }, 
        { gl::query_target_e::vertex_shader_invocations                 , gl::false_ }, 
        { gl::query_target_e::vertices_submitted                        , gl::false_ }, 
    };

    struct frame_buffer_state
    {
        gl::pixel_data_format_e color_read_format;
        gl::pixel_data_type_e   color_read_type;
        gl::uint32_t            default_height;
        gl::uint32_t            default_layers;
        gl::uint32_t            default_samples;
        gl::uint32_t            default_width;
        gl::bool_t              has_default_fixed_sample_locations;
        gl::bool_t              is_double_buffered;
        gl::uint32_t            sample_buffers;
        gl::uint32_t            samples;
        gl::bool_t              supports_stereo;
    };
    struct frame_buffer_attachment_state
    {
        gl::sizeu_t                                  alpha_size;
        gl::sizeu_t                                  blue_size;
        gl::color_encoding_e                         color_encoding;
        gl::frame_buffer_attachment_component_type_e component_type;
        gl::sizeu_t                                  depth_size;
        gl::sizeu_t                                  green_size;
        gl::bool_t                                   is_layered;
        gl::handle_t                                 object_name;
        gl::frame_buffer_attachment_object_type_e    object_type;
        gl::sizeu_t                                  red_size;
        gl::sizeu_t                                  stencil_size;
        gl::cubemap_face_e                           texture_cubemap_face;
        gl::uint32_t                                 texture_layer;
        gl::uint32_t                                 texture_level;
    };
    struct sampler_state
    {
        gl::vector_4f                      border_color         = { 0.0f, 0.0f, 0.0f, 0.0f }                               ;
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
    struct texture_state
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
