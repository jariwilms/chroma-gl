#pragma once

import std;
import chroma_gl;
import vendor.glfw;

#include "load_file.hpp"

static inline void triangle_example()
{
    //Vertex data
    auto const triangle_vertices              = std::vector<gl::float32_t>
    {
        //  x      y      z,     r      g      b
         0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, //Top    middle (red  )
        -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f, //Bottom left   (green)
         0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f, //Bottom right  (blue )
    };
    auto const triangle_indices               = std::vector<gl::uint32_t>
    {
           0u,    1u,    2u,                      //First  triangle
    };



    //Window creation
    auto const window_dimensions              = gl::vector_2u{ 1280u, 720u };
    auto       window                         = glfw::window{ "my_window", window_dimensions };
    auto const input                          = window.input_handler();

    //Triangle buffers
    auto       color_vertex_buffer            = gl::vertex_buffer<gl::float32_t>{ triangle_vertices };
    auto       color_index_buffer             = gl::index_buffer{ triangle_indices };
    auto       color_vertex_array             = gl::vertex_array{};
    using      position_attribute             = gl::vertex_attribute<gl::float32_t, 3u>;
    using      color_attribute                = gl::vertex_attribute<gl::float32_t, 3u>;
    using      color_vertex_layout            = gl::vertex_layout<position_attribute, color_attribute>;
    color_vertex_array.attach<color_vertex_layout>(color_vertex_buffer);
    color_vertex_array.attach                     (color_index_buffer );
    
    //Shader setup
    auto const color_vertex_shader_binary     = load_file("assets/shaders/compiled/color.vert.spv");
    auto const color_fragment_shader_binary   = load_file("assets/shaders/compiled/color.frag.spv");
    auto       color_vertex_shader            = std::make_shared<gl::shader>(gl::shader::type_e::vertex  , "main", color_vertex_shader_binary  );
    auto       color_fragment_shader          = std::make_shared<gl::shader>(gl::shader::type_e::fragment, "main", color_fragment_shader_binary);
    auto       color_shaders                  = std::initializer_list{ color_vertex_shader, color_fragment_shader };
    auto       color_pipeline                 = gl::pipeline{ color_shaders };



    //Render loop
    while (!window.should_close())
    {
        window.poll_events();

        gl::clear_color(gl::vector_4f{ 0.1f });
        gl::clear      (gl::buffer_mask_e::all);
        gl::viewport   (window.dimensions());

        color_pipeline    .bind();
        color_vertex_array.bind();
        gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::uint32, color_vertex_array.index_count(), gl::index_t{ 0u });

        window.swap_buffers();
    }

    window.close();
}
