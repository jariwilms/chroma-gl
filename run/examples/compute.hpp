import std;
import chroma_gl;
import vendor.rgfw;

#include "examples/load_file.hpp"

static inline void compute()
{
    //Buffer data
    auto const input_size             = 1024u;
    auto       input_data             = std::vector<gl::float32_t>(input_size);
    auto       output_data            = std::vector<gl::float32_t>(input_size);
    for (auto i = 0u; i < input_size; ++i) input_data[i] = static_cast<gl::float32_t>(i); //Set value of each element to its index
    
    

    //Window creation
    auto const window_dimensions      = rgfw::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window   { "my_window", window_dimensions, rgfw::window_display_mode_e::windowed, rgfw::false_ };
    auto const input                  = window.input_handler();

    //Triangle buffers
    auto       input_buffer           = gl::shader_storage_buffer<gl::float32_t>{ input_size };
    auto       output_buffer          = gl::shader_storage_buffer<gl::float32_t>{ input_size };
    
    //Shader setup
    auto const compute_shader_binary  = load_file("examples/assets/shaders/compiled/multiply.comp.spv");
    auto       compute_shader         = std::make_shared<gl::shader>(gl::shader::type_e::compute, "main", compute_shader_binary);
    auto       shader_list            = std::initializer_list{ compute_shader };
    auto       pipeline               = gl::pipeline{ shader_list };



    //Bindings and data upload
    pipeline     .bind ();
    input_buffer .bind (gl::binding_t{ 0u });
    output_buffer.bind (gl::binding_t{ 1u });
    input_buffer .upload(input_data);
    
    //Dispatch and CPU synchronization
    gl::dispatch_compute(gl::vector_3u{ input_size / 256u, 1u, 1u });
    auto       fence                  = gl::fence{}; //Fence is not placed by default
    fence.place();                                   //Place the fence
    //...                                            //Do other stuff
    fence.wait();                                    //Wait for the result
    
    output_buffer.download(output_data);
}
