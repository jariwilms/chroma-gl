export module opengl:utility;

import std;
import glm;
import :domain;
import :types;

export namespace gl
{
    template<typename value_t>
    auto to_underlying        (value_t              value) noexcept -> std::underlying_type_t<value_t>
    {
        return static_cast<std::underlying_type_t<value_t>>(value);
    }
    template<typename value_t>
    auto to_underlying_pointer(value_t      * const value) noexcept -> std::underlying_type_t<value_t>      * const
    {
        return std::bit_cast<std::underlying_type_t<value_t>* const>(value);
    }
    template<typename value_t>
    auto to_underlying_pointer(value_t const* const value) noexcept -> std::underlying_type_t<value_t> const* const
    {
        return std::bit_cast<std::underlying_type_t<value_t> const* const>(value);
    }

    auto value_pointer        (auto      & value) -> auto*
    {
        return glm::value_ptr(value);
    }
    auto value_pointer        (auto const& value) -> auto const*
    {
        return glm::value_ptr(value);
    }

    template<std::ranges::range range_t>
    auto as_bytes             (range_t const& range) -> std::span<gl::byte_t const>
    {
        using value_t = typename range_t::value_type;
        return std::span{ std::bit_cast<gl::byte_t const*>(range.data()), range.size() * sizeof(value_t) };
    }
    template<typename structure_t, typename member_t> requires std::is_standard_layout_v<structure_t>
    auto offset_of            (member_t structure_t::* member) -> gl::size_t
    {
        return reinterpret_cast<gl::size_t>(&(static_cast<structure_t*>(nullptr)->*member));
    }


    
    template<typename element_t>
    auto convert_range        (gl::range_t      range                                ) -> gl::byte_range_t
    {
        return gl::byte_range_t{ range.index * sizeof(element_t), range.count * sizeof(element_t) };
    }
    template<typename element_t>
    auto convert_range        (gl::byte_range_t range                                ) -> gl::range_t
    {
        return gl::range_t{ range.offset / sizeof(element_t), range.size / sizeof(element_t) };
    }
    auto clamp_range          (gl::range_t      range     , gl::size_t       boundary) -> gl::range_t
    {
        range.index = std::min(range.index, boundary              );
        range.count = std::min(range.count, boundary - range.index);

        return range;
    }
    auto clamp_range          (gl::byte_range_t byte_range, gl::size_t       boundary) -> gl::byte_range_t
    {
        byte_range.offset = std::min(byte_range.offset, boundary                    );
        byte_range.size   = std::min(byte_range.size  , boundary - byte_range.offset);

        return byte_range;
    }
    auto range_intersection   (gl::range_t      alpha     , gl::range_t      beta    ) -> gl::range_t
    {
        auto const intersect_index = std::max   (alpha.index              , beta.index                 );
        auto const intersect_end   = std::min   (alpha.index + alpha.count, beta.index  + beta.count   );
        auto const intersect_count = intersect_end > intersect_index ? intersect_end - intersect_index : gl::size_t{ 0u };
        
        return gl::range_t{ intersect_index, intersect_count };
    }
    auto range_intersection   (gl::byte_range_t alpha     , gl::byte_range_t beta    ) -> gl::byte_range_t
    {
        auto const intersect_index = std::max   (alpha.offset             , beta.offset            );
        auto const intersect_end   = std::min   (alpha.offset + alpha.size, beta.offset + beta.size);
        auto const intersect_count =intersect_end > intersect_index ? intersect_end - intersect_index : gl::size_t{ 0u };
        
        return gl::byte_range_t{ intersect_count, intersect_index };
    }
    auto range_overlaps       (gl::range_t      alpha     , gl::range_t      beta    ) -> gl::bool_t
    {
        return (alpha.index < beta.index + beta.count) && (beta.index < alpha.index + beta.count);
    }
    auto range_overlaps       (gl::byte_range_t alpha     , gl::byte_range_t beta    ) -> gl::bool_t
    {
        return (alpha.offset < beta.offset + beta.size) && (beta.offset < alpha.offset + beta.size);
    }
    template<typename element_t, gl::uint32_t component_v>
    auto clamp_region         (gl::region_t<element_t, component_v> region, gl::vector_t<element_t, component_v> boundary) -> gl::region_t<element_t, component_v>
    {
        auto result = gl::region_t<element_t, component_v>{};
        std::ranges::for_each(std::views::iota(0u, component_v), [&](auto index)
            {
                auto const maximum_extent = element_t{ boundary[index] - std::clamp(region.origin[index], element_t{ 0 }, boundary[index]) };
                result.origin[index]      = std::clamp(region.origin[index], element_t{ 0 }, boundary[index]);
                result.extent[index]      = std::clamp(region.extent[index], element_t{ 0 }, maximum_extent );
            });

        return result;
    }

    template<typename element_t, gl::uint32_t component_v> requires (std::is_integral_v<element_t>)
    auto mipmap_levels        (gl::vector_t<element_t, component_v> dimensions) -> element_t
    {
        return static_cast<element_t>(glm::levels(dimensions));
    }
}
