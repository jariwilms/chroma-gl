export module opengl.color;

import std;
import opengl.types;

export namespace gl::color
{
    constexpr auto from_hexadecimal(gl::uint32_t code) -> gl::vector_4f
    {
        return gl::vector_4f
        { 
            ((code >> 24u) & 0xFF) / 255.0f, 
            ((code >> 16u) & 0xFF) / 255.0f, 
            ((code >>  8u) & 0xFF) / 255.0f, 
            ((code >>  0u) & 0xFF) / 255.0f, 
        };
    }

    constexpr auto white       = gl::vector_4f{ 1.0f, 1.0f, 1.0f, 1.0f };
    constexpr auto gray        = gl::vector_4f{ 0.5f, 0.5f, 0.5f, 1.0f };
    constexpr auto black       = gl::vector_4f{ 0.0f, 0.0f, 0.0f, 1.0f };
    constexpr auto red         = gl::vector_4f{ 1.0f, 0.0f, 0.0f, 1.0f };
    constexpr auto green       = gl::vector_4f{ 0.0f, 1.0f, 0.0f, 1.0f };
    constexpr auto blue        = gl::vector_4f{ 0.0f, 0.0f, 1.0f, 1.0f };
    constexpr auto cyan        = gl::vector_4f{ 0.0f, 1.0f, 1.0f, 1.0f };
    constexpr auto magenta     = gl::vector_4f{ 1.0f, 0.0f, 1.0f, 1.0f };
    constexpr auto yellow      = gl::vector_4f{ 1.0f, 1.0f, 0.0f, 1.0f };
    
    constexpr auto transparent = gl::vector_4f{ 0.0f, 0.0f, 0.0f, 0.0f };
}
