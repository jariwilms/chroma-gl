export module opengl.object.vertex_array:vertex_attribute;

import std;
import opengl;

export namespace gl
{
    template<typename T, gl::uint32_t Count, gl::index_t Location = 0u, gl::uint32_t Instancing_Rate = 0u> requires (meta::within_closed_interval_v<Count, 1u, 4u>)
        struct vertex_attribute
    {
        using type = T;

        static const auto type_size = gl::size_t{ sizeof(T) };
        static const auto count = gl::count_t{ Count };
        static const auto stride = gl::size_t{ Count * sizeof(T) };
        static const auto location = gl::index_t{ Location };
        static const auto instancing_rate = gl::uint32_t{ Instancing_Rate };
    };
}
