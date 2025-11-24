export module opengl.context;

import std;
import opengl;

export namespace gl
{
    struct context
    {
        gl::context_flags_e      flags;
        gl::context_profile_e    profile;
        gl::uint32_t             major_version;
        gl::uint32_t             minor_version;
        std::string              vendor;
        std::string              renderer;
        std::string              version;
        std::string              shading_language_version;
        std::vector<std::string> extensions;
    };
}
