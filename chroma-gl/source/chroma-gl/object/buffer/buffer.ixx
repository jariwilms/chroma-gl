export module opengl.object.buffer;

import std;
import opengl;
import opengl.object;
import opengl.object.fence;
import opengl.object.lock;

export namespace glx
{
    //template<typename T>
    //class buffer : public gl::object
    //{
    //public:
    //    using target_e = gl::buffer_base_target_e;

    //    auto size () const -> gl::sizei_t
    //    {
    //        return size_;
    //    }
    //    auto count() const -> gl::count_t
    //    {
    //        return size_ / sizeof(T);
    //    }

    //protected:
    //    buffer()
    //        : gl::object{ gl::create_buffer() } {}

    //private:
    //    gl::sizei_t size_;
    //};

    //template<typename T>
    //class static_buffer : public gl::object
    //{
    //public:
    //    explicit 
    //    static_buffer(std::span<const T> data)
    //        : gl::object{ gl::create_buffer()                         }
    //        , size_     { static_cast<gl::sizei_t>(data.size_bytes()) }
    //    {
    //        gl::buffer_storage<T>(handle(), gl::buffer_storage_flags_e::static_, data);
    //    }
    //    static_buffer(static_buffer&&) = default;
    //   ~static_buffer()
    //    {
    //        gl::delete_buffer(handle());
    //    }

    //    auto size() const -> gl::sizei_t
    //    {
    //        return size_;
    //    }
    //    auto count() const -> gl::count_t
    //    {
    //        return size_ / sizeof(T);
    //    }

    //    auto operator=(static_buffer&&) -> static_buffer& = default;

    //private:
    //    gl::sizei_t size_;
    //};
    //template<typename T>
    //class dynamic_buffer : public gl::object
    //{
    //public:
    //    explicit
    //    dynamic_buffer(std::span<const T> data)
    //        : gl::object{ gl::create_buffer()                         }
    //        , size_     { static_cast<gl::sizei_t>(data.size_bytes()) }
    //    {
    //        gl::buffer_storage<T>(handle(), gl::buffer_storage_flags_e::shared, data);
    //    }
    //    explicit
    //    dynamic_buffer(gl::count_t count)
    //        : gl::object{ gl::create_buffer()                         }
    //        , size_     { static_cast<gl::sizei_t>(count * sizeof(T)) }
    //    {
    //        gl::buffer_storage<T>(handle(), gl::buffer_storage_flags_e::shared, count);
    //    }
    //    dynamic_buffer(dynamic_buffer&&) = default;
    //   ~dynamic_buffer()
    //    {
    //        unmap(); 
    //        gl::delete_buffer(handle());
    //    }

    //    void map         ()
    //    {
    //        map(count());
    //    }
    //    void map         (gl::range range)
    //    {
    //        if (range = gl::clamp_range(range, count()); range != mapped_range_ && range.count > gl::count_t{ 0u })
    //        {
    //            unmap();

    //            mapped_data_  = gl::map_buffer_range<T>(handle(), gl::buffer_mapping_range_access_flags_e::shared, range);
    //            mapped_range_ = range;
    //        }
    //    }
    //    void unmap       ()
    //    {
    //        if (!is_mapped())                return;
    //        if (!gl::unmap_buffer(handle())) throw std::runtime_error{ "Data store is undefined!" };

    //        locks_.clear();
    //        mapped_range_ = {};
    //        mapped_data_  = {};
    //    }

    //    void read        (std::span<      T> data)
    //    {
    //        const auto range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(data.size()) }, mapped_range_.count);
    //        await(range), std::memcpy(data.data(), mapped_data_.data(), range.count * sizeof(T)), lock(range);
    //    }
    //    void write       (std::span<const T> data)
    //    {
    //        const auto range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(data.size()) }, mapped_range_.count);
    //        await(range), std::memcpy(mapped_data_.data(), data.data(), range.count * sizeof(T)), lock(range);
    //    }

