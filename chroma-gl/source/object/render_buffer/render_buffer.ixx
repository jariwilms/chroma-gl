export module chroma_gl:object.render_buffer;

import std;
import opengl;
import :object;

export namespace gl
{
    class render_buffer : public gl::object
    {
    public:
        using format_e = gl::render_buffer_format_e;

        explicit
        render_buffer(format_e format, gl::vector_2u dimensions)
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
        auto dimensions() const -> gl::vector_2u
        {
            return dimensions_;
        }

        auto operator=(render_buffer&&) noexcept -> render_buffer& = default;

    private:
        format_e      format_;
        gl::vector_2u dimensions_;
    };
    class multisample_render_buffer : public gl::object
    {
    public:
        using format_e = gl::render_buffer_format_e;

        explicit
        multisample_render_buffer(format_e format, gl::vector_2u dimensions, gl::uint32_t sample_count)
            : gl::object{ gl::create_render_buffer() }
            , format_{ format }, dimensions_{ dimensions }, sample_count_{ sample_count }
        {
            gl::render_buffer_storage_multisample(handle(), format_, dimensions_, sample_count_);
        }
        multisample_render_buffer(multisample_render_buffer&&) noexcept = default;
       ~multisample_render_buffer()
        {
            gl::delete_render_buffer(handle());
        }

        auto format      () const -> format_e
        {
            return format_;
        }
        auto dimensions  () const -> gl::vector_2u
        {
            return dimensions_;
        }
        auto sample_count() const -> gl::uint32_t
        {
            return sample_count_;
        }

        auto operator=(multisample_render_buffer&&) noexcept -> multisample_render_buffer& = default;

    private:
        format_e      format_;
        gl::vector_2u dimensions_;
        gl::uint32_t  sample_count_;
    };
}
