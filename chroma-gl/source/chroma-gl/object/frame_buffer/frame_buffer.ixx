export module opengl.object.frame_buffer;

import std;
import opengl;
import opengl.object;
import opengl.object.cubemap;
import opengl.object.render_buffer;
import opengl.object.texture;

export namespace gl
{
    enum class frame_buffer_surface_e
    {
        texture      , 
        cubemap      , 
        render_buffer, 
    };

    struct frame_buffer_specification
    {
        using format_t = std::variant<gl::texture_format_e, gl::render_buffer_format_e>;

        frame_buffer_specification(const gl::string& identifier, gl::frame_buffer_surface_e surface, format_t format)
            : identifier{ identifier }, surface{ surface }, format{ format } {}

        gl::string                 identifier;
        gl::frame_buffer_surface_e surface;
        format_t                   format;
    };
    using frame_buffer_attachment_map_t = std::unordered_map<gl::frame_buffer_attachment_e, gl::frame_buffer_specification>;

    auto map_frame_buffer_attachment(gl::texture_format_e       texture_format      ) -> gl::frame_buffer_attachment_e
    {
        switch (texture_format)
        {
            using enum gl::texture_format_e;

            case depth_uint16_n              :
            case depth_uint24_n              :
            case depth_float32               : return gl::frame_buffer_attachment_e::depth        ;
            case stencil_uint8               : return gl::frame_buffer_attachment_e::stencil      ;
            case depth_stencil_uint24_n_uint8:
            case depth_stencil_float32_uint8 : return gl::frame_buffer_attachment_e::depth_stencil;

            default                          : return gl::frame_buffer_attachment_e::color_0      ;
        }
    }
    auto map_frame_buffer_attachment(gl::render_buffer_format_e render_buffer_format) -> gl::frame_buffer_attachment_e
    {
        switch (render_buffer_format)
        {
            using enum gl::render_buffer_format_e;

            case depth_uint16_n             :
            case depth_uint24_n             :
            case depth_float32              : return gl::frame_buffer_attachment_e::depth        ;
            case stencil_uint8              : return gl::frame_buffer_attachment_e::stencil      ;
            case depth_stencil_uint32_24_8  :
            case depth_stencil_float32_uint8: return gl::frame_buffer_attachment_e::depth_stencil;

            default                         : return gl::frame_buffer_attachment_e::color_0      ;
        }
    }

    class frame_buffer : public gl::object
    {
    public:
        using attachment_e       = gl::frame_buffer_attachment_e;
        using color_attachment_e = gl::frame_buffer_color_attachment_e;
        using source_e           = gl::frame_buffer_source_e;
        using specification_t    = gl::frame_buffer_specification;
        using surface_e          = gl::frame_buffer_surface_e;
        using target_e           = gl::frame_buffer_target_e;

