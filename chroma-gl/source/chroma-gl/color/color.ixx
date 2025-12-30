export module chroma_gl:color;

import std;
import glm;
import opengl;

export namespace gl::color
{
    enum class model_e
    {
        additive        , 
        subtractive     , 
        average         , 
        weighted_average, 
    };

    template<color::model_e model, typename... Args>
    constexpr auto mix(const gl::vector_4f&, const gl::vector_4f&, Args... args) = delete;
    template<> constexpr auto mix<color::model_e::additive>        (const gl::vector_4f& first, const gl::vector_4f& second)
    {
        return glm::clamp(first + second, 0.0f, 1.0f);
    }
    template<> constexpr auto mix<color::model_e::subtractive>     (const gl::vector_4f& first, const gl::vector_4f& second)
    {
        const auto first_inverted  = gl::vector_4f{ 1.0f } - first;
        const auto second_inverted = gl::vector_4f{ 1.0f } - second;
        return gl::vector_4f{ 1.0f } - glm::clamp(first_inverted + second_inverted, 0.0f, 1.0f);
    }
    template<> constexpr auto mix<color::model_e::average>         (const gl::vector_4f& first, const gl::vector_4f& second)
    {
        return (first + second) * 0.5f;
    }
    template<> constexpr auto mix<color::model_e::weighted_average>(const gl::vector_4f& first, const gl::vector_4f& second, gl::float32_t weight)
    {
        weight = glm::clamp(weight, 0.0f, 1.0f);
        return first * (1.0f - weight) + second * weight;
    }

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
