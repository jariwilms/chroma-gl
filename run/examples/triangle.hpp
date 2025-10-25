#pragma once

import std;
import chroma_gl;
import vendor.glfw;

#include "load_file.hpp"

static inline void triangle()
{
    //Vertex data
    auto const vertex_data            = std::vector<gl::float32_t>
    {
        //  x      y      z,     r      g      b
         0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, //Top    middle (red  )
        -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f, //Bottom left   (green)
         0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f, //Bottom right  (blue )
    };
    auto const index_data             = std::vector<gl::uint32_t>
    {
           0u,    1u,    2u,                      //First  triangle
    };



    //Window creation
    auto const window_dimensions      = gl::vector_2u{ 1280u, 720u };
    auto       window                 = glfw::window{ "my_window", window_dimensions };
    auto const input                  = window.input_handler();

    //Triangle buffers
    auto       vertex_buffer          = gl::vertex_buffer<gl::float32_t>{ vertex_data };
    auto       index_buffer           = gl::index_buffer{ index_data };
    auto       vertex_array           = gl::vertex_array{};
    using      position_attribute     = gl::vertex_attribute<gl::float32_t, 3u>;
    using      color_attribute        = gl::vertex_attribute<gl::float32_t, 3u>;
    using      color_vertex_layout    = gl::vertex_layout<position_attribute, color_attribute>;
    vertex_array.attach<color_vertex_layout>(vertex_buffer);
    vertex_array.attach                     (index_buffer );
    
    //Shader setup
    auto const vertex_shader_binary   = load_file("examples/assets/shaders/compiled/triangle.vert.spv");
    auto const fragment_shader_binary = load_file("examples/assets/shaders/compiled/triangle.frag.spv");
    auto       vertex_shader          = std::make_shared<gl::shader>(gl::shader::type_e::vertex  , "main", vertex_shader_binary  );
    auto       fragment_shader        = std::make_shared<gl::shader>(gl::shader::type_e::fragment, "main", fragment_shader_binary);
    auto       shader_list            = std::initializer_list{ vertex_shader, fragment_shader };
    auto       pipeline               = gl::pipeline{ shader_list };



    //Render loop
    while (!window.should_close())
    {
        window.poll_events();

        gl::clear_color(gl::vector_4f{ 0.1f } );
        gl::clear      (gl::buffer_mask_e::all);
        gl::viewport   (window.dimensions()   );

        pipeline    .bind();
        vertex_array.bind();
        gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::uint32, vertex_array.index_count(), gl::index_t{ 0u });

        window.swap_buffers();
    }

    window.close();
}
