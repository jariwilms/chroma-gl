export module opengl.camera;

import std;
import opengl.types;
import opengl.projection;
import glm;

export namespace gl
{
    class camera
    {
    public:
        explicit
        camera()
            : aspect_ratio{ 1.0f }, field_of_view{ 90.0f }, projection{ gl::matrix_4f{ 1.0f } } {}
        explicit
        camera(gl::float32_t aspect_ratio, gl::float32_t field_of_view)
            : aspect_ratio{ aspect_ratio }, field_of_view{ field_of_view }, projection{ gl::create_projection<gl::projection_type_e::perspective>(aspect_ratio, glm::radians(field_of_view), 0.01f, 1000.0f) } {}
        explicit
        camera(gl::float32_t aspect_ratio, gl::float32_t field_of_view, gl::matrix_4f&& projection)
            : aspect_ratio{ aspect_ratio }, field_of_view{ field_of_view }, projection{ std::forward<gl::matrix_4f>(projection) } {}

        gl::float32_t aspect_ratio;
        gl::float32_t field_of_view;
        gl::matrix_4f projection;
    };
}