    //    auto size        () const -> gl::sizei_t
    //    {
    //        return size_;
    //    }
    //    auto count       () const -> gl::count_t
    //    {
    //        return size_ / sizeof(T);
    //    }
    //    auto mapped_range() const -> gl::range
    //    {
    //        return mapped_range_;
    //    }
    //    auto is_mapped   () const -> gl::bool_t
    //    {
    //        return !mapped_data_.empty();
    //    }

    //private:
    //    void lock        (gl::range range)
    //    {
    //        locks_.emplace_back(gl::fence{}, range);
    //    }
    //    void await       (gl::range range)
    //    {
    //        auto remaining_locks = std::vector<gl::lock_t>{};
    //        std::ranges::for_each(locks_, [&](gl::lock_t& lock)
    //            {
    //                if (auto& [lock_fence, lock_range] = lock; gl::range_overlaps(lock_range, range))
    //                {
    //                    auto status  = gl::synchronization_status_e::timeout_expired;
    //                    auto timeout = gl::time_t{ 0u };

    //                    while (status == gl::synchronization_status_e::timeout_expired)
    //                    {
    //                        status  = gl::client_wait_sync(lock_fence, gl::synchronization_command_e::flush, timeout);
    //                        timeout = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count();
    //                        
    //                        if (status == gl::synchronization_status_e::wait_failed) throw std::runtime_error{ "Sync wait failed!" };
    //                    }
    //                }
    //                else
    //                {
    //                    remaining_locks.emplace_back(std::move(lock));
    //                }
    //            });

    //        locks_ = std::move(remaining_locks);
    //    }

    //    gl ::sizei_t            size_;
    //    std::vector<gl::lock_t> locks_;
    //    std::span<T>            mapped_data_;
    //    gl ::range              mapped_range_;
    //};

    //template<typename T>
    //class uniform_buffer : public glx::buffer<T>
    //{
    //public:
    //    uniform_buffer(const T& value)
    //    {
    //        gl::buffer_storage<T>(handle(), gl::buffer_storage_flags_e::shared_write, std::span{ &value, 1u });
    //    }

    //    void bind(gl::binding_t binding)
    //    {
    //        gl::bind_buffer_base(handle(), gl::buffer_base_target_e::uniform_buffer, binding);
    //    }

    //private:
    //    using gl::object::handle;
    //};
    //template<typename T>
    //class uniform_array_buffer
    //{

    //};
}
export namespace gly
{
    //class buffer : public gl::object
    //{
    //public:
    //    enum class mapping_e
    //    {
    //        none      , 
    //        read      , 
    //        write     , 
    //        read_write, 
    //    };

    //    buffer(buffer&& other) = default;
    //   ~buffer()
    //    {
    //        gl::delete_buffer(handle());
    //    }

    //    auto count() const -> gl::count_t
    //    {
    //        return count_;
    //    }
    //    auto size () const -> gl::sizei_t
    //    {
    //        return size_;
    //    }

    //    auto operator=(buffer&&) -> buffer& = default;

    //protected:
    //    template<typename T>
    //    buffer(gl::count_t count)
    //        : gl::object{ gl::create_buffer() }
    //        , count_{ count }, size_{ static_cast<gl::sizei_t>(count_ * sizeof(T)) } {}

    //private:
    //    gl::count_t count_;
    //    gl::sizei_t size_;
    //};
    //template<typename T>
    //class static_buffer : public glz::buffer
    //{
    //public:
    //    explicit
    //    static_buffer(std::span<const T> source)
    //        : glz::buffer<T>{ static_cast<gl::count_t>(source.size()) }
    //    {
    //        gl::buffer_storage(handle(), gl::buffer_storage_flags_e::static_, source);
    //    }

