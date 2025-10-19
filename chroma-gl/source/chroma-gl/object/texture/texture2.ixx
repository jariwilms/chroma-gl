//export module opengl.object.texture;
//
//import std;
//import opengl;
//import opengl.object;
//import opengl.object.mapping;
//
//export namespace gl
//{
//    class texture1d : public gl::object
//    {
//    public:
//        using format_e   = gl::texture_format_e;
//        enum class filter_e
//        {
//            none     , 
//            nearest  , 
//            bilinear , 
//            trilinear, 
//        };
//        using wrapping_e = gl::texture_wrapping_e;
//        using wrapping_t = gl::proxy<wrapping_e>;
//
//        texture1d(format_e format, filter_e filter, wrapping_t wrapping, const gl::vector1u& dimensions)
//            : gl::object{ gl::create_texture(gl::texture_target_e::_1d), [](auto* handle) { gl::delete_texture(*handle); } }
//            , format_{ format }, filter_{ filter }, wrapping_{ wrapping }, dimensions_{ dimensions }, mipmap_levels_{ 1u }
//        {
//            auto map_texture_minification_filter = [](filter_e filter) -> gl::texture_minification_filter_e
//                {
//                    switch (filter)
//                    {
//                        using enum filter_e;
//
//                        case none     : return gl::texture_minification_filter_e::nearest               ;
//                        case nearest  : return gl::texture_minification_filter_e::nearest_mipmap_nearest;
//                        case bilinear : return gl::texture_minification_filter_e::linear_mipmap_nearest ;
//                        case trilinear: return gl::texture_minification_filter_e::linear_mipmap_linear  ;
//
//                        default       : throw std::invalid_argument{ "invalid filter" };
//                    }
//                };
//            auto map_texture_magnification_filter = [](filter_e filter) -> gl::texture_magnification_filter_e
//                {
//                    switch (filter)
//                    {
//                        using enum filter_e;
//
//                        case none     : return gl::texture_magnification_filter_e::nearest;
//                        case nearest  : return gl::texture_magnification_filter_e::nearest;
//                        case bilinear : return gl::texture_magnification_filter_e::linear ;
//                        case trilinear: return gl::texture_magnification_filter_e::linear ;
//
//                        default       : throw std::invalid_argument{ "invalid filter" };
//                    }
//                };
//
//            if (filter_ != filter_e::none)
//            {
//                gl::texture_parameter(handle(), glp::magnification_filter{ map_texture_magnification_filter(filter_) });
//                gl::texture_parameter(handle(), glp::minification_filter { map_texture_minification_filter (filter_) });
//                gl::texture_parameter(handle(), glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });
//
//                mipmap_levels_ = gl::mipmap_levels(dimensions_);
//            }
//
//            const auto& [s] = wrapping_.pack;
//            gl::texture_parameter(handle(), glp::wrapping_s{ s });
//
//            gl::texture_storage_1d(handle(), format_, dimensions_, mipmap_levels_);
//        }
//        texture1d(format_e format, filter_e filter, wrapping_t wrapping, const gl::vector1u& dimensions, std::span<const gl::byte_t> data)
//            : texture1d{ format, filter, wrapping, dimensions }
//        {
//            copy(format, data);
//            generate_mipmap();
//        }
//        texture1d(format_e format,                                        const gl::vector1u& dimensions, std::span<const gl::byte_t> data)
//            : texture1d{ format, filter_e::trilinear, wrapping_e::repeat, dimensions, data } {}
//
//        void bind(gl::binding_t binding) const
//        {
//            gl::bind_texture_unit(handle(), binding);
//        }
//
//        void copy      (format_e format,                      std::span<const gl::byte_t> data)
//        {
//            copy_range(format, dimensions_, data);
//        }
//        void copy_range(format_e format, gl::length_t region, std::span<const gl::byte_t> data)
//        {
//            if (data.empty()) return;
//            if (glm::any(glm::greaterThan(region.origin + region.extent, dimensions_))) throw std::out_of_range{ "region exceeds texture bounds" };
//
//            gl::texture_sub_image_1d(handle(), gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
//        }
//
//        void apply_wrapping (wrapping_t wrapping)
//        {
//            wrapping_ = wrapping;
//
//            const auto& [s] = wrapping_.pack;
//            gl::texture_parameter(handle(), glp::wrapping_s{ s });
//        }
//        void generate_mipmap()
//        {
//            if (filter_ != filter_e::none) gl::generate_texture_mipmap(handle());
//        }
//
//        void resize(const gl::vector1u& dimensions)
//        {
//            gl::todo();
//        }
//
//        auto format       () const -> format_e
//        {
//            return format_;
//        }
//        auto filter       () const -> filter_e
//        {
//            return filter_;
//        }
//        auto wrapping     () const -> const std::tuple<wrapping_e>&
//        {
//            return wrapping_.pack;
//        }
//        auto dimensions   () const -> const gl::vector1u&
//        {
//            return dimensions_;
//        }
//        auto mipmap_levels() const -> gl::uint32_t
//        {
//            return mipmap_levels_;
//        }
//
//    private:
//        format_e     format_;
//        filter_e     filter_;
//        wrapping_t   wrapping_;
//        gl::vector1u dimensions_;
//        gl::uint32_t mipmap_levels_;
//    };
//    //class texture2d : public gl::object
//    //{
//    //public:
//    //    using format_e   = gl::texture_format_e;
//    //    using filter_e   = gl::texture_filter_e;
//    //    using wrapping_e = gl::texture_wrapping_e;
//    //    using wrapping_t = gl::proxy<wrapping_e, wrapping_e>;
//    //     
//    //    texture2d(format_e format, filter_e filter, wrapping_t wrapping, const gl::vector2u& dimensions)
//    //        : gl::object{ gl::create_texture(gl::texture_target_e::_2d), [](auto* handle) { gl::delete_texture(*handle); } }
//    //        , format_{ format }, filter_{ filter }, wrapping_{ wrapping }, dimensions_{ dimensions }, mipmap_levels_{ 1u }
//    //    {
//    //        if (filter_ != filter_e::none)
//    //        {
//    //            gl::texture_parameter(handle(), glp::magnification_filter{ gl::map_texture_magnification_filter(filter_) });
//    //            gl::texture_parameter(handle(), glp::minification_filter { gl::map_texture_minification_filter (filter_) });
//    //            gl::texture_parameter(handle(), glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });
//
//    //            mipmap_levels_ = gl::mipmap_levels(dimensions_);
//    //        }
//
//    //        const auto& [s, t] = wrapping_.pack;
//    //        gl::texture_parameter(handle(), glp::wrapping_s{ s });
//    //        gl::texture_parameter(handle(), glp::wrapping_t{ t });
//
//    //        gl::texture_storage_2d(handle(), format_, dimensions_, mipmap_levels_);
//    //    }
//    //    texture2d(format_e format, filter_e filter, wrapping_t wrapping, const gl::vector2u& dimensions, std::span<const gl::byte_t> data)
//    //        : texture2d{ format, filter, wrapping, dimensions }
//    //    {
//    //        copy(format, data);
//    //        generate_mipmap();
//    //    }
//    //    texture2d(format_e format,                                       const gl::vector2u& dimensions, std::span<const gl::byte_t> data)
//    //        : texture2d{ format, filter_e::trilinear, wrapping_e::repeat, dimensions, data } {}
//
//    //    void bind(gl::binding_t binding) const
//    //    {
//    //        gl::bind_texture_unit(handle(), binding);
//    //    }
//
//    //    void copy      (format_e format,                    std::span<const gl::byte_t> data)
//    //    {
//    //        copy_range(format, dimensions_, data);
//    //    }
//    //    void copy_range(format_e format, gl::area_t region, std::span<const gl::byte_t> data)
//    //    {
//    //        if (data.empty()) return;
//    //        if (glm::any(glm::greaterThan(region.origin + region.extent, dimensions_))) throw std::out_of_range{ "region exceeds texture bounds" };
//    //        
//    //        gl::texture_sub_image_2d(handle(), gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
//    //    }
//
//    //    void apply_wrapping (wrapping_t wrapping)
//    //    {
//    //        wrapping_ = wrapping;
//
//    //        const auto& [s, t] = wrapping_.pack;
//    //        gl::texture_parameter(handle(), glp::wrapping_s{ s });
//    //        gl::texture_parameter(handle(), glp::wrapping_t{ t });
//    //    }
//    //    void generate_mipmap()
//    //    {
//    //        if (filter_ != filter_e::none) gl::generate_texture_mipmap(handle());
//    //    }
//
//    //    void resize(const gl::vector2u& dimensions)
//    //    {
//    //        gl::todo();
//    //        if (dimensions != dimensions_) gl::texture2d::operator=(gl::texture2d{ format_, filter_, wrapping_, dimensions });
//    //    }
//
//    //    auto format       () const -> format_e
//    //    {
//    //        return format_;
//    //    }
//    //    auto filter       () const -> filter_e
//    //    {
//    //        return filter_;
//    //    }
//    //    auto wrapping     () const -> const std::tuple<wrapping_e, wrapping_e>&
//    //    {
//    //        return wrapping_.pack;
//    //    }
//    //    auto dimensions   () const -> const gl::vector2u&
//    //    {
//    //        return dimensions_;
//    //    }
//    //    auto mipmap_levels() const -> gl::uint32_t
//    //    {
//    //        return mipmap_levels_;
//    //    }
//
//    //private:
//    //    format_e     format_;
//    //    filter_e     filter_;
//    //    wrapping_t   wrapping_;
//    //    gl::vector2u dimensions_;
//    //    gl::uint32_t mipmap_levels_;
//    //};
//    //class texture3d : public gl::object
//    //{
//    //public:
//    //    using format_e   = gl::texture_format_e;
//    //    using filter_e   = gl::texture_filter_e;
//    //    using wrapping_e = gl::texture_wrapping_e;
//    //    using wrapping_t = gl::proxy<wrapping_e, wrapping_e, wrapping_e>;
//
//    //    texture3d(format_e format, filter_e filter, wrapping_t wrapping, const gl::vector3u& dimensions)
//    //        : gl::object{ gl::create_texture(gl::texture_target_e::_3d), [](auto* handle) { gl::delete_texture(*handle); } }
//    //        , format_{ format }, filter_{ filter }, wrapping_{ wrapping }, dimensions_{ dimensions }, mipmap_levels_{ 1u }
//    //    {
//    //        if (filter_ != filter_e::none)
//    //        {
//    //            gl::texture_parameter(handle(), glp::magnification_filter{ gl::map_texture_magnification_filter(filter_) });
//    //            gl::texture_parameter(handle(), glp::minification_filter { gl::map_texture_minification_filter(filter_) });
//    //            gl::texture_parameter(handle(), glp::maximum_anisotropy  { gl::float32_t{ 1.0f } });
//
//    //            mipmap_levels_ = gl::mipmap_levels(dimensions_);
//    //        }
//
//    //        const auto& [s, t, r] = wrapping_.pack;
//    //        gl::texture_parameter(handle(), glp::wrapping_s{ s });
//    //        gl::texture_parameter(handle(), glp::wrapping_t{ t });
//    //        gl::texture_parameter(handle(), glp::wrapping_r{ r });
//
//    //        gl::texture_storage_3d(handle(), format_, dimensions_, mipmap_levels_);
//    //    }
//    //    texture3d(format_e format, filter_e filter, wrapping_t wrapping, const gl::vector3u& dimensions, std::span<const gl::byte_t> data)
//    //        : texture3d{ format, filter, wrapping, dimensions }
//    //    {
//    //        copy(format, data);
//    //        generate_mipmap();
//    //    }
//    //    texture3d(format_e format,                                       const gl::vector3u& dimensions, std::span<const gl::byte_t> data)
//    //        : texture3d{ format, filter_e::trilinear, wrapping_e::repeat, dimensions, data } {}
//
//    //    void bind(gl::binding_t binding) const
//    //    {
//    //        gl::bind_texture_unit(handle(), binding);
//    //    }
//
//    //    void copy      (format_e format,                      std::span<const gl::byte_t> data)
//    //    {
//    //        copy_range(format, dimensions_, data);
//    //    }
//    //    void copy_range(format_e format, gl::volume_t region, std::span<const gl::byte_t> data)
//    //    {
//    //        if (data.empty()) return;
//    //        if (glm::any(glm::greaterThan(region.origin + region.extent, dimensions_))) throw std::out_of_range{ "region exceeds texture bounds" };
//
//    //        gl::texture_sub_image_3d(handle(), gl::map_texture_format_base(format), gl::map_texture_format_type(format), gl::uint32_t{ 0u }, region, data);
//    //    }
//
//    //    void apply_wrapping (wrapping_t wrapping)
//    //    {
//    //        wrapping_ = wrapping;
//
//    //        const auto& [s, t, r] = wrapping_.pack;
//    //        gl::texture_parameter(handle(), glp::wrapping_s{ s });
//    //        gl::texture_parameter(handle(), glp::wrapping_t{ t });
//    //        gl::texture_parameter(handle(), glp::wrapping_r{ r });
//    //    }
//    //    void generate_mipmap()
//    //    {
//    //        if (filter_ != filter_e::none) gl::generate_texture_mipmap(handle());
//    //    }
//
//    //    void resize(const gl::vector3u& dimensions)
//    //    {
//    //        gl::todo();
//    //    }
//
//    //    auto format       () const -> format_e
//    //    {
//    //        return format_;
//    //    }
//    //    auto filter       () const -> filter_e
//    //    {
//    //        return filter_;
//    //    }
//    //    auto wrapping     () const -> const std::tuple<wrapping_e, wrapping_e, wrapping_e>&
//    //    {
//    //        return wrapping_.pack;
//    //    }
//    //    auto dimensions   () const -> const gl::vector3u&
//    //    {
//    //        return dimensions_;
//    //    }
//    //    auto mipmap_levels() const -> gl::uint32_t
//    //    {
//    //        return mipmap_levels_;
//    //    }
//
//    //private:
//    //    format_e     format_;
//    //    filter_e     filter_;
//    //    wrapping_t   wrapping_;
//    //    gl::vector3u dimensions_;
//    //    gl::uint32_t mipmap_levels_;
//    //};
//
//    //class texture2d_ms : public gl::object
//    //{
//    //public:
//    //    using format_e = api::texture::format_e;
//
//    //    texture2d_ms(format_e format, const gl::vector2u& dimensions, gl::uint32_t samples)
//    //        : gl::object{ gl::create_texture(gl::texture_target_e::_2d_multisample), [](auto* handle) { gl::delete_texture(*handle); } }
//    //        , format_{ format }, dimensions_{ dimensions }, samples_{ samples }
//    //    {
//    //         gl::texture_storage_2d_multisample(handle(), gl::map_texture_format(format_), dimensions_, samples_);
//    //    }
//
//    //    void bind(gl::binding_t binding) const
//    //    {
//    //        gl::bind_texture_unit(handle(), binding);
//    //    }
//    //    
//    //    void resize(const gl::vector2u& dimensions)
//    //    {
//    //        gl::todo();
//    //    }
//
//    //    auto format    () const -> format_e
//    //    {
//    //        return format_;
//    //    }
//    //    auto dimensions() const -> const gl::vector2u&
//    //    {
//    //        return dimensions_;
//    //    }
//    //    auto samples   () const -> gl::uint32_t
//    //    {
//    //        return samples_;
//    //    }
//
//    //private:
//    //    format_e     format_;
//    //    gl::vector2u dimensions_;
//    //    gl::uint32_t samples_;
//    //};
//    //class texture3d_ms : public gl::object
//    //{
//    //public:
//    //    using format_e = api::texture::format_e;
//
//    //    texture3d_ms(format_e format, const gl::vector3u& dimensions, gl::uint32_t samples)
//    //        : gl::object{ gl::create_texture(gl::texture_target_e::_2d_multisample_array), [](auto* handle) { gl::delete_texture(*handle); } }
//    //        , format_{ format }, dimensions_{ dimensions }, samples_{ samples }
//    //    {
//    //         gl::texture_storage_3d_multisample(handle(), gl::map_texture_format(format_), dimensions_, samples_);
//    //    }
//
//    //    void bind(gl::binding_t binding) const
//    //    {
//    //        gl::bind_texture_unit(handle(), binding);
//    //    }
//
//    //    void resize(const gl::vector3u& dimensions)
//    //    {
//    //        gl::todo();
//    //    }
//
//    //    auto format    () const -> format_e
//    //    {
//    //        return format_;
//    //    }
//    //    auto dimensions() const -> const gl::vector3u&
//    //    {
//    //        return dimensions_;
//    //    }
//    //    auto samples   () const -> gl::uint32_t
//    //    {
//    //        return samples_;
//    //    }
//
//    //private:
//    //    format_e     format_;
//    //    gl::vector3u dimensions_;
//    //    gl::uint32_t samples_;
//    //};
//}
