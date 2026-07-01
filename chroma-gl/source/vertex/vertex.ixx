export module chroma_gl:vertex;

import std;
import opengl;

export namespace gl
{
    template <typename structure_t, typename... range_t>
    auto make_interleaved(range_t&&... ranges) -> std::vector<structure_t>
    {
        return std::views::zip(std::forward<range_t>(ranges)...)
            | std::views::transform([](auto&& tuple)
                {
                    return std::apply([](auto&&... args)
                        {
                            return structure_t{ std::forward<decltype(args)>(args)... };
                        }, std::forward<decltype(tuple)>(tuple));
                })
            | std::ranges::to<std::vector<structure_t>>();
    }
}
export namespace gl::vertex
{
    struct triangle
    {
        static auto constexpr positions   = std::array<gl::vector_3f, 3u>
        {
            gl::vector_3f{  0.0f,  1.0f,  0.0f }, 
            gl::vector_3f{ -1.0f, -1.0f,  0.0f }, 
            gl::vector_3f{  1.0f, -1.0f,  0.0f }, 
        };
        static auto constexpr coordinates = std::array<gl::vector_2f, 3u>
        {
            gl::vector_2f{ 0.5f, 1.0f }, 
            gl::vector_2f{ 0.0f, 0.0f }, 
            gl::vector_2f{ 1.0f, 0.0f }, 
        };
        static auto constexpr indices     = std::array<gl::uint32_t , 3u>
        {
            0u, 1u, 2u, 
        };
    };
    struct rectangle
    {
        static auto constexpr positions   = std::array<gl::vector_3f, 4u> 
        {
            gl::vector_3f{  1.0f,  1.0f,  0.0f }, 
            gl::vector_3f{ -1.0f,  1.0f,  0.0f }, 
            gl::vector_3f{ -1.0f, -1.0f,  0.0f }, 
            gl::vector_3f{  1.0f, -1.0f,  0.0f }, 
        };
        static auto constexpr coordinates = std::array<gl::vector_2f, 4u> 
        {
            gl::vector_2f{ 1.0f,  1.0f }, 
            gl::vector_2f{ 0.0f,  1.0f }, 
            gl::vector_2f{ 0.0f,  0.0f }, 
            gl::vector_2f{ 1.0f,  0.0f }, 
        };
        static auto constexpr indices     = std::array<gl::uint32_t , 6u> 
        {
            0u, 1u, 2u, 
            0u, 2u, 3u, 
        };
    };
}
