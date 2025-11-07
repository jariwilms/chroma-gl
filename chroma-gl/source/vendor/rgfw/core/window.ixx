export module vendor.rgfw.window;

import std;
import opengl.config;
import vendor.glad;
import vendor.rgfw.flags;
import vendor.rgfw.functions;
import vendor.rgfw.input;
import vendor.rgfw.structures;
import vendor.rgfw.types;

export namespace rgfw
{
    enum class window_display_mode_e
    {
        windowed  , 
        borderless, 
        fullscreen, 
    };

    class window
    {
    public:
        using display_mode_e = rgfw::window_display_mode_e;

        explicit
        window(const std::string& title, const rgfw::vector_2u& dimensions, display_mode_e display_mode = display_mode_e::windowed)
            : window_{}, title_{ title }, dimensions_{ dimensions }, display_mode_{ display_mode }
        {
            auto const is_debug_context = static_cast<rgfw::bool_t>(gl::config::build_configuration == gl::config::build_configuration_e::debug);
            auto       gl_hints         = rgfw::gl_hints
            {
                .double_buffer = rgfw::true_                     , 
                .debug         = is_debug_context                , 
                .profile       = rgfw::gl_profile_e::core        , 
                .major         = rgfw::int32_t{ 4 }              , 
                .minor         = rgfw::int32_t{ 6 }              , 
                .renderer      = rgfw::gl_renderer_e::accelerated, 
            };

            auto const window_flags     = 
                rgfw::window_flags_e::center           | 
                rgfw::window_flags_e::hide             | 
                rgfw::window_flags_e::scale_to_monitor | 
                rgfw::window_flags_e::opengl           ;
            window_                     = rgfw::create_window(title_, {}, dimensions, window_flags);
            input_                      = std::make_shared<rgfw::input>();
            if (!window_                                     ) throw std::runtime_error{ "failed to create window"   };
            if (!glad::initialize(RGFW_getProcAddress_OpenGL)) throw std::runtime_error{ "failed to initialize glad" };
            
            rgfw::window_show(window_);
        }

        void rename        (std::string     const& title     )
        {
            rgfw::window_set_title(window_, title);
        }
        void resize        (rgfw::vector_2u const& dimensions)
        {
            rgfw::window_resize(window_, dimensions);
        }
        void process_events()
        {
            auto event = rgfw::event{};
            while (rgfw::window_check_event(window_, &event))
            {
                if (event.type == rgfw::event_type_e::none) continue;

                switch (event.type)
                {
                    using enum rgfw::event_type_e;

                    case data_drag             : break;
                    case data_drop             : break;
                    case focus_in              : break;
                    case focus_out             : break;
                    case key_pressed           : input_->process(event);
                    case key_released          : input_->process(event);
                    case mouse_button_pressed  : input_->process(event);
                    case mouse_button_released : input_->process(event);
                    case mouse_enter           : input_->process(event);
                    case mouse_leave           : input_->process(event);
                    case mouse_position_changed: input_->process(event);
                    case mouse_scroll          : input_->process(event);
                    case none                  : break;
                    case quit                  : break;
                    case scale_updated         : break;
                    case window_maximized      : break;
                    case window_minimized      : break;
                    case window_moved          : break;
                    case window_refresh        : break;
                    case window_resized        : 
                    {
                        dimensions_ = rgfw::window_get_dimensions(window_);
                        break;
                    }
                    case window_restored       : break;

                    default                    : throw std::invalid_argument{ "invalid event type" };
                }
            }
        }
        void swap_buffers  ()
        {
            rgfw::window_swap_buffers(window_);
        }
        void close         ()
        {
            rgfw::window_close(window_);
        }

        auto title         () const -> const std::string&
        {
            return title_;
        }
        auto dimensions    () const -> const rgfw::vector_2u&
        {
            return dimensions_;
        }
        auto display_mode  () const -> display_mode_e
        {
            return display_mode_;
        }
        auto should_close  () const -> rgfw::bool_t
        {
            return rgfw::window_should_close(window_);
        }
        auto input_handler () const -> std::shared_ptr<const rgfw::input>
        {
            return input_;
        }
        auto native_handle () -> rgfw::window_t*
        {
            return window_;
        }

    private:
        rgfw::window_t*              window_;
        std::shared_ptr<rgfw::input> input_;
        std::string                  title_;
        rgfw::vector_2u              dimensions_;
        display_mode_e               display_mode_;
    };
}
