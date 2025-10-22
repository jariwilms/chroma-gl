import std;
import chroma_gl;
import vendor.glfw;

auto load_file(std::filesystem::path const& filepath) -> std::vector<gl::byte_t>
{
    auto file = std::ifstream{ filepath, std::ios::binary | std::ios::ate };
    if (!file) throw std::runtime_error{ "failed to open file: " + filepath.string() };

    auto const size   = file.tellg();
    auto       buffer = std::vector<gl::byte_t>(size);

    file.seekg(0u, std::ios::beg);
    file.read(std::bit_cast<gl::char_t*>(buffer.data()), size);

    return buffer;
}

auto main() -> int
{
    auto const triangle_vertices              = std::vector<gl::float32_t>
    {
        //  x      y      z,     r      g      b
         0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, //Top    middle (red  )
        -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f, //Bottom left   (green)
         0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f, //Bottom right  (blue )
    };
    auto const triangle_indices               = std::vector<gl::uint32_t>
    {
           0u,    1u,    2u,                      //First  triangle
    };



    //Window creation
    auto const window_dimensions              = gl::vector_2u{ 1280u, 720u };
    auto       window                         = glfw::window{ "my_window", window_dimensions };
    auto const input                          = window.input_handler();

    //Triangle data
    auto       color_vertex_buffer            = gl::vertex_buffer<gl::float32_t>{ triangle_vertices };
    auto       color_index_buffer             = gl::index_buffer{ triangle_indices };
    auto       color_vertex_array             = gl::vertex_array{};
    auto const position_descriptor            = gl::vertex_attribute_descriptor<gl::float32_t, 3u>{};
    auto const color_descriptor               = gl::vertex_attribute_descriptor<gl::float32_t, 3u>{};
    auto const color_vertex_layout            = gl::vertex_layout<decltype(position_descriptor), decltype(color_descriptor)>{};
    color_vertex_array.tie(color_vertex_buffer.handle(), color_vertex_layout        );
    color_vertex_array.tie(color_index_buffer .handle(), color_index_buffer .count());
    
    //Shader setup
    auto const color_vertex_shader_binary     = load_file("color.vert.spv");
    auto const color_fragment_shader_binary   = load_file("color.frag.spv");
    auto       color_vertex_shader            = std::make_shared<gl::shader>(gl::shader::type_e::vertex  , "main", color_vertex_shader_binary  );
    auto       color_fragment_shader          = std::make_shared<gl::shader>(gl::shader::type_e::fragment, "main", color_fragment_shader_binary);
    auto       color_shaders                  = std::initializer_list{ color_vertex_shader, color_fragment_shader };
    auto       color_pipeline                 = gl::pipeline{ color_shaders };



    gl::enable<gl::feature_e::blending>();
    gl::blend_function(gl::blending_factor_e::source_alpha, gl::blending_factor_e::one_minus_source_alpha);

    while (!window.should_close())
    {
        window.poll_events();

        gl::clear_color(gl::vector_4f{ 0.1f });
        gl::clear      (gl::buffer_mask_e::all);
        gl::viewport   (window.dimensions());

        color_pipeline    .bind();
        color_vertex_array.bind();
        gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::uint32, color_vertex_array.index_count(), gl::index_t{ 0u });

        window.swap_buffers();
    }

    window.close();
    return 0;
}
