export module opengl.utility;

import std;
import opengl.domain;
import opengl.types;
import vendor.glm;

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

              auto value_pointer        (auto& value) -> auto*
    {
        return glm::value_ptr(value);
    }
              auto value_pointer        (const auto& value) -> const auto*
    {
        return glm::value_ptr(value);
    }

    template<std::ranges::range Range>
    constexpr auto as_bytes             (Range source) -> std::span<const gl::byte_t>
    {
        using value_t = typename Range::value_type;
        return std::span{ std::bit_cast<const gl::byte_t*>(source.data()), source.size() * sizeof(value_t) };
    }
    template<typename S, typename T> requires std::is_standard_layout_v<S>
    constexpr auto offset_of            (T S::* member) -> std::size_t
    {
        return reinterpret_cast<std::size_t>(&(static_cast<S*>(nullptr)->*member));
    }
    template<typename T>
    constexpr auto ternary              (gl::bool_t condition, T true_type, T false_type) -> T
    {
        if   (condition) return true_type ;
        else             return false_type;
    }
    
    constexpr auto clamp_range          (gl::range_t      range     , gl::size_t boundary) -> gl::range_t
    {
        range.index = std::min(range.index, boundary              );
        range.count = std::min(range.count, boundary - range.index);

        return range;
    }
    constexpr auto clamp_range          (gl::byte_range_t byte_range, gl::size_t  boundary) -> gl::byte_range_t
    {
        byte_range.offset = std::min(byte_range.offset, boundary                    );
        byte_range.size   = std::min(byte_range.size  , boundary - byte_range.offset);

        return byte_range;
    }
    template<typename T>
    constexpr auto convert_range        (gl::range_t      range) -> gl::byte_range_t
    {
        return gl::byte_range_t{ range.count * sizeof(T), range.index * sizeof(T) };
    }
    template<typename T>
    constexpr auto convert_range        (gl::byte_range_t range) -> gl::range_t
    {
        return gl::range_t{ range.size / sizeof(T), range.offset / sizeof(T) };
    }
    constexpr auto range_overlaps       (gl::range_t      first, gl::range_t      second) -> gl::bool_t
    {
        return (first.index < second.index + second.count) && (second.index < first.index + second.count);
    }
    constexpr auto range_overlaps       (gl::byte_range_t first, gl::byte_range_t second) -> gl::bool_t
    {
        return (first.offset < second.offset + second.size) && (second.offset < first.offset + second.size);
    }
    constexpr auto range_intersection   (gl::byte_range_t first, gl::byte_range_t second) -> gl::byte_range_t
    {
        const auto first_end  = gl::size_t{ first .offset + first .size };
        const auto second_end = gl::size_t{ second.offset + second.size };
        const auto start      = gl::size_t{ (first.offset > second.offset) ? first.offset : second.offset };
        const auto end        = gl::size_t{ (first_end < second_end) ? first_end : second_end };

        if   (start < end) return gl::byte_range_t{ end - start, start };
        else               return gl::byte_range_t{};
    }
    template<typename T, gl::uint32_t Count>
    constexpr auto clamp_region         (const gl::region_t<T, Count>& region, const gl::vector_t<T, Count>& boundary) -> gl::region_t<T, Count>
    {
        auto result = gl::region_t<T, Count>{};
        std::ranges::for_each(std::views::iota(0u, Count), [&](auto index)
            {
                const auto maximum_extent = T{ boundary[index] - std::clamp(region.origin[index], T{ 0 }, boundary[index]) };
                result.origin[index]      = std::clamp(region.origin[index], T{ 0 }, boundary[index]);
                result.extent[index]      = std::clamp(region.extent[index], T{ 0 }, maximum_extent );
            });

        return result;
    }

    template<gl::uint32_t Count>
    constexpr auto mipmap_levels        (const gl::vector_t<gl::uint32_t, Count>& dimensions) -> gl::uint8_t
    {
        return static_cast<gl::uint8_t>(glm::levels(dimensions));
    }

              void todo                 ()
    {
        throw std::logic_error{ "the method or operation has not been implemented" };
    }
}
