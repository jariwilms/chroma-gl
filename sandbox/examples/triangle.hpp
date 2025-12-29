#pragma once

import std;
import chroma_gl;
import rgfw;

static inline void triangle()
{
    //Window creation
    auto const window_dimensions      = rgfw::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window   { "triangle example", window_dimensions };

    //Vertex data
    struct     vertices
    {
        gl::vector_3f position;
        gl::vector_3f color;
    };
    auto const position_data          = gl::vertex::triangle::positions | std::views::transform([](auto _) { return _ / 2.0f; }) | std::ranges::to<std::vector>();
    auto const color_data             = std::array<gl::vector_3f, 3u>
    {
         gl::vector_3f{ 1.0f, 0.0f, 0.0f }, //red
         gl::vector_3f{ 0.0f, 1.0f, 0.0f }, //green
         gl::vector_3f{ 0.0f, 0.0f, 1.0f }, //blue
    };
    auto const vertex_data            = gl::make_interleaved<vertices>(position_data, color_data);
    auto const index_data             = gl::vertex::triangle::indices;

    //Buffers and layouts
    auto       vertex_array           = gl::vertex_array{};
    auto       vertex_buffer          = gl::vertex_buffer<vertices>{ vertex_data };
    auto       index_buffer           = gl::index_buffer           { index_data  };
    using      position_attribute     = gl::vertex_attribute<gl::vector_3f>;
    using      color_attribute        = gl::vertex_attribute<gl::vector_3f>;
    using      triangle_layout        = gl::interleaved_layout<position_attribute, color_attribute>;
    vertex_array.attach<triangle_layout>(vertex_buffer);
    vertex_array.attach                 (index_buffer );
    
    //Shader setup
    auto pipeline                     = gl::create_pipeline_from_files(
        { 
            { gl::shader::type_e::vertex  , "examples/assets/shaders/compiled/triangle.vert.spv" }, 
            { gl::shader::type_e::fragment, "examples/assets/shaders/compiled/triangle.frag.spv" }, 
        });



    //Render loop
    while (window)
    {
        window.process_events();

        gl::viewport   (window.dimensions()    );
        gl::clear_color(gl::color::white * 0.1f);
        gl::clear      (gl::buffer_mask_e::all );
        
        pipeline    .bind();
        vertex_array.bind();
        gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::uint32, vertex_array.index_count(), gl::index_t{ 0u });

        window.swap_buffers();
    }
}
