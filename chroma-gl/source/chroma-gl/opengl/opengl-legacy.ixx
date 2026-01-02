export module opengl:legacy;

import std;
import <glad/gl.h>;
import :flags;
import :structures;
import :types;
import :utility;

export namespace gl::legacy
{
    auto is_buffer                                        (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsBuffer(std::to_underlying(handle));
    }
    auto is_framebuffer                                   (gl::handle_t handle) -> gl::bool_t
    {
        return ::glIsFramebuffer(std::to_underlying(handle));
    }
    auto is_program                                       (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsProgram(std::to_underlying(handle));
    }
    auto is_program_pipeline                              (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsProgramPipeline(std::to_underlying(handle));
    }
    auto is_query                                         (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsQuery(std::to_underlying(handle));
    }
    auto is_renderbuffer                                  (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsRenderbuffer(std::to_underlying(handle));
    }
    auto is_sampler                                       (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsSampler(std::to_underlying(handle));
    }
    auto is_shader                                        (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsShader(std::to_underlying(handle));
    }
    auto is_texture                                       (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsTexture(std::to_underlying(handle));
    }
    auto is_transform_feedback                            (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsTransformFeedback(std::to_underlying(handle));
    }
    auto is_vertex_array                                  (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsVertexArray(std::to_underlying(handle));
    }
    auto is_sync                                          (gl::sync_t   sync  ) -> gl::bool_t 
    {
        return ::glIsSync(sync);
    }

