export module chroma_gl:object.buffer;

import std;
import opengl;
import :object;
import :object.fence;
import :object.memory_lock;

export namespace gl
{
    template<typename derived_t, typename element_t>
    struct dynamic_upload
    {
        void upload(element_t const& element         , gl::index_t offset = 0u)
        {
            upload(std::span<element_t const>{ &element, 1u }, offset);
        }
        void upload(std::span<element_t const> memory, gl::index_t offset = 0u)
        {
            auto      & derived       = static_cast<derived_t&>(*this);
            auto const  upload_range  = gl::clamp_range(gl::range_t{ offset, memory.size() }, derived.count());
            if (upload_range.is_empty()) return;

            auto        mapped_memory = gl::map_buffer_range<element_t>(derived.handle(), gl::buffer_mapping_range_access_flags_e::write, upload_range);
            std::memcpy(mapped_memory.data() + upload_range.index, memory.data(), upload_range.count * sizeof(element_t));
            gl::unmap_buffer(derived.handle());
        }
    };
    template<typename derived_t, typename element_t>
    struct dynamic_download
    {
        void download(element_t& element         , gl::index_t offset = 0u)
        {
            download(std::span<element_t>{ &element, 1u }, offset);
        }
        void download(std::span<element_t> memory, gl::index_t offset = 0u)
        {
            auto      & derived        = static_cast<derived_t&>(*this);
            auto const  download_range = gl::clamp_range(gl::range_t{ offset, memory.size() }, derived.count());
            if (download_range.is_empty()) return;

            auto        mapped_memory  = gl::map_buffer_range<element_t>(derived.handle(), gl::buffer_mapping_range_access_flags_e::read, download_range);
            std::memcpy(memory.data(), mapped_memory.data() + download_range.index, download_range.count * sizeof(element_t));
            gl::unmap_buffer(derived.handle());
        }
    };

    template<typename derived_t, typename element_t, gl::bool_t upload_v, gl::bool_t download_v> struct dynamic_transfer_traits;
    template<typename derived_t, typename element_t> struct dynamic_transfer_traits<derived_t, element_t, gl::true_ , gl::false_> { using  type =        gl::dynamic_upload<derived_t, element_t>                                                      ; };
    template<typename derived_t, typename element_t> struct dynamic_transfer_traits<derived_t, element_t, gl::false_, gl::true_ > { using  type =                                                         gl::dynamic_download<derived_t, element_t>   ; };
    template<typename derived_t, typename element_t> struct dynamic_transfer_traits<derived_t, element_t, gl::true_ , gl::true_ > { struct type : public gl::dynamic_upload<derived_t, element_t>, public gl::dynamic_download<derived_t, element_t> {}; };
    template<typename derived_t, typename element_t, gl::bool_t upload_v, gl::bool_t download_v> using dynamic_transfer_t = dynamic_transfer_traits<derived_t, element_t, upload_v, download_v>::type;



    template<typename derived_t, typename element_t>
    struct persistent_upload
    {
        void upload(std::span<element_t const> memory, gl::index_t offset = 0u)
        {
            auto      & derived      = static_cast<derived_t&>(*this);
            auto const  upload_range = gl::clamp_range(gl::range_t{ offset, memory.size() }, derived.count());
            if (upload_range.is_empty()) return;

            derived.memory_locker_.wait(upload_range);
            std::memcpy(derived.mapped_memory_.data() + upload_range.index, memory.data(), upload_range.count * sizeof(element_t));
            derived.memory_locker_.lock(upload_range);
        }
    };
    template<typename derived_t, typename element_t>
    struct persistent_download
    {
        void download(std::span<element_t> memory, gl::index_t offset = 0u)
        {
            auto      & derived        = static_cast<derived_t&>(*this);
            auto const  download_range = gl::clamp_range(gl::range_t{ offset, memory.size() }, derived.count());
            if (download_range.is_empty()) return;

            derived.memory_locker_.wait(download_range);
            std::memcpy(memory.data(), derived.mapped_memory_.data() + download_range.index, download_range.count * sizeof(element_t));
            derived.memory_locker_.lock(download_range);
        }
    };

