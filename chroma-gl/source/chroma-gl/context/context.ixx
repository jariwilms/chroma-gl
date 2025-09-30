export module opengl.context;

import std;
import opengl;

       namespace gl
{
    struct context
    {
        gl::context_flags_e   flags                    = {};
        gl::context_profile_e profile                  = {};
        gl::uint32_t          major_version            = {};
        gl::uint32_t          minor_version            = {};
        std::string           vendor                   = {};
        std::string           renderer                 = {};
        std::string           version                  = {};
        std::string           shading_language_version = {};
    };

    auto context_ = gl::context{};
}
export namespace gl
{
    void create_context()
    {
        static auto once_flag = gl::false_;
        if (once_flag) return;
        
        auto& context = gl::context_;

        context.flags                    = gl::get_value <gl::data_e            ::context_flags           >();
        context.profile                  = gl::get_value <gl::data_e            ::context_profile_mask    >();
        context.major_version            = gl::get_value <gl::data_e            ::major_version           >();
        context.minor_version            = gl::get_value <gl::data_e            ::minor_version           >();
        context.vendor                   = gl::get_string<gl::context_property_e::vendor                  >();
        context.renderer                 = gl::get_string<gl::context_property_e::renderer                >();
        context.version                  = gl::get_string<gl::context_property_e::version                 >();
        context.shading_language_version = gl::get_string<gl::context_property_e::shading_language_version>();

        if (gl::to_underlying(context.flags & gl::context_flags_e::debug))
        {
            gl::enable<gl::feature_e::debug_output            >();
            gl::enable<gl::feature_e::debug_output_synchronous>();

            gl::debug_message_control (gl::debug_source_e::dont_care, gl::debug_type_e::dont_care, gl::debug_severity_e::dont_care, gl::true_);
            gl::debug_message_callback([](gl::enum_t source, gl::enum_t type, gl::uint32_t id, gl::enum_t severity, gl::sizei_t, const gl::char_t* message, const gl::void_t* const)
                {
                          auto map_source_message     = [](gl::debug_source_e   source    )
                        {
                            switch (source)
                            {
                                case gl::debug_source_e::api            : return "API";
                                case gl::debug_source_e::window_system  : return "Window System";
                                case gl::debug_source_e::shader_compiler: return "Shader Compiler";
                                case gl::debug_source_e::third_party    : return "Third Party";
                                case gl::debug_source_e::application    : return "Application";
                                case gl::debug_source_e::other          : return "Other";

                                default: throw std::invalid_argument{ "Invalid source!" };
                            }
                        };
                          auto map_severity_message   = [](gl::debug_severity_e severity  )
                        {
                            switch (severity)
                            {
                                case gl::debug_severity_e::high        : return "High";
                                case gl::debug_severity_e::medium      : return "Medium";
                                case gl::debug_severity_e::low         : return "Low";
                                case gl::debug_severity_e::notification: return "Notification";

                                default: throw std::invalid_argument{ "Invalid severity!" };
                            }
                        };
                          auto map_debug_type_message = [](gl::debug_type_e     debug_type)
                        {
                            switch (debug_type)
                            {
                                using enum gl::debug_type_e;

                                case error              : return "Error";
                                case deprecated_behavior: return "Deprecated Behavior";
                                case undefined_behavior : return "Undefined Behavior";
                                case portability        : return "Portability";
                                case performance        : return "Performance";
                                case marker             : return "Marker";
                                case push_group         : return "Push Group";
                                case pop_group          : return "Pop Group";
                                case other              : return "Other";
                                default: throw std::invalid_argument{ "Invalid type!" };
                            }
                        };

                    const auto source_e               = std::bit_cast<gl::debug_source_e  >(source  );
                    const auto severity_e             = std::bit_cast<gl::debug_severity_e>(severity);
                    const auto type_e                 = std::bit_cast<gl::debug_type_e    >(type    );

                    const auto source_message         = map_source_message    (source_e  );
                    const auto severity_message       = map_severity_message  (severity_e);
                    const auto type_message           = map_debug_type_message(type_e    );

                    if (severity_e == gl::debug_severity_e::notification) return;
                    if (severity_e == gl::debug_severity_e::low         ) return;

                    std::print("@GL_DEBUG [{0}] Type::{1}; Source::{2}; Severity::{3}; Message::{4}", id, type_message, source_message, severity_message, message);
                });
        }

        once_flag = gl::true_;
    }   
    auto get_context() -> const gl::context&
    {
        return gl::context_;
    }
}
