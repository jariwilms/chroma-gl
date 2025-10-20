export module opengl.object.buffer;

import std;
import opengl;
import opengl.object;
import opengl.object.fence;
import opengl.object.memory_lock;

export namespace gl
{
    template<typename T>
    struct mapping
    {
        std::span<T> memory;
        gl::range_t    range;
    };
    class  memory_locker
    {
    public:
        void lock          (gl::range_t range)
        {
            locks_.emplace_back(gl::fence{}, range);
        }
        void wait          (gl::range_t range)
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
        buffer(buffer&&) noexcept = default;
       ~buffer()
        {
            gl::delete_buffer(handle());
        }

        auto count() const -> gl::size_t
        {
            return element_count_;
        }
        auto size() const -> gl::size_t
        {
            return element_count_ * element_size_;
        }

        auto operator=(buffer&&) noexcept -> buffer & = default;

    protected:
        buffer(gl::size_t element_count, gl::size_t element_size)
            : gl::object{ gl::create_buffer() }
            , element_count_{ element_count }, element_size_{ element_size } {}

    private:
        gl::size_t element_count_;
        gl::size_t element_size_;
    };
    template<typename T>
    class static_buffer : public gl::buffer
    {
    public:
        static_buffer(std::span<const T> source)
            : gl::buffer{ static_cast<gl::count_t>(source.size()), sizeof(T) }
        {
            gl::buffer_storage(handle(), gl::buffer_storage_flags_e::static_, source);
        }
    };
    template<typename T, gl::bool_t Read, gl::bool_t Write>
    class dynamic_buffer : public gl::buffer
    {
    public:
        dynamic_buffer(gl::count_t element_count)
            : gl::buffer{ element_count, sizeof(T) }
        {
            auto buffer_storage_flags = gl::buffer_storage_flags_e{};
            if constexpr (Read ) buffer_storage_flags |= gl::buffer_storage_flags_e::read;
            if constexpr (Write) buffer_storage_flags |= gl::buffer_storage_flags_e::write;

            gl::buffer_storage<T>(handle(), buffer_storage_flags, element_count);
        }

        void read (std::span<      T> memory, gl::index_t offset = 0u) requires (Read )
        {
            const auto read_range = gl::clamp_range(gl::range_t{ static_cast<gl::count_t>(memory.size()), offset }, count());
            if (read_range.empty()) return;

            mapping_.memory = gl::map_buffer_range<T>(handle(), gl::buffer_mapping_range_access_flags_e::read, read_range);
            memory_locker_.wait(read_range);
            std::memcpy(memory.data(), mapping_.memory.data(), read_range.count * sizeof(T));
            memory_locker_.lock(read_range);
            gl::unmap_buffer(handle());
        }
        void write(std::span<const T> memory, gl::index_t offset = 0u) requires (Write)
        {
            const auto write_range = gl::clamp_range(gl::range_t{ memory.size(), offset }, count());
            if (write_range.empty()) return;

            mapping_.memory = gl::map_buffer_range<T>(handle(), gl::buffer_mapping_range_access_flags_e::write, count());
            memory_locker_.wait(write_range);
            std::memcpy(mapping_.memory.data(), memory.data(), write_range.count * sizeof(T));
            memory_locker_.lock(write_range);
            gl::unmap_buffer(handle());
        }

    private:
        gl::mapping<T>    mapping_;
        gl::memory_locker memory_locker_;
    };
    template<typename T, gl::bool_t Read, gl::bool_t Write>
    class persistent_buffer : public gl::buffer
    {
    public:
        persistent_buffer(gl::count_t element_count)
            : gl::buffer{ element_count, sizeof(T) }
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
        persistent_buffer(gl::persistent_buffer<T, Read, Write>&&) noexcept = default;
       ~persistent_buffer()
        {
            gl::unmap_buffer(handle());
        }

        void read (std::span<      T> memory, gl::index_t offset = 0u) requires (Read )
        {
            const auto read_range = gl::clamp_range(gl::range_t{ memory.size(), offset }, count());
            if (read_range.empty()) return;

            memory_locker_.wait(read_range);
            std::memcpy(memory.data(), mapping_.memory.data(), read_range.count * sizeof(T));
            memory_locker_.lock(read_range);
        }
        void write(std::span<const T> memory, gl::index_t offset = 0u) requires (Write)
        {
            const auto write_range = gl::clamp_range(gl::range_t{ static_cast<gl::count_t>(memory.size()), offset }, count());
            if (write_range.empty()) return;

            memory_locker_.wait(write_range);
            std::memcpy(mapping_.memory.data(), memory.data(), write_range.count * sizeof(T));
            memory_locker_.lock(write_range);
        }

