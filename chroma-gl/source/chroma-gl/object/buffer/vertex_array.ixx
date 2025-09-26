//export module fox.rendering.api.opengl.vertex_array;
//
//import std;
//import fox.rendering.layout;
//import fox.rendering.api.opengl;
//import fox.rendering.api.opengl.buffer;
//
//export namespace fox::gfx::api::gl
//{
//    class vertex_array : public gl::object
//    {
//    public:
//        vertex_array()
//            : gl::object{ gl::create_vertex_array(), [](auto* handle) { gl::delete_vertex_array(*handle); } }
//            , attributeIndex_{}, bindingPoint_{}, indexCount_{} {}
//
//        void bind() const
//        {
//            gl::bind_vertex_array(handle());
//        }
//
//        void enable_attribute (gl::index_t index)
//        {
//            gl::enable_vertex_array_attribute(handle(), index);
//        }
//        void disable_attribute(gl::index_t index)
//        {
//            gl::disable_vertex_array_attribute(handle(), index);
//        }
//
//        template<typename... attributes>
//        void tie(gl::handle_t vertexBuffer, gfx::vertex_layout<attributes...> layout)
//        {
//            gl::vertex_array_vertex_buffer(handle(), vertexBuffer, bindingPoint_, static_cast<gl::size_t>(layout.stride()), gl::index_t{ 0u });
//
//            auto offset = gl::offset_t{};
//            std::apply([&](auto... elements)
//                {
//                    ([&](auto element)
//                        {
//                            enable_attribute(attributeIndex_);
//
//                            gl::vertex_array_attribute_format (handle(), attributeIndex_, offset, gl::map_type<typename decltype(element)::type>(), element.count(), gl::false_);
//                            gl::vertex_array_attribute_binding(handle(), attributeIndex_, bindingPoint_);
//                            gl::vertex_array_binding_divisor  (handle(), gl::binding_t{ attributeIndex_ }, element.instancing_rate());
//
//                            offset += static_cast<gl::offset_t>(element.stride());
//                            ++attributeIndex_;
//                        } (elements), ...);
//                }, layout.attributes());
//
//            bindingPoint_ = gl::binding_t{ gl::to_underlying(bindingPoint_) + 1u };
//        }
//        void tie(gl::handle_t indexBuffer , gl::count_t indices                )
//        {
//            gl::vertex_array_element_buffer(handle(), indexBuffer);
//            indexCount_ = indices;
//        }
//
//        auto index_count() const -> gl::count_t
//        {
//            return indexCount_;
//        }
//
//    private:
//        gl::binding_t bindingPoint_;
//        gl::index_t   attributeIndex_;
//        gl::count_t   indexCount_;
//    };
//}
