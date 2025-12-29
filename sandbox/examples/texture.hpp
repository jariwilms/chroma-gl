#pragma once

import std;
import chroma_gl;
import rgfw;

static inline void texture()
{
    //Window creation
    auto const window_dimensions      = rgfw::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window   { "texture example", window_dimensions };
    
    //Vertex data
    auto const vertex_data            = std::vector<gl::float32_t>
    {
        //  x      y      z      u      v
         0.5f,  0.5f,  0.0f,  1.0f,  1.0f, 
        -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 
        -0.5f, -0.5f,  0.0f,  0.0f,  0.0f, 
         0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 
    };
    auto const index_data             = std::vector<gl::uint32_t>
    {
           0u,    1u,    2u, 
           0u,    2u,    3u, 
    };
    
    //Buffers and layouts
    auto       vertex_array           = gl::vertex_array{};
    auto       vertex_buffer          = gl::vertex_buffer<gl::float32_t>{ vertex_data };
    auto       index_buffer           = gl::index_buffer                { index_data  };
    using      position_attribute     = gl::vertex_attribute<gl::vector_3f>;
    using      uv_attribute           = gl::vertex_attribute<gl::vector_2f>;
    using      texture_layout         = gl::interleaved_layout<position_attribute, uv_attribute>;
    vertex_array.attach<texture_layout>(vertex_buffer);
    vertex_array.attach                     (index_buffer );

    //Shader setup
    auto pipeline                     = gl::create_pipeline_from_files(
        {
            { gl::shader::type_e::vertex  , "examples/assets/shaders/compiled/texture.vert.spv" },
            { gl::shader::type_e::fragment, "examples/assets/shaders/compiled/texture.frag.spv" },
        });
    
    //Texture loading
    auto       image_data             = gl::io::read("examples/assets/textures/opengl_logo.png");
    auto       image                  = gl::image::decode(gl::image::format_e::rgba_uint8, image_data);
    auto       texture                = gl::texture_2d{ gl::texture_2d::format_e::rgba_uint8_n, image.dimensions() };
    auto const pixel_data_descriptor  = gl::pixel_data_descriptor{ gl::texture_base_format_e::rgba, gl::pixel_data_type_e::byte };
    auto const texture_state          = gl::texture_state
    {
        .minification_filter  = gl::texture_minification_filter_e ::linear_mipmap_linear, 
        .magnification_filter = gl::texture_magnification_filter_e::linear              , 
        .maximum_anisotropy   = 16.0f                                                   , 
    };
    texture.upload          (pixel_data_descriptor, image.data());
    texture.apply           (texture_state);
    texture.generate_mipmaps();



    gl::enable<gl::feature_e::blending>();
    gl::blend_function(gl::blending_factor_e::source_alpha, gl::blending_factor_e::one_minus_source_alpha);

    //Render loop
    while (window)
    {
        window.process_events();

        gl::viewport   (window.dimensions());
        gl::clear_color(gl::vector_4f{ 0.1f });
        gl::clear      (gl::buffer_mask_e::all);

        pipeline    .bind();
        vertex_array.bind();
        texture     .bind(gl::binding_t{ 0u });
        gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::uint32, vertex_array.index_count(), gl::index_t{ 0u });

        window.swap_buffers();
    }
}
