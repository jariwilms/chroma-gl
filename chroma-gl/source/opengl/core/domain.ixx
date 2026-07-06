export module opengl:domain;

import std;
import :types;

export namespace gl
{
    struct index_range
    {
        constexpr
            index_range(gl::count_t count)
            : index{ 0u }, count{ count } {}
        constexpr
            index_range(gl::index_t index, gl::count_t count)
            : index{ index }, count{ count } {}

        auto constexpr is_empty() const -> gl::bool_t
        {
            return count == gl::count_t{ 0u };
        }

        auto constexpr operator==(index_range const&) const -> gl::bool_t = default;

        gl::index_t index;
        gl::count_t count;
    };
    struct byte_range
    {
        constexpr
            byte_range(gl::size_t size)
            : offset{ 0u }, size{ size } {}
        constexpr
            byte_range(gl::offset_t offset, gl::size_t size)
            : offset{ offset }, size{ size } {}

        auto constexpr is_empty() const -> gl::bool_t
        {
            return size == gl::size_t{ 0u };
        }

        auto constexpr operator==(byte_range const&) const -> gl::bool_t = default;

        gl::offset_t offset;
        gl::size_t   size;
    };
    template<std::totally_ordered element_t, gl::size_t dimension_v>
    struct region
    {
        constexpr
        region(gl::vector_t<element_t, dimension_v> const& extent = {}, gl::vector_t<element_t, dimension_v> const& origin = {})
            : extent{ extent }, origin{ origin } {}

        auto constexpr is_empty() const -> gl::bool_t
        {
            for (auto index = gl::size_t{ 0u }; index < dimension_v; ++index)
            {
                if (extent[index] <= element_t{})
                {
                    return gl::true_;
                }
            }
            return gl::false_;
        }

        auto constexpr operator==(region const&) const -> gl::bool_t = default;

        gl::vector_t<element_t, dimension_v> extent;
        gl::vector_t<element_t, dimension_v> origin;
    };

    using line      = gl::region<gl::uint32_t, 1u>;
    using rectangle = gl::region<gl::uint32_t, 2u>;
    using box       = gl::region<gl::uint32_t, 3u>;
    using hyper_box = gl::region<gl::uint32_t, 4u>;
}
