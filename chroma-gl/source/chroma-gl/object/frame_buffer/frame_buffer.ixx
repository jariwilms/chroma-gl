export module opengl.object.frame_buffer;

import std;
import opengl;
import opengl.object.cubemap;
import opengl.object.render_buffer;
import opengl.object.texture;

export namespace gl
{
    enum class attachment_e
    {
        color0, 
        color1, 
        color2, 
        color3, 
        color4, 
        color5, 
        color6, 
        color7, 
        depth, 
        stencil, 
        depth_stencil, 
    };
    enum class surface_e
    {
        texture,
        cubemap,
        render_buffer,
    };
    enum class target_e
    {
        read,
        write,
    };

    struct     specification
    {
        using format_v = std::variant<gl::texture2d::format_e, gl::cubemap::format_e, gl::render_buffer::format_e>;

        specification(const std::string& identifier, format_v format)
            : identifier{ identifier }, format{ format } {}

        std::string identifier;
        format_v    format;
    };
    struct     specification_ms
    {
        using format_v = std::variant<gl::texture2d::format_e, gl::render_buffer::format_e>;

        specification_ms(const std::string& identifier, format_v format)
            : identifier{ identifier }, format{ format } {}

        std::string identifier;
        format_v    format;
    };
    
    //TODO: make private?
    auto map_texture_attachment      (gl::texture2d::format_e     format, gl::uint32_t& color_index) -> gl::frame_buffer_attachment_e
        {
            switch (format)
            {
                case gl::texture2d::format_e::d16_unorm        :
                case gl::texture2d::format_e::d24_unorm        :
                case gl::texture2d::format_e::d32_float        : return gl::frame_buffer_attachment_e::depth        ;
                case gl::texture2d::format_e::d24_unorm_s8_uint:
                case gl::texture2d::format_e::d32_float_s8_uint: return gl::frame_buffer_attachment_e::depth_stencil;
                case gl::texture2d::format_e::s8_uint          : return gl::frame_buffer_attachment_e::stencil      ;

                default: return gl::frame_buffer_attachment_e::color_0 + color_index++;
            }
        };
    auto map_cubemap_attachment      (gl::cubemap::format_e       format, gl::uint32_t& color_index) -> gl::frame_buffer_attachment_e
    {
        switch (format)
        {
            case gl::cubemap::format_e::d16_unorm        :
            case gl::cubemap::format_e::d24_unorm        :
            case gl::cubemap::format_e::d32_float        : return gl::frame_buffer_attachment_e::depth        ;
            case gl::cubemap::format_e::d24_unorm_s8_uint:
            case gl::cubemap::format_e::d32_float_s8_uint: return gl::frame_buffer_attachment_e::depth_stencil;
            case gl::cubemap::format_e::s8_uint          : return gl::frame_buffer_attachment_e::stencil      ;

            default: return gl::frame_buffer_attachment_e::color_0 + color_index++;
        }
    };
    auto map_render_buffer_attachment(gl::render_buffer::format_e format, gl::uint32_t& color_index) -> gl::frame_buffer_attachment_e
    {
        switch (format)
        {
            case gl::render_buffer::format_e::d16_unorm        :
            case gl::render_buffer::format_e::d24_unorm        :
            case gl::render_buffer::format_e::d32_float        : return gl::frame_buffer_attachment_e::depth        ;
            case gl::render_buffer::format_e::d24_unorm_s8_uint:
            case gl::render_buffer::format_e::d32_float_s8_uint: return gl::frame_buffer_attachment_e::depth_stencil;
            case gl::render_buffer::format_e::s8_uint          : return gl::frame_buffer_attachment_e::stencil      ;

            default: return gl::frame_buffer_attachment_e::color_0 + color_index++;
        }
    };

    class frame_buffer : public gl::object
    {
    public:
        using attachment_e    = gl::frame_buffer_attachment_e;
        using specification_t = gl::specification;
        using surface_e       = gl::surface_e;
        using target_e        = gl::frame_buffer_target_e;

