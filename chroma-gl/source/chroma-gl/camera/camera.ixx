export module opengl.camera;

import std;
import opengl.types;
import opengl.projection;
import glm;

export namespace gl
{
    struct camera
    {
        gl::float32_t aspect_ratio  = gl::float32_t{ 1.0f };
        gl::float32_t field_of_view = glm::radians(45.0f);
        gl::matrix_4f projection    = gl::create_projection<gl::projection_type_e::perspective>(aspect_ratio, field_of_view, 0.01f, 100.0f);
    };
}
