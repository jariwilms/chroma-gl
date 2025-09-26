export module opengl.utility;

import std;
import opengl.types;
import opengl.domain;

export namespace gl
{
    template<typename T>
    constexpr auto to_underlying    (      T        value) noexcept -> std::underlying_type_t<T>
    {
        return static_cast<std::underlying_type_t<T>>(value);
    }
    template<typename T>
    constexpr auto to_underlying_ptr(      T* const value) noexcept -> std::underlying_type_t<T>* const
    {
        return std::bit_cast<std::underlying_type_t<T>* const>(value);
    }
    template<typename T>
    constexpr auto to_underlying_ptr(const T* const value) noexcept -> const std::underlying_type_t<T>* const
    {
        return std::bit_cast<const std::underlying_type_t<T>* const>(value);
    }



    template<template<typename> typename C, typename T, typename U>
    constexpr auto compare(const T left, const U right) -> gl::bool_t
    {
        if constexpr (std::is_same_v<C<gl::void_t>, std::equal_to     <gl::void_t>>) return std::cmp_equal        (left, right);
        if constexpr (std::is_same_v<C<gl::void_t>, std::not_equal_to <gl::void_t>>) return std::cmp_not_equal    (left, right);
        if constexpr (std::is_same_v<C<gl::void_t>, std::less         <gl::void_t>>) return std::cmp_less         (left, right);
        if constexpr (std::is_same_v<C<gl::void_t>, std::greater      <gl::void_t>>) return std::cmp_greater      (left, right);
        if constexpr (std::is_same_v<C<gl::void_t>, std::less_equal   <gl::void_t>>) return std::cmp_less_equal   (left, right);
        if constexpr (std::is_same_v<C<gl::void_t>, std::greater_equal<gl::void_t>>) return std::cmp_greater_equal(left, right);
    }
    template<template<typename> typename C, typename T, typename U> requires (std::is_enum_v<T> && std::is_enum_v<U>)
    constexpr auto compare_enum(const T left, const U right) -> gl::bool_t
    {
        return gl::compare<C>(gl::to_underlying(left), gl::to_underlying(right));
    }



    template<typename T>
    constexpr auto convert_range(gl::range     range) -> gl::byte_range
    {
        return gl::byte_range{ static_cast<gl::size_t>(range.count * sizeof(T)), static_cast<gl::offset_t>(range.index * sizeof(T)) };
    }
    template<typename T>
    constexpr auto convert_range(gl::byte_range range) -> gl::range
    {
        return gl::range{ static_cast<gl::count_t>(range.size / sizeof(T)), static_cast<gl::index_t>(range.offset / sizeof(T)) };
    }

    constexpr auto range_overlaps(gl::range     first, gl::range     second) -> gl::bool_t
    {
        return (first.index < second.index + second.count) && (second.index < first.index + second.count);
    }
    constexpr auto range_overlaps(gl::byte_range first, gl::byte_range second) -> gl::bool_t
    {
        return (first.offset < second.offset + second.size) && (second.offset < first.offset + second.size);
    }



    template<typename T, gl::size_t EXTENT = std::dynamic_extent>
    constexpr auto as_bytes(std::span<const T, EXTENT> span) -> std::span<const gl::byte_t>
    {
        return std::span{ reinterpret_cast<const gl::byte_t*>(span.data()), span.size_bytes() };
    }
    template<typename T>
    constexpr auto as_bytes(const T& container) -> std::span<const gl::byte_t>
    {
        return as_bytes(std::span{ container });
    }



    inline void todo()
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }



    template<typename... Ts>
    struct overload_t : Ts... { using Ts::operator()...; };
}