    //    using gl::object::handle;
    //};
    //template<typename T>
    //class dynamic_buffer : public glz::buffer<T>
    //{
    //public:
    //    explicit
    //    dynamic_buffer(gl::count_t count)
    //        : glz::buffer<T>{ count }
    //    {
    //        gl::buffer_storage(handle(), gl::buffer_storage_flags_e::shared, count);
    //    }
    //    explicit
    //    dynamic_buffer(std::span<const T> source)
    //        : glz::buffer<T>{ static_cast<gl::count_t>(source.size()) }
    //    {
    //        gl::buffer_storage(handle(), gl::buffer_storage_flags_e::shared, source);
    //    }
    //    dynamic_buffer(dynamic_buffer&&) noexcept = default;
    //   ~dynamic_buffer()
    //    {
    //        unmap(); 
    //    }

    //    void map         ()
    //    {
    //        map(count());
    //    }
    //    void map         (gl::range range)
    //    {
    //        if (range = gl::clamp_range(range, count()); range != mapped_range_ && range.count > gl::count_t{ 0u })
    //        {
    //            unmap();

    //            mapped_data_  = gl::map_buffer_range<T>(handle(), gl::buffer_mapping_range_access_flags_e::shared, range);
    //            mapped_range_ = range;
    //        }
    //    }
    //    void unmap       ()
    //    {
    //        if ( mapped_data_.empty())       return;
    //        if (!gl::unmap_buffer(handle())) throw std::runtime_error{ "Data store may be corrupt." };

    //        locks_.clear();
    //        mapped_data_  = {};
    //        mapped_range_ = {};
    //    }

    //    void read        (std::span<      T> destination)
    //    {
    //        const auto range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(destination.size()) }, mapped_range_.count);
    //        wait(range), std::memcpy(destination.data(), mapped_data_.data(), range.count * sizeof(T)), lock(range);
    //    }
    //    void write       (std::span<const T> source     )
    //    {
    //        const auto range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(source.size()) }, mapped_range_.count);
    //        wait(range), std::memcpy(mapped_data_.data(), source.data(), range.count * sizeof(T)), lock(range);
    //    }

    //    using gl ::object   ::handle;
    //    using glz::buffer<T>::count;
    //    using glz::buffer<T>::size;

    //    auto operator=(dynamic_buffer&&) noexcept -> dynamic_buffer& = default;

    //private:
    //    void lock        (gl::range range)
    //    {
    //        locks_.emplace_back(gl::fence{}, range);
    //    }
    //    void wait        (gl::range range)
    //    {
    //        auto remaining_locks = std::vector<gl::lock_t>{};
    //        std::ranges::for_each(locks_, [&](gl::lock_t& lock)
    //            {
    //                if (auto& [lock_fence, lock_range] = lock; gl::range_overlaps(lock_range, range))
    //                {
    //                    auto status  = gl::synchronization_status_e::timeout_expired;
    //                    auto timeout = gl::time_t{ 0u };

    //                    while (status == gl::synchronization_status_e::timeout_expired)
    //                    {
    //                        status  = gl::client_wait_sync(lock_fence, gl::synchronization_command_e::flush, timeout);
    //                        timeout = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count();
    //                        
    //                        if (status == gl::synchronization_status_e::wait_failed) throw std::runtime_error{ "Sync wait failed!" };
    //                    }
    //                }
    //                else
    //                {
    //                    remaining_locks.emplace_back(std::move(lock));
    //                }
    //            });

    //        locks_ = std::move(remaining_locks);
    //    }

    //    std::vector<gl::lock_t> locks_;
    //    std::span<T>            mapped_data_;
    //    gl ::range              mapped_range_;
    //};



    //template<typename T>
    //class uniform_buffer
    //{
    //public:
    //};
    //template<typename T>
    //class uniform_array_buffer
    //{
    //public:
    //    void write(                   std::span<const T > source)
    //    {

    //    }
    //    void write(gl::index_t index,           const T&  value )
    //    {
    //        
    //    }
    //};

    //
    //
    //template<typename T>
    //class shader_storage_buffer : public glz::dynamic_buffer<T>
    //{
    //public:
    //    using glz::dynamic_buffer<T>::dynamic_buffer;

    //    void bind(gl::binding_t binding)
    //    {
    //        gl::bind_buffer_base(handle(), gl::buffer_base_target_e::shader_storage_buffer, binding);
    //    }

