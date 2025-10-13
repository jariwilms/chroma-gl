# Chroma-gl
A modern OpenGL wrapper

## Introduction
Chroma-gl is a C++23 library that provides a modern, robust, and user-friendly interface for OpenGL.
Its primary goals are to:
* Offer a more intuitive and correct interface for development
* Encapsulate existing OpenGL functions, simplifying integration of custom logic and error checking
* Implement state caching in order to eliminate redundant API calls
* Ensure compile-and runtime safety through input validation

Despite OpenGL showing its age, it is still the go-to interface for aspiring graphics programmers or those who want a simple rendering API.

## Prerequisites
* C++23 Compiler
  * Visual Studio 2026 Insiders is heavily recommended.
* An OpenGL 4.6 compatible graphics driver.

## Getting Started
Note: The C++ module ecosystem is still maturing. Tooling support can be inconsistent, which may require manual project configuration.

1. Generate Project Files
Run the generate.bat script in the root directory. This will use Premake to create a Visual Studio solution (.sln) and project files.
2. Configure Project in Visual Studio (Important!)
Due to how Visual Studio currently handles C++ module dependencies when they are not part of the same project, you must manually adjust a few project settings:
   1. Open the generated .sln file in Visual Studio.
   2. In the Solution Explorer, right-click the chroma-gl project and select Properties.
   3. Navigate to Configuration Properties -> C/C++ -> Output Files.
   4. Change the following settings to use the $(IntDir)%(RelativeDir) macro:
      * Module Output File Name
      * Module Dependencies File Name
      * Object File Name
   5. Click Apply and then OK.

This ensures that the compiled module interface files are placed in a consistent location that your own project can find.

## Usage Example
```cpp
WIP
```

## Documentation
The chroma-gl API is designed to closely mirror the official OpenGL 4.6 specification. For detailed information on specific functions, please refer to the official documentation:
* https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf
* https://registry.khronos.org/OpenGL-Refpages/gl4/
* https://docs.gl/

## Contributing
If you find a bug, have a feature request, or would like to contribute code, please open an issue or submit a pull request. All contributions are welcome.

## License
Chroma-gl is licensed under the MIT License.
