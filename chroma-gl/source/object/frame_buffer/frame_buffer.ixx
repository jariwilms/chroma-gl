export module chroma_gl:object.frame_buffer;

import std;
import opengl;
import :object;
import :object.cubemap;
import :object.render_buffer;
import :object.texture;

export namespace gl
{
    enum class frame_buffer_surface_e
    {
        texture      , 
        cubemap      , 
        render_buffer, 
    };
    enum class multisample_frame_buffer_surface_e
    {
        texture      , 
        render_buffer, 
    };
    template<typename surface_t = gl::frame_buffer_surface_e>
    struct frame_buffer_specification
    {
        using format_t = std::variant<gl::texture_format_e, gl::render_buffer_format_e>;

        frame_buffer_specification(std::string identifier, surface_t surface, format_t format)
            : identifier{ std::move(identifier) }, surface{ surface }, format{ format } { }

        std::string identifier;
        surface_t   surface;
        format_t    format;
    };
    using frame_buffer_attachment_map_t             = std::map<gl::frame_buffer_attachment_e, gl::frame_buffer_specification<gl::frame_buffer_surface_e            >>;
    using multisample_frame_buffer_attachment_map_t = std::map<gl::frame_buffer_attachment_e, gl::frame_buffer_specification<gl::multisample_frame_buffer_surface_e>>;

    class frame_buffer : public gl::object
    {
    public:
        using attachment_e       = gl::frame_buffer_attachment_e;
        using color_attachment_e = gl::frame_buffer_color_attachment_e;
        using source_e           = gl::frame_buffer_source_e;
        using specification_t    = gl::frame_buffer_specification<gl::frame_buffer_surface_e>;
        using surface_e          = gl::frame_buffer_surface_e;
        using target_e           = gl::frame_buffer_target_e;

        explicit
            frame_buffer(gl::frame_buffer_attachment_map_t const& attachment_map, gl::vector_2u dimensions)
            : gl::object{ gl::create_frame_buffer() }
            , attachment_map_{ attachment_map }
            , textures_{}, cubemaps_{}, render_buffers_{}, dimensions_{ dimensions }
        {
            build(attachment_map_);
        }
        frame_buffer(frame_buffer&&) noexcept = default;
       ~frame_buffer()
        {
            gl::delete_frame_buffer(handle());
        }

        void bind        (target_e target)
        {
            gl::bind_frame_buffer(handle(), target);
        }
        template<surface_e surface_v = surface_e::texture>
        void bind_surface(std::string const& identifier, gl::binding_t slot)
        {
                 if constexpr (surface_v == surface_e::texture) textures_.at(identifier).bind(slot);
            else if constexpr (surface_v == surface_e::cubemap) cubemaps_.at(identifier).bind(slot);
            else static_assert(gl::false_ && gl::to_underlying(surface_v), "invalid surface");
        }

        template<surface_e surface_v = surface_e::texture>
        void attach      (std::string const& identifier, attachment_e attachment, gl::uint32_t image_level = 0u)
        {
                 if constexpr (surface_v == surface_e::texture      ) gl::frame_buffer_texture      (handle(), textures_      .at(identifier).handle(), attachment, image_level);
            else if constexpr (surface_v == surface_e::cubemap      ) gl::frame_buffer_texture      (handle(), cubemaps_      .at(identifier).handle(), attachment, image_level);
            else if constexpr (surface_v == surface_e::render_buffer) gl::frame_buffer_render_buffer(handle(), render_buffers_.at(identifier).handle(), attachment             );
            else static_assert(gl::false_ && gl::to_underlying(surface_v), "invalid surface");
        }

        void read_from   (source_e color_source)
        {
            gl::frame_buffer_read_buffer(handle(), color_source);
        }
        void write_to    (source_e color_source)
        {
            gl::frame_buffer_draw_buffer(handle(), color_source);
        }
        void write_to    (std::span<source_e const> color_sources)
        {
            gl::frame_buffer_draw_buffers(handle(), color_sources);
        }

        template<surface_e surface_v = surface_e::texture>
        void apply       (std::string const& identifier, auto state)
        {
            map_surface<surface_v>().at(identifier).apply(state);
        }

        void resize(gl::vector_2u dimensions)
        {
            if (dimensions == dimensions_) return;

            dimensions_ = dimensions;

            textures_      .clear();
            cubemaps_      .clear();
            render_buffers_.clear();

            build(attachment_map_);
        }

        template<surface_e surface_v = surface_e::texture>
        auto surface     (std::string const& identifier) const -> auto const&
        {
            return map_surface<surface_v>().at(identifier);
        }
        auto dimensions  ()                              const -> gl::vector_2u
        {
            return dimensions_;
        }

        auto operator=   (frame_buffer&&) noexcept -> frame_buffer& = default;

    private:
        template<surface_e surface_v>
        auto map_surface() -> auto&
        {
                 if constexpr (surface_v == surface_e::texture      ) return textures_;
            else if constexpr (surface_v == surface_e::cubemap      ) return cubemaps_;
            else if constexpr (surface_v == surface_e::render_buffer) return render_buffers_;
            else static_assert(gl::false_ && gl::to_underlying(surface_v), "invalid surface");
        }

