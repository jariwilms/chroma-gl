export module rgfw:input;

import std;
import :code;
import :functions;
import :structures;
import :types;

export namespace rgfw
{
    class input
    {
    public:
        void capture                   ()
        {
            last_active_keys_     = active_keys_;
            last_active_buttons_  = active_buttons_;
            last_cursor_position_ = cursor_position_;
            last_scroll_wheel_    = scroll_wheel_;
        }
        void reset                     ()
        {
            active_keys_        .reset();
            last_active_keys_   .reset();
            active_buttons_     .reset();
            last_active_buttons_.reset();

            cursor_position_      = rgfw::vector_2u{};
            last_cursor_position_ = rgfw::vector_2u{};
            scroll_wheel_         = rgfw::vector_2u{};
            last_scroll_wheel_    = rgfw::vector_2u{};
        }

        auto any_key_active            ()                    const -> rgfw::bool_t
        {
            return active_keys_.any();
        }
        auto any_button_active         ()                    const -> rgfw::bool_t
        {
            return active_buttons_.any();
        }

        auto key_active                (rgfw::key_e    code) const -> rgfw::bool_t
        {
            return active_keys_.test(std::to_underlying(code));
        }
        auto key_pressed               (rgfw::key_e    code) const -> rgfw::bool_t
        {
            return active_keys_.test(std::to_underlying(code)) && !last_active_keys_.test(std::to_underlying(code));
        }
        auto key_released              (rgfw::key_e    code) const -> rgfw::bool_t
        {
            return !active_keys_.test(std::to_underlying(code)) && last_active_keys_.test(std::to_underlying(code));
        }

        auto button_active             (rgfw::button_e code) const -> rgfw::bool_t
        {
            return active_buttons_.test(std::to_underlying(code));
        }
        auto button_pressed            (rgfw::button_e code) const -> rgfw::bool_t
        {
            return active_buttons_.test(std::to_underlying(code)) && !last_active_buttons_.test(std::to_underlying(code));
        }
        auto button_released           (rgfw::button_e code) const -> rgfw::bool_t
        {
            return !active_buttons_.test(std::to_underlying(code)) && last_active_buttons_.test(std::to_underlying(code));
        }

        auto cursor_position           ()                    const -> rgfw::vector_2f
        {
            return cursor_position_;
        }
        auto cursor_position_delta     ()                    const -> rgfw::vector_2f
        {
            return cursor_position_ - last_cursor_position_;
        }

        auto scroll_wheel              ()                    const -> rgfw::vector_2f
        {
            return scroll_wheel_;
        }
        auto scroll_wheel_delta        ()                    const -> rgfw::vector_2f
        {
            return last_scroll_wheel_ - scroll_wheel_;
        }

        void process                   (rgfw::event const& event)
        {
            switch (event.type)
            {
                using enum rgfw::event_type_e;
                case key_pressed           :
                {
                    auto const& key_event = event.key;
                    auto const& symbol    = static_cast<rgfw::key_e>(key_event.symbol);
                    if (symbol > rgfw::key_e::__maximum) return;

                    active_keys_[std::to_underlying(symbol)] = rgfw::true_;
                    break;
                }
                case key_released          :
                {
                    auto const& key_event = event.key;
                    auto const& symbol    = static_cast<rgfw::key_e>(key_event.symbol);
                    if (symbol > rgfw::key_e::__maximum) return;

                    active_keys_[std::to_underlying(symbol)] = rgfw::false_;
                    break;
                }
                case mouse_button_pressed  :
                {
                    auto const& mouse_button_event = event.mouse_button;
                    auto const& symbol             = static_cast<rgfw::button_e>(mouse_button_event.value);
                    if (symbol > rgfw::button_e::__maximum) return;

                    active_buttons_[std::to_underlying(symbol)] = rgfw::true_;
                    break;
                }
                case mouse_button_released :
                {
                    auto const& mouse_button_event = event.mouse_button;
                    auto const& symbol             = static_cast<rgfw::button_e>(mouse_button_event.value);
                    if (symbol > rgfw::button_e::__maximum) return;

                    active_buttons_[std::to_underlying(symbol)] = rgfw::false_;
                    break;
                }
                case mouse_enter           : break;
                case mouse_leave           : break;
                case mouse_position_changed: 
                {
                    auto const& mouse_position_event = event.mouse_position;
                    cursor_position_ = rgfw::vector_2u
                    {
                        static_cast<rgfw::uint32_t>(mouse_position_event.x), 
                        static_cast<rgfw::uint32_t>(mouse_position_event.y), 
                    };

                    break;
                }
                case mouse_scroll          : 
                {
                    auto const& mouse_scroll_event = event.mouse_scroll;
                    scroll_wheel_ = rgfw::vector_2u
                    {
                        static_cast<rgfw::uint32_t>(mouse_scroll_event.x),
                        static_cast<rgfw::uint32_t>(mouse_scroll_event.y),
                    };

                    break;
                }

                default: return;
            }

        }

    private:
        std::bitset<std::to_underlying(rgfw::key_e   ::__maximum)> active_keys_;
        std::bitset<std::to_underlying(rgfw::key_e   ::__maximum)> last_active_keys_;
        std::bitset<std::to_underlying(rgfw::button_e::__maximum)> active_buttons_;
        std::bitset<std::to_underlying(rgfw::button_e::__maximum)> last_active_buttons_;
        rgfw::vector_2u                                            cursor_position_;
        rgfw::vector_2u                                            last_cursor_position_;
        rgfw::vector_2u                                            scroll_wheel_;
        rgfw::vector_2u                                            last_scroll_wheel_;
    };
}
