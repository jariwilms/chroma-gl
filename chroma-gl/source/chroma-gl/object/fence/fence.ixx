export module opengl.object.fence;

import std;
import opengl;

export namespace gl
{
    class fence
    {
    public:
        explicit 
        fence() 
            : sync_{} {}
        fence(fence&& other) noexcept
            : sync_{ std::exchange(other.sync_, gl::sync_t{}) } {}
       ~fence() 
        {
            gl::delete_sync(sync_);
        }

        void place    ()
        {
            if (!sync_) sync_ = gl::fence_sync();
        }
        void wait     (gl::bool_t client_side = gl::true_)
        {
            if (client_side)
            {
                      auto status  = gl::client_wait_sync(sync_, gl::synchronization_command_e{}, gl::time_t{ 0u });
                const auto timeout = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count();
                while (status == gl::synchronization_status_e::timeout_expired)
                {
                    status = gl::client_wait_sync(sync_, gl::synchronization_command_e::flush, timeout);
                }

                if (status == gl::synchronization_status_e::wait_failed) throw std::runtime_error{ "sync wait failed" };
            }
            else
            {
                gl::server_wait_sync(sync_);
            }
        }

        auto operator=(fence&& other) noexcept -> fence&
        {
            if (this != &other) sync_ = std::exchange(other.sync_, sync_);

            return *this;
        }

    private:
        gl::sync_t sync_;
    };
}
