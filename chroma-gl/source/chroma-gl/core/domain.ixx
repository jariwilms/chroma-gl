export module opengl.domain;

import std;
import opengl.types;

export namespace gl
{
    template<typename T, gl::uint32_t N>
    struct region
    {
        constexpr region(const gl::vector_t<T, N>& extent = {}, const gl::vector_t<T, N>& origin = {})
            : extent{ extent }, origin{ origin } {}

        auto operator==(const region&) const -> gl::bool_t = default;

        gl::vector_t<T, N> extent{};
        gl::vector_t<T, N> origin{};
    };
    struct range
    {
        constexpr range(gl::count_t count = {}, gl::index_t index = {})
            : count{ count }, index{ index } {}

        auto operator==(const range&) const -> gl::bool_t = default;

        gl::count_t count{};
        gl::index_t index{};
    };
    struct byte_range
    {
        constexpr byte_range(gl::size_t size = {}, gl::offset_t offset = {})
            : size{ size }, offset{ offset } {}

        auto operator==(const byte_range&) const -> gl::bool_t = default;

        gl::size_t   size{};
        gl::offset_t offset{};
    };

    using length_t      = gl::region<gl::uint32_t, 1u>;
    using area_t        = gl::region<gl::uint32_t, 2u>;
    using volume_t      = gl::region<gl::uint32_t, 3u>;
    using hypervolume_t = gl::region<gl::uint32_t, 4u>; //Yes, this exists

}
