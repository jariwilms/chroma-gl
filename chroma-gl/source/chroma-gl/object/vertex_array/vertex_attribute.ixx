export module opengl.object.vertex_array:vertex_attribute;

import std;
import opengl;

       namespace gl
{
    template<typename T>
    struct component_traits
    {
        using type = T;
        static constexpr auto count     = gl::size_t{ 1u };
        static constexpr auto locations = gl::size_t{ 1u };
    };
    template<typename T, gl::uint32_t Components>
    struct component_traits<gl::vector_t<T, Components>>
    { 
        using type = T; 
        static constexpr auto count     = gl::size_t{ Components };
        static constexpr auto locations = gl::size_t{ 1u         };
    };
    template<typename T, gl::uint32_t Columns, gl::uint32_t Rows>
    struct component_traits<gl::matrix_t<T, Columns, Rows>>
    {
        using type = T;
        static constexpr auto count     = gl::size_t{ Columns };    
        static constexpr auto locations = gl::size_t{ Rows    };
    };
    template<typename T>
    struct component_traits<gl::quaternion_t<T>>
    {
        using type = T; 
        static constexpr auto count     = gl::size_t{ 4u };
        static constexpr auto locations = gl::size_t{ 1u };
    };
}
export namespace gl
{
    template<typename T, gl::size_t count_v = gl::component_traits<T>::count, gl::size_t locations_v = gl::component_traits<T>::locations, gl::size_t divisor_v = 0u, gl::bool_t is_normalized_v = gl::false_>
    struct vertex_attribute
    {
        using trait_t     = gl::component_traits<T>;
        using component_t = typename trait_t::type;

        static constexpr auto count         = count_v;
        static constexpr auto locations     = locations_v;
        static constexpr auto divisor       = divisor_v;
        static constexpr auto is_normalized = is_normalized_v;
        static constexpr auto size          = count * locations * sizeof(component_t);
        
        static_assert(std::is_integral_v<component_t> || std::is_floating_point_v<component_t>, "invalid vertex attribute type");
    };
}
