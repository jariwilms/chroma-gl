export module chroma_gl:object.vertex_array.vertex_layout;

import std;
import opengl;

export namespace gl
{
    template<typename... attribute_t>
    struct vertex_layout
    {
        using tuple_t                = std::tuple<attribute_t...>;
        static auto constexpr stride = static_cast<gl::size_t>((attribute_t::size + ...));
    };

    template<typename... attribute_t>
    using interleaved_layout = gl::vertex_layout<attribute_t...>;
    template<typename    attribute_t>
    using separate_layout    = gl::vertex_layout<attribute_t    >;
}
