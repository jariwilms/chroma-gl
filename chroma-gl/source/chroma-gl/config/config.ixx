export module chroma_gl:config;

import opengl;

export namespace gl::config
{
    enum class build_configuration_e
    {
        debug  , 
        release, 
    };

    auto constexpr version_major          = gl::uint32_t{ 4u };
    auto constexpr version_minor          = gl::uint32_t{ 6u };
    auto constexpr build_configuration    = config::build_configuration_e::BUILD_CONFIGURATION;
    auto constexpr spir_v                 = gl::true_;
    auto constexpr flip_images_vertically = gl::true_;
}