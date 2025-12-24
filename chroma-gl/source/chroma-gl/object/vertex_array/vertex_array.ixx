export module opengl.object.vertex_array;
export import :vertex_attribute;
export import :vertex_layout;

import std;
import opengl;
import opengl.object;
import opengl.object.buffer;

export namespace gl
{
    class vertex_array : public gl::object
    {
    public:
        explicit
        vertex_array()
            : gl::object{ gl::create_vertex_array() }
            , binding_point_{}, index_count_{}, attribute_location_{} {}
        vertex_array(vertex_array&&) noexcept = default;
       ~vertex_array()
        {
           gl::delete_vertex_array(handle());
        }

        void bind()
        {
            gl::bind_vertex_array(handle());
        }

        void enable_attribute (gl::index_t index)
        {
            gl::enable_vertex_array_attribute(handle(), index);
        }
        void disable_attribute(gl::index_t index)
        {
            gl::disable_vertex_array_attribute(handle(), index);
        }

        template<typename Layout>
        void attach(gl::buffer& vertex_buffer, std::optional<gl::index_t> attribute_location = std::nullopt)
        {
            using layout_t      = Layout;
            using tuple_t       = typename layout_t::tuple_t;
            auto  offset        = gl::ptrdiff_t{};
            attribute_location_ = attribute_location.value_or(attribute_location_);
            
            gl::vertex_array_vertex_buffer(handle(), vertex_buffer.handle(), binding_point_, gl::ptrdiff_t{ 0 }, layout_t::stride);
            std::apply([&](auto... attributes)
                {
                    ([&](auto attribute)
                        {
                            using attribute_t = decltype(attribute);
                            using component_t = typename attribute_t::component_t;
                            
                            enable_attribute(attribute_location_);
                            gl::vertex_array_attribute_format (handle(), gl::map_attribute_type<component_t>(), attribute_location_, attribute_t::components, offset, attribute_t::is_normalized);
                            gl::vertex_array_attribute_binding(handle(), attribute_location_, binding_point_);
                            gl::vertex_array_binding_divisor  (handle(), static_cast<gl::binding_t>(attribute_location_), attribute_t::divisor);

                            offset += attribute_t::stride;
                            ++attribute_location_;
                        } (attributes), ...);
                }, tuple_t{});

            ++binding_point_;
        }
        void attach(gl::buffer& index_buffer)
        {
            gl::vertex_array_element_buffer(handle(), index_buffer.handle());
            index_count_ = index_buffer.count();
        }
        void detach()
        {
            gl::vertex_array_element_buffer(handle(), gl::null_object);
            index_count_ = gl::count_t{ 0u };
        }

        auto index_count() const -> gl::count_t
        {
            return index_count_;
        }

        auto operator=(vertex_array&&) noexcept -> vertex_array& = default;

    private:
        gl::index_t   attribute_location_;
        gl::binding_t binding_point_;
        gl::count_t   index_count_;
    };
}
