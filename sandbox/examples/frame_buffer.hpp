import std;
import chroma_gl;
import rgfw;

#include "file.hpp"

void frame_buffer()
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
    auto const window_dimensions      = rgfw::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window   { "my_window", window_dimensions };
    auto const input                  = window.input_handler();

    //Triangle buffers
    auto       vertex_buffer          = gl::vertex_buffer<gl::float32_t>{ vertex_data };
    auto       index_buffer           = gl::index_buffer                { index_data  };
    auto       vertex_array           = gl::vertex_array{};
    using      position_attribute     = gl::vertex_attribute<gl::float32_t, 3u>;
    using      color_attribute        = gl::vertex_attribute<gl::float32_t, 3u>;
    using      triangle_data_layout   = gl::vertex_layout<position_attribute, color_attribute>;
    vertex_array.attach<triangle_data_layout>(vertex_buffer);
    vertex_array.attach                      (index_buffer );
    
    //Shader setup
    auto const vertex_shader_binary   = read_file("examples/assets/shaders/compiled/triangle.vert.spv");
    auto const fragment_shader_binary = read_file("examples/assets/shaders/compiled/triangle.frag.spv");
    auto       vertex_shader          = std::make_shared<gl::shader>(gl::shader::type_e::vertex  , "main", vertex_shader_binary  );
    auto       fragment_shader        = std::make_shared<gl::shader>(gl::shader::type_e::fragment, "main", fragment_shader_binary);
    auto       shader_list            = std::initializer_list{ vertex_shader, fragment_shader };
    auto       pipeline               = gl::pipeline{ shader_list };

    auto const my_color_specification = gl::frame_buffer_specification{ "my_color", gl::frame_buffer_surface_e::texture      , gl::texture_format_e      ::rgba_uint8_n              };
    auto const my_depth_specification = gl::frame_buffer_specification{ "my_depth", gl::frame_buffer_surface_e::render_buffer, gl::render_buffer_format_e::depth_stencil_uint32_24_8 };
    auto const my_attachment_map      = gl::frame_buffer_attachment_map_t
    {
        { gl::frame_buffer_attachment_e::color_0      , my_color_specification }, 
        { gl::frame_buffer_attachment_e::depth_stencil, my_depth_specification }, 
    };
    auto       my_frame_buffer        = gl::frame_buffer{ my_attachment_map, window_dimensions };



    while (window)
    {
        window.process_events();

        gl::viewport   (window.dimensions()   );
        gl::clear_color(gl::vector_4f{ 0.1f } );
        gl::clear      (gl::buffer_mask_e::all);
        
        pipeline       .bind();
        vertex_array   .bind();
        my_frame_buffer.bind(gl::frame_buffer::target_e::read_write);
        gl::draw_elements    (gl::draw_mode_e::triangles, gl::draw_type_e::uint32, vertex_array.index_count(), gl::index_t{ 0u });

        gl::blit_frame_buffer(my_frame_buffer.handle(), gl::default_frame_buffer, gl::buffer_mask_e::color, gl::frame_buffer_filter_e::nearest, window_dimensions, window_dimensions);

        window.swap_buffers();
    }

    auto       frame_buffer_pixels    = gl::read_pixels(window_dimensions, gl::pixel_data_format_e::rgba, gl::pixel_data_type_e::byte);
    auto       image                  = gl::image{ gl::image::format_e::rgba_uint8, window_dimensions, std::move(frame_buffer_pixels) };
    auto       encoded_image          = gl::image::encode<gl::image::extension_e::png>(gl::image::format_e::rgba_uint8, image);
    
    write_file("my_image.png", encoded_image);
}
