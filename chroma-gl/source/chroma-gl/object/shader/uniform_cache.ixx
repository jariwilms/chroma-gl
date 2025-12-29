export module opengl.uniform_cache;

import std;
import opengl;

export namespace gl
{
    class uniform_cache
    {
    public:
        explicit
        uniform_cache(gl::handle_t shader)
        {
            const auto active_resources = gl::get_program_interface_value<gl::program_interface_parameter_e::active_resources>(shader, gl::program_interface_e::uniform);
            for (auto index = gl::index_t{ 0u }; index < active_resources; ++index)
            {
                const auto values       = gl::get_program_resource_value<
                    gl::program_resource_e::type         , 
                    gl::program_resource_e::location     , 
                    gl::program_resource_e::block_index  , 
                    gl::program_resource_e::array_size   , 
                    gl::program_resource_e::array_stride , 
                    gl::program_resource_e::matrix_stride, 
                    gl::program_resource_e::is_row_major >(shader, gl::program_interface_e::uniform, index);

                const auto uniform_name = gl::get_program_resource_name(shader, gl::program_interface_e::uniform, index);
                uniforms_[uniform_name] = gl::uniform_info
                {
                    .name          = uniform_name                               , 
                    .type          = static_cast<gl::uniform_type_e>(values[0u]), 
                    .location      = static_cast<gl::index_t       >(values[1u]), 
                    .block_index   = static_cast<gl::index_t       >(values[2u]), 
                    .array_size    = static_cast<gl::size_t        >(values[3u]), 
                    .array_stride  = static_cast<gl::size_t        >(values[4u]), 
                    .matrix_stride = static_cast<gl::size_t        >(values[5u]), 
                    .is_row_major  = static_cast<gl::bool_t        >(values[6u]), 
                };
            }
        }

    private:
        std::unordered_map<std::string, gl::uniform_info> uniforms_;
    };
}
