export module opengl.constants;

import opengl.types;
import <glad/gl.h>;

export namespace gl
{
    constexpr auto none                 = gl::none_t  {    };
    constexpr auto null_object          = gl::handle_t{ 0u };
    constexpr auto default_frame_buffer = gl::handle_t{ 0u };
    constexpr auto invalid_index        = gl::index_t { GL_INVALID_INDEX };
}
