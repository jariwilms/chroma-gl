import std;
import chroma_gl;
import vendor.glfw;

#include "load_file.hpp"

void texture_example()
{
    auto const texture_vertices               = std::vector<gl::float32_t>
    {
        //  x      y      z      u      v
         0.5f,  0.5f,  0.0f,  1.0f,  1.0f,        // top    right
        -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,        // top    left 
        -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,        // bottom left
         0.5f, -0.5f,  0.0f,  1.0f,  0.0f,        // bottom right
    };
    auto const texture_indices                = std::vector<gl::uint32_t>
    {
           0u,    1u,    2u,                      //First  triangle
           0u,    2u,    3u,                      //Second triangle
    };



    //Window creation
    auto const window_dimensions              = gl::vector_2u{ 1280u, 720u };
    auto       window                         = glfw::window{ "my_window", window_dimensions };
    auto const input                          = window.input_handler();

    //Texture data
    auto       texture_vertex_buffer          = gl::vertex_buffer<gl::float32_t>{ texture_vertices };
    auto       texture_index_buffer           = gl::index_buffer                { texture_indices  };
    auto       texture_vertex_array           = gl::vertex_array{};
    auto const position_descriptor            = gl::vertex_attribute_descriptor<gl::float32_t, 3u>{};
    auto const uv_descriptor                  = gl::vertex_attribute_descriptor<gl::float32_t, 2u>{};
    auto const texture_vertex_layout          = gl::vertex_layout<decltype(position_descriptor), decltype(uv_descriptor)>{};
    texture_vertex_array.tie(texture_vertex_buffer.handle(), texture_vertex_layout        );
    texture_vertex_array.tie(texture_index_buffer .handle(), texture_index_buffer .count());

    auto       image_data                     = load_file("assets/textures/opengl_logo.png");
    auto       image                          = gl::image::decode(gl::image::format_e::rgba_uint8, image_data);
    auto       texture                        = gl::texture_2d{ gl::texture_2d::format_e::rgba_uint8_n, image.dimensions() };
    auto const texture_state                  = gl::texture_state
    {
        .minification_filter  = gl::texture_minification_filter_e ::linear_mipmap_linear, 
        .magnification_filter = gl::texture_magnification_filter_e::linear              , 
        .maximum_anisotropy   = 16.0f                                                   , 
    };
    auto const pixel_buffer_data              = gl::pixel_buffer_data{ gl::texture_base_format_e::rgba, gl::pixel_data_type_e::byte };
    texture.transfer        (pixel_buffer_data, image.data());
    texture.generate_mipmaps();
    texture.apply           (texture_state);

    //Shader setup
    auto const texture_vertex_shader_binary   = load_file("assets/shaders/compiled/texture.vert.spv");
    auto const texture_fragment_shader_binary = load_file("assets/shaders/compiled/texture.frag.spv");
    auto       texture_vertex_shader          = std::make_shared<gl::shader>(gl::shader::type_e::vertex  , "main", texture_vertex_shader_binary  );
    auto       texture_fragment_shader        = std::make_shared<gl::shader>(gl::shader::type_e::fragment, "main", texture_fragment_shader_binary);
    auto       texture_shaders                = std::initializer_list{ texture_vertex_shader, texture_fragment_shader };
    auto       texture_pipeline               = gl::pipeline{ texture_shaders };



    gl::enable<gl::feature_e::blending>();
    gl::blend_function(gl::blending_factor_e::source_alpha, gl::blending_factor_e::one_minus_source_alpha);

    while (!window.should_close())
    {
        window.poll_events();

        gl::clear_color(gl::vector_4f{ 0.1f });
        gl::clear      (gl::buffer_mask_e::all);
        gl::viewport   (window.dimensions());

        texture_pipeline    .bind();
        texture_vertex_array.bind();
        texture.bind(gl::binding_t{ 0u });
        gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::uint32, texture_vertex_array.index_count(), gl::index_t{ 0u });

        window.swap_buffers();
    }

    window.close();
}
