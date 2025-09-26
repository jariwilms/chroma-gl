export module opengl.legacy;
export import opengl.flags;
export import opengl.types;
export import opengl.utility;

import std;
import <glad/gl.h>;

export namespace gl::legacy
{
    auto get_boolean_value          (gl::data_e data) -> gl::bool_t
    {
        auto value = gl::boolean_t{};
        return ::glGetBooleanv(gl::to_underlying(data), &value), static_cast<gl::bool_t>(value);
    }
    auto get_integer_value          (gl::data_e data) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        return ::glGetIntegerv(gl::to_underlying(data), &value), value;
    }
    auto get_integer64_value        (gl::data_e data) -> gl::int64_t
    {
        auto value = gl::int64_t{};
        return ::glGetInteger64v(gl::to_underlying(data), &value), value;
    }
    auto get_float_value            (gl::data_e data) -> gl::float32_t
    {
        auto value = gl::float32_t{};
        return ::glGetFloatv(gl::to_underlying(data), &value), value;
    }
    auto get_float64_value          (gl::data_e data) -> gl::float64_t
    {
        auto value = gl::float64_t{};
        return ::glGetDoublev(gl::to_underlying(data), &value), value;
    }
    auto get_indexed_boolean_value  (gl::data_e data, gl::index_t index) -> gl::boolean_t
    {
        auto value = gl::boolean_t{};
        return ::glGetBooleani_v(gl::to_underlying(data), index, &value), value;
    }
    auto get_indexed_integer_value  (gl::data_e data, gl::index_t index) -> gl::int32_t
    {
        auto value = gl::int32_t{};
        return ::glGetIntegeri_v(gl::to_underlying(data), index, &value), value;
    }
    auto get_indexed_integer64_value(gl::data_e data, gl::index_t index) -> gl::int64_t
    {
        auto value = gl::int64_t{};
        return ::glGetInteger64i_v(gl::to_underlying(data), index, &value), value;
    }
    auto get_indexed_float_value    (gl::data_e data, gl::index_t index) -> gl::float32_t
    {
        auto value = gl::float32_t{};
        return ::glGetFloati_v(gl::to_underlying(data), index, &value), value;
    }
    auto get_indexed_float64_value  (gl::data_e data, gl::index_t index) -> gl::float64_t
    {
        auto value = gl::float64_t{};
        return ::glGetDoublei_v(gl::to_underlying(data), index, &value), value;
    }
    
    auto is_buffer                  (gl::handle_t handle) -> gl::bool_t 
    {
        return static_cast<gl::bool_t>(::glIsBuffer(std::to_underlying(handle)));
    }
    auto is_framebuffer             (gl::handle_t handle) -> gl::bool_t
    {
        return static_cast<gl::bool_t>(::glIsFramebuffer(std::to_underlying(handle)));
    }
    auto is_program                 (gl::handle_t handle) -> gl::bool_t 
    {
        return static_cast<gl::bool_t>(::glIsProgram(std::to_underlying(handle)));
    }
    auto is_program_pipeline        (gl::handle_t handle) -> gl::bool_t 
    {
        return static_cast<gl::bool_t>(::glIsProgramPipeline(std::to_underlying(handle)));
    }
    auto is_query                   (gl::handle_t handle) -> gl::bool_t 
    {
        return static_cast<gl::bool_t>(::glIsQuery(std::to_underlying(handle)));
    }
    auto is_renderbuffer            (gl::handle_t handle) -> gl::bool_t 
    {
        return static_cast<gl::bool_t>(::glIsRenderbuffer(std::to_underlying(handle)));
    }
    auto is_sampler                 (gl::handle_t handle) -> gl::bool_t 
    {
        return static_cast<gl::bool_t>(::glIsSampler(std::to_underlying(handle)));
    }
    auto is_shader                  (gl::handle_t handle) -> gl::bool_t 
    {
        return static_cast<gl::bool_t>(::glIsShader(std::to_underlying(handle)));
    }
    auto is_texture                 (gl::handle_t handle) -> gl::bool_t 
    {
        return static_cast<gl::bool_t>(::glIsTexture(std::to_underlying(handle)));
    }
    auto is_transform_feedback      (gl::handle_t handle) -> gl::bool_t 
    {
        return static_cast<gl::bool_t>(::glIsTransformFeedback(std::to_underlying(handle)));
    }
    auto is_vertex_array            (gl::handle_t handle) -> gl::bool_t 
    {
        return static_cast<gl::bool_t>(::glIsVertexArray(std::to_underlying(handle)));
    }
    auto is_sync                    (gl::sync_t sync) -> gl::bool_t 
    {
        return static_cast<gl::bool_t>(::glIsSync(sync));
    }

    auto get_error                  () -> gl::error_flag_e
    {
        return static_cast<gl::error_flag_e>(::glGetError());
    }














