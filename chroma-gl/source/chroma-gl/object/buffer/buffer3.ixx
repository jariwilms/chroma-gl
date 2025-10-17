export module buffer3;

import std;
import opengl;
import opengl.object;
import opengl.object.fence;
import opengl.object.memory_lock;

export namespace gl3
{
    template<typename T>
    struct mapping
    {
        std::span<T> memory;
        gl::range    range;
    };
    template<typename T>
    class memory_mapper : private gl3::mapping<T>
    {
    public:
        memory_mapper(gl::buffer_mapping_range_access_flags_e buffer_mapping_range_access_flags)
        {

        }

        void map         ()
        {
            //map(buffer_.count());
        }
        void map         (gl::range range)
        {
            //if (range = gl::clamp_range(range, count()); range != mapped_range_ && range.count > gl::count_t{ 0u })
            //{
            //    unmap();

            //    //memory = gl::map_buffer_range<T>(handle(), access_flags, range);
            //    //this->range  = range;
            //}
        }
        void unmap       ()
        {
            //if ( mapping_.memory.empty()           ) return;
            //if (!gl::unmap_buffer(buffer_.handle())) throw std::runtime_error{ "data store may be corrupt" };

            //memory = {};
            //range  = {};
        }

    private:
        //gl3::buffer & buffer_;
        //gl3::mapping& mapping_;
        //gl::buffer_mapping_range_access_flags_e buffer_mapping_range_access_flags_;
    };
    class memory_locker
    {
    public:
        void lock          (gl::range range)
        {
            locks_.emplace_back(gl::fence{}, range);
        }
        void wait          (gl::range range)
        {
            auto remaining_locks = std::vector<gl::memory_lock_t>{};
            std::ranges::for_each(locks_, [&](gl::memory_lock_t& lock)
                {
                    auto& [lock_fence, lock_range] = lock;
                    if   (gl::range_overlaps(lock_range, range)) wait_for_fence(lock_fence);
                    else                                         remaining_locks.emplace_back(std::move(lock));
                });

            locks_ = std::move(remaining_locks);
        }

    private:
        void wait_for_fence(gl::fence& fence)
        {
            auto status  = gl::synchronization_status_e::timeout_expired;
            auto timeout = gl::time_t{ 0u };

            while (status == gl::synchronization_status_e::timeout_expired)
            {
                status  = gl::client_wait_sync(fence, gl::synchronization_command_e::flush, timeout);
                timeout = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count();

                if (status == gl::synchronization_status_e::wait_failed) throw std::runtime_error{ "sync wait failed" };
            }
        }

        std::vector<gl::memory_lock_t> locks_;
    };
    
    

    class buffer : public gl::object
    {
    public:
        buffer(buffer&& other) = default;
       ~buffer()
        {
            gl::delete_buffer(handle());
        }

        auto count() const -> gl::count_t
        {
            return element_count_;
        }
        auto size() const -> gl::size_t
        {
            return element_count_ * element_size_;
        }

        auto operator=(buffer&&) -> buffer & = default;

    protected:
        buffer(gl::count_t element_count, gl::size_t element_size)
            : gl::object{ gl::create_buffer() }
            , element_count_{ element_count }, element_size_{ element_size } {}

    private:
        gl::count_t element_count_;
        gl::size_t  element_size_;
    };
    template<typename T>
    class static_buffer : public gl3::buffer
    {
    public:
        static_buffer(std::span<const T> source)
            : gl3::buffer{ static_cast<gl::count_t>(source.size()), sizeof(T) }
        {
            gl::buffer_storage(handle(), gl::buffer_storage_flags_e::static_, source);
        }
    };
    template<typename T, gl::bool_t Read, gl::bool_t Write>
    class dynamic_buffer : public gl3::buffer
    {
    public:
        dynamic_buffer(gl::count_t element_count)
            : gl3::buffer{ element_count, sizeof(T) }
        {
            auto buffer_storage_flags = gl::buffer_storage_flags_e{};
            if constexpr (Read ) buffer_storage_flags |= gl::buffer_storage_flags_e::read;
            if constexpr (Write) buffer_storage_flags |= gl::buffer_storage_flags_e::write;

            gl::buffer_storage<T>(handle(), buffer_storage_flags, element_count);
        }

        void read (std::span<T> memory, gl::index_t offset = 0u) requires (Read )
        {
            const auto read_range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(memory.size()), offset }, count());
            if (read_range.empty()) return;

