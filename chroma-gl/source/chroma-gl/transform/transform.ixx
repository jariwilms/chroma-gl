export module opengl.transform;

import opengl.types;

export namespace gl
{
    struct transform
    {
        gl::vector_4f     position = gl::vector_4f    { 0.0f };
        gl::quaternion_4f rotation = gl::quaternion_4f{ 1.0f, 0.0f, 0.0f, 0.0f };
        gl::vector_4f     scale    = gl::vector_4f    { 1.0f };
    };
}
