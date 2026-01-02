export module opengl:mapping;

import std;
import :flags;
import :types;
import :utility;

export namespace gl
{
    template<typename attribute_t>
    auto map_attribute_type                     () -> gl::vertex_array_attribute_type_e
    {
             if constexpr (std::is_same_v<attribute_t, gl::int8_t   >) return gl::vertex_array_attribute_type_e::int8   ;
        else if constexpr (std::is_same_v<attribute_t, gl::int16_t  >) return gl::vertex_array_attribute_type_e::int16  ;
        else if constexpr (std::is_same_v<attribute_t, gl::int32_t  >) return gl::vertex_array_attribute_type_e::int32  ;
        else if constexpr (std::is_same_v<attribute_t, gl::uint8_t  >) return gl::vertex_array_attribute_type_e::uint8  ;
        else if constexpr (std::is_same_v<attribute_t, gl::uint16_t >) return gl::vertex_array_attribute_type_e::uint16 ;
        else if constexpr (std::is_same_v<attribute_t, gl::uint32_t >) return gl::vertex_array_attribute_type_e::uint32 ;
        else if constexpr (std::is_same_v<attribute_t, gl::float32_t>) return gl::vertex_array_attribute_type_e::float32;
        else if constexpr (std::is_same_v<attribute_t, gl::float64_t>) return gl::vertex_array_attribute_type_e::float64;
    }
    auto map_buffer_base_format_component_count (gl::buffer_base_format_e   buffer_base_format  ) -> gl::count_t
    {
        switch (buffer_base_format)
        {
            case gl::buffer_base_format_e::r            : return 1u;
            case gl::buffer_base_format_e::r_int        : return 1u;
            case gl::buffer_base_format_e::g            : return 1u;
            case gl::buffer_base_format_e::g_int        : return 1u;
            case gl::buffer_base_format_e::b            : return 1u;
            case gl::buffer_base_format_e::b_int        : return 1u;
            case gl::buffer_base_format_e::rg           : return 2u;
            case gl::buffer_base_format_e::rg_int       : return 2u;
            case gl::buffer_base_format_e::rgb          : return 3u;
            case gl::buffer_base_format_e::rgb_int      : return 3u;
            case gl::buffer_base_format_e::bgr          : return 3u;
            case gl::buffer_base_format_e::bgr_int      : return 3u;
            case gl::buffer_base_format_e::rgba         : return 4u;
            case gl::buffer_base_format_e::rgba_int     : return 4u;
            case gl::buffer_base_format_e::bgra         : return 4u;
            case gl::buffer_base_format_e::bgra_int     : return 4u;
            case gl::buffer_base_format_e::depth        : return 1u;
            case gl::buffer_base_format_e::stencil      : return 1u;
            case gl::buffer_base_format_e::depth_stencil: return 2u;

            default: throw std::invalid_argument{ "invalid buffer base format"};
        }
    }
    auto map_data_type_size                     (gl::data_type_e            data_type           ) -> gl::size_t
    {
        switch (data_type)
        {
            case gl::data_type_e::int8   : return 1u;
            case gl::data_type_e::int16  : return 2u;
            case gl::data_type_e::int32  : return 3u;
            case gl::data_type_e::uint8  : return 1u;
            case gl::data_type_e::uint16 : return 2u;
            case gl::data_type_e::uint32 : return 3u;
            case gl::data_type_e::float32: return 4u;
            case gl::data_type_e::float64: return 8u;
            
            default: throw std::invalid_argument{ "invalid data type" };
        }
    }
    auto map_draw_type_size                     (gl::draw_type_e            draw_type           ) -> gl::size_t
    {
        switch (draw_type)
        {
            case gl::draw_type_e::uint8 : return sizeof(gl::uint8_t );
            case gl::draw_type_e::uint16: return sizeof(gl::uint16_t);
            case gl::draw_type_e::uint32: return sizeof(gl::uint32_t);

            default: throw std::invalid_argument{ "invalid draw type" };
        }
    }
    auto map_frame_buffer_attachment            (gl::render_buffer_format_e render_buffer_format) -> gl::frame_buffer_attachment_e
    {
        switch (render_buffer_format)
        {
            case gl::render_buffer_format_e::depth_uint16_n             :
            case gl::render_buffer_format_e::depth_uint24_n             :
            case gl::render_buffer_format_e::depth_float32              : return gl::frame_buffer_attachment_e::depth        ;
            case gl::render_buffer_format_e::stencil_uint8              : return gl::frame_buffer_attachment_e::stencil      ;
            case gl::render_buffer_format_e::depth_stencil_uint32_24_8  :
            case gl::render_buffer_format_e::depth_stencil_float32_uint8: return gl::frame_buffer_attachment_e::depth_stencil;

            default: return gl::frame_buffer_attachment_e::color_0;
        }
    }
    auto map_frame_buffer_attachment            (gl::texture_format_e       texture_format      ) -> gl::frame_buffer_attachment_e
    {
        switch (texture_format)
        {
            case gl::texture_format_e::depth_uint16_n              :
            case gl::texture_format_e::depth_uint24_n              :
            case gl::texture_format_e::depth_float32               : return gl::frame_buffer_attachment_e::depth        ;
            case gl::texture_format_e::stencil_uint8               : return gl::frame_buffer_attachment_e::stencil      ;
            case gl::texture_format_e::depth_stencil_uint24_n_uint8:
            case gl::texture_format_e::depth_stencil_float32_uint8 : return gl::frame_buffer_attachment_e::depth_stencil;

            default: return gl::frame_buffer_attachment_e::color_0      ;
        }
    }
    auto map_pixel_data_component_size          (gl::pixel_data_type_e      pixel_data_type     ) -> gl::uint32_t
    {
        switch (pixel_data_type)
        {
            case gl::pixel_data_type_e::int8                     : return 1u;
            case gl::pixel_data_type_e::int16                    : return 2u;
            case gl::pixel_data_type_e::int32                    : return 4u;

            case gl::pixel_data_type_e::uint8                    : return 1u;
            case gl::pixel_data_type_e::uint8_3_3_2              : return 1u;
            case gl::pixel_data_type_e::uint8_2_3_3_r            : return 1u;
            case gl::pixel_data_type_e::uint16                   : return 2u;
            case gl::pixel_data_type_e::uint16_4_4_4_4           : return 2u;
            case gl::pixel_data_type_e::uint16_4_4_4_4_r         : return 2u;
            case gl::pixel_data_type_e::uint16_5_5_5_1           : return 2u;
            case gl::pixel_data_type_e::uint16_1_5_5_5_r         : return 2u;
            case gl::pixel_data_type_e::uint16_5_6_5             : return 2u;
            case gl::pixel_data_type_e::uint16_5_6_5_r           : return 2u;
            case gl::pixel_data_type_e::uint32                   : return 4u;
            case gl::pixel_data_type_e::uint32_8_8_8_8           : return 4u;
            case gl::pixel_data_type_e::uint32_8_8_8_8_r         : return 4u;
            case gl::pixel_data_type_e::uint32_10_10_10_2        : return 4u;
            case gl::pixel_data_type_e::uint32_2_10_10_10_r      : return 4u;
            case gl::pixel_data_type_e::uint32_24_8              : return 4u;
            case gl::pixel_data_type_e::uint32_float32_10_11_11_r: return 4u;
            case gl::pixel_data_type_e::uint32_5_9_9_9_r         : return 4u;

            case gl::pixel_data_type_e::float16                  : return 2u;
            case gl::pixel_data_type_e::float32                  : return 4u;
            case gl::pixel_data_type_e::float32_uint32_24_8_r    : return 8u;

            default: throw std::invalid_argument{ "invalid pixel data type" };
        }
    }
    auto map_pixel_data_format_component_count  (gl::pixel_data_format_e    pixel_data_format   ) -> gl::uint32_t
    {
        switch (pixel_data_format)
        {
            case gl::pixel_data_format_e::r            : return 1u;
            case gl::pixel_data_format_e::g            : return 1u;
            case gl::pixel_data_format_e::b            : return 1u;
            case gl::pixel_data_format_e::rgb          : return 3u;
            case gl::pixel_data_format_e::bgr          : return 3u;
            case gl::pixel_data_format_e::rgba         : return 4u;
            case gl::pixel_data_format_e::bgra         : return 4u;
            case gl::pixel_data_format_e::depth        : return 1u;
            case gl::pixel_data_format_e::stencil      : return 1u;
            case gl::pixel_data_format_e::depth_stencil: return 2u;
            
            default: throw std::invalid_argument{ "invalid pixel data format" };
        }
    }
    auto map_program_stage                      (gl::shader_type_e          shader_type         ) -> gl::program_stage_e
    {
        switch (shader_type)
        {
            case gl::shader_type_e::vertex                 : return gl::program_stage_e::vertex                 ;
            case gl::shader_type_e::tessellation_control   : return gl::program_stage_e::tessellation_control   ;
            case gl::shader_type_e::tessellation_evaluation: return gl::program_stage_e::tessellation_evaluation;
            case gl::shader_type_e::geometry               : return gl::program_stage_e::geometry               ;
            case gl::shader_type_e::fragment               : return gl::program_stage_e::fragment               ;
            case gl::shader_type_e::compute                : return gl::program_stage_e::compute                ;

            default: throw std::invalid_argument{ "invalid shader type" };
        }
    }
    auto map_render_buffer_attachment           (gl::render_buffer_format_e render_buffer_format) -> gl::frame_buffer_attachment_e
    {
        switch (render_buffer_format)
        {
            case gl::render_buffer_format_e::depth_uint16_n             :
            case gl::render_buffer_format_e::depth_uint24_n             :
            case gl::render_buffer_format_e::depth_float32              : return gl::frame_buffer_attachment_e::depth        ;
            case gl::render_buffer_format_e::stencil_uint8              : return gl::frame_buffer_attachment_e::stencil      ;
            case gl::render_buffer_format_e::depth_stencil_uint32_24_8  :
            case gl::render_buffer_format_e::depth_stencil_float32_uint8: return gl::frame_buffer_attachment_e::depth_stencil;

            default: return gl::frame_buffer_attachment_e::color_0;
        }
    };
    auto map_texture_attachment                 (gl::texture_format_e       texture_format      ) -> gl::frame_buffer_attachment_e
    {
        switch (texture_format)
        {
            case gl::texture_format_e::depth_uint16_n              :
            case gl::texture_format_e::depth_uint24_n              :
            case gl::texture_format_e::depth_float32               : return gl::frame_buffer_attachment_e::depth        ;
            case gl::texture_format_e::stencil_uint8               : return gl::frame_buffer_attachment_e::stencil      ;
            case gl::texture_format_e::depth_stencil_uint24_n_uint8:
            case gl::texture_format_e::depth_stencil_float32_uint8 : return gl::frame_buffer_attachment_e::depth_stencil;

            default: return gl::frame_buffer_attachment_e::color_0;
        }
    };
    auto map_texture_base_format_component_count(gl::texture_base_format_e  texture_base_format ) -> gl::count_t
    {
        switch (texture_base_format)
        {
            case gl::texture_base_format_e::r      : return 1u;
            case gl::texture_base_format_e::rg     : return 2u;
            case gl::texture_base_format_e::rgb    : return 3u;
            case gl::texture_base_format_e::bgr    : return 3u;
            case gl::texture_base_format_e::rgba   : return 4u;
            case gl::texture_base_format_e::bgra   : return 4u;
            case gl::texture_base_format_e::depth  : return 1u;
            case gl::texture_base_format_e::stencil: return 1u;

            default: throw std::invalid_argument{ "invalid texture base format" };
        }
    }
    auto map_texture_base_format_components     (gl::texture_base_format_e  texture_base_format ) -> gl::uint32_t
    {
        switch (texture_base_format)
        {
            case gl::texture_base_format_e::r      : return 1u;
            case gl::texture_base_format_e::rg     : return 2u;
            case gl::texture_base_format_e::rgb    : return 3u;
            case gl::texture_base_format_e::rgba   : return 4u;
            case gl::texture_base_format_e::depth  : return 1u;
            case gl::texture_base_format_e::stencil: return 1u;

            default: throw std::invalid_argument{ "invalid texture base format" };
        }
    }
    auto map_texture_format_base                (gl::texture_format_e       texture_format      ) -> gl::texture_base_format_e
    {
        switch (texture_format)
        {
            case gl::texture_format_e::r_uint8_n     : 
            case gl::texture_format_e::r_uint16_n    : 
            case gl::texture_format_e::r_int8_n      : 
            case gl::texture_format_e::r_int16_n     : 
            case gl::texture_format_e::r_float16     : 
            case gl::texture_format_e::r_float32     : return gl::texture_base_format_e::r;

            case gl::texture_format_e::rg_uint8_n    : 
            case gl::texture_format_e::rg_uint16_n   : 
            case gl::texture_format_e::rg_int8_n     : 
            case gl::texture_format_e::rg_int16_n    : 
            case gl::texture_format_e::rg_float16    : 
            case gl::texture_format_e::rg_float32    : return gl::texture_base_format_e::rg;

            case gl::texture_format_e::rgb_uint8_n   : 
            case gl::texture_format_e::rgb_uint16_n  : 
            case gl::texture_format_e::rgb_int8_n    : 
            case gl::texture_format_e::rgb_int16_n   : 
            case gl::texture_format_e::srgb_uint8    : 
            case gl::texture_format_e::rgb_float16   : 
            case gl::texture_format_e::rgb_float32   : return gl::texture_base_format_e::rgb;

            case gl::texture_format_e::rgba_uint8_n  : 
            case gl::texture_format_e::rgba_uint16_n : 
            case gl::texture_format_e::rgba_int8_n   : 
            case gl::texture_format_e::rgba_int16_n  : 
            case gl::texture_format_e::srgba_uint8   : 
            case gl::texture_format_e::rgba_float16  : 
            case gl::texture_format_e::rgba_float32  : return gl::texture_base_format_e::rgba;

            case gl::texture_format_e::depth_uint16_n: 
            case gl::texture_format_e::depth_uint24_n: 
            case gl::texture_format_e::depth_float32 : return gl::texture_base_format_e::depth;

            case gl::texture_format_e::stencil_uint8 : return gl::texture_base_format_e::stencil;

            default: throw std::invalid_argument{ "invalid format" };
        }
    }
    auto map_texture_format_type                (gl::texture_format_e       texture_format      ) -> gl::pixel_data_type_e
    {
        switch (texture_format)
        {
            case gl::texture_format_e::r_int8_n     : 
            case gl::texture_format_e::rg_int8_n    : 
            case gl::texture_format_e::rgb_int8_n   : 
            case gl::texture_format_e::rgba_int8_n  : return gl::pixel_data_type_e::int8;

            case gl::texture_format_e::r_int16_n    : 
            case gl::texture_format_e::rg_int16_n   : 
            case gl::texture_format_e::rgb_int16_n  : 
            case gl::texture_format_e::rgba_int16_n : return gl::pixel_data_type_e::int16;

            case gl::texture_format_e::r_uint8_n    : 
            case gl::texture_format_e::rg_uint8_n   : 
            case gl::texture_format_e::rgb_uint8_n  : 
            case gl::texture_format_e::rgba_uint8_n : return gl::pixel_data_type_e::uint8;

            case gl::texture_format_e::r_uint16_n   : 
            case gl::texture_format_e::rg_uint16_n  : 
            case gl::texture_format_e::rgb_uint16_n : 
            case gl::texture_format_e::rgba_uint16_n: return gl::pixel_data_type_e::uint16;

            case gl::texture_format_e::srgb_uint8   : 
            case gl::texture_format_e::srgba_uint8  : return gl::pixel_data_type_e::uint8;

            case gl::texture_format_e::r_float16    : 
            case gl::texture_format_e::rg_float16   : 
            case gl::texture_format_e::rgb_float16  : 
            case gl::texture_format_e::rgba_float16 : return gl::pixel_data_type_e::float16;

            case gl::texture_format_e::r_float32    : 
            case gl::texture_format_e::rg_float32   : 
            case gl::texture_format_e::rgb_float32  : 
            case gl::texture_format_e::rgba_float32 : return gl::pixel_data_type_e::float32;
            
            default: throw std::invalid_argument{ "invalid format" };
        }
    }
    auto map_texture_format_size                (gl::texture_format_e       texture_format      ) -> gl::size_t
    {
        switch (texture_format)
        {
            case gl::texture_format_e::r_int8_n                    : return  1u;
            case gl::texture_format_e::r_int16_n                   : return  2u;
            case gl::texture_format_e::r_uint8_n                   : return  1u;
            case gl::texture_format_e::r_uint16_n                  : return  2u;
            case gl::texture_format_e::r_float16                   : return  2u;
            case gl::texture_format_e::r_float32                   : return  4u;

            case gl::texture_format_e::rg_int8_n                   : return  2u;
            case gl::texture_format_e::rg_int16_n                  : return  4u;
            case gl::texture_format_e::rg_uint8_n                  : return  2u;
            case gl::texture_format_e::rg_uint16_n                 : return  4u;
            case gl::texture_format_e::rg_float16                  : return  4u;
            case gl::texture_format_e::rg_float32                  : return  8u;

            case gl::texture_format_e::rgb_int8_n                  : return  3u;
            case gl::texture_format_e::rgb_int16_n                 : return  6u;
            case gl::texture_format_e::rgb_uint8_n                 : return  3u;
            case gl::texture_format_e::rgb_uint16_n                : return  6u;
            case gl::texture_format_e::rgb_float16                 : return  6u;
            case gl::texture_format_e::rgb_float32                 : return 12u;

            case gl::texture_format_e::rgba_int8_n                 : return  4u;
            case gl::texture_format_e::rgba_int16_n                : return  8u;
            case gl::texture_format_e::rgba_uint8_n                : return  4u;
            case gl::texture_format_e::rgba_uint16_n               : return  8u;
            case gl::texture_format_e::rgba_float16                : return  8u;
            case gl::texture_format_e::rgba_float32                : return 16u;

            case gl::texture_format_e::srgb_uint8                  : return  3u;
            case gl::texture_format_e::srgba_uint8                 : return  4u;

            case gl::texture_format_e::depth_uint16_n              : return  2u;
            case gl::texture_format_e::depth_uint24_n              : return  3u;
            case gl::texture_format_e::depth_float32               : return  4u;
            case gl::texture_format_e::stencil_uint8               : return  1u;
            case gl::texture_format_e::depth_stencil_uint24_n_uint8: return  4u;
            case gl::texture_format_e::depth_stencil_float32_uint8 : return  5u;

            default: throw std::invalid_argument{ "invalid format" };
        }
    }
    auto map_texture_target                     (gl::uint32_t               dimensions          ) -> gl::texture_target_e
    {
        switch (dimensions)
        {
            case 1u: return gl::texture_target_e::_1d;
            case 2u: return gl::texture_target_e::_2d;
            case 3u: return gl::texture_target_e::_3d;

            default: throw std::invalid_argument{ "invalid dimensions" };
        }
    }
    auto map_texture_array_target               (gl::uint32_t               dimensions          ) -> gl::texture_target_e
    {
        switch (dimensions)
        {
            case 1u: return gl::texture_target_e::_1d_array;
            case 2u: return gl::texture_target_e::_2d_array;

            default: throw std::invalid_argument{ "invalid dimensions" };
        }
    }
    auto map_texture_array_target_multisample   (gl::uint32_t               dimensions          ) -> gl::texture_target_e
    {
        switch (dimensions)
        {
            case 2u: return gl::texture_target_e::_2d_multisample_array;

            default: throw std::invalid_argument{ "invalid dimensions" };
        }
    }
    auto map_texture_target_multisample         (gl::uint32_t               dimensions          ) -> gl::texture_target_e
    {
        switch (dimensions)
        {
            case 2u: return gl::texture_target_e::_2d_multisample;

            default: throw std::invalid_argument{ "invalid dimensions" };
        }
    }
}
