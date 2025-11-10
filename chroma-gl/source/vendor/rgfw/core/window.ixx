export module rgfw:window    ;

import std;
import glad;
import opengl.config;
import :flags;
import :functions;
import :input;
import :structures;
import :types;

export namespace rgfw
{
    enum class window_display_mode_e
    {
        windowed  , 
        borderless, 
        fullscreen, 
    };
    enum class window_create_flags_e
    {
        allow_drag_and_drop, 
        borderless         , 
        center             , 
        center_cursor      , 
        floating           , 
        focus              , 
        focus_on_show      , 
        fullscreen         , 
        hidden             , 
        hide_mouse         , 
        maximize           , 
        minimize           , 
        no_border          , 
        no_resize          , 
        scale_to_monitor   , 
        transparent        , 
    };

    class window
    {
    public:
        using display_mode_e = rgfw::window_display_mode_e;

        explicit
        window(std::string const& title, rgfw::vector_2u const& dimensions, display_mode_e display_mode = display_mode_e::windowed, rgfw::bool_t show = rgfw::true_)
            : window_{}, input_{}, title_{ title }, dimensions_{ dimensions }, is_visible_{ show }, display_mode_{ display_mode }
        {
            auto const is_visible_flag  = is_visible_ ? rgfw::window_flags_e{} : rgfw::window_flags_e::hide;
            auto const window_flags     = 
                rgfw::window_flags_e::center          | 
                rgfw::window_flags_e::scale_to_monitor| 
                is_visible_flag                       ;
            window_                     = std::unique_ptr<rgfw::window_t, decltype([](rgfw::window_t* window) { rgfw::window_close(window); })>(rgfw::create_window(title_, {}, dimensions, window_flags));
            input_                      = std::make_shared<rgfw::input>();
            if (!window_                                 ) throw std::runtime_error{ "failed to create window"   };
            
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
            rgfw::create_context(window_.get(), gl_hints);
            if (!glad::initialize(rgfw::function_address)) throw std::runtime_error{ "failed to initialize glad" };
        }

        void rename        (std::string     const& title     )
        {
            rgfw::window_set_title(window_.get(), title);
            title_ = title;
        }
        void resize        (rgfw::vector_2u const& dimensions)
        {
            rgfw::window_resize(window_.get(), dimensions);
            dimensions_ = dimensions;
        }
        void process_events()
        {
            auto event = rgfw::event{};
            while (rgfw::window_check_event(window_.get(), &event))
            {
                switch (event.type)
                {
                    using enum rgfw::event_type_e;

                    case data_drag             : 
                    {
                        auto const& data_drag_event = event.data_drag;
                        data_drag_signaled_         = rgfw::true_;
                        data_drag_                  = rgfw::vector_2u
                        { 
                            static_cast<rgfw::int32_t>(data_drag_event.x), 
                            static_cast<rgfw::int32_t>(data_drag_event.y), 
                        };

                        break;
                    }
                    case data_drop             : 
                    {
                        auto const& data_drop_event = event.data_drop;
                        data_drop_signaled_         = rgfw::true_;
                        data_drop_                  = data_drop_event.files;

                        break;
                    }
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
                    case window_maximized      : 
                    {
                        is_visible_ = rgfw::true_;
                        break;
                    }
                    case window_minimized      : 
                    {
                        is_visible_ = rgfw::false_;
                        break;
                    }
                    case window_moved          : break;
                    case window_refresh        : break;
                    case window_resized        : 
                    {
                        dimensions_ = rgfw::window_get_dimensions(window_.get());
                        break;
                    }
                    case window_restored       : 
                    {
                        is_visible_ = rgfw::true_;
                        break;
                    }
                    
                    default                    : throw std::invalid_argument{ "invalid event type" };
                }
            }
        }
        void swap_buffers  ()
        {
            rgfw::window_swap_buffers(window_.get());
        }
        void show          ()
        {
            rgfw::window_show(window_.get());
        }
        void hide          ()
        {
            rgfw::window_hide(window_.get());
        }
        void close         ()
        {
            rgfw::window_set_should_close(window_.get(), rgfw::true_);
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
        auto is_visible    () const -> rgfw::bool_t
        {
            return is_visible_;
        }
        auto input_handler () const -> std::shared_ptr<const rgfw::input>
        {
            return input_;
        }
        auto data_drag     () -> std::optional<rgfw::vector_2u>
        {
            if (!data_drag_signaled_) return std::nullopt;
            
            data_drag_signaled_ = rgfw::false_;
            return data_drag_;
        }
        auto data_drop     () -> std::optional<std::span<rgfw::char_t const*>>
        {
            if (!data_drop_signaled_) return std::nullopt;

            data_drop_signaled_ = rgfw::false_;
            return data_drop_;
        }
        auto context       ()
        {
            return rgfw::window_get_context(window_.get());
        }
        auto native_handle () -> rgfw::window_t*
        {
            return window_.get();
        }

        operator rgfw::bool_t() const
        {
            return rgfw::window_should_close(window_.get()) == rgfw::false_;
        }

    private:
        using window_deleter_t = std::function<void(rgfw::window_t*)>;
        using window_pointer_t = std::unique_ptr<rgfw::window_t, window_deleter_t>;
        using input_pointer_t  = std::shared_ptr<rgfw::input>;

        window_pointer_t               window_;
        input_pointer_t                input_;
        std::string                    title_;
        rgfw::vector_2u                dimensions_;
        rgfw::bool_t                   is_visible_;
        display_mode_e                 display_mode_;
        rgfw::bool_t                   data_drag_signaled_;
        rgfw::vector_2u                data_drag_;
        rgfw::bool_t                   data_drop_signaled_;
        std::span<rgfw::char_t const*> data_drop_;
    };
}
