export module opengl:constants;

import std;
import :types;

export namespace gl
{
    constexpr auto none                 = gl::none_t  {    };
    constexpr auto null_object          = gl::handle_t{ 0u };
    constexpr auto default_frame_buffer = gl::handle_t{ 0u };
    constexpr auto invalid_size         = std::numeric_limits<gl::size_t >::max();
    constexpr auto invalid_index        = std::numeric_limits<gl::index_t>::max();
}
