export module chroma_gl:object.fence;

import std;
import opengl;

export namespace gl
{
    class fence
    {
    public:
        explicit 
        fence() 
            : sync_{ nullptr } {}
        fence(fence&& object) noexcept
            : sync_{ std::exchange(object.sync_, gl::sync_t{}) } {}
       ~fence() 
        {
            gl::delete_sync(sync_);
        }

        void place    ()
        {
            if (!sync_) sync_ = gl::fence_sync();
        }
        void wait     ()
        {
            auto       status  = gl::client_wait_sync(sync_, gl::synchronization_command_e::flush, gl::time_t{ 0u });
            auto const timeout = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count();
            while (status == gl::synchronization_status_e::timeout_expired)
            {
                status = gl::client_wait_sync(sync_, gl::synchronization_command_e::flush, timeout);
            }

            if (status == gl::synchronization_status_e::wait_failed) throw std::runtime_error{ "sync wait failed" };

            gl::delete_sync(sync_);
        }

        auto operator=(fence&& object) noexcept -> fence&
        {
            if (this != &object) sync_ = std::exchange(object.sync_, sync_);

            return *this;
        }

    private:
        gl::sync_t sync_;
    };
}
