export module opengl.meta;

import std;
import opengl.flags;
import opengl.types;

export namespace gl
{
    template<typename T, typename... Ts>
    constexpr auto all_same_type_v = static_cast<gl::bool_t>(std::conjunction_v<std::is_same<T, Ts>...>);



    template<gl::feature_e F>
    concept indexed_feature_c = 
        (
               F == gl::feature_e::blending 
            || F == gl::feature_e::scissor_test
        );

    template<gl::data_e D>
    concept indexed_data_c = 
        (
               D == gl::data_e::maximum_compute_work_group_count
            || D == gl::data_e::maximum_compute_work_group_size
            || D == gl::data_e::sample_mask_value
            || D == gl::data_e::shader_storage_buffer_size
            || D == gl::data_e::shader_storage_buffer_start
            || D == gl::data_e::transform_feedback_buffer_size
            || D == gl::data_e::transform_feedback_buffer_start
            || D == gl::data_e::uniform_buffer_size
            || D == gl::data_e::uniform_buffer_start
            || D == gl::data_e::vertex_binding_divisor
            || D == gl::data_e::vertex_binding_offset
            || D == gl::data_e::vertex_binding_stride
            || D == gl::data_e::vertex_binding_buffer
        );

    template<gl::texture_target_e T, gl::texture_target_e U>
    concept valid_texture_view_c = 
           (T == gl::texture_target_e::_1d                   && (U == gl::texture_target_e::_1d             || U == gl::texture_target_e::_1d_array                                                                                                ))
        || (T == gl::texture_target_e::_2d                   && (U == gl::texture_target_e::_2d             || U == gl::texture_target_e::_2d_array                                                                                                ))
        || (T == gl::texture_target_e::_3d                   && (U == gl::texture_target_e::_3d                                                                                                                                                    ))
        || (T == gl::texture_target_e::cubemap               && (U == gl::texture_target_e::cubemap         || U == gl::texture_target_e::_2d                   || U == gl::texture_target_e::_2d_array || U == gl::texture_target_e::cubemap_array))
        || (T == gl::texture_target_e::rectangle             && (U == gl::texture_target_e::rectangle                                                                                                                                              ))
        || (T == gl::texture_target_e::_1d_array             && (U == gl::texture_target_e::_1d             || U == gl::texture_target_e::_1d_array                                                                                                ))
        || (T == gl::texture_target_e::_2d_array             && (U == gl::texture_target_e::_2d             || U == gl::texture_target_e::_2d_array                                                                                                ))
        || (T == gl::texture_target_e::cubemap_array         && (U == gl::texture_target_e::_2d             || U == gl::texture_target_e::_2d_array             || U == gl::texture_target_e::cubemap  || U == gl::texture_target_e::cubemap_array ))
        || (T == gl::texture_target_e::_2d_multisample       && (U == gl::texture_target_e::_2d_multisample || U == gl::texture_target_e::_2d_multisample_array                                                                                    ))
        || (T == gl::texture_target_e::_2d_multisample_array && (U == gl::texture_target_e::_2d_multisample || U == gl::texture_target_e::_2d_multisample_array                                                                                    ));
}
