export module opengl.utility;

import std;
import opengl.domain;
import opengl.types;

export namespace gl
{
    template<typename T>
    constexpr auto to_underlying        (      T        value) noexcept ->       std::underlying_type_t<T>
    {
        return static_cast<std::underlying_type_t<T>>(value);
    }
    template<typename T>
    constexpr auto to_underlying_pointer(      T* const value) noexcept ->       std::underlying_type_t<T>* const
    {
        return std::bit_cast<std::underlying_type_t<T>* const>(value);
    }
    template<typename T>
    constexpr auto to_underlying_pointer(const T* const value) noexcept -> const std::underlying_type_t<T>* const
    {
        return std::bit_cast<const std::underlying_type_t<T>* const>(value);
    }

    template<template<typename> typename C, typename T, typename U>
    constexpr auto compare              (const T left, const U right) -> gl::bool_t
    {
        if constexpr (std::is_same_v<C<T>, std::equal_to     <T>>) return std::cmp_equal        (left, right);
        if constexpr (std::is_same_v<C<T>, std::not_equal_to <T>>) return std::cmp_not_equal    (left, right);
        if constexpr (std::is_same_v<C<T>, std::less         <T>>) return std::cmp_less         (left, right);
        if constexpr (std::is_same_v<C<T>, std::greater      <T>>) return std::cmp_greater      (left, right);
        if constexpr (std::is_same_v<C<T>, std::less_equal   <T>>) return std::cmp_less_equal   (left, right);
        if constexpr (std::is_same_v<C<T>, std::greater_equal<T>>) return std::cmp_greater_equal(left, right);
    }
    template<template<typename> typename C, typename T, typename U> requires (std::is_enum_v<T> && std::is_enum_v<U>)
    constexpr auto compare_enum         (const T left, const U right) -> gl::bool_t
    {
        return gl::compare<C>(gl::to_underlying(left), gl::to_underlying(right));
    }

    constexpr auto clamp_range          (gl::range      range     , gl::count_t boundary) -> gl::range
    {
        range.index = std::min(range.index, boundary              );
        range.count = std::min(range.count, boundary - range.index);

        return range;
    }
    constexpr auto clamp_range          (gl::byte_range byte_range, gl::size_t  boundary) -> gl::byte_range
    {
        byte_range.offset = std::min(byte_range.offset, boundary                    );
        byte_range.size   = std::min(byte_range.size  , boundary - byte_range.offset);

        return byte_range;
    }
    template<typename T>
    constexpr auto convert_range        (gl::range      range) -> gl::byte_range
    {
        return gl::byte_range{ static_cast<gl::size_t>(range.count * sizeof(T)), static_cast<gl::size_t>(range.index * sizeof(T)) };
    }
    template<typename T>
    constexpr auto convert_range        (gl::byte_range range) -> gl::range
    {
        return gl::range{ static_cast<gl::count_t>(range.size / sizeof(T)), static_cast<gl::index_t>(range.offset / sizeof(T)) };
    }
    constexpr auto range_overlaps       (gl::range      first, gl::range      second) -> gl::bool_t
    {
        return (first.index < second.index + second.count) && (second.index < first.index + second.count);
    }
    constexpr auto range_overlaps       (gl::byte_range first, gl::byte_range second) -> gl::bool_t
    {
        return (first.offset < second.offset + second.size) && (second.offset < first.offset + second.size);
    }
    constexpr auto range_intersection   (gl::byte_range first, gl::byte_range second) -> gl::byte_range
    {
        const auto first_end  = gl::size_t{ first .offset + first .size };
        const auto second_end = gl::size_t{ second.offset + second.size };
        const auto start      = gl::size_t{ (first.offset > second.offset) ? first.offset : second.offset };
        const auto end        = gl::size_t{ (first_end < second_end) ? first_end : second_end };

        if   (start < end) return gl::byte_range{ end - start, start };
        else               return gl::byte_range{};
    }

    template<typename T, gl::uint32_t N>
    constexpr auto clamp_region         (const gl::region<T, N>& region, const gl::vector_t<T, N>& boundary) -> gl::region<T, N>
    {
        auto result = gl::region<T, N>{};
        std::ranges::for_each(std::views::iota(0u, N), [&](auto index)
            {
                const auto maximum_extent = T{ boundary[index] - std::clamp(region.origin[index], T{ 0 }, boundary[index]) };
                result.origin[index]      = std::clamp(region.origin[index], T{ 0 }, boundary[index]);
                result.extent[index]      = std::clamp(region.extent[index], T{ 0 }, maximum_extent );
            });

        return result;
    }

    template<std::integral T, gl::uint32_t N>
    constexpr auto mipmap_levels        (const gl::vector_t<T, N>& vector) -> T
    {
        return glm::levels(vector);
    }

    template<typename T, gl::ptrdiff_t EXTENT = std::dynamic_extent>
    constexpr auto as_bytes             (std::span<const T, EXTENT> span) -> std::span<const gl::byte_t>
    {
        return std::span{ reinterpret_cast<const gl::byte_t*>(span.data()), span.size_bytes() };
    }
    template<std::ranges::range R>
    constexpr auto as_bytes             (const R& container) -> std::span<const gl::byte_t>
    {
        return as_bytes(std::span{ container });
    }

    template<typename T>
    constexpr auto ternary(gl::bool_t condition, T true_type, T false_type) -> T
    {
        if   (condition) return true_type ;
        else             return false_type;
    }

    void todo                           ()
    {
        throw std::logic_error{ "the method or operation has not been implemented" };
    }
}
