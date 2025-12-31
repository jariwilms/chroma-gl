export module opengl:legacy;
export import :flags;
export import :types;

import std;
import <glad/gl.h>;

namespace gl
{
    template<typename element_t, gl::size_t count_v>
    struct value_traits
    {
        using type = std::array<element_t, count_v>;
    };
    template<typename element_t>
    struct value_traits<element_t, 1u>
    {
        using type = element_t;
    };
    template<typename element_t, gl::size_t count_v>
    using value_traits_t = value_traits<element_t, count_v>::type;

    template<typename data_t, gl::size_t count_v>
    auto value_pointer(gl::value_traits_t<data_t, count_v>& value) -> data_t*
    {
        if   constexpr (count_v == 1u) return std::addressof(value);
        else                           return value.data();
    }
}
export namespace gl::legacy
{
    template<gl::size_t count_v = 1u>
    auto get_bool_value       (gl::data_e data, std::optional<gl::index_t> index = std::nullopt) -> gl::value_traits_t<gl::boolean_t, count_v>
    {
        auto value = gl::value_traits_t<gl::boolean_t, count_v>{};
        if   (index.has_value()) ::glGetBooleani_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index.value()), gl::value_pointer<gl::boolean_t, count_v>(value));
        else                     ::glGetBooleanv  (gl::to_underlying(data),                                           gl::value_pointer<gl::boolean_t, count_v>(value));

        return value;
    }
    template<gl::size_t count_v = 1u>
    auto get_int_value        (gl::data_e data, std::optional<gl::index_t> index = std::nullopt) -> gl::value_traits_t<gl::int32_t, count_v>
    {
        auto value = gl::value_traits_t<gl::int32_t, count_v>{};
        if   (index.has_value()) ::glGetIntegeri_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index.value()), gl::value_pointer<gl::int32_t, count_v>(value));
        else                     ::glGetIntegerv  (gl::to_underlying(data),                                           gl::value_pointer<gl::int32_t, count_v>(value));

        return value;
    }
    template<gl::size_t count_v = 1u>
    auto get_int64_value      (gl::data_e data, std::optional<gl::index_t> index = std::nullopt) -> gl::value_traits_t<gl::int64_t, count_v>
    {
        auto value = gl::value_traits_t<gl::int64_t, count_v>{};
        if   (index.has_value()) ::glGetInteger64i_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index.value()), gl::value_pointer<gl::int64_t, count_v>(value));
        else                     ::glGetInteger64v  (gl::to_underlying(data),                                           gl::value_pointer<gl::int64_t, count_v>(value));

        return value;
    }
    template<gl::size_t count_v = 1u>
    auto get_float_value      (gl::data_e data, std::optional<gl::index_t> index = std::nullopt) -> gl::value_traits_t<gl::float32_t, count_v>
    {
        auto value = gl::value_traits_t<gl::float32_t, count_v>{};
        if (index.has_value()) ::glGetFloati_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index.value()), gl::value_pointer<gl::float32_t, count_v>(value));
        else                   ::glGetFloatv  (gl::to_underlying(data),                                           gl::value_pointer<gl::float32_t, count_v>(value));

        return value;
    }
    template<gl::size_t count_v = 1u>
    auto get_float64_value    (gl::data_e data, std::optional<gl::index_t> index = std::nullopt) -> gl::value_traits_t<gl::float64_t, count_v>
    {
        auto value = gl::value_traits_t<gl::float64_t, count_v>{};
        if (index.has_value()) ::glGetDoublei_v(gl::to_underlying(data), static_cast<gl::uint32_t>(index.value()), gl::value_pointer<gl::float64_t, count_v>(value));
        else                   ::glGetDoublev  (gl::to_underlying(data),                                           gl::value_pointer<gl::float64_t, count_v>(value));

        return value;
    }

    auto is_buffer            (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsBuffer(std::to_underlying(handle));
    }
    auto is_framebuffer       (gl::handle_t handle) -> gl::bool_t
    {
        return ::glIsFramebuffer(std::to_underlying(handle));
    }
    auto is_program           (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsProgram(std::to_underlying(handle));
    }
    auto is_program_pipeline  (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsProgramPipeline(std::to_underlying(handle));
    }
    auto is_query             (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsQuery(std::to_underlying(handle));
    }
    auto is_renderbuffer      (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsRenderbuffer(std::to_underlying(handle));
    }
    auto is_sampler           (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsSampler(std::to_underlying(handle));
    }
    auto is_shader            (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsShader(std::to_underlying(handle));
    }
    auto is_texture           (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsTexture(std::to_underlying(handle));
    }
    auto is_transform_feedback(gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsTransformFeedback(std::to_underlying(handle));
    }
    auto is_vertex_array      (gl::handle_t handle) -> gl::bool_t 
    {
        return ::glIsVertexArray(std::to_underlying(handle));
    }
    auto is_sync              (gl::sync_t   sync  ) -> gl::bool_t 
    {
        return ::glIsSync(sync);
    }

    auto get_error            () -> gl::error_flag_e
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
