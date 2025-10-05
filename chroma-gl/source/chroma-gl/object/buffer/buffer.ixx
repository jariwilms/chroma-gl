export module opengl.object.buffer;

import std;
import opengl;
import opengl.object;

export namespace gl
{
    template<typename T>
    class buffer : public gl::object
    {
    public:
        explicit buffer(gl::count_t count)
            : gl::object{ gl::create_buffer(), [](auto* handle) { gl::delete_buffer(*handle); } }
            , size_{ static_cast<gl::sizei_t>(count * sizeof(T)) }, range_{}, sync_locks_{}, data_{}
        {
            if (gl::compare<std::equal_to>(count, gl::count_t{ 0u })) throw std::invalid_argument{ "Count must be greater than 0!" };

            gl::buffer_storage<T>(handle(), gl::buffer_storage_flags_e::dynamic_storage | gl::buffer_storage_flags_e::shared, count);
        }
        explicit buffer(std::span<const T> data)
            : gl::object{ gl::create_buffer(), [](auto* handle) { gl::delete_buffer(*handle); } }
            , size_{ static_cast<gl::sizei_t>(data.size_bytes()) }, range_{}, sync_locks_{}, data_{}
        {
            if (data.empty()) throw std::invalid_argument{ "Data may not be empty!" };

            gl::buffer_storage<T>(handle(), gl::buffer_storage_flags_e::dynamic_storage | gl::buffer_storage_flags_e::shared, data);
        }

        void copy     (                   std::span<const T> data)
        {
            copy(gl::index_t{ 0u }, data);
        }
        void copy     (gl::index_t index, std::span<const T> data)
        {
            if (is_mapped())                                     throw std::logic_error     { "Copying to a mapped buffer is not allowed!" };
            if (gl::compare<std::greater_equal>(index, count())) throw std::invalid_argument{ "Index out of range!"                        };
            
            gl::buffer_data(handle(), index, data);
        }

        auto map      () -> std::span<T>
        {
            if (!is_mapped())
            {
                range_ = count();
                
                await(range_);

                data_  = gl::map_buffer_range<T>(handle(), gl::buffer_mapping_range_access_flags_e::shared, count());
            }

            return data_;
        }
        auto map      (gl::range range) -> std::span<T>
        {
            if (range != range_)
            {
                range_ = gl::clamp_range(range, count());

                await(range_);
                
                data_       = gl::map_buffer_range<T>(handle(), gl::buffer_mapping_range_access_flags_e::shared, range_);
            }
            
            return data_;
        }
        void unmap    ()
        {
            if (!is_mapped())                return;
            if (!gl::unmap_buffer(handle())) throw std::runtime_error{ "Data store is undefined!" };

            std::ranges::for_each(sync_locks_, [](gl::sync_lock_t& sync_lock)
                {
                    const auto& [sync, lock] = sync_lock;
                    gl::delete_sync(sync);
                });

            range_     = {};
            sync_locks_.clear();
            data_      .reset();
        }

        void lock     (gl::range range)
        {
            sync_locks_.emplace_back(gl::fence_sync(), gl::clamp_range(range, count()));
        }
        void await    (gl::range range)
        {
            auto remaining_locks = std::vector<gl::sync_lock_t>{};
            std::ranges::for_each(sync_locks_, [&](const gl::sync_lock_t& sync_lock)
                {
                    if (const auto& [sync, lock] = sync_lock; gl::range_overlaps(lock, range))
                    {
                        auto status  = gl::synchronization_status_e::timeout_expired;
                        auto timeout = gl::time_t{ 0u };

                        while (status == gl::synchronization_status_e::timeout_expired)
                        {
                            status  = gl::client_wait_sync(sync, gl::synchronization_command_e::flush, timeout);
                            timeout = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count();
                            
                            if (status == gl::synchronization_status_e::wait_failed) throw std::runtime_error{ "Sync wait failed!" };
                        }

                        gl::delete_sync(sync);
                    }
                    else
                    {
                        remaining_locks.emplace_back(sync_lock);
                    }
                });

            sync_locks_ = std::move(remaining_locks);
        }

        auto size     () const -> gl::sizei_t
        {
            return size_;
        }
        auto count    () const -> gl::count_t
        {
            return static_cast<gl::count_t>(size() / sizeof(T));
        }
        auto is_mapped() const -> gl::bool_t
        {
            return !data_.empty();
        }
        auto data     () const -> std::span<const T>
        {
            return data_;
        }
        auto data     () -> std::span<T>
        {
            return data_.value();
        }

        auto operator[](gl::sizei_t index) const -> const T&
        {
            return data_[index];
        }
        auto operator[](gl::sizei_t index) -> T&
        {
            return data_[index];
        }

    private:
        gl::sizei_t                  size_;
        gl::range                    range_;
        std::vector<gl::sync_lock_t> sync_locks_;
        std::span<T>                 data_;
    };
    template<typename T>
    class uniform_buffer : public gl::object
    {
    public:
        explicit uniform_buffer(const T& data = {})
            : gl::object{ gl::create_buffer(), [](auto* handle) { gl::delete_buffer(*handle); } }
            , size_{ static_cast<gl::sizei_t>(sizeof(T)) }
        {
            gl::buffer_storage<T>(handle(), gl::buffer_storage_flags_e::dynamic_storage, std::span<const T>{ &data, 1u });
        }

        void bind      (gl::binding_t binding) const
        {
            gl::bind_buffer_base(handle(), gl::buffer_base_target_e::uniform_buffer, binding);
        }

        void copy      (const T& data)
        {
            gl::buffer_data(handle(), gl::index_t{ 0u }, std::span<const T>{ &data, 1u });
        }
        template<typename... U> requires (std::is_trivially_copyable_v<U> && ...)
        void copy_slice(gl::offset_t offset, U... slice) 
        {
            static_assert(sizeof...(U) <= sizeof(T), "Slice may not be larger than its containing structure!");

            auto array = std::array<gl::byte_t, sizeof...(U)>{};
            std::apply([&array](const auto&... element)
                {
                    auto offset = gl::offset_t{};
                    ((std::memcpy(array.data() + offset, &element, sizeof(element)), offset += sizeof(element)), ...);
                }, std::tuple{ std::forward<U>(slice)... });

            gl::buffer_data<gl::byte_t>(handle(), static_cast<gl::index_t>(offset), array);
        }

        auto size      () const -> gl::sizei_t
        {
            return size_;
        }

    private:
        gl::sizei_t size_;
    };
    template<typename T>
    class uniform_array_buffer : public gl::buffer<T>
    {
    public:
        using gl::buffer<T>::buffer;

        void bind(gl::binding_t binding                 ) const
        {
            gl::bind_buffer_base(handle(), gl::buffer_base_target_e::uniform_buffer, binding);
        }
        void bind(gl::binding_t binding, gl::range range) const
        {
            gl::bind_buffer_range<T>(handle(), gl::buffer_base_target_e::uniform_buffer, binding, range);
        }

        using gl::buffer<T>::copy;
        void copy(gl::index_t index, const T& data)
        {
            gl::buffer<T>::copy(index, std::span{ &data, gl::uint64_t{ 1u } });
        }

    private:
        using gl::buffer<T>::handle;
    };
}
