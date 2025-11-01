export module opengl.constants;

import opengl.types;

export namespace gl
{
    constexpr auto none                 = gl::enum_t  { 0u };
    constexpr auto null_object          = gl::handle_t{ 0u };
    constexpr auto default_frame_buffer = gl::handle_t{ 0u };
}
