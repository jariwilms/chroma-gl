#pragma once

import std;
import chroma_gl;
import rgfw;

static inline auto create_grid(gl::uint32_t grid_size, gl::float32_t grid_spacing) -> std::vector<gl::vector_3f>
{
    auto offsets = std::vector<gl::vector_3f>{};
    offsets.reserve(grid_size * grid_size);

    for (auto row = 0u; row < grid_size; ++row)
    {
        for (auto col = 0u; col < grid_size; ++col)
        {
            offsets.emplace_back(
                col * grid_spacing - (grid_size - 1) * grid_spacing / 2.0f , 
                (static_cast<gl::float32_t>(row) / 5.0f) - 0.9f            , 
                row * grid_spacing - (grid_size - 1) * grid_spacing / 2.0f);
        }
    }

    return offsets;
}
static inline void instanced()
{
    //Window creation
    auto const window_dimensions      = rgfw::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window   { "instanced example", window_dimensions };
    
    //Vertex data
    auto const vertex_data            = std::vector<gl::float32_t>
    {
        -0.05f, -0.05f, 0.00f, 
         0.05f, -0.05f, 0.00f, 
         0.00f,  0.05f, 0.00f, 
    };
    auto const grid_size              = 10u;
    auto const spacing                = 0.2f;
    auto const offset_data            = create_grid(grid_size, spacing);

    //Buffers and layouts
    auto       vertex_array           = gl::vertex_array{};
    auto       vertex_buffer          = gl::vertex_buffer<gl::float32_t>{ vertex_data };
    auto       offset_buffer          = gl::vertex_buffer<gl::vector_3f>{ offset_data };
    using      vertex_attribute       = gl::vertex_attribute<gl::float32_t, 3u>;
    using      offset_attribute       = gl::vertex_attribute<gl::float32_t, 3u, 1u, 1u>; //Divisor must be 1
    using      vertex_layout          = gl::separate_layout<vertex_attribute>;
    using      offset_layout          = gl::separate_layout<offset_attribute>;
    vertex_array.attach<vertex_layout>(vertex_buffer);
    vertex_array.attach<offset_layout>(offset_buffer);
    
    //Shader setup
    auto pipeline                     = gl::create_pipeline_from_files(
        {
            { gl::shader::type_e::vertex  , "examples/assets/shaders/compiled/instanced.vert.spv" },
            { gl::shader::type_e::fragment, "examples/assets/shaders/compiled/instanced.frag.spv" },
        });



    //Render loop
    while (window)
    {
        window.process_events();

        gl::viewport   (window.dimensions()   );
        gl::clear_color(gl::vector_4f{ 0.1f } );
        gl::clear      (gl::buffer_mask_e::all);

        pipeline    .bind();
        vertex_array.bind();
        gl::draw_arrays_instanced(gl::draw_mode_e::triangles, 3u, 100u);

        window.swap_buffers();
    }
}
