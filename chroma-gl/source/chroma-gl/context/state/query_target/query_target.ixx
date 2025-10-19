export module opengl.context.state.query_target;

import std;
import opengl;

export namespace gl
{
    std::unordered_map<gl::query_target_e, gl::bool_t> query_target_state
    {
        { gl::query_target_e::any_samples_passed                        , gl::false_ }, 
        { gl::query_target_e::any_samples_passed_conservative           , gl::false_ }, 
        { gl::query_target_e::clipping_input_primitives                 , gl::false_ }, 
        { gl::query_target_e::clipping_output_primitives                , gl::false_ }, 
        { gl::query_target_e::compute_shader_invocations                , gl::false_ }, 
        { gl::query_target_e::fragment_shader_invocations               , gl::false_ }, 
        { gl::query_target_e::geometry_shader_invocations               , gl::false_ }, 
        { gl::query_target_e::geometry_shader_primitives_emitted        , gl::false_ }, 
        { gl::query_target_e::primitives_generated                      , gl::false_ }, 
        { gl::query_target_e::primitives_submitted                      , gl::false_ }, 
        { gl::query_target_e::samples_passed                            , gl::false_ }, 
        { gl::query_target_e::tessellation_control_shader_patches       , gl::false_ }, 
        { gl::query_target_e::tessellation_evaluation_shader_invocations, gl::false_ }, 
        { gl::query_target_e::time_elapsed                              , gl::false_ }, 
        { gl::query_target_e::timestamp                                 , gl::false_ }, 
        { gl::query_target_e::transform_feedback_overflow               , gl::false_ }, 
        { gl::query_target_e::transform_feedback_primitives_written     , gl::false_ }, 
        { gl::query_target_e::transform_feedback_stream_overflow        , gl::false_ }, 
        { gl::query_target_e::vertex_shader_invocations                 , gl::false_ }, 
        { gl::query_target_e::vertices_submitted                        , gl::false_ }, 
    };
}