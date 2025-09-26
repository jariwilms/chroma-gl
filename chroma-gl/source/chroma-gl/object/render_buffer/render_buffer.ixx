//export module fox.rendering.api.opengl.render_buffer;
//
//import std;
//import fox.rendering.api.opengl;
//import fox.rendering.base.render_buffer;
//
//export namespace fox::gfx::api::gl
//{
//    class render_buffer : public gl::object
//    {
//    public:
//        using format_e = api::render_buffer::format_e;
//
//        render_buffer(format_e format, const gl::vector2u& dimensions)
//            : gl::object{ gl::create_render_buffer(), [](auto* handle) { gl::delete_render_buffer(*handle); }}
//            , format_{ format }, dimensions_{ dimensions }
//        {
//            gl::render_buffer_storage(handle(), gl::map_render_buffer_format(format), dimensions_);
//        }
//
//        void resize(const gl::vector2u& dimensions)
//        {
//            if (dimensions != dimensions_) gl::render_buffer::operator=(render_buffer{ format_, dimensions });
//        }
//
//        auto format    () const -> format_e
//        {
//            return format_;
//        }
//        auto dimensions() const -> const gl::vector2u&
//        {
//            return dimensions_;
//        }
//
//    private:
//        format_e     format_;
//        gl::vector2u dimensions_;
//    };
//    class render_buffer_ms : public gl::object
//    {
//    public:
//        using format_e = api::render_buffer::format_e;
//
//        render_buffer_ms(format_e format, const gl::vector2u& dimensions, gl::uint32_t samples)
//            : gl::object{ gl::create_render_buffer(), [](auto* handle) { gl::delete_render_buffer(*handle); }}
//            , format_{ format }, dimensions_{ dimensions }, samples_{ samples }
//        {
//            gl::render_buffer_storage_multisample(handle(), gl::map_render_buffer_format(format), dimensions_, samples_);
//        }
//
//        void resize(const gl::vector2u& dimensions)
//        {
//            if (dimensions != dimensions_) gl::render_buffer_ms::operator=(render_buffer_ms{ format_, dimensions, samples_ });
//        }
//
//        auto format    () const -> format_e
//        {
//            return format_;
//        }
//        auto dimensions() const -> const gl::vector2u&
//        {
//            return dimensions_;
//        }
//        auto samples   () const -> gl::uint32_t
//        {
//            return samples_;
//        }
//
//    private:
//        format_e     format_;
//        gl::vector2u dimensions_;
//        gl::uint32_t samples_;
//    };
//}
