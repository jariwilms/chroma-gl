import std;
import chroma_gl;
import rgfw;

static inline void instance_id()
{
    //Window creation
    auto const window_dimensions      = rgfw::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window   { "instance id example", window_dimensions };
    
    //Vertex data
    auto const vertex_data            = std::vector<gl::float32_t>
    {
         // x      y      r      g      b 
         0.0f,  0.1f,  1.0f,  0.0f,  0.0f,  // top
        -0.1f, -0.1f,  0.0f,  1.0f,  0.0f,  // bottom left
         0.1f, -0.1f,  0.0f,  0.0f,  1.0f   // bottom right
    };

    //Buffers and layouts
    auto       vertex_array           = gl::vertex_array{};
    auto       vertex_buffer          = gl::vertex_buffer<gl::float32_t>{ vertex_data };
    using      position_attribute     = gl::vertex_attribute<gl::float32_t, 2u>;
    using      color_attribute        = gl::vertex_attribute<gl::float32_t, 3u>;
    using      instance_layout        = gl::interleaved_layout<position_attribute, color_attribute>;
    vertex_array.attach<instance_layout>(vertex_buffer);
    
    //Shader setup
    auto pipeline = gl::create_pipeline_from_files(
        {
            { gl::shader::type_e::vertex  , "examples/assets/shaders/compiled/instance_id.vert.spv" },
            { gl::shader::type_e::fragment, "examples/assets/shaders/compiled/instance_id.frag.spv" },
        });



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
