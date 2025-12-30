export module opengl:domain;

import std;
import :types;

export namespace gl
{
    template<typename T, gl::uint32_t Components>
    struct region_t
    {
        region_t(                                           const gl::vector_t<T, Components>& extent)
            : origin{        }, extent{ extent } {}
        region_t(const gl::vector_t<T, Components>& origin, const gl::vector_t<T, Components>& extent)
            : origin{ origin }, extent{ extent } {}

        auto operator==(const region_t&) const -> gl::bool_t = default;

        gl::vector_t<T, Components> origin;
        gl::vector_t<T, Components> extent;
    };
    struct      range_t
    {
        range_t(                   gl::count_t count)
            : index{    0u }, count{ count } {}
        range_t(gl::index_t index, gl::count_t count)
            : index{ index }, count{ count } {}

        auto empty() const -> gl::bool_t
        {
            return count == gl::count_t{ 0u };
        }

        auto operator==(const range_t&) const -> gl::bool_t = default;

        gl::index_t index;
        gl::count_t count;
    };
    struct byte_range_t
    {
        byte_range_t(                   gl::size_t size)
            : offset{     0u }, size{ size } {}
        byte_range_t(gl::size_t offset, gl::size_t size)
            : offset{ offset }, size{ size } {}

        auto empty() const -> gl::bool_t
        {
            return size == gl::size_t{ 0u };
        }

        auto operator==(const byte_range_t&) const -> gl::bool_t = default;

        gl::size_t offset;
        gl::size_t size  ;
    };

    using length_t       = gl::region_t<gl::uint32_t, 1u>;
    using area_t         = gl::region_t<gl::uint32_t, 2u>;
    using volume_t       = gl::region_t<gl::uint32_t, 3u>;
    using hyper_volume_t = gl::region_t<gl::uint32_t, 4u>; //Yes, this exists
}
