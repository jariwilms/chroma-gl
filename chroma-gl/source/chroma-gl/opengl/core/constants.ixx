export module opengl:constants;

import std;
import :types;

export namespace gl
{
    auto constexpr none                 = gl::none_t  {    };
    auto constexpr null_object          = gl::handle_t{ 0u };
    auto constexpr default_frame_buffer = gl::handle_t{ 0u };
    auto constexpr invalid_size         = std::numeric_limits<gl::size_t >::max();
    auto constexpr invalid_index        = std::numeric_limits<gl::index_t>::max();
}
