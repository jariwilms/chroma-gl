export module opengl.object.buffer;

import std;
import opengl;
import opengl.object;
import opengl.object.fence;
import opengl.object.memory_lock;

export namespace gl
{
    class buffer : public gl::object
    {
    public:
        buffer(buffer&&) noexcept = default;
       ~buffer()
        {
            gl::delete_buffer(handle());
        }

        auto count() const -> gl::count_t
        {
            return element_count_;
        }
        auto size () const -> gl::size_t
        {
            return element_count_ * element_size_;
        }

        auto operator=(buffer&&) noexcept -> buffer& = default;

    protected:
        explicit
        buffer(gl::count_t element_count, gl::size_t element_size)
            : gl::object{ gl::create_buffer() }
            , element_count_{ element_count }, element_size_{ element_size } {}

    private:
        gl::count_t element_count_;
        gl::size_t  element_size_;
    };
    template<typename T>
    class static_buffer : public gl::buffer
    {
    public:
        explicit
        static_buffer(std::span<const T> memory)
            : gl::buffer{ memory.size(), sizeof(T) }
        {
            gl::buffer_storage<T>(handle(), gl::buffer_storage_flags_e::static_, memory);
        }
    };





    template<typename Derived, typename T>
    struct dynamic_upload
    {
        void upload(std::span<const T> memory, gl::index_t offset = 0u)
        {
                  auto& derived      = static_cast<Derived&>(*this);
            const auto  upload_range = gl::clamp_range(gl::range_t{ offset, memory.size() }, derived.count());
            if (upload_range.empty()) return;

            auto mapped_memory       = gl::map_buffer_range<T>(derived.handle(), gl::buffer_mapping_range_access_flags_e::write, upload_range);
            std::memcpy(mapped_memory.data() + upload_range.index, memory.data(), upload_range.count * sizeof(T));
            gl::unmap_buffer(derived.handle());
        }
    };
    template<typename Derived, typename T>
    struct dynamic_download
    {
        void download(std::span<T> memory, gl::index_t offset = 0u)
        {
                  auto& derived        = static_cast<Derived&>(*this);
            const auto  download_range = gl::clamp_range(gl::range_t{ offset, memory.size() }, derived.count());
            if (download_range.empty()) return;

            auto mapped_memory         = gl::map_buffer_range<T>(derived.handle(), gl::buffer_mapping_range_access_flags_e::read, download_range);
            std::memcpy(memory.data(), mapped_memory.data() + download_range.index, download_range.count * sizeof(T));
            gl::unmap_buffer(derived.handle());
        }
    };

    template<typename Derived, typename T, gl::bool_t Upload, gl::bool_t Download> struct dynamic_transfer;
    template<typename Derived, typename T> struct dynamic_transfer<Derived, T, gl::true_ , gl::false_> { using  type =        gl::dynamic_upload<Derived, T>                                            ; };
    template<typename Derived, typename T> struct dynamic_transfer<Derived, T, gl::false_, gl::true_ > { using  type =                                               gl::dynamic_download<Derived, T>   ; };
    template<typename Derived, typename T> struct dynamic_transfer<Derived, T, gl::true_ , gl::true_ > { struct type : public gl::dynamic_upload<Derived, T>, public gl::dynamic_download<Derived, T> {}; };

    template<typename T, gl::bool_t Upload = gl::true_, gl::bool_t Download = gl::true_>
    class dynamic_buffer : public gl::buffer, public gl::dynamic_transfer<gl::dynamic_buffer<T, Upload, Download>, T, Upload, Download>::type
    {
    public:
        explicit
        dynamic_buffer(gl::count_t element_count)
            : gl::buffer{ element_count, sizeof(T) }
        {
            auto buffer_storage_flags = gl::buffer_storage_flags_e{};
            if constexpr (Upload  ) buffer_storage_flags |= gl::buffer_storage_flags_e::write;
            if constexpr (Download) buffer_storage_flags |= gl::buffer_storage_flags_e::read;

            gl::buffer_storage<T>(handle(), buffer_storage_flags, element_count);
        }

    private:
        friend struct gl::dynamic_upload  <dynamic_buffer, T>;
        friend struct gl::dynamic_download<dynamic_buffer, T>;
    };



    template<typename Derived, typename T>
    struct persistent_upload
    {
        void upload(std::span<const T> memory, gl::index_t offset = 0u)
        {
                  auto& derived      = static_cast<Derived&>(*this);
            const auto  upload_range = gl::clamp_range(gl::range_t{ offset, memory.size() }, derived.count());
            if (upload_range.empty()) return;

            derived.memory_locker_.wait(upload_range);
            std::memcpy(derived.mapped_memory_.data() + upload_range.index, memory.data(), upload_range.count * sizeof(T));
            derived.memory_locker_.lock(upload_range);
        }
    };
    template<typename Derived, typename T>
    struct persistent_download
    {
        void download(std::span<T> memory, gl::index_t offset = 0u)
        {
                  auto& derived        = static_cast<Derived&>(*this);
            const auto  download_range = gl::clamp_range(gl::range_t{ offset, memory.size() }, derived.count());
            if (download_range.empty()) return;

            derived.memory_locker_.wait(download_range);
            std::memcpy(memory.data(), derived.mapped_memory_.data() + download_range.index, download_range.count * sizeof(T));
            derived.memory_locker_.lock(download_range);
        }
    };

