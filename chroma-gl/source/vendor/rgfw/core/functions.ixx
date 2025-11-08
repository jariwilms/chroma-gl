export module vendor.rgfw.functions;

import std;
import <rgfw/rgfw.h>;
import vendor.rgfw.flags;
import vendor.rgfw.structures;
import vendor.rgfw.types;

export namespace rgfw
{
    auto create_window          (std::string const& title, rgfw::vector_2u offset, rgfw::vector_2u position, rgfw::window_flags_e flags) -> rgfw::window_t*
    {
        return ::RGFW_createWindow(
            title.c_str()                         , 
            static_cast<rgfw::int32_t>(offset  .x), static_cast<rgfw::int32_t>(offset  .y), 
            static_cast<rgfw::int32_t>(position.x), static_cast<rgfw::int32_t>(position.y), 
            std::to_underlying(flags)            );
    }
    auto create_context         (rgfw::window_t* window, rgfw::gl_hints& gl_hints)
    {
        ::RGFW_window_createContext_OpenGL(window, reinterpret_cast<::RGFW_glHints*>(&gl_hints));
    }

    void make_current_context   (rgfw::window_t* window)
    {
        ::RGFW_window_makeCurrentContext_OpenGL(window);
    }
    void make_current_window    (rgfw::window_t* window)
    {
        ::RGFW_window_makeCurrentWindow_OpenGL(window);
    }
    auto window_check_event     (rgfw::window_t* window, rgfw::event* event) -> rgfw::bool_t
    {
        return ::RGFW_window_checkEvent(window, reinterpret_cast<rgfw::event_t*>(event));
    }
    auto window_get_context     (rgfw::window_t* window) -> rgfw::gl_context_t*
    {
        return ::RGFW_window_getContext_OpenGL(window);
    }
    auto window_get_dimensions  (rgfw::window_t* window) -> rgfw::vector_2u
    {
        auto dimensions = rgfw::vector_2u{};
        ::RGFW_window_getSize(window, reinterpret_cast<rgfw::int32_t*>(&dimensions.x), reinterpret_cast<rgfw::int32_t*>(&dimensions.y));

        return dimensions;
    }
    void window_hide            (rgfw::window_t* window)
    {
        ::RGFW_window_hide(window);
    }
    void window_resize          (rgfw::window_t* window, rgfw::vector_2u const& dimensions)
    {
        ::RGFW_window_resize(window, static_cast<rgfw::int32_t>(dimensions.x), static_cast<rgfw::int32_t>(dimensions.y));
    }
    void window_set_should_close(rgfw::window_t* window, rgfw::bool_t state)
    {
        ::RGFW_window_setShouldClose(window, state);
    }
    void window_set_title       (rgfw::window_t* window, std::string const& title)
    {
        ::RGFW_window_setName(window, title.c_str());
    }
    auto window_should_close    (rgfw::window_t* window) -> rgfw::bool_t
    {
        return ::RGFW_window_shouldClose(window);
    }
    void window_show            (rgfw::window_t* window)
    {
        ::RGFW_window_show(window);
    }
    void window_swap_buffers    (rgfw::window_t* window)
    {
        ::RGFW_window_swapBuffers_OpenGL(window);
    }
    void window_close           (rgfw::window_t* window)
    {
        return ::RGFW_window_close(window);
    }
}
