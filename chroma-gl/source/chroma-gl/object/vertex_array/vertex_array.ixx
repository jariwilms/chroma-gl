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
            , binding_point_{}, index_count_{}, attribute_index_{} {}
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
        void attach(gl::buffer& vertex_buffer)
        {
            using layout_t = Layout;
            using tuple_t  = typename layout_t::tuple_t;
            
            gl::vertex_array_vertex_buffer(handle(), vertex_buffer.handle(), binding_point_, layout_t::stride, gl::index_t{ 0u });
            
            auto  offset   = gl::ptrdiff_t{};
            std::apply([&](auto... attributes)
                {
                    ([&](auto attribute)
                        {
                            using attribute_t = decltype(attribute);
                            using component_t = typename attribute_t::component_t;
                            
                            enable_attribute(attribute_index_);
                            gl::vertex_array_attribute_format (handle(), attribute_index_, offset, gl::map_attribute_type<component_t>(), attribute_t::components, attribute_t::is_normalized);
                            gl::vertex_array_attribute_binding(handle(), attribute_index_, binding_point_);
                            gl::vertex_array_binding_divisor  (handle(), static_cast<gl::binding_t>(attribute_index_), attribute_t::divisor);

                            offset += attribute_t::stride;
                            ++attribute_index_;
                        } (attributes), ...);
                }, tuple_t{});

            binding_point_ = static_cast<gl::binding_t>(gl::to_underlying(binding_point_) + 1u);
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
        gl::binding_t binding_point_;
        gl::count_t   index_count_;
        gl::index_t   attribute_index_;
    };
}
