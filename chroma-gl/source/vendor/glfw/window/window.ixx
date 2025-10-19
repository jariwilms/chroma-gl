export module vendor.glfw.window;

import std;
import opengl.config;
import opengl.context;
import opengl.types;
import vendor.glad;
import vendor.glfw.functions;
import vendor.glfw.input;
import vendor.glfw.types;

export namespace glfw
{
    class window
    {
    public:
        enum class display_mode_e
        {
            windowed  , 
            borderless, 
            fullscreen, 
        };
        struct user_data
        {
            std::shared_ptr<glfw::input> input      = {};
            gl::vector2u*                dimensions = {};
        };

        window(const std::string& title, const gl::vector2u& dimensions)
           : title_{ title }, dimensions_{ dimensions }, display_mode_{ display_mode_e::windowed }
        {
            glfw::initialize();
            glfw::window_hint(glfw::hint_e::context_version_major, glfw::hint_value_e::opengl_version_major_4);
            glfw::window_hint(glfw::hint_e::context_version_minor, glfw::hint_value_e::opengl_version_minor_6);
            glfw::window_hint(glfw::hint_e::opengl_profile       , glfw::hint_value_e::opengl_core_profile   );
            glfw::window_hint(glfw::hint_e::refresh_rate         , glfw::hint_value_e::dont_care             );
            glfw::window_hint(glfw::hint_e::visible              , glfw::hint_value_e::false_                );

            if constexpr (gl::config::build_configuration == gl::config::build_configuration_e::debug)
                glfw::window_hint(glfw::hint_e::opengl_debug_context , glfw::hint_value_e::true_);

            window_ = std::unique_ptr<glfw::window_t, decltype([](auto* window)
                {
                    glfw::destroy_window(window);
                    glfw::terminate();
                })>{ glfw::create_window(title_, dimensions_) };

            glfw::make_context_current(window_.get());
            glfw::swap_interval       (gl::uint32_t{ 0u });
            glfw::set_window_monitor  (window_.get(), nullptr, dimensions_);
            glfw::show_window         (window_.get());
           
            glad::initialize();
            context_   = std::make_shared<gl::context>();
            input_     = std::make_shared<glfw::input>();
            user_data_ = window::user_data{ input_, &dimensions_ };

            glfw::set_window_user_pointer       (window_.get(), &user_data_);
            glfw::set_error_callback            (         [](                               gl::int32_t   error , const gl::char_t* description)
                {
                    std::print("[GLFW_ERROR] {}: {}\n", error, description);
                });
            glfw::set_key_callback              (window_.get(), [](glfw::window_t*  window, gl::int32_t   key   , gl::int32_t   scancode, gl::int32_t action, gl::int32_t modifiers) 
                { 
                    const auto* user_data = glfw::get_window_user_pointer<window::user_data>(window);
                    user_data->input->input_key_callback(window, glfw::key_e{ key }, scancode, action, glfw::modifier_e{ modifiers });
                });
            glfw::set_mouse_button_callback     (window_.get(), [](glfw::window_t*  window, gl::int32_t   button,                         gl::int32_t action, gl::int32_t modifiers)
                {
                    const auto* user_data = glfw::get_window_user_pointer<window::user_data>(window);
                    user_data->input->input_button_callback(window, glfw::button_e{ button }, action, glfw::modifier_e{ modifiers });
                });
            glfw::set_cursor_position_callback  (window_.get(), [](glfw::window_t*  window, gl::float64_t x     , gl::float64_t y       )
                {
                    const auto* user_data = glfw::get_window_user_pointer<window::user_data>(window);
                    user_data->input->input_cursor_callback(window, x, y);
                });
            glfw::set_scroll_callback           (window_.get(), [](glfw::window_t*  window, gl::float64_t x     , gl::float64_t y       )
                {
                    const auto* user_data = glfw::get_window_user_pointer<window::user_data>(window);
                    user_data->input->input_scroll_callback(window, x, y);
                });
            glfw::set_frame_buffer_size_callback(window_.get(), [](glfw::window_t*  window, gl::int32_t   width , gl::int32_t   height  )
                {
                    const auto* user_data = glfw::get_window_user_pointer<window::user_data>(window);
                    *user_data->dimensions = gl::vector2u{ width, height };
                });
        }

        void poll_events        ()
        {
            input_->capture();
            glfw::poll_events();
        }
        void swap_buffers       ()
        {
            glfw::swap_buffers(window_.get());
        }

        void rename             (const std::string & title     )
        {
            glfw::set_window_title(window_.get(), title.c_str());
        }
        void resize             (const gl::vector2u& dimensions)
        {
            glfw::set_window_size(window_.get(), dimensions);
            dimensions_ = dimensions;
        }

        void change_display_mode(display_mode_e display_mode)
        {
            auto monitor = static_cast<glfw::monitor_t*>(nullptr);
            if (display_mode == display_mode_e::fullscreen) monitor = glfw::get_primary_monitor();

            glfw::set_window_monitor(window_.get(), monitor, gl::vector2u{ 1280, 720 });
        }

        void        close       ()
        {
            glfw::set_window_should_close(window_.get(), gl::true_);
        }
        auto should_close       () const -> gl::bool_t
        {
            return glfw::window_should_close(window_.get());
        }

        auto title              () const -> const std::string&
        {
            return title_;
        }
        auto display_mode       () const -> display_mode_e
        {
            return display_mode_;
        }
        auto dimensions         () const -> const gl::vector2u&
        {
            return dimensions_;
        }
        auto input_handler      () const -> std::shared_ptr<const glfw::input>
        {
            return input_;
        }
        auto context            () const -> const gl::context&
        {
            return *context_;
        }
        auto native_handle      () -> glfw::window_t*
        {
            return window_.get();
        }

    private:
        std::unique_ptr<glfw::window_t, std::function<void(glfw::window_t*)>> window_;
        std::shared_ptr<gl::context>                                          context_;
        std::shared_ptr<glfw::input>                                          input_;
        std::string                                                           title_;
        display_mode_e                                                        display_mode_;
        gl::vector2u                                                          dimensions_;
        user_data                                                             user_data_;
    };
}