        frame_buffer()
            : gl::object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, texture_map_{}, cubemap_map_{}, render_buffer_map_{}, dimensions_{} {}
        frame_buffer(const gl::vector2u& dimensions, std::span<const specification_t> specifications)
            : gl::object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
            , attachments_{}, texture_map_{}, cubemap_map_{}, render_buffer_map_{}, dimensions_{ dimensions }
        {
            auto color_index = gl::uint32_t{ 0u };
            std::ranges::for_each(specifications, [&](const auto& specification)
                {
                    const auto& [identifier, format] = specification;
                    const auto  overload             = gl::overload_t
                    {
                        [&](gl::texture_format_e format)
                        {
                            auto texture    = std::make_shared<gl::texture2d>(format, gl::texture2d::filter_e::none, gl::texture2d::wrapping_e::repeat, dimensions_);
                            auto attachment = map_texture_attachment(texture->format(), color_index);

                            attach(identifier, attachment, texture);
                        }, 
                        [&](gl::cubemap_format_e format)
                        {
                            const auto texture_format = std::bit_cast<gl::texture_format_e>(format);
                                  auto cubemap        = std::make_shared<gl::cubemap>(texture_format, gl::cubemap::filter_e::none, gl::cubemap::wrapping_e::repeat, dimensions_);
                                  auto attachment     = map_cubemap_attachment(cubemap->format(), color_index);

                            attach(identifier, attachment, cubemap);
                        }, 
                        [&](gl::render_buffer_format_e format)
                        {
                            auto render_buffer = std::make_shared<gl::render_buffer>(format, dimensions_);
                            auto attachment    = map_render_buffer_attachment(render_buffer->format(), color_index);

                            attach(identifier, attachment, render_buffer);
                        }, 
                    };

                    std::visit(overload, format);
                });
            
            if (gl::compare<std::equal_to>(color_index, gl::uint32_t{ 0u }))
            {
                gl::frame_buffer_read_buffer(handle(), gl::frame_buffer_source_e::none);
                gl::frame_buffer_draw_buffer(handle(), gl::frame_buffer_source_e::none);
            }
            else
            {
                auto color_buffer_sources = std::vector<gl::frame_buffer_source_e>(color_index);
                std::ranges::for_each(std::views::iota(0u, color_index), [&](gl::uint32_t index)
                    {
                        color_buffer_sources.at(index) = gl::frame_buffer_source_e::color_0 + index;
                    });

                gl::frame_buffer_draw_buffers(handle(), color_buffer_sources);
            }

            if (gl::check_frame_buffer_status(handle()) != gl::frame_buffer_status_e::complete) throw std::runtime_error{ "Framebuffer is not complete!" };
        }