    auto get_boolean_value                                (gl::data_e data                                      ) -> gl::boolean_t
    {
        auto value = gl::boolean_t{};
        ::glGetBooleanv(gl::to_underlying(data), &value);

        return value;
    }
    auto get_boolean_value                                (gl::data_e data, gl::count_t count                   ) -> std::vector<gl::boolean_t>
    {
        auto value = std::vector<gl::boolean_t>(count);
        ::glGetBooleanv(gl::to_underlying(data), value.data());

        return value;
    }
    auto get_boolean_value_index                          (gl::data_e data,                    gl::index_t index) -> gl::boolean_t
    {
        auto value = gl::boolean_t{};
        ::glGetBooleani_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index), &value);

        return value;
    }
    auto get_boolean_value_index                          (gl::data_e data, gl::count_t count, gl::index_t index) -> std::vector<gl::boolean_t>
    {
        auto value = std::vector<gl::boolean_t>(count);
        ::glGetBooleani_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index), value.data());

        return value;
    }
    auto get_int32_value                                  (gl::data_e data                                      ) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetIntegerv(gl::to_underlying(data), &value);

        return value;
    }
    auto get_int32_value                                  (gl::data_e data, gl::count_t count                   ) -> std::vector<gl::int32_t>
    {
        auto value = std::vector<gl::int32_t>(count);
        ::glGetIntegerv(gl::to_underlying(data), value.data());

        return value;
    }
    auto get_int32_value_index                            (gl::data_e data,                    gl::index_t index) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetIntegeri_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index), &value);

        return value;
    }
    auto get_int32_value_index                            (gl::data_e data, gl::count_t count, gl::index_t index) -> std::vector<gl::int32_t>
    {
        auto value = std::vector<gl::int32_t>(count);
        ::glGetIntegeri_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index), value.data());

        return value;
    }
    auto get_int64_value                                  (gl::data_e data                                      ) -> gl::int64_t
    {
        auto value = gl::int64_t{};
        ::glGetInteger64v(gl::to_underlying(data), &value);

        return value;
    }
    auto get_int64_value                                  (gl::data_e data, gl::count_t count                   ) -> std::vector<gl::int64_t>
    {
        auto value = std::vector<gl::int64_t>(count);
        ::glGetInteger64v(gl::to_underlying(data), value.data());

        return value;
    }
    auto get_int64_value_index                            (gl::data_e data,                    gl::index_t index) -> gl::int64_t
    {
        auto value = gl::int64_t{};
        ::glGetInteger64i_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index), &value);

        return value;
    }
    auto get_int64_value_index                            (gl::data_e data, gl::count_t count, gl::index_t index) -> std::vector<gl::int64_t>
    {
        auto value = std::vector<gl::int64_t>(count);
        ::glGetInteger64i_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index), value.data());

        return value;
    }
    auto get_float32_value                                (gl::data_e data                                      ) -> gl::float32_t
    {
        auto value = gl::float32_t{};
        ::glGetFloatv(gl::to_underlying(data), &value);

        return value;
    }
    auto get_float32_value                                (gl::data_e data, gl::count_t count                   ) -> std::vector<gl::float32_t>
    {
        auto value = std::vector<gl::float32_t>(count);
        ::glGetFloatv(gl::to_underlying(data), value.data());

        return value;
    }
    auto get_float32_value_index                          (gl::data_e data,                    gl::index_t index) -> gl::float32_t
    {
        auto value = gl::float32_t{};
        ::glGetFloati_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index), &value);

        return value;
    }
    auto get_float32_value_index                          (gl::data_e data, gl::count_t count, gl::index_t index) -> std::vector<gl::float32_t>
    {
        auto value = std::vector<gl::float32_t>(count);
        ::glGetFloati_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index), value.data());

        return value;
    }
    auto get_float64_value                                (gl::data_e data                                      ) -> gl::float64_t
    {
        auto value = gl::float64_t{};
        ::glGetDoublev(gl::to_underlying(data), &value);

        return value;
    }
    auto get_float64_value                                (gl::data_e data, gl::count_t count                   ) -> std::vector<gl::float64_t>
    {
        auto value = std::vector<gl::float64_t>(count);
        ::glGetDoublev(gl::to_underlying(data), value.data());

        return value;
    }
    auto get_float64_value_index                          (gl::data_e data,                    gl::index_t index) -> gl::float64_t
    {
        auto value = gl::float64_t{};
        ::glGetDoublei_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index), &value);

        return value;
    }
    auto get_float64_value_index                          (gl::data_e data, gl::count_t count, gl::index_t index) -> std::vector<gl::float64_t>
    {
        auto value = std::vector<gl::float64_t>(count);
        ::glGetDoublei_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index), value.data());

        return value;
    }

    auto get_internal_format32_value                      (gl::enum_t internal_format, gl::internal_format_target_e internal_format_target, gl::internal_format_parameter_e internal_format_parameter) -> gl::enum_t
    {
        auto value = gl::int32_t{};
        ::glGetInternalformativ(gl::to_underlying(internal_format_target), internal_format, gl::to_underlying(internal_format_parameter), static_cast<gl::sizei_t>(sizeof(gl::int32_t)), &value);

        return value;
    }
    auto get_internal_format64_value                      (gl::enum_t internal_format, gl::internal_format_target_e internal_format_target, gl::internal_format_parameter_e internal_format_parameter) -> gl::int64_t
    {
        auto value = gl::int64_t{};
        ::glGetInternalformati64v(gl::to_underlying(internal_format_target), internal_format, gl::to_underlying(internal_format_parameter), static_cast<gl::sizei_t>(sizeof(gl::int64_t)), &value);

        return value;
    };
    auto get_sync_value                                   (gl::sync_t sync, gl::synchronization_property_e property) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetSynciv(sync, gl::to_underlying(property), gl::sizei_t{ 1 }, nullptr, &value);

        return value;
    }
    auto get_query_value                                  (gl::query_target_e query_target, gl::query_symbol_e symbol                   ) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetQueryiv(gl::to_underlying(query_target), gl::to_underlying(symbol), &value);

        return value;
    }
    auto get_query_value_index                            (gl::query_target_e query_target, gl::query_symbol_e symbol, gl::index_t index) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetQueryIndexediv(gl::to_underlying(query_target), static_cast<gl::uint32_t>(index), gl::to_underlying(symbol), &value);

        return value;
    }
    auto get_query_object_int32_value                     (gl::handle_t query, gl::query_parameter_e parameter) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetQueryObjectiv(gl::to_underlying(query), gl::to_underlying(parameter), &value);

        return value;
    };
    auto get_query_object_uint32_value                    (gl::handle_t query, gl::query_parameter_e parameter) -> gl::uint32_t
    {
        auto value = gl::uint32_t{};
        ::glGetQueryObjectuiv(gl::to_underlying(query), gl::to_underlying(parameter), &value);

        return value;
    };
    auto get_query_buffer_object_int32_value              (gl::handle_t query, gl::handle_t buffer, gl::query_parameter_e query_parameter, gl::ptrdiff_t offset)
        {
            ::glGetQueryBufferObjectiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(query_parameter), offset);
        };
    auto get_query_buffer_object_uint32_value             (gl::handle_t query, gl::handle_t buffer, gl::query_parameter_e query_parameter, gl::ptrdiff_t offset)
        {
            ::glGetQueryBufferObjectuiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(query_parameter), offset);
        };
    auto get_buffer_parameter_int32_value                 (gl::handle_t buffer, gl::buffer_parameter_e parameter) -> gl::int32_t
        {
            auto value = gl::int32_t{};
            ::glGetNamedBufferParameteriv(gl::to_underlying(buffer), gl::to_underlying(parameter), &value);

            return value;
        };
    auto get_buffer_parameter_int64_value                 (gl::handle_t buffer, gl::buffer_parameter_e parameter) -> gl::int64_t
        {
            auto value = gl::int64_t{};
            ::glGetNamedBufferParameteri64v(gl::to_underlying(buffer), gl::to_underlying(parameter), &value);

            return value;
        };

    auto get_shader_value                                 (gl::handle_t shader  , gl::shader_parameter_e  shader_parameter ) -> gl::int32_t
        {
            auto value = gl::int32_t{};
            ::glGetShaderiv(gl::to_underlying(shader), gl::to_underlying(shader_parameter), &value);

            return value;
        };
    auto get_program_value                                (gl::handle_t program , gl::program_parameter_e program_parameter) -> gl::int32_t
        {
            auto value = gl::int32_t{};
            ::glGetProgramiv(gl::to_underlying(program), gl::to_underlying(program_parameter), &value);

            return value;
        };
    auto get_program_pipeline_value                       (gl::handle_t pipeline, gl::pipeline_property_e pipeline_property) -> gl::int32_t
        {
            auto value = gl::int32_t{};
            ::glGetProgramPipelineiv(gl::to_underlying(pipeline), gl::to_underlying(pipeline_property), &value);

            return value;
        };

    auto get_sampler_parameter_int32_value                (gl::handle_t sampler, gl::sampler_parameter_e sampler_parameter                   ) -> gl::int32_t
        {
            auto value = gl::int32_t{};
            ::glGetSamplerParameteriv(gl::to_underlying(sampler), gl::to_underlying(sampler_parameter), &value);

            return value;
        };
    auto get_sampler_parameter_int32_value                (gl::handle_t sampler, gl::sampler_parameter_e sampler_parameter, gl::count_t count) -> std::vector<gl::int32_t>
        {
            auto value = std::vector<gl::int32_t>(count);
            ::glGetSamplerParameteriv(gl::to_underlying(sampler), gl::to_underlying(sampler_parameter), value.data());

            return value;
        };
    auto get_sampler_parameter_uint32_value               (gl::handle_t sampler, gl::sampler_parameter_e sampler_parameter                   ) -> gl::uint32_t
        {
            auto value = gl::uint32_t{};
            ::glGetSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(sampler_parameter), &value);

            return value;
        };
    auto get_sampler_parameter_uint32_value               (gl::handle_t sampler, gl::sampler_parameter_e sampler_parameter, gl::count_t count) -> std::vector<gl::uint32_t>
        {
            auto value = std::vector<gl::uint32_t>(count);
            ::glGetSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(sampler_parameter), value.data());

            return value;
        };
    auto get_sampler_parameter_float32_value              (gl::handle_t sampler, gl::sampler_parameter_e sampler_parameter                   ) -> gl::float32_t
        {
            auto value = gl::float32_t{};
            ::glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(sampler_parameter), &value);

            return value;
        };
    auto get_sampler_parameter_float32_value              (gl::handle_t sampler, gl::sampler_parameter_e sampler_parameter, gl::count_t count) -> std::vector<gl::float32_t>
        {
            auto value = std::vector<gl::float32_t>(count);
            ::glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(sampler_parameter), value.data());

            return value;
        };

    auto get_texture_parameter_int32_value                (gl::handle_t texture, gl::texture_parameter_e texture_parameter                   ) -> gl::int32_t
        {
            auto value = gl::int32_t{};
            ::glGetTextureParameteriv(gl::to_underlying(texture), gl::to_underlying(texture_parameter), &value);

            return value;
        };
    auto get_texture_parameter_int32_value                (gl::handle_t texture, gl::texture_parameter_e texture_parameter, gl::count_t count) -> std::vector<gl::int32_t>
    {
        auto value = std::vector<gl::int32_t>(count);
        ::glGetTextureParameteriv(gl::to_underlying(texture), gl::to_underlying(texture_parameter), value.data());

        return value;
    };
    auto get_texture_parameter_float32_value              (gl::handle_t texture, gl::texture_parameter_e texture_parameter                   ) -> gl::float32_t
        {
            auto value = gl::float32_t{};
            ::glGetTextureParameterfv(gl::to_underlying(texture), gl::to_underlying(texture_parameter), &value);

            return value;
        };
    auto get_texture_parameter_float32_value              (gl::handle_t texture, gl::texture_parameter_e texture_parameter, gl::count_t count) -> std::vector<gl::float32_t>
        {
        auto value = std::vector<gl::float32_t>(count);
            ::glGetTextureParameterfv(gl::to_underlying(texture), gl::to_underlying(texture_parameter), value.data());

            return value;
        };
    auto get_texture_level_parameter_int32_value          (gl::handle_t texture, gl::uint32_t image_level, gl::texture_level_parameter_e texture_level_parameter                   ) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetTextureLevelParameteriv(gl::to_underlying(texture), static_cast<gl::int32_t>(image_level), gl::to_underlying(texture_level_parameter), &value);
                
        return value;
    };
    auto get_texture_level_parameter_int32_value          (gl::handle_t texture, gl::uint32_t image_level, gl::texture_level_parameter_e texture_level_parameter, gl::count_t count) -> std::vector<gl::int32_t>
    {
        auto value = std::vector<gl::int32_t>(count);
        ::glGetTextureLevelParameteriv(gl::to_underlying(texture), static_cast<gl::int32_t>(image_level), gl::to_underlying(texture_level_parameter), value.data());
                
        return value;
    };

    auto get_frame_buffer_parameter_int32_value           (gl::handle_t frame_buffer, gl::frame_buffer_parameter_e parameter                   ) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetNamedFramebufferParameteriv(gl::to_underlying(frame_buffer), gl::to_underlying(parameter), &value);
                
        return value;
    };
    auto get_frame_buffer_parameter_int32_value           (gl::handle_t frame_buffer, gl::frame_buffer_parameter_e parameter, gl::count_t count) -> std::vector<gl::int32_t>
    {
        auto value = std::vector<gl::int32_t>(count);
        ::glGetNamedFramebufferParameteriv(gl::to_underlying(frame_buffer), gl::to_underlying(parameter), value.data());

        return value;
    };
    auto get_frame_buffer_attachment_parameter_int32_value(gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment, gl::frame_buffer_attachment_parameter_e parameter                   ) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetNamedFramebufferAttachmentParameteriv(gl::to_underlying(frame_buffer), gl::to_underlying(attachment), gl::to_underlying(parameter), &value);
                
        return value;
    };
    auto get_frame_buffer_attachment_parameter_int32_value(gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment, gl::frame_buffer_attachment_parameter_e parameter, gl::count_t count) -> std::vector<gl::int32_t>
    {
        auto value = std::vector<gl::int32_t>(count);
        ::glGetNamedFramebufferAttachmentParameteriv(gl::to_underlying(frame_buffer), gl::to_underlying(attachment), gl::to_underlying(parameter), value.data());
                
        return value;
    };
    auto get_render_buffer_parameter_int32_value          (gl::handle_t render_buffer, gl::render_buffer_parameter_e parameter                   ) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetNamedRenderbufferParameteriv(gl::to_underlying(render_buffer), gl::to_underlying(parameter), &value);
                
        return value;
    };
    auto get_render_buffer_parameter_int32_value          (gl::handle_t render_buffer, gl::render_buffer_parameter_e parameter, gl::count_t count) -> std::vector<gl::int32_t>
    {
        auto value = std::vector<gl::int32_t>(count);
        ::glGetNamedRenderbufferParameteriv(gl::to_underlying(render_buffer), gl::to_underlying(parameter), value.data());

        return value;
    };

    auto get_vertex_array_int32_value                     (gl::handle_t vertex_array, gl::vertex_array_parameter_e parameter                   ) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetVertexArrayiv(gl::to_underlying(vertex_array), gl::to_underlying(parameter), &value);

        return value;
    }
    auto get_vertex_array_int32_value                     (gl::handle_t vertex_array, gl::vertex_array_parameter_e parameter, gl::count_t count) -> std::vector<gl::int32_t>
    {
        auto value = std::vector<gl::int32_t>(count);
        ::glGetVertexArrayiv(gl::to_underlying(vertex_array), gl::to_underlying(parameter), value.data());

        return value;
    }

    auto get_vertex_array_int32_value_index               (gl::handle_t vertex_array, gl::vertex_array_parameter_e parameter, gl::index_t index                   ) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetVertexArrayIndexediv(gl::to_underlying(vertex_array), static_cast<gl::uint32_t>(index), gl::to_underlying(parameter), &value);

        return value;
    };
    auto get_vertex_array_int32_value_index               (gl::handle_t vertex_array, gl::vertex_array_parameter_e parameter, gl::index_t index, gl::count_t count) -> std::vector<gl::int32_t>
    {
        auto value = std::vector<gl::int32_t>(count);
        ::glGetVertexArrayIndexediv(gl::to_underlying(vertex_array), static_cast<gl::uint32_t>(index), gl::to_underlying(parameter), value.data());

        return value;
    };
    auto get_vertex_array_int64_value_index               (gl::handle_t vertex_array, gl::vertex_array_parameter_e parameter, gl::index_t index                   ) -> gl::int64_t
    {
        auto value = gl::int64_t{};
        ::glGetVertexArrayIndexed64iv(gl::to_underlying(vertex_array), static_cast<gl::uint32_t>(index), gl::to_underlying(parameter), &value);

        return value;
    };
    auto get_vertex_array_int64_value_index               (gl::handle_t vertex_array, gl::vertex_array_parameter_e parameter, gl::index_t index, gl::count_t count) -> std::vector<gl::int64_t>
    {
        auto value = std::vector<gl::int64_t>(count);
        ::glGetVertexArrayIndexed64iv(gl::to_underlying(vertex_array), static_cast<gl::uint32_t>(index), gl::to_underlying(parameter), value.data());

        return value;
    };

    auto get_program_interface_int32_value                (gl::handle_t program, gl::program_interface_e interface, gl::program_interface_parameter_e parameter                   ) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        ::glGetProgramInterfaceiv(gl::to_underlying(program), gl::to_underlying(interface), gl::to_underlying(parameter), &value);

        return value;
    };
    auto get_program_interface_int32_value                (gl::handle_t program, gl::program_interface_e interface, gl::program_interface_parameter_e parameter, gl::count_t count) -> std::vector<gl::int32_t>
    {
        auto value = std::vector<gl::int32_t>(count);
        ::glGetProgramInterfaceiv(gl::to_underlying(program), gl::to_underlying(interface), gl::to_underlying(parameter), value.data());

        return value;
    };

    void sampler_parameter_int32_value                    (gl::handle_t sampler, gl::sampler_parameter_e parameter, gl::int32_t   value)
    {
        ::glSamplerParameterIiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
    };
    void sampler_parameter_uint32_value                   (gl::handle_t sampler, gl::sampler_parameter_e parameter, gl::uint32_t  value)
    {
        ::glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
    };
    void sampler_parameter_float32_value                  (gl::handle_t sampler, gl::sampler_parameter_e parameter, gl::float32_t value)
    {
        ::glSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
    };

    void texture_parameter_int32_value                    (gl::handle_t texture, gl::texture_parameter_e parameter, gl::int32_t   value)
    {
        ::glTextureParameteri(gl::to_underlying(texture), gl::to_underlying(parameter), value);
    };
    void texture_parameter_uint32_value                   (gl::handle_t texture, gl::texture_parameter_e parameter, gl::uint32_t  value)
    {
        ::glTextureParameteri(gl::to_underlying(texture), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
    };
    void texture_parameter_float32_value                  (gl::handle_t texture, gl::texture_parameter_e parameter, gl::float32_t value)
    {
        ::glTextureParameterfv(gl::to_underlying(texture), gl::to_underlying(parameter), &value);
    };

    void frame_buffer_parameter_int32_value               (gl::handle_t frame_buffer, gl::frame_buffer_parameter_e parameter, gl::uint32_t value)
        {
            ::glNamedFramebufferParameteri(gl::to_underlying(frame_buffer), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
        };

    void patch_parameter_int32_value                      (gl::patch_parameter_e parameter, gl::int32_t   value)
        {
            ::glPatchParameteri(gl::to_underlying(parameter), value);
        };
    void patch_parameter_float32_value                    (gl::patch_parameter_e parameter, gl::float32_t value)
        {
            ::glPatchParameterfv(gl::to_underlying(parameter), &value);
        };

    void vertex_array_attribute_format_int32              (gl::handle_t vertex_array, gl::index_t attribute_index, gl::vertex_array_attribute_type_e attribute_type, gl::count_t attribute_count, gl::ptrdiff_t byte_offset)
        {
            ::glVertexArrayAttribIFormat(
                gl::to_underlying        (vertex_array)   , 
                static_cast<gl::uint32_t>(attribute_index), static_cast<gl::int32_t> (attribute_count), 
                gl::to_underlying        (attribute_type) , static_cast<gl::uint32_t>(byte_offset)   );
        };
    void vertex_array_attribute_format_float32            (gl::handle_t vertex_array, gl::index_t attribute_index, gl::vertex_array_attribute_type_e attribute_type, gl::count_t attribute_count, gl::ptrdiff_t byte_offset, gl::bool_t is_normalized)
        {
            ::glVertexArrayAttribFormat(
                gl::to_underlying        (vertex_array)   , 
                static_cast<gl::uint32_t>(attribute_index),                static_cast<gl::int32_t> (attribute_count), 
                gl::to_underlying        (attribute_type) , is_normalized, static_cast<gl::uint32_t>(byte_offset)   );
        };
    void vertex_array_attribute_format_float64            (gl::handle_t vertex_array, gl::index_t attribute_index, gl::vertex_array_attribute_type_e attribute_type, gl::count_t attribute_count, gl::ptrdiff_t byte_offset                          )
        {
            ::glVertexArrayAttribLFormat(
                gl::to_underlying        (vertex_array)   , 
                static_cast<gl::uint32_t>(attribute_index), static_cast<gl::int32_t> (attribute_count), 
                gl::to_underlying        (attribute_type) , static_cast<gl::uint32_t>(byte_offset)   );
        };

    void point_parameter_int32                            (gl::point_parameter_e parameter, gl::int32_t   value)
        {
            ::glPointParameteri(gl::to_underlying(parameter), value);
        };
    void point_parameter_float32                          (gl::point_parameter_e parameter, gl::float32_t value)
        {
            ::glPointParameterf(gl::to_underlying(parameter), value);
        };

    void clear_frame_buffer_int32_value                   (gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, gl::int32_t   const* value)
    {
        ::glClearNamedFramebufferiv(gl::to_underlying(frame_buffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
    };
    void clear_frame_buffer_uint32_value                  (gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, gl::uint32_t  const* value)
    {
        ::glClearNamedFramebufferuiv(gl::to_underlying(frame_buffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
    };
    void clear_frame_buffer_float32_value                 (gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, gl::float32_t const* value)
    {
        ::glClearNamedFramebufferfv(gl::to_underlying(frame_buffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
    };
    void clear_frame_buffer_fi                            (gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, gl::float32_t depth, gl::int32_t stencil)
    {
        ::glClearNamedFramebufferfi(gl::to_underlying(frame_buffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), depth, stencil);
    };

    auto get_error                                        () -> gl::error_flag_e
    {
        return static_cast<gl::error_flag_e>(::glGetError());
    }





    //glActiveTexture
    //glBeginTransformFeedback
    //glBindAttribLocation
    //glBindFragDataLocation
    //glBindFragDataLocationIndexed
    //glBindRenderbuffer
    //glBindTextures
    //glBindTransformFeedback
    //glBindVertexBuffer
    //glBindVertexBuffers
    //glBlendFunci
    //glBlitFramebuffer
    //glBufferData
    //glBufferStorage
    //glBufferSubData
    //glCheckFramebufferStatus
    //glClearBufferData
    //glClearBufferSubData
    //glClearBufferfi
    //glClearBufferfv
    //glClearBufferiv
    //glClearBufferuiv
    //glCompressedTexImage1D
    //glCompressedTexImage2D
    //glCompressedTexImage3D
    //glCompressedTexSubImage1D
    //glCompressedTexSubImage2D
    //glCompressedTexSubImage3D
    //glCopyBufferSubData
    //glCopyTexImage1D
    //glCopyTexImage2D
    //glCopyTexSubImage1D
    //glCopyTexSubImage2D
    //glCopyTexSubImage3D
    //glCreateTransformFeedbacks
    //glDeleteTransformFeedbacks
    //glDisableVertexAttribArray
    //glDrawBuffer
    //glDrawBuffers
    //glDrawBuffersATI
    //glDrawTransformFeedback
    //glDrawTransformFeedbackInstanced
    //glDrawTransformFeedbackStream
    //glDrawTransformFeedbackStreamInstanced
    //glEnableVertexAttribArray
    //glEndTransformFeedback
    //glFlushMappedBufferRange
    //glFramebufferParameteri
    //glFramebufferRenderbuffer
    //glFramebufferTexture
    //glFramebufferTexture1D
    //glFramebufferTexture2D
    //glFramebufferTexture3D
    //glFramebufferTextureLayer
    //glGenBuffers
    //glGenFramebuffers
    //glGenProgramPipelines
    //glGenQueries
    //glGenRenderbuffers
    //glGenSamplers
    //glGenTextures
    //glGenTransformFeedbacks
    //glGenVertexArrays
    //glGenerateMipmap
    //glGetActiveAtomicCounterBufferiv
    //glGetActiveAttrib
    //glGetActiveSubroutineName
    //glGetActiveSubroutineUniformName
    //glGetActiveSubroutineUniformiv
    //glGetActiveUniform
    //glGetActiveUniformBlockName
    //glGetActiveUniformBlockiv
    //glGetActiveUniformName
    //glGetActiveUniformsiv
    //glGetAttribLocation
    //glGetBufferParameteri64v
    //glGetBufferParameteriv
    //glGetBufferPointerv
    //glGetBufferSubData
    //glGetCompressedTexImage
    //glGetDoublei_v
    //glGetError
    //glGetFloati_v
    //glGetFragDataIndex
    //glGetFragDataLocation
    //glGetFramebufferAttachmentParameteriv
    //glGetFramebufferParameteriv
    //glGetNamedBufferPointerv
    //glGetObjectLabel
    //glGetObjectPtrLabel
    //glGetProgramStageiv
    //glGetQueryBufferObjecti64v
    //glGetQueryBufferObjectui64v
    //glGetQueryObjecti64v
    //glGetQueryObjectui64v
    //glGetRenderbufferParameteriv
    //glGetSamplerParameterIiv
    //glGetSubroutineIndex
    //glGetSubroutineUniformLocation
    //glGetTexImage
    //glGetTexLevelParameterfv
    //glGetTexLevelParameteriv
    //glGetTexParameterIiv
    //glGetTexParameterIuiv
    //glGetTexParameterfv
    //glGetTexParameteriv
    //glGetTextureLevelParameterfv
    //glGetTextureParameterIiv
    //glGetTextureParameterIuiv
    //glGetTransformFeedbackVarying
    //glGetTransformFeedbacki64_v
    //glGetTransformFeedbacki_v
    //glGetTransformFeedbackiv
    //glGetUniformBlockIndex
    //glGetUniformIndices
    //glGetUniformLocation
    //glGetUniformSubroutineuiv
    //glGetUniformdv
    //glGetUniformfv
    //glGetUniformiv
    //glGetUniformuiv
    //glGetVertexAttribIiv
    //glGetVertexAttribIuiv
    //glGetVertexAttribLdv
    //glGetVertexAttribPointerv
    //glGetVertexAttribdv
    //glGetVertexAttribfv
    //glGetVertexAttribiv
    //glGetnCompressedTexImage
    //glGetnTexImage
    //glGetnUniformdv
    //glGetnUniformfv
    //glGetnUniformiv
    //glGetnUniformuiv
    //glInvalidateFramebuffer
    //glInvalidateSubFramebuffer
    //glIsBuffer
    //glIsFramebuffer
    //glIsProgram
    //glIsProgramPipeline
    //glIsQuery
    //glIsRenderbuffer
    //glIsSampler
    //glIsShader
    //glIsSync
    //glIsTexture
    //glIsTransformFeedback
    //glIsVertexArray
    //glMapBuffer
    //glMapBufferRange
    //glMultiDrawArraysIndirectCount
    //glMultiDrawElementsIndirectCount
    //glNamedBufferData
    //glPauseTransformFeedback
    //glPixelStoref
    //glPointParameterfSGIS
    //glPointParameterfv
    //glPointParameterfvSGIS
    //glPointParameteriv
    //glProgramUniform1d
    //glProgramUniform1dv
    //glProgramUniform2d
    //glProgramUniform2dv
    //glProgramUniform2i
    //glProgramUniform2iv
    //glProgramUniform2ui
    //glProgramUniform2uiv
    //glProgramUniform3d
    //glProgramUniform3dv
    //glProgramUniform3i
    //glProgramUniform3iv
    //glProgramUniform3ui
    //glProgramUniform3uiv
    //glProgramUniform4d
    //glProgramUniform4dv
    //glProgramUniformMatrix2dv
    //glProgramUniformMatrix2x3dv
    //glProgramUniformMatrix2x4dv
    //glProgramUniformMatrix3dv
    //glProgramUniformMatrix3x2dv
    //glProgramUniformMatrix3x4dv
    //glProgramUniformMatrix4dv
    //glProgramUniformMatrix4x2dv
    //glProgramUniformMatrix4x3dv
    //glReadBuffer
    //glReadPixels
    //glRenderbufferStorage
    //glRenderbufferStorageMultisample
    //glResumeTransformFeedback
    //glSamplerParameteri
    //glSamplerParameteriv
    //glScissorIndexedv
    //glShaderStorageBlockBinding
    //glStencilFuncSeparateATI
    //glStencilOpSeparateATI
    //glTexBuffer
    //glTexBufferRange
    //glTexImage1D
    //glTexImage2D
    //glTexImage2DMultisample
    //glTexImage3D
    //glTexImage3DMultisample
    //glTexParameterIiv
    //glTexParameterIuiv
    //glTexParameterf
    //glTexParameterfv
    //glTexParameteri
    //glTexParameteriv
    //glTexStorage1D
    //glTexStorage2D
    //glTexStorage2DMultisample
    //glTexStorage3D
    //glTexStorage3DMultisample
    //glTexSubImage1D
    //glTexSubImage2D
    //glTexSubImage3D
    //glTextureParameteriv
    //glTransformFeedbackBufferBase
    //glTransformFeedbackBufferRange
    //glTransformFeedbackVaryings
    //glUniform1d
    //glUniform1dv
    //glUniform1f
    //glUniform1fv
    //glUniform1i
    //glUniform1iv
    //glUniform1ui
    //glUniform1uiv
    //glUniform2d
    //glUniform2dv
    //glUniform2f
    //glUniform2fv
    //glUniform2i
    //glUniform2iv
    //glUniform2ui
    //glUniform2uiv
    //glUniform3d
    //glUniform3dv
    //glUniform3f
    //glUniform3fv
    //glUniform3i
    //glUniform3iv
    //glUniform3ui
    //glUniform3uiv
    //glUniform4d
    //glUniform4dv
    //glUniform4f
    //glUniform4fv
    //glUniform4i
    //glUniform4iv
    //glUniform4ui
    //glUniform4uiv
    //glUniformBlockBinding
    //glUniformMatrix2dv
    //glUniformMatrix2fv
    //glUniformMatrix2x3dv
    //glUniformMatrix2x3fv
    //glUniformMatrix2x4dv
    //glUniformMatrix2x4fv
    //glUniformMatrix3dv
    //glUniformMatrix3fv
    //glUniformMatrix3x2dv
    //glUniformMatrix3x2fv
    //glUniformMatrix3x4dv
    //glUniformMatrix3x4fv
    //glUniformMatrix4dv
    //glUniformMatrix4fv
    //glUniformMatrix4x2dv
    //glUniformMatrix4x2fv
    //glUniformMatrix4x3dv
    //glUniformMatrix4x3fv
    //glUniformSubroutinesuiv
    //glUnmapBuffer
    //glVertexAttrib1d
    //glVertexAttrib1dv
    //glVertexAttrib1fv
    //glVertexAttrib1sv
    //glVertexAttrib2d
    //glVertexAttrib2dv
    //glVertexAttrib2fv
    //glVertexAttrib2sv
    //glVertexAttrib3d
    //glVertexAttrib3dv
    //glVertexAttrib3fv
    //glVertexAttrib3sv
    //glVertexAttrib4Nbv
    //glVertexAttrib4Niv
    //glVertexAttrib4Nsv
    //glVertexAttrib4Nubv
    //glVertexAttrib4Nuiv
    //glVertexAttrib4Nusv
    //glVertexAttrib4bv
    //glVertexAttrib4d
    //glVertexAttrib4dv
    //glVertexAttrib4fv
    //glVertexAttrib4iv
    //glVertexAttrib4sv
    //glVertexAttrib4ubv
    //glVertexAttrib4uiv
    //glVertexAttrib4usv
    //glVertexAttribBinding
    //glVertexAttribDivisor
    //glVertexAttribFormat
    //glVertexAttribI1iv
    //glVertexAttribI1uiv
    //glVertexAttribI2iv
    //glVertexAttribI2uiv
    //glVertexAttribI3iv
    //glVertexAttribI3uiv
    //glVertexAttribI4bv
    //glVertexAttribI4iv
    //glVertexAttribI4sv
    //glVertexAttribI4ubv
    //glVertexAttribI4uiv
    //glVertexAttribI4usv
    //glVertexAttribIFormat
    //glVertexAttribIPointer
    //glVertexAttribL1dv
    //glVertexAttribL2dv
    //glVertexAttribL3dv
    //glVertexAttribL4dv
    //glVertexAttribLFormat
    //glVertexAttribLPointer
    //glVertexAttribP1ui
    //glVertexAttribP1uiv
    //glVertexAttribP2ui
    //glVertexAttribP2uiv
    //glVertexAttribP3ui
    //glVertexAttribP3uiv
    //glVertexAttribP4ui
    //glVertexAttribP4uiv
    //glVertexAttribPointer
    //glVertexBindingDivisor
    //glViewportIndexedfv
}
