export module opengl.types;

import std;
import <glad/gl.h>;
import glm;

export namespace gl
{
    using bool_t                        = bool                         ;

    using void_t                        = ::GLvoid                     ;
    using boolean_t                     = ::GLboolean                  ;
    using byte_t                        = ::GLubyte                    ;
    using char_t                        = ::GLchar                     ;

    using int8_t                        = ::GLbyte                     ;
    using int16_t                       = ::GLshort                    ;
    using int32_t                       = ::GLint                      ;
    using int64_t                       = ::GLint64                    ;
    using uint8_t                       = ::GLubyte                    ;
    using uint16_t                      = ::GLushort                   ;
    using uint32_t                      = ::GLuint                     ;
    using uint64_t                      = ::GLuint64                   ;
    using float16_t                     = ::GLhalf                     ;
    using float32_t                     = ::GLfloat                    ;
    using float64_t                     = ::GLdouble                   ;

    using sizeu_t                       = ::GLuint                     ; //Unsigned 32-bit size-type
    using sizei_t                       = ::GLsizei                    ; //  Signed 32-bit size-type
    using size_t                        = ::khronos_usize_t            ; //Maximum possible size of an object on a given platform
    using count_t                       = ::khronos_usize_t            ; //Number of elements
    using index_t                       = ::khronos_usize_t            ; //Number of elements offset
    using sizeiptr_t                    = ::GLsizeiptr                 ; //Address pointer
    using intptr_t                      = ::GLintptr                   ; //Address pointer byte offset
    using ptrdiff_t                     = ::GLintptr                   ; //Address pointer byte offset alias
    
    using enum_t                        = ::GLenum                     ; //Enumeration constant
    using bitfield_t                    = ::GLbitfield                 ; //Combination of logical bits
    using sync_t                        = ::GLsync                     ; //Synchronization primitive
    using time_t                        = ::khronos_utime_nanoseconds_t; //Duration expressed in nanoseconds
    using c_string                      = ::GLchar const*              ; //Null-terminated character array
    
    using debug_callback_t              = gl::void_t(__stdcall*)(gl::enum_t, gl::enum_t, gl::uint32_t, gl::enum_t, gl::sizei_t, gl::c_string, const gl::void_t*);



    template<typename T, gl::uint32_t Components>
    using vector_t                      = glm::vec<Components, T, glm::packed_highp>;
    template<typename T, gl::uint32_t Rows, gl::uint32_t Columns = Rows>
    using matrix_t                      = glm::mat<Rows, Columns, T>;
    template<typename T>
    using quaternion_t                  = glm::qua<T, glm::packed_highp>;

    using vector_1b                     = gl::vector_t    <gl::boolean_t, 1u>;
    using vector_2b                     = gl::vector_t    <gl::boolean_t, 2u>;
    using vector_3b                     = gl::vector_t    <gl::boolean_t, 3u>;
    using vector_4b                     = gl::vector_t    <gl::boolean_t, 4u>;
    using vector_1i                     = gl::vector_t    <gl::int32_t  , 1u>;
    using vector_2i                     = gl::vector_t    <gl::int32_t  , 2u>;
    using vector_3i                     = gl::vector_t    <gl::int32_t  , 3u>;
    using vector_4i                     = gl::vector_t    <gl::int32_t  , 4u>;
    using vector_1u                     = gl::vector_t    <gl::uint32_t , 1u>;
    using vector_2u                     = gl::vector_t    <gl::uint32_t , 2u>;
    using vector_3u                     = gl::vector_t    <gl::uint32_t , 3u>;
    using vector_4u                     = gl::vector_t    <gl::uint32_t , 4u>;
    using vector_1f                     = gl::vector_t    <gl::float32_t, 1u>;
    using vector_2f                     = gl::vector_t    <gl::float32_t, 2u>;
    using vector_3f                     = gl::vector_t    <gl::float32_t, 3u>;
    using vector_4f                     = gl::vector_t    <gl::float32_t, 4u>;
    using vector_1d                     = gl::vector_t    <gl::float64_t, 1u>;
    using vector_2d                     = gl::vector_t    <gl::float64_t, 2u>;
    using vector_3d                     = gl::vector_t    <gl::float64_t, 3u>;
    using vector_4d                     = gl::vector_t    <gl::float64_t, 4u>;
    using matrix_2f                     = gl::matrix_t    <gl::float32_t, 2u>;
    using matrix_3f                     = gl::matrix_t    <gl::float32_t, 3u>;
    using matrix_4f                     = gl::matrix_t    <gl::float32_t, 4u>;
    using quaternion_4f                 = gl::quaternion_t<gl::float32_t    >;



    enum                                : gl::bool_t  { false_ = GL_FALSE, true_ = GL_TRUE, };
    enum class none_t                   : decltype(GL_NONE);
    enum class binding_t                : gl::uint32_t;
    enum class handle_t                 : gl::uint32_t;

    template<typename... Ts>
    struct overload_t : Ts... { using Ts::operator()...; };
}
