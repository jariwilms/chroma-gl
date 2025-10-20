export module opengl.domain;

import std;
import opengl.types;

export namespace gl
{
    template<typename T, gl::uint32_t Count>
    struct region_t
    {
        constexpr region_t(const gl::vector_t<T, Count>& extent = {}, const gl::vector_t<T, Count>& origin = {})
            : extent{ extent }, origin{ origin } {}

        auto operator==(const region_t&) const -> gl::bool_t = default;

        gl::vector_t<T, Count> extent{};
        gl::vector_t<T, Count> origin{};
    };
    struct      range_t
    {
        constexpr range_t(gl::size_t count = {}, gl::size_t index = {})
            : count{ count }, index{ index } {}

        constexpr auto operator==(const range_t&) const -> gl::bool_t = default;

        auto empty() const -> gl::bool_t
        {
            return count == gl::size_t{ 0u };
        }

        gl::size_t count{};
        gl::size_t index{};
    };
    struct byte_range_t
    {
        constexpr byte_range_t(gl::size_t size = {}, gl::size_t offset = {})
            : size{ size }, offset{ offset } {}

        constexpr auto operator==(const byte_range_t&) const -> gl::bool_t = default;

        auto empty() const -> gl::bool_t
        {
            return size == gl::size_t{ 0u };
        }

        gl::size_t size  {};
        gl::size_t offset{};
    };

    using length_t      = gl::region_t<gl::uint32_t, 1u>;
    using area_t        = gl::region_t<gl::uint32_t, 2u>;
    using volume_t      = gl::region_t<gl::uint32_t, 3u>;
    using hypervolume_t = gl::region_t<gl::uint32_t, 4u>; //Yes, this exists
}
