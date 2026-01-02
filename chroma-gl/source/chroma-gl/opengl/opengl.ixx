export module opengl;
export import :constants;
export import :domain;
export import :flags;
export import :mapping;
export import :meta;
export import :parameters;
export import :state;
export import :structures;
export import :types;
export import :utility;
#ifdef GL_LEGACY_EXPORT
export import :legacy;
#else
       import :legacy;
#endif

import std;
import <glad/gl.h>;

export namespace gl
{
    //C++ OpenGL Wrapper Library
    //
    //This library provides a modern, robust, and user-friendly interface for OpenGL
    //Its primary goals are to:
    //    * Offer a more intuitive and correct interface for development
    //    * Encapsulate existing OpenGL functions, simplifying integration of additional logic
    //    * Cache state in order to eliminate redundant driver calls
    //    * Provide compile-and runtime safety through comprehensive input validation
    //
    //Functions are organized according to their appearance in the OpenGL 4.6 Core Profile Specification
    //Reference: https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf



    //Chapter 22 - Context State Queries
    template<gl::data_e data_v>
    auto get_value                                        () -> auto
    {
             if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::area_t         >)
        {
            auto const value = legacy::get_int32_value(data_v, 4u);
            return gl::area_t{ gl::vector_2u{ value[2u], value[3u] }, gl::vector_2u{ value[0u], value[1u] } };
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::binary_format_e>)
        {
            auto const program_binary_format_count = static_cast<gl::count_t>(legacy::get_int32_value(gl::data_e::number_program_binary_formats));
            return std::bit_cast<std::vector<gl::binary_format_e>>(legacy::get_int32_value(data_v, program_binary_format_count));
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::bitfield_t     >)
        {
            return static_cast<gl::bitfield_t>(legacy::get_int32_value(data_v));
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::boolean_t      >)
        {
            return legacy::get_boolean_value(data_v);
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::float32_t      >)
        {
            return legacy::get_float32_value(data_v);
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::float64_t      >)
        {
            return legacy::get_float64_value(data_v);
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::handle_t       >)
        {
            return static_cast<gl::handle_t>(legacy::get_int32_value(data_v));
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::int32_t        >)
        {
            return legacy::get_int32_value(data_v);
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::int64_t        >)
        {
            return legacy::get_int64_value(data_v);
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::size_t         >)
        {
            return static_cast<gl::size_t>(legacy::get_int32_value(data_v));
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::uint32_t       >)
        {
            return static_cast<gl::uint32_t>(legacy::get_int32_value(data_v));
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::vector_2f      >)
        {
            auto const value = legacy::get_float32_value(data_v, 2u);
            return gl::vector_2f{ value[0u], value[1u] };
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::vector_2i      >)
        {
            auto const value = legacy::get_int32_value(data_v, 2u);
            return gl::vector_4i{ value[0u], value[1u] };
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::vector_4b      >)
        {
            auto const value = legacy::get_boolean_value(data_v, 4u);
            return gl::vector_4b{ value[0u], value[1u], value[2u], value[3u] };
        }
        else if constexpr (std::is_same_v<meta::data_tag_t<data_v>, gl::vector_4f      >)
        {
            auto const value = legacy::get_float32_value(data_v, 4u);
            return gl::vector_4f{ value[0u], value[1u], value[2u], value[3u] };
        }
        else return static_cast<meta::data_tag_t<data_v>>(legacy::get_int32_value(data_v));
    }
    template<gl::data_e data_v>
    auto get_value                                        (gl::index_t index) -> auto
    {
             if constexpr (std::is_same_v<meta::indexed_data_tag_t<data_v>, gl::area_t    >)
        {
            auto const value = legacy::get_int32_value_index(data_v, 4u, index);
            return gl::area_t{ gl::vector_2u{ value[2u], value[3u] }, gl::vector_2u{ value[0u], value[1u] } };
        }
        else if constexpr (std::is_same_v<meta::indexed_data_tag_t<data_v>, gl::bitfield_t>)
        {
            return static_cast<gl::bitfield_t>(legacy::get_int32_value_index(data_v, index));
        }
        else if constexpr (std::is_same_v<meta::indexed_data_tag_t<data_v>, gl::boolean_t >)
        {
            return legacy::get_boolean_value_index(data_v, index);
        }
        else if constexpr (std::is_same_v<meta::indexed_data_tag_t<data_v>, gl::handle_t  >)
        {
            return static_cast<gl::handle_t>(legacy::get_int32_value_index(data_v, index));
        }
        else if constexpr (std::is_same_v<meta::indexed_data_tag_t<data_v>, gl::size_t    >)
        {
            return static_cast<gl::size_t>(legacy::get_int32_value_index(data_v, index));
        }
        else if constexpr (std::is_same_v<meta::indexed_data_tag_t<data_v>, gl::uint32_t  >)
        {
            return static_cast<gl::uint32_t>(legacy::get_int32_value_index(data_v, index));
        }
        else if constexpr (std::is_same_v<meta::indexed_data_tag_t<data_v>, gl::vector_4u >)
        {
            auto const value = legacy::get_int32_value_index(data_v, 4u, index);
            return gl::vector_4u{ value[0u], value[1u], value[2u], value[3u] };
        }
        else return static_cast<meta::data_tag_t<data_v>>(legacy::get_int32_value_index(data_v, index));
    }
    template<gl::feature_e feature_v>
    void enable                                           ()
    {
        ::glEnable(gl::to_underlying(feature_v));
    }
    template<gl::feature_e feature_v>
    void enable                                           (gl::index_t index)
    {
        ::glEnablei(gl::to_underlying(feature_v), index);
    }
    template<gl::feature_e feature_v>
    void disable                                          ()
    {
        ::glDisable(gl::to_underlying(feature_v));
    }
    template<gl::feature_e feature_v>
    void disable                                          (gl::index_t index)
    {
        ::glDisablei(gl::to_underlying(feature_v), index);
    }
    template<gl::feature_e feature_v>
    auto is_enabled                                       () -> gl::bool_t
    {
        return static_cast<gl::bool_t>(::glIsEnabled(gl::to_underlying(feature_v)));
    }
    template<gl::feature_e feature_v>
    auto is_enabled                                       (gl::index_t index) -> gl::bool_t
    {
        return static_cast<gl::bool_t>(::glIsEnabledi(gl::to_underlying(feature_v)));
    }
    template<gl::callback_pointer_parameter_e parameter_v, typename value_t = gl::void_t>
    auto get_pointer_value                                () -> value_t*
    {
        auto* pointer = reinterpret_cast<value_t*>(nullptr);
        ::glGetPointerv(gl::to_underlying(parameter_v), &pointer);
        
        return pointer;
    }
    template<gl::context_property_e property_v>
    auto get_string                                       () -> std::string
    {
        auto const* c_string = reinterpret_cast<gl::c_string>(::glGetString(gl::to_underlying(property_v)));
        return std::string{ c_string };
    }
    template<gl::context_property_e property_v>
    auto get_string                                       (gl::index_t index) -> std::string
    {
        auto const* c_string = reinterpret_cast<gl::c_string>(::glGetStringi(gl::to_underlying(property_v), static_cast<gl::uint32_t>(index)));
        return std::string{ c_string };
    }
    template<gl::internal_format_parameter_e parameter_v>
    auto get_internal_format_value                        (gl::enum_t internal_format, gl::internal_format_target_e internal_format_target) -> auto
    {
             if constexpr (std::is_same_v<parameter_v, gl::bool_t  >)
        {
            return static_cast<gl::bool_t>(legacy::get_internal_format32_value(internal_format, internal_format_target, parameter_v));
        }
        else if constexpr (std::is_same_v<parameter_v, gl::sizeu_t >)
        {
            return static_cast<gl::sizeu_t>(legacy::get_internal_format32_value(internal_format, internal_format_target, parameter_v));
        }
        else if constexpr (std::is_same_v<parameter_v, gl::uint32_t>)
        {
            return static_cast<gl::uint32_t>(legacy::get_internal_format32_value(internal_format, internal_format_target, parameter_v));
        }
        else return static_cast<gl::enum_t>(legacy::get_internal_format32_value(internal_format, internal_format_target, parameter_v));
    }

    //Chapter 4 - Event Model
    template<gl::synchronization_property_e property_v>
    auto get_sync_value                                   (gl::sync_t sync) -> auto
    {
        using enum gl::synchronization_property_e;
        if constexpr (property_v == condition) return static_cast<gl::synchronization_object_condition_e>(legacy::get_sync_value(sync, property_v));
        if constexpr (property_v == flags    ) return static_cast<gl::bitfield_t                        >(legacy::get_sync_value(sync, property_v));
        if constexpr (property_v == status   ) return static_cast<gl::synchronization_object_status_e   >(legacy::get_sync_value(sync, property_v));
        if constexpr (property_v == type     ) return static_cast<gl::synchronization_object_type_e     >(legacy::get_sync_value(sync, property_v));
    }
    template<gl::query_symbol_e symbol_v>
    auto get_query_value                                  (gl::query_target_e query_target) -> gl::int32_t
    {
        return legacy::get_query_value(query_target, symbol_v);
    }
    template<gl::query_symbol_e symbol_v>
    auto get_query_value_index                            (gl::query_target_e query_target, gl::index_t index) -> gl::int32_t
    {
        return legacy::get_query_value_index(query_target, symbol_v, index);
    }
    template<gl::query_parameter_e parameter_v>
    auto get_query_object_value                           (gl::handle_t query) -> auto
    {
        using enum gl::query_parameter_e;
        if constexpr (parameter_v == target          ) return static_cast<gl::query_target_e>(legacy::get_query_object_int32_value (query, parameter_v));
        if constexpr (parameter_v == result          ) return                                 legacy::get_query_object_uint32_value(query, parameter_v) ;
        if constexpr (parameter_v == result_available) return static_cast<gl::bool_t        >(legacy::get_query_object_int32_value( query, parameter_v));
        if constexpr (parameter_v == result_no_wait  ) return                                 legacy::get_query_object_uint32_value(query, parameter_v) ;
    }
    template<gl::query_parameter_e parameter_v>
    void get_query_buffer_object_value                    (gl::handle_t query, gl::handle_t buffer, gl::ptrdiff_t offset)
    {
        using enum gl::query_parameter_e;
        if constexpr (parameter_v == target          ) legacy::get_query_buffer_object_int32_value (query, buffer, parameter_v, offset);
        if constexpr (parameter_v == result          ) legacy::get_query_buffer_object_uint32_value(query, buffer, parameter_v, offset);
        if constexpr (parameter_v == result_available) legacy::get_query_buffer_object_int32_value (query, buffer, parameter_v, offset);
        if constexpr (parameter_v == result_no_wait  ) legacy::get_query_buffer_object_uint32_value(query, buffer, parameter_v, offset);
    }



    //Chapter 6 - Buffer Objects
    template<gl::buffer_parameter_e Parameter>
    auto get_buffer_parameter_value                       (gl::handle_t buffer) -> auto
    {
        using enum gl::buffer_parameter_e;
        if constexpr (Parameter == access       ) return static_cast<gl::buffer_mapping_access_e      >(legacy::get_buffer_parameter_int32_value(buffer, Parameter));
        if constexpr (Parameter == access_flags ) return static_cast<gl::buffer_mapping_access_flags_e>(legacy::get_buffer_parameter_int32_value(buffer, Parameter));
        if constexpr (Parameter == is_immutable ) return static_cast<gl::bool_t                       >(legacy::get_buffer_parameter_int32_value(buffer, Parameter));
        if constexpr (Parameter == is_mapped    ) return static_cast<gl::bool_t                       >(legacy::get_buffer_parameter_int32_value(buffer, Parameter));
        if constexpr (Parameter == map_length   ) return static_cast<gl::size_t                       >(legacy::get_buffer_parameter_int64_value(buffer, Parameter));
        if constexpr (Parameter == map_offset   ) return static_cast<gl::size_t                       >(legacy::get_buffer_parameter_int64_value(buffer, Parameter));
        if constexpr (Parameter == size         ) return static_cast<gl::size_t                       >(legacy::get_buffer_parameter_int64_value(buffer, Parameter));
        if constexpr (Parameter == storage_flags) return static_cast<gl::buffer_storage_flags_e       >(legacy::get_buffer_parameter_int32_value(buffer, Parameter));
        if constexpr (Parameter == usage        ) return static_cast<gl::buffer_usage_e               >(legacy::get_buffer_parameter_int32_value(buffer, Parameter));
    }
    template<typename element_t = gl::byte_t>
    auto get_buffer_data                                  (gl::handle_t buffer) -> std::vector<element_t>
    {
        auto const buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        if (buffer_size % sizeof(element_t) != gl::size_t{ 0u }) throw std::invalid_argument{ "buffer can not be partitioned by element" };

        auto       vector      = std::vector<element_t>(buffer_size / sizeof(element_t));
        ::glGetNamedBufferSubData(gl::to_underlying(buffer), gl::intptr_t{ 0 }, static_cast<gl::sizeiptr_t>(buffer_size), vector.data());
        
        return vector;
    }
    template<typename element_t = gl::byte_t>
    auto get_buffer_sub_data                              (gl::handle_t buffer, gl::range_t range) -> std::vector<element_t>
    {
        auto const buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        auto const byte_range  = gl::convert_range<element_t>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        auto       vector      = std::vector<element_t>(range.count);
        ::glGetNamedBufferSubData(gl::to_underlying(buffer), static_cast<gl::intptr_t>(byte_range.offset), static_cast<gl::sizeiptr_t>(byte_range.size), vector.data());
        
        return vector;
    }
    


    //Chapter 7 - Programs and Shaders
    template<gl::shader_parameter_e parameter_v>
    auto get_shader_value                                 (gl::handle_t shader) -> auto
    {
        using enum gl::shader_parameter_e;
        if constexpr (parameter_v == compile_status ) return static_cast<gl::bool_t       >(legacy::get_shader_value(shader, parameter_v));
        if constexpr (parameter_v == delete_status  ) return static_cast<gl::bool_t       >(legacy::get_shader_value(shader, parameter_v));
        if constexpr (parameter_v == info_log_length) return static_cast<gl::size_t       >(legacy::get_shader_value(shader, parameter_v));
        if constexpr (parameter_v == source_length  ) return static_cast<gl::size_t       >(legacy::get_shader_value(shader, parameter_v));
        if constexpr (parameter_v == type           ) return static_cast<gl::shader_type_e>(legacy::get_shader_value(shader, parameter_v));
    }
    template<gl::program_parameter_e parameter_v>
    auto get_program_value                                (gl::handle_t program) -> auto
    {
        using enum gl::program_parameter_e;
        if constexpr (parameter_v == active_atomic_counter_buffers            ) return static_cast<gl::uint32_t                        >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == active_attribute_maximum_length          ) return static_cast<gl::size_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == active_attributes                        ) return static_cast<gl::uint32_t                        >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == active_uniform_block_maximum_name_length ) return static_cast<gl::size_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == active_uniform_blocks                    ) return static_cast<gl::uint32_t                        >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == active_uniform_maximum_length            ) return static_cast<gl::size_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == active_uniforms                          ) return static_cast<gl::uint32_t                        >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == attached_shaders                         ) return static_cast<gl::uint32_t                        >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == binary_length                            ) return static_cast<gl::size_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == compute_work_group_size                  ) return static_cast<gl::size_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == delete_status                            ) return static_cast<gl::bool_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == geometry_input_type                      ) return static_cast<gl::draw_mode_e                     >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == geometry_output_type                     ) return static_cast<gl::draw_mode_e                     >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == geometry_shader_invocations              ) return static_cast<gl::uint32_t                        >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == geometry_vertices_out                    ) return static_cast<gl::uint32_t                        >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == info_log_length                          ) return static_cast<gl::size_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == is_binary_retrievable                    ) return static_cast<gl::bool_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == is_separable                             ) return static_cast<gl::bool_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == link_status                              ) return static_cast<gl::bool_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == tessellation_control_output_vertices     ) return static_cast<gl::uint32_t                        >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == tessellation_generation_mode             ) return static_cast<gl::tessellation_generation_e       >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == tessellation_generation_point_mode       ) return static_cast<gl::bool_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == tessellation_generation_spacing          ) return static_cast<gl::tessellation_spacing_e          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == tessellation_generation_vertex_order     ) return static_cast<gl::tessellation_vertex_order_e     >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == transform_feedback_buffer_mode           ) return static_cast<gl::transform_feedback_buffer_mode_e>(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == transform_feedback_varying_maximum_length) return static_cast<gl::size_t                          >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == transform_feedback_varyings              ) return static_cast<gl::uint32_t                        >(legacy::get_program_value(program, parameter_v));
        if constexpr (parameter_v == validate_status                          ) return static_cast<gl::bool_t                          >(legacy::get_program_value(program, parameter_v));
    }
    template<gl::pipeline_property_e property_v>
    auto get_program_pipeline_value                       (gl::handle_t pipeline) -> auto
    {
        using enum gl::pipeline_property_e;
        if   constexpr (property_v == validate_status) return static_cast<gl::bool_t  >(legacy::get_program_pipeline_value(pipeline, property_v));
        if   constexpr (property_v == info_log_length) return static_cast<gl::size_t  >(legacy::get_program_pipeline_value(pipeline, property_v));
        else                                           return static_cast<gl::handle_t>(legacy::get_program_pipeline_value(pipeline, property_v));
    }
    auto get_attached_shaders                             (gl::handle_t program) -> std::vector<gl::handle_t>
    {
        auto const attached_shaders = gl::get_program_value<gl::program_parameter_e::attached_shaders>(program);
        auto       vector           = std::vector<gl::handle_t>(attached_shaders);
        ::glGetAttachedShaders(gl::to_underlying(program), static_cast<gl::sizei_t>(attached_shaders), nullptr, gl::to_underlying_pointer(vector.data()));
        
        return vector;
    }
    auto get_shader_info_log                              (gl::handle_t shader) -> std::string
    {
        auto const info_log_length = get_shader_value<gl::shader_parameter_e::info_log_length>(shader);
        auto       info_log        = std::string(info_log_length, '\0');
        
        if (!info_log.empty())
        {
            ::glGetShaderInfoLog(gl::to_underlying(shader), static_cast<gl::sizei_t>(info_log_length), nullptr, info_log.data());
            info_log.pop_back();
        }

        return info_log;
    }
    auto get_program_info_log                             (gl::handle_t program) -> std::string
    {
        auto const info_log_length = gl::get_program_value<gl::program_parameter_e::info_log_length>(program);
        auto       info_log        = std::string(info_log_length, '\0');
        
        if (!info_log.empty())
        {
            ::glGetProgramInfoLog(gl::to_underlying(program), static_cast<gl::sizei_t>(info_log_length), nullptr, info_log.data());
            info_log.pop_back();
        }

        return info_log;
    }
    auto get_pipeline_info_log                            (gl::handle_t pipeline) -> std::string
    {
        auto const info_log_length = gl::get_program_pipeline_value<gl::pipeline_property_e::info_log_length>(pipeline);
        auto       info_log        = std::string(info_log_length, '\0');
        
        if (!info_log.empty())
        {
            ::glGetProgramPipelineInfoLog(gl::to_underlying(pipeline), static_cast<gl::sizei_t>(info_log_length), nullptr, info_log.data());
            info_log.pop_back();
        }

        return info_log;
    }
    auto get_shader_source                                (gl::handle_t shader) -> std::string
    {
        auto const shader_source_length = get_shader_value<gl::shader_parameter_e::source_length>(shader);
        auto       shader_source        = std::string(shader_source_length, '\0');
        
        if (!shader_source.empty())
        {
            ::glGetShaderSource(gl::to_underlying(shader), static_cast<gl::sizei_t>(shader_source_length), nullptr, shader_source.data());
            shader_source.pop_back();
        }

        return shader_source;
    }
    auto get_shader_precision_format                      (gl::shader_type_e shader_type, gl::shader_precision_format_e shader_precision_format) -> std::tuple<gl::vector_2i, gl::int32_t>
    {
        auto range     = gl::vector_2i{};
        auto precision = gl::int32_t{};
        ::glGetShaderPrecisionFormat(gl::to_underlying(shader_type), gl::to_underlying(shader_precision_format), gl::value_pointer(range), &precision);
        
        return std::make_tuple(range, precision);
    }



    //Chapter 8 - Textures and Samplers
    template<gl::sampler_parameter_e parameter_v>
    auto get_sampler_parameter_value                      (gl::handle_t sampler) -> auto
    {
        using enum gl::sampler_parameter_e;
        if constexpr (parameter_v == border_color        )
        {
            auto const value = legacy::get_sampler_parameter_float32_value(sampler, parameter_v, 4u);
            return gl::vector_4f{ value[0u], value[1u], value[2u], value[3u] };
        }
        if constexpr (parameter_v == compare_function    ) return static_cast<gl::texture_compare_function_e    >(legacy::get_sampler_parameter_uint32_value (sampler, parameter_v));
        if constexpr (parameter_v == compare_mode        ) return static_cast<gl::texture_compare_mode_e        >(legacy::get_sampler_parameter_uint32_value (sampler, parameter_v));
        if constexpr (parameter_v == lod_bias            ) return                                                (legacy::get_sampler_parameter_float32_value(sampler, parameter_v));
        if constexpr (parameter_v == magnification_filter) return static_cast<gl::texture_magnification_filter_e>(legacy::get_sampler_parameter_uint32_value (sampler, parameter_v));
        if constexpr (parameter_v == maximum_anisotropy  ) return                                                (legacy::get_sampler_parameter_float32_value(sampler, parameter_v));
        if constexpr (parameter_v == maximum_lod         ) return                                                (legacy::get_sampler_parameter_float32_value(sampler, parameter_v));
        if constexpr (parameter_v == minification_filter ) return static_cast<gl::texture_minification_filter_e >(legacy::get_sampler_parameter_uint32_value (sampler, parameter_v));
        if constexpr (parameter_v == minimum_lod         ) return                                                (legacy::get_sampler_parameter_float32_value(sampler, parameter_v));
        if constexpr (parameter_v == wrapping_r          ) return static_cast<gl::texture_wrapping_e            >(legacy::get_sampler_parameter_uint32_value (sampler, parameter_v));
        if constexpr (parameter_v == wrapping_s          ) return static_cast<gl::texture_wrapping_e            >(legacy::get_sampler_parameter_uint32_value (sampler, parameter_v));
        if constexpr (parameter_v == wrapping_t          ) return static_cast<gl::texture_wrapping_e            >(legacy::get_sampler_parameter_uint32_value (sampler, parameter_v));
    }
    template<gl::texture_parameter_e parameter_v>
    auto get_texture_parameter_value                      (gl::handle_t texture) -> auto
    {
        using enum gl::texture_parameter_e;
        if constexpr (parameter_v == base_level          ) return static_cast<gl::uint32_t                      >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == border_color        )
        {
            auto const value = legacy::get_texture_parameter_float32_value(texture, parameter_v, 4u);
            return gl::vector_4f{ value[0u], value[1u], value[2u], value[3u] };
        }
        if constexpr (parameter_v == compare_function    ) return static_cast<gl::texture_compare_function_e    >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == compare_mode        ) return static_cast<gl::texture_compare_mode_e        >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == depth_stencil_mode  ) return static_cast<gl::depth_stencil_texture_mode_e  >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == lod_bias            ) return                                                 legacy::get_texture_parameter_float32_value(texture, parameter_v);
        if constexpr (parameter_v == magnification_filter) return static_cast<gl::texture_magnification_filter_e>(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == maximum_anisotropy  ) return                                                 legacy::get_texture_parameter_float32_value(texture, parameter_v);
        if constexpr (parameter_v == maximum_level       ) return static_cast<gl::uint32_t                      >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == maximum_lod         ) return                                                 legacy::get_texture_parameter_float32_value(texture, parameter_v);
        if constexpr (parameter_v == minification_filter ) return static_cast<gl::texture_minification_filter_e >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == minimum_lod         ) return                                                 legacy::get_texture_parameter_float32_value(texture, parameter_v);
        if constexpr (parameter_v == swizzle_a           ) return static_cast<gl::texture_swizzle_e             >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == swizzle_b           ) return static_cast<gl::texture_swizzle_e             >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == swizzle_g           ) return static_cast<gl::texture_swizzle_e             >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == swizzle_r           ) return static_cast<gl::texture_swizzle_e             >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == swizzle_rgba        ) return static_cast<gl::texture_swizzle_e             >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == target              ) return static_cast<gl::texture_target_e              >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == wrapping_r          ) return static_cast<gl::texture_wrapping_e            >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == wrapping_s          ) return static_cast<gl::texture_wrapping_e            >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
        if constexpr (parameter_v == wrapping_t          ) return static_cast<gl::texture_wrapping_e            >(legacy::get_texture_parameter_int32_value  (texture, parameter_v));
    }
    template<gl::texture_level_parameter_e parameter_v>
    auto get_texture_level_parameter_value                (gl::handle_t texture, gl::uint32_t image_level)
    {
        using enum gl::texture_level_parameter_e;
        if constexpr (parameter_v == alpha_size           ) return static_cast<gl::size_t                  >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == alpha_type           ) return static_cast<gl::texture_component_type_e>(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == blue_size            ) return static_cast<gl::size_t                  >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == blue_type            ) return static_cast<gl::texture_component_type_e>(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == buffer_offset        ) return static_cast<gl::ptrdiff_t               >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == buffer_size          ) return static_cast<gl::size_t                  >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == compressed_image_size) return static_cast<gl::size_t                  >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == depth                ) return static_cast<gl::uint32_t                >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == depth_size           ) return static_cast<gl::size_t                  >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == depth_type           ) return static_cast<gl::texture_component_type_e>(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == green_size           ) return static_cast<gl::size_t                  >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == green_type           ) return static_cast<gl::texture_component_type_e>(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == height               ) return static_cast<gl::uint32_t                >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == internal_format      ) return static_cast<gl::enum_t                  >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == is_compressed        ) return static_cast<gl::bool_t                  >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == red_size             ) return static_cast<gl::size_t                  >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == red_type             ) return static_cast<gl::texture_component_type_e>(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
        if constexpr (parameter_v == width                ) return static_cast<gl::uint32_t                >(legacy::get_texture_level_parameter_int32_value(texture, image_level, parameter_v));
    }
    template<typename element_t = gl::byte_t>
    auto get_texture_image                                (gl::handle_t texture, gl::uint32_t image_level,                            gl::buffer_data_descriptor buffer_data_descriptor) -> std::vector<element_t>
    {
        auto const image_width          = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        auto const image_height         = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        auto const image_depth          = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, image_level);

        auto const pixel_count          = image_width * image_height * image_depth;
        auto const pixel_component_size = gl::map_pixel_data_component_size         (buffer_data_descriptor.pixel_data_type);
        auto const pixel_size           = gl::map_buffer_base_format_component_count(buffer_data_descriptor.base_format    ) * pixel_component_size;
        auto const image_size           = pixel_count * pixel_size;
        if (image_size % sizeof(element_t) != gl::size_t{ 0u }) throw std::invalid_argument{ "image can not be partitioned by element" };

        auto       vector               = std::vector<element_t>(image_size / sizeof(element_t));
        ::glGetTextureImage(
            gl::to_underlying       (texture)                           , 
            static_cast<gl::int32_t>(image_level)                       , 
            gl::to_underlying       (buffer_data_descriptor.base_format), gl::to_underlying(buffer_data_descriptor.pixel_data_type), 
            static_cast<gl::sizei_t>(image_size)                        , vector.data()                                           );

        return vector;
    }
    template<typename element_t = gl::byte_t>
    auto get_texture_sub_image                            (gl::handle_t texture, gl::uint32_t image_level, gl::volume_t image_volume, gl::buffer_data_descriptor buffer_data_descriptor) -> std::vector<element_t>
    {
        auto const image_width          = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        auto const image_height         = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        auto const image_depth          = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, image_level);
        if (image_volume.origin.x + image_volume.extent.x > image_width ) throw std::invalid_argument{ "volume width exceeds image width"   };
        if (image_volume.origin.y + image_volume.extent.y > image_height) throw std::invalid_argument{ "volume height exceeds image height" };
        if (image_volume.origin.z                         > image_depth ) throw std::invalid_argument{ "volume depth exceeds image depth"   };

        auto const pixel_count          = image_volume.extent.x * image_volume.extent.y * image_volume.extent.z;
        auto const pixel_component_size = gl::map_pixel_data_component_size         (buffer_data_descriptor.pixel_data_type);
        auto const pixel_size           = gl::map_buffer_base_format_component_count(buffer_data_descriptor.base_format    ) * pixel_component_size;
        auto const image_size           = pixel_count * pixel_size;
        if (image_size % sizeof(element_t) != gl::size_t{ 0u }) throw std::invalid_argument{ "image can not be partitioned by element" };

        auto       vector               = std::vector<element_t>(image_size / sizeof(element_t));
        ::glGetTextureSubImage(
            gl::to_underlying       (texture)                           , 
            static_cast<gl::int32_t>(image_level)                       , 
            static_cast<gl::int32_t>(image_volume.origin.x)             , static_cast<gl::int32_t>(image_volume.origin.y)                 , static_cast<gl::int32_t>(image_volume.origin.z), 
            static_cast<gl::sizei_t>(image_volume.extent.x)             , static_cast<gl::sizei_t>(image_volume.extent.y)                 , static_cast<gl::sizei_t>(image_volume.extent.z), 
            gl::to_underlying       (buffer_data_descriptor.base_format), gl::to_underlying       (buffer_data_descriptor.pixel_data_type), 
            static_cast<gl::sizei_t>(image_size)                        , vector.data()                                                  );

        return vector;
    }
    template<typename element_t = gl::byte_t>
    auto get_compressed_texture_image                     (gl::handle_t texture, gl::uint32_t image_level) -> std::vector<element_t>
    {
        auto const compressed_image_size = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::compressed_image_size>(texture, image_level);
        if (compressed_image_size % sizeof(element_t) != gl::size_t{ 0u }) throw std::invalid_argument{ "image can not be partitioned by element" };

        auto       vector                = std::vector<element_t>(compressed_image_size / sizeof(element_t));
        ::glGetCompressedTextureImage(
            gl::to_underlying       (texture)              , 
            static_cast<gl::int32_t>(image_level)          , 
            static_cast<gl::sizei_t>(compressed_image_size), vector.data());

        return vector;
    }
    template<typename element_t = gl::byte_t>
    auto get_compressed_texture_sub_image                 (gl::handle_t texture, gl::uint32_t image_level, gl::volume_t image_volume) -> std::vector<element_t>
    {
        auto const compressed_image_size   = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::compressed_image_size>(texture, image_level);
        if (compressed_image_size % sizeof(element_t) != gl::size_t{ 0u })        throw std::invalid_argument{ "image can not be partitioned by element" };

        auto const image_width             = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        auto const image_height            = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        auto const image_depth             = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, image_level);
        if (image_volume.origin.x + image_volume.extent.x > image_width ) throw std::invalid_argument{ "volume width exceeds image width"   };
        if (image_volume.origin.y + image_volume.extent.y > image_height) throw std::invalid_argument{ "volume height exceeds image height" };
        if (image_volume.origin.z                         > image_depth ) throw std::invalid_argument{ "volume depth exceeds image depth"   };
        
        auto const compressed_block_width  = gl::get_value<gl::data_e::pack_compressed_block_width >();
        auto const compressed_block_height = gl::get_value<gl::data_e::pack_compressed_block_height>();
        auto const compressed_block_depth  = gl::get_value<gl::data_e::pack_compressed_block_depth >();
        if ((image_volume.extent.x != image_width  || image_volume.origin.x != 0u) && image_volume.origin.x % compressed_block_width  != gl::size_t{ 0u }) throw std::invalid_argument{ "volume width exceeds image width"   };
        if ((image_volume.extent.y != image_height || image_volume.origin.y != 0u) && image_volume.origin.y % compressed_block_height != gl::size_t{ 0u }) throw std::invalid_argument{ "volume height exceeds image height" };
        if ((image_volume.extent.z != image_width  || image_volume.origin.z != 0u) && image_volume.origin.z % compressed_block_depth  != gl::size_t{ 0u }) throw std::invalid_argument{ "volume depth exceeds image depth"   };

        auto       vector                  = std::vector<element_t>(compressed_image_size / sizeof(element_t));
        ::glGetCompressedTextureSubImage(
            gl::to_underlying       (texture)              , 
            static_cast<gl::int32_t>(image_level)          , 
            static_cast<gl::int32_t>(image_volume.origin.x), static_cast<gl::int32_t>(image_volume.origin.y), static_cast<gl::int32_t>(image_volume.origin.z), 
            static_cast<gl::sizei_t>(image_volume.extent.x), static_cast<gl::sizei_t>(image_volume.extent.y), static_cast<gl::sizei_t>(image_volume.extent.z), 
            static_cast<gl::sizei_t>(compressed_image_size), vector.data()                                 );

        return vector;
    }



    //Chapter 9 - FrameBuffer and FrameBuffer Objects
    template<gl::frame_buffer_parameter_e parameter_v>
    auto get_frame_buffer_parameter_value                 (gl::handle_t frame_buffer) -> auto
    {
        using enum gl::frame_buffer_parameter_e;
        if constexpr (parameter_v  == default_width                     ) return static_cast<gl::uint32_t           >(legacy::get_frame_buffer_parameter_int32_value(frame_buffer, parameter_v));
        if constexpr (parameter_v  == default_height                    ) return static_cast<gl::uint32_t           >(legacy::get_frame_buffer_parameter_int32_value(frame_buffer, parameter_v));
        if constexpr (parameter_v  == default_layers                    ) return static_cast<gl::uint32_t           >(legacy::get_frame_buffer_parameter_int32_value(frame_buffer, parameter_v));
        if constexpr (parameter_v  == default_samples                   ) return static_cast<gl::uint32_t           >(legacy::get_frame_buffer_parameter_int32_value(frame_buffer, parameter_v));
        if constexpr (parameter_v  == has_default_fixed_sample_locations) return static_cast<gl::bool_t             >(legacy::get_frame_buffer_parameter_int32_value(frame_buffer, parameter_v));
        if constexpr (parameter_v  == color_read_format                 ) return static_cast<gl::pixel_data_format_e>(legacy::get_frame_buffer_parameter_int32_value(frame_buffer, parameter_v));
        if constexpr (parameter_v  == color_read_type                   ) return static_cast<gl::pixel_data_type_e  >(legacy::get_frame_buffer_parameter_int32_value(frame_buffer, parameter_v));
        if constexpr (parameter_v  == is_double_buffered                ) return static_cast<gl::bool_t             >(legacy::get_frame_buffer_parameter_int32_value(frame_buffer, parameter_v));
        if constexpr (parameter_v  == sample_buffers                    ) return static_cast<gl::uint32_t           >(legacy::get_frame_buffer_parameter_int32_value(frame_buffer, parameter_v));
        if constexpr (parameter_v  == samples                           ) return static_cast<gl::uint32_t           >(legacy::get_frame_buffer_parameter_int32_value(frame_buffer, parameter_v));
        if constexpr (parameter_v  == supports_stereo                   ) return static_cast<gl::bool_t             >(legacy::get_frame_buffer_parameter_int32_value(frame_buffer, parameter_v));
    }
    template<gl::frame_buffer_attachment_parameter_e parameter_v>
    auto get_frame_buffer_attachment_parameter_value      (gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment) -> auto
    {
        using enum gl::frame_buffer_attachment_parameter_e;
        if constexpr (parameter_v == alpha_size          ) return static_cast<gl::size_t                                  >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == blue_size           ) return static_cast<gl::size_t                                  >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == color_encoding      ) return static_cast<gl::color_encoding_e                        >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == component_type      ) return static_cast<gl::frame_buffer_attachment_component_type_e>(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == depth_size          ) return static_cast<gl::size_t                                  >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == green_size          ) return static_cast<gl::size_t                                  >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == is_layered          ) return static_cast<gl::bool_t                                  >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == object_name         ) return static_cast<gl::handle_t                                >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == object_type         ) return static_cast<gl::frame_buffer_attachment_object_type_e   >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == red_size            ) return static_cast<gl::size_t                                  >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == stencil_size        ) return static_cast<gl::size_t                                  >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == texture_cubemap_face) return static_cast<gl::cubemap_face_e                          >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == texture_layer       ) return static_cast<gl::uint32_t                                >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
        if constexpr (parameter_v == texture_level       ) return static_cast<gl::uint32_t                                >(legacy::get_frame_buffer_attachment_parameter_int32_value(frame_buffer, attachment, parameter_v));
    }
    template<gl::render_buffer_parameter_e parameter_v>
    auto get_render_buffer_parameter_value                (gl::handle_t render_buffer) -> auto
    {
        using enum gl::render_buffer_parameter_e;
        if constexpr (parameter_v == width          ) return static_cast<gl::uint32_t             >(legacy::get_render_buffer_parameter_int32_value(render_buffer, parameter_v));
        if constexpr (parameter_v == height         ) return static_cast<gl::uint32_t             >(legacy::get_render_buffer_parameter_int32_value(render_buffer, parameter_v));
        if constexpr (parameter_v == internal_format) return static_cast<gl::frame_buffer_format_e>(legacy::get_render_buffer_parameter_int32_value(render_buffer, parameter_v));
        if constexpr (parameter_v == samples        ) return static_cast<gl::uint32_t             >(legacy::get_render_buffer_parameter_int32_value(render_buffer, parameter_v));
        if constexpr (parameter_v == red_size       ) return static_cast<gl::size_t               >(legacy::get_render_buffer_parameter_int32_value(render_buffer, parameter_v));
        if constexpr (parameter_v == green_size     ) return static_cast<gl::size_t               >(legacy::get_render_buffer_parameter_int32_value(render_buffer, parameter_v));
        if constexpr (parameter_v == blue_size      ) return static_cast<gl::size_t               >(legacy::get_render_buffer_parameter_int32_value(render_buffer, parameter_v));
        if constexpr (parameter_v == alpha_size     ) return static_cast<gl::size_t               >(legacy::get_render_buffer_parameter_int32_value(render_buffer, parameter_v));
        if constexpr (parameter_v == depth_size     ) return static_cast<gl::size_t               >(legacy::get_render_buffer_parameter_int32_value(render_buffer, parameter_v));
        if constexpr (parameter_v == stencil_size   ) return static_cast<gl::size_t               >(legacy::get_render_buffer_parameter_int32_value(render_buffer, parameter_v));
    }



    //Chapter 10 - Vertex Specification and Drawing Commands
    template<gl::vertex_array_parameter_e     parameter_v>
    auto get_vertex_array_indexed_value                   (gl::handle_t vertex_array) -> auto
    {
        if constexpr (parameter_v == gl::vertex_array_parameter_e::element_array_buffer_binding) return static_cast<gl::handle_t>(legacy::get_vertex_array_int32_value(vertex_array, parameter_v));
    }
    template<gl::vertex_array_parameter_e     parameter_v>
    auto get_vertex_array_indexed_value                   (gl::handle_t vertex_array, gl::index_t index) -> auto
    {
        using enum gl::vertex_array_parameter_e;
        if constexpr (parameter_v == binding_offset ) return static_cast<gl::ptrdiff_t                    >(legacy::get_vertex_array_int64_value_index(vertex_array, parameter_v, index));
        if constexpr (parameter_v == divisor        ) return static_cast<gl::uint32_t                     >(legacy::get_vertex_array_int32_value_index(vertex_array, parameter_v, index));
        if constexpr (parameter_v == is_enabled     ) return static_cast<gl::bool_t                       >(legacy::get_vertex_array_int32_value_index(vertex_array, parameter_v, index));
        if constexpr (parameter_v == is_integer_data) return static_cast<gl::bool_t                       >(legacy::get_vertex_array_int32_value_index(vertex_array, parameter_v, index));
        if constexpr (parameter_v == is_long_data   ) return static_cast<gl::bool_t                       >(legacy::get_vertex_array_int32_value_index(vertex_array, parameter_v, index));
        if constexpr (parameter_v == is_normalized  ) return static_cast<gl::bool_t                       >(legacy::get_vertex_array_int32_value_index(vertex_array, parameter_v, index));
        if constexpr (parameter_v == relative_offset) return static_cast<gl::ptrdiff_t                    >(legacy::get_vertex_array_int32_value_index(vertex_array, parameter_v, index));
        if constexpr (parameter_v == size           ) return static_cast<gl::size_t                       >(legacy::get_vertex_array_int32_value_index(vertex_array, parameter_v, index));
        if constexpr (parameter_v == stride         ) return static_cast<gl::size_t                       >(legacy::get_vertex_array_int32_value_index(vertex_array, parameter_v, index));
        if constexpr (parameter_v == type           ) return static_cast<gl::vertex_array_attribute_type_e>(legacy::get_vertex_array_int32_value_index(vertex_array, parameter_v, index));
    }



    //Chapter 20 - Debug Output
    auto get_debug_message_log(gl::count_t count) -> std::vector<gl::message_log>
    {
        auto const maximum_debug_message_length = static_cast<gl::size_t>(gl::get_value<gl::data_e::maximum_debug_message_length>());
        auto const message_log_length           = count * maximum_debug_message_length;
    
        auto       sources                      = std::vector<gl::debug_source_e  >(count);
        auto       types                        = std::vector<gl::debug_type_e    >(count);
        auto       ids                          = std::vector<gl::uint32_t        >(count);
        auto       severities                   = std::vector<gl::debug_severity_e>(count);
        auto       lengths                      = std::vector<gl::sizei_t         >(count);
        auto       buffer                       = std::string(message_log_length, '\0');
    
        auto const retrieved_message_count      = ::glGetDebugMessageLog(
            static_cast<gl::uint32_t>(count)             , 
            static_cast<gl::sizei_t> (message_log_length), 
            gl::to_underlying_pointer(sources   .data()) , 
            gl::to_underlying_pointer(types     .data()) , 
                                      ids       .data()  , 
            gl::to_underlying_pointer(severities.data()) , 
                                      lengths   .data()  , 
                                      buffer    .data() );
        auto       messages                     = std::vector<gl::message_log>(retrieved_message_count);
        auto       offset                       = gl::offset_t{ 0u };

        for (auto i = gl::index_t{ 0u }; i < retrieved_message_count; ++i)
        {
            messages[i] = gl::message_log
            {
                .id       = ids[i],
                .source   = sources[i],
                .type     = types[i],
                .severity = severities[i],
                .message  = std::string(buffer.data() + offset, lengths[i])
            };

            offset += lengths[i];
        }
    
        return messages;
    }





    //Chapter 2 - OpenGL Fundamentals
    auto get_graphics_reset_status                        () -> gl::error_graphics_reset_status_e
    {
        return static_cast<gl::error_graphics_reset_status_e>(::glGetGraphicsResetStatus());
    }
    void flush                                            ()
    {
        ::glFlush();
    }
    void finish                                           ()
    {
        ::glFinish();
    }



    //Chapter 4 - Event Model
    auto fence_sync                                       () -> gl::sync_t
    {
        return static_cast<gl::sync_t>(::glFenceSync(gl::to_underlying(gl::synchronization_object_condition_e::gpu_commands_complete), gl::bitfield_t{ 0u }));
    }
    void delete_sync                                      (gl::sync_t sync)
    {
        if (sync) ::glDeleteSync(sync);
    }
    auto client_wait_sync                                 (gl::sync_t sync, gl::synchronization_command_e synchronization_command, gl::time_t timeout) -> gl::synchronization_status_e
    {
        return static_cast<gl::synchronization_status_e>(::glClientWaitSync(sync, gl::to_underlying(synchronization_command), timeout));
    }
    void server_wait_sync                                 (gl::sync_t sync)
    {
        ::glWaitSync(sync, gl::bitfield_t{ 0u }, gl::to_underlying(gl::synchronization_timeout_e::ignored));
    }
    auto create_query                                     (gl::query_target_e target) -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        ::glCreateQueries(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle));
        
        return handle;
    }
    auto create_queries                                   (gl::query_target_e target, gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        ::glCreateQueries(gl::to_underlying(target), static_cast<gl::sizei_t>(count), gl::to_underlying_pointer(handles.data()));
        
        return handles;
    }
    void delete_query                                     (gl::handle_t query)
    {
        ::glDeleteQueries(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&query));
    }
    void delete_queries                                   (std::span<const gl::handle_t> queries)
    {
        ::glDeleteQueries(static_cast<gl::sizei_t>(queries.size()), gl::to_underlying_pointer(queries.data()));
    }
    void begin_query                                      (gl::handle_t query, gl::query_target_e target)
    {
        ::glBeginQuery(gl::to_underlying(target), gl::to_underlying(query));
    }
    void begin_query_index                                (gl::handle_t query, gl::query_target_e target, gl::index_t index)
    {
        ::glBeginQueryIndexed(gl::to_underlying(target), static_cast<gl::uint32_t>(index), gl::to_underlying(query));
    }
    void end_query                                        (gl::query_target_e target)
    {
        ::glEndQuery(gl::to_underlying(target));
    }
    void end_query_index                                  (gl::query_target_e target, gl::index_t index)
    {
        ::glEndQueryIndexed(gl::to_underlying(target), static_cast<gl::uint32_t>(index));
    }
    void query_counter                                    (gl::handle_t query)
    {
        ::glQueryCounter(gl::to_underlying(query), gl::to_underlying(gl::query_counter_e::timestamp));
    }



    //Chapter 6 - Buffer Objects
    auto create_buffer                                    () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        ::glCreateBuffers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle));
        
        return handle;
    }
    auto create_buffers                                   (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        ::glCreateBuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data()));
        
        return handles;
    }
    void delete_buffer                                    (gl::handle_t buffer)
    {
        ::glDeleteBuffers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&buffer));
    }
    void delete_buffers                                   (std::span<const gl::handle_t> buffers)
    {
        ::glDeleteBuffers(static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_pointer(buffers.data()));
    }
    void bind_buffer                                      (gl::handle_t buffer, gl::buffer_target_e           target                       )
    {
        ::glBindBuffer(gl::to_underlying(target), gl::to_underlying(buffer));
    }
    void bind_buffer_base                                 (gl::handle_t buffer, gl::buffer_base_target_e base_target, gl::binding_t binding)
    {
        ::glBindBufferBase(gl::to_underlying(base_target), binding, gl::to_underlying(buffer));
    }
    void bind_buffers_base                                (std::span<const gl::handle_t> buffers, gl::buffer_base_target_e target, gl::binding_t start_binding)
    {
        ::glBindBuffersBase(gl::to_underlying(target), start_binding, static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_pointer(buffers.data()));
    }
    template<typename T = gl::byte_t>
    void bind_buffer_range                                (gl::handle_t                  buffer , gl::buffer_base_target_e base_target, gl::binding_t binding,                 gl::range_t  range )
    {
        const auto buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto byte_range  = gl::convert_range<T>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        ::glBindBufferRange(
            gl::to_underlying        (base_target)      , gl::to_underlying          (binding)         , gl::to_underlying(buffer), 
            static_cast<gl::intptr_t>(byte_range.offset), static_cast<gl::sizeiptr_t>(byte_range.size));
    }
    template<typename T = gl::byte_t>
    void bind_buffers_range                               (std::span<const gl::handle_t> buffers, gl::buffer_base_target_e base_target, gl::binding_t binding, std::span<const gl::range_t> ranges)
    {
        const auto sizes   = std::vector<gl::size_t  >(ranges.size());
        const auto offsets = std::vector<gl::intptr_t>(ranges.size());
        for (std::tuple<gl::handle_t&, gl::range_t&> value : std::views::zip(buffers, ranges))
        {
            const auto buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(std::get<0u>(value));
            const auto byte_range  = gl::convert_range<T>(std::get<1u>(value));
            
            sizes  .emplace_back(byte_range.size  );
            offsets.emplace_back(byte_range.offset);
        }

        ::glBindBuffersRange(
            gl::to_underlying        (base_target)   , gl::to_underlying        (binding)       , 
            static_cast<gl::sizei_t >(buffers.size()), gl::to_underlying_pointer(buffers.data()), 
            static_cast<gl::intptr_t>(offsets.data()), static_cast<gl::intptr_t>(sizes.data()) );
    }
    template<typename T = gl::byte_t>
    void buffer_storage                                   (gl::handle_t buffer, gl::buffer_storage_flags_e flags, gl::count_t element_count)
    {
        ::glNamedBufferStorage(
            gl::to_underlying(buffer), static_cast<gl::sizeiptr_t>(element_count * sizeof(T)), 
            nullptr                  , gl::to_underlying          (flags)                   );
    }
    template<typename T = gl::byte_t>
    void buffer_storage                                   (gl::handle_t buffer, gl::buffer_storage_flags_e flags, std::span<const T> memory)
    {
        ::glNamedBufferStorage(
            gl::to_underlying(buffer), static_cast<gl::sizeiptr_t>(memory.size_bytes()), 
            memory.data()            , gl::to_underlying          (flags)             );
    }
    template<typename T = gl::byte_t>
    void buffer_sub_data                                  (gl::handle_t buffer, gl::index_t index, std::span<const T> memory)
    {
        const auto buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto byte_range  = gl::byte_range_t{ index * sizeof(T), memory.size_bytes() };
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        ::glNamedBufferSubData(
            gl::to_underlying          (buffer)           , 
            static_cast<gl::intptr_t  >(byte_range.offset), 
            static_cast<gl::sizeiptr_t>(byte_range.size)  , memory.data());
    }
    template<typename T = gl::byte_t>
    void clear_buffer_data                                (gl::handle_t buffer, gl::buffer_base_format_e base_format, gl::buffer_format_e format, gl::data_type_e data_type,                    T value)
    {
        const auto base_format_component_count = gl::map_buffer_base_format_component_count(base_format);
        const auto data_type_size              = gl::map_data_type_size                    (data_type  );
        if (base_format_component_count * data_type_size > sizeof(T)) throw std::invalid_argument{ "base format and type do not match clear value" };

        ::glClearNamedBufferData(
            gl::to_underlying(buffer)     , gl::to_underlying(format)   , 
            gl::to_underlying(base_format), gl::to_underlying(data_type), 
            &value                       );
    }
    template<typename T = gl::byte_t>
    void clear_buffer_sub_data                            (gl::handle_t buffer, gl::buffer_base_format_e base_format, gl::buffer_format_e format, gl::data_type_e data_type, gl::range_t range, T value)
    {
        const auto buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto byte_range  = gl::convert_range<T>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        const auto base_format_component_count = gl::map_buffer_base_format_component_count(base_format);
        const auto data_type_size              = gl::map_data_type_size                    (data_type  );
        if (base_format_component_count * data_type_size > sizeof(T)) throw std::invalid_argument{ "base format and type do not match clear value" };

        ::glClearNamedBufferSubData(
            gl::to_underlying        (buffer)           , gl::to_underlying          (format)         , 
            static_cast<gl::intptr_t>(byte_range.offset), static_cast<gl::sizeiptr_t>(byte_range.size), 
            gl::to_underlying        (base_format)      , gl::to_underlying          (data_type)      , 
            &value                                     );
    }
    template<typename T = gl::byte_t>
    auto map_buffer                                       (gl::handle_t buffer, gl::buffer_mapping_range_access_flags_e range_access_flags                   ) -> std::span<T>
    {
        const auto  buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        if (buffer_size % sizeof(T) != gl::size_t{ 0u }) throw std::invalid_argument{ "buffer size is not divisible by type size" };
        
              auto* pointer     = ::glMapNamedBufferRange(gl::to_underlying(buffer), gl::intptr_t{ 0 }, static_cast<gl::sizeiptr_t>(buffer_size), gl::to_underlying(range_access_flags));
        if (!pointer) throw std::runtime_error{ "failed to map buffer" };
        
        return std::span{ reinterpret_cast<T*>(pointer), buffer_size / sizeof(T) };
    }
    template<typename T = gl::byte_t>
    auto map_buffer_range                                 (gl::handle_t buffer, gl::buffer_mapping_range_access_flags_e range_access_flags, gl::range_t range) -> std::span<T>
    {
        const auto  buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto  byte_range  = gl::convert_range<T>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

              auto* pointer     = ::glMapNamedBufferRange(gl::to_underlying(buffer), static_cast<gl::intptr_t>(byte_range.offset), static_cast<gl::sizeiptr_t>(byte_range.size), gl::to_underlying(range_access_flags));
        if (!pointer) throw std::runtime_error{ "failed to map buffer" };

        return std::span{ reinterpret_cast<T*>(pointer), range.count };
    }
    template<typename T = gl::byte_t>
    void flush_buffer                                     (gl::handle_t buffer)
    {
        const auto buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        ::glFlushMappedNamedBufferRange(gl::to_underlying(buffer), gl::intptr_t{ 0u }, static_cast<gl::sizeiptr_t>(buffer_size));
    }
    template<typename T = gl::byte_t>
    void flush_buffer_range                               (gl::handle_t buffer, gl::range_t range)
    {
        const auto  buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto  byte_range  = gl::convert_range<T>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        ::glFlushMappedNamedBufferRange(
            gl::to_underlying         (buffer)          , 
            static_cast<gl::intptr_t>(byte_range.offset), static_cast<gl::sizeiptr_t>(byte_range.size));
    }
    auto unmap_buffer                                     (gl::handle_t buffer) -> gl::bool_t
    {
        return ::glUnmapNamedBuffer(gl::to_underlying(buffer));
    }
    void invalidate_buffer_data                           (gl::handle_t buffer)
    {
        ::glInvalidateBufferData(gl::to_underlying(buffer));
    }
    template<typename T = gl::byte_t>
    void invalidate_buffer_sub_data                       (gl::handle_t buffer, gl::range_t range)
    {
        const auto  buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto  byte_range  = gl::convert_range<T>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        ::glInvalidateBufferSubData(
            gl::to_underlying        (buffer)           , 
            static_cast<gl::intptr_t>(byte_range.offset), static_cast<gl::sizeiptr_t>(byte_range.size));
    }
    template<typename T = gl::byte_t>
    void copy_buffer_sub_data                             (gl::handle_t source_buffer, gl::handle_t destination_buffer, gl::range_t source_range, gl::index_t destination_index)
    {
        const auto  source_buffer_size      = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(source_buffer     );
        const auto  destination_buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(destination_buffer);
        const auto  source_byte_range       = gl::convert_range<T>(source_range);
        if (source_byte_range.offset + source_byte_range.size > source_buffer_size     ) throw std::invalid_argument{ "range exceeds source buffer bounds"      };
        if (source_byte_range.offset + source_byte_range.size > destination_buffer_size) throw std::invalid_argument{ "range exceeds destination buffer bounds" };

        ::glCopyNamedBufferSubData(
            gl::to_underlying          (source_buffer)           , gl::to_underlying        (destination_buffer)           , 
            static_cast<gl::intptr_t  >(source_byte_range.offset), static_cast<gl::intptr_t>(destination_index * sizeof(T)), 
            static_cast<gl::sizeiptr_t>(source_byte_range.size) );
    }
    


    //Chapter 7 - Programs and Shaders
    auto create_shader                                    (gl::shader_type_e type) -> gl::handle_t
    {
        return static_cast<gl::handle_t>(::glCreateShader(gl::to_underlying(type)));
    }
    void shader_source                                    (gl::handle_t shader, const std::string& source_code)
    {
        const auto* c_string = source_code.c_str();
        ::glShaderSource(gl::to_underlying(shader), gl::sizei_t{ 1 }, &c_string, nullptr);
    }
    void compile_shader                                   (gl::handle_t shader)
    {
        ::glCompileShader(gl::to_underlying(shader));
    }
    void release_shader_compiler                          ()
    {
        ::glReleaseShaderCompiler();
    }
    void delete_shader                                    (gl::handle_t shader)
    {
        ::glDeleteShader(gl::to_underlying(shader));
    }
    void shader_binary                                    (                gl::handle_t  shader , gl::shader_binary_format_e binary_format, std::span<const gl::byte_t> binary)
    {
        ::glShaderBinary(
            gl::sizei_t{ 1 }                  , 
            gl::to_underlying_pointer(&shader), gl::to_underlying       (binary_format)       , 
            binary.data()                     , static_cast<gl::sizei_t>(binary.size_bytes()));
    }
    void shader_binaries                                  (std::span<const gl::handle_t> shaders, gl::enum_t                        format, std::span<const gl::byte_t> binary)
    {
        ::glShaderBinary(
            static_cast<gl::sizei_t> (shaders.size())      , 
            gl::to_underlying_pointer(shaders.data())      , format, binary.data(), 
            static_cast<gl::sizei_t> (binary.size_bytes()));
    }
    void specialize_shader                                (gl::handle_t shader, const std::string& entry_point, std::span<const gl::uint32_t> indices = {}, std::span<const gl::uint32_t> values = {})
    {
        const auto* c_string = entry_point.c_str();
        const auto  count    = std::min(indices.size(), values.size());
        ::glSpecializeShader(gl::to_underlying(shader), c_string, static_cast<gl::uint32_t>(count), indices.data(), values.data());
    }
    auto create_program                                   () -> gl::handle_t
    {
        return static_cast<gl::handle_t>(::glCreateProgram());
    }
    void attach_shader                                    (gl::handle_t program, gl::handle_t shader)
    {
        ::glAttachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    void detach_shader                                    (gl::handle_t program, gl::handle_t shader)
    {
        ::glDetachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    void link_program                                     (gl::handle_t program)
    {
        ::glLinkProgram(gl::to_underlying(program));
    }
    template<gl::program_specification_e Specification>
    void program_parameter                                (gl::handle_t program, gl::bool_t value)
    {
        ::glProgramParameteri(gl::to_underlying(program), gl::to_underlying(Specification), value);
    }
    void delete_program                                   (gl::handle_t program)
    {
        ::glDeleteProgram(gl::to_underlying(program));
    }
    auto create_shader_program                            (gl::shader_type_e type, const std::string& source_code) -> gl::handle_t
    {
        const auto* c_string = source_code.c_str();
        return static_cast<gl::handle_t>(::glCreateShaderProgramv(gl::to_underlying(type), gl::sizei_t{ 1 }, &c_string));
    }
    template<gl::program_interface_parameter_e Parameter>
    auto get_program_interface_value                      (gl::handle_t program, gl::program_interface_e interface) -> auto
    {
        auto get_program_interface_iv = [](gl::handle_t program, gl::program_interface_e interface, gl::program_interface_parameter_e parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                ::glGetProgramInterfaceiv(gl::to_underlying(program), gl::to_underlying(interface), gl::to_underlying(parameter), &value);

                return value;
            };

        using enum gl::program_interface_parameter_e;
        if constexpr (Parameter == active_resources                   ) return static_cast<gl::uint32_t>(get_program_interface_iv(program, interface, Parameter));
        if constexpr (Parameter == maximum_name_length                ) return static_cast<gl::size_t  >(get_program_interface_iv(program, interface, Parameter));
        if constexpr (Parameter == maximum_number_active_variables    ) return static_cast<gl::uint32_t>(get_program_interface_iv(program, interface, Parameter));
        if constexpr (Parameter == maximum_number_compatible_resources) return static_cast<gl::uint32_t>(get_program_interface_iv(program, interface, Parameter));
    }
    auto get_program_resource_index                       (gl::handle_t program, gl::program_interface_e interface, const std::string& identifier) -> gl::index_t
    {
        return ::glGetProgramResourceIndex(gl::to_underlying(program), gl::to_underlying(interface), identifier.c_str());
    }
    auto get_program_resource_name                        (gl::handle_t program, gl::program_interface_e interface, gl::index_t index) -> std::string
    {
        const auto maximum_name_length = gl::get_program_interface_value<gl::program_interface_parameter_e::maximum_name_length>(program, interface);
              auto length              = gl::sizei_t{ 0u };
              auto value               = std::string(maximum_name_length, '\0');
        ::glGetProgramResourceName(gl::to_underlying(program), gl::to_underlying(interface), static_cast<gl::uint32_t>(index), static_cast<gl::sizei_t>(value.length()), &length, value.data());
        
        value.resize(length);
        return value;
    }
    template<gl::program_resource_e... Resource>
    auto get_program_resource_value                       (gl::handle_t program, gl::program_interface_e interface, gl::index_t index) -> std::array<gl::int32_t, sizeof...(Resource)>
    {
        const auto property_count = sizeof...(Resource);
        const auto array          = std::array<gl::enum_t , property_count>{ gl::to_underlying(Resource)... };
              auto value          = std::array<gl::int32_t, property_count>{};
        ::glGetProgramResourceiv(
            gl::to_underlying        (program), gl::to_underlying       (interface)     , 
            static_cast<gl::uint32_t>(index)  , static_cast<gl::sizei_t>(property_count), 
            array.data()                      , static_cast<gl::sizei_t>(array.size())  , 
            nullptr                           , value.data()                           );

        return value;
    }
    auto get_program_resource_location                    (gl::handle_t program, gl::program_interface_e interface, const std::string& identifier) -> gl::int32_t
    {
        const auto value = ::glGetProgramResourceLocation(gl::to_underlying(program), gl::to_underlying(interface), identifier.c_str());
        if (value == -1) throw std::runtime_error{ "name does not identify an active variable or identifies an active variable that does not have a valid location" };

        return value;
    }
    auto get_program_resource_location_index              (gl::handle_t program,                                    const std::string& identifier) -> gl::int32_t
    {
        const auto value = ::glGetProgramResourceLocationIndex(gl::to_underlying(program), gl::to_underlying(gl::program_interface_e::program_output), identifier.c_str());
        if (value == -1) throw std::runtime_error{ "name does not identify an active variable or identifies an active variable that does not have a valid location" };

        return value;
    }
    template<typename T>
    void program_uniform                                  (gl::handle_t program, gl::index_t location, const T& value)
    {
        const auto p     = gl::to_underlying(program);
        const auto l     = static_cast<gl::int32_t>(location);
        const auto count = gl::sizei_t{ 1 };

             if constexpr (std::is_same_v<gl::int32_t    , T>) ::glProgramUniform1iv        (p, l, count,                              &value );
        else if constexpr (std::is_same_v<gl::uint32_t   , T>) ::glProgramUniform1uiv       (p, l, count,                              &value );
        else if constexpr (std::is_same_v<gl::float32_t  , T>) ::glProgramUniform1fv        (p, l, count,                              &value );

        else if constexpr (std::is_same_v<gl::vector_1i  , T>) ::glProgramUniform4iv        (p, l, count,             gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::vector_2i  , T>) ::glProgramUniform4iv        (p, l, count,             gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::vector_3i  , T>) ::glProgramUniform4iv        (p, l, count,             gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::vector_4i  , T>) ::glProgramUniform4iv        (p, l, count,             gl::value_pointer(value));

        else if constexpr (std::is_same_v<gl::vector_1u  , T>) ::glProgramUniform4uiv       (p, l, count,             gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::vector_2u  , T>) ::glProgramUniform4uiv       (p, l, count,             gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::vector_3u  , T>) ::glProgramUniform4uiv       (p, l, count,             gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::vector_4u  , T>) ::glProgramUniform4uiv       (p, l, count,             gl::value_pointer(value));
        
        else if constexpr (std::is_same_v<gl::vector_1f  , T>) ::glProgramUniform1fv        (p, l, count,             gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::vector_2f  , T>) ::glProgramUniform2fv        (p, l, count,             gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::vector_3f  , T>) ::glProgramUniform3fv        (p, l, count,             gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::vector_4f  , T>) ::glProgramUniform4fv        (p, l, count,             gl::value_pointer(value));

        else if constexpr (std::is_same_v<gl::matrix_2f  , T>) ::glProgramUniformMatrix2fv  (p, l, count, gl::false_, gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::matrix_3f  , T>) ::glProgramUniformMatrix3fv  (p, l, count, gl::false_, gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::matrix_4f  , T>) ::glProgramUniformMatrix4fv  (p, l, count, gl::false_, gl::value_pointer(value));

        else if constexpr (std::is_same_v<gl::matrix_2x3f, T>) ::glProgramUniformMatrix2x3fv(p, l, count, gl::false_, gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::matrix_2x4f, T>) ::glProgramUniformMatrix2x4fv(p, l, count, gl::false_, gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::matrix_3x2f, T>) ::glProgramUniformMatrix3x2fv(p, l, count, gl::false_, gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::matrix_3x4f, T>) ::glProgramUniformMatrix3x4fv(p, l, count, gl::false_, gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::matrix_4x2f, T>) ::glProgramUniformMatrix4x2fv(p, l, count, gl::false_, gl::value_pointer(value));
        else if constexpr (std::is_same_v<gl::matrix_4x3f, T>) ::glProgramUniformMatrix4x3fv(p, l, count, gl::false_, gl::value_pointer(value));
        
        else static_assert(false && sizeof(T), "invalid uniform type");
    }
    auto create_pipeline                                  () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        ::glCreateProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle));
        
        return handle;
    }
    auto create_pipelines                                 (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        ::glCreateProgramPipelines(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data()));
        
        return handles;
    }
    void delete_pipeline                                  (gl::handle_t pipeline)
    {
        ::glDeleteProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&pipeline));
    }
    void delete_pipelines                                 (std::span<const gl::handle_t> pipeline)
    {
        ::glDeleteProgramPipelines(static_cast<gl::sizei_t>(pipeline.size()), gl::to_underlying_pointer(pipeline.data()));
    }
    void bind_pipeline                                    (gl::handle_t pipeline)
    {
        ::glBindProgramPipeline(gl::to_underlying(pipeline));
    }
    void use_program_stage                                (gl::handle_t pipeline, gl::handle_t program, gl::program_stage_e program_stage)
    {
        ::glUseProgramStages(gl::to_underlying(pipeline), gl::to_underlying(program_stage), gl::to_underlying(program));
    }
    void active_shader_program                            (gl::handle_t pipeline, gl::handle_t program)
    {
        ::glActiveShaderProgram(gl::to_underlying(pipeline), gl::to_underlying(program));
    }
    auto get_program_binary                               (gl::handle_t program) -> gl::binary_info
    {
        const auto binary_length = gl::get_program_value<gl::program_parameter_e::binary_length>(program);
              auto binary_info   = gl::binary_info{ gl::enum_t{}, std::vector<gl::byte_t>(binary_length) };
        ::glGetProgramBinary(gl::to_underlying(program), static_cast<gl::sizei_t>(binary_length), nullptr, &binary_info.format, binary_info.binary.data());
        
        return binary_info;
    }
    void program_binary                                   (gl::handle_t program, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        ::glProgramBinary(gl::to_underlying(program), format, binary.data(), static_cast<gl::sizei_t>(binary.size()));
    }
    void memory_barrier                                   (gl::memory_barrier_e                   barrier)
    {
        ::glMemoryBarrier(gl::to_underlying(barrier));
    }
    void memory_barrier_by_region                         (gl::memory_regional_barrier_e regional_barrier)
    {
        ::glMemoryBarrierByRegion(gl::to_underlying(regional_barrier));
    }



    //Chapter 8 - Textures and Samplers
    auto create_texture                                   (gl::texture_target_e target) -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        ::glCreateTextures(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle));
        
        return handle;
    }
    auto create_textures                                  (gl::texture_target_e target, gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        ::glCreateTextures(gl::to_underlying(target), static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data()));
        
        return handles;
    }
    void delete_texture                                   (gl::handle_t texture)
    {
        ::glDeleteTextures(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&texture));
    }
    void delete_textures                                  (std::span<const gl::handle_t> textures)
    {
        ::glDeleteTextures(static_cast<gl::sizei_t>(textures.size()), gl::to_underlying_pointer(textures.data()));
    }
    void bind_texture_unit                                (gl::handle_t texture, gl::binding_t binding)
    {
        ::glBindTextureUnit(binding, gl::to_underlying(texture));
    }
    auto create_sampler                                   () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        ::glCreateSamplers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle));
        
        return handle;
    }
    auto create_samplers                                  (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        ::glCreateSamplers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data()));
        
        return handles;
    }
    void delete_sampler                                   (gl::handle_t sampler)
    {
        ::glDeleteSamplers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&sampler));
    }
    void delete_samplers                                  (std::span<const gl::handle_t> samplers)
    {
        ::glDeleteSamplers(static_cast<gl::sizei_t>(samplers.size()), gl::to_underlying_pointer(samplers.data()));
    }
    void bind_sampler                                     (gl::handle_t sampler, gl::binding_t binding)
    {
        ::glBindSampler(binding, gl::to_underlying(sampler));
    }
    void bind_samplers                                    (std::span<const gl::handle_t> samplers, gl::index_t index)
    {
        ::glBindSamplers(static_cast<gl::uint32_t>(index), static_cast<gl::sizei_t>(samplers.size()), gl::to_underlying_pointer(samplers.data()));
    }
    template<gl::sampler_parameter_e Parameter>
    auto sampler_parameter                                (gl::handle_t sampler, gl::sampler_parameter_argument_t<Parameter> value) -> auto
    {
        auto sampler_parameter_iv  = [](gl::handle_t sampler, gl::sampler_parameter_e parameter, gl::int32_t   value)
            {
                ::glSamplerParameterIiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };
        auto sampler_parameter_uiv = [](gl::handle_t sampler, gl::sampler_parameter_e parameter, gl::uint32_t  value)
            {
                ::glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };
        auto sampler_parameter_fv  = [](gl::handle_t sampler, gl::sampler_parameter_e parameter, gl::float32_t value)
            {
                ::glSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };

        using enum gl::sampler_parameter_e;
             if constexpr (Parameter == border_color        ) 
        {
            auto overload = gl::overload_t
            {
                [=](gl::vector_4i vector) { ::glSamplerParameterIiv (gl::to_underlying(sampler), gl::to_underlying(Parameter), gl::value_pointer(vector)); },
                [=](gl::vector_4u vector) { ::glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(Parameter), gl::value_pointer(vector)); },
                [=](gl::vector_4f vector) { ::glSamplerParameterfv  (gl::to_underlying(sampler), gl::to_underlying(Parameter), gl::value_pointer(vector)); },
            };

            std::visit(overload, value);
        }
        else if constexpr (Parameter == compare_function    ) sampler_parameter_uiv(sampler, Parameter, gl::to_underlying(value));
        else if constexpr (Parameter == compare_mode        ) sampler_parameter_uiv(sampler, Parameter, gl::to_underlying(value));
        else if constexpr (Parameter == lod_bias            ) sampler_parameter_fv (sampler, Parameter,                   value );
        else if constexpr (Parameter == magnification_filter) sampler_parameter_uiv(sampler, Parameter, gl::to_underlying(value));
        else if constexpr (Parameter == maximum_anisotropy  ) sampler_parameter_fv (sampler, Parameter,                   value );
        else if constexpr (Parameter == maximum_lod         ) sampler_parameter_fv (sampler, Parameter,                   value );
        else if constexpr (Parameter == minification_filter ) sampler_parameter_uiv(sampler, Parameter, gl::to_underlying(value));
        else if constexpr (Parameter == minimum_lod         ) sampler_parameter_fv (sampler, Parameter,                   value );
        else if constexpr (Parameter == wrapping_r          ) sampler_parameter_uiv(sampler, Parameter, gl::to_underlying(value));
        else if constexpr (Parameter == wrapping_s          ) sampler_parameter_uiv(sampler, Parameter, gl::to_underlying(value));
        else if constexpr (Parameter == wrapping_t          ) sampler_parameter_uiv(sampler, Parameter, gl::to_underlying(value));
    }
    template<gl::packing_mode_e Mode>
    void pixel_store                                      (gl::int32_t parameter)
    {
        ::glPixelStorei(gl::to_underlying(Mode), parameter);
    }
    void texture_sub_image_1d                             (gl::handle_t texture, gl::uint32_t image_level, gl::length_t image_region, gl::texture_data_descriptor texture_data_descriptor, std::span<const gl::byte_t> memory)
    {
        const auto image_width = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        if (image_region.origin.x + image_region.extent.x > image_width) throw std::invalid_argument{ "region width exceeds image bounds" };

        ::glTextureSubImage1D(
            gl::to_underlying       (texture)                            , static_cast<gl::int32_t>(image_level)                            ,  
            static_cast<gl::int32_t>(image_region.origin.x)              , static_cast<gl::sizei_t>(image_region.extent.x)                  , 
            gl::to_underlying       (texture_data_descriptor.base_format), gl::to_underlying       (texture_data_descriptor.pixel_data_type), 
            memory.data()                                               );
    }
    void texture_sub_image_2d                             (gl::handle_t texture, gl::uint32_t image_level, gl::area_t   image_region, gl::texture_data_descriptor texture_data_descriptor, std::span<const gl::byte_t> memory)
    {
        const auto image_width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        const auto image_height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        if (image_region.origin.x + image_region.extent.x > image_width ) throw std::invalid_argument{ "region width exceeds image bounds" };
        if (image_region.origin.y + image_region.extent.y > image_height) throw std::invalid_argument{ "region height exceeds image bounds" };

        ::glTextureSubImage2D(
            gl::to_underlying       (texture)                            , static_cast<gl::int32_t>(image_level)                            , 
            static_cast<gl::int32_t>(image_region.origin.x)              , static_cast<gl::int32_t>(image_region.origin.y)                  , 
            static_cast<gl::sizei_t>(image_region.extent.x)              , static_cast<gl::sizei_t>(image_region.extent.y)                  , 
            gl::to_underlying       (texture_data_descriptor.base_format), gl::to_underlying       (texture_data_descriptor.pixel_data_type), 
            memory.data()                                               );
    }
    void texture_sub_image_3d                             (gl::handle_t texture, gl::uint32_t image_level, gl::volume_t image_region, gl::texture_data_descriptor texture_data_descriptor, std::span<const gl::byte_t> memory)
    {
        const auto image_width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        const auto image_height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        const auto image_depth  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, image_level);
        if (image_region.origin.x + image_region.extent.x > image_width ) throw std::invalid_argument{ "region width exceeds image bounds"  };
        if (image_region.origin.y + image_region.extent.y > image_height) throw std::invalid_argument{ "region height exceeds image bounds" };
        if (image_region.origin.z + image_region.extent.z > image_depth ) throw std::invalid_argument{ "region depth exceeds image bounds"  };

        ::glTextureSubImage3D(
            gl::to_underlying       (texture)                            , static_cast<gl::int32_t>(image_level)                            , 
            static_cast<gl::int32_t>(image_region.origin.x)              , static_cast<gl::int32_t>(image_region.origin.y)                  , static_cast<gl::int32_t>(image_region.origin.z), 
            static_cast<gl::sizei_t>(image_region.extent.x)              , static_cast<gl::sizei_t>(image_region.extent.y)                  , static_cast<gl::sizei_t>(image_region.extent.z), 
            gl::to_underlying       (texture_data_descriptor.base_format), gl::to_underlying       (texture_data_descriptor.pixel_data_type), 
            memory.data()                                               );
    }
    void copy_texture_sub_image_1d                        (gl::handle_t texture, gl::uint32_t image_level, gl::length_t image_region, const gl::vector_2u& coordinates)
    {
        const auto image_width = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        if (image_region.origin.x + image_region.extent.x > image_width) throw std::invalid_argument{ "region width exceeds image bounds" };
        
        ::glCopyTextureSubImage1D(
            gl::to_underlying       (texture)               , static_cast<gl::int32_t>(image_level)  , 
            static_cast<gl::int32_t>(image_region.origin.x) ,
            static_cast<gl::int32_t>(coordinates        .x) , static_cast<gl::int32_t>(coordinates.y), 
            static_cast<gl::sizei_t>(image_region.extent.x));
    }
    void copy_texture_sub_image_2d                        (gl::handle_t texture, gl::uint32_t image_level, gl::area_t   image_region, const gl::vector_2u& coordinates)
    {
        const auto image_width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        const auto image_height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        if (image_region.origin.x + image_region.extent.x > image_width ) throw std::invalid_argument{ "region width exceeds image bounds"  };
        if (image_region.origin.y + image_region.extent.y > image_height) throw std::invalid_argument{ "region height exceeds image bounds" };

        ::glCopyTextureSubImage2D(
            gl::to_underlying       (texture)              , static_cast<gl::int32_t>(image_level)           , 
            static_cast<gl::int32_t>(image_region.origin.x), static_cast<gl::int32_t>(image_region.origin.y) , 
            static_cast<gl::int32_t>(coordinates        .x), static_cast<gl::int32_t>(coordinates        .y) , 
            static_cast<gl::sizei_t>(image_region.extent.x), static_cast<gl::sizei_t>(image_region.extent.y));
    }
    void copy_texture_sub_image_3d                        (gl::handle_t texture, gl::uint32_t image_level, gl::volume_t image_region, const gl::vector_2u& coordinates)
    {
        const auto image_width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        const auto image_height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        const auto image_depth  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, image_level);
        if (image_region.origin.x + image_region.extent.x > image_width ) throw std::invalid_argument{ "region width exceeds image bounds"  };
        if (image_region.origin.y + image_region.extent.y > image_height) throw std::invalid_argument{ "region height exceeds image bounds" };
        if (image_region.origin.z + image_region.extent.z > image_depth ) throw std::invalid_argument{ "region depth exceeds image bounds"  };

        ::glCopyTextureSubImage3D(
            gl::to_underlying       (texture)              , static_cast<gl::int32_t>(image_level)           , 
            static_cast<gl::int32_t>(image_region.origin.x), static_cast<gl::int32_t>(image_region.origin.y) , static_cast<gl::int32_t>(image_region.origin.z), 
            static_cast<gl::int32_t>(coordinates        .x), static_cast<gl::int32_t>(coordinates        .y) , 
            static_cast<gl::sizei_t>(image_region.extent.x), static_cast<gl::sizei_t>(image_region.extent.y));
    }
    void compressed_texture_sub_image_1d                  (gl::handle_t texture, gl::uint32_t image_level, gl::length_t image_region, gl::compressed_texture_base_format_e compressed_base_format, std::span<const gl::byte_t> memory)
    {
        const auto image_width = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        if (image_region.origin.x + image_region.extent.x > image_width) throw std::invalid_argument{ "invalid image_region width" };

        ::glCompressedTextureSubImage1D(
            gl::to_underlying       (texture)               , static_cast<gl::int32_t>(image_level)          , 
            static_cast<gl::int32_t>(image_region.origin.x) , static_cast<gl::sizei_t>(image_region.extent.x), 
            gl::to_underlying       (compressed_base_format),
            static_cast<gl::sizei_t>(memory.size())         , memory.data()                                 );
    }
    void compressed_texture_sub_image_2d                  (gl::handle_t texture, gl::uint32_t image_level, gl::area_t   image_region, gl::compressed_texture_base_format_e compressed_base_format, std::span<const gl::byte_t> memory)
    {
        const auto image_width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        const auto image_height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        if (image_region.origin.x + image_region.extent.x > image_width ) throw std::invalid_argument{ "invalid region width"  };
        if (image_region.origin.y + image_region.extent.y > image_height) throw std::invalid_argument{ "invalid region height" };

        ::glCompressedTextureSubImage2D(
            gl::to_underlying       (texture)               , static_cast<gl::int32_t>(image_level)          , 
            static_cast<gl::int32_t>(image_region.origin.x) , static_cast<gl::int32_t>(image_region.origin.y), 
            static_cast<gl::sizei_t>(image_region.extent.x) , static_cast<gl::sizei_t>(image_region.extent.y), 
            gl::to_underlying       (compressed_base_format), 
            static_cast<gl::sizei_t>(memory.size())         , memory.data()                                 );
    }
    void compressed_texture_sub_image_3d                  (gl::handle_t texture, gl::uint32_t image_level, gl::volume_t image_region, gl::compressed_texture_base_format_e compressed_base_format, std::span<const gl::byte_t> memory)
    {
        const auto image_width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        const auto image_height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        const auto image_depth  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, image_level);
        if (image_region.origin.x + image_region.extent.x > image_width ) throw std::invalid_argument{ "invalid region width"  };
        if (image_region.origin.y + image_region.extent.y > image_height) throw std::invalid_argument{ "invalid region height" };
        if (image_region.origin.z + image_region.extent.z > image_depth ) throw std::invalid_argument{ "invalid region depth"  };
        
        ::glCompressedTextureSubImage3D(
            gl::to_underlying       (texture)               , static_cast<gl::int32_t>(image_level)          , 
            static_cast<gl::int32_t>(image_region.origin.x) , static_cast<gl::int32_t>(image_region.origin.y), static_cast<gl::int32_t>(image_region.origin.z), 
            static_cast<gl::sizei_t>(image_region.extent.x) , static_cast<gl::sizei_t>(image_region.extent.y), static_cast<gl::sizei_t>(image_region.extent.z), 
            gl::to_underlying       (compressed_base_format),
            static_cast<gl::sizei_t>(memory.size())         , memory.data()                                 );
    }
    void texture_buffer                                   (gl::handle_t texture, gl::handle_t buffer, gl::buffer_format_e format)
    {
        ::glTextureBuffer(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer));
    }
    template<typename T = gl::byte_t>
    void texture_buffer_range                             (gl::handle_t texture, gl::handle_t buffer, gl::buffer_format_e format, gl::range_t range)
    {
        const auto buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto byte_range  = gl::convert_range<T>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        ::glTextureBufferRange(
            gl::to_underlying        (texture)          , 
            gl::to_underlying        (format)           , gl::to_underlying          (buffer)          , 
            static_cast<gl::intptr_t>(byte_range.offset), static_cast<gl::sizeiptr_t>(byte_range.size));
    }
    template<gl::texture_parameter_e Parameter>
    void texture_parameter                                (gl::handle_t texture, gl::texture_parameter_argument_t<Parameter> value)
    {
        auto texture_parameter_iv  = [](gl::handle_t texture, gl::texture_parameter_e parameter, gl::int32_t                            value) -> gl::void_t
            {
                ::glTextureParameteri(gl::to_underlying(texture), gl::to_underlying(parameter), value);
            };
        auto texture_parameter_uiv = [](gl::handle_t texture, gl::texture_parameter_e parameter, gl::uint32_t                           value) -> gl::void_t
            {
                ::glTextureParameteri(gl::to_underlying(texture), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
            };
        auto texture_parameter_fv  = [](gl::handle_t texture, gl::texture_parameter_e parameter, gl::float32_t                          value) -> gl::void_t
            {
                ::glTextureParameterfv(gl::to_underlying(texture), gl::to_underlying(parameter), &value);
            };
        auto set_swizzle_rgba      = [](gl::handle_t texture, gl::texture_parameter_e parameter, std::array<gl::texture_swizzle_e, 4u>& value) -> gl::void_t
            {
                ::glTextureParameterIuiv(gl::to_underlying(texture), gl::to_underlying(parameter), gl::to_underlying_pointer(value.data()));
            };

        using enum gl::texture_parameter_e;
        if constexpr (Parameter == base_level          ) texture_parameter_uiv(texture, Parameter,                   value );
        if constexpr (Parameter == border_color        )
             {
                auto overload = gl::overload_t
                {
                    [=](gl::vector_4i vector) { ::glTextureParameterIiv (gl::to_underlying(texture), gl::to_underlying(Parameter), gl::value_pointer(vector)); },
                    [=](gl::vector_4u vector) { ::glTextureParameterIuiv(gl::to_underlying(texture), gl::to_underlying(Parameter), gl::value_pointer(vector)); },
                    [=](gl::vector_4f vector) { ::glTextureParameterfv  (gl::to_underlying(texture), gl::to_underlying(Parameter), gl::value_pointer(vector)); },
                };

                std::visit(overload, value);
             }
        if constexpr (Parameter == compare_function    ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == compare_mode        ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == depth_stencil_mode  ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == lod_bias            ) texture_parameter_fv (texture, Parameter,                   value );
        if constexpr (Parameter == magnification_filter) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == maximum_anisotropy  ) texture_parameter_fv (texture, Parameter,                   value );
        if constexpr (Parameter == maximum_level       ) texture_parameter_uiv(texture, Parameter,                   value );
        if constexpr (Parameter == maximum_lod         ) texture_parameter_fv (texture, Parameter,                   value );
        if constexpr (Parameter == minification_filter ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == minimum_lod         ) texture_parameter_fv (texture, Parameter,                   value );
        if constexpr (Parameter == swizzle_a           ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == swizzle_b           ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == swizzle_g           ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == swizzle_r           ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == swizzle_rgba        ) set_swizzle_rgba     (texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == target              ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == wrapping_r          ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == wrapping_s          ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
        if constexpr (Parameter == wrapping_t          ) texture_parameter_uiv(texture, Parameter, gl::to_underlying(value));
    }
    void generate_texture_mipmaps                         (gl::handle_t texture)
    {
        ::glGenerateTextureMipmap(gl::to_underlying(texture));
    }
    template<gl::texture_target_e Original, gl::texture_target_e Target> requires (meta::is_valid_texture_view<Original, Target>())
    void texture_view                                     (gl::handle_t source_texture, gl::handle_t destination_texture, gl::texture_format_e format, gl::uint32_t image_levels, gl::uint32_t first_image_level, gl::uint32_t image_layers, gl::uint32_t first_image_layer)
    {
        ::glTextureView(gl::to_underlying(destination_texture), gl::to_underlying(Target), gl::to_underlying(source_texture), gl::to_underlying(format), first_image_level, image_levels, first_image_layer, image_layers);
    }
    void texture_storage_1d                               (gl::handle_t texture, gl::texture_format_e format, const gl::vector_1u& dimensions, gl::uint32_t image_levels)
    {
        ::glTextureStorage1D(
            gl::to_underlying       (texture)      , static_cast<gl::sizei_t>(image_levels), gl::to_underlying(format),
            static_cast<gl::sizei_t>(dimensions.x));
    }
    void texture_storage_2d                               (gl::handle_t texture, gl::texture_format_e format, const gl::vector_2u& dimensions, gl::uint32_t image_levels)
    {
        ::glTextureStorage2D(
            gl::to_underlying       (texture)     , static_cast<gl::sizei_t>(image_levels) , gl::to_underlying(format),
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    void texture_storage_3d                               (gl::handle_t texture, gl::texture_format_e format, const gl::vector_3u& dimensions, gl::uint32_t image_levels)
    {
        ::glTextureStorage3D(
            gl::to_underlying       (texture)     , static_cast<gl::sizei_t>(image_levels), gl::to_underlying       (format)       ,
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z));
    }
    void texture_storage_2d_multisample                   (gl::handle_t texture, gl::texture_format_e format, const gl::vector_2u& dimensions, gl::uint32_t samples, gl::bool_t has_fixed_sample_locations = gl::true_)
    {
        ::glTextureStorage2DMultisample(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(samples)     , gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::boolean_t>(has_fixed_sample_locations));
    }
    void texture_storage_3d_multisample                   (gl::handle_t texture, gl::texture_format_e format, const gl::vector_3u& dimensions, gl::uint32_t samples, gl::bool_t has_fixed_sample_locations = gl::true_)
    {
        ::glTextureStorage3DMultisample(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(samples)     , gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z), static_cast<gl::boolean_t>(has_fixed_sample_locations));
    }
    void invalidate_texture_image                         (gl::handle_t texture, gl::uint32_t image_level)
    {
        ::glInvalidateTexImage(gl::to_underlying(texture), static_cast<gl::int32_t>(image_level));
    }
    void invalidate_texture_sub_image                     (gl::handle_t texture, gl::uint32_t image_level, gl::volume_t image_region)
    {
        const auto image_width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        const auto image_height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        const auto image_depth  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, image_level);
        if (image_region.origin.x + image_region.extent.x > image_width ) throw std::invalid_argument{ "invalid region width"  };
        if (image_region.origin.y + image_region.extent.y > image_height) throw std::invalid_argument{ "invalid region height" };
        if (image_region.origin.z + image_region.extent.z > image_depth ) throw std::invalid_argument{ "invalid region depth"  };

        ::glInvalidateTexSubImage(
            gl::to_underlying       (texture)              , static_cast<gl::int32_t>(image_level)          , 
            static_cast<gl::int32_t>(image_region.origin.x), static_cast<gl::int32_t>(image_region.origin.y), static_cast<gl::int32_t>(image_region.origin.z) , 
            static_cast<gl::sizei_t>(image_region.extent.x), static_cast<gl::sizei_t>(image_region.extent.y), static_cast<gl::sizei_t>(image_region.extent.z));
    }
    void clear_texture_image                              (gl::handle_t texture, gl::texture_base_format_e base_format, gl::texture_type_e type, gl::uint32_t image_level,                            std::span<const gl::byte_t> memory)
    {
        ::glClearTexImage(
            gl::to_underlying(texture)    , static_cast<gl::int32_t>(image_level), 
            gl::to_underlying(base_format), gl::to_underlying       (type)       , memory.data());
    }
    void clear_texture_sub_image                          (gl::handle_t texture, gl::texture_base_format_e base_format, gl::texture_type_e type, gl::uint32_t image_level, gl::volume_t image_region, std::span<const gl::byte_t> memory)
    {
        const auto image_width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        const auto image_height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        const auto image_depth  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, image_level);
        if (image_region.origin.x + image_region.extent.x > image_width ) throw std::invalid_argument{ "invalid region width"  };
        if (image_region.origin.y + image_region.extent.y > image_height) throw std::invalid_argument{ "invalid region height" };
        if (image_region.origin.z + image_region.extent.z > image_depth ) throw std::invalid_argument{ "invalid region depth"  };

        ::glClearTexSubImage(
            gl::to_underlying       (texture)              , static_cast<gl::int32_t>(image_level)          , 
            static_cast<gl::int32_t>(image_region.origin.x), static_cast<gl::int32_t>(image_region.origin.y), static_cast<gl::int32_t>(image_region.origin.z), 
            static_cast<gl::sizei_t>(image_region.extent.x), static_cast<gl::sizei_t>(image_region.extent.y), static_cast<gl::sizei_t>(image_region.extent.z), 
            gl::to_underlying       (base_format)          , gl::to_underlying       (type)                 , memory.data()                                 );
    }
    void bind_image_texture                               (gl::handle_t texture, gl::uint32_t image_level, gl::bool_t is_layered, gl::uint32_t image_layer, gl::index_t image_unit, gl::image_format_e image_format, gl::image_access_e image_access)
    {
        ::glBindImageTexture(
            static_cast<gl::uint32_t>(image_unit) , gl::to_underlying         (texture)     , 
            static_cast<gl::int32_t> (image_level), static_cast<gl::boolean_t>(is_layered)  , 
            static_cast<gl::int32_t> (image_layer), gl::to_underlying         (image_access), gl::to_underlying(image_format));
    }
    void bind_image_textures                              (std::span<const gl::handle_t> textures, gl::range_t range)
    {
        ::glBindImageTextures(static_cast<gl::uint32_t>(range.index), static_cast<gl::sizei_t>(range.count), gl::to_underlying_pointer(textures.data()));
    }



    //Chapter 9 - FrameBuffers and FrameBuffer Objects
    auto create_frame_buffer                              () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        ::glCreateFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle));
            
        return handle;
    }
    auto create_frame_buffers                             (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        ::glCreateFramebuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data()));
        
        return handles;
    }
    void delete_frame_buffer                              (gl::handle_t frame_buffer)
    {
        ::glDeleteFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&frame_buffer));
    }
    void delete_frame_buffers                             (std::span<const gl::handle_t> frame_buffers)
    {
        ::glDeleteFramebuffers(static_cast<gl::sizei_t>(frame_buffers.size()), gl::to_underlying_pointer(frame_buffers.data()));
    }
    void bind_frame_buffer                                (gl::handle_t frame_buffer, gl::frame_buffer_target_e target)
    {
        ::glBindFramebuffer(gl::to_underlying(target), gl::to_underlying(frame_buffer));
    }
    template<gl::frame_buffer_parameter_e Parameter>
    void frame_buffer_parameter                           (gl::handle_t frame_buffer, gl::uint32_t value)
    {
        auto frame_buffer_parameter_i = [](gl::handle_t frame_buffer, gl::frame_buffer_parameter_e parameter, gl::uint32_t value)
            {
                ::glNamedFramebufferParameteri(gl::to_underlying(frame_buffer), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
            };

        using enum gl::frame_buffer_parameter_e;
        if constexpr (
            Parameter == default_width                      ||
            Parameter == default_height                     ||
            Parameter == default_layers                     ||
            Parameter == default_samples                    ||
            Parameter == has_default_fixed_sample_locations ||
            Parameter == default_width                       ) frame_buffer_parameter_i(frame_buffer, Parameter, value);
        else static_assert(gl::false_, "invalid frame buffer parameter");
    }
    auto create_render_buffer                             () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        ::glCreateRenderbuffers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle));
        
        return handle;
    }
    auto create_render_buffers                            (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        ::glCreateRenderbuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data()));
        
        return handles;
    }
    void delete_render_buffer                             (gl::handle_t render_buffer)
    {
        ::glDeleteRenderbuffers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&render_buffer));
    }
    void delete_render_buffers                            (std::span<const gl::handle_t> render_buffers)
    {
        ::glDeleteRenderbuffers(static_cast<gl::sizei_t>(render_buffers.size()), gl::to_underlying_pointer(render_buffers.data()));
    }
    void render_buffer_storage                            (gl::handle_t render_buffer, gl::render_buffer_format_e format, const gl::vector_2u& dimensions)
    {
        ::glNamedRenderbufferStorage(
            gl::to_underlying       (render_buffer), gl::to_underlying       (format)       , 
            static_cast<gl::sizei_t>(dimensions.x) , static_cast<gl::sizei_t>(dimensions.y));
    }
    void render_buffer_storage_multisample                (gl::handle_t render_buffer, gl::render_buffer_format_e format, const gl::vector_2u& dimensions, gl::uint32_t samples)
    {
        ::glNamedRenderbufferStorageMultisample(
            gl::to_underlying       (render_buffer), static_cast<gl::sizei_t>(samples)      , gl::to_underlying(format), 
            static_cast<gl::sizei_t>(dimensions.x) , static_cast<gl::sizei_t>(dimensions.y));
    }
    void frame_buffer_render_buffer                       (gl::handle_t frame_buffer, gl::handle_t render_buffer, gl::frame_buffer_attachment_e attachment)
    {
        ::glNamedFramebufferRenderbuffer(
            gl::to_underlying(frame_buffer)                             , gl::to_underlying(attachment)    , 
            gl::to_underlying(gl::render_buffer_target_e::render_buffer), gl::to_underlying(render_buffer));
    }
    void frame_buffer_texture                             (gl::handle_t frame_buffer, gl::handle_t texture      , gl::frame_buffer_attachment_e attachment, gl::uint32_t image_level)
    {
        ::glNamedFramebufferTexture(
            gl::to_underlying       (frame_buffer), gl::to_underlying(attachment), gl::to_underlying(texture), 
            static_cast<gl::int32_t>(image_level));
    }
    void frame_buffer_texture_layer                       (gl::handle_t frame_buffer, gl::handle_t texture      , gl::frame_buffer_attachment_e attachment, gl::uint32_t image_level, gl::uint32_t image_layer)
    {
        ::glNamedFramebufferTextureLayer(
            gl::to_underlying       (frame_buffer), gl::to_underlying       (attachment)  , gl::to_underlying(texture), 
            static_cast<gl::int32_t>(image_level) , static_cast<gl::int32_t>(image_layer));
    }
    void texture_barrier                                  ()
    {
        ::glTextureBarrier();
    }
    auto check_frame_buffer_status                        (gl::handle_t frame_buffer, gl::frame_buffer_target_e frame_buffer_target) -> gl::frame_buffer_status_e
    {
        return static_cast<gl::frame_buffer_status_e>(::glCheckNamedFramebufferStatus(gl::to_underlying(frame_buffer), gl::to_underlying(frame_buffer_target)));
    }



    //Chapter 10 - Vertex Specification and Drawing Commands
    template<gl::patch_parameter_e Parameter>
    void patch_parameter                                  (gl::patch_parameter_argument_t<Parameter> value)
    {
        auto patch_parameter_i = [](gl::patch_parameter_e parameter, gl::int32_t   value)
            {
                ::glPatchParameteri(gl::to_underlying(parameter), value);
            };
        auto patch_parameter_f = [](gl::patch_parameter_e parameter, gl::float32_t value)
            {
                ::glPatchParameterfv(gl::to_underlying(parameter), &value);
            };

        using enum gl::patch_parameter_e;
        if constexpr (Parameter == patch_default_inner_level) ::glPatchParameterfv(gl::to_underlying(Parameter), value.data());
        if constexpr (Parameter == patch_default_outer_level) ::glPatchParameterfv(gl::to_underlying(Parameter), value.data());
        if constexpr (Parameter == patch_vertices           ) patch_parameter_i (                    Parameter , value       );
    }
    template<typename T, gl::uint32_t Count, gl::bool_t IsNormalized = gl::false_>
    void specify_vertex_attribute                         (gl::index_t index, const gl::vector_t<T, Count>& value)
    {
        const auto maximum_vertex_attributes = gl::get_value<gl::data_e::maximum_vertex_attributes>();
        if (index > maximum_vertex_attributes) throw std::invalid_argument{ "index exceeds vertex attribute limit" };
        
             if constexpr (std::is_same_v<T, gl::uint8_t  >)
        {
            if constexpr (Count == 4 && IsNormalized == gl::true_ ) ::glVertexAttrib4Nub(index, value.x, value.y, value.z, value.w);
        }
        else if constexpr (std::is_same_v<T, gl::int16_t  >)
        {
            if constexpr (Count == 1 && IsNormalized == gl::false_) ::glVertexAttrib1s  (index, value.x                           );
            if constexpr (Count == 2 && IsNormalized == gl::false_) ::glVertexAttrib2s  (index, value.x, value.y                  );
            if constexpr (Count == 3 && IsNormalized == gl::false_) ::glVertexAttrib3s  (index, value.x, value.y, value.z         );
            if constexpr (Count == 4 && IsNormalized == gl::false_) ::glVertexAttrib4s  (index, value.x, value.y, value.z, value.w);
        }
        else if constexpr (std::is_same_v<T, gl::int32_t  >)
        {
            if constexpr (Count == 1 && IsNormalized == gl::false_) ::glVertexAttribI1i (index, value.x                           );
            if constexpr (Count == 2 && IsNormalized == gl::false_) ::glVertexAttribI2i (index, value.x, value.y                  );
            if constexpr (Count == 3 && IsNormalized == gl::false_) ::glVertexAttribI3i (index, value.x, value.y, value.z         );
            if constexpr (Count == 4 && IsNormalized == gl::false_) ::glVertexAttribI4i (index, value.x, value.y, value.z, value.w);
        }
        else if constexpr (std::is_same_v<T, gl::uint32_t >)
        {
            if constexpr (Count == 1 && IsNormalized == gl::false_) ::glVertexAttribI1ui(index, value.x                           );
            if constexpr (Count == 2 && IsNormalized == gl::false_) ::glVertexAttribI2ui(index, value.x, value.y                  );
            if constexpr (Count == 3 && IsNormalized == gl::false_) ::glVertexAttribI3ui(index, value.x, value.y, value.z         );
            if constexpr (Count == 4 && IsNormalized == gl::false_) ::glVertexAttribI4ui(index, value.x, value.y, value.z, value.w);
        }
        else if constexpr (std::is_same_v<T, gl::float32_t>)
        {
            if constexpr (Count == 1 && IsNormalized == gl::false_) ::glVertexAttrib1f  (index, value.x                           );
            if constexpr (Count == 2 && IsNormalized == gl::false_) ::glVertexAttrib2f  (index, value.x, value.y                  );
            if constexpr (Count == 3 && IsNormalized == gl::false_) ::glVertexAttrib3f  (index, value.x, value.y, value.z         );
            if constexpr (Count == 4 && IsNormalized == gl::false_) ::glVertexAttrib4f  (index, value.x, value.y, value.z, value.w);
        }
        else if constexpr (std::is_same_v<T, gl::float64_t>)
        {
            if constexpr (Count == 1 && IsNormalized == gl::false_) ::glVertexAttribL1d (index, value.x                           );
            if constexpr (Count == 2 && IsNormalized == gl::false_) ::glVertexAttribL2d (index, value.x, value.y                  );
            if constexpr (Count == 3 && IsNormalized == gl::false_) ::glVertexAttribL3d (index, value.x, value.y, value.z         );
            if constexpr (Count == 4 && IsNormalized == gl::false_) ::glVertexAttribL4d (index, value.x, value.y, value.z, value.w);
        }
        else    static_assert(gl::false_ && sizeof(T), "parameters do not match a valid vertex attribute function");
    }
    auto create_vertex_array                              () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        ::glCreateVertexArrays(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle));
        
        return handle;
    }
    auto create_vertex_arrays                             (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        ::glCreateVertexArrays(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data()));
        
        return handles;
    }
    void delete_vertex_array                              (gl::handle_t vertex_array)
    {
        ::glDeleteVertexArrays(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&vertex_array));
    }
    void delete_vertex_arrays                             (std::span<const gl::handle_t> vertex_arrays)
    {
        ::glDeleteVertexArrays(static_cast<gl::sizei_t>(vertex_arrays.size()), gl::to_underlying_pointer(vertex_arrays.data()));
    }
    void bind_vertex_array                                (gl::handle_t vertex_array)
    {
        ::glBindVertexArray(gl::to_underlying(vertex_array));
    }
    void vertex_array_element_buffer                      (gl::handle_t vertex_array, gl::handle_t element_buffer)
    {
        ::glVertexArrayElementBuffer(gl::to_underlying(vertex_array), gl::to_underlying(element_buffer));
    }
    void vertex_array_attribute_format                    (gl::handle_t vertex_array, gl::vertex_array_attribute_type_e attribute_type, gl::index_t attribute_index, gl::count_t attribute_count, gl::ptrdiff_t byte_offset, gl::bool_t is_normalized = gl::false_)
    {
        auto vertex_array_attribute_format_i = [](gl::handle_t vertex_array, gl::index_t attribute_index, gl::vertex_array_attribute_type_e attribute_type, gl::count_t attribute_count, gl::ptrdiff_t byte_offset                          ) -> gl::void_t
            {
                ::glVertexArrayAttribIFormat(
                    gl::to_underlying        (vertex_array)   , 
                    static_cast<gl::uint32_t>(attribute_index), static_cast<gl::int32_t >(attribute_count), 
                    gl::to_underlying        (attribute_type) , static_cast<gl::uint32_t>(byte_offset)   );
            };
        auto vertex_array_attribute_format_f = [](gl::handle_t vertex_array, gl::index_t attribute_index, gl::vertex_array_attribute_type_e attribute_type, gl::count_t attribute_count, gl::ptrdiff_t byte_offset, gl::bool_t is_normalized)
            {
                ::glVertexArrayAttribFormat(
                    gl::to_underlying        (vertex_array)   , 
                    static_cast<gl::uint32_t>(attribute_index),                static_cast<gl::int32_t >(attribute_count),
                    gl::to_underlying        (attribute_type) , is_normalized, static_cast<gl::uint32_t>(byte_offset)   );
            };
        auto vertex_array_attribute_format_l = [](gl::handle_t vertex_array, gl::index_t attribute_index, gl::vertex_array_attribute_type_e attribute_type, gl::count_t attribute_count, gl::ptrdiff_t byte_offset                          )
            {
                ::glVertexArrayAttribLFormat(
                    gl::to_underlying        (vertex_array)   , 
                    static_cast<gl::uint32_t>(attribute_index), static_cast<gl::int32_t >(attribute_count),
                    gl::to_underlying        (attribute_type) , static_cast<gl::uint32_t>(byte_offset)   );
            };

        const auto maximum_vertex_attributes = gl::get_value<gl::data_e::maximum_vertex_attributes>();
        if (attribute_index > maximum_vertex_attributes) throw std::invalid_argument{ "index exceeds vertex attribute limit" };
        
        switch (attribute_type)
        {
            using enum vertex_array_attribute_type_e;
            case int8                      : 
            case uint8                     : 
            case int16                     : 
            case uint16                    : 
            case int32                     : 
            case uint32                    : 
            case int32_2_10_10_10_r        : 
            case uint32_2_10_10_10_r       : 
            case uint32_10_11_11_11_float_r: return vertex_array_attribute_format_i(vertex_array, attribute_index, attribute_type, attribute_count, byte_offset               );
            case fixed                     : 
            case float16                   : 
            case float32                   : return vertex_array_attribute_format_f(vertex_array, attribute_index, attribute_type, attribute_count, byte_offset, is_normalized);
            case float64                   : return vertex_array_attribute_format_l(vertex_array, attribute_index, attribute_type, attribute_count, byte_offset               );
        }
    }
    void vertex_array_vertex_buffer                       (gl::handle_t vertex_array, gl::handle_t vertex_buffer, gl::binding_t binding, gl::ptrdiff_t element_offset, gl::ptrdiff_t element_stride)
    {
        ::glVertexArrayVertexBuffer(gl::to_underlying(vertex_array), binding, gl::to_underlying(vertex_buffer), static_cast<gl::intptr_t>(element_offset), static_cast<gl::sizei_t>(element_stride));
    }
    void vertex_array_vertex_buffers                      (gl::handle_t vertex_array, std::span<const gl::handle_t> vertex_buffers, gl::index_t first_binding, std::span<const gl::ptrdiff_t> offsets, std::span<const gl::uint32_t> strides)
    {
        const auto count = std::min(strides.size(), offsets.size());

        ::glVertexArrayVertexBuffers(
            gl::to_underlying        (vertex_array)         , 
            static_cast<gl::uint32_t>(first_binding)        , static_cast     <      gl::sizei_t  >(count)         , 
            gl::to_underlying_pointer(vertex_buffers.data()), reinterpret_cast<const gl::intptr_t*>(offsets.data()), reinterpret_cast<const gl::sizei_t*>(strides.data()));
    }
    void vertex_array_attribute_binding                   (gl::handle_t vertex_array, gl::index_t attribute_index, gl::binding_t binding)
    {
        ::glVertexArrayAttribBinding(gl::to_underlying(vertex_array), static_cast<gl::uint32_t>(attribute_index), binding);
    }
    void enable_vertex_array_attribute                    (gl::handle_t vertex_array, gl::index_t attribute_index)
    {
        ::glEnableVertexArrayAttrib(gl::to_underlying(vertex_array), static_cast<gl::uint32_t>(attribute_index));
    }
    void disable_vertex_array_attribute                   (gl::handle_t vertex_array, gl::index_t attribute_index)
    {
        ::glDisableVertexArrayAttrib(gl::to_underlying(vertex_array), static_cast<gl::uint32_t>(attribute_index));
    }
    void vertex_array_binding_divisor                     (gl::handle_t vertex_array, gl::binding_t binding, gl::uint32_t instance_step_rate)
    {
        ::glVertexArrayBindingDivisor(gl::to_underlying(vertex_array), binding, instance_step_rate);
    }
    void primitive_restart_index                          (gl::index_t restart_index)
    {
        ::glPrimitiveRestartIndex(static_cast<gl::uint32_t>(restart_index));
    }
    void draw_arrays                                      (gl::draw_mode_e draw_mode, gl::range_t range)
    {
        ::glDrawArrays(
            gl::to_underlying       (draw_mode)  , 
            static_cast<gl::int32_t>(range.index), static_cast<gl::sizei_t>(range.count));
    }
    void draw_arrays_indirect                             (gl::draw_mode_e draw_mode, gl::index_t offset)
    {
        const auto draw_indirect_buffer_binding = gl::get_value<gl::data_e::draw_indirect_buffer_binding>();
        if (draw_indirect_buffer_binding == gl::null_object) throw std::runtime_error{ "no draw indirect buffer bound" };

        ::glDrawArraysIndirect(
            gl::to_underlying                  (draw_mode)                                         , 
            reinterpret_cast<const gl::void_t*>(offset * sizeof(gl::draw_arrays_indirect_command)));
    }
    void draw_arrays_instanced                            (gl::draw_mode_e draw_mode, gl::range_t range, gl::count_t instance_count)
    {
        ::glDrawArraysInstanced(
            gl::to_underlying       (draw_mode)  , static_cast<gl::int32_t>(range.index)    , 
            static_cast<gl::sizei_t>(range.count), static_cast<gl::sizei_t>(instance_count));
    }
    void draw_arrays_instanced_base_instance              (gl::draw_mode_e draw_mode, gl::range_t range, gl::index_t base_instance, gl::count_t instance_count)
    {
        ::glDrawArraysInstancedBaseInstance(
            gl::to_underlying       (draw_mode)  , static_cast<gl::int32_t>(range.index)   , 
            static_cast<gl::sizei_t>(range.count), static_cast<gl::sizei_t>(instance_count), static_cast<gl::uint32_t>(base_instance));
    }
    void draw_elements                                    (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t element_count, gl::index_t offset)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawElements(
            gl::to_underlying(draw_mode), static_cast     <      gl::sizei_t >(element_count)           , 
            gl::to_underlying(draw_type), reinterpret_cast<const gl::void_t *>(offset * draw_type_size));
    }
    void draw_elements_base_vertex                        (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t element_count, gl::index_t offset, gl::int32_t base_vertex)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawElementsBaseVertex(
            gl::to_underlying(draw_mode), static_cast     <      gl::sizei_t >(element_count)          , 
            gl::to_underlying(draw_type), reinterpret_cast<const gl::void_t *>(offset * draw_type_size), base_vertex);
    }
    void draw_elements_indirect                           (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::index_t offset)
    {
        const auto draw_indirect_buffer_binding = gl::get_value<gl::data_e::draw_indirect_buffer_binding>();
        if (draw_indirect_buffer_binding == gl::null_object) throw std::runtime_error{ "no draw indirect buffer bound" };

        ::glDrawElementsIndirect(
            gl::to_underlying                  (draw_mode)                                           , gl::to_underlying(draw_type), 
            reinterpret_cast<const gl::void_t*>(offset * sizeof(gl::draw_elements_indirect_command)));
    }
    void draw_elements_instanced                          (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t element_count, gl::index_t offset, gl::count_t instance_count)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawElementsInstanced(
            gl::to_underlying(draw_mode),                                                               static_cast<gl::sizei_t>(element_count ) , 
            gl::to_underlying(draw_type), reinterpret_cast<const gl::void_t*>(offset * draw_type_size), static_cast<gl::sizei_t>(instance_count));
    }
    void draw_elements_instanced_base_instance            (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t element_count, gl::index_t offset, gl::count_t instance_count, gl::index_t base_instance)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawElementsInstancedBaseInstance(
            gl::to_underlying(draw_mode),                                                               static_cast<gl::sizei_t>(element_count) , 
            gl::to_underlying(draw_type), reinterpret_cast<const gl::void_t*>(offset * draw_type_size), static_cast<gl::sizei_t>(instance_count), static_cast<gl::uint32_t>(base_instance));
    }
    void draw_elements_instanced_base_vertex              (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t element_count, gl::index_t offset, gl::count_t instance_count, gl::int32_t base_vertex)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawElementsInstancedBaseVertex(
            gl::to_underlying(draw_mode),                                                               static_cast<gl::sizei_t>(element_count) , 
            gl::to_underlying(draw_type), reinterpret_cast<const gl::void_t*>(offset * draw_type_size), static_cast<gl::sizei_t>(instance_count), base_vertex);
    }
    void draw_elements_instanced_base_vertex_base_instance(gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t element_count, gl::index_t offset, gl::count_t instance_count, gl::int32_t base_vertex, gl::index_t base_instance)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawElementsInstancedBaseVertexBaseInstance(
            gl::to_underlying(draw_mode),                                                               static_cast<gl::sizei_t>(element_count) , 
            gl::to_underlying(draw_type), reinterpret_cast<const gl::void_t*>(offset * draw_type_size), static_cast<gl::sizei_t>(instance_count), base_vertex, static_cast<gl::uint32_t>(base_instance));
    }
    void draw_range_elements                              (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::index_t start_index, gl::index_t end_index, gl::count_t element_count, gl::index_t offset)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawRangeElements(
            gl::to_underlying        (draw_mode)    , 
            static_cast<gl::uint32_t>(start_index)  , static_cast<gl::uint32_t>(end_index), 
            static_cast<gl::sizei_t >(element_count), gl::to_underlying        (draw_type), reinterpret_cast<const gl::void_t*>(offset * draw_type_size));
    }
    void draw_range_elements_base_vertex                  (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::index_t start_index, gl::index_t end_index, gl::count_t element_count, gl::index_t offset, gl::int32_t base_vertex)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawRangeElementsBaseVertex(
            gl::to_underlying        (draw_mode)    , 
            static_cast<gl::uint32_t>(start_index)  , static_cast<gl::uint32_t>(end_index), 
            static_cast<gl::sizei_t >(element_count), gl::to_underlying        (draw_type), reinterpret_cast<const gl::void_t*>(offset * draw_type_size), base_vertex);
    }
    void multi_draw_arrays                                (gl::draw_mode_e draw_mode, std::span<const gl::index_t> starting_indices, std::span<const gl::count_t> vertex_counts)
    {
        const auto draw_count = std::min(starting_indices.size(), vertex_counts.size());
        ::glMultiDrawArrays(
            gl::to_underlying                   (draw_mode)           , reinterpret_cast<const gl::int32_t*>(starting_indices.data()), 
            reinterpret_cast<const gl::sizei_t*>(vertex_counts.data()), static_cast     <      gl::sizei_t >(draw_count)            );
    }
    void multi_draw_arrays_indirect                       (gl::draw_mode_e draw_mode, gl::count_t draw_count, gl::index_t offset)
    {
        const auto draw_indirect_buffer_binding = gl::get_value<gl::data_e::draw_indirect_buffer_binding>();
        if (draw_indirect_buffer_binding == gl::null_object) throw std::runtime_error{ "no draw indirect buffer bound" };

        ::glMultiDrawArraysIndirect(
            gl::to_underlying       (draw_mode)                                                    , 
            reinterpret_cast<const gl::void_t *>(offset * sizeof(gl::draw_arrays_indirect_command)),
            static_cast     <      gl::sizei_t >(draw_count)                                       , gl::sizei_t{ 0 });
    }
    void multi_draw_elements                              (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, std::span<const gl::count_t> element_counts, std::span<const gl::index_t> index_offsets)
    {
        const auto draw_count     = std::min(element_counts.size(), index_offsets.size());
        const auto offset_pointer = index_offsets.data();
        ::glMultiDrawElements(
            gl::to_underlying(draw_mode), reinterpret_cast<const gl::sizei_t*       >(element_counts.data()), 
            gl::to_underlying(draw_type), reinterpret_cast<const gl::void_t * const*>(&offset_pointer)      , static_cast<gl::sizei_t>(draw_count));
    }
    void multi_draw_elements_indirect                     (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t draw_count, gl::index_t offset)
    {
        ::glMultiDrawElementsIndirect(
            gl::to_underlying                  (draw_mode)                                          , gl::to_underlying       (draw_type) , 
            reinterpret_cast<const gl::void_t*>(offset * sizeof(gl::draw_elements_indirect_command)), static_cast<gl::sizei_t>(draw_count), gl::sizei_t{ 0 });
    }
    void multi_draw_elements_base_vertex                  (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, std::span<const gl::count_t> element_counts, std::span<const gl::index_t> index_offsets, std::span<const gl::int32_t> base_vertex_offsets)
    {
        const auto draw_count     = std::min(std::min(element_counts.size(), index_offsets.size()), base_vertex_offsets.size());
        const auto offset_pointer = index_offsets.data();
        ::glMultiDrawElementsBaseVertex(
            gl::to_underlying       (draw_mode) , reinterpret_cast<const gl::sizei_t*       >(element_counts.data())     , 
            gl::to_underlying       (draw_type) , reinterpret_cast<const gl::void_t * const*>(&offset_pointer)           , 
            static_cast<gl::sizei_t>(draw_count),                                             base_vertex_offsets.data());
    }
    void begin_conditional_render                         (gl::handle_t query, gl::query_mode_e query_mode)
    {
        ::glBeginConditionalRender(gl::to_underlying(query), gl::to_underlying(query_mode));
    }
    void end_conditional_render                           ()
    {
        ::glEndConditionalRender();
    }



    //Chapter 11 - Programmable Vertex Processing
    void validate_program                                 (gl::handle_t program)
    {
        ::glValidateProgram(gl::to_underlying(program));
    }
    void validate_program_pipeline                        (gl::handle_t pipeline)
    {
        ::glValidateProgramPipeline(gl::to_underlying(pipeline));
    }



    //Chapter 13 - Fixed-Function Vertex Post-Processing
    void provoking_vertex                                 (gl::provoking_vertex_mode_e mode)
    {
        ::glProvokingVertex(gl::to_underlying(mode));
    }
    void clip_control                                     (gl::clipping_origin_e origin, gl::clipping_depth_mode_e mode)
    {
        ::glClipControl(gl::to_underlying(origin), gl::to_underlying(mode));
    }
    void depth_range_array_value                          (gl::index_t index, std::span<const gl::vector_2d> ranges)
    {
        ::glDepthRangeArrayv(static_cast<gl::uint32_t>(index), static_cast<gl::sizei_t>(ranges.size()), gl::value_pointer(*ranges.data()));
    }
    void depth_range_indexed                              (gl::index_t index, const gl::vector_2d& range)
    {
        ::glDepthRangeIndexed(static_cast<gl::uint32_t>(index), range.x, range.y);
    }
    void depth_range                                      (const gl::vector_2f& range)
    {
        ::glDepthRangef(range.x, range.y);
    }
    void viewport_array_value                             (gl::index_t index, std::span<const gl::vector_2f> ranges)
    {
        ::glViewportArrayv(static_cast<gl::uint32_t>(index), static_cast<gl::sizei_t>(ranges.size()), gl::value_pointer(*ranges.data()));
    }
    void viewport_indexed                                 (gl::index_t index, gl::region_t<gl::float32_t, 2u> region)
    {
        ::glViewportIndexedf(static_cast<gl::uint32_t>(index), region.origin.x, region.origin.y, region.extent.x, region.extent.y);
    }
    void viewport                                         (gl::area_t region)
    {
        ::glViewport(
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }



    //Chapter 14 - Fixed-Function Primitive Assembly and Rasterization
    auto get_multisample_value                            (gl::index_t sample_index) -> gl::vector_2f
    {
        auto value = gl::vector_2f{};
        ::glGetMultisamplefv(gl::to_underlying(gl::multisample_parameter_e::sample_position), static_cast<gl::uint32_t>(sample_index), gl::value_pointer(value));
        
        return value;
    }
    void minimum_sample_shading                           (gl::float32_t value)
    {
        ::glMinSampleShading(value);
    }
    void point_size                                       (gl::float32_t size)
    {
        ::glPointSize(size);
    }
    template<gl::point_parameter_e Parameter>
    void point_parameter                                  (gl::point_parameter_argument_t<Parameter> value)
    {
        auto point_parameter_i = [](gl::point_parameter_e parameter, gl::int32_t   value) -> gl::void_t
            {
                ::glPointParameteri(gl::to_underlying(parameter), value);
            };
        auto point_parameter_f = [](gl::point_parameter_e parameter, gl::float32_t value) -> gl::void_t
            {
                ::glPointParameterf(gl::to_underlying(parameter), value);
            };

        using enum gl::point_parameter_e;
        if constexpr (Parameter == fade_threshold_size     ) point_parameter_f(Parameter,                   value );
        if constexpr (Parameter == sprite_coordinate_origin) point_parameter_i(Parameter, gl::to_underlying(value));
    }
    void line_width                                       (gl::float32_t value)
    {
        ::glLineWidth(value);
    }
    void front_face                                       (gl::orientation_e orientation)
    {
        ::glFrontFace(gl::to_underlying(orientation));
    }
    void cull_face                                        (gl::culling_facet_e face)
    {
        ::glCullFace(gl::to_underlying(face));
    }
    void polygon_mode                                     (gl::polygon_mode_e mode)
    {
        ::glPolygonMode(gl::to_underlying(gl::polygon_face_e::front_and_back), gl::to_underlying(mode));
    }
    void polygon_offset_clamp                             (gl::float32_t factor, gl::float32_t units, gl::float32_t clamp)
    {
        ::glPolygonOffsetClamp(factor, units, clamp);
    }
    void scissor_array                                    (gl::index_t index, std::span<const gl::uint32_t, 4u> values)
    {
        ::glScissorArrayv(
            static_cast     <      gl::uint32_t >(index)         , 
            static_cast     <      gl::sizei_t  >(values.size()) , 
            reinterpret_cast<const gl::int32_t *>(values.data()));
    }
    void scissor_indexed                                  (gl::index_t index, gl::area_t region)
    {
        ::glScissorIndexed(
            static_cast<gl::uint32_t>(index)          , 
            static_cast<gl::int32_t >(region.origin.x), static_cast<gl::int32_t>(region.origin.y) ,  
            static_cast<gl::sizei_t >(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    void scissor                                          (gl::area_t region)
    {
        ::glScissor(
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y) , 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    void sample_coverage                                  (gl::float32_t value, gl::bool_t invert)
    {
        ::glSampleCoverage(value, invert);
    }
    void sample_mask_index                                (gl::uint32_t mask, gl::uint32_t value)
    {
        ::glSampleMaski(mask, value);
    }



    //Chapter 17 - Writing Fragments and Samples to the Framebuffer
    void stencil_function                                 (gl::stencil_function_e function, gl::uint32_t reference, gl::uint32_t mask)
    {
        ::glStencilFunc(gl::to_underlying(function), static_cast<gl::int32_t>(reference), mask);
    }
    void stencil_function_separate                        (gl::stencil_face_e face, gl::stencil_function_e function, gl::uint32_t reference, gl::uint32_t mask)
    {
        ::glStencilFuncSeparate(gl::to_underlying(face), gl::to_underlying(function), static_cast<gl::int32_t>(reference), mask);
    }
    void stencil_operation                                (gl::stencil_action_e stencil, gl::stencil_action_e depth, gl::stencil_action_e depth_stencil)
    {
        ::glStencilOp(gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depth_stencil));
    }
    void stencil_operation_separate                       (gl::stencil_face_e face, gl::stencil_action_e stencil, gl::stencil_action_e depth, gl::stencil_action_e depth_stencil)
    {
        ::glStencilOpSeparate(gl::to_underlying(face), gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depth_stencil));
    }
    void depth_function                                   (gl::depth_function_e function)
    {
        ::glDepthFunc(gl::to_underlying(function));
    }
    void blend_equation                                   (gl::blending_equation_e equation)
    {
        ::glBlendEquation(gl::to_underlying(equation));
    }
    void blend_equation_indexed                           (gl::blending_equation_e equation,                                gl::index_t index)
    {
        ::glBlendEquationi(static_cast<gl::uint32_t>(index), gl::to_underlying(equation));
    }
    void blend_equation_separate                          (gl::blending_equation_e color   , gl::blending_equation_e alpha                   )
    {
        ::glBlendEquationSeparate(gl::to_underlying(color), gl::to_underlying(alpha));
    }
    void blend_equation_separate_indexed                  (gl::blending_equation_e color   , gl::blending_equation_e alpha, gl::index_t index)
    {
        ::glBlendEquationSeparatei(static_cast<gl::uint32_t>(index), gl::to_underlying(color), gl::to_underlying(alpha));
    }
    void blend_function                                   (gl::blending_factor_e source      , gl::blending_factor_e destination                                                                                                      )
    {
        ::glBlendFunc(gl::to_underlying(source), gl::to_underlying(destination));
    }
    void blend_function_indexed                           (gl::blending_factor_e source_color, gl::blending_factor_e source_alpha, gl::blending_factor_e destination_color, gl::blending_factor_e destination_alpha, gl::index_t index)
    {
        ::glBlendFuncSeparatei(
            static_cast<gl::uint32_t>(index)       , 
            gl::to_underlying        (source_color), gl::to_underlying(destination_color) , 
            gl::to_underlying        (source_alpha), gl::to_underlying(destination_alpha));
    }
    void blend_function_separate                          (gl::blending_factor_e source_color, gl::blending_factor_e source_alpha, gl::blending_factor_e destination_color, gl::blending_factor_e destination_alpha                   )
    {
        ::glBlendFuncSeparate(gl::to_underlying(source_color), gl::to_underlying(destination_color), gl::to_underlying(source_alpha), gl::to_underlying(destination_alpha));
    }
    void blend_function_separate_indexed                  (gl::blending_factor_e source_color, gl::blending_factor_e source_alpha, gl::blending_factor_e destination_color, gl::blending_factor_e destination_alpha, gl::index_t index)
    {
        ::glBlendFuncSeparatei(
            static_cast<gl::uint32_t>(index)       , 
            gl::to_underlying        (source_color), gl::to_underlying(destination_color) , 
            gl::to_underlying        (source_alpha), gl::to_underlying(destination_alpha));
    }
    void blend_color                                      (const gl::vector_4f& color)
    {
        ::glBlendColor(color.r, color.g, color.b, color.a);
    }
    void logical_pixel_operation                          (gl::logical_pixel_operation_e operation)
    {
        ::glLogicOp(gl::to_underlying(operation));
    }
    void frame_buffer_draw_buffer                         (gl::handle_t frame_buffer, gl::frame_buffer_source_e source)
    {
        ::glNamedFramebufferDrawBuffer(gl::to_underlying(frame_buffer), gl::to_underlying(source));
    }
    void frame_buffer_draw_buffers                        (gl::handle_t frame_buffer, std::span<const gl::frame_buffer_source_e> sources)
    {
        const auto maximum_draw_buffers = gl::get_value<gl::data_e::maximum_draw_buffers>();
        if (sources.size() > maximum_draw_buffers) throw std::invalid_argument{ "exceeded maximum supported draw buffers" };

        ::glNamedFramebufferDrawBuffers(gl::to_underlying(frame_buffer), static_cast<gl::sizei_t>(sources.size()), gl::to_underlying_pointer(sources.data()));
    }
    void color_mask                                       (const gl::vector_4b& mask)
    {
        ::glColorMask(mask.r, mask.g, mask.b, mask.a);
    }
    void color_mask_index                                 (gl::handle_t buffer, const gl::vector_4b& mask)
    {
        ::glColorMaski(gl::to_underlying(buffer), mask.r, mask.g, mask.b, mask.a);
    }
    void depth_mask                                       (gl::bool_t flag)
    {
        ::glDepthMask(flag);
    }
    void stencil_mask                                     (gl::uint32_t mask)
    {
        ::glStencilMask(mask);
    }
    void stencil_mask_separate                            (gl::stencil_face_e face, gl::uint32_t mask)
    {
        ::glStencilMaskSeparate(gl::to_underlying(face), mask);
    }
    void clear                                            (gl::buffer_mask_e mask)
    {
        ::glClear(gl::to_underlying(mask));
    }
    void clear_color                                      (const gl::vector_4f& color)
    {
        ::glClearColor(color.r, color.g, color.b, color.a);
    }
    void clear_depth                                      (gl::float32_t depth)
    {
        ::glClearDepthf(depth);
    }
    void clear_stencil                                    (gl::index_t index)
    {
        ::glClearStencil(static_cast<gl::int32_t>(index));
    }
    template<gl::frame_buffer_attachment_e A>
    void clear_frame_buffer_value                         (gl::handle_t frame_buffer, gl::frame_buffer_attachment_argument_t<A> value)
    {
        auto clear_frame_buffer_iv  = [](gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, const gl::int32_t  * value)
            {
                ::glClearNamedFramebufferiv(gl::to_underlying(frame_buffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        auto clear_frame_buffer_uiv = [](gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, const gl::uint32_t * value)
            {
                ::glClearNamedFramebufferuiv(gl::to_underlying(frame_buffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        auto clear_frame_buffer_fv  = [](gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, const gl::float32_t* value)
            {
                ::glClearNamedFramebufferfv(gl::to_underlying(frame_buffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        auto clear_frame_buffer_fi  = [](gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment, gl::index_t index, gl::float32_t depth, gl::int32_t stencil)
            {
                ::glClearNamedFramebufferfi(gl::to_underlying(frame_buffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), depth, stencil);
            };

        using enum gl::frame_buffer_attachment_e;
        if constexpr (
                      A == color_0      ||
                      A == color_1      ||
                      A == color_2      ||
                      A == color_3      ||
                      A == color_4      ||
                      A == color_5      ||
                      A == color_6      ||
                      A == color_7       )
        {
            auto overload = gl::overload_t
            {
                [=](gl::vector_4i vector) { clear_frame_buffer_iv (frame_buffer, A, static_cast<gl::index_t>(A - color_0), gl::value_pointer(vector)); }, 
                [=](gl::vector_4u vector) { clear_frame_buffer_uiv(frame_buffer, A, static_cast<gl::index_t>(A - color_0), gl::value_pointer(vector)); }, 
                [=](gl::vector_4f vector) { clear_frame_buffer_fv (frame_buffer, A, static_cast<gl::index_t>(A - color_0), gl::value_pointer(vector)); }, 
            };

            std::visit(overload, value);
        }
        if constexpr (A == depth         )
        {
            auto overload = gl::overload_t
            {
                [=](gl::int32_t   _) { clear_frame_buffer_iv (frame_buffer, A, gl::index_t{ 0u }, &_); }, 
                [=](gl::uint32_t  _) { clear_frame_buffer_uiv(frame_buffer, A, gl::index_t{ 0u }, &_); }, 
                [=](gl::float32_t _) { clear_frame_buffer_fv (frame_buffer, A, gl::index_t{ 0u }, &_); }, 
            };

            std::visit(overload, value);
        }
        if constexpr (A == stencil       )
        {
            auto overload = gl::overload_t
            {
                [=](gl::int32_t   _) { clear_frame_buffer_iv (frame_buffer, A, gl::index_t{ 0u }, &_); }, 
                [=](gl::uint32_t  _) { clear_frame_buffer_uiv(frame_buffer, A, gl::index_t{ 0u }, &_); }, 
                [=](gl::float32_t _) { clear_frame_buffer_fv (frame_buffer, A, gl::index_t{ 0u }, &_); }, 
            };

            std::visit(overload, value);
        }
        if constexpr (A == depth_stencil )
        {
            const auto [depth, stencil] = value;
            clear_frame_buffer_fi(frame_buffer, A, gl::index_t{ 0u }, depth, stencil);
        }
    }
    void invalidate_frame_buffer_data                     (gl::handle_t frame_buffer, std::span<const gl::frame_buffer_attachment_e> attachments)
    {
        ::glInvalidateNamedFramebufferData(
            gl::to_underlying        (frame_buffer)       , 
            static_cast<gl::sizei_t> (attachments.size()) , 
            gl::to_underlying_pointer(attachments.data()));
    }
    void invalidate_frame_buffer_sub_data                 (gl::handle_t frame_buffer, std::span<const gl::frame_buffer_attachment_e> attachments, gl::area_t region)
    {
        ::glInvalidateNamedFramebufferSubData(
            gl::to_underlying       (frame_buffer)      , 
            static_cast<gl::sizei_t>(attachments.size()), gl::to_underlying_pointer(attachments.data()), 
            static_cast<gl::int32_t>(region.origin.x)   , static_cast<gl::int32_t> (region.origin.y)   , 
            static_cast<gl::sizei_t>(region.extent.x)   , static_cast<gl::sizei_t> (region.extent.y)  );
    }



    //Chapter 18 - Reading and Copying Pixels
    void frame_buffer_read_buffer                         (gl::handle_t frame_buffer, gl::frame_buffer_source_e source)
    {
        ::glNamedFramebufferReadBuffer(gl::to_underlying(frame_buffer), gl::to_underlying(source));
    }
    template<typename T = gl::byte_t>
    auto read_pixels                                      (gl::area_t region, gl::pixel_data_format_e format, gl::pixel_data_type_e type) -> std::vector<T>
    {
        const auto bytes_per_pixel = map_pixel_data_format_component_count(format) * map_pixel_data_component_size(type);
        const auto required_size   = region.extent.x * region.extent.y * bytes_per_pixel;
              auto vector          = std::vector<T>(required_size / sizeof(T));

        glReadnPixels(
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), 
            gl::to_underlying       (format)         , gl::to_underlying       (type)           , 
            static_cast<gl::sizei_t>(required_size)  , vector.data()                           );
        
        return vector;
    }
    void clamp_color                                      (gl::bool_t value)
    {
        ::glClampColor(gl::to_underlying(gl::clamp_color_e::read), value);
    }
    void blit_frame_buffer                                (gl::handle_t source, gl::handle_t destination, gl::buffer_mask_e mask, gl::frame_buffer_filter_e filter, gl::area_t source_region, gl::area_t destination_region)
    {
        ::glBlitNamedFramebuffer(
            gl::to_underlying       (source)                     , 
            gl::to_underlying       (destination)                , 
            static_cast<gl::int32_t>(source_region     .origin.x), static_cast<gl::int32_t>(source_region     .origin.y), static_cast<gl::int32_t>(source_region     .extent.x), static_cast<gl::int32_t>(source_region     .extent.y), 
            static_cast<gl::int32_t>(destination_region.origin.x), static_cast<gl::int32_t>(destination_region.origin.y), static_cast<gl::int32_t>(destination_region.extent.x), static_cast<gl::int32_t>(destination_region.extent.y), 
            gl::to_underlying       (mask)                       , gl::to_underlying       (filter)                    );
    }
    void copy_image_sub_data                              (gl::handle_t source, gl::handle_t destination, gl::texture_target_e source_target, gl::texture_target_e destination_target, gl::hyper_volume_t source_region, gl::hyper_volume_t destination_region)
    {
        ::glCopyImageSubData(
            gl::to_underlying       (source                     ), gl::to_underlying       (source_target              ), static_cast<gl::int32_t>(source_region     .extent.w) , 
            static_cast<gl::int32_t>(source_region     .origin.x), static_cast<gl::int32_t>(source_region     .origin.y), static_cast<gl::int32_t>(source_region     .origin.z) , 
            gl::to_underlying       (destination                ), gl::to_underlying       (destination_target         ), static_cast<gl::int32_t>(destination_region.extent.w) , 
            static_cast<gl::int32_t>(destination_region.origin.x), static_cast<gl::int32_t>(destination_region.origin.y), static_cast<gl::int32_t>(destination_region.origin.z) , 
            static_cast<gl::sizei_t>(source_region     .extent.x), static_cast<gl::sizei_t>(source_region     .extent.y), static_cast<gl::sizei_t>(source_region     .extent.z));
    }



    //Chapter 19 - Compute Shaders
    void dispatch_compute                                 (gl::vector_3u work_groups)
    {
        ::glDispatchCompute(work_groups.x, work_groups.y, work_groups.z);
    }
    void dispatch_compute_indirect                        (gl::index_t   offset     )
    {
        ::glDispatchComputeIndirect(static_cast<gl::intptr_t>(offset * sizeof(gl::dispatch_indirect_command)));
    }



    //Chapter 20 - Debug Output
    void debug_message_callback                           (gl::debug_callback_t callback, const gl::void_t* parameter = nullptr)
    {
        ::glDebugMessageCallback(callback, parameter);
    }
    void debug_message_control                            (gl::debug_source_e source, gl::debug_type_e type, gl::debug_severity_e severity, gl::bool_t state)
    {
        ::glDebugMessageControl(gl::to_underlying(source), gl::to_underlying(type), gl::to_underlying(severity), gl::sizei_t{ 0 }, nullptr, state);
    }
    void debug_message_insert                             (gl::handle_t user_identifier, gl::debug_type_e type, gl::debug_severity_e severity, const std::string& message)
    {
        ::glDebugMessageInsert(
            gl::to_underlying(gl::debug_source_e::application), 
            gl::to_underlying(type)                           , gl::to_underlying(user_identifier), gl::to_underlying(severity),
            static_cast<gl::sizei_t>(message.length())        , message.data()                   );
    }
    void push_debug_group                                 (gl::handle_t      identifier,                                                       const std::string& message)
    {
        const auto* c_string = message.c_str();
        ::glPushDebugGroup(gl::to_underlying(gl::debug_source_e::application), gl::to_underlying(identifier), gl::sizei_t{ -1 }, c_string);
    }
    void pop_debug_group                                  ()
    {
        ::glPopDebugGroup();
    }
    void object_label                                     (gl::handle_t identifier, gl::object_type_e type, const std::string& label)
    {
        const auto* c_string = label.c_str();
        ::glObjectLabel(gl::to_underlying(type), gl::to_underlying(identifier), gl::sizei_t{ -1 }, c_string);
    }
    void object_pointer_label                             (gl::sync_t sync, const std::string& identifier)
    {
        const auto* c_string = identifier.c_str();
        ::glObjectPtrLabel(sync, gl::sizei_t{ -1 }, c_string);
    }
    

    
    //Chapter 21 - Special Functions
    void hint                                             (gl::hint_target_e target, gl::hint_mode_e mode)
    {
        ::glHint(gl::to_underlying(target), gl::to_underlying(mode));
    }
}
