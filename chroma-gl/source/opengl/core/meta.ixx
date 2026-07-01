export module opengl:meta;

import std;
import :domain;
import :flags;
import :types;

export namespace gl::meta
{
    template<typename alpha_t, typename... beta_t>
    auto constexpr all_same_type_v          = std::conjunction_v<std::is_same<alpha_t, beta_t>...>;
    template<auto check_v, auto mininum_v, auto maximum_v>
    auto constexpr within_open_interval_v   = (check_v >  mininum_v && check_v <  maximum_v);
    template<auto check_v, auto minimum_v, auto maximum_v>
    auto constexpr within_closed_interval_v = (check_v >= minimum_v && check_v <= maximum_v);



    template<gl::feature_e feature_v>
    auto constexpr is_indexed_feature() -> gl::bool_t
    {
        using enum gl::feature_e;
        if   constexpr (feature_v == blending || feature_v == scissor_test) return gl::true_ ;
        else                                                                return gl::false_;
    }
    template<gl::data_e data_v>
    auto constexpr is_indexed_data() -> gl::bool_t
    {
        using enum gl::data_e;
        if constexpr (
            data_v == atomic_counter_buffer_binding     || 
            data_v == blending_destination_alpha        || 
            data_v == blending_destination_rgb          || 
            data_v == blending_equation_alpha           || 
            data_v == blending_equation_rgb             || 
            data_v == blending_source_alpha             || 
            data_v == blending_source_rgb               || 
            data_v == image_binding_access              || 
            data_v == image_binding_format              || 
            data_v == image_binding_layer               || 
            data_v == image_binding_layered             || 
            data_v == image_binding_level               || 
            data_v == image_binding_name                || 
            data_v == maximum_compute_work_group_count  || 
            data_v == maximum_compute_work_group_count  || 
            data_v == maximum_compute_work_group_size   || 
            data_v == maximum_compute_work_group_size   || 
            data_v == query_buffer_binding              || 
            data_v == sample_mask_value                 || 
            data_v == sample_mask_value                 || 
            data_v == scissor_box                       || 
            data_v == shader_storage_buffer_binding     || 
            data_v == shader_storage_buffer_size        || 
            data_v == shader_storage_buffer_size        || 
            data_v == shader_storage_buffer_start       || 
            data_v == shader_storage_buffer_start       || 
            data_v == transform_feedback_buffer_binding || 
            data_v == transform_feedback_buffer_size    || 
            data_v == transform_feedback_buffer_size    || 
            data_v == transform_feedback_buffer_start   || 
            data_v == transform_feedback_buffer_start   || 
            data_v == uniform_buffer_binding            || 
            data_v == uniform_buffer_size               || 
            data_v == uniform_buffer_size               || 
            data_v == uniform_buffer_start              || 
            data_v == uniform_buffer_start              || 
            data_v == vertex_binding_buffer             || 
            data_v == vertex_binding_buffer             || 
            data_v == vertex_binding_divisor            || 
            data_v == vertex_binding_divisor            || 
            data_v == vertex_binding_offset             || 
            data_v == vertex_binding_offset             || 
            data_v == vertex_binding_stride             || 
            data_v == vertex_binding_stride             || 
            data_v == viewport                           ) return gl::true_ ;
        else                                               return gl::false_;
    }
    template<gl::data_e data_v>
    consteval auto is_non_indexed_data() -> gl::bool_t
    {
        return !meta::is_indexed_data<data_v>();
    }  
    template<gl::context_property_e property_v>
    consteval auto is_indexed_property() -> gl::bool_t
    {
        if   constexpr (property_v == gl::context_property_e::extensions) return gl::true_ ;
        else                                                              return gl::false_;
    }
    template<gl::context_property_e property_v>
    consteval auto is_non_indexed_property() -> gl::bool_t
    {
        if   constexpr (property_v == gl::context_property_e::extensions) return gl::false_;
        else                                                              return gl::true_ ;
    }
    template<gl::texture_target_e from_v, gl::texture_target_e to_v>
    consteval auto is_valid_texture_view() -> gl::bool_t
    {
        using enum gl::texture_target_e;
        if constexpr (
            (from_v == _1d                   && (to_v == _1d             || to_v == _1d_array                                                          )) || 
            (from_v == _2d                   && (to_v == _2d             || to_v == _2d_array                                                          )) || 
            (from_v == _3d                   && (to_v == _3d                                                                                           )) || 
            (from_v == cubemap               && (to_v == cubemap         || to_v == _2d                   || to_v == _2d_array || to_v == cubemap_array)) || 
            (from_v == rectangle             && (to_v == rectangle                                                                                     )) || 
            (from_v == _1d_array             && (to_v == _1d             || to_v == _1d_array                                                          )) || 
            (from_v == _2d_array             && (to_v == _2d             || to_v == _2d_array                                                          )) || 
            (from_v == cubemap_array         && (to_v == _2d             || to_v == _2d_array             || to_v == cubemap  || to_v == cubemap_array )) || 
            (from_v == _2d_multisample       && (to_v == _2d_multisample || to_v == _2d_multisample_array                                              )) || 
            (from_v == _2d_multisample_array && (to_v == _2d_multisample || to_v == _2d_multisample_array                                              ))  ) 
             return gl::true_ ;
        else return gl::false_;
    }











