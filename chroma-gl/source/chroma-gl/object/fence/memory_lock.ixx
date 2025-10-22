export module opengl.object.memory_lock;

import std;
import opengl;
import opengl.object.fence;

export namespace gl
{
    using memory_lock_t = std::tuple<gl::fence, gl::range_t>;
}