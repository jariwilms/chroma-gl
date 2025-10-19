export module opengl.object.query;

import std;
import opengl;
import opengl.object;
import opengl.context.state;

export namespace gl
{
    class query : public gl::object
    {
    public:
        using target_e = gl::query_target_e;
        
        explicit 
        query(target_e target)
            : gl::object{ gl::create_query(target) }
            , target_   { target                   } {}
        query(query&&) noexcept = default;
       ~query()
        {
            gl::delete_query(handle());
        }
        
        void begin    ()
        {
            if (gl::query_target_state.at(target_)) throw std::runtime_error{ "target query already in progress" };

            gl::begin_query(handle(), target_);
            gl::query_target_state.at(target_) = gl::true_;
        }
        void end      ()
        {
            if (!gl::query_target_state.at(target_)) throw std::runtime_error{ "target query not in progress" };

            gl::end_query(target_);
            gl::query_target_state.at(target_) = gl::false_;
        }
        
        auto available() const -> gl::bool_t
        {
            return gl::get_query_object_value<gl::query_parameter_e::result_available>(handle());
        }
        auto result   () const -> gl::uint32_t
        {
            return gl::get_query_object_value<gl::query_parameter_e::result>(handle());
        }

        auto target   () const -> target_e
        {
            return target_;
        }

        auto operator=(query&&) noexcept -> query& = default;

    private:
        target_e target_;
    };
}
