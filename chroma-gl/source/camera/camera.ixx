export module chroma_gl:camera;

import std;
import glm;
import opengl;
import :projection;

export namespace gl
{
    struct camera
    {
        gl::float32_t aspect_ratio  = 1.0f;
        gl::float32_t field_of_view = glm::radians(90.0f);
        gl::matrix_4f projection    = projection::perspective(aspect_ratio, field_of_view, 0.01f, 100.0f);
    };
}
