export module chroma_gl:object.memory_lock;

import std;
import opengl;
import :object.fence;

export namespace gl
{
    using memory_lock_t = std::tuple<gl::fence, gl::range_t>;
    class memory_locker
    {
    public:
        memory_locker()
            : locks_{} {}

        void lock(gl::range_t range)
        {
            auto& [fence, _] = locks_.emplace_back(gl::fence{}, range);
            fence.place();
        }
        void wait(gl::range_t range)
        {
            auto remaining_locks = std::vector<gl::memory_lock_t>{};
            std::ranges::for_each(locks_, [&](gl::memory_lock_t& lock)
                {
                    auto& [lock_fence, lock_range] = lock;
                    if   (gl::range_overlaps(lock_range, range)) lock_fence     .wait();
                    else                                         remaining_locks.emplace_back(std::move(lock));
                });
            
            locks_ = std::move(remaining_locks);
        }

    private:
        std::vector<gl::memory_lock_t> locks_;
    };
}
