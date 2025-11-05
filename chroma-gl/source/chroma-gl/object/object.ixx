export module opengl.object;

import std;
import opengl;

export namespace gl
{
    class object
    {
    public:
        auto handle() -> gl::handle_t
        {
            return handle_;
        }

    protected:
        explicit 
        object(gl::handle_t handle)
            : handle_{ handle } {}
        explicit 
        object(object&& other) noexcept
            : handle_{ std::exchange(other.handle_ , gl::null_object) } {}

        auto handle() const -> gl::handle_t
        {
            return handle_;
        }

        auto operator=(object&& other) noexcept -> object&
        {
            if (this != &other) handle_ = std::exchange(other.handle_, handle_);

            return *this;
        }

    private:
        gl::handle_t handle_;
    };
}
