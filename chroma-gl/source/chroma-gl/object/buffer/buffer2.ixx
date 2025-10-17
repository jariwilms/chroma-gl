export module buffer2;
//
//import std;
//import opengl;
//import opengl.object;
//import opengl.object.fence;
//import opengl.object.memory_lock;
//
//export namespace gl2
//{
//    class buffer : public gl::object
//    {
//    public:
//        buffer(buffer&& other) = default;
//       ~buffer()
//        {
//            gl::delete_buffer(handle());
//        }
//
//        auto count    () const -> gl::count_t
//        {
//            return element_count_;
//        }
//        auto size     () const -> gl::size_t
//        {
//            return element_count_ * element_size_;
//        }
//
//        auto operator=(buffer&&) -> buffer& = default;
//
//    protected:
//        buffer(gl::count_t element_count, gl::size_t element_size)
//            : gl::object{ gl::create_buffer() }
//            , element_count_{ element_count }, element_size_{ element_size } {}
//
//    private:
//        gl::count_t element_count_;
//        gl::size_t  element_size_;
//    };
//    template<typename T>
//    class static_buffer : public gl2::buffer
//    {
//    public:
//        static_buffer(std::span<const T> source)
//            : gl2::buffer{ source.size(), sizeof(T) }
//        {
//            gl::buffer_storage(handle(), gl::buffer_storage_flags_e::static_, source);
//        }
//    };
//
//    template<typename T>
//    class mappable_buffer : public gl2::buffer
//    {
//    public:
//        mappable_buffer(gl::count_t element_count, gl::size_t element_size)
//            : gl2::buffer{ element_count, element_size } {}
//       ~mappable_buffer()
//        {
//            unmap();
//        }
//
//        void map         (gl::buffer_mapping_range_access_flags_e access_flags)
//        {
//            map(count(), access_flags);
//        }
//        void map         (gl::range range, gl::buffer_mapping_range_access_flags_e access_flags)
//        {
//            if (range = gl::clamp_range(range, count()); range != mapped_range_ && range.count > gl::count_t{ 0u })
//            {
//                unmap();
//
//                mapped_data_  = gl::map_buffer_range<T>(handle(), access_flags, range);
//                mapped_range_ = range;
//            }
//        }
//        void unmap       ()
//        {
//            if ( mapped_data_.empty()      ) return;
//            if (!gl::unmap_buffer(handle())) throw std::runtime_error{ "data store may be corrupt" };
//
//            locks_.clear();
//            mapped_data_  = {};
//            mapped_range_ = {};
//        }
//
//        void lock        (gl::range range)
//        {
//            locks_.emplace_back(gl::fence{}, range);
//        }
//        void wait        (gl::range range)
//        {
//            auto remaining_locks = std::vector<gl::memory_lock_t>{};
//            std::ranges::for_each(locks_, [&](gl::memory_lock_t& lock)
//                {
//                    if (auto& [lock_fence, lock_range] = lock; gl::range_overlaps(lock_range, range))
//                    {
//                        auto status = gl::synchronization_status_e::timeout_expired;
//                        auto timeout = gl::time_t{ 0u };
//
//                        while (status == gl::synchronization_status_e::timeout_expired)
//                        {
//                            status = gl::client_wait_sync(lock_fence, gl::synchronization_command_e::flush, timeout);
//                            timeout = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds{ 1u }).count();
//
//                            if (status == gl::synchronization_status_e::wait_failed) throw std::runtime_error{ "Sync wait failed!" };
//                        }
//                    }
//                    else
//                    {
//                        remaining_locks.emplace_back(std::move(lock));
//                    }
//                });
//
//            locks_ = std::move(remaining_locks);
//        }
//
//        auto mapped_data () const -> std::span<const T>
//        {
//            return mapped_data_;
//        }
//        auto mapped_data () -> std::span<T>
//        {
//            return mapped_data_;
//        }
//        auto mapped_range() const -> gl::range
//        {
//            return mapped_range_;
//        }
//
//    private:
//        std::vector<gl::memory_lock_t> locks_;
//        std::span<T>            mapped_data_;
//        gl::range               mapped_range_;
//    };
//    template<typename Derived, typename T, gl::bool_t Read = gl::true_, gl::bool_t Write = gl::true_, gl::bool_t Persistent = gl::true_>
//    class transfer_buffer;
//    template<typename Derived, typename T, gl::bool_t Persistent>
//    class transfer_buffer<Derived, T, gl::false_, gl::false_, Persistent>
//    {
//    public:
//        transfer_buffer()
//        {
//            static_assert(gl::false_, "invalid specification");
//        }
//    };
//    template<typename Derived, typename T, gl::bool_t Persistent>
//    class transfer_buffer<Derived, T, gl::true_, gl::false_, Persistent>
//    {
//    public:
//        void read(std::span<T> destination)
//        {
//            auto&       self         = reinterpret_cast<gl2::mappable_buffer<T>&>(*this);
//            auto  const range        = gl::clamp_range(gl::range{ static_cast<gl::count_t>(destination.size()) }, self.mapped_range().count);
//            auto        access_flags = gl::buffer_mapping_range_access_flags_e::read;
//            if constexpr (Persistent) access_flags |= gl::buffer_mapping_range_access_flags_e::persistent | gl::buffer_mapping_range_access_flags_e::coherent;
//
//            if constexpr (!Persistent) self.map(access_flags);
//            self.wait(range), std::memcpy(destination.data(), self.mapped_data().data(), range.count * sizeof(T)), self.lock(range);
//            if constexpr (!Persistent) self.unmap();
//        }
//    };
//    template<typename Derived, typename T, gl::bool_t Persistent>
//    class transfer_buffer<Derived, T, gl::false_, gl::true_, Persistent>
//    {
//    public:
//        void write(std::span<const T> source)
//        {
//            auto&       self         = reinterpret_cast<gl2::mappable_buffer<T>&>(*this);
//            auto  const range        = gl::clamp_range(gl::range{ static_cast<gl::count_t>(source.size()) }, self.mapped_range().count);
//            auto        access_flags = gl::buffer_mapping_range_access_flags_e::write;
//            if constexpr (Persistent) access_flags |= gl::buffer_mapping_range_access_flags_e::persistent | gl::buffer_mapping_range_access_flags_e::coherent;
//
//            if constexpr (!Persistent) self.map(access_flags);
//            self.wait(range), std::memcpy(self.mapped_data().data(), source.data(), range.count * sizeof(T)), self.lock(range);
//            if constexpr (!Persistent) self.unmap();
//        }
//    };
//    template<typename Derived, typename T, gl::bool_t Persistent>
//    class transfer_buffer<Derived, T, gl::true_, gl::true_, Persistent> 
//        : public gl2::transfer_buffer<Derived, T, gl::true_ , gl::false_, Persistent>
//        , public gl2::transfer_buffer<Derived, T, gl::false_, gl::true_ , Persistent>
//    {
//
//    };
//    template<typename T, gl::bool_t Read = gl::true_, gl::bool_t Write = gl::true_, gl::bool_t Persistent = gl::true_>
//    class dynamic_buffer
//        : protected gl2::mappable_buffer<T>
//        , public    gl2::transfer_buffer<gl2::dynamic_buffer<T>, T, Read, Write, Persistent>
//    {
//    public:
//        dynamic_buffer(gl::count_t count)
//            : gl2::mappable_buffer<T>{ count, sizeof(T) }
//        {
//            auto buffer_storage_flags = gl::buffer_storage_flags_e{};
//            if constexpr (Read      ) buffer_storage_flags |= gl::buffer_storage_flags_e::read;
//            if constexpr (Write     ) buffer_storage_flags |= gl::buffer_storage_flags_e::write;
//            if constexpr (Persistent) buffer_storage_flags |= gl::buffer_storage_flags_e::persistent | gl::buffer_storage_flags_e::coherent;
//
//            gl::buffer_storage(handle(), buffer_storage_flags, size());
//        }
//
//    private:
//        using gl::object::handle;
//        using gl2::buffer::size;
//    };
//
//    template<typename T, gl::bool_t Read = gl::true_, gl::bool_t Write = gl::true_>
//    using persistent_buffer = gl2::dynamic_buffer<T, Read, Write, gl::true_>;
//    template<typename T, gl::bool_t Persistent>
//    using result_buffer     = gl2::dynamic_buffer<T, gl::true_, gl::false_, Persistent>;
//    template<typename T>
//    using stream_buffer     = gl2::dynamic_buffer<T, gl::false_, gl::true_, gl::true_>;
//    template<typename T, gl::bool_t Persistent = gl::true_>
//    using shared_buffer     = gl2::dynamic_buffer<T, gl::true_, gl::true_, Persistent>;
//
//    void my_func()
//    {
//        auto my_buffer = gl2::stream_buffer<gl::uint32_t>{ 8u };
//        my_buffer.write({});
//
//    }
//}
