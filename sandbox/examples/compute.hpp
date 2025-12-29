import std;
import chroma_gl;
import rgfw;

static inline void compute()
{
    //Window creation
    auto const window_dimensions      = rgfw::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window   { "compute example", window_dimensions, rgfw::window_display_mode_e::windowed, rgfw::false_ };
    
    //Buffer data
    auto const input_size             = 1024u;
    auto       input_data             = std::vector<gl::float32_t>(input_size);
    auto       output_data            = std::vector<gl::float32_t>(input_size);
    for (auto i = 0u; i < input_size; ++i)
    {
        input_data[i] = static_cast<gl::float32_t>(i); //Set value of each element to its index
    }

    //Buffers and layouts
    auto       input_buffer           = gl::shader_storage_buffer<gl::float32_t>{ input_size };
    auto       output_buffer          = gl::shader_storage_buffer<gl::float32_t>{ input_size };
    auto       fence                  = gl::fence{}; //Fence is not placed by default
    
    //Shader setup
    auto       pipeline               = gl::create_pipeline_from_files(
        {
            { gl::shader::type_e::compute, "examples/assets/shaders/compiled/multiply.comp.spv" },
        });

    //Bindings and data upload
    pipeline     .bind ();
    input_buffer .bind (gl::binding_t{ 0u });
    output_buffer.bind (gl::binding_t{ 1u });
    input_buffer .upload(input_data);
    
    //Dispatch and CPU synchronization
    gl::dispatch_compute(gl::vector_3u{ input_size / 256u, 1u, 1u });
    fence.place(); //Place the fence
    //...          //Do other stuff
    fence.wait();  //Wait for the result
    output_buffer.download(output_data);
}
