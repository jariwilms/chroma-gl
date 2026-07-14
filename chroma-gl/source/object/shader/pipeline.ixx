export module chroma_gl:object.pipeline;

import std;
import opengl;
import :object;
import :object.shader;

export namespace gl
{
    class pipeline : public gl::object
    {
    public:
        using stage_e = gl::program_stage_e;

        pipeline()
            : gl::object{ gl::create_pipeline() } {}
        explicit
        pipeline(std::span<std::shared_ptr<gl::shader> const> shaders)
            : pipeline{}
        {
            std::ranges::for_each(shaders, [&](auto shader) { link(shader); });
        }
        pipeline(pipeline&&) noexcept = default;
       ~pipeline()
        {
            gl::delete_pipeline(handle());
        }

        void bind  ()
        {
            gl::bind_pipeline(handle());
        }
        void link  (std::shared_ptr<gl::shader> shader)
        {
            auto const program_stage = gl::map_program_stage(shader->type());
            gl::use_program_stage(handle(), shader->handle(), program_stage);
            shaders_.emplace(shader->type(), shader);
        }
        void unlink(stage_e program_stage)
        {
            gl::use_program_stage(handle(), gl::null_object, program_stage);
        }

        auto stage (this auto&& self, stage_e stage) -> auto&&
        {
            return shaders_.at(stage);
        }

        auto operator=(pipeline&&) noexcept -> pipeline& = default;

    private:
        std::unordered_map<gl::shader::type_e, std::shared_ptr<gl::shader>> shaders_;
    };
}
