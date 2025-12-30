export module chroma_gl:object.vertex_array;
export import :object.vertex_array.vertex_attribute;
export import :object.vertex_array.vertex_layout;

import std;
import opengl;
import :object;
import :object.buffer;

export namespace gl
{
    class vertex_array : public gl::object
    {
    public:
        explicit
        vertex_array()
            : gl::object{ gl::create_vertex_array() }
            , attribute_location_{}, binding_point_{}, index_count_{} {}
        vertex_array(vertex_array&&) noexcept = default;
       ~vertex_array()
        {
           gl::delete_vertex_array(handle());
        }

        void bind       ()
        {
            gl::bind_vertex_array(handle());
        }

        void enable     (gl::index_t index)
        {
            gl::enable_vertex_array_attribute(handle(), index);
        }
        void disable    (gl::index_t index)
        {
            gl::disable_vertex_array_attribute(handle(), index);
        }

        template<typename layout_t>
        void attach     (gl::buffer& vertex_buffer, std::optional<gl::index_t> target_location = std::nullopt)
        {
            using tuple_t         = typename layout_t::tuple_t;
            attribute_location_   = target_location.value_or(attribute_location_);
            auto attribute_offset = gl::ptrdiff_t{ 0 };

            gl::vertex_array_vertex_buffer(handle(), vertex_buffer.handle(), binding_point_, gl::ptrdiff_t{ 0 }, layout_t::stride);
            std::apply([&](auto... attributes)
                {
                    (std::invoke([&](auto attribute)
                        {
                            using attribute_t = decltype(attribute);
                            using component_t = typename attribute_t::component_t;

                            gl::vertex_array_binding_divisor(handle(), binding_point_, attribute_t::divisor);
                            for (auto index = gl::index_t{ 0u }; index < attribute_t::locations; ++index)
                            {
                                const auto location_offset = attribute_offset + (index * attribute_t::count * sizeof(component_t));

                                gl::enable_vertex_array_attribute (handle(), attribute_location_);
                                gl::vertex_array_attribute_format (handle(), gl::map_attribute_type<component_t>(), attribute_location_, attribute_t::count, location_offset, attribute_t::is_normalized);
                                gl::vertex_array_attribute_binding(handle(), attribute_location_, binding_point_);
                            
                                ++attribute_location_;
                            }

                            attribute_offset += attribute_t::size;
                        }, attributes)
                    , ...);
                }, tuple_t{});

            ++binding_point_;
        }
        void attach     (gl::buffer& index_buffer)
        {
            gl::vertex_array_element_buffer(handle(), index_buffer.handle());
            index_count_ = index_buffer.count();
        }
        void detach     ()
        {
            gl::vertex_array_element_buffer(handle(), gl::null_object);
            index_count_ = gl::count_t{ 0u };
        }

        auto index_count() const -> gl::count_t
        {
            return index_count_;
        }

        auto operator=  (vertex_array&&) noexcept -> vertex_array& = default;

    private:
        gl::index_t   attribute_location_;
        gl::binding_t binding_point_;
        gl::count_t   index_count_;
    };
}
