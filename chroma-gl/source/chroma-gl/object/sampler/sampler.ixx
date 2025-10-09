export module opengl.object.sampler;
//
//import opengl;
//import opengl.object;
//import opengl.object.texture;
//
//export namespace gl
//{
//	class sampler : public gl::object
//	{
//	public:
//		using parameter_e = gl::sampler_parameter_e;
//
//		sampler()
//			: gl::object{ gl::create_sampler(), [](auto* handle) { gl::delete_sampler(*handle); } }
//		{
//			gl::todo();
//		}
//
//		void bind(gl::binding_t slot)
//		{
//			gl::bind_sampler(handle(), slot);
//		}
//	};
//}