        void build(gl::frame_buffer_attachment_map_t const& attachment_map)
        {
            auto const color_attachments = build_attachments(attachment_map);
            configure_draw_buffers(color_attachments);
            validate();
        }
        auto build_attachments(gl::frame_buffer_attachment_map_t const& attachment_map) -> std::vector<color_attachment_e>
        {
            auto color_attachments = std::vector<color_attachment_e>{};

            std::ranges::for_each(attachment_map, [&](auto const& iterator)
                {
                    auto const& [attachment, specification] = iterator;
                    switch (specification.surface)
                    {
                        case surface_e::texture      : build_texture_attachment      (attachment, specification, color_attachments); break;
                        case surface_e::cubemap      : build_cubemap_attachment      (attachment, specification, color_attachments); break;
                        case surface_e::render_buffer: build_render_buffer_attachment(attachment, specification, color_attachments); break;

                        default: throw std::invalid_argument{ "invalid surface" };
                    }
                });

            return color_attachments;
        }
        void build_texture_attachment(attachment_e attachment, specification_t const& specification, std::vector<color_attachment_e>& color_attachments)
        {
            auto const format = std::get<gl::texture_format_e>(specification.format);
            track_if_color(format, attachment, color_attachments);

            textures_.emplace(specification.identifier, gl::texture_2d{ format, dimensions_, gl::false_ });
            attach<surface_e::texture>(specification.identifier, attachment, gl::uint32_t{ 0u });
        }
        void build_cubemap_attachment(attachment_e attachment, specification_t const& specification, std::vector<color_attachment_e>& color_attachments)
        {
            auto const format = std::get<gl::texture_format_e>(specification.format);
            track_if_color(format, attachment, color_attachments);

            cubemaps_.emplace(specification.identifier, gl::cubemap{ format, dimensions_, gl::false_ });
            attach<surface_e::cubemap>(specification.identifier, attachment, gl::uint32_t{ 0u });
        }
        void build_render_buffer_attachment(attachment_e attachment, specification_t const& specification, std::vector<color_attachment_e>& color_attachments)
        {
            auto const format = std::get<gl::render_buffer_format_e>(specification.format);
            track_if_color(format, attachment, color_attachments);

            render_buffers_.emplace(specification.identifier, gl::render_buffer{ format, dimensions_ });
            attach<surface_e::render_buffer>(specification.identifier, attachment);
        }
        template<typename format_t>
        void track_if_color(format_t format, attachment_e attachment, std::vector<color_attachment_e>& color_attachments)
        {
            if (gl::map_frame_buffer_attachment(format) == attachment_e::color_0)
            {
                color_attachments.emplace_back(static_cast<color_attachment_e>(attachment));
            }
        }
        void configure_draw_buffers(std::vector<color_attachment_e> const& color_attachments)
        {
            if (color_attachments.empty())
            {
                read_from(source_e::none);
                write_to(source_e::none);
                return;
            }

            auto color_buffer_sources = std::vector<source_e>(color_attachments.size());
            for (auto const [color_index, color_attachment] : std::views::enumerate(color_attachments))
            {
                auto const offset = gl::to_underlying(color_attachment - color_attachment_e::color_0);
                color_buffer_sources.at(color_index) = source_e::color_0 + offset;
            }

            write_to(color_buffer_sources);
        }
        void validate()
        {
            auto const frame_buffer_status = gl::check_frame_buffer_status(handle(), gl::frame_buffer_target_e::read_write);
            if (frame_buffer_status != gl::frame_buffer_status_e::complete) throw std::runtime_error{ "frame buffer status not complete" };
        }

        gl::frame_buffer_attachment_map_t                  attachment_map_;
        std::unordered_map<std::string, gl::texture_2d   > textures_;
        std::unordered_map<std::string, gl::cubemap      > cubemaps_;
        std::unordered_map<std::string, gl::render_buffer> render_buffers_;
        gl::vector_2u                                      dimensions_;
    };
    //class multisample_frame_buffer : public gl::object
    //{
    //public:
    //    using attachment_e       = gl::frame_buffer_attachment_e;
    //    using color_attachment_e = gl::frame_buffer_color_attachment_e;
    //    using source_e           = gl::frame_buffer_source_e;
    //    using specification_t    = gl::frame_buffer_specification<gl::multisample_frame_buffer_surface_e>;
    //    using surface_e          = gl::multisample_frame_buffer_surface_e;
    //    using target_e           = gl::frame_buffer_target_e;

    //    explicit
    //    multisample_frame_buffer(gl::multisample_frame_buffer_attachment_map_t const& attachment_map, gl::vector_2u dimensions, gl::uint32_t sample_count)
    //        : gl::object{ gl::create_frame_buffer() }
    //        , textures_{}, render_buffers_{}, dimensions_{ dimensions }, sample_count_{ sample_count }
    //    {
    //        auto color_attachments = std::vector<color_attachment_e>{};
    //        std::ranges::for_each(attachment_map, [&](auto const& iterator)
    //        {
    //                auto const& [attachment, specification] = iterator;
    //            switch (specification.surface)
    //            {
    //                case surface_e::texture      :
    //                {
    //                    auto const format  = std::get<gl::texture_format_e>(specification.format);
    //                    if (gl::map_frame_buffer_attachment(format) == attachment_e::color_0) color_attachments.emplace_back(static_cast<color_attachment_e>(attachment));