        void bind(target_e target)
        {
            gl::bind_frame_buffer(handle(), target);
        }
        template<surface_e A = surface_e::texture>
        void bind_surface(const std::string& identifier, gl::binding_t binding) const
        {
            if constexpr (A == surface_e::texture) texture_map_.at(identifier)->bind(binding);
            if constexpr (A == surface_e::cubemap) cubemap_map_.at(identifier)->bind(binding);
        }

        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::texture2d>     texture      , gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle(), texture->handle(), attachment, level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            texture_map_.emplace(identifier, texture);
        }
        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::cubemap>       cubemap      , gl::uint32_t level = 0u)
        {
            gl::frame_buffer_texture(handle(), cubemap->handle(), attachment, level);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            cubemap_map_.emplace(identifier, cubemap);
        }
        void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::render_buffer> render_buffer)
        {
            gl::frame_buffer_render_buffer(handle(), render_buffer->handle(), attachment);

            attachments_.at(gl::to_underlying(attachment)) = identifier;
            render_buffer_map_.emplace(identifier, render_buffer);
        }
        
        template<surface_e A = surface_e::texture>
        void detach(const std::string& identifier, attachment_e attachment)
        {
            if constexpr (A == surface_e::texture)
            {
                gl::frame_buffer_texture(handle(), gl::null_object, attachment, gl::uint32_t{ 0u });
                texture_map_.erase(identifier);
            }
            if constexpr (A == surface_e::cubemap)
            {
                gl::frame_buffer_texture(handle(), gl::null_object, attachment, gl::uint32_t{ 0u });
                cubemap_map_.erase(identifier);
            }
            if constexpr (A == surface_e::render_buffer)
            {
                gl::frame_buffer_render_buffer(handle(), gl::null_object, attachment, gl::uint32_t{ 0u });
                render_buffer_map_.erase(identifier);
            }
        }
        
        void read_from(const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
        {
            auto& texture = texture_map_.at(identifier);

            gl::frame_buffer_texture    (handle(), texture->handle(), gl::frame_buffer_attachment_e::color_0 + index, level);
            gl::frame_buffer_read_buffer(handle(), gl::frame_buffer_source_e::color_0 + index);
        }
        void write_to (const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
        {
            auto& texture = texture_map_.at(identifier);

            gl::frame_buffer_texture    (handle(), texture->handle(), gl::frame_buffer_attachment_e::color_0 + index, level);
            gl::frame_buffer_draw_buffer(handle(), gl::frame_buffer_source_e::color_0 + index);
        }

        void resize(const gl::vector2u& dimensions)
        {
            std::ranges::for_each(texture_map_      , [&](const auto& _)
                {
                    const auto& [identifier, texture] = _;
                    texture->resize(dimensions);
                });
            std::ranges::for_each(render_buffer_map_, [&](const auto& _)
                {
                    const auto& [identifier, renderBuffer] = _;
                    renderBuffer->resize(dimensions);
                });

            dimensions_ = dimensions;
        }

        template<surface_e A = surface_e::texture>
        auto surface(const std::string& identifier) -> auto
        {
            if constexpr (A == surface_e::texture)
            {
                return texture_map_.at(identifier);
            }
            if constexpr (A == surface_e::cubemap)
            {
                return cubemap_map_.at(identifier);
            }
            if constexpr (A == surface_e::render_buffer)
            {
                return render_buffer_map_.at(identifier);
            }
        }
        
        auto attachment(attachment_e attachment) const -> const std::string&
        {
            return attachments_.at(gl::to_underlying(attachment));
        }
        auto dimensions() const -> const gl::vector2u&
        {
            return dimensions_;
        }

    private:
        std::array<std::string, 11u>                                        attachments_;
        std::unordered_map<std::string, std::shared_ptr<gl::texture2d>>     texture_map_;
        std::unordered_map<std::string, std::shared_ptr<gl::cubemap>>       cubemap_map_;
        std::unordered_map<std::string, std::shared_ptr<gl::render_buffer>> render_buffer_map_;
        gl::vector2u                                                        dimensions_;
    };
    //class frame_buffer_ms : public gl::object
    //{
    //public:
    //    using attachment_e    = api::frame_buffer::attachment_e;
    //    using specification_t = api::frame_buffer::specification_ms;
    //    using surface_e       = api::frame_buffer::surface_e;
    //    using target_e        = api::frame_buffer::target_e;

    //    frame_buffer_ms(const gl::vector2u& dimensions, gl::uint32_t samples)
    //        : gl::object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
    //        , attachments_{}, textureMap_{}, renderBufferMap_{}, dimensions_{ dimensions }, samples_{ samples } {}
    //    frame_buffer_ms(const gl::vector2u& dimensions, std::span<const specification_t> specifications, gl::uint32_t samples)
    //        : gl::object{ gl::create_frame_buffer(), [](auto* handle) { gl::delete_frame_buffer(*handle); } }
    //        , attachments_{}, textureMap_{}, renderBufferMap_{}, dimensions_{ dimensions }, samples_{ samples }
    //    {
    //        auto map_texture_attachment       = [](api::texture::format_e      format, gl::uint32_t& colorIndex)
    //            {
    //                switch (format)
    //                {
    //                    case api::texture::format_e::d16_unorm:
    //                    case api::texture::format_e::d24_unorm:
    //                    case api::texture::format_e::d32_float:         return api::frame_buffer::attachment_e::depth;

    //                    case api::texture::format_e::d24_unorm_s8_uint:
    //                    case api::texture::format_e::d32_float_s8_uint: return api::frame_buffer::attachment_e::depth_stencil;

    //                    case api::texture::format_e::s8_uint:           return api::frame_buffer::attachment_e::stencil;

    //                    default:                                        return api::frame_buffer::attachment_e::color0 + colorIndex++;
    //                }
    //            };
    //        auto map_render_buffer_attachment = [](api::render_buffer::format_e format, gl::uint32_t& colorIndex)
    //        {
    //            switch (format)
    //            {
    //                case api::render_buffer::format_e::d16_unorm:
    //                case api::render_buffer::format_e::d24_unorm:
    //                case api::render_buffer::format_e::d32_float:         return api::frame_buffer::attachment_e::depth;

    //                case api::render_buffer::format_e::d24_unorm_s8_uint:
    //                case api::render_buffer::format_e::d32_float_s8_uint: return api::frame_buffer::attachment_e::depth_stencil;

    //                case api::render_buffer::format_e::s8_uint:           return api::frame_buffer::attachment_e::stencil;

    //                default:                                              return api::frame_buffer::attachment_e::color0 + colorIndex++;
    //            }
    //        };

    //        auto colorIndex = gl::uint32_t{ 0u };
    //        std::ranges::for_each(specifications, [&, this](const auto& specification)
    //            {
    //                const auto& [identifier, format] = specification;
    //                const auto  overload             = gl::overload
    //                {
    //                    [&](api::texture     ::format_e format)
    //                    {
    //                        auto texture    = std::make_shared<gl::texture2d_ms>(format, dimensions_, samples_);
    //                        auto attachment = map_texture_attachment(texture->format(), colorIndex);

    //                        attach(identifier, attachment, texture);
    //                    }, 
    //                    [&](api::render_buffer::format_e format)
    //                    {
    //                        auto renderBuffer = std::make_shared<gl::render_buffer_ms>(format, dimensions_, samples_);
    //                        auto attachment   = map_render_buffer_attachment(renderBuffer->format(), colorIndex);

    //                        attach(identifier, attachment, renderBuffer);
    //                    }, 
    //                };

    //                std::visit(overload, format);
    //            });

    //        if (gl::compare<std::equal_to>(colorIndex, gl::uint32_t{ 0u }))
    //        {
    //            gl::frame_buffer_read_buffer(handle(), gl::frame_buffer_source_e::none);
    //            gl::frame_buffer_draw_buffer(handle(), gl::frame_buffer_source_e::none);
    //        }
    //        else
    //        {
    //            auto colorBufferSources = std::vector<gl::frame_buffer_source_e>(colorIndex);
    //            std::ranges::for_each(std::views::iota(0u, colorIndex), [&](gl::uint32_t index)
    //                {
    //                    colorBufferSources.at(index) = gl::frame_buffer_source_e::color0 + index;
    //                });

    //            gl::frame_buffer_draw_buffers(handle(), colorBufferSources);
    //        }

    //        if (gl::check_frame_buffer_status(handle()) != gl::frame_buffer_status_e::complete) throw std::runtime_error{ "Framebuffer is not complete!" };
    //     }
    //    
    //    void bind(target_e target)
    //    {
    //        gl::bind_frame_buffer(handle(), gl::map_frame_buffer_target(target));
    //    }
    //    template<surface_e A = surface_e::texture>
    //    void bind_surface(const std::string& identifier, gl::binding_t binding) const
    //    {
    //        if constexpr (A == surface_e::texture) textureMap_.at(identifier)->bind(binding);
    //    }

    //    void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::texture2d_ms>    texture, gl::uint32_t level = 0u)
    //    {
    //        gl::frame_buffer_texture(handle(), texture->handle(), gl::map_frame_buffer_attachment(attachment), level);

    //        attachments_.at(gl::to_underlying(attachment)) = identifier;
    //        textureMap_.emplace(identifier, texture);
    //    }
    //    void attach(const std::string& identifier, attachment_e attachment, std::shared_ptr<gl::render_buffer_ms> renderBuffer)
    //    {
    //        gl::frame_buffer_render_buffer(handle(), renderBuffer->handle(), gl::map_frame_buffer_attachment(attachment));

    //        attachments_.at(gl::to_underlying(attachment)) = identifier;
    //        renderBufferMap_.emplace(identifier, renderBuffer);
    //    }

    //    template<surface_e A = surface_e::texture>
    //    void detach(const std::string& identifier, attachment_e attachment)
    //    {
    //        if constexpr (A == surface_e::texture)
    //        {
    //            gl::frame_buffer_texture(handle_, gl::null_object, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
    //            textureMap_.erase(identifier);
    //        }
    //        if constexpr (A == surface_e::render_buffer)
    //        {
    //            gl::frame_buffer_render_buffer(handle_, gl::null_object, gl::map_frame_buffer_attachment(attachment), gl::uint32_t{ 0u });
    //            renderBufferMap_.erase(identifier);
    //        }
    //    }

    //    void read_from(const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
    //    {
    //        auto& texture = textureMap_.at(identifier);

    //        gl::frame_buffer_texture    (handle(), texture->handle(), gl::frame_buffer_attachment_e::color0 + index, level);
    //        gl::frame_buffer_read_buffer(handle(), gl::frame_buffer_source_e::color0 + index);
    //    }
    //    void write_to (const std::string& identifier, gl::index_t index, gl::uint32_t level = 0u)
    //    {
    //        auto& texture = textureMap_.at(identifier);

    //        gl::frame_buffer_texture    (handle(), texture->handle(), gl::frame_buffer_attachment_e::color0 + index, level);
    //        gl::frame_buffer_draw_buffer(handle(), gl::frame_buffer_source_e::color0 + index);
    //    }

    //    void resize(const gl::vector2u& dimensions)
    //    {
    //        std::ranges::for_each(textureMap_     , [&](const auto& _)
    //            {
    //                const auto& [identifier, texture] = _;
    //                texture->resize(dimensions);
    //            });
    //        std::ranges::for_each(renderBufferMap_, [&](const auto& _)
    //            {
    //                const auto& [identifier, renderBuffer] = _;
    //                renderBuffer->resize(dimensions);
    //            });

    //        dimensions_ = dimensions;
    //    }

    //    template<surface_e A = surface_e::texture>
    //    auto surface(const std::string& identifier) -> auto
    //    {
    //        if constexpr (A == surface_e::texture)
    //        {
    //            return textureMap_.at(identifier);
    //        }
    //        if constexpr (A == surface_e::render_buffer)
    //        {
    //            return renderBufferMap_.at(identifier);
    //        }
    //    }

    //    auto attachment(attachment_e attachment) const -> const std::string&
    //    {
    //        return attachments_.at(gl::to_underlying(attachment));
    //    }
    //    auto dimensions() const -> const gl::vector2u&
    //    {
    //        return dimensions_;
    //    }
    //    auto samples   () const
    //    {
    //        return samples_;
    //    }

    //private:
    //    std::array<std::string, 11u>                                           attachments_;
    //    std::unordered_map<std::string, std::shared_ptr<gl::texture2d_ms>>     textureMap_;
    //    std::unordered_map<std::string, std::shared_ptr<gl::render_buffer_ms>> renderBufferMap_;
    //    gl::vector2u                                                           dimensions_;
    //    gl::uint32_t                                                           samples_;
    //};
}
