export module opengl.config;

export namespace gl::config
{
    enum class build_configuration_e
    {
        debug  , 
        release, 
    };

    constexpr auto build_configuration = config::build_configuration_e::BUILD_CONFIGURATION;
}