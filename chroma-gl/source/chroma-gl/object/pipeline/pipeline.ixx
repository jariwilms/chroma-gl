export module opengl.object.pipeline;

import std;
import opengl;
import opengl.object;
import opengl.object.shader;

export namespace gl
{
    using pipeline_layout_t = std::unordered_map<gl::program_stage_e, std::shared_ptr<gl::shader>>;
    class pipeline : public gl::object
    {
    public:
        using stage_e  = gl::program_stage_e;
        using layout_t = gl::pipeline_layout_t;

        explicit
        pipeline(std::span<const std::shared_ptr<gl::shader>> shaders)
            : gl::object{ gl::create_pipeline() }
            , layout_{}
        {
            std::ranges::for_each(shaders, [&](std::shared_ptr<gl::shader> shader) { stage(shader); });
        }
        pipeline(pipeline&&) noexcept = default;
       ~pipeline()
        {
            gl::delete_pipeline(handle());
        }

        void bind     ()
        {
            gl::bind_pipeline(handle());
        }
        
        void stage    (std::shared_ptr<gl::shader> shader)
        {
            if (!shader) return;
            
            const auto program_stage = gl::map_program_stage(shader->type());
            layout_.insert_or_assign(program_stage, shader);
            gl::use_program_stage(handle(), shader->handle(), program_stage);
        }
        void unstage  (stage_e stage)
        {
            layout_.erase(stage);
        }

        auto layout   () const -> const layout_t&
        {
            return layout_;
        }
        auto layout   () -> layout_t&
        {
            return layout_;
        }

        auto operator=(pipeline&&) noexcept -> pipeline& = default;

    private:
        layout_t layout_;
    };
}
