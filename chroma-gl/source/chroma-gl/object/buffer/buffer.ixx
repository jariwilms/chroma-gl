export module opengl.object.buffer;
//
//import std;
//import opengl;
//import opengl.object;
//import opengl.object.fence;
//import opengl.object.::memory_lock_t;
//
//export namespace gl
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
//        auto count() const -> gl::size_t
//        {
//            return size_ / element_size_;
//        }
//        auto size () const -> gl::size_t
//        {
//            return size_;
//        }
//
//        auto operator=(buffer&&) -> buffer& = default;
//
//    protected:
//        buffer(gl::size_t size, gl::size_t element_size)
//            : gl::object{ gl::create_buffer() }
//            , size_{ size }, element_size_{ element_size } {}
//
//    private:
//        gl::size_t size_;
//        gl::size_t element_size_;
//    };
//    template<typename T>
//    class static_buffer : public gl::buffer
//    {
//    public:
//        static_buffer(std::span<const T> source)
//            : gl::buffer{ source.size_bytes(), sizeof(T) }
//        {
//            gl::buffer_storage(handle(), gl::buffer_storage_flags_e::static_, source);
//        }
//    };
//    template<typename T, gl::bool_t Read = gl::true_, gl::bool_t Write = gl::true_>
//    class dynamic_buffer : public gl::buffer
//    {
//    public:
//        dynamic_buffer(std::span<const T> source)
//            : gl::buffer{ source.size_bytes(), sizeof(T) }
//            , locks_{}, mapped_data_{}, mapped_range_{}
//        {
//            gl::buffer_storage(handle(), storage_flags(), source);
//        }
//        dynamic_buffer(gl::size_t size)
//            : gl::buffer{ size, sizeof(T) }
//            , locks_{}, mapped_data_{}, mapped_range_{}
//        {
//            gl::buffer_storage(handle(), storage_flags(), size);
//        }
//        dynamic_buffer(dynamic_buffer&&) noexcept = default;
//       ~dynamic_buffer()
//        {
//            unmap();
//        }
//
//        void map          ()
//        {
//            map(count());
//        }
//        void map          (gl::range range)
//        {
//            if (range = gl::clamp_range(range, count()); range != mapped_range_ && range.count > gl::count_t{ 0u })
//            {
//                unmap();
//
//                mapped_data_ = gl::map_buffer_range<T>(handle(), access_flags(), range);
//                mapped_range_ = range;
//            }
//        }
//        void unmap        ()
//        {
//            if ( mapped_data_.empty()      ) return;
//            if (!gl::unmap_buffer(handle())) throw std::runtime_error{ "data store may be corrupt" };
//
//            locks_.clear();
//            mapped_data_ = {};
//            mapped_range_ = {};
//        }
//
//        void read         (std::span<      T> destination) requires (Read )
//        {
//            const auto range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(destination.size()) }, mapped_range_.count);
//            wait(range), std::memcpy(destination.data(), mapped_data_.data(), range.count * sizeof(T)), lock(range);
//        }
//        void write        (std::span<const T> source     ) requires (Write)
//        {
//            const auto range = gl::clamp_range(gl::range{ static_cast<gl::count_t>(source.size()) }, mapped_range_.count);
//            wait(range), std::memcpy(mapped_data_.data(), source.data(), range.count * sizeof(T)), lock(range);
//        }
//
//        auto operator=    (dynamic_buffer&&) noexcept -> dynamic_buffer& = default;
//
//    private:
//        void lock         (gl::range range)
//        {
//            locks_.emplace_back(gl::fence{}, range);
//        }
//        void wait         (gl::range range)
//        {
//            auto remaining_locks = std::vector<gl::lock_t>{};
//            std::ranges::for_each(locks_, [&](gl::lock_t& lock)
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
//        auto storage_flags() const -> gl::buffer_storage_flags_e
//        {
//            auto storage_flags = gl::buffer_storage_flags_e::persistent | gl::buffer_storage_flags_e::coherent;
//            if constexpr (Read ) storage_flags |= gl::buffer_storage_flags_e::read ;
//            if constexpr (Write) storage_flags |= gl::buffer_storage_flags_e::write;
//
//            return storage_flags;
//        }
//        auto access_flags () const -> gl::buffer_mapping_range_access_flags_e
//        {
//            auto access_flags = gl::buffer_mapping_range_access_flags_e::persistent | gl::buffer_mapping_range_access_flags_e::coherent;
//            if constexpr (Read ) access_flags |= gl::buffer_mapping_range_access_flags_e::read ;
//            if constexpr (Write) access_flags |= gl::buffer_mapping_range_access_flags_e::write;
//
//            return access_flags;
//        }
//
//        std::vector<gl::lock_t> locks_;
//        std::span<T>            mapped_data_;
//        gl::range               mapped_range_;
//    };
//
//    template<typename T>
//    using vertex_buffer = gl::static_buffer<T          >;
//    using index_buffer  = gl::static_buffer<gl::index_t>;
//
//
//
//    template<typename T>
//    class uniform_buffer : public gl::dynamic_buffer<T, gl::false_, gl::true_>
//    {
//    public:
//        uniform_buffer(const T& value)
//            : gl::dynamic_buffer<T, gl::false_, gl::true_>{ std::span<const T>{ &value, 1u } } {}
//
//        void bind(gl::binding_t binding)
//        {
//            gl::bind_buffer_base(this->handle(), gl::buffer_base_target_e::uniform_buffer, binding);
//        }
//    };
//    template<typename T>
//    class uniform_array_buffer : public gl::dynamic_buffer<T, gl::false_, gl::true_>
//    {
//    public:
//        using gl::dynamic_buffer<T>::dynamic_buffer;
//
//        void bind(gl::binding_t binding)
//        {
//            gl::bind_buffer_base(this->handle(), gl::buffer_base_target_e::uniform_buffer, binding);
//        }
//    };
//
//
//
//    template<typename T, gl::buffer_target_e Target, gl::bool_t Read = gl::true_, gl::bool_t Write = gl::true_>
//    class generic_buffer : public gl::dynamic_buffer<T, Read, Write>
//    {
//    public:
//        using gl::dynamic_buffer<T, Read, Write>::dynamic_buffer;
//
//        void bind()
//        {
//            gl::bind_buffer(this->handle(), Target);
//        }
//    };
//
//
//
//    template<typename T>
//    class shader_storage_buffer : public gl::dynamic_buffer<T>
//    {
//    public:
//        using gl::dynamic_buffer<T>::dynamic_buffer;
//
//        void bind(gl::binding_t binding)
//        {
//            gl::bind_buffer_base(this->handle(), gl::buffer_base_target_e::shader_storage_buffer, binding);
//        }
//    };
//    class draw_arrays_indirect_buffer : public gl::dynamic_buffer<gl::draw_arrays_indirect_command>
//    {
//    public:
//        using gl::dynamic_buffer<gl::draw_arrays_indirect_command>::dynamic_buffer;
//
//        void bind()
//        {
//            gl::bind_buffer(handle(), gl::buffer_target_e::draw_indirect_buffer);
//        }
//    };
//    class draw_elements_indirect_buffer : public gl::dynamic_buffer<gl::draw_elements_indirect_command>
//    {
//    public:
//        using gl::dynamic_buffer<gl::draw_elements_indirect_command>::dynamic_buffer;
//
//        void bind()
//        {
//            gl::bind_buffer(handle(), gl::buffer_target_e::draw_indirect_buffer);
//        }
//    };
//
//    //using pixel_pack_buffer   = gl::generic_buffer<gl::byte_t, gl::buffer_target_e::pixel_pack_buffer>;
//
//
//
//    struct texture_data_descriptor
//    {
//        texture_data_descriptor(gl::texture_base_format_e base_format, gl::pixel_data_type_e pixel_data_type, std::span<const gl::byte_t> source)
//            : base_format{ base_format }, pixel_data_type{ pixel_data_type }, source{ source } {}
//
//        gl::texture_base_format_e   base_format;
//        gl::pixel_data_type_e       pixel_data_type;
//        std::span<const gl::byte_t> source;
//    };
//    class pixel_unpack_buffer : public gl::dynamic_buffer<gl::byte_t, gl::false_, gl::true_>
//    {
//    public:
//        pixel_unpack_buffer(gl::size_t size)
//            : gl::dynamic_buffer<gl::byte_t, gl::false_, gl::true_>{ size } {}
//
//        void bind()
//        {
//            gl::bind_buffer(handle(), gl::buffer_target_e::pixel_unpack_buffer);
//        }
//
//        void stream(const gl::texture_data_descriptor& texture_data_descriptor)
//        {
//
//        }
//    };
//}