    template<typename derived_t, typename element_t, gl::bool_t upload_v, gl::bool_t download_v> struct persistent_transfer_traits;
    template<typename derived_t, typename element_t> struct persistent_transfer_traits<derived_t, element_t, gl::true_ , gl::false_> { using  type =        gl::persistent_upload<derived_t, element_t>                                                         ; };
    template<typename derived_t, typename element_t> struct persistent_transfer_traits<derived_t, element_t, gl::false_, gl::true_ > { using  type =                                                            gl::persistent_download<derived_t, element_t>   ; };
    template<typename derived_t, typename element_t> struct persistent_transfer_traits<derived_t, element_t, gl::true_ , gl::true_ > { struct type : public gl::persistent_upload<derived_t, element_t>, public gl::persistent_download<derived_t, element_t> {}; };
    template<typename derived_t, typename element_t, gl::bool_t upload_v, gl::bool_t download_v> using persistent_transfer_t = persistent_transfer_traits<derived_t, element_t, upload_v, download_v>::type;



    template<typename derived_t, gl::none_t                       >
    class non_bindable_buffer
    {

    };
    template<typename derived_t, gl::buffer_target_e      target_v>
    class bindable_buffer
    {
    public:
        void bind  ()
        {
            auto& derived = static_cast<derived_t&>(*this);
            gl::bind_buffer(derived.handle(), target_v);
        }
        void unbind()
        {
            gl::bind_buffer(gl::null_object, target_v);
        }
    };
    template<typename derived_t, gl::buffer_base_target_e target_v>
    class base_bindable_buffer
    {
    public:
        void bind(gl::binding_t binding)
        {
            auto& derived = static_cast<derived_t&>(*this);
            gl::bind_buffer_base(derived.handle(), target_v, binding);
        }
    };

    template<typename target_t> struct bindable_buffer_traits;
    template<> struct bindable_buffer_traits<gl::none_t              > { template<typename derived_t, gl::none_t               target_v> using type = gl::non_bindable_buffer <derived_t, target_v>; };
    template<> struct bindable_buffer_traits<gl::buffer_target_e     > { template<typename derived_t, gl::buffer_target_e      target_v> using type = gl::bindable_buffer     <derived_t, target_v>; };
    template<> struct bindable_buffer_traits<gl::buffer_base_target_e> { template<typename derived_t, gl::buffer_base_target_e target_v> using type = gl::base_bindable_buffer<derived_t, target_v>; };
    template<typename derived_t, auto binding_v> using bindable_buffer_t = typename bindable_buffer_traits<decltype(binding_v)>::template type<derived_t, binding_v>;





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
    template<typename element_t, auto binding_v = gl::none>
    class static_buffer 
        : public gl::buffer
        , public gl::bindable_buffer_t<gl::static_buffer<element_t, binding_v>, binding_v>
    {
    public:
        explicit
        static_buffer(std::span<element_t const> memory)
            : gl::buffer{ memory.size(), sizeof(element_t) }
        {
            gl::buffer_storage<element_t>(handle(), gl::buffer_storage_flags_e::static_, memory);
        }
    };
    template<typename element_t, gl::bool_t upload_v = gl::true_, gl::bool_t download_v = gl::true_, auto binding_v = gl::none>
    class dynamic_buffer 
        : public gl::buffer
        , public gl::dynamic_transfer_t<gl::dynamic_buffer<element_t, upload_v, download_v, binding_v>, element_t, upload_v, download_v>
        , public gl::bindable_buffer_t <gl::dynamic_buffer<element_t, upload_v, download_v, binding_v>, binding_v>
    {
    public:
        explicit
        dynamic_buffer(gl::count_t element_count)
            : gl::buffer{ element_count, sizeof(element_t) }
        {
            auto buffer_storage_flags = gl::buffer_storage_flags_e{};
            if constexpr (upload_v  ) buffer_storage_flags |= gl::buffer_storage_flags_e::write;
            if constexpr (download_v) buffer_storage_flags |= gl::buffer_storage_flags_e::read;

            gl::buffer_storage<element_t>(handle(), buffer_storage_flags, element_count);
        }

    private:
        friend struct gl::dynamic_upload  <dynamic_buffer, element_t>;
        friend struct gl::dynamic_download<dynamic_buffer, element_t>;
    };
    template<typename element_t, gl::bool_t upload_v = gl::true_, gl::bool_t download_v = gl::true_, auto binding_v = gl::none>
    class persistent_buffer 
        : public gl::buffer
        , public gl::persistent_transfer_t<gl::persistent_buffer<element_t, upload_v, download_v, binding_v>, element_t, upload_v, download_v>
        , public gl::bindable_buffer_t    <gl::persistent_buffer<element_t, upload_v, download_v, binding_v>, binding_v>
    {
    public:
        explicit
        persistent_buffer(gl::count_t element_count)
            : gl::buffer{ element_count, sizeof(element_t) }
            , mapped_memory_{}, memory_locker_{}
        {
            auto storage_flags              = gl::buffer_storage_flags_e::persistent | gl::buffer_storage_flags_e::coherent;
            if constexpr (upload_v  ) storage_flags |= gl::buffer_storage_flags_e::write;
            if constexpr (download_v) storage_flags |= gl::buffer_storage_flags_e::read;

            auto mapping_range_access_flags = gl::buffer_mapping_range_access_flags_e::persistent | gl::buffer_mapping_range_access_flags_e::coherent;
            if constexpr (upload_v  ) mapping_range_access_flags |= gl::buffer_mapping_range_access_flags_e::write;
            if constexpr (download_v) mapping_range_access_flags |= gl::buffer_mapping_range_access_flags_e::read;

                             gl::buffer_storage  <element_t>(handle(), storage_flags             , element_count);
            mapped_memory_ = gl::map_buffer_range<element_t>(handle(), mapping_range_access_flags, count()      );
        }

    private:
        friend struct gl::persistent_upload  <persistent_buffer, element_t>;
        friend struct gl::persistent_download<persistent_buffer, element_t>;

        std::span<element_t> mapped_memory_;
        gl::memory_locker    memory_locker_;
    };
    template<typename element_t, auto binding_v = gl::none>
    class partition_buffer : private gl::persistent_buffer<element_t, gl::true_, gl::false_, binding_v>
    {
    public:
        explicit
        partition_buffer(gl::count_t partition_count, gl::count_t partition_element_count)
            : gl::persistent_buffer<element_t, gl::true_, gl::false_, binding_v>{ partition_count * partition_element_count }
            , partition_count_{ partition_count }, partition_element_count_{ partition_element_count }, partition_index_{ 0u } {}