        auto operator=(gl::persistent_buffer<T, Read, Write>&&) noexcept -> gl::persistent_buffer<T, Read, Write>& = default;

    private:
        gl::mapping<T>    mapping_;
        gl::memory_locker memory_locker_;
    };
    template<typename T, gl::bool_t Read, gl::bool_t Write>
    class partition_buffer : private gl::dynamic_buffer<T, Read, Write>
    {
    public:
        partition_buffer(gl::count_t partition_count, gl::count_t partition_element_count)
            : gl::dynamic_buffer<T, Read, Write>{ partition_count * partition_element_count }
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



    template<auto Target, typename T>
    class bindable_buffer;
    template<auto Target, typename T> requires (std::is_same_v<decltype(Target), gl::buffer_target_e     >)
    class bindable_buffer<Target, T> : public T
    {
    public:
        using T::T;

        void bind()
        {
            gl::bind_buffer(this->handle(), Target);
        }
    };
    template<auto Target, typename T> requires (std::is_same_v<decltype(Target), gl::buffer_base_target_e>)
    class bindable_buffer<Target, T> : public T
    {
    public:
        using T::T;

        void bind(gl::binding_t binding)
        {
            gl::bind_buffer_base(this->handle(), Target, binding);
        }
    };

    template<typename T                                   > using generic_buffer = gl::dynamic_buffer   <T, gl::true_ , gl::true_ >;
    template<typename T                                   > using stream_buffer  = gl::persistent_buffer<T, gl::false_, gl::true_ >;
    template<typename T                                   > using shared_buffer  = gl::persistent_buffer<T, gl::true_ , gl::true_ >;
    template<typename T                                   > using result_buffer  = gl::persistent_buffer<T, gl::true_ , gl::false_>;



    struct pixel_buffer_data
    {
        gl::texture_base_format_e texture_base_format = gl::texture_base_format_e::rgba;
        gl::pixel_data_type_e     pixel_data_type     = gl::pixel_data_type_e    ::byte;
    };
    struct compressed_pixel_buffer_data
    {
        gl::texture_compressed_base_format_e texture_compressed_base_format = gl::texture_compressed_base_format_e::rgba;
        //gl::pixel_data_type_e     pixel_data_type = gl::pixel_data_type_e::byte;
    };
    class pixel_pack_buffer
    {
        //TODO
    };
    class pixel_unpack_buffer : public gl::bindable_buffer<gl::buffer_target_e::pixel_unpack_buffer, gl::stream_buffer<gl::byte_t>>
    {
    public:
        pixel_unpack_buffer(gl::count_t element_count)
            : gl::bindable_buffer<gl::buffer_target_e::pixel_unpack_buffer, gl::stream_buffer<gl::byte_t>>{ element_count }
            , pixel_buffer_data_{} {}

        void write            (gl::pixel_buffer_data pixel_buffer_data, std::span<const gl::byte_t> memory)
        {
            pixel_buffer_data_ = pixel_buffer_data;
            gl::bindable_buffer<gl::buffer_target_e::pixel_unpack_buffer, gl::stream_buffer<gl::byte_t>>::write(memory);
        }

        auto pixel_buffer_data() const -> gl::pixel_buffer_data
        {
            return pixel_buffer_data_;
        }

    private:
        gl::pixel_buffer_data pixel_buffer_data_;
    };



    
    template<typename T                                   > using uniform_buffer        = gl::bindable_buffer<gl::buffer_base_target_e::uniform_buffer       , gl::stream_buffer    <T             >>;
    template<typename T, gl::bool_t Read, gl::bool_t Write> using shader_storage_buffer = gl::bindable_buffer<gl::buffer_base_target_e::shader_storage_buffer, gl::persistent_buffer<T, Read, Write>>;
                                                            //using pixel_pack_buffer     = gl::bindable_buffer<gl::buffer_target_e     ::pixel_pack_buffer    , gl::stream_buffer    <gl::byte_t    >>;
                                                            //using pixel_unpack_buffer   = gl::bindable_buffer<gl::buffer_target_e     ::pixel_unpack_buffer  , gl::stream_buffer    <gl::byte_t    >>;
    template<typename T                                   > using draw_indirect_buffer  = gl::bindable_buffer<gl::buffer_target_e     ::draw_indirect_buffer , gl::stream_buffer    <T             >>;
}