    template<typename Derived, typename T, gl::bool_t Upload, gl::bool_t Download> struct persistent_transfer;
    template<typename Derived, typename T> struct persistent_transfer<Derived, T, gl::true_ , gl::false_> { using  type =        gl::persistent_upload<Derived, T>                                               ; };
    template<typename Derived, typename T> struct persistent_transfer<Derived, T, gl::false_, gl::true_ > { using  type =                                                  gl::persistent_download<Derived, T>   ; };
    template<typename Derived, typename T> struct persistent_transfer<Derived, T, gl::true_ , gl::true_ > { struct type : public gl::persistent_upload<Derived, T>, public gl::persistent_download<Derived, T> {}; };

    template<typename T, gl::bool_t Upload = gl::true_, gl::bool_t Download = gl::true_>
    class persistent_buffer : public gl::buffer, public gl::persistent_transfer<gl::persistent_buffer<T, Upload, Download>, T, Upload, Download>::type
    {
    public:
        explicit
        persistent_buffer(gl::count_t element_count)
            : gl::buffer{ element_count, sizeof(T) }
            , mapped_memory_{}, memory_locker_{}
        {
            auto storage_flags              = gl::buffer_storage_flags_e::persistent | gl::buffer_storage_flags_e::coherent;
            if constexpr (Upload  ) storage_flags |= gl::buffer_storage_flags_e::write;
            if constexpr (Download) storage_flags |= gl::buffer_storage_flags_e::read;

            auto mapping_range_access_flags = gl::buffer_mapping_range_access_flags_e::persistent | gl::buffer_mapping_range_access_flags_e::coherent;
            if constexpr (Upload  ) mapping_range_access_flags |= gl::buffer_mapping_range_access_flags_e::write;
            if constexpr (Download) mapping_range_access_flags |= gl::buffer_mapping_range_access_flags_e::read;

                             gl::buffer_storage  <T>(handle(), storage_flags             , element_count);
            mapped_memory_ = gl::map_buffer_range<T>(handle(), mapping_range_access_flags, count()      );
        }

    private:
        friend struct gl::persistent_upload  <persistent_buffer<T, Upload, Download>, T>;
        friend struct gl::persistent_download<persistent_buffer<T, Upload, Download>, T>;

        std::span<T>      mapped_memory_;
        gl::memory_locker memory_locker_;
    };



    template<typename T, auto Target>
    class bindable_buffer;
    template<typename T, auto Target> requires (std::is_same_v<decltype(Target), gl::buffer_target_e     >)
    class bindable_buffer<T, Target> : public T
    {
    public:
        using T::T;

        void bind  ()
        {
            gl::bind_buffer(T::handle(), Target);
        }
        void unbind()
        {
            gl::bind_buffer(gl::null_object, Target);
        }
    };
    template<typename T, auto Target> requires (std::is_same_v<decltype(Target), gl::buffer_base_target_e>)
    class bindable_buffer<T, Target> : public T
    {
    public:
        using T::T;

        void bind(gl::binding_t binding)
        {
            gl::bind_buffer_base(T::handle(), Target, binding);
        }
    };



    template<typename T> 
    using vertex_buffer         = gl::static_buffer<T>;
    using index_buffer          = gl::static_buffer<gl::uint32_t>;

    template<typename T>
    using uniform_buffer        = gl::bindable_buffer<gl::dynamic_buffer<T, gl::true_, gl::false_>, gl::buffer_base_target_e::uniform_buffer>;
    template<typename T, gl::bool_t Upload = gl::true_, gl::bool_t Download = gl::true_>
    using shader_storage_buffer = gl::bindable_buffer<gl::persistent_buffer<T, Upload, Download>, gl::buffer_base_target_e::shader_storage_buffer>;

    template<typename T> 
    using shared_buffer         = gl::shader_storage_buffer<T, gl::true_ , gl::true_ >;
    template<typename T> 
    using stream_buffer         = gl::shader_storage_buffer<T, gl::true_ , gl::false_>;
    template<typename T> 
    using result_buffer         = gl::shader_storage_buffer<T, gl::false_, gl::true_ >;

    using pixel_unpack_buffer   = gl::bindable_buffer<gl::stream_buffer<gl::byte_t                        >, gl::buffer_target_e::pixel_unpack_buffer >;
    using pixel_pack_buffer     = gl::bindable_buffer<gl::result_buffer<gl::byte_t                        >, gl::buffer_target_e::pixel_pack_buffer   >;
    using draw_indirect_buffer  = gl::bindable_buffer<gl::stream_buffer<gl::draw_elements_indirect_command>, gl::buffer_target_e::draw_indirect_buffer>;





    template<typename T>
    class partition_buffer : private gl::stream_buffer<T>
    {
    public:
        explicit
        partition_buffer(gl::count_t partition_count, gl::count_t partition_element_count)
            : gl::stream_buffer<T>{ partition_count * partition_element_count }
            , partition_count_{ partition_count }, partition_element_count_{ partition_element_count }, partition_index_{ 0u } {}

        void upload(std::span<const T> memory)
        {
            const auto partition_offset = partition_index_ * partition_element_count_;
            gl::stream_buffer<T>::upload(memory, partition_offset);
            
            ++partition_index_ %= partition_count_;
        }

    private:
        gl::count_t partition_count_;
        gl::count_t partition_element_count_;
        gl::index_t partition_index_;
    };
}
