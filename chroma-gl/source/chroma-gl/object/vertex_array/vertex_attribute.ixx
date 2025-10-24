export module opengl.object.vertex_array:vertex_attribute;

import std;
import opengl;

export namespace gl
{
    template<typename T, gl::count_t Components, gl::index_t Divisor = 0u, gl::bool_t Normalized = gl::false_> requires (meta::within_closed_interval_v<Components, 1u, 4u>)
    struct vertex_attribute
    {
        using component_t = T;

        static const auto components     = gl::count_t{ Components             };
        static const auto component_size = gl::size_t { sizeof(T)              };
        static const auto stride         = gl::size_t { Components * sizeof(T) };
        static const auto divisor        = gl::index_t{ Divisor                };
        static const auto is_normalized  = gl::bool_t { Normalized             };
    };
}
