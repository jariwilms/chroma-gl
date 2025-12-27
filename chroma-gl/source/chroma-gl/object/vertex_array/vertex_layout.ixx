export module opengl.object.vertex_array:vertex_layout;

import std;
import opengl;

export namespace gl
{
    template<typename... Attributes>
    struct vertex_layout
    {
        using tuple_t            = std::tuple<Attributes...>;
        static const auto stride = static_cast<gl::size_t>((Attributes::stride + ...));
    };

    template<typename... Attributes>
    using interleaved_layout = gl::vertex_layout<Attributes...>;
    template<typename    Attribute>
    using separate_layout    = gl::vertex_layout<Attribute    >;
}
