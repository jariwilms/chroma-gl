#pragma once

import std;
import chroma_gl;
import rgfw;
import glm;

static inline void cube()
{
    //Window creation
    auto const window_dimensions      = rgfw::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window   { "triangle example", window_dimensions };
    auto       input                  = window.input_handler();

    //Vertex data
    auto const vertex_data            = std::vector<gl::float32_t>
    {
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f, 
         0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, 
    };

    //Buffers and layouts
    auto       vertex_array           = gl::vertex_array{};
    auto       vertex_buffer          = gl::vertex_buffer<gl::float32_t>{ vertex_data };
    using      position_attribute     = gl::vertex_attribute<gl::vector_3f>;
    using      cube_layout            = gl::vertex_layout<position_attribute>;
    vertex_array.attach<cube_layout>(vertex_buffer);

    //Uniform data
    struct mvp
    {
        gl::matrix_4f model;
        gl::matrix_4f view;
        gl::matrix_4f projection;
    };
    auto const aspect_ratio           = static_cast<gl::float32_t>(window_dimensions.x) / window_dimensions.y;
    auto       camera_position        = gl::vector_3f{ 0.0f, 0.0f, 10.0f };
    auto       mvp_uniform            = gl::uniform_buffer<mvp>{ gl::count_t{ 1u } };
    auto       matrices               = mvp
    {
        gl::matrix_4f{ 1.0f }                                                                                     , 
        glm::lookAt(camera_position, gl::vector_3f{ 0.0f }, gl::vector_3f{ 0.0f,  1.0f,  0.0f })                  , 
        gl::create_projection<gl::projection_type_e::perspective>(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f), 
    };

    mvp_uniform.bind(gl::binding_t{ 0u });
    mvp_uniform.upload(matrices);

    //Shader setup
    auto       pipeline               = gl::create_pipeline_from_files(
        { 
            { gl::shader::type_e::vertex  , "examples/assets/shaders/compiled/cube.vert.spv" }, 
            { gl::shader::type_e::fragment, "examples/assets/shaders/compiled/cube.frag.spv" }, 
        });

    //Timing
    auto       time_now               = std::chrono::system_clock::now();
    auto       time_before            = std::chrono::system_clock::now();
    auto       delta                  = gl::float32_t{};



    gl::enable<gl::feature_e::depth_test>();

    //Render loop
    while (window)
    {
        time_now    = std::chrono::system_clock::now();
        delta       = std::chrono::duration<gl::float32_t>(time_now - time_before).count();
        time_before = time_now;



        window.process_events();
        if (input->any_key_active())
        {
            if (input->key_active(rgfw::key_e::d)) camera_position.x += 10.0f * delta;
            if (input->key_active(rgfw::key_e::a)) camera_position.x -= 10.0f * delta;
            if (input->key_active(rgfw::key_e::s)) camera_position.z += 10.0f * delta;
            if (input->key_active(rgfw::key_e::w)) camera_position.z -= 10.0f * delta;
            if (input->key_active(rgfw::key_e::e)) camera_position.y += 10.0f * delta;
            if (input->key_active(rgfw::key_e::q)) camera_position.y -= 10.0f * delta;

            matrices.view = glm::lookAt(camera_position, camera_position + gl::vector_3f{ 0.0f, 0.0f, -1.0f }, gl::vector_3f(0.0f, 1.0f, 0.0f));
            mvp_uniform.upload(matrices);
        }



        gl::viewport   (window.dimensions()    );
        gl::clear_color(gl::color::white * 0.1f);
        gl::clear      (gl::buffer_mask_e::all );
        
        pipeline    .bind();
        vertex_array.bind();
        gl::draw_arrays(gl::draw_mode_e::triangles, gl::range_t{ 36u });

        window.swap_buffers();
    }
}
