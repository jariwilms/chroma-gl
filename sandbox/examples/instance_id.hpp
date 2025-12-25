import std;
import chroma_gl;
import rgfw;

#include "examples/file.hpp"

static inline void instance_id()
{
    //Window creation
    auto const window_dimensions      = rgfw::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window   { "my_window", window_dimensions };
    auto const input                  = window.input_handler();
    
    //Vertex data
    auto const vertex_data            = std::vector<gl::float32_t>
    {
         // positions    // colors
         0.0f,   0.15f,  1.0f, 0.0f, 0.0f,  // top
        -0.15f, -0.15f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.15f, -0.15f,  0.0f, 0.0f, 1.0f   // bottom right
    };

    //Buffers and layouts
    auto       vertex_buffer          = gl::vertex_buffer<gl::float32_t>{ vertex_data };
    auto       vertex_array           = gl::vertex_array{};
    using      position_attribute     = gl::vertex_attribute<gl::float32_t, 2u>;
    using      color_attribute        = gl::vertex_attribute<gl::float32_t, 3u>;
    using      vertex_layout          = gl::vertex_layout<position_attribute, color_attribute>;
    vertex_array.attach<vertex_layout>(vertex_buffer);
    
    //Shader setup
    auto const vertex_shader_binary   = read_file("examples/assets/shaders/compiled/instance_id.vert.spv"); //Make sure to compile shaders with --target-env=opengl
    auto const fragment_shader_binary = read_file("examples/assets/shaders/compiled/instance_id.frag.spv"); //
    auto       vertex_shader          = std::make_shared<gl::shader>(gl::shader::type_e::vertex  , "main", vertex_shader_binary  );
    auto       fragment_shader        = std::make_shared<gl::shader>(gl::shader::type_e::fragment, "main", fragment_shader_binary);
    auto       shaders                = std::initializer_list{ vertex_shader, fragment_shader };
    auto       pipeline               = gl::pipeline{ shaders };



    //Render loop
    while (window)
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
}
