export module opengl.object.pipeline;

import std;
import opengl;
import opengl.object;
import opengl.object.shader;

export namespace gl
{
    constexpr auto map_program_stage(gl::shader_type_e shader_type) -> gl::program_stage_e
    {
        switch (shader_type)
        {
            using enum gl::shader_type_e;

            case vertex                 : return gl::program_stage_e::vertex                 ;
            case tessellation_control   : return gl::program_stage_e::tessellation_control   ;
            case tessellation_evaluation: return gl::program_stage_e::tessellation_evaluation;
            case geometry               : return gl::program_stage_e::geometry               ;
            case fragment               : return gl::program_stage_e::fragment               ;
            case compute                : return gl::program_stage_e::compute                ;

            default                     : throw std::invalid_argument{ "invalid shader type" };
        }
    }

    class pipeline : gl::object
    {
    public:
        using stage_e  = gl::program_stage_e;
        using layout_t = std::unordered_map<stage_e, std::shared_ptr<gl::shader>>;

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
            gl::use_program_stages(handle(), shader->handle(), program_stage);
        }
        void unstage  (stage_e stage)
        {
            layout_.erase(stage);
        }

        auto layout   () const -> const layout_t&
        {
            return layout_;
        }

        auto operator=(pipeline&&) noexcept -> pipeline& = default;

    private:
        layout_t layout_;
    };
}
