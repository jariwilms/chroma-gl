export module opengl.object.lock;

import std;
import opengl;
import opengl.object.fence;

export namespace gl
{
    using lock_t = std::tuple<gl::fence, gl::range>;
}