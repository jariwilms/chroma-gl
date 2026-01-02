export module chroma_gl:object.query;

import std;
import opengl;
import :object;

export namespace gl
{
    template<gl::query_target_e target_v>
    class base_query : public gl::object
    {
    public:
        using target_e = gl::query_target_e;

        base_query(base_query&&) noexcept = default;
       ~base_query()
        {
            gl::delete_query(handle());
        }

        auto is_available() const -> gl::bool_t
        {
            return gl::get_query_object_parameter<gl::query_parameter_e::result_available>(handle());
        }
        auto result      () const -> auto
        {
            return gl::get_query_object_parameter<gl::query_parameter_e::result>(handle());
        }

        auto operator=(base_query&&) noexcept -> base_query & = default;

    protected:
        explicit
        base_query()
            : gl::object{ gl::create_query(target_v) } {}
    };
    template<gl::query_target_e target_v>
    class query : public gl::base_query<target_v>
    {
    public:
        explicit
        query() = default;

        void begin() 
        {
            gl::begin_query(gl::base_query<target_v>::handle(), target_v);
        }
        void end  () 
        {
            gl::end_query(target_v);
        }
    };
    template<>
    class query<gl::query_target_e::timestamp> : public gl::base_query<gl::query_target_e::timestamp>
    {
    public:
        explicit
        query() = default;

        void record()
        {
            gl::query_counter(handle());
        }
    };
}
