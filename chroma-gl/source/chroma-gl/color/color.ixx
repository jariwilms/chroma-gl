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

    template<color::model_e model_v, typename... argument_t>
    auto constexpr mix(gl::vector_4f, gl::vector_4f, argument_t...) = delete;
    template<> 
    auto constexpr mix<color::model_e::additive>        (gl::vector_4f alpha, gl::vector_4f beta)
    {
        return glm::clamp(alpha + beta, 0.0f, 1.0f);
    }
    template<> 
    auto constexpr mix<color::model_e::subtractive>     (gl::vector_4f alpha, gl::vector_4f beta)
    {
        auto const additive = color::mix<color::model_e::additive>(gl::vector_4f{ 1.0f } - alpha, gl::vector_4f{ 1.0f } - beta);
        return gl::vector_4f{ 1.0f } - additive;
    }
    template<> 
    auto constexpr mix<color::model_e::average>         (gl::vector_4f alpha, gl::vector_4f beta)
    {
        return (alpha + beta) * 0.5f;
    }
    template<> 
    auto constexpr mix<color::model_e::weighted_average>(gl::vector_4f alpha, gl::vector_4f beta, gl::float32_t factor)
    {
        factor = glm::clamp(factor, 0.0f, 1.0f);
        return alpha * (1.0f - factor) + beta * factor;
    }

    auto constexpr from_hexadecimal(gl::uint32_t code) -> gl::vector_4f
    {
        return gl::vector_4f
        { 
            ((code >> 24u) & 0xFF) / 255.0f, 
            ((code >> 16u) & 0xFF) / 255.0f, 
            ((code >>  8u) & 0xFF) / 255.0f, 
            ((code >>  0u) & 0xFF) / 255.0f, 
        };
    }

    auto constexpr white       = gl::vector_4f{ 1.0f, 1.0f, 1.0f, 1.0f };
    auto constexpr gray        = gl::vector_4f{ 0.5f, 0.5f, 0.5f, 1.0f };
    auto constexpr black       = gl::vector_4f{ 0.0f, 0.0f, 0.0f, 1.0f };
    auto constexpr red         = gl::vector_4f{ 1.0f, 0.0f, 0.0f, 1.0f };
    auto constexpr green       = gl::vector_4f{ 0.0f, 1.0f, 0.0f, 1.0f };
    auto constexpr blue        = gl::vector_4f{ 0.0f, 0.0f, 1.0f, 1.0f };
    auto constexpr cyan        = gl::vector_4f{ 0.0f, 1.0f, 1.0f, 1.0f };
    auto constexpr magenta     = gl::vector_4f{ 1.0f, 0.0f, 1.0f, 1.0f };
    auto constexpr yellow      = gl::vector_4f{ 1.0f, 1.0f, 0.0f, 1.0f };
    
    auto constexpr transparent = gl::vector_4f{ 0.0f, 0.0f, 0.0f, 0.0f };
}
