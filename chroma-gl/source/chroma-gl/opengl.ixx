export module opengl;
export import opengl.constants;
export import opengl.domain;
export import opengl.flags;
export import opengl.mapping;
export import opengl.meta;
export import opengl.parameters;
export import opengl.proxy;
export import opengl.state;
export import opengl.structures;
export import opengl.types;
export import opengl.utility;

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
    template<gl::data_e Data>                 requires (meta::is_non_indexed_data<Data>())
    auto get_value                                        () -> auto
    {
        auto get_boolean        = [](gl::data_e data) -> gl::bool_t
            {
                auto value = gl::boolean_t{};
                return ::glGetBooleanv(gl::to_underlying(data), &value), static_cast<gl::bool_t>(value);
            };
        auto get_int32          = [](gl::data_e data) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return ::glGetIntegerv(gl::to_underlying(data), &value), value;
            };
        auto get_int64          = [](gl::data_e data) -> gl::int64_t
            {
                auto value = gl::int64_t{};
                return ::glGetInteger64v(gl::to_underlying(data), &value), value;
            };
        auto get_uint32         = [](gl::data_e data) -> gl::uint32_t
            {
                auto value = gl::int32_t{};
                return ::glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::int32_t>(value);
            };
        auto get_uint64         = [](gl::data_e data) -> gl::uint64_t
            {
                auto value = gl::int64_t{};
                return ::glGetInteger64v(gl::to_underlying(data), &value), static_cast<gl::uint64_t>(value);
            };
        auto get_float32        = [](gl::data_e data) -> gl::float32_t
            {
                auto value = gl::float32_t{};
                return ::glGetFloatv(gl::to_underlying(data), &value), value;
            };
        auto get_float64        = [](gl::data_e data) -> gl::float64_t
            {
                auto value = gl::float64_t{};
                return ::glGetDoublev(gl::to_underlying(data), &value), value;
            };
        auto get_vector4b       = [](gl::data_e data) -> gl::vector_4b
            {
                auto value = gl::vector_4b{};
                return ::glGetBooleanv(gl::to_underlying(data), gl::value_pointer(value)), value;
            };
        auto get_vector2i       = [](gl::data_e data) -> gl::vector_2i
            {
                auto value = gl::vector_2i{};
                return ::glGetIntegerv(gl::to_underlying(data), gl::value_pointer(value)), value;
            };
        auto get_vector2f       = [](gl::data_e data) -> gl::vector_2f
            {
                auto value = gl::vector_2f{};
                return ::glGetFloatv(gl::to_underlying(data), gl::value_pointer(value)), value;
            };
        auto get_vector4f       = [](gl::data_e data) -> gl::vector_4f
            {
                auto value = gl::vector_4f{};
                return ::glGetFloatv(gl::to_underlying(data), gl::value_pointer(value)), value;
            };
        auto get_handle         = [](gl::data_e data) -> gl::handle_t
            {
                auto value = gl::int32_t{};
                return ::glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::handle_t>(value);
            };
        auto get_index          = [](gl::data_e data) -> gl::index_t
            {
                auto value = gl::int32_t{};
                return ::glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::index_t>(value);
            };
        auto get_bitfield       = [](gl::data_e data) -> gl::bitfield_t
            {
                auto value = gl::int32_t{};
                return ::glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::bitfield_t>(value);
            };
        auto get_binary_formats = [](gl::data_e data) -> std::vector<gl::enum_t>
            {
                auto program_binary_format_count = gl::count_t{};
                ::glGetIntegerv(gl::to_underlying(gl::data_e::number_program_binary_formats), std::bit_cast<gl::int32_t*>(&program_binary_format_count));

                auto program_binary_formats      = std::vector<gl::enum_t>(program_binary_format_count);
                ::glGetIntegerv(gl::to_underlying(data), std::bit_cast<gl::int32_t*>(program_binary_formats.data()));

                return program_binary_formats;
            };
        auto get_area           = [](gl::data_e data) -> gl::area_t
            {
                auto value = gl::vector_4u{};
                ::glGetIntegerv(gl::to_underlying(data), std::bit_cast<gl::int32_t*>(gl::value_pointer(value)));

                return gl::area_t{ gl::vector_2u{ value.z, value.w }, gl::vector_2u{ value.x, value.y } };
            };

        using enum gl::data_e;
        if constexpr (Data == atomic_counter_buffer_binding                        ) return get_handle(Data);
        if constexpr (Data == aliased_line_width_range                             ) return get_vector2f(Data);
        if constexpr (Data == blend_color                                          ) return get_vector4f(Data);
        if constexpr (Data == blending_destination_alpha                           ) return static_cast<gl::blending_factor_e>            (get_uint32(Data));
        if constexpr (Data == blending_destination_rgb                             ) return static_cast<gl::blending_factor_e>            (get_uint32(Data));
        if constexpr (Data == blending_destination_alpha                           ) return static_cast<gl::blending_equation_e>          (get_uint32(Data));
        if constexpr (Data == blending_equation_rgb                                ) return static_cast<gl::blending_equation_e>          (get_uint32(Data));
        if constexpr (Data == blending_source_alpha                                ) return static_cast<gl::blending_factor_e>            (get_uint32(Data));
        if constexpr (Data == blending_source_rgb                                  ) return static_cast<gl::blending_factor_e>            (get_uint32(Data));
        if constexpr (Data == clipping_depth_mode                                  ) return static_cast<gl::clipping_depth_mode_e>        (get_uint32(Data));
        if constexpr (Data == clipping_origin                                      ) return static_cast<gl::clipping_origin_e>            (get_uint32(Data));
        if constexpr (Data == color_clear_value                                    ) return get_vector4f(Data);
        if constexpr (Data == color_write_mask                                     ) return get_vector4b(Data);
        if constexpr (Data == context_flags                                        ) return static_cast<gl::context_flags_e>              (get_uint32(Data));
        if constexpr (Data == context_profile_mask                                 ) return static_cast<gl::context_profile_e>            (get_uint32(Data));
        if constexpr (Data == copy_read_buffer_binding                             ) return get_handle(Data);
        if constexpr (Data == copy_write_buffer_binding                            ) return get_handle(Data);
        if constexpr (Data == current_program                                      ) return get_handle(Data);
        if constexpr (Data == debug_group_stack_depth                              ) return get_uint32(Data);
        if constexpr (Data == debug_logged_messages                                ) return get_uint32(Data);
        if constexpr (Data == depth_clear_value                                    ) return get_float64(Data);
        if constexpr (Data == depth_function                                       ) return static_cast<gl::depth_function_e>             (get_uint32(Data));
        if constexpr (Data == depth_range                                          ) return get_vector2f(Data);
        if constexpr (Data == dispatch_indirect_buffer_binding                     ) return get_handle(Data);
        if constexpr (Data == double_buffer                                        ) return get_boolean(Data);
        if constexpr (Data == draw_buffer                                          ) return static_cast<gl::frame_buffer_source_e>        (get_uint32(Data));
        if constexpr (Data == draw_frame_buffer_binding                            ) return get_handle(Data);
        if constexpr (Data == draw_indirect_buffer_binding                         ) return get_handle(Data);
        if constexpr (Data == fragment_shader_derivative_hint                      ) return static_cast<gl::hint_mode_e>                  (get_uint32(Data));
        if constexpr (Data == implementation_color_read_format                     ) return static_cast<gl::pixel_data_format_e>          (get_uint32(Data));
        if constexpr (Data == implementation_color_read_type                       ) return static_cast<gl::pixel_data_type_e>            (get_uint32(Data));
        if constexpr (Data == index_array_buffer_binding                           ) return get_handle(Data);
        if constexpr (Data == layer_provoking_vertex                               ) return static_cast<gl::provoking_vertex_mode_e>      (get_uint32(Data));
        if constexpr (Data == line_smooth_hint                                     ) return static_cast<gl::hint_mode_e>                  (get_uint32(Data));
        if constexpr (Data == line_width                                           ) return get_float64(Data);
        if constexpr (Data == logic_operation_mode                                 ) return static_cast<gl::logical_pixel_operation_e>    (get_uint32(Data));
        if constexpr (Data == major_version                                        ) return get_uint32(Data);
        if constexpr (Data == maximum_3d_texture_size                              ) return get_uint32(Data);
        if constexpr (Data == maximum_array_texture_layers                         ) return get_uint32(Data);
        if constexpr (Data == maximum_clip_distances                               ) return get_uint32(Data);
        if constexpr (Data == maximum_color_attachments                            ) return get_uint32(Data);
        if constexpr (Data == maximum_color_texture_samples                        ) return get_uint32(Data);
        if constexpr (Data == maximum_combined_atomic_counters                     ) return get_uint32(Data);
        if constexpr (Data == maximum_combined_compute_uniform_components          ) return get_uint32(Data);
        if constexpr (Data == maximum_combined_fragment_uniform_components         ) return get_uint32(Data);
        if constexpr (Data == maximum_combined_geometry_uniform_components         ) return get_uint32(Data);
        if constexpr (Data == maximum_combined_shader_storage_blocks               ) return get_uint32(Data);
        if constexpr (Data == maximum_combined_texture_image_units                 ) return get_uint32(Data);
        if constexpr (Data == maximum_combined_uniform_blocks                      ) return get_uint32(Data);
        if constexpr (Data == maximum_combined_vertex_uniform_components           ) return get_uint32(Data);
        if constexpr (Data == maximum_compute_atomic_counter_buffers               ) return get_uint32(Data);
        if constexpr (Data == maximum_compute_atomic_counters                      ) return get_uint32(Data);
        if constexpr (Data == maximum_compute_shader_storage_blocks                ) return get_uint32(Data);
        if constexpr (Data == maximum_compute_texture_image_units                  ) return get_uint32(Data);
        if constexpr (Data == maximum_compute_uniform_blocks                       ) return get_uint32(Data);
        if constexpr (Data == maximum_compute_uniform_components                   ) return get_uint32(Data);
        if constexpr (Data == maximum_compute_work_group_count                     ) return get_uint32(Data);
        if constexpr (Data == maximum_compute_work_group_invocations               ) return get_uint32(Data);
        if constexpr (Data == maximum_compute_work_group_size                      ) return get_uint32(Data);
        if constexpr (Data == maximum_cubemap_texture_size                         ) return get_uint32(Data);
        if constexpr (Data == maximum_debug_group_stack_depth                      ) return get_uint32(Data);
        if constexpr (Data == maximum_debug_message_length                         ) return get_uint32(Data);
        if constexpr (Data == maximum_depth_texture_samples                        ) return get_uint32(Data);
        if constexpr (Data == maximum_draw_buffers                                 ) return get_uint32(Data);
        if constexpr (Data == maximum_dual_source_draw_buffers                     ) return get_uint32(Data);
        if constexpr (Data == maximum_element_index                                ) return get_index(Data);
        if constexpr (Data == maximum_fragment_atomic_counters                     ) return get_uint32(Data);
        if constexpr (Data == maximum_fragment_input_components                    ) return get_uint32(Data);
        if constexpr (Data == maximum_fragment_shader_storage_blocks               ) return get_uint32(Data);
        if constexpr (Data == maximum_fragment_uniform_blocks                      ) return get_uint32(Data);
        if constexpr (Data == maximum_fragment_uniform_components                  ) return get_uint32(Data);
        if constexpr (Data == maximum_fragment_uniform_vectors                     ) return get_uint32(Data);
        if constexpr (Data == maximum_frame_buffer_height                          ) return get_uint32(Data);
        if constexpr (Data == maximum_frame_buffer_layers                          ) return get_uint32(Data);
        if constexpr (Data == maximum_frame_buffer_samples                         ) return get_uint32(Data);
        if constexpr (Data == maximum_frame_buffer_width                           ) return get_uint32(Data);
        if constexpr (Data == maximum_geometry_atomic_counters                     ) return get_uint32(Data);
        if constexpr (Data == maximum_geometry_input_components                    ) return get_uint32(Data);
        if constexpr (Data == maximum_geometry_output_components                   ) return get_uint32(Data);
        if constexpr (Data == maximum_geometry_shader_storage_blocks               ) return get_uint32(Data);
        if constexpr (Data == maximum_geometry_texture_image_units                 ) return get_uint32(Data);
        if constexpr (Data == maximum_geometry_uniform_blocks                      ) return get_uint32(Data);
        if constexpr (Data == maximum_geometry_uniform_components                  ) return get_uint32(Data);
        if constexpr (Data == maximum_index_elements                               ) return get_uint32(Data);
        if constexpr (Data == maximum_integer_samples                              ) return get_uint32(Data);
        if constexpr (Data == maximum_label_length                                 ) return get_uint32(Data);
        if constexpr (Data == maximum_program_texel_offset                         ) return get_uint32(Data);
        if constexpr (Data == maximum_rectangle_texture_size                       ) return get_uint32(Data);
        if constexpr (Data == maximum_render_buffer_size                           ) return get_uint32(Data);
        if constexpr (Data == maximum_sample_mask_words                            ) return get_uint32(Data);
        if constexpr (Data == maximum_server_wait_timeout                          ) return get_uint32(Data);
        if constexpr (Data == maximum_shader_storage_buffer_bindings               ) return get_uint32(Data);
        if constexpr (Data == maximum_tessellation_control_atomic_counters         ) return get_uint32(Data);
        if constexpr (Data == maximum_tessellation_control_shaders_torageblocks    ) return get_uint32(Data);
        if constexpr (Data == maximum_tessellation_evaluation_atomic_counters      ) return get_uint32(Data);
        if constexpr (Data == maximum_tessellation_evaluation_shader_storage_blocks) return get_uint32(Data);
        if constexpr (Data == maximum_texture_buffer_size                          ) return get_uint32(Data);
        if constexpr (Data == maximum_texture_image_units                          ) return get_uint32(Data);
        if constexpr (Data == maximum_texture_lod_bias                             ) return get_uint32(Data);
        if constexpr (Data == maximum_texture_size                                 ) return get_uint32(Data);
        if constexpr (Data == maximum_uniform_block_size                           ) return get_uint32(Data);
        if constexpr (Data == maximum_uniform_buffer_bindings                      ) return get_uint32(Data);
        if constexpr (Data == maximum_uniform_locations                            ) return get_uint32(Data);
        if constexpr (Data == maximum_varying_components                           ) return get_uint32(Data);
        if constexpr (Data == maximum_varying_floats                               ) return get_uint32(Data);
        if constexpr (Data == maximum_varying_vectors                              ) return get_uint32(Data);
        if constexpr (Data == maximum_vertex_atomic_counters                       ) return get_uint32(Data);
        if constexpr (Data == maximum_vertex_attribute_bindings                    ) return get_uint32(Data);
        if constexpr (Data == maximum_vertex_attribute_relative_offset             ) return get_uint32(Data);
        if constexpr (Data == maximum_vertex_attributes                            ) return get_uint32(Data);
        if constexpr (Data == maximum_vertex_elements                              ) return get_uint32(Data);
        if constexpr (Data == maximum_vertex_output_components                     ) return get_uint32(Data);
        if constexpr (Data == maximum_vertex_shader_storage_blocks                 ) return get_uint32(Data);
        if constexpr (Data == maximum_vertex_texture_image_units                   ) return get_uint32(Data);
        if constexpr (Data == maximum_vertex_uniform_blocks                        ) return get_uint32(Data);
        if constexpr (Data == maximum_vertex_uniform_components                    ) return get_uint32(Data);
        if constexpr (Data == maximum_vertex_uniform_vectors                       ) return get_uint32(Data);
        if constexpr (Data == maximum_viewport_dimensions                          ) return get_uint32(Data);
        if constexpr (Data == maximum_viewports                                    ) return get_uint32(Data);
        if constexpr (Data == minimum_map_buffer_alignment                         ) return get_uint32(Data);
        if constexpr (Data == minimum_program_texel_offset                         ) return get_int32(Data);
        if constexpr (Data == minor_version                                        ) return get_uint32(Data);
        if constexpr (Data == number_compressed_texture_formats                    ) return get_uint32(Data);
        if constexpr (Data == number_extensions                                    ) return get_uint32(Data);
        if constexpr (Data == number_program_binary_formats                        ) return get_uint32(Data);
        if constexpr (Data == number_shader_binary_formats                         ) return get_uint32(Data);
        if constexpr (Data == pack_alignment                                       ) return get_uint32(Data);
        if constexpr (Data == pack_compressed_block_depth                          ) return get_uint32(Data);
        if constexpr (Data == pack_compressed_block_height                         ) return get_uint32(Data);
        if constexpr (Data == pack_compressed_block_size                           ) return static_cast<gl::size_t>(get_uint32(Data));
        if constexpr (Data == pack_compressed_block_width                          ) return get_uint32(Data);
        if constexpr (Data == pack_image_height                                    ) return get_uint32(Data);
        if constexpr (Data == pack_row_length                                      ) return get_uint32(Data);
        if constexpr (Data == pack_skip_images                                     ) return get_uint32(Data);
        if constexpr (Data == pack_skip_pixels                                     ) return get_uint32(Data);
        if constexpr (Data == pack_skip_rows                                       ) return get_uint32(Data);
        if constexpr (Data == pack_swap_bytes                                      ) return get_boolean(Data);
        if constexpr (Data == parameter_buffer_binding                             ) return get_handle(Data);
        if constexpr (Data == patch_default_inner_level                            ) return get_vector2f(Data);
        if constexpr (Data == patch_default_outer_level                            ) return get_vector4f(Data);
        if constexpr (Data == pixel_pack_buffer_binding                            ) return get_handle(Data);
        if constexpr (Data == pixel_unpack_buffer_binding                          ) return get_handle(Data);
        if constexpr (Data == point_fade_threshold_size                            ) return get_float32(Data);
        if constexpr (Data == point_size                                           ) return get_float32(Data);
        if constexpr (Data == point_size_granularity                               ) return get_float32(Data);
        if constexpr (Data == point_size_range                                     ) return get_vector2f(Data);
        if constexpr (Data == polygon_offset_factor                                ) return get_float32(Data);
        if constexpr (Data == polygon_offset_units                                 ) return get_float32(Data);
        if constexpr (Data == polygon_smooth_hint                                  ) return static_cast<gl::hint_mode_e>                  (get_uint32(Data));
        if constexpr (Data == primitive_restart_index                              ) return get_index(Data);
        if constexpr (Data == program_binary_formats                               ) return get_binary_formats(Data);
        if constexpr (Data == program_pipeline_binding                             ) return get_handle(Data);
        if constexpr (Data == provoking_vertex                                     ) return static_cast<gl::provoking_vertex_mode_e>      (get_uint32(Data));
        if constexpr (Data == read_buffer                                          ) return static_cast<gl::frame_buffer_source_e>        (get_uint32(Data));
        if constexpr (Data == read_frame_buffer_binding                            ) return get_handle(Data);
        if constexpr (Data == render_buffer_binding                                ) return get_handle(Data);
        if constexpr (Data == reset_notification_strategy                          ) return static_cast<gl::reset_notification_strategy_e>(get_uint32(Data));
        if constexpr (Data == sample_buffers                                       ) return get_uint32(Data);
        if constexpr (Data == sample_coverage_invert                               ) return get_boolean(Data);
        if constexpr (Data == sample_coverage_value                                ) return get_float32(Data);
        if constexpr (Data == sampler_binding                                      ) return get_handle(Data);
        if constexpr (Data == samples                                              ) return get_bitfield(Data);
        if constexpr (Data == scissor_box                                          ) return get_area(Data);
        if constexpr (Data == shader_compiler                                      ) return get_boolean(Data);
        if constexpr (Data == shader_storage_buffer_binding                        ) return get_handle(Data);
        if constexpr (Data == shader_storage_buffer_offset_alignment               ) return get_uint32(Data);
        if constexpr (Data == smooth_line_width_granularity                        ) return get_float32(Data);
        if constexpr (Data == smooth_line_width_range                              ) return get_vector2f(Data);
        if constexpr (Data == stencil_back_fail                                    ) return static_cast<gl::stencil_action_e>             (get_uint32(Data));
        if constexpr (Data == stencil_back_function                                ) return static_cast<gl::stencil_function_e>           (get_uint32(Data));
        if constexpr (Data == stencil_back_pass_depth_fail                         ) return static_cast<gl::stencil_action_e>             (get_uint32(Data));
        if constexpr (Data == stencil_back_pass_depth_pass                         ) return static_cast<gl::stencil_action_e>             (get_uint32(Data));
        if constexpr (Data == stencil_back_reference                               ) return get_int32(Data);
        if constexpr (Data == stencil_back_value_mask                              ) return get_uint32(Data);
        if constexpr (Data == stencil_back_write_mask                              ) return get_uint32(Data);
        if constexpr (Data == stencil_clear_value                                  ) return get_index(Data);
        if constexpr (Data == stencil_fail                                         ) return static_cast<gl::stencil_action_e>             (get_uint32(Data));
        if constexpr (Data == stencil_function                                     ) return static_cast<gl::stencil_function_e>           (get_uint32(Data));
        if constexpr (Data == stencil_pass_depth_fail                              ) return static_cast<gl::stencil_action_e>             (get_uint32(Data));
        if constexpr (Data == stencil_pass_depth_pass                              ) return static_cast<gl::stencil_action_e>             (get_uint32(Data));
        if constexpr (Data == stencil_reference                                    ) return get_int32(Data);
        if constexpr (Data == stencil_value_mask                                   ) return get_uint32(Data);
        if constexpr (Data == stencil_write_mask                                   ) return get_uint32(Data);
        if constexpr (Data == supports_stereo                                      ) return get_boolean(Data);
        if constexpr (Data == sub_pixel_bits                                       ) return get_uint32(Data);
        if constexpr (Data == texture_binding_1d                                   ) return get_handle(Data);
        if constexpr (Data == texture_binding_1d_array                             ) return get_handle(Data);
        if constexpr (Data == texture_binding_2d                                   ) return get_handle(Data);
        if constexpr (Data == texture_binding_2d_array                             ) return get_handle(Data);
        if constexpr (Data == texture_binding_2d_multisample                       ) return get_handle(Data);
        if constexpr (Data == texture_binding_2d_multisample_array                 ) return get_handle(Data);
        if constexpr (Data == texture_binding_3d                                   ) return get_handle(Data);
        if constexpr (Data == texture_binding_buffer                               ) return get_handle(Data);
        if constexpr (Data == texture_binding_cubemap                              ) return get_handle(Data);
        if constexpr (Data == texture_binding_rectangle                            ) return get_handle(Data);
        if constexpr (Data == texture_buffer_binding                               ) return get_handle(Data);
        if constexpr (Data == texture_buffer_offset_alignment                      ) return get_uint32(Data);
        if constexpr (Data == texture_compression_hint                             ) return static_cast<gl::hint_mode_e>                  (get_uint32(Data));
        if constexpr (Data == timestamp                                            ) return get_int64(Data);
        if constexpr (Data == transform_feedback_binding                           ) return get_handle(Data);
        if constexpr (Data == transform_feedback_buffer_binding                    ) return get_handle(Data);
        if constexpr (Data == uniform_buffer_binding                               ) return get_handle(Data);
        if constexpr (Data == uniform_buffer_offset_alignment                      ) return get_uint32(Data);
        if constexpr (Data == unpack_alignment                                     ) return get_uint32(Data);
        if constexpr (Data == unpack_compressed_block_depth                        ) return get_uint32(Data);
        if constexpr (Data == unpack_compressed_block_height                       ) return get_uint32(Data);
        if constexpr (Data == unpack_compressed_block_size                         ) return static_cast<gl::size_t>(get_uint32(Data));
        if constexpr (Data == unpack_compressed_block_width                        ) return get_uint32(Data);
        if constexpr (Data == unpack_image_height                                  ) return get_uint32(Data);
        if constexpr (Data == unpack_row_length                                    ) return get_uint32(Data);
        if constexpr (Data == unpack_skip_images                                   ) return get_uint32(Data);
        if constexpr (Data == unpack_skip_pixels                                   ) return get_uint32(Data);
        if constexpr (Data == unpack_skip_rows                                     ) return get_uint32(Data);
        if constexpr (Data == unpack_swap_bytes                                    ) return get_boolean(Data);
        if constexpr (Data == vertex_array_binding                                 ) return get_handle(Data);
        if constexpr (Data == viewport                                             ) return get_area(Data);
        if constexpr (Data == viewport_bounds_range                                ) return get_vector2i(Data);
        if constexpr (Data == viewport_index_provoking_vertex                      ) return static_cast<gl::provoking_vertex_convention_e>(get_uint32(Data));
        if constexpr (Data == viewport_sub_pixel_bits                              ) return get_uint32(Data);
    }
    template<gl::data_e Data>                 requires (meta::is_indexed_data<Data>())
    auto get_value_index                                  (gl::index_t index) -> auto
    {
        auto get_uint32                = [](gl::data_e data, gl::index_t index) -> gl::uint32_t
            {
                auto value = gl::int32_t{};
                return ::glGetIntegeri_v(gl::to_underlying(data), index, &value), std::bit_cast<gl::uint32_t>(value);
            };
        auto get_uint64                = [](gl::data_e data, gl::index_t index) -> gl::uint64_t
            {
                auto value = gl::int64_t{};
                return ::glGetInteger64i_v(gl::to_underlying(data), index, &value), std::bit_cast<gl::uint64_t>(value);
            };
        auto get_area                  = [](gl::data_e data, gl::index_t index) -> gl::area_t
            {
                auto value = gl::vector_4u{};
                ::glGetIntegeri_v(gl::to_underlying(data), index, std::bit_cast<gl::int32_t*>(gl::value_pointer(value)));

                return gl::area_t{ gl::vector_2u{ value.z, value.w }, gl::vector_2u{ value.x, value.y } };
            };
        auto get_blending_equation     = [](gl::data_e data, gl::index_t index) -> std::array<gl::blending_equation_e, 8u>
            {
                auto value = std::array<gl::int32_t, 8u>{};
                return ::glGetIntegeri_v(gl::to_underlying(data), index, value.data()), std::bit_cast<std::array<gl::blending_equation_e, 8u>>(value);
            };
        auto get_blending_factor       = [](gl::data_e data, gl::index_t index) -> std::array<gl::blending_factor_e, 8u>
            {
                auto value = std::array<gl::int32_t, 8u>{};
                return ::glGetIntegeri_v(gl::to_underlying(data), index, value.data()), std::bit_cast<std::array<gl::blending_equation_e, 8u>>(value);
            };
        auto get_handle                = [](gl::data_e data, gl::index_t index) -> gl::handle_t
            {
                auto value = gl::int32_t{};
                return ::glGetIntegeri_v(gl::to_underlying(data), index, &value), std::bit_cast<gl::handle_t>(value);
            };
        auto get_vector3u              = [](gl::data_e data, gl::index_t index) -> gl::vector_3u
            {
                auto value = gl::vector_3i{};
                return ::glGetIntegeri_v(gl::to_underlying(data), index, gl::value_pointer(value)), std::bit_cast<gl::vector_3u>(value);
            };
        auto get_image_binding_access  = [](gl::data_e data, gl::index_t index) -> std::array<gl::image_access_e, 8u>
            {
                auto value = std::array<gl::int32_t, 8u>{};
                return ::glGetIntegeri_v(gl::to_underlying(data), index, value.data()), std::bit_cast<std::array<gl::image_access_e, 8u>>(value);
            };
        auto get_image_binding_format  = [](gl::data_e data, gl::index_t index) -> std::array<gl::uint32_t, 8u>
            {
                auto value = std::array<gl::int32_t, 8u>{};
                return ::glGetIntegeri_v(gl::to_underlying(data), index, value.data()), std::bit_cast<std::array<gl::uint32_t, 8u>>(value);
            };
        auto get_image_binding_layer   = [](gl::data_e data, gl::index_t index) -> std::array<gl::uint32_t, 8u>
            {
                auto value = std::array<gl::int32_t, 8u>{};
                return ::glGetIntegeri_v(gl::to_underlying(data), index, value.data()), std::bit_cast<std::array<gl::uint32_t, 8u>>(value);
            };
        auto get_image_binding_layered = [](gl::data_e data, gl::index_t index) -> std::array<gl::bool_t, 8u>
            {
                auto value = std::array<gl::boolean_t, 8u>{};
                return ::glGetBooleani_v(gl::to_underlying(data), index, value.data()), std::bit_cast<std::array<gl::bool_t, 8u>>(value);
            };
        auto get_image_binding_level   = [](gl::data_e data, gl::index_t index) -> std::array<gl::uint32_t, 8u>
            {
                auto value = std::array<gl::int32_t, 8u>{};
                return ::glGetIntegeri_v(gl::to_underlying(data), index, value.data()), std::bit_cast<std::array<gl::uint32_t, 8u>>(value);
            };
        auto get_image_binding_name    = [](gl::data_e data, gl::index_t index) -> std::array<gl::uint32_t, 8u>
            {
                auto value = std::array<gl::int32_t, 8u>{};
                return ::glGetIntegeri_v(gl::to_underlying(data), index, value.data()), std::bit_cast<std::array<gl::uint32_t, 8u>>(value);
            };
        auto get_scissor_box           = [](gl::data_e data, gl::index_t index) -> gl::vector_4i
            {
                auto value = gl::vector_4i{};
                return ::glGetIntegeri_v(gl::to_underlying(data), index, gl::value_pointer(value)), value;
            };

        using enum gl::data_e;
        if constexpr (Data == atomic_counter_buffer_binding    ) return get_handle               (Data, index);
        if constexpr (Data == blending_equation_alpha          ) return get_blending_equation    (Data, index);
        if constexpr (Data == blending_equation_rgb            ) return get_blending_equation    (Data, index);
        if constexpr (Data == blending_source_alpha            ) return get_blending_factor      (Data, index);
        if constexpr (Data == blending_source_rgb              ) return get_blending_factor      (Data, index);
        if constexpr (Data == blending_destination_alpha       ) return get_blending_factor      (Data, index);
        if constexpr (Data == blending_destination_rgb         ) return get_blending_factor      (Data, index);
        if constexpr (Data == image_binding_access             ) return get_image_binding_access (Data, index);
        if constexpr (Data == image_binding_format             ) return get_image_binding_format (Data, index);
        if constexpr (Data == image_binding_layer              ) return get_image_binding_layer  (Data, index);
        if constexpr (Data == image_binding_layered            ) return get_image_binding_layered(Data, index);
        if constexpr (Data == image_binding_level              ) return get_image_binding_level  (Data, index);
        if constexpr (Data == image_binding_name               ) return get_image_binding_name   (Data, index);
        if constexpr (Data == maximum_compute_work_group_count ) return get_vector3u             (Data, index);
        if constexpr (Data == maximum_compute_work_group_size  ) return get_vector3u             (Data, index);
        if constexpr (Data == query_buffer_binding             ) return get_handle               (Data, index);
        if constexpr (Data == scissor_box                      ) return get_scissor_box          (Data, index);
        if constexpr (Data == sample_mask_value                ) return get_uint32               (Data, index);
        if constexpr (Data == shader_storage_buffer_binding    ) return get_handle               (Data, index);
        if constexpr (Data == shader_storage_buffer_size       ) return get_uint64               (Data, index);
        if constexpr (Data == shader_storage_buffer_start      ) return get_uint64               (Data, index);
        if constexpr (Data == transform_feedback_buffer_binding) return get_handle               (Data, index);
        if constexpr (Data == transform_feedback_buffer_size   ) return get_uint64               (Data, index);
        if constexpr (Data == transform_feedback_buffer_start  ) return get_uint64               (Data, index);
        if constexpr (Data == uniform_buffer_binding           ) return get_handle               (Data, index);
        if constexpr (Data == uniform_buffer_size              ) return get_uint64               (Data, index);
        if constexpr (Data == uniform_buffer_start             ) return get_uint64               (Data, index);
        if constexpr (Data == vertex_binding_buffer            ) return get_handle               (Data, index);
        if constexpr (Data == vertex_binding_divisor           ) return get_uint32               (Data, index);
        if constexpr (Data == vertex_binding_offset            ) return get_uint32               (Data, index);
        if constexpr (Data == vertex_binding_stride            ) return get_uint32               (Data, index);
        if constexpr (Data == viewport                         ) return get_area                 (Data, index);
    }
    template<gl::feature_e Feature>
    void enable                                           ()
    {
        ::glEnable(gl::to_underlying(Feature));
    }
    template<gl::feature_e Feature>           requires (meta::is_indexed_feature<Feature>())
    void enable_index                                     (gl::index_t index)
    {
        ::glEnablei(gl::to_underlying(Feature), index);
    }
    template<gl::feature_e Feature>
    void disable                                          ()
    {
        ::glDisable(gl::to_underlying(Feature));
    }
    template<gl::feature_e Feature>           requires (meta::is_indexed_feature<Feature>())
    void disable_index                                    (gl::index_t index)
    {
        ::glDisablei(gl::to_underlying(Feature), index);
    }
    template<gl::feature_e Feature>
    auto is_enabled                                       () -> gl::bool_t
    {
        return ::glIsEnabled(gl::to_underlying(Feature));
    }
    template<gl::feature_e Feature>           requires (meta::is_indexed_feature<Feature>())
    auto is_enabled_index                                 (gl::index_t index) -> gl::bool_t
    {
        return ::glIsEnabledi(gl::to_underlying(Feature));
    }
    template<gl::callback_pointer_parameter_e Parameter, typename T = gl::void_t>
    auto get_pointer_value                                () -> T*
    {
        auto value = std::bit_cast<gl::void_t*>(nullptr);
        ::glGetPointerv(gl::to_underlying(Parameter), &value);
        
        return std::bit_cast<T*>(value);
    }
    template<gl::context_property_e Property> requires (meta::is_non_indexed_property<Property>())
    auto get_string                                       () -> std::string
    {
        return std::string{ std::bit_cast<gl::c_string>(::glGetString(gl::to_underlying(Property))) };
    }
    template<gl::context_property_e Property> requires (meta::is_indexed_property<Property>())
    auto get_string_index                                 (gl::index_t index) -> std::string
    {
        return std::string{ std::bit_cast<gl::c_string>(::glGetStringi(gl::to_underlying(Property), static_cast<gl::uint32_t>(index))) };
    }
    template<gl::internal_format_parameter_e Parameter>
    auto get_internal_format_value                        (gl::internal_format_target_e internal_format_target, gl::enum_t internal_format) -> auto
    {
        auto get_internal_format_iv   = [](gl::internal_format_target_e internal_format_target, gl::enum_t internal_format, gl::internal_format_parameter_e internal_format_parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return ::glGetInternalformativ(gl::to_underlying(internal_format_target), internal_format, gl::to_underlying(internal_format_parameter), static_cast<gl::sizei_t>(sizeof(gl::int32_t)), &value), value;
            };
        auto get_internal_format_i64v = [](gl::internal_format_target_e internal_format_target, gl::enum_t internal_format, gl::internal_format_parameter_e internal_format_parameter) -> gl::int64_t
            {
                auto value = gl::int64_t{};
                return ::glGetInternalformati64v(gl::to_underlying(internal_format_target), internal_format, gl::to_underlying(internal_format_parameter), static_cast<gl::sizei_t>(sizeof(gl::int64_t)), &value), value;
            };

        //Queries marked with "//" may be erroneous
        using enum gl::internal_format_parameter_e;
        if constexpr (Parameter == auto_generate_mipmap                  ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == clear_buffer                          ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == clear_texture                         ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == color_components                      ) return static_cast<gl::uint32_t        >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == color_encoding                        ) return static_cast<gl::color_encoding_e>(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == is_color_renderable                   ) return static_cast<gl::bool_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == compute_texture                       ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == depth_components                      ) return static_cast<gl::uint32_t        >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == is_depth_renderable                   ) return static_cast<gl::bool_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == supports_filter                       ) return static_cast<gl::bool_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == fragment_texture                      ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == supports_frame_buffer_blend           ) return static_cast<gl::bool_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == frame_buffer_renderable               ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == frame_buffer_renderable_layered       ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == geometry_texture                      ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == get_texture_image_format              ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == get_texture_image_type                ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == image_compatibility_class             ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == image_format_compatibility_type       ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == image_pixel_format                    ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == image_pixel_type                      ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == internal_format_alpha_size            ) return static_cast<gl::sizeu_t         >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == internal_format_alpha_type            ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == internal_format_blue_size             ) return static_cast<gl::sizeu_t         >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == internal_format_blue_type             ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == internal_format_depth_size            ) return static_cast<gl::sizeu_t         >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == internal_format_depth_type            ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == internal_format_green_size            ) return static_cast<gl::sizeu_t         >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == internal_format_green_type            ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == internal_format_preferred             ) return static_cast<gl::bool_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == internal_format_red_size              ) return static_cast<gl::sizeu_t         >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == internal_format_red_type              ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == internal_format_shared_size           ) return static_cast<gl::sizeu_t         >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == internal_format_stencil_size          ) return static_cast<gl::sizeu_t         >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == internal_format_stencil_type          ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == is_supported                          ) return static_cast<gl::bool_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == maximum_combined_dimensions           ) return static_cast<gl::uint32_t        >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == maximum_depth                         ) return static_cast<gl::uint32_t        >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == maximum_height                        ) return static_cast<gl::uint32_t        >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == maximum_layers                        ) return static_cast<gl::uint32_t        >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == maximum_width                         ) return static_cast<gl::uint32_t        >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == supports_mipmap                       ) return static_cast<gl::bool_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == number_sample_counts                  ) return static_cast<gl::uint32_t        >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == read_pixels                           ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == read_pixels_format                    ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == read_pixels_type                      ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == samples                               ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == shader_image_atomic                   ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == shader_image_load                     ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == shader_image_store                    ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == simultaneous_texture_and_depth_test   ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == simultaneous_texture_and_depth_write  ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == simultaneous_texture_and_stencil_test ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == simultaneous_texture_and_stencil_write) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == srgb_read                             ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == srgb_write                            ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == stencil_components                    ) return static_cast<gl::uint32_t        >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == is_stencil_renderable                 ) return static_cast<gl::bool_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == tessellation_control_texture          ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == tessellation_evaluation_texture       ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == is_texture_compressed                 ) return static_cast<gl::bool_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == texture_compressed_block_height       ) return static_cast<gl::uint32_t        >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == texture_compressed_block_size         ) return static_cast<gl::sizeu_t         >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == texture_compressed_block_width        ) return static_cast<gl::uint32_t        >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == texture_gather                        ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == texture_gather_shadow                 ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == texture_image_format                  ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == texture_image_type                    ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
        if constexpr (Parameter == texture_shadow                        ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == texture_view                          ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == vertex_texture                        ) return static_cast<gl::support_level_e >(get_internal_format_iv(internal_format_target, internal_format, Parameter));
        if constexpr (Parameter == view_compatibility_class              ) return static_cast<gl::enum_t          >(get_internal_format_iv(internal_format_target, internal_format, Parameter)); //
    }



    //Chapter 4 - Event Model
    template<gl::synchronization_property_e Property>
    auto get_sync_value                                   (gl::sync_t sync) -> auto
    {
        auto get_sync_iv = [](gl::sync_t sync, gl::synchronization_property_e property) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return ::glGetSynciv(sync, gl::to_underlying(property), gl::sizei_t{ 1 }, nullptr, &value), value;
            };

        using enum gl::synchronization_property_e;
        if constexpr (Property == condition) return static_cast<gl::synchronization_object_condition_e>(get_sync_iv(sync, Property));
        if constexpr (Property == flags    ) return static_cast<gl::bitfield_t                        >(get_sync_iv(sync, Property));
        if constexpr (Property == status   ) return static_cast<gl::synchronization_object_status_e   >(get_sync_iv(sync, Property));
        if constexpr (Property == type     ) return static_cast<gl::synchronization_object_type_e     >(get_sync_iv(sync, Property));
    }
    template<gl::query_symbol_e Symbol>
    auto get_query_value                                  (gl::query_target_e query_target) -> gl::uint32_t
    {
        auto value = gl::uint32_t{};
        ::glGetQueryiv(gl::to_underlying(query_target), gl::to_underlying(Symbol), std::bit_cast<gl::int32_t*>(&value));
        
        return value;
    }
    template<gl::query_symbol_e Symbol>
    auto get_query_value_index                            (gl::query_target_e query_target, gl::index_t index) -> gl::uint32_t
    {
        auto value = gl::uint32_t{};
        ::glGetQueryIndexediv(gl::to_underlying(query_target), index, gl::to_underlying(Symbol), std::bit_cast<gl::int32_t*>(&value));
        
        return value;
    }
    template<gl::query_parameter_e Parameter>
    auto get_query_object_value                           (gl::handle_t query) -> auto
    {
        auto get_query_object_iv  = [](gl::handle_t query, gl::query_parameter_e parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return ::glGetQueryObjectiv(gl::to_underlying(query), gl::to_underlying(parameter), &value), value;
            };
        auto get_query_object_uiv = [](gl::handle_t query, gl::query_parameter_e parameter) -> gl::uint32_t
            {
                auto value = gl::uint32_t{};
                return ::glGetQueryObjectuiv(gl::to_underlying(query), gl::to_underlying(parameter), &value), value;
            };

        using enum gl::query_parameter_e;
        if constexpr (Parameter == target          ) return static_cast<gl::query_target_e>(get_query_object_iv (query, Parameter));
        if constexpr (Parameter == result          ) return                                 get_query_object_uiv(query, Parameter) ;
        if constexpr (Parameter == result_available) return static_cast<gl::bool_t        >(get_query_object_iv (query, Parameter));
        if constexpr (Parameter == result_no_wait  ) return                                 get_query_object_uiv(query, Parameter) ;
    }
    template<gl::query_parameter_e Parameter>
    void get_query_buffer_object_value                    (gl::handle_t query, gl::handle_t buffer, gl::ptrdiff_t byte_offset)
    {
        auto get_query_buffer_object_iv  = [](gl::handle_t query, gl::handle_t buffer, gl::query_parameter_e query_parameter, gl::ptrdiff_t byte_offset)
            {
                ::glGetQueryBufferObjectiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(query_parameter), byte_offset);
            };
        auto get_query_buffer_object_uiv = [](gl::handle_t query, gl::handle_t buffer, gl::query_parameter_e query_parameter, gl::ptrdiff_t byte_offset)
            {
                ::glGetQueryBufferObjectuiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(query_parameter), byte_offset);
            };

        using enum gl::query_parameter_e;
        if constexpr (Parameter == target          ) get_query_buffer_object_iv (query, buffer, Parameter, byte_offset);
        if constexpr (Parameter == result          ) get_query_buffer_object_uiv(query, buffer, Parameter, byte_offset);
        if constexpr (Parameter == result_available) get_query_buffer_object_iv (query, buffer, Parameter, byte_offset);
        if constexpr (Parameter == result_no_wait  ) get_query_buffer_object_uiv(query, buffer, Parameter, byte_offset);
    }



    //Chapter 6 - Buffer Objects
    template<gl::buffer_parameter_e Parameter>
    auto get_buffer_parameter_value                       (gl::handle_t buffer) -> auto
    {
        auto get_buffer_parameter_iv   = [](gl::handle_t buffer, gl::buffer_parameter_e parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return ::glGetNamedBufferParameteriv(gl::to_underlying(buffer), gl::to_underlying(parameter), &value), value;
            };
        auto get_buffer_parameter_i64v = [](gl::handle_t buffer, gl::buffer_parameter_e parameter) -> gl::int64_t
            {
                auto value = gl::int64_t{};
                return ::glGetNamedBufferParameteri64v(gl::to_underlying(buffer), gl::to_underlying(parameter), &value), value;
            };

        using enum gl::buffer_parameter_e;
        if constexpr (Parameter == access       ) return static_cast<gl::buffer_mapping_access_e      >(get_buffer_parameter_iv  (buffer, Parameter));
        if constexpr (Parameter == access_flags ) return static_cast<gl::buffer_mapping_access_flags_e>(get_buffer_parameter_iv  (buffer, Parameter));
        if constexpr (Parameter == is_immutable ) return static_cast<gl::bool_t                       >(get_buffer_parameter_iv  (buffer, Parameter));
        if constexpr (Parameter == is_mapped    ) return static_cast<gl::bool_t                       >(get_buffer_parameter_iv  (buffer, Parameter));
        if constexpr (Parameter == map_length   ) return static_cast<gl::size_t                       >(get_buffer_parameter_i64v(buffer, Parameter));
        if constexpr (Parameter == map_offset   ) return static_cast<gl::size_t                       >(get_buffer_parameter_i64v(buffer, Parameter));
        if constexpr (Parameter == size         ) return static_cast<gl::size_t                       >(get_buffer_parameter_i64v(buffer, Parameter));
        if constexpr (Parameter == storage_flags) return static_cast<gl::buffer_storage_flags_e       >(get_buffer_parameter_iv  (buffer, Parameter));
        if constexpr (Parameter == usage        ) return static_cast<gl::buffer_usage_e               >(get_buffer_parameter_iv  (buffer, Parameter));
    }
    template<typename T>
    auto get_buffer_data                                  (gl::handle_t buffer) -> std::vector<T>
    {
        const auto buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        if ((buffer_size % sizeof(T)) != 0u) throw std::invalid_argument{ "buffer size is not divisible by type size" };

              auto vector      = std::vector<T>(buffer_size / sizeof(T));
        return ::glGetNamedBufferSubData(gl::to_underlying(buffer), gl::ptrdiff_t{ 0 }, buffer_size, vector.data()), vector;
    }
    template<typename T>
    auto get_buffer_sub_data                              (gl::handle_t buffer, gl::range_t range) -> std::vector<T>
    {
        const auto buffer_size   = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        if ((buffer_size % sizeof(T)) != gl::size_t{ 0u }) throw std::invalid_argument{ "buffer size is not divisible by type size" };

        const auto intersection  = gl::range_intersection(range, gl::range_t{ buffer_size / sizeof(T) });
        if (intersection.empty()) return std::vector<T>{};

              auto vector        = std::vector<T>(intersection.count);
        ::glGetNamedBufferSubData(gl::to_underlying(buffer), static_cast<gl::ptrdiff_t>(intersection.index * sizeof(T)), static_cast<gl::sizei_t>(intersection.count * sizeof(T)), vector.data());
        
        return vector;
    }
    


    //Chapter 7 - Programs and Shaders
    template<gl::shader_parameter_e Parameter>
    auto get_shader_value                                 (gl::handle_t shader) -> auto
    {
        auto get_shader_iv = [](gl::handle_t shader, gl::shader_parameter_e shader_parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                ::glGetShaderiv(gl::to_underlying(shader), gl::to_underlying(shader_parameter), &value);
                
                return value;
            };

        using enum gl::shader_parameter_e;
        if constexpr (Parameter == compile_status ) return static_cast<gl::bool_t       >(get_shader_iv(shader, Parameter));
        if constexpr (Parameter == delete_status  ) return static_cast<gl::bool_t       >(get_shader_iv(shader, Parameter));
        if constexpr (Parameter == info_log_length) return static_cast<gl::size_t       >(get_shader_iv(shader, Parameter));
        if constexpr (Parameter == source_length  ) return static_cast<gl::size_t       >(get_shader_iv(shader, Parameter));
        if constexpr (Parameter == type           ) return static_cast<gl::shader_type_e>(get_shader_iv(shader, Parameter));
    }
    template<gl::program_parameter_e Parameter>
    auto get_program_value                                (gl::handle_t program) -> auto
    {
        auto get_program_iv = [](gl::handle_t program, gl::program_parameter_e program_parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                ::glGetProgramiv(gl::to_underlying(program), gl::to_underlying(program_parameter), &value);
                
                return value;
            };

        using enum gl::program_parameter_e;
        if constexpr (Parameter == active_atomic_counter_buffers            ) return static_cast<gl::uint32_t                        >(get_program_iv(program, Parameter));
        if constexpr (Parameter == active_attribute_maximum_length          ) return static_cast<gl::size_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == active_attributes                        ) return static_cast<gl::uint32_t                        >(get_program_iv(program, Parameter));
        if constexpr (Parameter == active_uniform_block_maximum_name_length ) return static_cast<gl::size_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == active_uniform_blocks                    ) return static_cast<gl::uint32_t                        >(get_program_iv(program, Parameter));
        if constexpr (Parameter == active_uniform_maximum_length            ) return static_cast<gl::size_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == active_uniforms                          ) return static_cast<gl::uint32_t                        >(get_program_iv(program, Parameter));
        if constexpr (Parameter == attached_shaders                         ) return static_cast<gl::uint32_t                        >(get_program_iv(program, Parameter));
        if constexpr (Parameter == binary_length                            ) return static_cast<gl::size_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == compute_work_group_size                  ) return static_cast<gl::size_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == delete_status                            ) return static_cast<gl::bool_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == geometry_input_type                      ) return static_cast<gl::draw_mode_e                     >(get_program_iv(program, Parameter));
        if constexpr (Parameter == geometry_output_type                     ) return static_cast<gl::draw_mode_e                     >(get_program_iv(program, Parameter));
        if constexpr (Parameter == geometry_shader_invocations              ) return static_cast<gl::uint32_t                        >(get_program_iv(program, Parameter));
        if constexpr (Parameter == geometry_vertices_out                    ) return static_cast<gl::uint32_t                        >(get_program_iv(program, Parameter));
        if constexpr (Parameter == info_log_length                          ) return static_cast<gl::size_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == is_binary_retrievable                    ) return static_cast<gl::bool_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == is_separable                             ) return static_cast<gl::bool_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == link_status                              ) return static_cast<gl::bool_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == tessellation_control_output_vertices     ) return static_cast<gl::uint32_t                        >(get_program_iv(program, Parameter));
        if constexpr (Parameter == tessellation_generation_mode             ) return static_cast<gl::tessellation_generation_e       >(get_program_iv(program, Parameter));
        if constexpr (Parameter == tessellation_generation_point_mode       ) return static_cast<gl::bool_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == tessellation_generation_spacing          ) return static_cast<gl::tessellation_spacing_e          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == tessellation_generation_vertex_order     ) return static_cast<gl::tessellation_vertex_order_e     >(get_program_iv(program, Parameter));
        if constexpr (Parameter == transform_feedback_buffer_mode           ) return static_cast<gl::transform_feedback_buffer_mode_e>(get_program_iv(program, Parameter));
        if constexpr (Parameter == transform_feedback_varying_maximum_length) return static_cast<gl::size_t                          >(get_program_iv(program, Parameter));
        if constexpr (Parameter == transform_feedback_varyings              ) return static_cast<gl::uint32_t                        >(get_program_iv(program, Parameter));
        if constexpr (Parameter == validate_status                          ) return static_cast<gl::bool_t                          >(get_program_iv(program, Parameter));
    }
    template<gl::pipeline_property_e Property>
    auto get_program_pipeline_value                       (gl::handle_t pipeline) -> auto
    {
        auto get_program_pipeline_iv = [](gl::handle_t pipeline, gl::pipeline_property_e pipeline_property) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                ::glGetProgramPipelineiv(gl::to_underlying(pipeline), gl::to_underlying(pipeline_property), &value);
                
                return value;
            };

        using enum gl::pipeline_property_e;
        if   constexpr (Property == validate_status) return static_cast<gl::bool_t  >(get_program_pipeline_iv(pipeline, Property));
        if   constexpr (Property == info_log_length) return static_cast<gl::size_t  >(get_program_pipeline_iv(pipeline, Property));
        else                                         return static_cast<gl::handle_t>(get_program_pipeline_iv(pipeline, Property));
    }
    auto get_attached_shaders                             (gl::handle_t program) -> std::vector<gl::handle_t>
    {
        const auto attached_shaders = gl::get_program_value<gl::program_parameter_e::attached_shaders>(program);
              auto vector           = std::vector<gl::handle_t>(attached_shaders);
        ::glGetAttachedShaders(gl::to_underlying(program), static_cast<gl::sizei_t>(attached_shaders), nullptr, gl::to_underlying_pointer(vector.data()));
        
        return vector;
    }
    auto get_shader_info_log                              (gl::handle_t shader) -> std::string
    {
        const auto info_log_length = get_shader_value<gl::shader_parameter_e::info_log_length>(shader);
              auto info_log        = std::string(info_log_length, '\0');

        if (!info_log.empty())
        {
            ::glGetShaderInfoLog(gl::to_underlying(shader), static_cast<gl::sizei_t>(info_log_length), nullptr, info_log.data());
            info_log.pop_back();
        }

        return info_log;
    }
    auto get_program_info_log                             (gl::handle_t program) -> std::string
    {
        const auto info_log_length = gl::get_program_value<gl::program_parameter_e::info_log_length>(program);
              auto info_log        = std::string(info_log_length, '\0');

        if (!info_log.empty())
        {
            ::glGetProgramInfoLog(gl::to_underlying(program), static_cast<gl::sizei_t>(info_log_length), nullptr, info_log.data());
            info_log.pop_back();
        }

        return info_log;
    }
    auto get_pipeline_info_log                            (gl::handle_t pipeline) -> std::string
    {
        const auto info_log_length = gl::get_program_pipeline_value<gl::pipeline_property_e::info_log_length>(pipeline);
              auto info_log        = std::string(info_log_length, '\0');

        if (!info_log.empty())
        {
            ::glGetProgramPipelineInfoLog(gl::to_underlying(pipeline), static_cast<gl::sizei_t>(info_log_length), nullptr, info_log.data());
            info_log.pop_back();
        }

        return info_log;
    }
    auto get_shader_source                                (gl::handle_t shader) -> std::string
    {
        const auto shader_source_length = get_shader_value<gl::shader_parameter_e::source_length>(shader);
              auto shader_source        = std::string(shader_source_length, '\0');

        if (!shader_source.empty())
        {
            ::glGetShaderSource(gl::to_underlying(shader), static_cast<gl::sizei_t>(shader_source_length), nullptr, shader_source.data());
            shader_source.pop_back();
        }

        return shader_source;
    }
    auto get_shader_precision_format                      (gl::shader_type_e shader_type, gl::shader_precision_format_e shader_precision_format) -> std::tuple<std::array<gl::int32_t, 2u>, gl::int32_t>
    {
        auto range     = std::array<gl::int32_t, 2u>{};
        auto precision = gl::int32_t{};
        return ::glGetShaderPrecisionFormat(gl::to_underlying(shader_type), gl::to_underlying(shader_precision_format), range.data(), &precision), std::make_tuple(range, precision);
    }



    //Chapter 8 - Textures and Samplers
    template<gl::sampler_parameter_e Parameter>
    auto get_sampler_parameter_value                      (gl::handle_t sampler) -> auto
    {
        auto get_sampler_parameter_iv  = [](gl::handle_t sampler, gl::sampler_parameter_e sampler_parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                ::glGetSamplerParameteriv(gl::to_underlying(sampler), gl::to_underlying(sampler_parameter), &value);
                
                return value;
            };
        auto get_sampler_parameter_uiv = [](gl::handle_t sampler, gl::sampler_parameter_e sampler_parameter) -> gl::uint32_t
            {
                auto value = gl::uint32_t{};
                ::glGetSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(sampler_parameter), &value);
                
                return value;
            };
        auto get_sampler_parameter_fv  = [](gl::handle_t sampler, gl::sampler_parameter_e sampler_parameter) -> gl::float32_t
            {
                auto value = gl::float32_t{};
                ::glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(sampler_parameter), &value);
                
                return value;
            };
        auto get_border_color          = [](gl::handle_t sampler) -> gl::vector_4f
            {
                auto value = gl::vector_4f{};
                return ::glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(gl::sampler_parameter_e::border_color), gl::value_pointer(value)), value;
            };

        using enum gl::sampler_parameter_e;
        if constexpr (Parameter == border_color        ) return                                                (get_border_color         (sampler           ));
        if constexpr (Parameter == compare_function    ) return static_cast<gl::texture_compare_function_e    >(get_sampler_parameter_uiv(sampler, Parameter));
        if constexpr (Parameter == compare_mode        ) return static_cast<gl::texture_compare_mode_e        >(get_sampler_parameter_uiv(sampler, Parameter));
        if constexpr (Parameter == lod_bias            ) return                                                (get_sampler_parameter_fv (sampler, Parameter));
        if constexpr (Parameter == magnification_filter) return static_cast<gl::texture_magnification_filter_e>(get_sampler_parameter_uiv(sampler, Parameter));
        if constexpr (Parameter == maximum_anisotropy  ) return                                                (get_sampler_parameter_fv (sampler, Parameter));
        if constexpr (Parameter == maximum_lod         ) return                                                (get_sampler_parameter_fv (sampler, Parameter));
        if constexpr (Parameter == minification_filter ) return static_cast<gl::texture_minification_filter_e >(get_sampler_parameter_uiv(sampler, Parameter));
        if constexpr (Parameter == minimum_lod         ) return                                                (get_sampler_parameter_fv (sampler, Parameter));
        if constexpr (Parameter == wrapping_r          ) return static_cast<gl::texture_wrapping_e            >(get_sampler_parameter_uiv(sampler, Parameter));
        if constexpr (Parameter == wrapping_s          ) return static_cast<gl::texture_wrapping_e            >(get_sampler_parameter_uiv(sampler, Parameter));
        if constexpr (Parameter == wrapping_t          ) return static_cast<gl::texture_wrapping_e            >(get_sampler_parameter_uiv(sampler, Parameter));
    }
    template<gl::texture_parameter_e Parameter>
    auto get_texture_parameter_value                      (gl::handle_t texture) -> auto
    {
        auto get_texture_parameter_iv = [](gl::handle_t texture, gl::texture_parameter_e texture_parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                ::glGetTextureParameteriv(gl::to_underlying(texture), gl::to_underlying(texture_parameter), &value);
                
                return value;
            };
        auto get_texture_parameter_fv = [](gl::handle_t texture, gl::texture_parameter_e texture_parameter) -> gl::float32_t
            {
                auto value = gl::float32_t{};
                ::glGetTextureParameterfv(gl::to_underlying(texture), gl::to_underlying(texture_parameter), &value);
                
                return value;
            };
        auto get_array4f              = [](gl::handle_t texture, gl::texture_parameter_e texture_parameter) -> std::array<gl::float32_t, 4u>
            {
                auto value = std::array<gl::float32_t, 4u>{};
                ::glGetTextureParameterfv(gl::to_underlying(texture), gl::to_underlying(texture_parameter), value.data());
                
                return value;
            };

        using enum gl::texture_parameter_e;
        if constexpr (Parameter == base_level          ) return static_cast<gl::uint32_t                      >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == border_color        ) return                                                 get_array4f             (texture, Parameter);
        if constexpr (Parameter == compare_function    ) return static_cast<gl::texture_compare_function_e    >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == compare_mode        ) return static_cast<gl::texture_compare_mode_e        >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == depth_stencil_mode  ) return static_cast<gl::depth_stencil_texture_mode_e  >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == lod_bias            ) return                                                 get_texture_parameter_fv(texture, Parameter);
        if constexpr (Parameter == magnification_filter) return static_cast<gl::texture_magnification_filter_e>(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == maximum_anisotropy  ) return                                                 get_texture_parameter_fv(texture, Parameter);
        if constexpr (Parameter == maximum_level       ) return static_cast<gl::uint32_t                      >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == maximum_lod         ) return                                                 get_texture_parameter_fv(texture, Parameter);
        if constexpr (Parameter == minification_filter ) return static_cast<gl::texture_minification_filter_e >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == minimum_lod         ) return                                                 get_texture_parameter_fv(texture, Parameter);
        if constexpr (Parameter == swizzle_a           ) return static_cast<gl::texture_swizzle_e             >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == swizzle_b           ) return static_cast<gl::texture_swizzle_e             >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == swizzle_g           ) return static_cast<gl::texture_swizzle_e             >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == swizzle_r           ) return static_cast<gl::texture_swizzle_e             >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == swizzle_rgba        ) return static_cast<gl::texture_swizzle_e             >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == target              ) return static_cast<gl::texture_target_e              >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == wrapping_r          ) return static_cast<gl::texture_wrapping_e            >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == wrapping_s          ) return static_cast<gl::texture_wrapping_e            >(get_texture_parameter_iv(texture, Parameter));
        if constexpr (Parameter == wrapping_t          ) return static_cast<gl::texture_wrapping_e            >(get_texture_parameter_iv(texture, Parameter));
    }
    template<gl::texture_level_parameter_e Parameter>
    auto get_texture_level_parameter_value                (gl::handle_t texture, gl::uint32_t image_level)
    {
        auto get_texture_level_parameter_iv = [](gl::handle_t texture, gl::uint32_t image_level, gl::texture_level_parameter_e texture_level_parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                ::glGetTextureLevelParameteriv(gl::to_underlying(texture), static_cast<gl::int32_t>(image_level), gl::to_underlying(texture_level_parameter), &value);
                
                return value;
            };

        using enum gl::texture_level_parameter_e;
        if constexpr (Parameter == alpha_size           ) return static_cast<gl::size_t                  >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == alpha_type           ) return static_cast<gl::texture_component_type_e>(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == blue_size            ) return static_cast<gl::size_t                  >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == blue_type            ) return static_cast<gl::texture_component_type_e>(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == buffer_offset        ) return static_cast<gl::ptrdiff_t               >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == buffer_size          ) return static_cast<gl::size_t                  >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == compressed_image_size) return static_cast<gl::size_t                  >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == depth                ) return static_cast<gl::uint32_t                >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == depth_size           ) return static_cast<gl::size_t                  >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == depth_type           ) return static_cast<gl::texture_component_type_e>(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == green_size           ) return static_cast<gl::size_t                  >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == green_type           ) return static_cast<gl::texture_component_type_e>(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == height               ) return static_cast<gl::uint32_t                >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == internal_format      ) return static_cast<gl::enum_t                  >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == is_compressed        ) return static_cast<gl::bool_t                  >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == red_size             ) return static_cast<gl::size_t                  >(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == red_type             ) return static_cast<gl::texture_component_type_e>(get_texture_level_parameter_iv(texture, image_level, Parameter));
        if constexpr (Parameter == width                ) return static_cast<gl::uint32_t                >(get_texture_level_parameter_iv(texture, image_level, Parameter));
    }
    template<typename T = gl::byte_t>
    auto get_texture_image                                (gl::handle_t texture, gl::uint32_t image_level,                            gl::buffer_base_format_e buffer_base_format, gl::pixel_data_type_e pixel_data_type) -> std::vector<T>
    {
        const auto texture_level_width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        const auto texture_level_height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        const auto texture_level_depth  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, image_level);
        const auto pixel_count          = texture_level_width * texture_level_height * texture_level_depth;
        const auto pixel_component_size = gl::map_pixel_data_component_size(pixel_data_type);
        const auto pixel_size           = pixel_component_size * gl::map_buffer_base_format_component_count(buffer_base_format);
        const auto image_size           = pixel_count * pixel_size;
        if (image_size % sizeof(T) != gl::size_t{ 0u }) throw std::invalid_argument{ "type size is not an exact multiple of image size" };

              auto vector               = std::vector<T>(image_size / sizeof(T));
        ::glGetTextureImage(
            gl::to_underlying       (texture)           , 
            static_cast<gl::int32_t>(image_level)       , 
            gl::to_underlying       (buffer_base_format), gl::to_underlying(pixel_data_type), 
            static_cast<gl::sizei_t>(image_size)        , vector.data()                    );

        return vector;
    }
    template<typename T = gl::byte_t>
    auto get_texture_sub_image                            (gl::handle_t texture, gl::uint32_t image_level, gl::volume_t image_volume, gl::buffer_base_format_e buffer_base_format, gl::pixel_data_type_e pixel_data_type) -> std::vector<T>
    {
        const auto image_width          = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, image_level);
        const auto image_height         = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, image_level);
        const auto image_depth          = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, image_level);
        if (image_volume.origin.x + image_volume.extent.x > image_width ) throw std::invalid_argument{ "volume width exceeds texture width"  };
        if (image_volume.origin.y + image_volume.extent.y > image_height) throw std::invalid_argument{ "volume width exceeds texture height" };
        if (image_volume.origin.z                         > image_depth ) throw std::invalid_argument{ "volume width exceeds texture depth"  };

        const auto pixel_count          = image_volume.extent.x * image_volume.extent.y * image_volume.extent.z;
        const auto pixel_component_size = gl::map_pixel_data_component_size(pixel_data_type);
        const auto pixel_size           = pixel_component_size * gl::map_buffer_base_format_component_count(buffer_base_format);
        const auto image_size           = pixel_count * pixel_size;
        if (image_size % sizeof(T) != gl::size_t{ 0u }) throw std::invalid_argument{ "type size is not an exact multiple of image size" };

              auto vector               = std::vector<T>(image_size / sizeof(T));
        ::glGetTextureSubImage(
            gl::to_underlying       (texture)              , 
            static_cast<gl::int32_t>(image_level)          , 
            static_cast<gl::int32_t>(image_volume.origin.x), static_cast<gl::int32_t>(image_volume.origin.y), static_cast<gl::int32_t>(image_volume.origin.z), 
            static_cast<gl::sizei_t>(image_volume.extent.x), static_cast<gl::sizei_t>(image_volume.extent.y), static_cast<gl::sizei_t>(image_volume.extent.z), 
            gl::to_underlying       (buffer_base_format)   , gl::to_underlying       (pixel_data_type)      , 
            static_cast<gl::sizei_t>(image_size)           , vector.data()                                 );

        return vector;
    }
    template<typename T = gl::byte_t>
    auto get_compressed_texture_image                     (gl::handle_t texture, gl::uint32_t image_level) -> std::vector<T>
    {
        const auto compressed_image_size = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::compressed_image_size>(texture, image_level);
        if (compressed_image_size % sizeof(T) != gl::size_t{ 0u }) throw std::invalid_argument{ "type size is not an exact multiple of texture size" };

              auto vector                = std::vector<T>(compressed_image_size / sizeof(T));
        ::glGetCompressedTextureImage(
            gl::to_underlying       (texture)              , 
            static_cast<gl::int32_t>(image_level)          , 
            static_cast<gl::sizei_t>(compressed_image_size), vector.data());

        return vector;
    }
    template<typename T = gl::byte_t>
    auto get_compressed_texture_sub_image                 (gl::handle_t texture, gl::uint32_t image_level, gl::volume_t image_volume) -> std::vector<T>
    {
        const auto texture_level_width     = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width                >(texture, image_level);
        const auto texture_level_height    = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height               >(texture, image_level);
        const auto texture_level_depth     = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth                >(texture, image_level);
        if (image_volume.origin.x + image_volume.extent.x > texture_level_width ) throw std::invalid_argument{ "volume width exceeds texture width"  };
        if (image_volume.origin.y + image_volume.extent.y > texture_level_height) throw std::invalid_argument{ "volume width exceeds texture height" };
        if (image_volume.origin.z                         > texture_level_depth ) throw std::invalid_argument{ "volume width exceeds texture depth"  };
        
        const auto compressed_block_width  = gl::get_value<gl::data_e::pack_compressed_block_width >();
        const auto compressed_block_height = gl::get_value<gl::data_e::pack_compressed_block_height>();
        const auto compressed_block_depth  = gl::get_value<gl::data_e::pack_compressed_block_depth >();
        if ((image_volume.extent.x != texture_level_width  || image_volume.origin.x != 0u) && image_volume.origin.x % compressed_block_width  != gl::size_t{ 0u }) throw std::invalid_argument{ "volume width exceeds texture width"  };
        if ((image_volume.extent.y != texture_level_height || image_volume.origin.y != 0u) && image_volume.origin.y % compressed_block_height != gl::size_t{ 0u }) throw std::invalid_argument{ "volume width exceeds texture height" };
        if ((image_volume.extent.z != texture_level_width  || image_volume.origin.z != 0u) && image_volume.origin.z % compressed_block_depth  != gl::size_t{ 0u }) throw std::invalid_argument{ "volume width exceeds texture depth"  };

        const auto compressed_image_size   = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::compressed_image_size>(texture, image_level);
        if (compressed_image_size % sizeof(T) != gl::size_t{ 0u }               ) throw std::invalid_argument{ "type size is not an exact multiple of texture size" };

              auto vector               = std::vector<T>(compressed_image_size / sizeof(T));
        ::glGetCompressedTextureSubImage(
            gl::to_underlying       (texture)              , 
            static_cast<gl::int32_t>(image_level)          , 
            static_cast<gl::int32_t>(image_volume.origin.x), static_cast<gl::int32_t>(image_volume.origin.y), static_cast<gl::int32_t>(image_volume.origin.z), 
            static_cast<gl::sizei_t>(image_volume.extent.x), static_cast<gl::sizei_t>(image_volume.extent.y), static_cast<gl::sizei_t>(image_volume.extent.z), 
            static_cast<gl::sizei_t>(compressed_image_size), vector.data()                                 );

        return vector;
    }



    //Chapter 9 - FrameBuffer and FrameBuffer Objects
    template<gl::frame_buffer_parameter_e Parameter>
    auto get_frame_buffer_parameter_value                 (gl::handle_t frame_buffer) -> auto
    {
        auto get_frame_buffer_parameter_iv = [](gl::handle_t frame_buffer, gl::frame_buffer_parameter_e parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return ::glGetNamedFramebufferParameteriv(gl::to_underlying(frame_buffer), gl::to_underlying(parameter), &value), value;
            };

        using enum gl::frame_buffer_parameter_e;
        if constexpr (Parameter == default_width                     ) return static_cast<gl::uint32_t           >(get_frame_buffer_parameter_iv(frame_buffer, Parameter));
        if constexpr (Parameter == default_height                    ) return static_cast<gl::uint32_t           >(get_frame_buffer_parameter_iv(frame_buffer, Parameter));
        if constexpr (Parameter == default_layers                    ) return static_cast<gl::uint32_t           >(get_frame_buffer_parameter_iv(frame_buffer, Parameter));
        if constexpr (Parameter == default_samples                   ) return static_cast<gl::uint32_t           >(get_frame_buffer_parameter_iv(frame_buffer, Parameter));
        if constexpr (Parameter == has_default_fixed_sample_locations) return static_cast<gl::bool_t             >(get_frame_buffer_parameter_iv(frame_buffer, Parameter));

        if (frame_buffer == gl::default_frame_buffer) throw std::invalid_argument{ "parameter may not be queried on the default framebuffer" };

        if constexpr (Parameter == color_read_format                 ) return static_cast<gl::pixel_data_format_e>(get_frame_buffer_parameter_iv(frame_buffer, Parameter));
        if constexpr (Parameter == color_read_type                   ) return static_cast<gl::pixel_data_type_e  >(get_frame_buffer_parameter_iv(frame_buffer, Parameter));
        if constexpr (Parameter == is_double_buffered                ) return static_cast<gl::bool_t             >(get_frame_buffer_parameter_iv(frame_buffer, Parameter));
        if constexpr (Parameter == sample_buffers                    ) return static_cast<gl::uint32_t           >(get_frame_buffer_parameter_iv(frame_buffer, Parameter));
        if constexpr (Parameter == samples                           ) return static_cast<gl::uint32_t           >(get_frame_buffer_parameter_iv(frame_buffer, Parameter));
        if constexpr (Parameter == supports_stereo                   ) return static_cast<gl::bool_t             >(get_frame_buffer_parameter_iv(frame_buffer, Parameter));
    }
    template<gl::frame_buffer_attachment_parameter_e Parameter>
    auto get_frame_buffer_attachment_parameter_value      (gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment) -> auto
    {
        auto get_frame_buffer_attachment_parameter_iv = [](gl::handle_t frame_buffer, gl::frame_buffer_attachment_e attachment, gl::frame_buffer_attachment_parameter_e parameter)
            {
                auto value = gl::int32_t{};
                return ::glGetNamedFramebufferAttachmentParameteriv(gl::to_underlying(frame_buffer), gl::to_underlying(attachment), gl::to_underlying(parameter), &value), value;
            };

        using enum gl::frame_buffer_attachment_parameter_e;
        if constexpr (Parameter == alpha_size          ) return static_cast<gl::size_t                                  >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == blue_size           ) return static_cast<gl::size_t                                  >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == color_encoding      ) return static_cast<gl::color_encoding_e                        >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == component_type      ) return static_cast<gl::frame_buffer_attachment_component_type_e>(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == depth_size          ) return static_cast<gl::size_t                                  >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == green_size          ) return static_cast<gl::size_t                                  >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == is_layered          ) return static_cast<gl::bool_t                                  >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == object_name         ) return static_cast<gl::handle_t                                >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == object_type         ) return static_cast<gl::frame_buffer_attachment_object_type_e   >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == red_size            ) return static_cast<gl::size_t                                  >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == stencil_size        ) return static_cast<gl::size_t                                  >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == texture_cubemap_face) return static_cast<gl::cubemap_face_e                          >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == texture_layer       ) return static_cast<gl::uint32_t                                >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
        if constexpr (Parameter == texture_level       ) return static_cast<gl::uint32_t                                >(get_frame_buffer_attachment_parameter_iv(frame_buffer, attachment, Parameter));
    }
    template<gl::render_buffer_parameter_e Parameter>
    auto get_render_buffer_parameter_value                (gl::handle_t render_buffer) -> auto
    {
        auto get_render_buffer_parameter_iv = [](gl::handle_t render_buffer, gl::render_buffer_parameter_e parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return ::glGetNamedRenderbufferParameteriv(gl::to_underlying(render_buffer), gl::to_underlying(parameter), &value), value;
            };

        using enum gl::render_buffer_parameter_e;
        if constexpr (Parameter == width          ) return static_cast<gl::uint32_t             >(get_render_buffer_parameter_iv(render_buffer, Parameter));
        if constexpr (Parameter == height         ) return static_cast<gl::uint32_t             >(get_render_buffer_parameter_iv(render_buffer, Parameter));
        if constexpr (Parameter == internal_format) return static_cast<gl::frame_buffer_format_e>(get_render_buffer_parameter_iv(render_buffer, Parameter));
        if constexpr (Parameter == samples        ) return static_cast<gl::uint32_t             >(get_render_buffer_parameter_iv(render_buffer, Parameter));
        if constexpr (Parameter == red_size       ) return static_cast<gl::size_t               >(get_render_buffer_parameter_iv(render_buffer, Parameter));
        if constexpr (Parameter == green_size     ) return static_cast<gl::size_t               >(get_render_buffer_parameter_iv(render_buffer, Parameter));
        if constexpr (Parameter == blue_size      ) return static_cast<gl::size_t               >(get_render_buffer_parameter_iv(render_buffer, Parameter));
        if constexpr (Parameter == alpha_size     ) return static_cast<gl::size_t               >(get_render_buffer_parameter_iv(render_buffer, Parameter));
        if constexpr (Parameter == depth_size     ) return static_cast<gl::size_t               >(get_render_buffer_parameter_iv(render_buffer, Parameter));
        if constexpr (Parameter == stencil_size   ) return static_cast<gl::size_t               >(get_render_buffer_parameter_iv(render_buffer, Parameter));
    }



    //Chapter 10 - Vertex Specification and Drawing Commands
    template<gl::vertex_array_parameter_e     Parameter>
    auto get_vertex_array_indexed_value                   (gl::handle_t vertex_array) -> gl::handle_t
    {
        if constexpr (Parameter == gl::vertex_array_parameter_e::element_array_buffer_binding)
        {
            auto value = gl::int32_t{};
            return ::glGetVertexArrayiv(gl::to_underlying(vertex_array), gl::to_underlying(Parameter), &value), static_cast<gl::handle_t>(value);
        }
    }
    template<gl::vertex_array_parameter_e     Parameter>
    auto get_vertex_array_indexed_value                   (gl::handle_t vertex_array, gl::index_t index) -> auto
    {
              auto get_vertex_array_indexed32_iv = [](gl::handle_t vertex_array, gl::vertex_array_parameter_e parameter, gl::index_t index) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return ::glGetVertexArrayIndexediv(gl::to_underlying(vertex_array), index, gl::to_underlying(parameter), &value), value;
            };
              auto get_vertex_array_indexed64_iv = [](gl::handle_t vertex_array, gl::vertex_array_parameter_e parameter, gl::index_t index) -> gl::int64_t
            {
                auto value = gl::int64_t{};
                return ::glGetVertexArrayIndexed64iv(gl::to_underlying(vertex_array), index, gl::to_underlying(parameter), &value), value;
            };
        
        const auto maximum_vertex_attributes     = gl::get_value<gl::data_e::maximum_vertex_attributes>();
        if (index > maximum_vertex_attributes - gl::uint32_t{ 1u }) throw std::out_of_range{ "index out of range" };
        
        using enum gl::vertex_array_parameter_e;
        if constexpr (Parameter == binding_offset ) return static_cast<gl::ptrdiff_t                    >(get_vertex_array_indexed64_iv(vertex_array, Parameter, index));
        if constexpr (Parameter == divisor        ) return static_cast<gl::uint32_t                     >(get_vertex_array_indexed32_iv(vertex_array, Parameter, index));
        if constexpr (Parameter == is_enabled     ) return static_cast<gl::bool_t                       >(get_vertex_array_indexed32_iv(vertex_array, Parameter, index));
        if constexpr (Parameter == is_integer_data) return static_cast<gl::bool_t                       >(get_vertex_array_indexed32_iv(vertex_array, Parameter, index));
        if constexpr (Parameter == is_long_data   ) return static_cast<gl::bool_t                       >(get_vertex_array_indexed32_iv(vertex_array, Parameter, index));
        if constexpr (Parameter == is_normalized  ) return static_cast<gl::bool_t                       >(get_vertex_array_indexed32_iv(vertex_array, Parameter, index));
        if constexpr (Parameter == relative_offset) return static_cast<gl::ptrdiff_t                    >(get_vertex_array_indexed32_iv(vertex_array, Parameter, index));
        if constexpr (Parameter == size           ) return static_cast<gl::size_t                       >(get_vertex_array_indexed32_iv(vertex_array, Parameter, index));
        if constexpr (Parameter == stride         ) return static_cast<gl::size_t                       >(get_vertex_array_indexed32_iv(vertex_array, Parameter, index));
        if constexpr (Parameter == type           ) return static_cast<gl::vertex_array_attribute_type_e>(get_vertex_array_indexed32_iv(vertex_array, Parameter, index));
    }



    //Chapter 20 - Debug Output
    auto get_debug_message_log                            (gl::count_t count) -> std::vector<gl::message_log>
    {
        auto get_debug_message_log_ = [](gl::count_t count, std::span<gl::debug_source_e> sources, std::span<gl::debug_type_e> types, std::span<gl::uint32_t> ids, std::span<gl::debug_severity_e> severities, std::span<gl::sizei_t> lengths, std::string& message_log) -> gl::uint32_t
            {
                const auto maximum_debug_message_length = gl::get_value<gl::data_e::maximum_debug_message_length>();
                const auto message_log_length           = count * maximum_debug_message_length;
                message_log                             = std::string(message_log_length, '\0');

                return ::glGetDebugMessageLog(
                    static_cast<gl::uint32_t>(count)             , static_cast<gl::sizei_t> (message_log_length) , 
                    gl::to_underlying_pointer(sources    .data()), gl::to_underlying_pointer(types      .data()), 
                                              ids        .data() , gl::to_underlying_pointer(severities .data()), 
                                              lengths    .data() ,                           message_log.data());
            };
        
              auto sources      = std::vector<gl::debug_source_e  >(count);
              auto types        = std::vector<gl::debug_type_e    >(count);
              auto ids          = std::vector<gl::uint32_t        >(count);
              auto severities   = std::vector<gl::debug_severity_e>(count);
              auto lengths      = std::vector<gl::sizei_t         >(count);
              auto message_log  = std::string{};

        const auto message_log_count = get_debug_message_log_(count, sources, types, ids, severities, lengths, message_log);
              auto message_logs      = std::vector<gl::message_log>(message_log_count);

        if (!message_logs.empty())
        {
            for (auto offset = gl::ptrdiff_t{ 0 }; const auto index : std::views::iota(0u, message_log_count))
            {
                const auto length = lengths.at(index);
                      auto log    = std::string{ message_log.data() + offset, static_cast<gl::size_t>(length) - 1u };

                message_logs.at(index) = gl::message_log
                {
                    .id       = ids       .at(index), 
                    .message  = std::move(log)      , 
                    .source   = sources   .at(index), 
                    .type     = types     .at(index), 
                    .severity = severities.at(index), 
                };

                offset += length;
            }
        }

        return message_logs;
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
        return ::glCreateQueries(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle)), handle;
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
        return ::glCreateBuffers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle)), handle;
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
        ::glBindBufferBase(gl::to_underlying(base_target), gl::to_underlying(binding), gl::to_underlying(buffer));
    }
    void bind_buffers_base                                (std::span<const gl::handle_t> buffers, gl::buffer_base_target_e target, gl::binding_t start_binding)
    {
        ::glBindBuffersBase(gl::to_underlying(target), gl::to_underlying(start_binding), static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_pointer(buffers.data()));
    }
    template<typename T = gl::byte_t>
    void bind_buffer_range                                (gl::handle_t                  buffer , gl::buffer_base_target_e base_target, gl::binding_t binding, gl::range_t                  range )
    {
        const auto buffer_size  = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto byte_range   = gl::convert_range<T>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        ::glBindBufferRange(
            gl::to_underlying         (base_target)      , gl::to_underlying      (binding)         , gl::to_underlying(buffer),
            static_cast<gl::ptrdiff_t>(byte_range.offset), static_cast<gl::size_t>(byte_range.size));
    }
    template<typename T = gl::byte_t>
    void bind_buffers_range                               (std::span<const gl::handle_t> buffers, gl::buffer_base_target_e base_target, gl::binding_t binding, std::span<const gl::range_t> ranges)
    {
        const auto sizes   = std::vector<gl::size_t   >(ranges.size());
        const auto offsets = std::vector<gl::ptrdiff_t>(ranges.size());
        for (std::tuple<gl::handle_t&, gl::range_t&> value : std::views::zip(buffers, ranges))
        {
            const auto buffer_size  = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(std::get<0u>(value));
            const auto byte_range   = gl::convert_range<T>(std::get<1u>(value));
            if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

            sizes  .emplace_back(byte_range.size  );
            offsets.emplace_back(byte_range.offset);
        }

        ::glBindBuffersRange(gl::to_underlying(base_target), gl::to_underlying(binding), static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_pointer(buffers.data()), offsets.data(), sizes.data());
    }
    template<typename T = gl::byte_t>
    void buffer_storage                                   (gl::handle_t buffer, gl::buffer_storage_flags_e flags, gl::count_t element_count)
    {
        ::glNamedBufferStorage(gl::to_underlying(buffer), static_cast<gl::size_t>(element_count * sizeof(T)), nullptr, gl::to_underlying(flags));
    }
    template<typename T = gl::byte_t>
    void buffer_storage                                   (gl::handle_t buffer, gl::buffer_storage_flags_e flags, std::span<const T> memory)
    {
        ::glNamedBufferStorage(gl::to_underlying(buffer), static_cast<gl::size_t>(memory.size_bytes()), memory.data(), gl::to_underlying(flags));
    }
    template<typename T = gl::byte_t>
    void buffer_sub_data                                  (gl::handle_t buffer, gl::index_t index, std::span<const T> memory)
    {
        const auto buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto byte_range  = gl::convert_range<T>(gl::range_t{ memory.size(), index });
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        ::glNamedBufferSubData(gl::to_underlying(buffer), static_cast<gl::ptrdiff_t>(byte_range.offset), static_cast<gl::sizei_t>(byte_range.size), memory.data());
    }
    template<typename T = gl::byte_t>
    void clear_buffer_data                                (gl::handle_t buffer, gl::buffer_base_format_e base_format, gl::buffer_format_e format, gl::data_type_e data_type,                    T value)
    {
        const auto base_format_components = gl::map_buffer_base_format_components(base_format);
        const auto data_type_size         = gl::map_data_type_size               (data_type  );
        if (base_format_components * data_type_size > sizeof(T)) throw std::invalid_argument{ "base format and type do not match clear value" };

        ::glClearNamedBufferData(gl::to_underlying(buffer), gl::to_underlying(format), gl::to_underlying(base_format), gl::to_underlying(data_type), &value);
    }
    template<typename T = gl::byte_t>
    void clear_buffer_sub_data                            (gl::handle_t buffer, gl::buffer_base_format_e base_format, gl::buffer_format_e format, gl::data_type_e data_type, gl::range_t range, T value)
    {
        const auto buffer_size            = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto byte_range             = gl::convert_range<T>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        const auto base_format_components = gl::map_buffer_base_format_components(base_format);
        const auto data_type_size         = gl::map_data_type_size               (data_type  );
        if (base_format_components * data_type_size > sizeof(T)) throw std::invalid_argument{ "base format and type do not match clear value" };

        ::glClearNamedBufferSubData(
            gl::to_underlying         (buffer)           , gl::to_underlying       (format)         , 
            static_cast<gl::ptrdiff_t>(byte_range.offset), static_cast<gl::sizei_t>(byte_range.size), 
            gl::to_underlying         (base_format)      , gl::to_underlying       (data_type)      , 
            &value                                      );
    }
    template<typename T = gl::byte_t>
    auto map_buffer                                       (gl::handle_t buffer, gl::buffer_mapping_access_flags_e             access_flags                   ) -> std::span<T>
    {
        const auto  buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        if (buffer_size % sizeof(T) != gl::size_t{ 0u }) throw std::invalid_argument{ "buffer size is not an exact multiple of type size" };
        
              auto* pointer     = reinterpret_cast<T*>(::glMapNamedBufferRange(gl::to_underlying(buffer), gl::ptrdiff_t{ 0 }, static_cast<gl::sizei_t>(buffer_size), gl::to_underlying(access_flags)));
        if (!pointer) throw std::runtime_error{ "failed to map buffer" };
        
        return std::span{ pointer, buffer_size / sizeof(T) };
    }
    template<typename T = gl::byte_t>
    auto map_buffer_range                                 (gl::handle_t buffer, gl::buffer_mapping_range_access_flags_e range_access_flags, gl::range_t range) -> std::span<T>
    {
        const auto  buffer_size  = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto  byte_range   = gl::convert_range<T>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };
        
              auto* pointer      = reinterpret_cast<T*>(::glMapNamedBufferRange(gl::to_underlying(buffer), static_cast<gl::ptrdiff_t>(byte_range.offset), static_cast<gl::sizei_t>(byte_range.size), gl::to_underlying(range_access_flags)));
        if (!pointer) throw std::runtime_error{ "failed to map buffer" };

        return std::span{ pointer, byte_range.size / sizeof(T) };
    }
    template<typename T = gl::byte_t>
    void flush_buffer_range                               (gl::handle_t buffer, gl::range_t range)
    {
        const auto buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto byte_range  = gl::convert_range<T>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        ::glFlushMappedNamedBufferRange(gl::to_underlying(buffer), static_cast<gl::ptrdiff_t>(byte_range.offset), static_cast<gl::sizei_t>(byte_range.size));
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
        const auto buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(buffer);
        const auto byte_range  = gl::convert_range<T>(range);
        if (byte_range.offset + byte_range.size > buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        ::glInvalidateBufferSubData(gl::to_underlying(buffer), static_cast<gl::ptrdiff_t>(byte_range.offset), static_cast<gl::size_t>(byte_range.size));
    }
    template<typename T = gl::byte_t>
    void copy_buffer_sub_data                             (gl::handle_t source_buffer, gl::handle_t destination_buffer, gl::range_t source_range, gl::index_t destination_offset)
    {
        const auto source_buffer_size      = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(source_buffer     );
        const auto destination_buffer_size = gl::get_buffer_parameter_value<gl::buffer_parameter_e::size>(destination_buffer);
        const auto source_byte_range       = gl::convert_range<T>(source_range);
        if (source_byte_range.offset + source_byte_range.size > source_buffer_size     ) throw std::invalid_argument{ "range exceeds buffer bounds" };
        if (source_byte_range.offset + source_byte_range.size > destination_buffer_size) throw std::invalid_argument{ "range exceeds buffer bounds" };

        ::glCopyNamedBufferSubData(
            gl::to_underlying         (source_buffer)           , gl::to_underlying         (destination_buffer), 
            static_cast<gl::ptrdiff_t>(source_byte_range.offset), static_cast<gl::ptrdiff_t>(destination_offset), 
            static_cast<gl::size_t   >(source_byte_range.size ));
    }
    


    //Chapter 7 - Programs and Shaders
    auto create_shader                                    (gl::shader_type_e type) -> gl::handle_t
    {
        return static_cast<gl::handle_t>(::glCreateShader(gl::to_underlying(type)));
    }
    void shader_source                                    (gl::handle_t shader, const std::string& source)
    {
        const auto* c_string = source.c_str();
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
    void shader_binary                                    (gl::handle_t                  shader , gl::shader_binary_format_e binary_format, std::span<const gl::byte_t> binary)
    {
        ::glShaderBinary(
            gl::sizei_t{ 1 }                  , 
            gl::to_underlying_pointer(&shader), gl::to_underlying       (binary_format)       , 
            binary.data()                     , static_cast<gl::sizei_t>(binary.size_bytes()));
    }
    void shader_binaries                                  (std::span<const gl::handle_t> shaders, gl::enum_t                        format, std::span<const gl::byte_t> binary)
    {
        ::glShaderBinary(static_cast<gl::sizei_t>(shaders.size()), gl::to_underlying_pointer(shaders.data()), format, binary.data(), static_cast<gl::sizei_t>(binary.size_bytes()));
    }
    template<gl::count_t Count = 0u>
    void specialize_shader                                (gl::handle_t shader, const std::string& entry_point, std::span<const gl::uint32_t, Count> indices = {}, std::span<const gl::uint32_t, Count> values = {})
    {
        const auto* c_string = entry_point.c_str();
        ::glSpecializeShader(gl::to_underlying(shader), c_string, Count, indices.data(), values.data());
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
    auto create_shader_program                            (gl::shader_type_e type, const std::string& source) -> gl::handle_t
    {
        const auto* c_string = source.c_str();
        return static_cast<gl::handle_t>(::glCreateShaderProgramv(gl::to_underlying(type), gl::sizei_t{ 1 }, &c_string));
    }
    auto create_pipeline                                  () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return ::glCreateProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle)), handle;
    }
    auto create_pipelines                                 (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return ::glCreateProgramPipelines(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data())), handles;
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
    void use_program_stages                               (gl::handle_t pipeline, gl::handle_t program, gl::program_stage_e program_stages)
    {
        ::glUseProgramStages(gl::to_underlying(pipeline), gl::to_underlying(program_stages), gl::to_underlying(program));
    }
    auto get_program_binary                               (gl::handle_t program) -> gl::binary_info
    {
        const auto binary_length = gl::get_program_value<gl::program_parameter_e::binary_length>(program);
              auto binary_info   = gl::binary_info{};
        return ::glGetProgramBinary(gl::to_underlying(program), static_cast<gl::sizei_t>(binary_length), nullptr, &binary_info.format, binary_info.binary.data()), binary_info;
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
        return ::glCreateTextures(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle)), handle;
    }
    auto create_textures                                  (gl::texture_target_e target, gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return ::glCreateTextures(gl::to_underlying(target), static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data())), handles;
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
        ::glBindTextureUnit(gl::to_underlying(binding), gl::to_underlying(texture));
    }
    auto create_sampler                                   () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return ::glCreateSamplers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle)), handle;
    }
    auto create_samplers                                  (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return ::glCreateSamplers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data())), handles;
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
        ::glBindSampler(gl::to_underlying(binding), gl::to_underlying(sampler));
    }
    void bind_samplers                                    (std::span<const gl::handle_t> samplers, gl::range_t range)
    {
        ::glBindSamplers(static_cast<gl::uint32_t>(range.index), static_cast<gl::sizei_t>(range.count), gl::to_underlying_pointer(samplers.data()));
    }
    template<gl::sampler_parameter_e P>
    auto sampler_parameter                                (gl::handle_t sampler, gl::sampler_parameter_argument_t<P> value) -> auto
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

             if constexpr (P == border_color        ) 
        {
            auto overload = gl::overload_t
            {
                [=](gl::vector_4i vector) { ::glSamplerParameterIiv (gl::to_underlying(sampler), gl::to_underlying(P), gl::value_pointer(vector)); },
                [=](gl::vector_4u vector) { ::glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(P), gl::value_pointer(vector)); },
                [=](gl::vector_4f vector) { ::glSamplerParameterfv  (gl::to_underlying(sampler), gl::to_underlying(P), gl::value_pointer(vector)); },
            };

            std::visit(overload, value);
        }
        else if constexpr (P == compare_function    ) sampler_parameter_uiv(sampler, P, gl::to_underlying(value));
        else if constexpr (P == compare_mode        ) sampler_parameter_uiv(sampler, P, gl::to_underlying(value));
        else if constexpr (P == lod_bias            ) sampler_parameter_fv (sampler, P,                   value );
        else if constexpr (P == magnification_filter) sampler_parameter_uiv(sampler, P, gl::to_underlying(value));
        else if constexpr (P == maximum_anisotropy  ) sampler_parameter_fv (sampler, P,                   value );
        else if constexpr (P == maximum_lod         ) sampler_parameter_fv (sampler, P,                   value );
        else if constexpr (P == minification_filter ) sampler_parameter_uiv(sampler, P, gl::to_underlying(value));
        else if constexpr (P == minimum_lod         ) sampler_parameter_fv (sampler, P,                   value );
        else if constexpr (P == wrapping_r          ) sampler_parameter_uiv(sampler, P, gl::to_underlying(value));
        else if constexpr (P == wrapping_s          ) sampler_parameter_uiv(sampler, P, gl::to_underlying(value));
        else if constexpr (P == wrapping_t          ) sampler_parameter_uiv(sampler, P, gl::to_underlying(value));
    }
    template<gl::packing_mode_e P>
    void pixel_store                                      (gl::int32_t parameter)
    {
        ::glPixelStorei(gl::to_underlying(P), parameter);
    }
    void texture_sub_image_1d                             (gl::handle_t texture, gl::texture_base_format_e base_format, gl::pixel_data_type_e pixel_data_type, gl::uint32_t level, gl::length_t region, std::span<const gl::byte_t> source)
    {
        const auto width = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, level);
        if (region.origin.x + region.extent.x > width ) throw std::invalid_argument{ "invalid region width" };

        ::glTextureSubImage1D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::sizei_t>(region.extent.x), 
            gl::to_underlying       (base_format)    , gl::to_underlying       (pixel_data_type), 
            source.data()                           );
    }
    void texture_sub_image_2d                             (gl::handle_t texture, gl::texture_base_format_e base_format, gl::pixel_data_type_e pixel_data_type, gl::uint32_t level, gl::area_t   region, std::span<const gl::byte_t> source)
    {
        const auto width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, level);
        const auto height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, level);
        if (region.origin.x + region.extent.x > width ) throw std::invalid_argument{ "invalid region width"  };
        if (region.origin.y + region.extent.y > height) throw std::invalid_argument{ "invalid region height" };

        ::glTextureSubImage2D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), 
            gl::to_underlying       (base_format)    , gl::to_underlying       (pixel_data_type), 
            source.data()                           );
    }
    void texture_sub_image_3d                             (gl::handle_t texture, gl::texture_base_format_e base_format, gl::pixel_data_type_e pixel_data_type, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> source)
    {
        const auto width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, level);
        const auto height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, level);
        const auto depth  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, level);
        if (region.origin.x + region.extent.x > width ) throw std::invalid_argument{ "invalid region width"  };
        if (region.origin.y + region.extent.y > height) throw std::invalid_argument{ "invalid region height" };
        if (region.origin.z + region.extent.z > depth ) throw std::invalid_argument{ "invalid region depth"  };

        ::glTextureSubImage3D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying       (base_format)    , gl::to_underlying       (pixel_data_type), 
            source.data()                           );
    }
    void copy_texture_sub_image_1d                        (gl::handle_t texture, gl::uint32_t level, gl::length_t region, const gl::vector_2u& coordinates)
    {
        const auto width = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, level);
        if (region.origin.x + region.extent.x > width) throw std::invalid_argument{ "invalid region width"  };
        
        ::glCopyTextureSubImage1D(
            gl::to_underlying       (texture)         , static_cast<gl::int32_t>(level)        , 
            static_cast<gl::int32_t>(region.origin.x) , 
            static_cast<gl::int32_t>(coordinates  .x) , static_cast<gl::int32_t>(coordinates.y), 
            static_cast<gl::sizei_t>(region.extent.x));
    }
    void copy_texture_sub_image_2d                        (gl::handle_t texture, gl::uint32_t level, gl::area_t   region, const gl::vector_2u& coordinates)
    {
        const auto width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, level);
        const auto height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, level);
        if (region.origin.x + region.extent.x > width ) throw std::invalid_argument{ "invalid region width"  };
        if (region.origin.y + region.extent.y > height) throw std::invalid_argument{ "invalid region height" };

        ::glCopyTextureSubImage2D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)           , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y) , 
            static_cast<gl::int32_t>(coordinates  .x), static_cast<gl::int32_t>(coordinates  .y) , 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    void copy_texture_sub_image_3d                        (gl::handle_t texture, gl::uint32_t level, gl::volume_t region, const gl::vector_2u& coordinates)
    {
        const auto width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, level);
        const auto height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, level);
        const auto depth  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, level);
        if (region.origin.x + region.extent.x > width ) throw std::invalid_argument{ "invalid region width"  };
        if (region.origin.y + region.extent.y > height) throw std::invalid_argument{ "invalid region height" };
        if (region.origin.z + region.extent.z > depth ) throw std::invalid_argument{ "invalid region depth"  };

        ::glCopyTextureSubImage3D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)           , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y) , static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::int32_t>(coordinates  .x), static_cast<gl::int32_t>(coordinates  .y) , 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    void compressed_texture_sub_image_1d                  (gl::handle_t texture, gl::texture_compressed_base_format_e format, gl::uint32_t level, gl::length_t region, std::span<const gl::byte_t> source)
    {
        const auto width = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, level);
        if (region.origin.x + region.extent.x > width) throw std::invalid_argument{ "invalid region width" };

        ::glCompressedTextureSubImage1D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::sizei_t>(region.extent.x), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(source.size())  , source.data()                             );
    }
    void compressed_texture_sub_image_2d                  (gl::handle_t texture, gl::texture_compressed_base_format_e format, gl::uint32_t level, gl::area_t   region, std::span<const gl::byte_t> source)
    {
        const auto width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, level);
        const auto height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, level);
        if (region.origin.x + region.extent.x > width ) throw std::invalid_argument{ "invalid region width"  };
        if (region.origin.y + region.extent.y > height) throw std::invalid_argument{ "invalid region height" };

        ::glCompressedTextureSubImage2D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(source.size())  , source.data()                             );
    }
    void compressed_texture_sub_image_3d                  (gl::handle_t texture, gl::texture_compressed_base_format_e format, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> source)
    {
        const auto width  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::width >(texture, level);
        const auto height = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::height>(texture, level);
        const auto depth  = gl::get_texture_level_parameter_value<gl::texture_level_parameter_e::depth >(texture, level);
        if (region.origin.x + region.extent.x > width ) throw std::invalid_argument{ "invalid region width"  };
        if (region.origin.y + region.extent.y > height) throw std::invalid_argument{ "invalid region height" };
        if (region.origin.z + region.extent.z > depth ) throw std::invalid_argument{ "invalid region depth"  };
        
        ::glCompressedTextureSubImage3D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(source.size())  , source.data()                             );
    }
    void texture_buffer                                   (gl::handle_t texture, gl::handle_t buffer, gl::buffer_format_e format)
    {
        ::glTextureBuffer(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer));
    }
    template<typename T>
    void texture_buffer_range                             (gl::handle_t texture, gl::handle_t buffer, gl::buffer_format_e format, gl::range_t range)
    {
        const auto byte_range = gl::convert_range<T>(range);
        ::glTextureBufferRange(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer), static_cast<gl::ptrdiff_t>(byte_range.offset), static_cast<gl::sizei_t>(byte_range.size));
    }
    template<gl::texture_parameter_e P>
    void texture_parameter                                (gl::handle_t texture, gl::texture_parameter_argument_t<P> value)
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

             if constexpr (P == base_level          ) texture_parameter_uiv(texture, P,                   value );
        else if constexpr (P == border_color        )
             {
                auto overload = gl::overload_t
                {
                    [=](gl::vector_4i vector) { ::glTextureParameterIiv (gl::to_underlying(texture), gl::to_underlying(P), gl::value_pointer(vector)); },
                    [=](gl::vector_4u vector) { ::glTextureParameterIuiv(gl::to_underlying(texture), gl::to_underlying(P), gl::value_pointer(vector)); },
                    [=](gl::vector_4f vector) { ::glTextureParameterfv  (gl::to_underlying(texture), gl::to_underlying(P), gl::value_pointer(vector)); },
                };

                std::visit(overload, value);
             }
        else if constexpr (P == compare_function    ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == compare_mode        ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == depth_stencil_mode  ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == lod_bias            ) texture_parameter_fv (texture, P,                   value );
        else if constexpr (P == magnification_filter) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == maximum_anisotropy  ) texture_parameter_fv (texture, P,                   value );
        else if constexpr (P == maximum_level       ) texture_parameter_uiv(texture, P,                   value );
        else if constexpr (P == maximum_lod         ) texture_parameter_fv (texture, P,                   value );
        else if constexpr (P == minification_filter ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == minimum_lod         ) texture_parameter_fv (texture, P,                   value );
        else if constexpr (P == swizzle_a           ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == swizzle_b           ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == swizzle_g           ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == swizzle_r           ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == swizzle_rgba        ) set_swizzle_rgba     (texture, P, gl::to_underlying(value));
        else if constexpr (P == target              ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == wrapping_r          ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == wrapping_s          ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
        else if constexpr (P == wrapping_t          ) texture_parameter_uiv(texture, P, gl::to_underlying(value));
    }
    void generate_texture_mipmaps                         (gl::handle_t texture)
    {
        ::glGenerateTextureMipmap(gl::to_underlying(texture));
    }
    template<gl::texture_target_e T, gl::texture_target_e U> requires (meta::is_valid_texture_view<T, U>())
    void texture_view                                     (gl::handle_t source, gl::handle_t destination, gl::texture_format_e format, gl::uint32_t minimum_level, gl::uint32_t levels, gl::uint32_t minimum_layer, gl::uint32_t layers)
    {
        ::glTextureView(gl::to_underlying(destination), gl::to_underlying(U), gl::to_underlying(source), gl::to_underlying(format), minimum_level, levels, minimum_layer, layers);
    }
    void texture_storage_1d                               (gl::handle_t texture, gl::texture_format_e format, const gl::vector_1u& dimensions, gl::uint32_t levels)
    {
        ::glTextureStorage1D(
            gl::to_underlying       (texture)      , static_cast<gl::sizei_t>(levels), gl::to_underlying(format), 
            static_cast<gl::sizei_t>(dimensions.x));
    }
    void texture_storage_2d                               (gl::handle_t texture, gl::texture_format_e format, const gl::vector_2u& dimensions, gl::uint32_t levels)
    {
        ::glTextureStorage2D(
            gl::to_underlying       (texture)     , static_cast<gl::sizei_t>(levels)       , gl::to_underlying(format), 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    void texture_storage_3d                               (gl::handle_t texture, gl::texture_format_e format, const gl::vector_3u& dimensions, gl::uint32_t levels)
    {
        ::glTextureStorage3D(
            gl::to_underlying       (texture)     , static_cast<gl::sizei_t>(levels)      , gl::to_underlying       (format)       , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z));
    }
    void texture_storage_2d_multisample                   (gl::handle_t texture, gl::texture_format_e format, const gl::vector_2u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::true_)
    {
        ::glTextureStorage2DMultisample(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(samples)     , gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), fixed);
    }
    void texture_storage_3d_multisample                   (gl::handle_t texture, gl::texture_format_e format, const gl::vector_3u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::true_)
    {
        ::glTextureStorage3DMultisample(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(samples)     , gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z), fixed);
    }
    void invalidate_texture_image                         (gl::handle_t texture, gl::uint32_t level)
    {
        ::glInvalidateTexImage(gl::to_underlying(texture), static_cast<gl::int32_t>(level));
    }
    void invalidate_texture_sub_image                     (gl::handle_t texture, gl::uint32_t level, gl::volume_t region)
    {
        ::glInvalidateTexSubImage(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z) , 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z));
    }
    void clear_texture_image                              (gl::handle_t texture, gl::texture_base_format_e format, gl::texture_type_e type, gl::uint32_t level, std::span<const gl::byte_t> source)
    {
        ::glClearTexImage(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level), 
            gl::to_underlying(format) , gl::to_underlying       (type) , source.data());
    }
    void clear_texture_sub_image                          (gl::handle_t texture, gl::texture_base_format_e format, gl::texture_type_e type, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> source)
    {
        ::glClearTexSubImage(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying       (format)         , gl::to_underlying       (type)           , source.data()                           );
    }
    void bind_image_texture                               (gl::handle_t texture, gl::uint32_t level, gl::bool_t is_layered, gl::uint32_t layer, gl::index_t image_unit, gl::image_format_e image_format, gl::image_access_e image_access)
    {
        ::glBindImageTexture(
            static_cast<gl::uint32_t>(image_unit), gl::to_underlying(texture), 
            static_cast<gl::int32_t> (level)     , is_layered, 
            static_cast<gl::int32_t> (layer)     , gl::to_underlying(image_access), gl::to_underlying(image_format));
    }
    void bind_image_textures                              (std::span<const gl::handle_t> textures, gl::range_t range)
    {
        ::glBindImageTextures(static_cast<gl::uint32_t>(range.index), static_cast<gl::sizei_t>(range.count), gl::to_underlying_pointer(textures.data()));
    }



    //Chapter 9 - FrameBuffers and FrameBuffer Objects
    auto create_frame_buffer                              () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return ::glCreateFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle)), handle;
    }
    auto create_frame_buffer                              (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return ::glCreateFramebuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data())), handles;
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
    template<gl::frame_buffer_parameter_e P>
    void frame_buffer_parameter                           (gl::handle_t frame_buffer, gl::uint32_t value)
    {
        auto frame_buffer_parameter_i = [](gl::handle_t frame_buffer, gl::frame_buffer_parameter_e parameter, gl::uint32_t value)
            {
                ::glNamedFramebufferParameteri(gl::to_underlying(frame_buffer), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
            };

        if constexpr (
               P == gl::frame_buffer_parameter_e::default_width               
            || P == gl::frame_buffer_parameter_e::default_height
            || P == gl::frame_buffer_parameter_e::default_layers
            || P == gl::frame_buffer_parameter_e::default_samples
            || P == gl::frame_buffer_parameter_e::has_default_fixed_sample_locations
            || P == gl::frame_buffer_parameter_e::default_width                     ) frame_buffer_parameter_i(frame_buffer, P, value);
        else static_assert(gl::false_, "invalid frame buffer parameter");
    }
    auto create_render_buffer                             () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return ::glCreateRenderbuffers(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle)), handle;
    }
    auto create_render_buffers                            (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return ::glCreateRenderbuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data())), handles;
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
    void frame_buffer_texture                             (gl::handle_t frame_buffer, gl::handle_t texture      , gl::frame_buffer_attachment_e attachment, gl::uint32_t level)
    {
        ::glNamedFramebufferTexture(
            gl::to_underlying(frame_buffer) , gl::to_underlying(attachment), gl::to_underlying(texture), 
            static_cast<gl::int32_t>(level));
    }
    void frame_buffer_texture_layer                       (gl::handle_t frame_buffer, gl::handle_t texture      , gl::frame_buffer_attachment_e attachment, gl::uint32_t level, gl::uint32_t layer)
    {
        ::glNamedFramebufferTextureLayer(
            gl::to_underlying       (frame_buffer), gl::to_underlying       (attachment), gl::to_underlying(texture), 
            static_cast<gl::int32_t>(level)       , static_cast<gl::int32_t>(layer)    );
    }
    void texture_barrier                                  ()
    {
        ::glTextureBarrier();
    }
    auto check_frame_buffer_status                        (gl::handle_t frame_buffer) -> gl::frame_buffer_status_e
    {
        return static_cast<gl::frame_buffer_status_e>(::glCheckNamedFramebufferStatus(gl::to_underlying(frame_buffer), gl::to_underlying(gl::frame_buffer_target_e::write)));
    }



    //Chapter 10 - Vertex Specification and Drawing Commands
    template<gl::patch_parameter_e P>
    void patch_parameter                                  (gl::patch_parameter_argument_t<P> value)
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

        if constexpr (P == patch_default_inner_level) ::glPatchParameterfv(gl::to_underlying(gl::patch_parameter_e::patch_default_inner_level), value.data());
        if constexpr (P == patch_default_outer_level) ::glPatchParameterfv(gl::to_underlying(gl::patch_parameter_e::patch_default_outer_level), value.data());
        if constexpr (P == patch_vertices           ) patch_parameter_i (                    gl::patch_parameter_e::patch_vertices            , value       );
    }
    template<typename T, gl::uint32_t Count, gl::bool_t Normalized = gl::false_>
    void specify_vertex_attribute                         (gl::index_t index, const gl::vector_t<T, Count>& value)
    {
        const auto maximum_vertex_attributes = gl::get_value<gl::data_e::maximum_vertex_attributes>();
        if (index > maximum_vertex_attributes) throw std::invalid_argument{ "index exceeds vertex attribute limit" };
        
             if constexpr (std::is_same_v<T, gl::uint8_t  >)
        {
            if constexpr (Count == 4 && Normalized == gl::true_ ) ::glVertexAttrib4Nub(index, value.x, value.y, value.z, value.w);
        }
        else if constexpr (std::is_same_v<T, gl::int16_t  >)
        {
            if constexpr (Count == 1 && Normalized == gl::false_) ::glVertexAttrib1s  (index, value.x                           );
            if constexpr (Count == 2 && Normalized == gl::false_) ::glVertexAttrib2s  (index, value.x, value.y                  );
            if constexpr (Count == 3 && Normalized == gl::false_) ::glVertexAttrib3s  (index, value.x, value.y, value.z         );
            if constexpr (Count == 4 && Normalized == gl::false_) ::glVertexAttrib4s  (index, value.x, value.y, value.z, value.w);
        }
        else if constexpr (std::is_same_v<T, gl::int32_t  >)
        {
            if constexpr (Count == 1 && Normalized == gl::false_) ::glVertexAttribI1i (index, value.x                           );
            if constexpr (Count == 2 && Normalized == gl::false_) ::glVertexAttribI2i (index, value.x, value.y                  );
            if constexpr (Count == 3 && Normalized == gl::false_) ::glVertexAttribI3i (index, value.x, value.y, value.z         );
            if constexpr (Count == 4 && Normalized == gl::false_) ::glVertexAttribI4i (index, value.x, value.y, value.z, value.w);
        }
        else if constexpr (std::is_same_v<T, gl::uint32_t >)
        {
            if constexpr (Count == 1 && Normalized == gl::false_) ::glVertexAttribI1ui(index, value.x                           );
            if constexpr (Count == 2 && Normalized == gl::false_) ::glVertexAttribI2ui(index, value.x, value.y                  );
            if constexpr (Count == 3 && Normalized == gl::false_) ::glVertexAttribI3ui(index, value.x, value.y, value.z         );
            if constexpr (Count == 4 && Normalized == gl::false_) ::glVertexAttribI4ui(index, value.x, value.y, value.z, value.w);
        }
        else if constexpr (std::is_same_v<T, gl::float32_t>)
        {
            if constexpr (Count == 1 && Normalized == gl::false_) ::glVertexAttrib1f  (index, value.x                           );
            if constexpr (Count == 2 && Normalized == gl::false_) ::glVertexAttrib2f  (index, value.x, value.y                  );
            if constexpr (Count == 3 && Normalized == gl::false_) ::glVertexAttrib3f  (index, value.x, value.y, value.z         );
            if constexpr (Count == 4 && Normalized == gl::false_) ::glVertexAttrib4f  (index, value.x, value.y, value.z, value.w);
        }
        else if constexpr (std::is_same_v<T, gl::float64_t>)
        {
            if constexpr (Count == 1 && Normalized == gl::false_) ::glVertexAttribL1d (index, value.x                           );
            if constexpr (Count == 2 && Normalized == gl::false_) ::glVertexAttribL2d (index, value.x, value.y                  );
            if constexpr (Count == 3 && Normalized == gl::false_) ::glVertexAttribL3d (index, value.x, value.y, value.z         );
            if constexpr (Count == 4 && Normalized == gl::false_) ::glVertexAttribL4d (index, value.x, value.y, value.z, value.w);
        }
        else              static_assert(gl::false_ && sizeof(T), "parameters do not match a valid vertex attribute function");
    }
    auto create_vertex_array                              () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return ::glCreateVertexArrays(gl::sizei_t{ 1 }, gl::to_underlying_pointer(&handle)), handle;
    }
    auto create_vertex_arrays                             (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return ::glCreateVertexArrays(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_pointer(handles.data())), handles;
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
    void vertex_array_attribute_format                    (gl::handle_t vertex_array, gl::index_t attribute, gl::ptrdiff_t offset, gl::vertex_array_attribute_type_e type, gl::count_t count, gl::bool_t is_normalized = gl::false_)
    {
        auto vertex_array_attribute_format_i = [](gl::handle_t vertex_array, gl::index_t attribute, gl::vertex_array_attribute_type_e type, gl::count_t count, gl::ptrdiff_t offset                       ) -> gl::void_t
            {
                ::glVertexArrayAttribIFormat(
                    gl::to_underlying        (vertex_array), 
                    static_cast<gl::uint32_t>(attribute)   , static_cast<gl::int32_t >(count)  , 
                    gl::to_underlying        (type)        , static_cast<gl::uint32_t>(offset));
            };
        auto vertex_array_attribute_format_f = [](gl::handle_t vertex_array, gl::index_t attribute, gl::vertex_array_attribute_type_e type, gl::count_t count, gl::ptrdiff_t offset, gl::bool_t normalized)
            {
                ::glVertexArrayAttribFormat(
                    gl::to_underlying        (vertex_array), 
                    static_cast<gl::uint32_t>(attribute)   ,             static_cast<gl::int32_t >(count)  , 
                    gl::to_underlying        (type)        , normalized, static_cast<gl::uint32_t>(offset));
            };
        auto vertex_array_attribute_format_l = [](gl::handle_t vertex_array, gl::index_t attribute, gl::vertex_array_attribute_type_e type, gl::count_t count, gl::ptrdiff_t offset                       )
            {
                ::glVertexArrayAttribLFormat(
                    gl::to_underlying        (vertex_array), 
                    static_cast<gl::uint32_t>(attribute)   , static_cast<gl::int32_t >(count)  , 
                    gl::to_underlying        (type)        , static_cast<gl::uint32_t>(offset));
            };

        const auto maximum_vertex_attributes = gl::get_value<gl::data_e::maximum_vertex_attributes>();
        if (attribute > maximum_vertex_attributes) throw std::invalid_argument{ "index exceeds vertex attribute limit" };
        
        switch (type)
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
            case uint32_10_11_11_11_float_r: return vertex_array_attribute_format_i(vertex_array, attribute, type, count, offset               );
            case fixed                     : 
            case float16                   : 
            case float32                   : return vertex_array_attribute_format_f(vertex_array, attribute, type, count, offset, is_normalized);
            case float64                   : return vertex_array_attribute_format_l(vertex_array, attribute, type, count, offset               );
        }
    }
    void vertex_array_vertex_buffer                       (gl::handle_t vertex_array, gl::handle_t vertex_buffer, gl::binding_t binding, gl::size_t stride, gl::index_t index)
    {
        ::glVertexArrayVertexBuffer(gl::to_underlying(vertex_array), gl::to_underlying(binding), gl::to_underlying(vertex_buffer), static_cast<gl::ptrdiff_t>(index), static_cast<gl::sizei_t>(stride));
    }
    void vertex_array_vertex_buffers                      (gl::handle_t vertex_array, std::span<const gl::handle_t> vertex_buffers, std::span<const gl::sizeu_t> strides, std::span<const gl::sizeu_t> offsets, gl::range_t range)
    {
        if (vertex_buffers.size() != strides.size()) throw std::invalid_argument{ "vertex buffer size does not match stride size" };

        ::glVertexArrayVertexBuffers(
            gl::to_underlying        (vertex_array)         , 
            static_cast<gl::uint32_t>(range.index)          , static_cast<gl::sizei_t>           (range.count)   , 
            gl::to_underlying_pointer(vertex_buffers.data()), std::bit_cast<const gl::ptrdiff_t*>(offsets.data()), std::bit_cast<const gl::sizei_t*>(strides.data()));
    }
    void vertex_array_attribute_binding                   (gl::handle_t vertex_array, gl::index_t attribute, gl::binding_t binding)
    {
        ::glVertexArrayAttribBinding(gl::to_underlying(vertex_array), static_cast<gl::uint32_t>(attribute), gl::to_underlying(binding));
    }
    void enable_vertex_array_attribute                    (gl::handle_t vertex_array, gl::index_t index)
    {
        ::glEnableVertexArrayAttrib(gl::to_underlying(vertex_array), static_cast<gl::uint32_t>(index));
    }
    void disable_vertex_array_attribute                   (gl::handle_t vertex_array, gl::index_t index)
    {
        ::glDisableVertexArrayAttrib(gl::to_underlying(vertex_array), static_cast<gl::uint32_t>(index));
    }
    void vertex_array_binding_divisor                     (gl::handle_t vertex_array, gl::binding_t binding, gl::uint32_t divisor)
    {
        ::glVertexArrayBindingDivisor(gl::to_underlying(vertex_array), gl::to_underlying(binding), divisor);
    }
    void primitive_restart_index                          (gl::index_t index)
    {
        ::glPrimitiveRestartIndex(static_cast<gl::uint32_t>(index));
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
            gl::to_underlying               (draw_mode)                                         , 
            std::bit_cast<const gl::void_t*>(offset * sizeof(gl::draw_arrays_indirect_command)));
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
            gl::to_underlying(draw_mode), static_cast  <      gl::sizei_t>(element_count)           , 
            gl::to_underlying(draw_type), std::bit_cast<const gl::void_t*>(offset * draw_type_size));
    }
    void draw_elements_base_vertex                        (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t element_count, gl::index_t offset, gl::int32_t base_vertex)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawElementsBaseVertex(
            gl::to_underlying(draw_mode),                                                            static_cast<gl::sizei_t>(element_count), 
            gl::to_underlying(draw_type), std::bit_cast<const gl::void_t*>(offset * draw_type_size),                          base_vertex  );
    }
    void draw_elements_indirect                           (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::index_t offset)
    {
        const auto draw_indirect_buffer_binding = gl::get_value<gl::data_e::draw_indirect_buffer_binding>();
        if (draw_indirect_buffer_binding == gl::null_object) throw std::runtime_error{ "no draw indirect buffer bound" };

        ::glDrawElementsIndirect(
            gl::to_underlying               (draw_mode)                                           , gl::to_underlying(draw_type), 
            std::bit_cast<const gl::void_t*>(offset * sizeof(gl::draw_elements_indirect_command)));
    }
    void draw_elements_instanced                          (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t element_count, gl::index_t offset, gl::count_t instance_count)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawElementsInstanced(
            gl::to_underlying(draw_mode),                                                            static_cast<gl::sizei_t>(element_count ) , 
            gl::to_underlying(draw_type), std::bit_cast<const gl::void_t*>(offset * draw_type_size), static_cast<gl::sizei_t>(instance_count));
    }
    void draw_elements_instanced_base_instance            (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t element_count, gl::index_t offset, gl::count_t instance_count, gl::index_t base_instance)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawElementsInstancedBaseInstance(
            gl::to_underlying(draw_mode),                                                            static_cast<gl::sizei_t>(element_count) , 
            gl::to_underlying(draw_type), std::bit_cast<const gl::void_t*>(offset * draw_type_size), static_cast<gl::sizei_t>(instance_count), static_cast<gl::uint32_t>(base_instance));
    }
    void draw_elements_instanced_base_vertex              (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t element_count, gl::index_t offset, gl::count_t instance_count, gl::int32_t base_vertex)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawElementsInstancedBaseVertex(
            gl::to_underlying(draw_mode),                                                            static_cast<gl::sizei_t>(element_count) , 
            gl::to_underlying(draw_type), std::bit_cast<const gl::void_t*>(offset * draw_type_size), static_cast<gl::sizei_t>(instance_count), base_vertex);
    }
    void draw_elements_instanced_base_vertex_base_instance(gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t element_count, gl::index_t offset, gl::count_t instance_count, gl::int32_t base_vertex, gl::index_t base_instance)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawElementsInstancedBaseVertexBaseInstance(
            gl::to_underlying(draw_mode),                                                            static_cast<gl::sizei_t>(element_count) , 
            gl::to_underlying(draw_type), std::bit_cast<const gl::void_t*>(offset * draw_type_size), static_cast<gl::sizei_t>(instance_count), base_vertex, static_cast<gl::uint32_t>(base_instance));
    }
    void draw_range_elements                              (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::index_t start_index, gl::index_t end_index, gl::count_t element_count, gl::index_t offset)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawRangeElements(
            gl::to_underlying        (draw_mode)    , 
            static_cast<gl::uint32_t>(start_index)  , static_cast<gl::uint32_t>(end_index), 
            static_cast<gl::sizei_t >(element_count), gl::to_underlying        (draw_type), std::bit_cast<const gl::void_t*>(offset * draw_type_size));
    }
    void draw_range_elements_base_vertex                  (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::index_t start_index, gl::index_t end_index, gl::count_t element_count, gl::index_t offset, gl::int32_t base_vertex)
    {
        const auto draw_type_size = gl::map_draw_type_size(draw_type);
        ::glDrawRangeElementsBaseVertex(
            gl::to_underlying        (draw_mode)    , 
            static_cast<gl::uint32_t>(start_index)  , static_cast<gl::uint32_t>(end_index), 
            static_cast<gl::sizei_t >(element_count), gl::to_underlying        (draw_type), std::bit_cast<const gl::void_t*>(offset * draw_type_size), base_vertex);
    }
    void multi_draw_arrays                                (gl::draw_mode_e draw_mode, std::span<const gl::index_t> starting_indices, std::span<const gl::count_t> vertex_counts)
    {
        const auto draw_count = std::min(starting_indices.size(), vertex_counts.size());
        ::glMultiDrawArrays(
            gl::to_underlying                (draw_mode)           , std::bit_cast<const gl::int32_t*>(starting_indices.data()), 
            std::bit_cast<const gl::sizei_t*>(vertex_counts.data()), static_cast  <      gl::sizei_t >(draw_count)            );
    }
    void multi_draw_arrays_indirect                       (gl::draw_mode_e draw_mode, gl::count_t draw_count, gl::index_t offset)
    {
        const auto draw_indirect_buffer_binding = gl::get_value<gl::data_e::draw_indirect_buffer_binding>();
        if (draw_indirect_buffer_binding == gl::null_object) throw std::runtime_error{ "no draw indirect buffer bound" };

        ::glMultiDrawArraysIndirect(
            gl::to_underlying       (draw_mode) , std::bit_cast<const gl::void_t*>(offset * sizeof(gl::draw_arrays_indirect_command)), 
            static_cast<gl::sizei_t>(draw_count), gl::sizei_t{ 0 }                                                                  );
    }
    void multi_draw_elements                              (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, std::span<const gl::count_t> element_counts, std::span<const gl::index_t> index_offsets)
    {
        const auto draw_count = std::min(element_counts.size(), index_offsets.size());
        ::glMultiDrawElements(
            gl::to_underlying(draw_mode), std::bit_cast<const gl::sizei_t*>(element_counts.data()), 
            gl::to_underlying(draw_type), std::bit_cast<const gl::void_t**>(index_offsets .data()), static_cast<gl::sizei_t>(draw_count));
    }
    void multi_draw_elements_indirect                     (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, gl::count_t draw_count, gl::index_t offset)
    {
        ::glMultiDrawElementsIndirect(
            gl::to_underlying               (draw_mode)                                          , gl::to_underlying       (draw_type) , 
            std::bit_cast<const gl::void_t*>(offset * sizeof(gl::draw_elements_indirect_command)), static_cast<gl::sizei_t>(draw_count), gl::sizei_t{ 0 });
    }
    void multi_draw_elements_base_vertex                  (gl::draw_mode_e draw_mode, gl::draw_type_e draw_type, std::span<const gl::count_t> element_counts, std::span<const gl::index_t> index_offsets, std::span<const gl::int32_t> base_vertex_offsets)
    {
        const auto draw_count = std::min(std::min(element_counts.size(), index_offsets.size()), base_vertex_offsets.size());
        ::glMultiDrawElementsBaseVertex(
            gl::to_underlying(draw_mode), std::bit_cast<const gl::sizei_t*>(element_counts     .data()), 
            gl::to_underlying(draw_type), std::bit_cast<const gl::void_t**>(index_offsets      .data()), static_cast<gl::sizei_t>(draw_count), 
                                                                            base_vertex_offsets.data());
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
    auto get_multisample_value                            (gl::index_t index) -> gl::vector_2f
    {
        auto value = gl::vector_2f{};
        return ::glGetMultisamplefv(gl::to_underlying(gl::multisample_parameter_e::sample_position), static_cast<gl::uint32_t>(index), gl::value_pointer(value)), value;
    }
    void minimum_sample_shading                           (gl::float32_t value)
    {
        ::glMinSampleShading(value);
    }
    void point_size                                       (gl::float32_t size)
    {
        ::glPointSize(size);
    }
    template<gl::point_parameter_e P>
    void point_parameter                                  (gl::point_parameter_argument_t<P> value)
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

        if constexpr (P == fade_threshold_size     ) point_parameter_f(P,                   value );
        if constexpr (P == sprite_coordinate_origin) point_parameter_i(P, gl::to_underlying(value));
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
            static_cast   <     gl::uint32_t>(index)         , 
            static_cast   <     gl::sizei_t >(values.size()) , 
            std::bit_cast<const gl::int32_t*>(values.data())); 
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
    void blend_equation_indexed                           (gl::blending_equation_e equation, gl::index_t index)
    {
        ::glBlendEquationi(static_cast<gl::uint32_t>(index), gl::to_underlying(equation));
    }
    void blend_equation_separate                          (gl::blending_equation_e equation_rgb, gl::blending_equation_e equation_alpha)
    {
        ::glBlendEquationSeparate(gl::to_underlying(equation_rgb), gl::to_underlying(equation_alpha));
    }
    void blend_equation_separate_indexed                  (gl::blending_equation_e color, gl::blending_equation_e alpha, gl::index_t index)
    {
        ::glBlendEquationSeparatei(static_cast<gl::uint32_t>(index), gl::to_underlying(color), gl::to_underlying(alpha));
    }
    void blend_function                                   (gl::blending_factor_e source, gl::blending_factor_e destination)
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
    void blend_function_separate                          (gl::blending_factor_e source_color, gl::blending_factor_e source_alpha, gl::blending_factor_e destination_color, gl::blending_factor_e destination_alpha)
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
    template<typename T>
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
    void copy_image_sub_data                              (gl::handle_t source, gl::handle_t destination, gl::texture_target_e source_target, gl::texture_target_e destination_target, gl::hypervolume_t source_region, gl::hypervolume_t destination_region)
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
    void dispatch_compute_indirect                        (gl::index_t offset)
    {
        ::glDispatchComputeIndirect(static_cast<gl::ptrdiff_t>(offset * sizeof(gl::dispatch_indirect_command)));
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
    void push_debug_group                                 (gl::handle_t identifier, const std::string& message)
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
