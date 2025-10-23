# Chroma-gl
An OpenGL wrapper library.

## Introduction
Chroma-gl is a C++23 library that provides a modern, robust, and user-friendly interface for OpenGL.
Its primary goals are to:
* Offer a more intuitive and correct interface for development.
* Encapsulate existing OpenGL functions, simplifying integration of custom logic and error checking.
* Implement state caching in order to eliminate redundant API calls.
* Ensure compile-and runtime safety through input validation.

Even though OpenGL is showing its age, it is still widely used by aspiring graphics programmers, or those who want a less complex rendering API.

This library is designed in two parts, and can be imported using the following modules:
* opengl: provides a wrapper around the OpenGL 4.6 API
* chroma_gl: provides additional object classes like gl::texture_2d, gl::shader etc.

## Prerequisites
* C++23 Compiler
  * Visual Studio 2026 Insiders is heavily recommended.
* An OpenGL 4.6 compatible graphics driver.

## Getting Started
Note: The C++ module ecosystem is still maturing. Tooling support can be inconsistent, which may require manual project configuration

1. Create solution<br>
Run the generate.bat script in the root directory. Premake5 will generate a Visual Studio solution (.sln) along with project files.
2. Open the solution.
3. Build the solution. If you encounter errors about missing module files, continue to step 4.
4. Configure Project in Visual Studio. (Important!)<br>
Due to how Visual Studio currently handles C++ module dependencies, you must manually adjust a few project settings:
   1. In the Solution Explorer, right-click the chroma-gl project and select Properties.
   2. Navigate to Configuration Properties -> C/C++ -> Output Files.
   3. Change the following settings to use the $(IntDir)%(RelativeDir) macro:
      * Module Output File Name
      * Module Dependencies File Name
      * Object File Name
   4. Click Apply and then OK.

## Usage Example
The following program demonstrates how to render a simple triangle to the screen

```cpp
import std;
import chroma_gl;
import vendor.glfw;

auto load_file(std::filesystem::path const& filepath) -> std::vector<gl::byte_t>
{
    auto file = std::ifstream{ filepath, std::ios::binary | std::ios::ate };
    if (!file) throw std::runtime_error{ "failed to open file: " + filepath.string() };

    auto const size   = file.tellg();
    auto       buffer = std::vector<gl::byte_t>(static_cast<gl::size_t>(size));

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
```

## Documentation
The chroma-gl API is designed to closely mirror the official OpenGL 4.6 specification. For detailed information, please refer to the official documentation:
* https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf
* https://registry.khronos.org/OpenGL-Refpages/gl4/
* https://docs.gl/

## Contributing
If you find a bug, have a feature request, or would like to contribute code, please open an issue or submit a pull request. All contributions are welcome.

## License
Chroma-gl is licensed under the MIT License.

## Addendum
###### <i>Someone please hire me lol</i>
