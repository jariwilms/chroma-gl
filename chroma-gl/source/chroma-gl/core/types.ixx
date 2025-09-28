export module opengl.types;

import std;
import <glad/gl.h>;
import vendor.glm;

export namespace gl
{
    using void_t     = GLvoid      ;
    using bool_t     = bool        ; //Fundamental
    using boolean_t  = GLboolean   ; //Unsigned char
    using char_t     = GLchar      ;
    using byte_t     = GLubyte     ;

    using int8_t     = GLbyte      ;
    using uint8_t    = GLubyte     ;
    using int16_t    = GLshort     ;
    using uint16_t   = GLushort    ;
    using int32_t    = GLint       ;
    using uint32_t   = GLuint      ;
    using int64_t    = GLint64     ;
    using uint64_t   = GLuint64    ;
    using float16_t  = GLhalf      ;
    using float32_t  = GLfloat     ;
    using float64_t  = GLdouble    ;

    using enum_t     = GLenum      ; //Enumerated constant
    using sizei_t    = GLsizei     ; //Sizes and dimensions (non-negative)
    using size_t     = GLsizeiptr  ; //Number of bytes
    using offset_t   = GLintptr    ; //Number of bytes offset
    using count_t    = gl::uint32_t; //Number of elements
    using index_t    = gl::uint32_t; //Number of elements offset
    using sync_t     = GLsync      ; //Synchronization primitive
    using bitfield_t = GLbitfield  ; //Bitwise combination of flags
    using time_t     = gl::uint64_t; //Duration in nanoseconds

    using pointer_t  = gl::void_t* ; //Generic pointer type

    enum : gl::bool_t
    {
        false_ = GL_FALSE, 
        true_  = GL_TRUE , 
    };
    
    enum class handle_t             : gl::uint32_t;
    enum class binding_t            : gl::index_t ;
    enum class key_t                : gl::uint64_t;

    //enum class buffer_t             : std::underlying_type_t<gl::handle_t>;
    //enum class frame_buffer_t       : std::underlying_type_t<gl::handle_t>;
    //enum class program_t            : std::underlying_type_t<gl::handle_t>;
    //enum class pipeline_t           : std::underlying_type_t<gl::handle_t>;
    //enum class query_t              : std::underlying_type_t<gl::handle_t>;
    //enum class render_buffer_t      : std::underlying_type_t<gl::handle_t>;
    //enum class sampler_t            : std::underlying_type_t<gl::handle_t>;
    //enum class shader_t             : std::underlying_type_t<gl::handle_t>;
    //enum class shader_program_t     : std::underlying_type_t<gl::handle_t>;
    //enum class texture_t            : std::underlying_type_t<gl::handle_t>;
    //enum class texture_1d_t         : std::underlying_type_t<gl::handle_t>;
    //enum class texture_2d_t         : std::underlying_type_t<gl::handle_t>;
    //enum class texture_3d_t         : std::underlying_type_t<gl::handle_t>;
    //enum class transform_feedback_t : std::underlying_type_t<gl::handle_t>;
    //enum class vertex_array_t       : std::underlying_type_t<gl::handle_t>;



    template<typename... Ts>
    struct overload_t : Ts... { using Ts::operator()...; };



    template<typename T, gl::uint32_t N>
    using vector_t     = glm::vec<N, T, glm::packed_highp>;
    template<typename T, gl::uint32_t R, gl::uint32_t C = R>
    using matrix_t     = glm::mat<R, C, T>;
    template<typename T>
    using quaternion   = glm::qua<T, glm::packed_highp>;

    using vector1b     = gl::vector_t  <gl::boolean_t, 1u>;
    using vector2b     = gl::vector_t  <gl::boolean_t, 2u>;
    using vector3b     = gl::vector_t  <gl::boolean_t, 3u>;
    using vector4b     = gl::vector_t  <gl::boolean_t, 4u>;

    using vector1i     = gl::vector_t  <gl::int32_t  , 1u>;
    using vector2i     = gl::vector_t  <gl::int32_t  , 2u>;
    using vector3i     = gl::vector_t  <gl::int32_t  , 3u>;
    using vector4i     = gl::vector_t  <gl::int32_t  , 4u>;

    using vector1u     = gl::vector_t  <gl::uint32_t , 1u>;
    using vector2u     = gl::vector_t  <gl::uint32_t , 2u>;
    using vector3u     = gl::vector_t  <gl::uint32_t , 3u>;
    using vector4u     = gl::vector_t  <gl::uint32_t , 4u>;

    using vector1f     = gl::vector_t  <gl::float32_t, 1u>;
    using vector2f     = gl::vector_t  <gl::float32_t, 2u>;
    using vector3f     = gl::vector_t  <gl::float32_t, 3u>;
    using vector4f     = gl::vector_t  <gl::float32_t, 4u>;

    using vector1d     = gl::vector_t  <gl::float64_t, 1u>;
    using vector2d     = gl::vector_t  <gl::float64_t, 2u>;
    using vector3d     = gl::vector_t  <gl::float64_t, 3u>;
    using vector4d     = gl::vector_t  <gl::float64_t, 4u>;

    using matrix2f     = gl::matrix_t  <gl::float32_t, 2u>;
    using matrix3f     = gl::matrix_t  <gl::float32_t, 3u>;
    using matrix4f     = gl::matrix_t  <gl::float32_t, 4u>;

    using quaternion4f = gl::quaternion<gl::float32_t    >;

    auto value_pointer(auto value) -> auto*
    {
        return glm::value_ptr(value);
    }



    void _debug_callback(gl::enum_t, gl::enum_t, gl::uint32_t, gl::enum_t, gl::sizei_t, const gl::char_t*, const gl::void_t*);
    using debug_callback_t = decltype(_debug_callback);
}
