# Chroma-gl
An OpenGL wrapper library.

## Introduction
Chroma-gl is a C++23 library that provides a modern, robust, and user-friendly interface for OpenGL.
Its primary goals are to:
* Offer a more intuitive and correct interface for development
* Encapsulate existing OpenGL functions, simplifying integration of custom logic and error checking
* Implement state caching in order to eliminate redundant API calls
* Ensure compile-and runtime safety through input validation

This library is designed in two parts, and can be imported using the following modules:
| Module    | Description                                                                         |
|-----------|-------------------------------------------------------------------------------------|
| opengl    | Wrapper around the OpenGL 4.6 API                                                   |
| chroma_gl | Provides additional utility and object classes like gl::buffer, gl::texture_2d etc. |

## Prerequisites
* C++23 Compiler
  * Visual Studio 2026 Insiders is heavily recommended.
* An OpenGL 4.6 compatible graphics driver.

## Getting Started
>[!NOTE]
>The C++ module ecosystem is still maturing. Tooling support can be inconsistent, which may require manual project configuration.

1. Create solution  
Run the generate.bat script in the root directory. Premake will generate a Visual Studio solution (.sln) along with project files
2. Build the solution. If you do not encounter errors about missing module files, you may skip step 3
3. Configure Project in Visual Studio  
Due to how Visual Studio currently handles C++ module dependencies, you may need to manually adjust some project settings
   1. In the Solution Explorer, right-click the chroma-gl project and select Properties
   2. Navigate to Configuration Properties -> C/C++ -> Output Files
   3. Change the following settings to use the $(IntDir)%(RelativeDir) macro:
      * Module Output File Name
      * Module Dependencies File Name
      * Object File Name
   4. Click Apply and then OK

## Usage Example
The following program demonstrates how to render a simple triangle to the screen.

```cpp
import std;
import chroma_gl;
import vendor.rgfw;

auto load_file(std::filesystem::path const& filepath) -> std::vector<gl::byte_t>
{
    auto file   = std::ifstream{ filepath, std::ios::binary | std::ios::ate };
    if (!file) throw std::runtime_error{ "failed to open file" };

    auto buffer = std::vector<gl::byte_t>(file.tellg());
    file.seekg(0u);
    file.read (reinterpret_cast<gl::char_t*>(buffer.data()), buffer.size());
    
    return buffer;
}

auto main() -> int
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
    auto const vertex_shader_binary   = load_file("examples/assets/shaders/compiled/triangle.vert.spv");
    auto const fragment_shader_binary = load_file("examples/assets/shaders/compiled/triangle.frag.spv");
    auto       vertex_shader          = std::make_shared<gl::shader>(gl::shader::type_e::vertex  , "main", vertex_shader_binary  );
    auto       fragment_shader        = std::make_shared<gl::shader>(gl::shader::type_e::fragment, "main", fragment_shader_binary);
    auto       shader_list            = std::initializer_list{ vertex_shader, fragment_shader };
    auto       pipeline               = gl::pipeline{ shader_list };


    
    //Render loop
    while (window)
    {
        window.process_events();

        gl::viewport   (window.dimensions()   );
        gl::clear_color(gl::vector_4f{ 0.1f } );
        gl::clear      (gl::buffer_mask_e::all);
        
        pipeline    .bind();
        vertex_array.bind();
        gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::uint32, vertex_array.index_count(), gl::index_t{ 0u });

        window.swap_buffers();
    }

    return 0;
}
```

## Documentation
Chroma-gl is designed to closely mirror the OpenGL 4.6 API. For detailed information, please refer to the official documentation:
* https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf
* https://registry.khronos.org/OpenGL-Refpages/gl4/
* https://docs.gl/

## Contributing
If you find a bug, have a feature request, or would like to contribute code, please open an issue or submit a pull request. All contributions are welcome.

## License
Chroma-gl is licensed under the MIT License.

## Addendum
###### <i>Someone please hire me lol</i>
