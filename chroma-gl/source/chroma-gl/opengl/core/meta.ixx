export module opengl:meta;

import std;
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
}
