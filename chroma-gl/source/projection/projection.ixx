export module chroma_gl:projection;

import std;
import glm;
import opengl;

export namespace gl
{
    namespace projection
    {
        auto orthographic(gl::float32_t left, gl::float32_t right, gl::float32_t bottom, gl::float32_t top, gl::float32_t near, gl::float32_t far) -> gl::matrix_4f
        {
            return gl::matrix_4f{ glm::ortho(left, right, bottom, top, near, far) };
        }
        auto perspective(gl::float32_t vertical_fov, gl::float32_t aspect_ratio, gl::float32_t near, gl::float32_t far) -> gl::matrix_4f
        {
            return gl::matrix_4f{ glm::perspective(vertical_fov, aspect_ratio, near, far) };
        }
    }
}
