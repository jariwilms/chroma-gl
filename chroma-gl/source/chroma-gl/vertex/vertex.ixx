export module opengl.vertex;

import std;
import opengl;

export namespace gl
{
    template <typename T, typename... Ranges>
    auto make_interleaved(Ranges&&... ranges) -> std::vector<T>
    {
        return std::views::zip(std::forward<Ranges>(ranges)...)
            | std::views::transform([](auto&& tuple)
                {
                    return std::apply([](auto&&... args)
                        {
                            return T{ std::forward<decltype(args)>(args)... };
                        }, std::forward<decltype(tuple)>(tuple));
                })
            | std::ranges::to<std::vector<T>>();
    }
}
export namespace gl::vertex
{
    struct triangle
    {
        static inline const std::array<gl::vector_3f, 3u> positions   = 
        {
            gl::vector_3f{  0.0f,  1.0f,  0.0f }, 
            gl::vector_3f{ -1.0f, -1.0f,  0.0f }, 
            gl::vector_3f{  1.0f, -1.0f,  0.0f }, 
        };
        static inline const std::array<gl::vector_2f, 3u> coordinates = 
        {
            gl::vector_2f{ 0.5f, 1.0f }, 
            gl::vector_2f{ 0.0f, 0.0f }, 
            gl::vector_2f{ 1.0f, 0.0f }, 
        };
        static inline const std::array<gl::uint32_t , 3u> indices     = 
        {
            0u, 1u, 2u, 
        };
    };
    struct rectangle
    {
        static inline const std::array<gl::vector_3f, 4u> positions   = 
        {
            gl::vector_3f{  1.0f,  1.0f,  0.0f }, 
            gl::vector_3f{ -1.0f,  1.0f,  0.0f }, 
            gl::vector_3f{ -1.0f, -1.0f,  0.0f }, 
            gl::vector_3f{  1.0f, -1.0f,  0.0f }, 
        };
        static inline const std::array<gl::vector_2f, 4u> coordinates = 
        {
            gl::vector_2f{ 1.0f,  1.0f }, 
            gl::vector_2f{ 0.0f,  1.0f }, 
            gl::vector_2f{ 0.0f,  0.0f }, 
            gl::vector_2f{ 1.0f,  0.0f }, 
        };
        static inline const std::array<gl::uint32_t , 6u> indices     = 
        {
            0u, 1u, 2u, 
            0u, 2u, 3u, 
        };
    };
}
