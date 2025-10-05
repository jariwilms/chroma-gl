export module opengl.object;

import std;
import opengl;

export namespace gl
{
    class object
    {
    protected:
        explicit object(gl::handle_t handle)
            : handle_{ handle }, deleter_{} {}
        template<typename Dx>
        explicit object(gl::handle_t handle, Dx deleter)
            : handle_{ handle }, deleter_{ &handle_, std::move(deleter) } {}
        explicit object(object&& other) noexcept
            : handle_ { std::exchange(other.handle_ , gl::null_object) }
            , deleter_{ std::exchange(other.deleter_, {}             ) } {}

        auto handle() -> gl::handle_t
        {
            return handle_;
        }

        auto operator=(object&& other) noexcept -> object&
        {
            if (this != &other) handle_ = std::exchange(other.handle_, handle_);
            
            return *this;
        }

    private:
        gl::handle_t                  handle_;
        std::shared_ptr<gl::handle_t> deleter_;
    };
}
