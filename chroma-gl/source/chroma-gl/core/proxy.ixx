export module opengl.proxy;

import std;
import opengl.meta;

export namespace gl
{
    template<typename... T> requires (gl::all_same_type_v<T...>)
    struct proxy
    {
        template<typename U> requires (std::is_convertible_v<U, T> && ...)
        constexpr proxy(const U&   element )
            : pack{ std::make_tuple(static_cast<T>(element)...) } {}
        constexpr proxy(      T... elements)
            : pack{ std::make_tuple(elements...) } {}

        template<typename Fn>
        void apply(Fn&& function)
        {
            std::apply([function](auto&&... element) { ((function(element)), ...); }, pack);
        }

        std::tuple<T...> pack;
    };
}
