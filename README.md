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
  * Visual Studio 2026 Insiders is highly recommended
* An OpenGL 4.6 compatible graphics driver

## Getting Started
>[!NOTE]
>The C++ module ecosystem is still maturing. Tooling support may be inconsistent.

1. Create solution  
Run the following command in the root directory: "generate.bat -s". Premake will generate a Visual Studio solution (.sln) along with project files
Additionally, specifying the "-s" flag will create a standalone sandbox project
2. Build the solution. If you do not encounter errors about missing module files, you may skip the next step
3. (Optional) Fix module filename collisions
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
import rgfw;

auto main() -> int
{
    //Window creation
    auto const window_dimensions      = rgfw::vector_2u{ 1280u, 720u };
    auto       window                 = rgfw::window   { "triangle example", window_dimensions };

    //Vertex data
    struct     vertices
    {
        gl::vector_3f position;
        gl::vector_3f color;
    };
    auto const position_data          = gl::vertex::triangle::positions | std::views::transform([](auto _) { return _ / 2.0f; }) | std::ranges::to<std::vector>();
    auto const color_data             = std::array<gl::vector_3f, 3u>
    {
         gl::vector_3f{ 1.0f, 0.0f, 0.0f }, //red
         gl::vector_3f{ 0.0f, 1.0f, 0.0f }, //green
         gl::vector_3f{ 0.0f, 0.0f, 1.0f }, //blue
    };
    auto const vertex_data            = gl::make_interleaved<vertices>(position_data, color_data);
    auto const index_data             = gl::vertex::triangle::indices;

    //Buffers and layouts
    auto       vertex_array           = gl::vertex_array{};
    auto       vertex_buffer          = gl::vertex_buffer<vertices>{ vertex_data };
    auto       index_buffer           = gl::index_buffer           { index_data  };
    using      position_attribute     = gl::vertex_attribute<gl::float32_t, 3u>;
    using      color_attribute        = gl::vertex_attribute<gl::float32_t, 3u>;
    using      triangle_layout        = gl::interleaved_layout<position_attribute, color_attribute>;
    vertex_array.attach<triangle_layout>(vertex_buffer);
    vertex_array.attach                 (index_buffer );
    
    //Shader setup
    auto pipeline                     = gl::create_pipeline_from_files(
        { 
            { gl::shader::type_e::vertex  , "examples/assets/shaders/compiled/triangle.vert.spv" }, 
            { gl::shader::type_e::fragment, "examples/assets/shaders/compiled/triangle.frag.spv" }, 
        });


    
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