    //                    textures_.emplace(specification.identifier, gl::multisample_texture_2d{ format, dimensions_, sample_count_ });
    //                    attach<surface_e::texture>(specification.identifier, attachment, gl::uint32_t{ 0u });
    //                }
    //                case surface_e::render_buffer:
    //                {
    //                    auto const format        = std::get<gl::render_buffer_format_e>(specification.format);
    //                    if (gl::map_frame_buffer_attachment(format) == attachment_e::color_0) color_attachments.emplace_back(static_cast<color_attachment_e>(attachment));

    //                    render_buffers_.emplace(specification.identifier, gl::multisample_render_buffer{ format, dimensions_, sample_count_ });
    //                    attach<surface_e::render_buffer>(specification.identifier, attachment);
    //                }

    //                default: throw std::invalid_argument{ "invalid surface" };
    //            }
    //        });

    //        if   (color_attachments.empty())
    //        {
    //            read_from(source_e::none);
    //            write_to (source_e::none);
    //        }
    //        else
    //        {
    //            auto color_buffer_sources = std::vector<source_e>(color_attachments.size());
    //            for (auto const [color_index, color_attachment] : std::views::enumerate(color_attachments))
    //            {
    //                auto const offset = gl::to_underlying(color_attachment - color_attachment_e::color_0);
    //                color_buffer_sources.at(color_index) = source_e::color_0 + offset;
    //            }
    //
    //            write_to(color_buffer_sources);
    //        }
    //
    //        auto const frame_buffer_status = gl::check_frame_buffer_status(handle(), gl::frame_buffer_target_e::read_write);
    //        if (frame_buffer_status != gl::frame_buffer_status_e::complete) throw std::runtime_error{ "frame buffer status not complete" };
    //    }
    //    multisample_frame_buffer(multisample_frame_buffer&&) noexcept = default;
    //   ~multisample_frame_buffer()
    //    {
    //        gl::delete_frame_buffer(handle());
    //    }

    //    void bind        (target_e target)
    //    {
    //        gl::bind_frame_buffer(handle(), target);
    //    }
    //    template<surface_e surface_v = surface_e::texture>
    //    void bind_surface(std::string const& identifier, gl::binding_t slot)
    //    {
    //        if   constexpr (surface_v == surface_e::texture) textures_.at(identifier).bind(slot);
    //        else static_assert(gl::false_ && gl::to_underlying(surface_v), "invalid surface");
    //    }

    //    template<surface_e surface_v = surface_e::texture>
    //    void attach      (std::string const& identifier, attachment_e attachment, gl::uint32_t image_level = 0u)
    //    {
    //             if constexpr (surface_v == surface_e::texture      ) gl::frame_buffer_texture      (handle(), textures_      .at(identifier).handle(), attachment, image_level);
    //        else if constexpr (surface_v == surface_e::render_buffer) gl::frame_buffer_render_buffer(handle(), render_buffers_.at(identifier).handle(), attachment             );
    //        else static_assert(gl::false_ && gl::to_underlying(surface_v), "invalid surface");
    //    }

    //    void read_from   (source_e color_source)
    //    {
    //        gl::frame_buffer_read_buffer(handle(), color_source);
    //    }
    //    void write_to    (source_e color_source)
    //    {
    //        gl::frame_buffer_draw_buffer(handle(), color_source);
    //    }
    //    void write_to    (std::span<source_e const> color_sources)
    //    {
    //        gl::frame_buffer_draw_buffers(handle(), color_sources);
    //    }

    //    template<surface_e surface_v = surface_e::texture>
    //    auto surface(std::string const& identifier) const -> auto const&
    //    {
    //        return map_surface<surface_v>().at(identifier);
    //    }
    //    auto dimensions  ()                              const -> gl::vector_2u
    //    {
    //        return dimensions_;
    //    }
    //    auto sample_count()                              const -> gl::uint32_t
    //    {
    //        return sample_count_;
    //    }

    //    auto operator=(multisample_frame_buffer&&) noexcept -> multisample_frame_buffer& = default;

    //private:
    //    template<surface_e surface_v>
    //    auto map_surface() -> auto&
    //    {
    //             if constexpr (surface_v == surface_e::texture      ) return textures_;
    //        else if constexpr (surface_v == surface_e::render_buffer) return render_buffers_;
    //        else static_assert(gl::false_ && gl::to_underlying(surface_v), "invalid surface");
    //    }

    //    std::unordered_map<std::string, gl::multisample_texture_2d   > textures_;
    //    std::unordered_map<std::string, gl::multisample_render_buffer> render_buffers_;
    //    gl::vector_2u                                                  dimensions_;
    //    gl::uint32_t                                                   sample_count_;
    //};
}
