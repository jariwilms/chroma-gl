export module opengl.object.vertex_array;

import std;
import opengl;
import opengl.object;
import opengl.object.buffer;

       namespace gl
{
    template<typename T>
    auto map_attribute_type                () -> gl::vertex_array_attribute_type_e
    {
        if constexpr (std::is_same_v<T, gl::int8_t   >) return gl::vertex_array_attribute_type_e::int8   ;
        if constexpr (std::is_same_v<T, gl::int16_t  >) return gl::vertex_array_attribute_type_e::int16  ;
        if constexpr (std::is_same_v<T, gl::int32_t  >) return gl::vertex_array_attribute_type_e::int32  ;
        if constexpr (std::is_same_v<T, gl::uint8_t  >) return gl::vertex_array_attribute_type_e::uint8  ;
        if constexpr (std::is_same_v<T, gl::uint16_t >) return gl::vertex_array_attribute_type_e::uint16 ;
        if constexpr (std::is_same_v<T, gl::uint32_t >) return gl::vertex_array_attribute_type_e::uint32 ;
        if constexpr (std::is_same_v<T, gl::float32_t>) return gl::vertex_array_attribute_type_e::float32;
        if constexpr (std::is_same_v<T, gl::float64_t>) return gl::vertex_array_attribute_type_e::float64;
    }
}
export namespace gl
{
    template<typename T, gl::uint32_t Count, gl::index_t Location = 0u, gl::uint32_t Instancing = 0u> requires (meta::within_closed_interval_v<Count, 1u, 4u>)
    struct vertex_attribute_descriptor
    {
        using type = T;

        constexpr auto size           () const -> gl::size_t
        {
            return sizeof(T);
        }
        constexpr auto count          () const -> gl::count_t
        {
            return Count;
        }
        constexpr auto stride         () const -> gl::size_t
        {
            return size() * count();
        }
        constexpr auto location       () const -> gl::index_t
        {
            return Location;
        }
        constexpr auto instancing_rate() const -> gl::uint32_t
        {
            return Instancing;
        }
    };
    template<typename... T>
    struct vertex_layout
    {
        constexpr auto stride    () const -> gl::size_t
        {
            auto stride = gl::size_t{};
            std::apply([&](const auto&... attribute)
                {
                    ((stride += attribute.stride()), ...);
                }, std::tuple<T...>{});

            return stride;
        }
        constexpr auto attributes() const -> std::tuple<T...>
        {
            return std::tuple<T...>{};
        }
    };

    class vertex_array : public gl::object
    {
    public:
        explicit
        vertex_array()
            : gl::object{ gl::create_vertex_array() }
            , binding_point_{}, attribute_index_{}, index_count_{} {}
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

        template<typename... Attributes>
        void tie(gl::handle_t vertex_buffer, gl::vertex_layout<Attributes...> layout)
        {
            gl::vertex_array_vertex_buffer(handle(), vertex_buffer, binding_point_, layout.stride(), gl::index_t{ 0u });

            auto offset = gl::size_t{};
            std::apply([&](auto... attributes)
                {
                    ([&](auto attribute)
                        {
                            using attribute_t = typename decltype(attribute)::type;

                            enable_attribute(attribute_index_);
                            gl::vertex_array_attribute_format (handle(), attribute_index_, offset, gl::map_attribute_type<attribute_t>(), attribute.count(), gl::false_);
                            gl::vertex_array_attribute_binding(handle(), attribute_index_, binding_point_);
                            gl::vertex_array_binding_divisor  (handle(), static_cast<gl::binding_t>(attribute_index_), attribute.instancing_rate());

                            offset += attribute.stride();
                            ++attribute_index_;
                        } (attributes), ...);
                }, layout.attributes());

            binding_point_ = static_cast<gl::binding_t>(gl::to_underlying(binding_point_) + 1u);
        }
        void tie(gl::handle_t index_buffer , gl::count_t indices                    )
        {
            gl::vertex_array_element_buffer(handle(), index_buffer);
            index_count_ = indices;
        }

        auto index_count() const -> gl::count_t
        {
            return index_count_;
        }

    private:
        gl::binding_t binding_point_;
        gl::index_t   attribute_index_;
        gl::count_t   index_count_;
    };
}
