export module opengl.object.fence;

import std;
import opengl;

export namespace gl
{
    class fence
    {
    public:
        explicit fence() 
        { 
            sync_ = gl::fence_sync(); 
        }
                 fence(fence&& other) noexcept
        {
            sync_ = std::exchange(other.sync_, gl::sync_t{});
        }
                ~fence() 
        { 
            gl::delete_sync(sync_);
        }

             operator  gl::sync_t()
        {
            return sync_;
        }
        auto operator=           (fence&& other) noexcept -> fence&
        {
            if (this != &other) sync_ = std::exchange(other.sync_, sync_);

            return *this;
        }

    private:
        gl::sync_t sync_;
    };
}
