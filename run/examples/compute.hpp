import std;
import chroma_gl;
import vendor.glfw;

#include "examples/load_file.hpp"

static inline void compute_result()
{
    //Buffer data
    auto const input_size             = 1024u;
    auto       input_data             = std::vector<gl::float32_t>(input_size);
    auto       output_data            = std::vector<gl::float32_t>(input_size);
    for (auto i = 0u; i < input_size; ++i) input_data[i] = static_cast<gl::float32_t>(i);

    //Window creation
    auto const window_dimensions      = gl::vector_2u{ 1280u, 720u };
    auto       window                 = glfw::window{ "my_window", window_dimensions };
    auto const input                  = window.input_handler();

    //Triangle buffers
    auto       input_buffer           = gl::shader_storage_buffer<gl::float32_t>{ input_size };
    auto       output_buffer          = gl::shader_storage_buffer<gl::float32_t>{ input_size };
    
    //Shader setup
    auto const compute_shader_binary  = load_file("examples/assets/shaders/compiled/multiply.comp.spv");
    auto       compute_shader         = std::make_shared<gl::shader>(gl::shader::type_e::compute, "main", compute_shader_binary);
    auto       shader_list            = std::initializer_list{ compute_shader };
    auto       pipeline               = gl::pipeline{ shader_list };

    //Dispatch and CPU synchronization
    pipeline     .bind ();
    input_buffer .bind (gl::binding_t{ 0u });
    output_buffer.bind (gl::binding_t{ 1u });
    input_buffer .write(input_data);

    gl::dispatch_compute(gl::vector_3u{ input_size / 256u, 1u, 1u });
    auto       fence                  = gl::fence{};
    auto       result                 = gl::client_wait_sync(fence, gl::synchronization_command_e::flush, gl::time_t{ 1000000000 }); //1s
    
    output_buffer.read(output_data);

    window.close();
}
