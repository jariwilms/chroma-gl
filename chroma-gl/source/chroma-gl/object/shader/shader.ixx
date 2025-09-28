export module opengl.object.shader;

import std;
import <glad/gl.h>;
import opengl;

export namespace gl
{
    class shader : public gl::object
    {
    public:
        using type_e = gl::shader_type_e;

        shader(type_e type, std::span<const gl::byte_t> binary)
            : gl::object{ gl::create_program(), [](auto* handle) { gl::delete_program(*handle); }}
            , type_{ type }
        {
            auto shader = gl::create_shader(type);

            gl::program_parameter<gl::program_specification_e::separable>(handle(), gl::true_);
            gl::shader_binary    (shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary);
            gl::specialize_shader(shader, "main");

            const auto compile_status = gl::get_shader_value<gl::shader_parameter_e::compile_status>(shader);
            if (compile_status != gl::true_) throw std::runtime_error{ gl::get_shader_info_log(shader) };
            
            gl::attach_shader(handle(), shader);
            gl::link_program (handle()        );

            const auto link_status = gl::get_program_value<gl::program_parameter_e::link_status>(handle());
            if (link_status != gl::true_) throw std::runtime_error{ gl::get_program_info_log(handle()) };

            gl::detach_shader(handle(), shader);
            gl::delete_shader(          shader);
        }

        auto type() const -> type_e
        {
            return type_;
        }

    private:
        type_e type_;
    };
}
