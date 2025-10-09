export module opengl.object.pipeline;
//
//import std;
//import opengl;
//import opengl.object;
//import opengl.object.mapping;
//import opengl.object.shader;
//
//export namespace gl
//{
//    class pipeline : public gl::object
//    {
//    public:
//        struct layout
//        {
//            std::shared_ptr<gl::shader> vertex                 {};
//            std::shared_ptr<gl::shader> tessellation_control   {};
//            std::shared_ptr<gl::shader> tessellation_evaluation{};
//            std::shared_ptr<gl::shader> geometry               {};
//            std::shared_ptr<gl::shader> fragment               {};
//        };
//
//        explicit pipeline(const layout& layout)
//            : gl::object{ gl::create_program_pipeline(), [](auto* handle) { gl::delete_program_pipeline(*handle); }}
//            , layout_{ layout }
//        {
//            if (auto shader = layout_.vertex                 ; shader) gl::use_program_stages(handle(), shader->handle(), gl::map_program_stage(shader->type()));
//            if (auto shader = layout_.tessellation_control   ; shader) gl::use_program_stages(handle(), shader->handle(), gl::map_program_stage(shader->type()));
//            if (auto shader = layout_.tessellation_evaluation; shader) gl::use_program_stages(handle(), shader->handle(), gl::map_program_stage(shader->type()));
//            if (auto shader = layout_.geometry               ; shader) gl::use_program_stages(handle(), shader->handle(), gl::map_program_stage(shader->type()));
//            if (auto shader = layout_.fragment               ; shader) gl::use_program_stages(handle(), shader->handle(), gl::map_program_stage(shader->type()));
//        }
//
//        void bind()
//        {
//            gl::bind_program_pipeline(handle());
//        }
//
//    private:
//        layout layout_;
//    };
//}