        void upload(std::span<element_t const> memory)
        {
            auto const partition_offset = partition_index_ * partition_element_count_;
            gl::persistent_buffer<element_t, gl::true_, gl::false_, binding_v>::upload(memory, partition_offset);
            
            ++partition_index_ %= partition_count_;
        }

    private:
        gl::count_t partition_count_;
        gl::count_t partition_element_count_;
        gl::index_t partition_index_;
    };





    template<typename element_t> 
    using vertex_buffer         = gl::static_buffer<element_t>;
    using index_buffer          = gl::static_buffer<gl::uint32_t>;

    template<typename element_t>
    using uniform_buffer        = gl::dynamic_buffer   <element_t, gl::true_ , gl::false_, gl::buffer_base_target_e::uniform_buffer       >;
    template<typename element_t, gl::bool_t upload_v = gl::true_, gl::bool_t download_v = gl::true_>
    using shader_storage_buffer = gl::persistent_buffer<element_t, upload_v  , download_v, gl::buffer_base_target_e::shader_storage_buffer>;

    template<typename element_t, auto binding_v = gl::none> 
    using shared_buffer         = gl::persistent_buffer<element_t, gl::true_ , gl::true_ , binding_v>;
    template<typename element_t, auto binding_v = gl::none> 
    using stream_buffer         = gl::persistent_buffer<element_t, gl::true_ , gl::false_, binding_v>;
    template<typename element_t, auto binding_v = gl::none> 
    using result_buffer         = gl::persistent_buffer<element_t, gl::false_, gl::true_ , binding_v>;

    using pixel_pack_buffer     = gl::result_buffer<gl::byte_t                        , gl::buffer_target_e::pixel_pack_buffer   >;
    using pixel_unpack_buffer   = gl::stream_buffer<gl::byte_t                        , gl::buffer_target_e::pixel_unpack_buffer >;
    using draw_indirect_buffer  = gl::stream_buffer<gl::draw_elements_indirect_command, gl::buffer_target_e::draw_indirect_buffer>;
}
