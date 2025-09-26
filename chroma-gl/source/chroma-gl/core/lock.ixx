export module opengl.lock;

import std;
import opengl.domain;
import opengl.types;

export namespace gl
{
    using sync_lock_t = std::tuple<gl::sync_t, gl::range>;
}
