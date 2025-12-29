import std;
import chroma_gl;
import rgfw;

void frame_buffer()
{
    //Window creation
    auto const window_dimensions      = rgfw::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window   { "frame buffer example", window_dimensions };
    auto const input                  = window.input_handler();

    //Vertex data
    auto const vertex_data            = std::vector<gl::float32_t>
    {
        //  x      y      z,     r      g      b
         0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 
        -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 
         0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 
    };
    auto const index_data             = std::vector<gl::uint32_t>
    {
           0u,    1u,    2u, 
    };

    //Buffers and layouts
    auto       vertex_array           = gl::vertex_array{};
    auto       vertex_buffer          = gl::vertex_buffer<gl::float32_t>{ vertex_data };
    auto       index_buffer           = gl::index_buffer                { index_data  };
    using      position_attribute     = gl::vertex_attribute<gl::vector_3f>;
    using      color_attribute        = gl::vertex_attribute<gl::vector_3f>;
    using      frame_buffer_layout    = gl::interleaved_layout<position_attribute, color_attribute>;
    vertex_array.attach<frame_buffer_layout>(vertex_buffer);
    vertex_array.attach                     (index_buffer );
    
    //Shader setup
    auto pipeline                     = gl::create_pipeline_from_files(
        {
            { gl::shader::type_e::vertex  , "examples/assets/shaders/compiled/triangle.vert.spv" },
            { gl::shader::type_e::fragment, "examples/assets/shaders/compiled/triangle.frag.spv" },
        });

    //Frame Buffer Specification
    auto const color_specification    = gl::frame_buffer_specification{ "my_color", gl::frame_buffer_surface_e::texture      , gl::texture_format_e      ::rgba_uint8_n              };
    auto const depth_specification    = gl::frame_buffer_specification{ "my_depth", gl::frame_buffer_surface_e::render_buffer, gl::render_buffer_format_e::depth_stencil_uint32_24_8 };
    auto const attachment_map         = gl::frame_buffer_attachment_map_t
    {
        { gl::frame_buffer_attachment_e::color_0      , color_specification }, 
        { gl::frame_buffer_attachment_e::depth_stencil, depth_specification }, 
    };
    auto       frame_buffer           = gl::frame_buffer{ attachment_map, window_dimensions };



    //Render Loop
    while (window)
    {
        window.process_events();

        gl::viewport   (window.dimensions()   );
        gl::clear_color(gl::vector_4f{ 0.1f } );
        gl::clear      (gl::buffer_mask_e::all);
        
        pipeline       .bind();
        vertex_array   .bind();
        frame_buffer.bind(gl::frame_buffer::target_e::read_write);
        gl::draw_elements    (gl::draw_mode_e::triangles, gl::draw_type_e::uint32, vertex_array.index_count(), gl::index_t{ 0u });
        gl::blit_frame_buffer(frame_buffer.handle(), gl::default_frame_buffer, gl::buffer_mask_e::color, gl::frame_buffer_filter_e::nearest, window_dimensions, window_dimensions);

        if (input->key_pressed(rgfw::key_e::s))
        {
            auto const frame_buffer_pixels = gl::read_pixels(window.dimensions(), gl::pixel_data_format_e::rgba, gl::pixel_data_type_e::byte);
            auto const image               = gl::image{ gl::image::format_e::rgba_uint8, window.dimensions(), std::move(frame_buffer_pixels) };
            auto const encoded_image       = gl::image::encode<gl::image::extension_e::png>(gl::image::format_e::rgba_uint8, image);
    
            gl::io::write("my_image.png", encoded_image);
        }

        window.swap_buffers();
    }
}
