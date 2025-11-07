export module vendor.rgfw.flags;

import std;
import <rgfw/rgfw.h>;
import vendor.rgfw.types;

export namespace rgfw
{
    enum class event_type_e : ::RGFW_eventType
    {
        data_drag              = ::RGFW_dataDrag           , 
        data_drop              = ::RGFW_dataDrop           , 
        focus_in               = ::RGFW_focusIn            , 
        focus_out              = ::RGFW_focusOut           , 
        key_pressed            = ::RGFW_keyPressed         , 
        key_released           = ::RGFW_keyReleased        , 
        mouse_button_pressed   = ::RGFW_mouseButtonPressed , 
        mouse_button_released  = ::RGFW_mouseButtonReleased, 
        mouse_enter            = ::RGFW_mouseEnter         , 
        mouse_leave            = ::RGFW_mouseLeave         , 
        mouse_position_changed = ::RGFW_mousePosChanged    , 
        mouse_scroll           = ::RGFW_mouseScroll        , 
        none                   = ::RGFW_eventNone          , 
        quit                   = ::RGFW_quit               , 
        scale_updated          = ::RGFW_scaleUpdated       , 
        window_maximized       = ::RGFW_windowMaximized    , 
        window_minimized       = ::RGFW_windowMinimized    , 
        window_moved           = ::RGFW_windowMoved        , 
        window_refresh         = ::RGFW_windowRefresh      , 
        window_resized         = ::RGFW_windowResized      , 
        window_restored        = ::RGFW_windowRestored     , 
    };
    enum class window_flags_e : ::RGFW_windowFlags
    {
        allow_dnd        = ::RGFW_windowAllowDND      , 
        borderless       = ::RGFW_windowedFullscreen  , 
        center           = ::RGFW_windowCenter        , 
        center_cursor    = ::RGFW_windowCenterCursor  , 
        egl              = ::RGFW_windowEGL           , 
        floating         = ::RGFW_windowFloating      , 
        focus            = ::RGFW_windowFocus         , 
        focus_on_show    = ::RGFW_windowFocusOnShow   , 
        fullscreen       = ::RGFW_windowFullscreen    , 
        hide             = ::RGFW_windowHide          , 
        hide_mouse       = ::RGFW_windowHideMouse     , 
        maximize         = ::RGFW_windowMaximize      , 
        minimize         = ::RGFW_windowMinimize      , 
        no_border        = ::RGFW_windowNoBorder      , 
        no_resize        = ::RGFW_windowNoResize      , 
        opengl           = ::RGFW_windowOpenGL        , 
        scale_to_monitor = ::RGFW_windowScaleToMonitor, 
        transparent      = ::RGFW_windowTransparent   , 
    };
    enum class gl_release_behavior_e : ::RGFW_glReleaseBehavior
    {
        flush, 
        none , 
    };
    enum class gl_profile_e : ::RGFW_glProfile
    {
        compatibility, 
        core         , 
        es           , 
    };
    enum class gl_renderer_e : ::RGFW_glRenderer
    {
        accelerated, 
        software   , 
    };
    enum class event_flag_e : ::RGFW_eventFlag
    {
        data_drag              = ::RGFW_dataDragFlag           , 
        data_drop              = ::RGFW_dataDropFlag           , 
        focus_in               = ::RGFW_focusInFlag            , 
        focus_out              = ::RGFW_focusOutFlag           , 
        key_pressed            = ::RGFW_keyPressedFlag         , 
        key_released           = ::RGFW_keyReleasedFlag        , 
        mouse_button_pressed   = ::RGFW_mouseButtonPressedFlag , 
        mouse_button_released  = ::RGFW_mouseButtonReleasedFlag, 
        mouse_enter            = ::RGFW_mouseEnterFlag         , 
        mouse_leave            = ::RGFW_mouseLeaveFlag         , 
        mouse_position_changed = ::RGFW_mousePosChangedFlag    , 
        mouse_scroll           = ::RGFW_mouseScrollFlag        , 
        quit                   = ::RGFW_quitFlag               , 
        scale_updated          = ::RGFW_scaleUpdatedFlag       , 
        window_moved           = ::RGFW_windowMovedFlag        , 
        window_maximized       = ::RGFW_windowMaximizedFlag    , 
        window_minimized       = ::RGFW_windowMinimizedFlag    , 
        window_refresh         = ::RGFW_windowRefreshFlag      , 
        window_resized         = ::RGFW_windowResizedFlag      , 
        window_restored        = ::RGFW_windowRestoredFlag     , 

        all_events             = ::RGFW_allEventFlags          , 
        data_drop_events       = ::RGFW_dataDropEventsFlag     , 
        focus_events           = ::RGFW_focusEventsFlag        , 
        key_events             = ::RGFW_keyEventsFlag          , 
        mouse_events           = ::RGFW_mouseEventsFlag        , 
        window_events          = ::RGFW_windowEventsFlag       , 
    };



    constexpr auto operator|(rgfw::window_flags_e left, rgfw::window_flags_e right) noexcept -> rgfw::window_flags_e { return static_cast<rgfw::window_flags_e>(std::to_underlying(left) | std::to_underlying(right)); }
}
