export module rgfw:window;

import std;
import glad;
import :flags;
import :functions;
import :input;
import :structures;
import :types;

export namespace rgfw
{
    class window
    {
    public:
        using flags_e        = rgfw::window_flags_e;
        using display_mode_e = rgfw::window_display_mode_e;

        explicit
        window(std::string const& title, rgfw::vector_2u const& dimensions, flags_e create_flags = flags_e::none, display_mode_e display_mode = display_mode_e::windowed, rgfw::bool_t show = rgfw::true_, rgfw::bool_t is_debug_context = rgfw::false_)
            : window_{}, input_{ std::make_shared<rgfw::input>() }
            , title_{ title }, dimensions_{ dimensions }, is_visible_{ show }, is_debug_context_{ is_debug_context }, display_mode_{ display_mode }
            , data_drag_signaled_{ rgfw::false_ }, data_drag_{}, data_drop_signaled_{ rgfw::false_ }, data_drop_{}
        {
            rgfw::initialize(title, rgfw::initialization_flag_e::opengl);

            if (!show) create_flags |= flags_e::hidden;
            switch (display_mode)
            {
                using enum display_mode_e;
                case windowed  : break;
                case borderless: create_flags |= flags_e::borderless; break;
                case fullscreen: create_flags |= flags_e::fullscreen; break;
                default        : throw std::invalid_argument{ "invalid display mode" };
            }

            window_ = window_pointer_t{ rgfw::create_window(title_, {}, dimensions_, create_flags) };
            if (!window_) throw std::runtime_error{ "failed to create window" };

            auto gl_hints = rgfw::gl_hints
            {
                .double_buffer = rgfw::true_                     , 
                .debug         = is_debug_context_               , 
                .profile       = rgfw::gl_profile_e::core        , 
                .major         = rgfw::int32_t{ 4 }              , 
                .minor         = rgfw::int32_t{ 6 }              , 
                .renderer      = rgfw::gl_renderer_e::accelerated, 
            };

            context_ = rgfw::create_context(window_.get(), gl_hints);
            if (!glad::initialize(rgfw::loader)) throw std::runtime_error{ "failed to initialize glad" };
        }

        window(window&&) noexcept = default;
       ~window()                  = default;

        auto rename           (std::string     const& title     ) -> void
        {
            rgfw::window_set_title(window_.get(), title);
            title_ = title;
        }
        auto resize           (rgfw::vector_2u const& dimensions) -> void
        {
            rgfw::window_resize(window_.get(), dimensions);
            dimensions_ = dimensions;
        }

        auto set_display_mode (display_mode_e mode) -> void
        {
            switch (mode)
            {
                using enum display_mode_e;
                case windowed  :
                {
                    rgfw::window_set_fullscreen(window_.get(), rgfw::false_);
                    rgfw::window_set_border    (window_.get(), rgfw::true_);
                    break;
                }
                case borderless:
                {
                    rgfw::window_set_fullscreen(window_.get(), rgfw::false_);
                    rgfw::window_set_border    (window_.get(), rgfw::false_);
                    break;
                }
                case fullscreen:
                {
                    rgfw::window_set_fullscreen(window_.get(), rgfw::true_);
                    break;
                }
                default: throw std::invalid_argument{ "invalid display mode" };
            }

            display_mode_ = mode;
        }

        auto process_events   () -> void
        {
            input_->capture();

            auto event = rgfw::event{};
            while (rgfw::window_check_event(window_.get(), &event))
            {
                switch (event.type)
                {
                    using enum rgfw::event_type_e;
                    case data_drag             :
                    {
                        auto const& data_drag_event = event.data_drag;
                        data_drag_signaled_          = rgfw::true_;
                        data_drag_                   = rgfw::vector_2u
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
                        data_drop_.clear();
                        data_drop_.reserve(data_drop_event.files.size());
                        for (rgfw::char_t const* file : data_drop_event.files)
                        {
                            if (file) data_drop_.emplace_back(file);
                        }

                        break;
                    }
                    case key_character         : input_->process(event); break;
                    case key_pressed           : input_->process(event); break;
                    case key_released          : input_->process(event); break;
                    case monitor_connected     : break;
                    case monitor_disconnected  : break;
                    case mouse_button_pressed  : input_->process(event); break;
                    case mouse_button_released : input_->process(event); break;
                    case mouse_enter           : input_->process(event); break;
                    case mouse_leave           : input_->process(event); break;
                    case mouse_motion          : input_->process(event); break;
                    case mouse_motion_raw      : break;
                    case mouse_scroll          : input_->process(event); break;
                    case none                  : break;
                    case scale_updated         : break;
                    case window_close          : break;
                    case window_focus_in       : break;
                    case window_focus_out      : break;
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

                    default: break;
                }
            }
        }
        auto swap_buffers     () -> void
        {
            rgfw::window_swap_buffers(window_.get());
        }
        auto show             () -> void
        {
            rgfw::window_show(window_.get());
            is_visible_ = rgfw::true_;
        }
        auto hide             () -> void
        {
            rgfw::window_hide(window_.get());
            is_visible_ = rgfw::false_;
        }
        auto close            () -> void
        {
            rgfw::window_set_should_close(window_.get(), rgfw::true_);
        }

        auto title            () const -> std::string const&
        {
            return title_;
        }
        auto dimensions       () const -> rgfw::vector_2u const&
        {
            return dimensions_;
        }
        auto display_mode     () const -> display_mode_e
        {
            return display_mode_;
        }
        auto is_visible       () const -> rgfw::bool_t
        {
            return is_visible_;
        }
        auto is_debug_context () const -> rgfw::bool_t
        {
            return is_debug_context_;
        }
        auto input_handler    () const -> std::shared_ptr<rgfw::input const>
        {
            return input_;
        }
        auto is_open          () const
        {
            return rgfw::window_should_close(window_.get()) != rgfw::true_;
        }

        auto data_drag        () -> std::optional<rgfw::vector_2u>
        {
            if (!data_drag_signaled_) return std::nullopt;

            data_drag_signaled_ = rgfw::false_;
            return data_drag_;
        }
        auto data_drop        () -> std::optional<std::vector<std::string>>
        {
            if (!data_drop_signaled_) return std::nullopt;

            data_drop_signaled_ = rgfw::false_;
            return std::exchange(data_drop_, {});
        }
        auto context          ()
        {
            return rgfw::window_get_context(window_.get());
        }
        auto native_handle    () -> rgfw::window_t*
        {
            return window_.get();
        }

        explicit operator rgfw::bool_t() const
        {
            return is_open();
        }

        auto operator=(window&&) noexcept -> window& = default;

    private:
        struct deleter
        {
            auto operator()(rgfw::window_t* window) const -> rgfw::void_t
            {
                if (window) rgfw::window_close(window);
            }
        };

        using window_pointer_t = std::unique_ptr<rgfw::window_t, deleter>;
        using input_pointer_t  = std::shared_ptr<rgfw::input>;

        window_pointer_t         window_;
        input_pointer_t          input_;
        rgfw::gl_context_t*      context_;
        std::string              title_;
        rgfw::vector_2u          dimensions_;
        rgfw::bool_t             is_visible_;
        rgfw::bool_t             is_debug_context_;
        display_mode_e           display_mode_;
        rgfw::bool_t             data_drag_signaled_;
        rgfw::vector_2u          data_drag_;
        rgfw::bool_t             data_drop_signaled_;
        std::vector<std::string> data_drop_;
    };
}