    //    using gl::object::handle;
    //};
    // 
    // 
    //class atomic_counter_buffer
    //class indirect_draw_buffer
}
export namespace glz //mappable buffer with virtual inheritance
{
    //template<typename T>//, gl::buffer_mapping_range_access_flags_e RAF = gl::buffer_mapping_range_access_flags_e{}>
    //class basic_mappable_buffer : public glz::buffer<T>
    //{
    //protected:
    //    basic_mappable_buffer(gl::count_t count = 0u)
    //        : glz::buffer<T>{ count } {}

    //    void map         (                 gl::buffer_mapping_range_access_flags_e range_access_flags)
    //    {
    //        map(count(), range_access_flags);
    //    }
    //    void map         (gl::range range, gl::buffer_mapping_range_access_flags_e range_access_flags)
    //    {
    //        if (range = gl::clamp_range(range, count()); range != mapped_range_ && range.count > gl::count_t{ 0u })
    //        {
    //            unmap();

    //            mapped_data_  = gl::map_buffer_range<T>(handle(), range_access_flags, range);
    //            mapped_range_ = range;
    //        }
    //    }
    //    void unmap       ()
    //    {
    //        if ( mapped_data_.empty())       return;
    //        if (!gl::unmap_buffer(handle())) throw std::runtime_error{ "data store may be corrupt" };

    //        locks_.clear();
    //        mapped_data_  = {};
    //        mapped_range_ = {};
    //    }

    //    void lock        (gl::range range)
    //    {
    //        locks_.emplace_back(gl::fence{}, range);
    //    }
    //    void wait        (gl::range range)
    //    {
    //        auto remaining_locks = std::vector<gl::lock_t>{};
    //        std::ranges::for_each(locks_, [&](gl::lock_t& lock)
    //            {
    //                if (auto& [lock_fence, lock_range] = lock; gl::range_overlaps(lock_range, range))
    //                {
    //                    auto status  = gl::synchronization_status_e::timeout_expired;
    //                    auto timeout = gl::time_t{ 0u };

    //                    while (status == gl::synchronization_status_e::timeout_expired)
    //                    {
    //                        status  = gl::client_wait_sync(lock_fence, gl::synchronization_command_e::flush, timeout);
    //                        timeout = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count();
    //                        
    //                        if (status == gl::synchronization_status_e::wait_failed) throw std::runtime_error{ "Sync wait failed!" };
    //                    }
    //                }
    //                else
    //                {
    //                    remaining_locks.emplace_back(std::move(lock));
    //                }
    //            });

    //        locks_ = std::move(remaining_locks);
    //    }

    //    auto mapped_range() const -> gl::range
    //    {
    //        return mapped_range_;
    //    }
    //    auto mapped_data () -> std::span<T>
    //    {
    //        return mapped_data_;
    //    }

    //private:
    //    using gl::object::handle;
    //    using glz::buffer<T>::count;

    //    std::vector<gl::lock_t> locks_;
    //    std::span<T>            mapped_data_;
    //    gl::range               mapped_range_;
    //};
    //template<typename T>
    //class mappable_read_buffer : virtual public peer::basic_mappable_buffer<T> 
    //{
    //public:
    //    void read(std::span<T> destination)
    //    {
    //        const auto range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(destination.size()) }, mapped_range().count);
    //        wait(range), std::memcpy(destination.data(), mapped_data().data(), range.count * sizeof(T)), lock(range);
    //    }

    //protected:
    //    mappable_read_buffer() = default;

    //private:
    //    using peer::basic_mappable_buffer<T>::lock;
    //    using peer::basic_mappable_buffer<T>::wait;
    //    using peer::basic_mappable_buffer<T>::mapped_data;
    //    using peer::basic_mappable_buffer<T>::mapped_range;
    //};
    //template<typename T>
    //class mappable_write_buffer : virtual public peer::basic_mappable_buffer<T> 
    //{
    //public:
    //    void write(std::span<const T> source)
    //    {
    //        const auto range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(source.size()) }, mapped_range().count);
    //        wait(range), std::memcpy(mapped_data().data(), source.data(), range.count * sizeof(T)), lock(range);
    //    }

