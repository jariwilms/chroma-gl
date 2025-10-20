export module vendor.glfw.input;

import std;
import <glfw/glfw3.h>;
import opengl.types;
import opengl.utility;
import vendor.glfw.types;
import vendor.glfw.input.code;

export namespace glfw
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

            cursor_position_      = {};
            last_cursor_position_ = {};
            scroll_wheel_         = {};
            last_scroll_wheel_    = {};
        }

        auto any_key_active            ()                    const -> gl::bool_t
        {
            return active_keys_.any();
        }
        auto any_button_active         ()                    const -> gl::bool_t
        {
            return active_buttons_.any();
        }

        auto key_active                (glfw::key_e code)    const -> gl::bool_t
        {
            return active_keys_.test(std::to_underlying(code));
        }
        auto key_pressed               (glfw::key_e code)    const -> gl::bool_t
        {
            return active_keys_.test(std::to_underlying(code)) && !last_active_keys_.test(std::to_underlying(code));
        }
        auto key_released              (glfw::key_e code)    const -> gl::bool_t
        {
            return !active_keys_.test(std::to_underlying(code)) && last_active_keys_.test(std::to_underlying(code));
        }

        auto button_active             (glfw::button_e code) const -> gl::bool_t
        {
            return active_buttons_.test(std::to_underlying(code));
        }
        auto button_pressed            (glfw::button_e code) const -> gl::bool_t
        {
            return active_buttons_.test(std::to_underlying(code)) && !last_active_buttons_.test(std::to_underlying(code));
        }
        auto button_released           (glfw::button_e code) const -> gl::bool_t
        {
            return !active_buttons_.test(std::to_underlying(code)) && last_active_buttons_.test(std::to_underlying(code));
        }

        auto cursor_position           ()                    const -> gl::vector_2f
        {
            return cursor_position_;
        }
        auto cursor_position_delta     ()                    const -> gl::vector_2f
        {
            return cursor_position_ - last_cursor_position_;
        }

        auto scroll_wheel              ()                    const -> gl::vector_2f
        {
            return scroll_wheel_;
        }
        auto scroll_wheel_delta        ()                    const -> gl::vector_2f
        {
            return last_scroll_wheel_ - scroll_wheel_;
        }

        void input_key_callback        (glfw::window_t*, glfw::key_e    key   , gl::int32_t, gl::int32_t action, glfw::modifier_e)
        {
            if ((key < key_min) || (key > key_max)) return;

            switch (glfw::input_action_e{ action })
            {
                case glfw::input_action_e::release: active_keys_.set(std::to_underlying(key), gl::false_); break;
                case glfw::input_action_e::press  : active_keys_.set(std::to_underlying(key), gl::true_ ); break;
                case glfw::input_action_e::repeat :                                                        break;
            }
        }
        void input_button_callback     (glfw::window_t*, glfw::button_e button,              gl::int32_t action, glfw::modifier_e)
        {
            if ((button < button_min) || (button > button_max)) return;

            switch (glfw::input_action_e{ action })
            {
                case glfw::input_action_e::release: active_buttons_.set(std::to_underlying(button), gl::false_); break;
                case glfw::input_action_e::press  : active_buttons_.set(std::to_underlying(button), gl::true_ ); break;
                case glfw::input_action_e::repeat :                                                              break;
            }
        }
        void input_cursor_callback     (glfw::window_t*, gl::float64_t  x, gl::float64_t y)
        {
            cursor_position_ = gl::vector_2f{ static_cast<gl::float32_t>(x), static_cast<gl::float32_t>(y) };
        }
        void input_scroll_callback     (glfw::window_t*, gl::float64_t  x, gl::float64_t y)
        {
            scroll_wheel_ = gl::vector_2f{ static_cast<gl::float32_t>(x), static_cast<gl::float32_t>(y) };
        }

    private:
        std::bitset<std::to_underlying(key_max   )> active_keys_;
        std::bitset<std::to_underlying(key_max   )> last_active_keys_;
        std::bitset<std::to_underlying(button_max)> active_buttons_;
        std::bitset<std::to_underlying(button_max)> last_active_buttons_;
        gl::vector_2f                                cursor_position_;
        gl::vector_2f                                last_cursor_position_;
        gl::vector_2f                                scroll_wheel_;
        gl::vector_2f                                last_scroll_wheel_;
    };
}
