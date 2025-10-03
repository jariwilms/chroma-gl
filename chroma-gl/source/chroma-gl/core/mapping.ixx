export module opengl.mapping;

import std;
import opengl.flags;
import opengl.types;
import opengl.utility;

export namespace gl
{
    template<typename T>
    constexpr auto map_type() -> gl::vertex_array_attribute_type_e
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

}
