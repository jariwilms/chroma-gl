export module opengl.object.render_buffer;

import std;
import opengl;
import opengl.object;

export namespace gl
{
    class render_buffer : public gl::object
    {
    public:
        using format_e = gl::render_buffer_format_e;

        render_buffer(format_e format, const gl::vector_2u& dimensions)
            : gl::object{ gl::create_render_buffer() }
            , format_{ format }, dimensions_{ dimensions }
        {
            gl::render_buffer_storage(handle(), format_, dimensions_);
        }
        render_buffer(render_buffer&&) noexcept = default;
       ~render_buffer()
        {
            gl::delete_render_buffer(handle());
        }

        auto format    () const -> format_e
        {
            return format_;
        }
        auto dimensions() const -> const gl::vector_2u&
        {
            return dimensions_;
        }

        auto operator=(render_buffer&&) noexcept -> render_buffer& = default;

    private:
        format_e      format_;
        gl::vector_2u dimensions_;
    };
}