//    void active_shader_program      ()
//    {
//        glActiveShaderProgram();
//    }
//    void active_texture             ()
//    {
//        glActiveTexture();
//    }
//    void attach_shader              ()
//    {
//        glAttachShader();
//    }
//    void bind_attrib_location       ()
//    {
//        glBindAttribLocation();
//    }
//    void bind_buffer                ()
//    {
//        glBindBuffer();
//    }
//    void bind_texture               ()
//    {
//        glBindTexture();
//    }
//    void bind_textures              ()
//    {
//        glBindTextures();
//    }
//    void bind_transform_feedback    ()
//    {
//        glBindTransformFeedback();
//    }
//    void bind_vertex_buffer         ()
//    {
//        glBindVertexBuffer();
//    }
//    void bind_vertex_buffers        ()
//    {
//        glBindVertexBuffers();
//    }
//    void buffer_data                ()
//    {
//        glBufferData();
//    }
//    void buffer_sub_data            ()
//    {
//        glBufferSubData();
//    }
//    void check_framebuffer_status   ()
//    {
//        glCheckFramebufferStatus();
//    }
//    void clear_buffer_data          ()
//    {
//        glClearBufferData();
//    }
//    void clear_buffer_sub_data      ()
//    {
//        glClearBufferSubData();
//    }
//    void compressed_tex_image1_d    ()
//    {
//        glCompressedTexImage1D();
//    }
//    void compressed_tex_image2_d    ()
//    {
//        glCompressedTexImage2D();
//    }
//    void compressed_tex_image3_d    ()
//    {
//        glCompressedTexImage3D();
//    }
//    void compressed_tex_sub_image1_d()
//    {
//        glCompressedTexSubImage1D();
//    }
//    void compressed_tex_sub_image2_d()
//    {
//        glCompressedTexSubImage2D();
//    }
//    void compressed_tex_sub_image3_d()
//    {
//        glCompressedTexSubImage3D();
//    }
//    void copy_buffer_sub_data       ()
//    {
//        glCopyBufferSubData();
//    }
//    void copy_tex_image1_d          ()
//    {
//        glCopyTexImage1D();
//    }
//    void copy_tex_image2_d          ()
//    {
//        glCopyTexImage2D();
//    }
//    void copy_tex_sub_image1_d      ()
//    {
//        glCopyTexSubImage1D();
//    }
//    void copy_tex_sub_image2_d      ()
//    {
//        glCopyTexSubImage2D();
//    }
//    void copy_tex_sub_image3_d      ()
//    {
//        glCopyTexSubImage3D();
//    }
//    void delete_transform_feedbacks ()
//    {
//        glDeleteTransformFeedbacks();
//    }
//    void disable_vertex_attrib_array()
//    {
//      glDisableVertexAttribArray();
//    }











    //glActiveShaderProgram;
    //glActiveTexture;
    //glAttachShader;
    //glBindAttribLocation
    //glBindBuffer
    //glBindTexture
    //glBindTextures
    //glBindTransformFeedback
    //glBindVertexBuffer
    //glBindVertexBuffers
    //glBufferData
    //glBufferSubData
    //glCheckFramebufferStatus
    //glClearBufferData
    //glClearBufferSubData
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
    //glDeleteTransformFeedbacks
    //glDisableVertexAttribArray
    //glDrawBuffer
    //glDrawBuffers
    //glEnableVertexAttribArray
    //glDrawTransformFeedback
    //glDrawTransformFeedbackInstanced
    //glDrawTransformFeedbackStream
    //glDrawTransformFeedbackStreamInstanced
    //glEndTransformFeedback
    //glFlushMappedBufferRange
    //glFramebufferParameteri
    //glFramebufferRenderbuffer
    //glFramebufferTexture
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
    //glGetActiveAttrib
    //glGetActiveUniform
    //glGetActiveUniformBlockName
    //glGetActiveUniformName
    //glGetActiveUniformsiv
    //glGetAttribLocation
    //glGetBufferParameteriv
    //glGetBufferPointerv
    //glGetBufferSubData
    //glGetCompressedTexImage
    //glGetError
    //glGetFragDataIndex
    //glGetFragDataLocation
    //glGetProgramResourceIndex
    //glGetProgramResourceLocation
    //glGetProgramResourceLocationIndex
    //glGetProgramResourceName
    //glGetTexImage
    //glGetTransformFeedbackVarying
    //glGetUniformBlockIndex
    //glGetUniformIndices
    //glGetUniformLocation
    //glHint
    //glInvalidateFramebuffer
    //glInvalidateSubFramebuffer

    //glMapBufferRange
    //glPolygonOffset
    //glReadBuffer
    //glReadPixels
    //glRenderbufferStorage
    //glRenderbufferStorageMultisample
    //glResumeTransformFeedback
    //glTexBuffer
    //glTexBufferRange //4.6?
    //glTexImage1D
    //glTexImage2D
    //glTexImage2DMultisample
    //glTexImage3D
    //glTexImage3DMultisample
    //glTexStorage1D
    //glTexStorage2D
    //glTexStorage2DMultisample
    //glTexStorage3D
    //glTexStorage3DMultisample
    //glTexSubImage1D
    //glTexSubImage2D
    //glTexSubImage3D
    //glTransformFeedbackBufferBase
    //glTransformFeedbackBufferRange
    //glTransformFeedbackVaryings
    //glUniformBlockBinding
    //glUnmapBuffer
    //glUseProgram
    //glVertexAttribBinding
    //glVertexAttribDivisor
    //glVertexAttribFormat
    //glVertexAttribPointer
    //glVertexBindingDivisor



    //?
    //glDrawArraysIndirect
    //glDrawElementsBaseVertex
    //glDrawElementsIndirect
    //glDrawElementsInstancedBaseVertex
    //glDrawElementsInstancedBaseVertexBaseInstance
    //glDrawRangeElements
    //glDrawRangeElementsBaseVertex



    //4.6
    //glBindFragDataLocation
    //glBindFragDataLocationIndexed
    //glBindImageTexture
    //glBindImageTextures
    //glGetActiveAtomicCounterBufferiv
    //glGetActiveSubroutineName        //Program introspection?
    //glGetActiveSubroutineUniform     //
    //glGetActiveSubroutineUniformName //
    //glGetCompressedTextureSubImage
    //glGetObjectLabel
    //glGetObjectPtrLabel
    //glGetProgramStage
    //glGetSubroutineIndex
    //glGetSubroutineUniformLocation
    //glMultiDrawArrays
    //glMultiDrawArraysIndirect
    //glMultiDrawElements
    //glMultiDrawElementsBaseVertex
    //glMultiDrawElementsIndirect
    //glPauseTransformFeedback
    //glShaderStorageBlockBinding



    //Not found
    //glBindRenderBuffer
    //glBlitFrameBuffer
    //glClearBuffer
    //glGet
    //glGetActiveUniformBlock
    //glGetBufferParameter
    //glGetFramebufferAttachmentParameter
    //glGetFramebufferParameter
    //glGetInternalformat
    //glGetProgramInterface
    //glGetProgramPipeline
    //glGetProgramResource
    //glGetRenderbufferParameter
    //glGetTexLevelParameter
    //glGetTexParameter
    //glGetTransformFeedback
    //glGetUniform
    //glGetUniformSubroutine
    //glGetVertexAttrib
    //glProgramUniform
    //glTexParameter
    //glUniform
    //glUniformSubroutines
    //glVertexAttrib
}
