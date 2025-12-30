export module opengl:utility;

import std;
import glm;
import :domain;
import :types;

export namespace gl
{
    template<typename T>
    auto to_underlying        (      T        value) noexcept ->       std::underlying_type_t<T>
    {
        return static_cast<std::underlying_type_t<T>>(value);
    }
    template<typename T>
    auto to_underlying_pointer(      T* const value) noexcept ->       std::underlying_type_t<T>* const
    {
        return std::bit_cast<std::underlying_type_t<T>* const>(value);
    }
    template<typename T>
    auto to_underlying_pointer(const T* const value) noexcept -> const std::underlying_type_t<T>* const
    {
        return std::bit_cast<const std::underlying_type_t<T>* const>(value);
    }

    auto value_pointer        (      auto& value) -> auto*
    {
        return glm::value_ptr(value);
    }
    auto value_pointer        (const auto& value) -> const auto*
    {
        return glm::value_ptr(value);
    }

    template<std::ranges::range range>
    auto as_bytes             (const range& source) -> std::span<const gl::byte_t>
    {
        using value_t = typename range::value_type;
        return std::span{ std::bit_cast<const gl::byte_t*>(source.data()), source.size() * sizeof(value_t) };
    }
    template<typename S, typename T> requires std::is_standard_layout_v<S>
    auto offset_of            (T S::* member) -> std::size_t
    {
        return reinterpret_cast<gl::size_t>(&(static_cast<S*>(nullptr)->*member));
    }
    
    template<typename T>
    auto convert_range        (gl::range_t      range) -> gl::byte_range_t
    {
        return gl::byte_range_t{ range.index * sizeof(T), range.count * sizeof(T) };
    }
    template<typename T>
    auto convert_range        (gl::byte_range_t range) -> gl::range_t
    {
        return gl::range_t{ range.offset / sizeof(T), range.size / sizeof(T) };
    }
    auto clamp_range          (gl::range_t      range     , gl::size_t boundary) -> gl::range_t
    {
        range.index = std::min(range.index, boundary              );
        range.count = std::min(range.count, boundary - range.index);

        return range;
    }
    auto clamp_range          (gl::byte_range_t byte_range, gl::size_t boundary) -> gl::byte_range_t
    {
        byte_range.offset = std::min(byte_range.offset, boundary                    );
        byte_range.size   = std::min(byte_range.size  , boundary - byte_range.offset);

        return byte_range;
    }
    auto range_intersection   (gl::range_t      first, gl::range_t      second) -> gl::range_t
    {
        const auto intersect_index = std::max   (first.index              , second.index                   );
        const auto intersect_end   = std::min   (first.index + first.count, second.index  + second.count   );
        const auto intersect_count = intersect_end > intersect_index ? intersect_end - intersect_index : gl::size_t{ 0u };
        
        return gl::range_t{ intersect_index, intersect_count };
    }
    auto range_intersection   (gl::byte_range_t first, gl::byte_range_t second) -> gl::byte_range_t
    {
        const auto intersect_index = std::max   (first.offset             , second.offset              );
        const auto intersect_end   = std::min   (first.offset + first.size, second.offset + second.size);
        const auto intersect_count =intersect_end > intersect_index ? intersect_end - intersect_index : gl::size_t{ 0u };
        
        return gl::byte_range_t{ intersect_count, intersect_index };
    }
    auto range_overlaps       (gl::range_t      first, gl::range_t      second) -> gl::bool_t
    {
        return (first.index < second.index + second.count) && (second.index < first.index + second.count);
    }
    auto range_overlaps       (gl::byte_range_t first, gl::byte_range_t second) -> gl::bool_t
    {
        return (first.offset < second.offset + second.size) && (second.offset < first.offset + second.size);
    }
    template<typename T, gl::uint32_t Components>
    auto clamp_region         (const gl::region_t<T, Components>& region, const gl::vector_t<T, Components>& boundary) -> gl::region_t<T, Components>
    {
        auto result = gl::region_t<T, Components>{};
        std::ranges::for_each(std::views::iota(0u, Components), [&](auto index)
            {
                const auto maximum_extent = T{ boundary[index] - std::clamp(region.origin[index], T{ 0 }, boundary[index]) };
                result.origin[index]      = std::clamp(region.origin[index], T{ 0 }, boundary[index]);
                result.extent[index]      = std::clamp(region.extent[index], T{ 0 }, maximum_extent );
            });

        return result;
    }

    template<gl::uint32_t Count>
    auto mipmap_levels        (const gl::vector_t<gl::uint32_t, Count>& dimensions) -> gl::uint8_t
    {
        return static_cast<gl::uint8_t>(glm::levels(dimensions));
    }
}
