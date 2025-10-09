export module opengl.object.vertex_array;
//
//import std;
//import opengl;
//import opengl.object;
//import opengl.object.buffer;
//import opengl.object.mapping;
//
//export namespace gl
//{
//    template<typename T, gl::uint32_t N, gl::index_t L = 0u, gl::uint32_t I = 0u> requires (meta::within_closed_interval_v<N, 1u, 4u>)
//    struct vertex_attribute_descriptor
//    {
//        using type = T;
//
//        constexpr auto size           () const -> gl::size_t
//        {
//            return sizeof(T);
//        }
//        constexpr auto count          () const -> gl::uint32_t
//        {
//            return N;
//        }
//        constexpr auto stride         () const -> gl::size_t
//        {
//            return size() * count();
//        }
//        constexpr auto location       () const -> gl::index_t
//        {
//            return L;
//        }
//        constexpr auto instancing_rate() const -> gl::uint32_t const
//        {
//            return I;
//        }
//    };
//    template<typename... T>
//    struct vertex_layout
//    {
//        constexpr auto stride    () const -> gl::size_t
//        {
//            auto stride = gl::size_t{};
//            std::apply([&](const auto&... attribute)
//                {
//                    ((stride += attribute.stride()), ...);
//                }, std::tuple<T...>{});
//
//            return stride;
//        }
//        constexpr auto attributes() const -> std::tuple<T...>
//        {
//            return std::tuple<T...>{};
//        }
//    };
//
//    class vertex_array : public gl::object
//    {
//    public:
//        vertex_array()
//            : gl::object{ gl::create_vertex_array(), [](auto* handle) { gl::delete_vertex_array(*handle); } }
//            , attribute_index_{}, binding_point_{}, index_count_{} {}
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
//        template<typename... Attributes>
//        void tie(gl::handle_t vertexbuffer, gl::vertex_layout<Attributes...> layout)
//        {
//            gl::vertex_array_vertex_buffer(handle(), vertexbuffer, binding_point_, static_cast<gl::size_t>(layout.stride()), gl::index_t{ 0u });
//
//            auto offset = gl::offset_t{};
//            std::apply([&](auto... attributes)
//                {
//                    ([&](auto attribute)
//                        {
//                            enable_attribute(attribute_index_);
//
//                            gl::vertex_array_attribute_format (handle(), attribute_index_, offset, gl::map_attribute_type<typename decltype(attribute)::type>(), attribute.count(), gl::false_);
//                            gl::vertex_array_attribute_binding(handle(), attribute_index_, binding_point_);
//                            gl::vertex_array_binding_divisor  (handle(), gl::binding_t{ attribute_index_ }, attribute.instancing_rate());
//
//                            offset += static_cast<gl::offset_t>(attribute.stride());
//                            ++attribute_index_;
//                        } (attributes), ...);
//                }, layout.attributes());
//
//            binding_point_ = gl::binding_t{ gl::to_underlying(binding_point_) + 1u };
//        }
//        void tie(gl::handle_t indexbuffer , gl::count_t indices                )
//        {
//            gl::vertex_array_element_buffer(handle(), indexbuffer);
//            index_count_ = indices;
//        }
//
//        auto index_count() const -> gl::count_t
//        {
//            return index_count_;
//        }
//
//    private:
//        gl::binding_t binding_point_;
//        gl::index_t   attribute_index_;
//        gl::count_t   index_count_;
//    };
//}