        frame_buffer(const gl::frame_buffer_attachment_map_t attachment_map, const gl::vector_2u& dimensions)
            : gl::object{ gl::create_frame_buffer() }
            , textures_{}, cubemaps_{}, render_buffers_{}, dimensions_{ dimensions }
        {
            auto color_attachments = std::vector<color_attachment_e>{};
            std::ranges::for_each(attachment_map, [&](const auto& iterator)
            {
                const auto& [attachment, specification] = iterator;
                switch (specification.surface)
                {
                    case surface_e::texture      :
                    {
                        const auto format  = std::get<gl::texture_format_e>(specification.format);
                        if (gl::map_frame_buffer_attachment(format) == attachment_e::color_0) color_attachments.emplace_back(static_cast<color_attachment_e>(attachment));

                              auto texture = gl::texture_2d{ format, dimensions_ };
                        gl::frame_buffer_texture(handle(), texture.handle(), attachment, gl::uint32_t{ 0u });
                        textures_.emplace(specification.identifier, std::move(texture));
                    }
                    case surface_e::cubemap      :
                    {
                        const auto format  = std::get<gl::texture_format_e>(specification.format);
                        if (gl::map_frame_buffer_attachment(format) == attachment_e::color_0) color_attachments.emplace_back(static_cast<color_attachment_e>(attachment));

                              auto cubemap = gl::cubemap{ format, dimensions_ };
                        gl::frame_buffer_texture(handle(), cubemap.handle(), attachment, gl::uint32_t{ 0u });
                        cubemaps_.emplace(specification.identifier, std::move(cubemap));
                    }
                    case surface_e::render_buffer:
                    {
                        const auto format        = std::get<gl::render_buffer_format_e>(specification.format);
                        if (gl::map_frame_buffer_attachment(format) == attachment_e::color_0) color_attachments.emplace_back(static_cast<color_attachment_e>(attachment));

                              auto render_buffer = gl::render_buffer{ format, dimensions_ };
                        gl::frame_buffer_render_buffer(handle(), render_buffer.handle(), attachment);
                        render_buffers_.emplace(specification.identifier, std::move(render_buffer));
                    }

                    default                      : throw std::invalid_argument{ "invalid surface" };
                }
            });

            if   (color_attachments.empty())
            {
                gl::frame_buffer_read_buffer(handle(), source_e::none);
                gl::frame_buffer_draw_buffer(handle(), source_e::none);
            }
            else
            {
                auto color_buffer_sources = std::vector<source_e>(color_attachments.size());
                for (const auto [index, color_attachment] : std::views::enumerate(color_attachments))
                {
                    const auto offset = gl::to_underlying(color_attachment - color_attachment_e::color_0);
                    color_buffer_sources.at(index) = source_e::color_0 + offset;
                }
    
                gl::frame_buffer_draw_buffers(handle(), color_buffer_sources);
            }
    
            const auto frame_buffer_status = gl::check_frame_buffer_status(handle());
            if (frame_buffer_status != gl::frame_buffer_status_e::complete) throw std::runtime_error{ "framebuffer not complete" };
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
        template<surface_e Surface = surface_e::texture>
        void bind_surface(const gl::string& identifier, gl::binding_t slot)
        {
                 if constexpr (Surface == surface_e::texture) textures_.at(identifier)->bind(slot);
            else if constexpr (Surface == surface_e::cubemap) cubemaps_.at(identifier)->bind(slot);
            else static_assert(gl::false_ && gl::to_underlying(Surface), "invalid surface");
        }

        template<surface_e Surface = surface_e::texture>
        void read_from   (const gl::string& identifier, color_attachment_e color_attachment, gl::uint32_t image_level)
        {
                 if constexpr (Surface == surface_e::texture)
            {
                auto& texture = textures_.at(identifier);
                gl::frame_buffer_texture    (handle(), texture.handle(), static_cast<attachment_e>(color_attachment), image_level);
                gl::frame_buffer_read_buffer(handle(), static_cast<source_e>(color_attachment));
            }
            else if constexpr (Surface == surface_e::cubemap)
            {
                auto& cubemap = cubemaps_.at(identifier);
                gl::frame_buffer_texture    (handle(), cubemap.handle(), static_cast<attachment_e>(color_attachment), image_level);
                gl::frame_buffer_read_buffer(handle(), static_cast<source_e>(color_attachment));
            }
            else static_assert(gl::false_ && gl::to_underlying(Surface), "invalid surface");
        }
        template<surface_e Surface = surface_e::texture>
        void write_to    (const gl::string& identifier, color_attachment_e color_attachment, gl::uint32_t image_level)
        {
            //if constexpr (Surface == surface_e::texture)
            //{
            //    auto& texture = textures_.at(identifier);
            //    gl::frame_buffer_texture    (handle(), texture.handle(), static_cast<attachment_e>(color_attachment), image_level);
            //    gl::frame_buffer_draw_buffer(handle(), static_cast<source_e>(color_attachment));
            //}
            //else if constexpr (Surface == surface_e::cubemap)
            //{
            //    auto& cubemap = cubemaps_.at(identifier);
            //    gl::frame_buffer_texture(handle(), cubemap.handle(), static_cast<attachment_e>(color_attachment), image_level);
            //    gl::frame_buffer_draw_buffer(handle(), static_cast<source_e>(color_attachment));
            //}
            //else if constexpr (Surface == surface_e::render_buffer)
            //{
            //    auto& render_buffer = render_buffers_.at(identifier);
            //    gl::frame_buffer_render_buffer(handle(), render_buffer.handle(), static_cast<attachment_e>(color_attachment));
            //    gl::frame_buffer_draw_buffer  (handle(), static_cast<source_e>(color_attachment));
            //}
            //else static_assert(gl::false_ && gl::to_underlying(Surface), "invalid surface");
        }

        template<surface_e Surface = surface_e::texture>
        auto surface     (const gl::string& identifier) const -> const auto&
        {
                 if constexpr (Surface == surface_e::texture      ) return textures_      .at(identifier);
            else if constexpr (Surface == surface_e::cubemap      ) return cubemaps_      .at(identifier);
            else if constexpr (Surface == surface_e::render_buffer) return render_buffers_.at(identifier);
        }
        auto dimensions  ()                             const -> const gl::vector_2u&
        {
            return dimensions_;
        }

        auto operator=(frame_buffer&&) noexcept -> frame_buffer& = default;

    private:
        std::unordered_map<gl::string, gl::texture_2d   > textures_;
        std::unordered_map<gl::string, gl::cubemap      > cubemaps_;
        std::unordered_map<gl::string, gl::render_buffer> render_buffers_;
        gl::vector_2u                                     dimensions_;
    };
}
