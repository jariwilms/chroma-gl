export module opengl.config;

import opengl.types;

export namespace gl::config
{
    enum class build_configuration_e
    {
        debug  , 
        release, 
    };

    constexpr auto version_major          = gl::uint32_t{ 4u };
    constexpr auto version_minor          = gl::uint32_t{ 6u };
    constexpr auto build_configuration    = config::build_configuration_e::BUILD_CONFIGURATION;
    constexpr auto flip_images_vertically = gl::true_;
}