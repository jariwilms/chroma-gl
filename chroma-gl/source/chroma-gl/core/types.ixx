export module opengl.types;

import std;
import <glad/gl.h>;
import vendor.glm;

export namespace gl
{
    using void_t                        = ::GLvoid                     ;
    using bool_t                        = bool                         ;
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

    using sizeu_t                       = ::GLuint                     ;
    using sizei_t                       = ::GLsizei                    ;
    using size_t                        = ::khronos_usize_t            ;
    using count_t                       = ::GLuint                     ; //Number of elements
    using index_t                       = ::GLuint                     ; //Number of elements offset
    using ptrdiff_t                     = ::GLsizeiptr                 ; //Address pointer
    using intptr_t                      = ::GLintptr                   ; //Address pointer offset
    
    using enum_t                        = ::GLenum                     ; //Enumeration constant
    using bitfield_t                    = ::GLbitfield                 ; //Combination of logical bits
    using sync_t                        = ::GLsync                     ; //Synchronization primitive
    using time_t                        = ::khronos_utime_nanoseconds_t; //Duration expressed in nanoseconds

    template<typename T, gl::uint32_t Count>
    using vector_t                      = glm::vec<Count, T, glm::packed_highp>;
    template<typename T, gl::uint32_t Rows, gl::uint32_t Columns = Rows>
    using matrix_t                      = glm::mat<Rows, Columns, T>;
    template<typename T>
    using quaternion_t                  = glm::qua<T, glm::packed_highp>;

    using vector1b                      = gl::vector_t    <gl::boolean_t, 1u>;
    using vector2b                      = gl::vector_t    <gl::boolean_t, 2u>;
    using vector3b                      = gl::vector_t    <gl::boolean_t, 3u>;
    using vector4b                      = gl::vector_t    <gl::boolean_t, 4u>;
    using vector1i                      = gl::vector_t    <gl::int32_t  , 1u>;
    using vector2i                      = gl::vector_t    <gl::int32_t  , 2u>;
    using vector3i                      = gl::vector_t    <gl::int32_t  , 3u>;
    using vector4i                      = gl::vector_t    <gl::int32_t  , 4u>;
    using vector1u                      = gl::vector_t    <gl::uint32_t , 1u>;
    using vector2u                      = gl::vector_t    <gl::uint32_t , 2u>;
    using vector3u                      = gl::vector_t    <gl::uint32_t , 3u>;
    using vector4u                      = gl::vector_t    <gl::uint32_t , 4u>;
    using vector1f                      = gl::vector_t    <gl::float32_t, 1u>;
    using vector2f                      = gl::vector_t    <gl::float32_t, 2u>;
    using vector3f                      = gl::vector_t    <gl::float32_t, 3u>;
    using vector4f                      = gl::vector_t    <gl::float32_t, 4u>;
    using vector1d                      = gl::vector_t    <gl::float64_t, 1u>;
    using vector2d                      = gl::vector_t    <gl::float64_t, 2u>;
    using vector3d                      = gl::vector_t    <gl::float64_t, 3u>;
    using vector4d                      = gl::vector_t    <gl::float64_t, 4u>;
    using matrix2f                      = gl::matrix_t    <gl::float32_t, 2u>;
    using matrix3f                      = gl::matrix_t    <gl::float32_t, 3u>;
    using matrix4f                      = gl::matrix_t    <gl::float32_t, 4u>;
    using quaternion4f                  = gl::quaternion_t<gl::float32_t    >;

    using string                        = std::string;
    using c_string                      = const gl::char_t*;
    template<typename T>
    using vector                        = std::vector<T>;

    enum                                : gl::bool_t  { false_ = GL_FALSE, true_ = GL_TRUE, };
    enum class binding_t                : gl::uint32_t;
    enum class key_t                    : gl::uint64_t;

    enum class handle_t                 : gl::uint32_t;
    enum class texture_t                : std::underlying_type_t<gl::handle_t>;
    enum class vertex_array_t           : std::underlying_type_t<gl::handle_t>;
    enum class buffer_t                 : std::underlying_type_t<gl::handle_t>;
    enum class shader_t                 : std::underlying_type_t<gl::handle_t>;
    enum class program_t                : std::underlying_type_t<gl::handle_t>;
    enum class query_t                  : std::underlying_type_t<gl::handle_t>;
    enum class program_pipeline_t       : std::underlying_type_t<gl::handle_t>;
    enum class sampler_t                : std::underlying_type_t<gl::handle_t>;
    enum class frame_buffer_t           : std::underlying_type_t<gl::handle_t>;
    enum class render_buffer_t          : std::underlying_type_t<gl::handle_t>;
    enum class transform_feedback_t     : std::underlying_type_t<gl::handle_t>;



    auto value_pointer(auto value) -> auto*
    {
        return glm::value_ptr(value);
    }

    using debug_callback_t = gl::void_t(__stdcall*)(gl::enum_t source, gl::enum_t type, gl::uint32_t id, gl::enum_t severity, gl::sizei_t length, gl::c_string message, const gl::void_t* user_parameter);
}
