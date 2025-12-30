export module chroma_gl:object.sampler;

import std;
import opengl;
import :object;
import :object.texture;

export namespace gl
{
    class sampler : public gl::object
    {
    public:
        using parameter_e = gl::sampler_parameter_e;

        explicit
        sampler(const gl::state::sampler& state)
            : gl::object{ gl::create_sampler() }
        {
            apply(state);
        }
       ~sampler()
        {
            gl::delete_sampler(handle());
        }

        void bind (gl::binding_t slot)
        {
            gl::bind_sampler(handle(), slot);
        }

        template<gl::sampler_parameter_e Parameter>
        void apply(auto value)
        {
            gl::sampler_parameter<Parameter>(handle(), value);
        }
        void apply(const gl::state::sampler& state)
        {
            apply<gl::sampler_parameter_e::border_color        >(state.border_color        );
            apply<gl::sampler_parameter_e::compare_mode        >(state.compare_mode        );
            apply<gl::sampler_parameter_e::compare_function    >(state.compare_function    );
            apply<gl::sampler_parameter_e::minification_filter >(state.minification_filter );
            apply<gl::sampler_parameter_e::magnification_filter>(state.magnification_filter);
            apply<gl::sampler_parameter_e::wrapping_s          >(state.wrapping_s          );
            apply<gl::sampler_parameter_e::wrapping_t          >(state.wrapping_t          );
            apply<gl::sampler_parameter_e::wrapping_r          >(state.wrapping_r          );
            apply<gl::sampler_parameter_e::maximum_anisotropy  >(state.maximum_anisotropy  );
            apply<gl::sampler_parameter_e::minimum_lod         >(state.minimum_lod         );
            apply<gl::sampler_parameter_e::maximum_lod         >(state.maximum_lod         );
            apply<gl::sampler_parameter_e::lod_bias            >(state.lod_bias            );
        }
    };
}
