export module opengl.config;

import opengl.types;

export namespace gl::config
{
    enum class build_configuration_e
    {
        debug  , 
        release, 
    };

    constexpr auto flip_images         = gl::true_;
    constexpr auto build_configuration = config::build_configuration_e::BUILD_CONFIGURATION;
}