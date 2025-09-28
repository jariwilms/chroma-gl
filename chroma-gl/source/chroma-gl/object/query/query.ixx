export module opengl.object.query;

import std;
import opengl;
import opengl.object;

export namespace gl
{
	class query : public gl::object
	{
	public:
		using target_e = gl::query_target_e;
        
		explicit query(target_e target)
			: gl::object{ gl::create_query(target), [](auto* handle) { gl::delete_query(*handle); }}
			, target_   { target }
		{
			gl::todo();
		}

		auto target() const -> target_e
		{
			return target_;
		}

	private:
		target_e target_;
	};
}
