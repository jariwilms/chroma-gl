#pragma once

import std;
import chroma_gl;
import vendor.rgfw;

#include "load_file.hpp"

static inline void instanced()
{
    //Vertex data
    auto const vertices = std::vector<gl::float32_t>
    {
        -0.05f, -0.05f, 0.0f, 
         0.05f, -0.05f, 0.0f, 
         0.00f,  0.05f, 0.0f, 
    };
    auto const grid_size = 10;
    auto const spacing   = 0.2f;
    auto       offsets   = std::vector<gl::vector_3f>{};
    offsets.reserve(grid_size * grid_size);

    for (auto row = 0u; row < grid_size; ++row)
    {
        for (auto col = 0u; col < grid_size; ++col)
        {
            offsets.emplace_back(
                col * spacing - (grid_size - 1) * spacing / 2.0f , 
                (static_cast<gl::float32_t>(row) / 5.0f) - 0.9f  , 
                row * spacing - (grid_size - 1) * spacing / 2.0f);
        }
    }



    //Window creation
    auto const window_dimensions      = gl::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window{ "my_window", window_dimensions };
    auto const input                  = window.input_handler();

    //Triangle buffers
    auto       vertex_buffer          = gl::vertex_buffer<gl::float32_t>{ vertices };
    auto       offset_buffer          = gl::vertex_buffer<gl::vector_3f>{ offsets };
    auto       vertex_array           = gl::vertex_array{};
    using      vertex_attribute       = gl::vertex_attribute<gl::float32_t, 3u>;
    using      offset_attribute       = gl::vertex_attribute<gl::float32_t, 3u, 1u>;
    using      vertex_layout          = gl::vertex_layout<vertex_attribute>;
    using      offset_layout          = gl::vertex_layout<offset_attribute>;
    vertex_array.attach<vertex_layout>(vertex_buffer);
    vertex_array.attach<offset_layout>(offset_buffer);
    
    //Shader setup
    auto const vertex_shader_binary   = load_file("examples/assets/shaders/compiled/instanced.vert.spv");
    auto const fragment_shader_binary = load_file("examples/assets/shaders/compiled/instanced.frag.spv");
    auto       vertex_shader          = std::make_shared<gl::shader>(gl::shader::type_e::vertex  , "main", vertex_shader_binary  );
    auto       fragment_shader        = std::make_shared<gl::shader>(gl::shader::type_e::fragment, "main", fragment_shader_binary);
    auto       shader_list            = std::initializer_list{ vertex_shader, fragment_shader };
    auto       pipeline               = gl::pipeline{ shader_list };



    //Render loop
    while (!window.should_close())
    {
        window.process_events();

        gl::clear_color(gl::vector_4f{ 0.1f } );
        gl::clear      (gl::buffer_mask_e::all);
        gl::viewport   (window.dimensions()   );

        pipeline    .bind();
        vertex_array.bind();
        gl::draw_arrays_instanced(gl::draw_mode_e::triangles, 3, 100);

        window.swap_buffers();
    }

    window.close();
}
