export module opengl.legacy;
export import opengl.flags;
export import opengl.types;

import std;
import <glad/gl.h>;

export namespace gl::legacy
{
    auto get_error() -> gl::error_flag_e
    {
        return static_cast<gl::error_flag_e>(::glGetError());
    }
    auto is_sync(gl::sync_t sync) -> gl::bool_t
    {
        return static_cast<gl::bool_t>(::glIsSync(sync));
    }

    //glActiveShaderProgram;
    //glActiveTexture;
    //glAttachShader;
    //glBindAttribLocation
    //glBindBuffer
    //glBindRenderBuffer
    //glBindTexture
    //glBindTextures
    //glBindTransformFeedback
    //glBindVertexBuffer
    //glBindVertexBuffers
    //glBlitFrameBuffer
    //glBufferData
    //glBufferSubData
    //glCheckFramebufferStatus
    //glClearBuffer
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
    //glGet
    //glGetActiveAttrib
    //glGetActiveUniform
    //glGetActiveUniformBlock
    //glGetActiveUniformBlockName
    //glGetActiveUniformName
    //glGetActiveUniformsiv
    //glGetAttribLocation
    //glGetBufferParameter
    //glGetBufferParameteriv
    //glGetBufferPointerv
    //glGetBufferSubData
    //glGetCompressedTexImage
    //glGetError
    //glGetFragDataIndex
    //glGetFragDataLocation
    //glGetFramebufferAttachmentParameter
    //glGetFramebufferParameter
    //glGetInternalformat
    //glGetProgramInterface
    //glGetProgramPipeline
    //glGetProgramResource
    //glGetProgramResourceIndex
    //glGetProgramResourceLocation
    //glGetProgramResourceLocationIndex
    //glGetProgramResourceName
    //glGetRenderbufferParameter
    //glGetTexImage
    //glGetTexLevelParameter
    //glGetTexParameter
    //glGetTransformFeedback
    //glGetTransformFeedbackVarying
    //glGetUniform
    //glGetUniformBlockIndex
    //glGetUniformIndices
    //glGetUniformLocation
    //glGetUniformSubroutine
    //glGetVertexAttrib
    //glHint
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
    //glMapBufferRange
    //glPolygonOffset
    //glProgramUniform
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
    //glTexParameter
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
    //glUniform
    //glUniformBlockBinding
    //glUniformSubroutines
    //glUnmapBuffer
    //glUseProgram
    //glVertexAttrib
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
}
