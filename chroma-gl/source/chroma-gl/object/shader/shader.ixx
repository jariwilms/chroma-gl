export module chroma_gl:object.shader;

import std;
import opengl;
import :config;
import :object;

export namespace gl
{
    class shader : public gl::object
    {
    public:
        using type_e = gl::shader_type_e;

        explicit
        shader(type_e type, const std::string& entry_point, std::span<const gl::byte_t> binary)
            : gl::object{ gl::create_program() }
            , type_{ type }
        {
            gl::program_parameter<gl::program_specification_e::separable>(handle(), gl::true_);

            const auto shader         = gl::create_shader(type_);
            gl::shader_binary    (shader, gl::shader_binary_format_e::spir_v, binary);
            gl::specialize_shader(shader, entry_point);

            const auto compile_status = gl::get_shader_value<gl::shader_parameter_e::compile_status>(shader);
            if (compile_status != gl::true_) throw std::runtime_error{ gl::get_shader_info_log(shader) };
            
            gl::attach_shader(handle(), shader);
            gl::link_program (handle()        );

            const auto link_status    = gl::get_program_value<gl::program_parameter_e::link_status>(handle());
            if (link_status != gl::true_) throw std::runtime_error{ gl::get_program_info_log(handle()) };

            gl::detach_shader(handle(), shader);
            gl::delete_shader(          shader);
        }
        shader(shader&&) noexcept = default;
       ~shader()
        {
            gl::delete_program(handle());
        }

        template<typename T>
        void upload(gl::index_t location, const T& value)
        {
            gl::program_uniform(handle(), location, value);
        }

        auto type() const -> type_e
        {
            return type_;
        }

        auto operator=(shader&&) noexcept -> shader& = default;

    private:
        type_e type_;
    };
}
