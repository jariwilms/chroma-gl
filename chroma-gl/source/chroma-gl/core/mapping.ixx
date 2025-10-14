export module opengl.mapping;

import std;
import opengl.flags;
import opengl.types;
import opengl.utility;

export namespace gl
{
    template<typename T>
    auto map_attribute_type() -> gl::vertex_array_attribute_type_e
    {
        if constexpr (std::is_same_v<T, gl::int8_t   >) return gl::vertex_array_attribute_type_e::int8   ;          
        if constexpr (std::is_same_v<T, gl::uint8_t  >) return gl::vertex_array_attribute_type_e::uint8  ;  
        if constexpr (std::is_same_v<T, gl::int16_t  >) return gl::vertex_array_attribute_type_e::int16  ;         
        if constexpr (std::is_same_v<T, gl::uint16_t >) return gl::vertex_array_attribute_type_e::uint16 ;  
        if constexpr (std::is_same_v<T, gl::int32_t  >) return gl::vertex_array_attribute_type_e::int32  ;        
        if constexpr (std::is_same_v<T, gl::uint32_t >) return gl::vertex_array_attribute_type_e::uint32 ;
        if constexpr (std::is_same_v<T, gl::float32_t>) return gl::vertex_array_attribute_type_e::float32;
        if constexpr (std::is_same_v<T, gl::float64_t>) return gl::vertex_array_attribute_type_e::float64;        
    }

    auto map_draw_type_size(gl::draw_type_e draw_type) -> gl::size_t
    {
        switch (draw_type)
        {
            using enum gl::draw_type_e;

            case uint8 : return sizeof(gl::uint8_t );
            case uint16: return sizeof(gl::uint16_t);
            case uint32: return sizeof(gl::uint32_t);

            default    : throw std::invalid_argument{ "invalid draw type" };
        }
    }

    auto map_texture_base_format_components(gl::texture_base_format_e texture_base_format) -> gl::uint32_t
    {
        switch (texture_base_format)
        {
            using enum gl::texture_base_format_e;

            case r   : return 1u;
            case rg  : return 2u;
            case rgb : return 3u;
            case rgba: return 4u;
            case d   : return 1u;
            case s   : return 1u;

            default  : throw std::invalid_argument{ "invalid texture base format" };
        }
    }
    auto map_pixel_data_format_components  (gl::pixel_data_format_e pixel_data_format) -> gl::uint32_t
    {
        switch (pixel_data_format)
        {
            using enum gl::pixel_data_format_e;

            case r   : return 1u;
            case g   : return 1u;
            case b   : return 1u;
            case rgb : return 3u;
            case bgr : return 3u;
            case rgba: return 4u;
            case bgra: return 4u;
            case d   : return 1u;
            case s   : return 1u;
            case ds  : return 2u;
            
            default  : throw std::invalid_argument{ "invalid pixel data format" };
        }
    }
    auto map_pixel_data_bytes_per_component(gl::pixel_data_type_e pixel_data_type) -> gl::uint32_t
    {
        switch (pixel_data_type)
        {
            using enum gl::pixel_data_type_e;

            case int8                     : return 1u;
            case int16                    : return 2u;
            case int32                    : return 4u;

            case uint8                    : return 1u;
            case uint8_3_3_2              : return 1u;
            case uint8_2_3_3_r            : return 1u;
            case uint16                   : return 2u;
            case uint16_4_4_4_4           : return 2u;
            case uint16_4_4_4_4_r         : return 2u;
            case uint16_5_5_5_1           : return 2u;
            case uint16_1_5_5_5_r         : return 2u;
            case uint16_5_6_5             : return 2u;
            case uint16_5_6_5_r           : return 2u;
            case uint32                   : return 4u;
            case uint32_8_8_8_8           : return 4u;
            case uint32_8_8_8_8_r         : return 4u;
            case uint32_10_10_10_2        : return 4u;
            case uint32_2_10_10_10_r      : return 4u;
            case uint32_24_8              : return 4u;
            case uint32_float32_10_11_11_r: return 4u;
            case uint32_5_9_9_9_r         : return 4u;

            case float16                  : return 2u;
            case float32                  : return 4u;
            case float32_uint32_24_8_r    : return 4u;

            default                       : throw std::invalid_argument{ "invalid pixel data type" };
        }
    }

