export module opengl.meta;

import std;
import opengl.flags;
import opengl.types;

export namespace gl::meta
{
    template<typename T, typename... Ts>
    constexpr auto all_same_type_v = static_cast<gl::bool_t>(std::conjunction_v<std::is_same<T, Ts>...>);
    
    template<auto value, auto min, auto max>
    constexpr auto within_open_interval_v   = value >  min && value <  max;
    
    template<auto value, auto min, auto max>
    constexpr auto within_closed_interval_v = value >= min && value <= max;



    template<gl::feature_e F>
    consteval auto is_indexed_feature() -> gl::bool_t
    {
        using enum gl::feature_e;

        if constexpr (
            F == blending      || 
            F == scissor_test   ) return gl::true_ ;
        else                      return gl::false_;
    }
    template<gl::data_e D>
    consteval auto is_indexed_data() -> gl::bool_t
    {
        using enum gl::data_e;

        if constexpr (
            D == maximum_compute_work_group_count ||
            D == maximum_compute_work_group_size  ||
            D == sample_mask_value                ||
            D == shader_storage_buffer_size       ||
            D == shader_storage_buffer_start      ||
            D == transform_feedback_buffer_size   ||
            D == transform_feedback_buffer_start  ||
            D == uniform_buffer_size              ||
            D == uniform_buffer_start             ||
            D == vertex_binding_divisor           ||
            D == vertex_binding_offset            ||
            D == vertex_binding_stride            ||
            D == vertex_binding_buffer             ) return gl::true_ ;
        else                                         return gl::false_;
    }
    template<gl::data_e D>
    consteval auto is_non_indexed_data() -> gl::bool_t
    {
        return !meta::is_indexed_data<D>();
    }  
    template<gl::texture_target_e T, gl::texture_target_e U>
    consteval auto is_valid_texture_view() -> gl::bool_t
    {
        using enum gl::texture_target_e;

        if constexpr (
            (T == _1d                   && (U == _1d             || U == _1d_array                                                    )) ||
            (T == _2d                   && (U == _2d             || U == _2d_array                                                    )) ||
            (T == _3d                   && (U == _3d                                                                                  )) ||
            (T == cubemap               && (U == cubemap         || U == _2d                   || U == _2d_array || U == cubemap_array)) ||
            (T == rectangle             && (U == rectangle                                                                            )) ||
            (T == _1d_array             && (U == _1d             || U == _1d_array                                                    )) ||
            (T == _2d_array             && (U == _2d             || U == _2d_array                                                    )) ||
            (T == cubemap_array         && (U == _2d             || U == _2d_array             || U == cubemap  || U == cubemap_array )) ||
            (T == _2d_multisample       && (U == _2d_multisample || U == _2d_multisample_array                                        )) ||
            (T == _2d_multisample_array && (U == _2d_multisample || U == _2d_multisample_array                                        ))  ) return gl::true_ ;
        else                                                                                                                                return gl::false_;
    }
}
