export module opengl.mapping;

import std;
import opengl.flags;
import opengl.types;
import opengl.utility;

export namespace gl
{
    template<typename T>
    constexpr auto map_attribute_type() -> gl::vertex_array_attribute_type_e
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

    auto map_buffer_base_format(gl::buffer_format_e format)
    {
        //gl::buffer_base_format_e;
        //r       
        //g       
        //b       
        //rg      
        //rgb     
        //rgba    
        //bgr     
        //bgra    
        //r_int   
        //g_int   
        //b_int   
        //rg_int  
        //rgb_int 
        //rgba_int
        //bgr_int 
        //bgra_int
        //d       
        //s       
        //ds      



        //r_int8      
        //r_int16     
        //r_int32     
        //r_uint8     
        //r_uint8_n   
        //r_uint16    
        //r_uint16_n  
        //r_uint32    
        //r_float16   
        //r_float32   
       
        //rg_int8     
        //rg_int16    
        //rg_int32    
        //rg_uint8    
        //rg_uint8_n  
        //rg_uint16   
        //rg_uint16_n 
        //rg_uint32   
        //rg_float16  
        //rg_float32  
       
        //rgb_int32   
        //rgb_uint32  
        //rgb_float32 
       
        //rgba_int8   
        //rgba_int16  
        //rgba_int16_n
        //rgba_int32  
        //rgba_uint8  
        //rgba_uint8_n
        //rgba_uint16 
        //rgba_uint32 
        //rgba_float16
        //rgba_float32

    }

    auto map_texture_attachment      (gl::texture_format_e     format) -> gl::frame_buffer_attachment_e
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
    auto map_render_buffer_attachment(gl::render_buffer_format_e format) -> gl::frame_buffer_attachment_e
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
    auto map_program_stage           (gl::shader_type_e type) -> gl::program_stage_e
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

    auto map_texture_format_base     (gl::texture_format_e format) -> gl::texture_base_format_e
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
    auto map_texture_format_type     (gl::texture_format_e format) -> gl::pixel_data_type_e
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