    auto map_texture_attachment            (gl::texture_format_e format) -> gl::frame_buffer_attachment_e
    {
        switch (format)
        {
            using enum gl::texture_format_e;

            case d_uint16_n       :
            case d_uint24_n       :
            case d_float32        : return gl::frame_buffer_attachment_e::depth        ;
            case s_uint8          : return gl::frame_buffer_attachment_e::stencil      ;
            case ds_uint24_n_uint8:
            case ds_float32_uint8 : return gl::frame_buffer_attachment_e::depth_stencil;

            default               : return gl::frame_buffer_attachment_e::color_0      ;
        }
    };
    auto map_render_buffer_attachment      (gl::render_buffer_format_e format) -> gl::frame_buffer_attachment_e
    {
        switch (format)
        {
            using enum gl::render_buffer_format_e;

            case d_uint16_n      :
            case d_uint24_n      :
            case d_float32       : return gl::frame_buffer_attachment_e::depth        ;
            case s_uint8         : return gl::frame_buffer_attachment_e::stencil      ;
            case ds_uint32_24_8  :
            case ds_float32_uint8: return gl::frame_buffer_attachment_e::depth_stencil;

            default              : return gl::frame_buffer_attachment_e::color_0      ;
        }
    };
    auto map_program_stage                 (gl::shader_type_e type) -> gl::program_stage_e
    {
        switch (type)
        {
            using enum gl::shader_type_e;

            case vertex                 : return gl::program_stage_e::vertex;
            case tessellation_control   : return gl::program_stage_e::tessellation_control;
            case tessellation_evaluation: return gl::program_stage_e::tessellation_evaluation;
            case geometry               : return gl::program_stage_e::geometry;
            case fragment               : return gl::program_stage_e::fragment;
            case compute                : return gl::program_stage_e::compute;

            default                     : throw std::invalid_argument{ "nvalid stage" };
        }
    }

    auto map_texture_format_base           (gl::texture_format_e format) -> gl::texture_base_format_e
    {
        switch (format)
        {
            using enum gl::texture_format_e;

            case r_uint8_n   : case r_uint16_n   : case r_int8_n   : case r_int16_n   : case r_float16  : case r_float32   :                    return gl::texture_base_format_e::r   ;
            case rg_uint8_n  : case rg_uint16_n  : case rg_int8_n  : case rg_int16_n  : case rg_float16 : case rg_float32  :                    return gl::texture_base_format_e::rg  ;
            case rgb_uint8_n : case rgb_uint16_n : case rgb_int8_n : case rgb_int16_n : case srgb_uint8 : case rgb_float16 : case rgb_float32 : return gl::texture_base_format_e::rgb ;
            case rgba_uint8_n: case rgba_uint16_n: case rgba_int8_n: case rgba_int16_n: case srgba_uint8: case rgba_float16: case rgba_float32: return gl::texture_base_format_e::rgba;
            case d_uint16_n  : case d_uint24_n   : case d_float32  :                                                                            return gl::texture_base_format_e::d   ;
            case s_uint8     :                                                                                                                  return gl::texture_base_format_e::s   ;

            default          : throw std::invalid_argument{ "invalid format" };
        }
    }
    auto map_texture_format_type           (gl::texture_format_e format) -> gl::pixel_data_type_e
    {
        switch (format)
        {
            using enum gl::texture_format_e;

            case r_int8_n  : case rg_int8_n  : case rgb_int8_n  : case rgba_int8_n  : return gl::pixel_data_type_e::int8   ;
            case r_int16_n : case rg_int16_n : case rgb_int16_n : case rgba_int16_n : return gl::pixel_data_type_e::int16  ;
            case r_uint8_n : case rg_uint8_n : case rgb_uint8_n : case rgba_uint8_n : return gl::pixel_data_type_e::uint8  ;
            case r_uint16_n: case rg_uint16_n: case rgb_uint16_n: case rgba_uint16_n: return gl::pixel_data_type_e::uint16 ;
                                               case srgb_uint8  : case srgba_uint8  : return gl::pixel_data_type_e::uint8  ;
            case r_float16 : case rg_float16 : case rgb_float16 : case rgba_float16 : return gl::pixel_data_type_e::float16;
            case r_float32 : case rg_float32 : case rgb_float32 : case rgba_float32 : return gl::pixel_data_type_e::float32;
            
            default        : throw std::invalid_argument{ "invalid format" };
        }
    }
}