    //protected:
    //    mappable_write_buffer() = default;

    //private:
    //    using peer::basic_mappable_buffer<T>::lock;
    //    using peer::basic_mappable_buffer<T>::wait;
    //    using peer::basic_mappable_buffer<T>::mapped_data;
    //    using peer::basic_mappable_buffer<T>::mapped_range;
    //};
    //template<typename T, gl::bool_t R, gl::bool_t W>
    //class mappable_buffer :
    //    public std::conditional_t<R, mappable_read_buffer <T>, std::monostate>, 
    //    public std::conditional_t<W, mappable_write_buffer<T>, std::monostate>
    //{
    //public:
    //    mappable_buffer(gl::count_t count) 
    //        : peer::basic_mappable_buffer<T>{ count }
    //    {
    //        auto storage_flags = gl::buffer_storage_flags_e::persistent | gl::buffer_storage_flags_e::coherent;
    //        if constexpr (R) storage_flags |= gl::buffer_storage_flags_e::read;
    //        if constexpr (W) storage_flags |= gl::buffer_storage_flags_e::write;

    //        gl::buffer_storage<T>(this->handle(), storage_flags, count);
    //    }

    //    void map()
    //    {
    //        peer::mappable_buffer<T>::map();
    //    }
    //    void map(gl::range range)
    //    {
    //        auto range_access_flags = gl::buffer_mapping_range_access_flags_e::persistent | gl::buffer_mapping_range_access_flags_e::coherent;
    //        if constexpr (R) range_access_flags |= gl::buffer_mapping_range_access_flags_e::read;
    //        if constexpr (W) range_access_flags |= gl::buffer_mapping_range_access_flags_e::write;

    //        peer::mappable_buffer<T>::map(range, range_access_flags);
    //    }
    //    void unmap()
    //    {
    //        peer::mappable_buffer<T>::unmap();
    //    }

    //private:
    //    using gl::object::handle;
    //    using glz::buffer<T>::count;
    //    using peer::basic_mappable_buffer<T>::lock;
    //    using peer::basic_mappable_buffer<T>::wait;
    //    using peer::basic_mappable_buffer<T>::mapped_data;
    //    using peer::basic_mappable_buffer<T>::mapped_range;
    //};

    //template<typename T, gl::bool_t R = gl::true_, gl::bool_t W = gl::true_>
    //class shader_storage_buffer : public peer::mappable_buffer<T, R, W>
    //{
    //public:
    //    shader_storage_buffer(gl::count_t count)
    //        : peer::mappable_buffer<T, R, W>{ count }
    //    {

    //    }

    //    void bind(gl::binding_t binding)
    //    {
    //        gl::bind_buffer_base(this->handle(), gl::buffer_base_target_e::shader_storage_buffer, binding);
    //    }
    //};
}

export namespace gla
{
    //class buffer : public gl::object
    //{
    //public:
    //    enum class mapping_e
    //    {
    //        none      , 
    //        read      , 
    //        write     , 
    //        read_write, 
    //    };

    //    buffer(buffer&& other) = default;
    //   ~buffer()
    //    {
    //        gl::delete_buffer(handle());
    //    }

    //    auto count() const -> gl::count_t
    //    {
    //        return count_;
    //    }
    //    auto size () const -> gl::sizei_t
    //    {
    //        return size_;
    //    }

    //    auto operator=(buffer&&) -> buffer& = default;

    //protected:
    //    buffer(gl::count_t count, gl::sizei_t element_size)
    //        : gl::object{ gl::create_buffer() }
    //        , count_{ count }, size_{ static_cast<gl::sizei_t>(count_ * element_size) } {}

    //private:
    //    gl::count_t count_;
    //    gl::sizei_t size_;
    //};
    //template<typename T>
    //class static_buffer : gla::buffer
    //{
    //public:
    //    static_buffer(gl::count_t count)
    //        : gla::buffer<T>{ count }
    //    {

    //    }
    //};
}
