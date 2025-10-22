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

        sampler(const gl::sampler_state& sampler_state)
            : gl::object{ gl::create_sampler() }
        {
            apply(sampler_state);
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
        void apply(const gl::sampler_state& sampler_state)
        {
            using enum gl::sampler_parameter_e;

            apply<border_color        >(sampler_state.border_color        );
            apply<compare_mode        >(sampler_state.compare_mode        );
            apply<compare_function    >(sampler_state.compare_function    );
            apply<minification_filter >(sampler_state.minification_filter );
            apply<magnification_filter>(sampler_state.magnification_filter);
            apply<wrapping_s          >(sampler_state.wrapping_s          );
            apply<wrapping_t          >(sampler_state.wrapping_t          );
            apply<wrapping_r          >(sampler_state.wrapping_r          );
            apply<maximum_anisotropy  >(sampler_state.maximum_anisotropy  );
            apply<minimum_lod         >(sampler_state.minimum_lod         );
            apply<maximum_lod         >(sampler_state.maximum_lod         );
            apply<lod_bias            >(sampler_state.lod_bias            );
        }
    };
}
