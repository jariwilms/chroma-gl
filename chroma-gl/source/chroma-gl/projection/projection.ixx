export module chroma_gl:projection;

import std;
import glm;
import opengl;

export namespace gl
{
    using projection_t = gl::matrix_4f;

    enum class projection_type_e
    {
        orthographic, 
        perspective , 
    };
    template<gl::projection_type_e Type, typename... Args>
    auto create_projection(Args...) -> gl::projection_t = delete;

    template<>
    auto create_projection<gl::projection_type_e::orthographic>(gl::float32_t left_plane, gl::float32_t right_plane, gl::float32_t bottom_plane, gl::float32_t top_plane, gl::float32_t near_plane, gl::float32_t far_plane) -> gl::projection_t
    {
        return glm::ortho(left_plane, right_plane, bottom_plane, top_plane, near_plane, far_plane);
    }
    template<>
    auto create_projection<gl::projection_type_e::perspective >(gl::float32_t vertical_fov, gl::float32_t aspect_ratio, gl::float32_t near_plane, gl::float32_t far_plane) -> gl::projection_t
    {
        return glm::perspective(vertical_fov, aspect_ratio, near_plane, far_plane);
    }
}
