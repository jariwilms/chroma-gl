export module opengl:domain;

import std;
import :types;

export namespace gl
{
    template<typename T, gl::uint32_t Components>
    struct region_t
    {
        region_t(                                    gl::vector_t<T, Components> extent)
            : origin{        }, extent{ extent } {}
        region_t(gl::vector_t<T, Components> origin, gl::vector_t<T, Components> extent)
            : origin{ origin }, extent{ extent } {}

        auto is_empty  () const -> gl::bool_t
        {
            auto const* value_pointer = std::addressof(extent.x);
            for (auto index = gl::index_t{ 0u }; index < Components; ++index)
            {
                if (value_pointer[index] != T{ 0 }) return gl::false_;
            }

            return gl::true_;
        }

        auto operator==(region_t const&) const -> gl::bool_t = default;

        gl::vector_t<T, Components> origin;
        gl::vector_t<T, Components> extent;
    };
    struct      range_t
    {
        range_t(                   gl::count_t count)
            : index{    0u }, count{ count } {}
        range_t(gl::index_t index, gl::count_t count)
            : index{ index }, count{ count } {}

        auto is_empty  () const -> gl::bool_t
        {
            return count == gl::count_t{ 0u };
        }

        auto operator==(range_t const&) const -> gl::bool_t = default;

        gl::index_t index;
        gl::count_t count;
    };
    struct byte_range_t
    {
        byte_range_t(                     gl::size_t size)
            : offset{     0u }, size{ size } {}
        byte_range_t(gl::offset_t offset, gl::size_t size)
            : offset{ offset }, size{ size } {}

        auto is_empty  () const -> gl::bool_t
        {
            return size == gl::size_t{ 0u };
        }

        auto operator==(byte_range_t const&) const -> gl::bool_t = default;

        gl::offset_t offset;
        gl::size_t   size  ;
    };

    using length_t       = gl::region_t<gl::uint32_t, 1u>;
    using area_t         = gl::region_t<gl::uint32_t, 2u>;
    using volume_t       = gl::region_t<gl::uint32_t, 3u>;
    using hyper_volume_t = gl::region_t<gl::uint32_t, 4u>; //Yes, this exists
}