    template<gl::data_e data_v> struct data_tag {};    
    template<gl::data_e data_v> using data_tag_t = data_tag<data_v>::type;

    template<> struct data_tag<gl::data_e::atomic_counter_buffer_binding                        >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::aliased_line_width_range                             >{ using type = gl::vector_2f                    ; };
    template<> struct data_tag<gl::data_e::blend_color                                          >{ using type = gl::vector_4f                    ; };
    template<> struct data_tag<gl::data_e::blending_destination_alpha                           >{ using type = gl::blending_factor_e            ; };    
    template<> struct data_tag<gl::data_e::blending_destination_rgb                             >{ using type = gl::blending_factor_e            ; };    
    template<> struct data_tag<gl::data_e::blending_equation_alpha                              >{ using type = gl::blending_equation_e          ; };    
    template<> struct data_tag<gl::data_e::blending_equation_rgb                                >{ using type = gl::blending_equation_e          ; };    
    template<> struct data_tag<gl::data_e::blending_source_alpha                                >{ using type = gl::blending_factor_e            ; };    
    template<> struct data_tag<gl::data_e::blending_source_rgb                                  >{ using type = gl::blending_factor_e            ; };    
    template<> struct data_tag<gl::data_e::clipping_depth_mode                                  >{ using type = gl::clipping_depth_mode_e        ; };    
    template<> struct data_tag<gl::data_e::clipping_origin                                      >{ using type = gl::clipping_origin_e            ; };    
    template<> struct data_tag<gl::data_e::color_clear_value                                    >{ using type = gl::vector_4f                    ; };
    template<> struct data_tag<gl::data_e::color_write_mask                                     >{ using type = gl::vector_4b                    ; };
    template<> struct data_tag<gl::data_e::context_flags                                        >{ using type = gl::context_flags_e              ; };    
    template<> struct data_tag<gl::data_e::context_profile_mask                                 >{ using type = gl::context_profile_e            ; };    
    template<> struct data_tag<gl::data_e::copy_read_buffer_binding                             >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::copy_write_buffer_binding                            >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::current_program                                      >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::debug_group_stack_depth                              >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::debug_logged_messages                                >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::depth_clear_value                                    >{ using type = gl::float64_t                    ; };
    template<> struct data_tag<gl::data_e::depth_function                                       >{ using type = gl::depth_function_e             ; };    
    template<> struct data_tag<gl::data_e::depth_range                                          >{ using type = gl::vector_2f                    ; };
    template<> struct data_tag<gl::data_e::dispatch_indirect_buffer_binding                     >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::double_buffer                                        >{ using type = gl::boolean_t                    ; };
    template<> struct data_tag<gl::data_e::draw_buffer                                          >{ using type = gl::frame_buffer_source_e        ; };    
    template<> struct data_tag<gl::data_e::draw_frame_buffer_binding                            >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::draw_indirect_buffer_binding                         >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::fragment_shader_derivative_hint                      >{ using type = gl::hint_mode_e                  ; };    
    template<> struct data_tag<gl::data_e::implementation_color_read_format                     >{ using type = gl::pixel_data_format_e          ; };    
    template<> struct data_tag<gl::data_e::implementation_color_read_type                       >{ using type = gl::pixel_data_type_e            ; };    
    template<> struct data_tag<gl::data_e::index_array_buffer_binding                           >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::layer_provoking_vertex                               >{ using type = gl::provoking_vertex_mode_e      ; };    
    template<> struct data_tag<gl::data_e::line_smooth_hint                                     >{ using type = gl::hint_mode_e                  ; };    
    template<> struct data_tag<gl::data_e::line_width                                           >{ using type = gl::float64_t                    ; };
    template<> struct data_tag<gl::data_e::logic_operation_mode                                 >{ using type = gl::logical_pixel_operation_e    ; };    
    template<> struct data_tag<gl::data_e::major_version                                        >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_3d_texture_size                              >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_array_texture_layers                         >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_clip_distances                               >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_color_attachments                            >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_color_texture_samples                        >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_combined_atomic_counters                     >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_combined_compute_uniform_components          >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_combined_fragment_uniform_components         >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_combined_geometry_uniform_components         >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_combined_shader_storage_blocks               >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_combined_texture_image_units                 >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_combined_uniform_blocks                      >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_combined_vertex_uniform_components           >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_compute_atomic_counter_buffers               >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_compute_atomic_counters                      >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_compute_shader_storage_blocks                >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_compute_texture_image_units                  >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_compute_uniform_blocks                       >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_compute_uniform_components                   >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_compute_work_group_count                     >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_compute_work_group_invocations               >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_compute_work_group_size                      >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_cubemap_texture_size                         >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_debug_group_stack_depth                      >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_debug_message_length                         >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_depth_texture_samples                        >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_draw_buffers                                 >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_dual_source_draw_buffers                     >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_element_index                                >{ using type = gl::uint64_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_fragment_atomic_counters                     >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_fragment_input_components                    >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_fragment_shader_storage_blocks               >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_fragment_uniform_blocks                      >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_fragment_uniform_components                  >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_fragment_uniform_vectors                     >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_frame_buffer_height                          >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_frame_buffer_layers                          >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_frame_buffer_samples                         >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_frame_buffer_width                           >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_geometry_atomic_counters                     >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_geometry_input_components                    >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_geometry_output_components                   >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_geometry_shader_storage_blocks               >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_geometry_texture_image_units                 >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_geometry_uniform_blocks                      >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_geometry_uniform_components                  >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_index_elements                               >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_integer_samples                              >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_label_length                                 >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_program_texel_offset                         >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_rectangle_texture_size                       >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_render_buffer_size                           >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_sample_mask_words                            >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_server_wait_timeout                          >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_shader_storage_buffer_bindings               >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_tessellation_control_atomic_counters         >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_tessellation_control_shaders_torageblocks    >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_tessellation_evaluation_atomic_counters      >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_tessellation_evaluation_shader_storage_blocks>{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_texture_buffer_size                          >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_texture_image_units                          >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_texture_lod_bias                             >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_texture_size                                 >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_uniform_block_size                           >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_uniform_buffer_bindings                      >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_uniform_locations                            >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_varying_components                           >{ using type = gl::uint32_t                     ; };
  //template<> struct data_tag<gl::data_e::maximum_varying_floats                               >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_varying_vectors                              >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_vertex_atomic_counters                       >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_vertex_attribute_bindings                    >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_vertex_attribute_relative_offset             >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_vertex_attributes                            >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_vertex_elements                              >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_vertex_output_components                     >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_vertex_shader_storage_blocks                 >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_vertex_texture_image_units                   >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_vertex_uniform_blocks                        >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_vertex_uniform_components                    >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_vertex_uniform_vectors                       >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_viewport_dimensions                          >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::maximum_viewports                                    >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::minimum_map_buffer_alignment                         >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::minimum_program_texel_offset                         >{ using type = gl::int32_t                      ; };
    template<> struct data_tag<gl::data_e::minor_version                                        >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::number_compressed_texture_formats                    >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::number_extensions                                    >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::number_program_binary_formats                        >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::number_shader_binary_formats                         >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::pack_alignment                                       >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::pack_compressed_block_depth                          >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::pack_compressed_block_height                         >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::pack_compressed_block_size                           >{ using type = gl::size_t                       ; };
    template<> struct data_tag<gl::data_e::pack_compressed_block_width                          >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::pack_image_height                                    >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::pack_row_length                                      >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::pack_skip_images                                     >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::pack_skip_pixels                                     >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::pack_skip_rows                                       >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::pack_swap_bytes                                      >{ using type = gl::boolean_t                    ; };
    template<> struct data_tag<gl::data_e::parameter_buffer_binding                             >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::patch_default_inner_level                            >{ using type = gl::vector_2f                    ; };
    template<> struct data_tag<gl::data_e::patch_default_outer_level                            >{ using type = gl::vector_4f                    ; };
    template<> struct data_tag<gl::data_e::pixel_pack_buffer_binding                            >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::pixel_unpack_buffer_binding                          >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::point_fade_threshold_size                            >{ using type = gl::float32_t                    ; };
    template<> struct data_tag<gl::data_e::point_size                                           >{ using type = gl::float32_t                    ; };
    template<> struct data_tag<gl::data_e::point_size_granularity                               >{ using type = gl::float32_t                    ; };
    template<> struct data_tag<gl::data_e::point_size_range                                     >{ using type = gl::vector_2f                    ; };
    template<> struct data_tag<gl::data_e::polygon_offset_factor                                >{ using type = gl::float32_t                    ; };
    template<> struct data_tag<gl::data_e::polygon_offset_units                                 >{ using type = gl::float32_t                    ; };
    template<> struct data_tag<gl::data_e::polygon_smooth_hint                                  >{ using type = gl::hint_mode_e                  ; };
    template<> struct data_tag<gl::data_e::primitive_restart_index                              >{ using type = gl::size_t                       ; };
    template<> struct data_tag<gl::data_e::program_binary_formats                               >{ using type = gl::binary_format_e              ; };
    template<> struct data_tag<gl::data_e::program_pipeline_binding                             >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::provoking_vertex                                     >{ using type = gl::provoking_vertex_mode_e      ; };
    template<> struct data_tag<gl::data_e::read_buffer                                          >{ using type = gl::frame_buffer_source_e        ; };
    template<> struct data_tag<gl::data_e::read_frame_buffer_binding                            >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::render_buffer_binding                                >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::reset_notification_strategy                          >{ using type = gl::reset_notification_strategy_e; };
    template<> struct data_tag<gl::data_e::sample_buffers                                       >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::sample_coverage_invert                               >{ using type = gl::boolean_t                    ; };
    template<> struct data_tag<gl::data_e::sample_coverage_value                                >{ using type = gl::float32_t                    ; };
    template<> struct data_tag<gl::data_e::sampler_binding                                      >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::samples                                              >{ using type = gl::bitfield_t                   ; };
    template<> struct data_tag<gl::data_e::scissor_box                                          >{ using type = gl::area_t                       ; };
    template<> struct data_tag<gl::data_e::shader_compiler                                      >{ using type = gl::boolean_t                    ; };
    template<> struct data_tag<gl::data_e::shader_storage_buffer_binding                        >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::shader_storage_buffer_offset_alignment               >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::smooth_line_width_granularity                        >{ using type = gl::float32_t                    ; };
    template<> struct data_tag<gl::data_e::smooth_line_width_range                              >{ using type = gl::vector_2f                    ; };
    template<> struct data_tag<gl::data_e::stencil_back_fail                                    >{ using type = gl::stencil_action_e             ; };
    template<> struct data_tag<gl::data_e::stencil_back_function                                >{ using type = gl::stencil_function_e           ; };
    template<> struct data_tag<gl::data_e::stencil_back_pass_depth_fail                         >{ using type = gl::stencil_action_e             ; };
    template<> struct data_tag<gl::data_e::stencil_back_pass_depth_pass                         >{ using type = gl::stencil_action_e             ; };
    template<> struct data_tag<gl::data_e::stencil_back_reference                               >{ using type = gl::int32_t                      ; };
    template<> struct data_tag<gl::data_e::stencil_back_value_mask                              >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::stencil_back_write_mask                              >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::stencil_clear_value                                  >{ using type = gl::size_t                       ; };
    template<> struct data_tag<gl::data_e::stencil_fail                                         >{ using type = gl::stencil_action_e             ; };
    template<> struct data_tag<gl::data_e::stencil_function                                     >{ using type = gl::stencil_function_e           ; };
    template<> struct data_tag<gl::data_e::stencil_pass_depth_fail                              >{ using type = gl::stencil_action_e             ; };
    template<> struct data_tag<gl::data_e::stencil_pass_depth_pass                              >{ using type = gl::stencil_action_e             ; };
    template<> struct data_tag<gl::data_e::stencil_reference                                    >{ using type = gl::int32_t                      ; };
    template<> struct data_tag<gl::data_e::stencil_value_mask                                   >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::stencil_write_mask                                   >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::supports_stereo                                      >{ using type = gl::boolean_t                    ; };
    template<> struct data_tag<gl::data_e::sub_pixel_bits                                       >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::texture_binding_1d                                   >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::texture_binding_1d_array                             >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::texture_binding_2d                                   >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::texture_binding_2d_array                             >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::texture_binding_2d_multisample                       >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::texture_binding_2d_multisample_array                 >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::texture_binding_3d                                   >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::texture_binding_buffer                               >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::texture_binding_cubemap                              >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::texture_binding_rectangle                            >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::texture_buffer_binding                               >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::texture_buffer_offset_alignment                      >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::texture_compression_hint                             >{ using type = gl::hint_mode_e                  ; };
    template<> struct data_tag<gl::data_e::timestamp                                            >{ using type = gl::int64_t                      ; };
    template<> struct data_tag<gl::data_e::transform_feedback_binding                           >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::transform_feedback_buffer_binding                    >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::uniform_buffer_binding                               >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::uniform_buffer_offset_alignment                      >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::unpack_alignment                                     >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::unpack_compressed_block_depth                        >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::unpack_compressed_block_height                       >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::unpack_compressed_block_size                         >{ using type = gl::size_t                       ; };
    template<> struct data_tag<gl::data_e::unpack_compressed_block_width                        >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::unpack_image_height                                  >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::unpack_row_length                                    >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::unpack_skip_images                                   >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::unpack_skip_pixels                                   >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::unpack_skip_rows                                     >{ using type = gl::uint32_t                     ; };
    template<> struct data_tag<gl::data_e::unpack_swap_bytes                                    >{ using type = gl::boolean_t                    ; };
    template<> struct data_tag<gl::data_e::vertex_array_binding                                 >{ using type = gl::handle_t                     ; };
    template<> struct data_tag<gl::data_e::viewport                                             >{ using type = gl::area_t                       ; };
    template<> struct data_tag<gl::data_e::viewport_bounds_range                                >{ using type = gl::vector_2i                    ; };
    template<> struct data_tag<gl::data_e::viewport_index_provoking_vertex                      >{ using type = gl::provoking_vertex_convention_e; };
    template<> struct data_tag<gl::data_e::viewport_sub_pixel_bits                              >{ using type = gl::uint32_t                     ; };



    template<gl::data_e data_v> struct indexed_data_tag {};
    template<gl::data_e data_v> using indexed_data_tag_t = meta::indexed_data_tag<data_v>::type;

    template<> struct indexed_data_tag<gl::data_e::atomic_counter_buffer_binding    >{ using type = gl::handle_t           ; };
    template<> struct indexed_data_tag<gl::data_e::blending_equation_alpha          >{ using type = gl::blending_equation_e; };
    template<> struct indexed_data_tag<gl::data_e::blending_equation_rgb            >{ using type = gl::blending_equation_e; };
    template<> struct indexed_data_tag<gl::data_e::blending_source_alpha            >{ using type = gl::blending_factor_e  ; };
    template<> struct indexed_data_tag<gl::data_e::blending_source_rgb              >{ using type = gl::blending_factor_e  ; };
    template<> struct indexed_data_tag<gl::data_e::blending_destination_alpha       >{ using type = gl::blending_factor_e  ; };
    template<> struct indexed_data_tag<gl::data_e::blending_destination_rgb         >{ using type = gl::blending_factor_e  ; };
    template<> struct indexed_data_tag<gl::data_e::image_binding_access             >{ using type = gl::image_access_e     ; };
    template<> struct indexed_data_tag<gl::data_e::image_binding_format             >{ using type = gl::image_format_e     ; };
    template<> struct indexed_data_tag<gl::data_e::image_binding_layer              >{ using type = gl::uint32_t           ; };
    template<> struct indexed_data_tag<gl::data_e::image_binding_layered            >{ using type = gl::boolean_t          ; };
    template<> struct indexed_data_tag<gl::data_e::image_binding_level              >{ using type = gl::uint32_t           ; };
    template<> struct indexed_data_tag<gl::data_e::image_binding_name               >{ using type = gl::handle_t           ; };
    template<> struct indexed_data_tag<gl::data_e::maximum_compute_work_group_count >{ using type = gl::size_t             ; };
    template<> struct indexed_data_tag<gl::data_e::maximum_compute_work_group_size  >{ using type = gl::size_t             ; };
    template<> struct indexed_data_tag<gl::data_e::query_buffer_binding             >{ using type = gl::handle_t           ; };
    template<> struct indexed_data_tag<gl::data_e::scissor_box                      >{ using type = gl::vector_4u          ; };
    template<> struct indexed_data_tag<gl::data_e::sample_mask_value                >{ using type = gl::bitfield_t         ; };
    template<> struct indexed_data_tag<gl::data_e::shader_storage_buffer_binding    >{ using type = gl::handle_t           ; };
    template<> struct indexed_data_tag<gl::data_e::shader_storage_buffer_size       >{ using type = gl::size_t             ; };
    template<> struct indexed_data_tag<gl::data_e::shader_storage_buffer_start      >{ using type = gl::size_t             ; };
    template<> struct indexed_data_tag<gl::data_e::transform_feedback_buffer_binding>{ using type = gl::handle_t           ; };
    template<> struct indexed_data_tag<gl::data_e::transform_feedback_buffer_size   >{ using type = gl::size_t             ; };
    template<> struct indexed_data_tag<gl::data_e::transform_feedback_buffer_start  >{ using type = gl::size_t             ; };
    template<> struct indexed_data_tag<gl::data_e::uniform_buffer_binding           >{ using type = gl::handle_t           ; };
    template<> struct indexed_data_tag<gl::data_e::uniform_buffer_size              >{ using type = gl::size_t             ; };
    template<> struct indexed_data_tag<gl::data_e::uniform_buffer_start             >{ using type = gl::size_t             ; };
    template<> struct indexed_data_tag<gl::data_e::vertex_binding_buffer            >{ using type = gl::handle_t           ; };
    template<> struct indexed_data_tag<gl::data_e::vertex_binding_divisor           >{ using type = gl::uint32_t           ; };
    template<> struct indexed_data_tag<gl::data_e::vertex_binding_offset            >{ using type = gl::size_t             ; };
    template<> struct indexed_data_tag<gl::data_e::vertex_binding_stride            >{ using type = gl::size_t             ; };
    template<> struct indexed_data_tag<gl::data_e::viewport                         >{ using type = gl::area_t             ; };



    template<gl::internal_format_parameter_e parameter_v> struct internal_format_data_tag {};
    template<gl::internal_format_parameter_e parameter_v> using internal_format_data_tag_t = internal_format_data_tag<parameter_v>::type;

    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::auto_generate_mipmap                  >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::clear_buffer                          >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::clear_texture                         >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::color_components                      >{ using type = gl::uint32_t        ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::color_encoding                        >{ using type = gl::color_encoding_e; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::is_color_renderable                   >{ using type = gl::bool_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::compute_texture                       >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::depth_components                      >{ using type = gl::uint32_t        ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::is_depth_renderable                   >{ using type = gl::bool_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::supports_filter                       >{ using type = gl::bool_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::fragment_texture                      >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::supports_frame_buffer_blend           >{ using type = gl::bool_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::frame_buffer_renderable               >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::frame_buffer_renderable_layered       >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::geometry_texture                      >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::get_texture_image_format              >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::get_texture_image_type                >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::image_compatibility_class             >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::image_format_compatibility_type       >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::image_pixel_format                    >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::image_pixel_type                      >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_alpha_size            >{ using type = gl::sizeu_t         ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_alpha_type            >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_blue_size             >{ using type = gl::sizeu_t         ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_blue_type             >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_depth_size            >{ using type = gl::sizeu_t         ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_depth_type            >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_green_size            >{ using type = gl::sizeu_t         ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_green_type            >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_preferred             >{ using type = gl::bool_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_red_size              >{ using type = gl::sizeu_t         ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_red_type              >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_shared_size           >{ using type = gl::sizeu_t         ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_stencil_size          >{ using type = gl::sizeu_t         ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::internal_format_stencil_type          >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::is_supported                          >{ using type = gl::bool_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::maximum_combined_dimensions           >{ using type = gl::uint32_t        ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::maximum_depth                         >{ using type = gl::uint32_t        ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::maximum_height                        >{ using type = gl::uint32_t        ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::maximum_layers                        >{ using type = gl::uint32_t        ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::maximum_width                         >{ using type = gl::uint32_t        ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::supports_mipmap                       >{ using type = gl::bool_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::number_sample_counts                  >{ using type = gl::uint32_t        ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::read_pixels                           >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::read_pixels_format                    >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::read_pixels_type                      >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::samples                               >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::shader_image_atomic                   >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::shader_image_load                     >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::shader_image_store                    >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::simultaneous_texture_and_depth_test   >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::simultaneous_texture_and_depth_write  >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::simultaneous_texture_and_stencil_test >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::simultaneous_texture_and_stencil_write>{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::srgb_read                             >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::srgb_write                            >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::stencil_components                    >{ using type = gl::uint32_t        ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::is_stencil_renderable                 >{ using type = gl::bool_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::tessellation_control_texture          >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::tessellation_evaluation_texture       >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::is_texture_compressed                 >{ using type = gl::bool_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::texture_compressed_block_height       >{ using type = gl::uint32_t        ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::texture_compressed_block_size         >{ using type = gl::sizeu_t         ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::texture_compressed_block_width        >{ using type = gl::uint32_t        ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::texture_gather                        >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::texture_gather_shadow                 >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::texture_image_format                  >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::texture_image_type                    >{ using type = gl::enum_t          ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::texture_shadow                        >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::texture_view                          >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::vertex_texture                        >{ using type = gl::support_level_e ; };
    template<> struct internal_format_data_tag<gl::internal_format_parameter_e::view_compatibility_class              >{ using type = gl::enum_t          ; };
}