            mapping_.memory = gl::map_buffer_range<T>(handle(), gl::buffer_mapping_range_access_flags_e::read, read_range);
            memory_locker_.wait(read_range);
            std::memcpy(memory.data(), mapping_.memory.data(), read_range.count * sizeof(T));
            memory_locker_.lock(read_range);
            gl::unmap_buffer(handle());
        }
        void write(std::span<T> memory, gl::index_t offset = 0u) requires (Write)
        {
            const auto write_range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(memory.size()), offset }, count());
            if (write_range.empty()) return;

            mapping_.memory = gl::map_buffer_range<T>(handle(), gl::buffer_mapping_range_access_flags_e::write, count());
            memory_locker_.wait(write_range);
            std::memcpy(mapping_.memory.data(), memory.data(), write_range.count * sizeof(T));
            memory_locker_.lock(write_range);
            gl::unmap_buffer(handle());
        }

    private:
        gl3::mapping<T>    mapping_;
        gl3::memory_locker memory_locker_;
    };
    template<typename T, gl::bool_t Read, gl::bool_t Write>
    class persistent_buffer : public gl3::buffer
    {
    public:
        persistent_buffer(gl::count_t element_count)
            : gl3::buffer{ element_count, sizeof(T) }
        {
            auto buffer_storage_flags      = gl::buffer_storage_flags_e::persistent | gl::buffer_storage_flags_e::coherent;
            if constexpr (Read ) buffer_storage_flags |= gl::buffer_storage_flags_e::read;
            if constexpr (Write) buffer_storage_flags |= gl::buffer_storage_flags_e::write;

            auto buffer_range_access_flags = gl::buffer_mapping_range_access_flags_e::persistent | gl::buffer_mapping_range_access_flags_e::coherent;
            if constexpr (Read ) buffer_range_access_flags |= gl::buffer_mapping_range_access_flags_e::read;
            if constexpr (Write) buffer_range_access_flags |= gl::buffer_mapping_range_access_flags_e::write;

                              gl::buffer_storage  <T>(handle(), buffer_storage_flags     , element_count);
            mapping_.memory = gl::map_buffer_range<T>(handle(), buffer_range_access_flags, count()      );
        }
       ~persistent_buffer()
        {
            gl::unmap_buffer(handle());
        }

        void read (std::span<T> memory, gl::index_t offset = 0u) requires (Read )
        {
            const auto read_range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(memory.size()), offset }, count());
            if (read_range.empty()) return;

            memory_locker_.wait(read_range);
            std::memcpy(memory.data(), mapping_.memory.data(), read_range.count * sizeof(T));
            memory_locker_.lock(read_range);
        }
        void write(std::span<T> memory, gl::index_t offset = 0u) requires (Write)
        {
            const auto write_range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(memory.size()), offset }, count());
            if (write_range.empty()) return;

            memory_locker_.wait(write_range);
            std::memcpy(mapping_.memory.data(), memory.data(), write_range.count * sizeof(T));
            memory_locker_.lock(write_range);
        }

    private:
        gl3::mapping<T>    mapping_;
        gl3::memory_locker memory_locker_;
    };
    template<typename T, gl::bool_t Read, gl::bool_t Write>
    class partition_buffer : private gl3::dynamic_buffer<T, Read, Write>
    {
    public:
        partition_buffer(gl::count_t partition_count, gl::count_t partition_element_count)
            : gl3::dynamic_buffer<T, Read, Write>{ partition_count * partition_element_count }
            , partition_index_{ 0u }, partition_count_{ partition_count }, partition_element_count_{ partition_element_count } {}

        void read_next (std::span<const T> memory, gl::index_t offset) requires (Read )
        {
            const auto partition_offset = partition_index_ * partition_element_count_;
            read(memory, partition_offset + offset);
            
            to_next_partition();
        }
        void write_next(std::span<const T> memory, gl::index_t offset) requires (Write)
        {
            const auto partition_offset = partition_index_ * partition_element_count_;
            write(memory, partition_offset + offset);
            
            to_next_partition();
        }

    private:
        void to_next_partition()
        {
            ++partition_index_ %= partition_count_;
        }
        
        gl::count_t partition_index_;
        gl::count_t partition_count_;
        gl::count_t partition_element_count_;
    };

    template<typename T> using stream_buffer = gl3::persistent_buffer<T, gl::false_, gl::true_ >;
    template<typename T> using shared_buffer = gl3::persistent_buffer<T, gl::true_ , gl::true_ >;
    template<typename T> using result_buffer = gl3::persistent_buffer<T, gl::true_ , gl::false_>;
}
