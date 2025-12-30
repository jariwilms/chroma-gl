export module opengl.object.sampler;

import std;
import opengl;
import opengl.object;
import opengl.object.texture;

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
            using enum gl::sampler_parameter_e;

            apply<border_color        >(state.border_color        );
            apply<compare_mode        >(state.compare_mode        );
            apply<compare_function    >(state.compare_function    );
            apply<minification_filter >(state.minification_filter );
            apply<magnification_filter>(state.magnification_filter);
            apply<wrapping_s          >(state.wrapping_s          );
            apply<wrapping_t          >(state.wrapping_t          );
            apply<wrapping_r          >(state.wrapping_r          );
            apply<maximum_anisotropy  >(state.maximum_anisotropy  );
            apply<minimum_lod         >(state.minimum_lod         );
            apply<maximum_lod         >(state.maximum_lod         );
            apply<lod_bias            >(state.lod_bias            );
        }
    };
}
