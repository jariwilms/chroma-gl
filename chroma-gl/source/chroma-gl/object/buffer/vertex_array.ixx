export module opengl.object.vertex_array;

import std;
import opengl;
import opengl.object.buffer;

export namespace gl::meta //TODO, remove
{
    template<typename T, typename... Ts>
    constexpr auto all_same_type_v = static_cast<gl::bool_t>(std::conjunction_v<std::is_same<T, Ts>...>);
    
    template<auto value, auto min, auto max>
    constexpr auto within_open_interval_v   = value >  min && value <  max;
    template<auto value, auto min, auto max>
    constexpr auto within_closed_interval_v = value >= min && value <= max;

    template<typename T>
    constexpr auto map_type() -> gl::vertex_array_attribute_type_e
    {
        if constexpr (std::is_same_v<T, gl::int8_t   >) return gl::vertex_array_attribute_type_e::int8_t   ;          
        if constexpr (std::is_same_v<T, gl::uint8_t  >) return gl::vertex_array_attribute_type_e::uint8_t  ;  
        if constexpr (std::is_same_v<T, gl::int16_t  >) return gl::vertex_array_attribute_type_e::int16_t  ;         
        if constexpr (std::is_same_v<T, gl::uint16_t >) return gl::vertex_array_attribute_type_e::uint16_t ;  
        if constexpr (std::is_same_v<T, gl::int32_t  >) return gl::vertex_array_attribute_type_e::int32_t  ;        
        if constexpr (std::is_same_v<T, gl::uint32_t >) return gl::vertex_array_attribute_type_e::uint32_t ;
        if constexpr (std::is_same_v<T, gl::float32_t>) return gl::vertex_array_attribute_type_e::float32_t; ;
        if constexpr (std::is_same_v<T, gl::float64_t>) return gl::vertex_array_attribute_type_e::float64_t;        
    }
}
export namespace gl
{
    template<typename T, gl::uint32_t N, gl::index_t L = 0u, gl::uint32_t I = 0u> requires (meta::within_closed_interval_v<N, 1u, 4u>)
    struct vertex_attribute_descriptor
    {
        using type = T;

        constexpr auto size           () const -> gl::size_t
        {
            return sizeof(T);
        }
        constexpr auto count          () const -> gl::uint32_t
        {
            return N;
        }
        constexpr auto stride         () const -> gl::size_t
        {
            return size() * count();
        }
        constexpr auto location       () const -> gl::index_t
        {
            return L;
        }
        constexpr auto instancing_rate() const -> gl::uint32_t const
        {
            return I;
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
        vertex_array()
            : gl::object{ gl::create_vertex_array(), [](auto* handle) { gl::delete_vertex_array(*handle); } }
            , attribute_index_{}, binding_point_{}, index_count_{} {}

        void bind() const
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
        void tie(gl::handle_t vertexbuffer, gl::vertex_layout<Attributes...> layout)
        {
            gl::vertex_array_vertex_buffer(handle(), vertexbuffer, binding_point_, static_cast<gl::size_t>(layout.stride()), gl::index_t{ 0u });

            auto offset = gl::offset_t{};
            std::apply([&](auto... attributes)
                {
                    ([&](auto attribute)
                        {
                            enable_attribute(attribute_index_);

                            gl::vertex_array_attribute_format (handle(), attribute_index_, offset, meta::map_type<typename decltype(attribute)::type>(), attribute.count(), gl::false_);
                            gl::vertex_array_attribute_binding(handle(), attribute_index_, binding_point_);
                            gl::vertex_array_binding_divisor  (handle(), gl::binding_t{ attribute_index_ }, attribute.instancing_rate());

                            offset += static_cast<gl::offset_t>(attribute.stride());
                            ++attribute_index_;
                        } (attributes), ...);
                }, layout.attributes());

            binding_point_ = gl::binding_t{ gl::to_underlying(binding_point_) + 1u };
        }
        void tie(gl::handle_t indexbuffer , gl::count_t indices                )
        {
            gl::vertex_array_element_buffer(handle(), indexbuffer);
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
