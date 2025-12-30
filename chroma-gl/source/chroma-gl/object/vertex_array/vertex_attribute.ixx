export module chroma_gl:object.vertex_array.vertex_attribute;

import std;
import opengl;

       namespace gl
{
    template<typename component_t>
    struct component_traits
    {
        using type = component_t;
        static auto constexpr count     = gl::size_t{ 1u };
        static auto constexpr locations = gl::size_t{ 1u };
    };
    template<typename component_t, gl::uint32_t Components>
    struct component_traits<gl::vector_t<component_t, Components>>
    { 
        using type = component_t; 
        static auto constexpr count     = gl::size_t{ Components };
        static auto constexpr locations = gl::size_t{ 1u         };
    };
    template<typename component_t, gl::uint32_t Columns, gl::uint32_t Rows>
    struct component_traits<gl::matrix_t<component_t, Columns, Rows>>
    {
        using type = component_t;
        static auto constexpr count     = gl::size_t{ Columns };
        static auto constexpr locations = gl::size_t{ Rows    };
    };
    template<typename component_t>
    struct component_traits<gl::quaternion_t<component_t>>
    {
        using type = component_t; 
        static auto constexpr count     = gl::size_t{ 4u };
        static auto constexpr locations = gl::size_t{ 1u };
    };
}
export namespace gl
{
    template<typename attribute_t, gl::size_t count_v = gl::component_traits<attribute_t>::count, gl::size_t locations_v = gl::component_traits<attribute_t>::locations, gl::size_t divisor_v = 0u, gl::bool_t is_normalized_v = gl::false_>
    struct vertex_attribute
    {
        using component_t = typename gl::component_traits<attribute_t>::type;

        static auto constexpr count         = count_v;
        static auto constexpr locations     = locations_v;
        static auto constexpr divisor       = divisor_v;
        static auto constexpr is_normalized = is_normalized_v;
        static auto constexpr size          = count_v * locations_v * sizeof(component_t);
        
        static_assert(std::is_integral_v<component_t> || std::is_floating_point_v<component_t>, "invalid vertex attribute type");
    };
}
