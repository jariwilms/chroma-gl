export module rgfw:flags;

import std;
import <rgfw/rgfw.h>;
import :types;

export namespace rgfw
{
    enum class initialization_flag_e : RGFW_initFlags
    {
        opengl = RGFW_initOpenGL, 
        vulkan = RGFW_initVulkan, 
        direcx = RGFW_initX11   , 
    };
    enum class event_type_e : ::RGFW_eventType
    {
        data_drag              = ::RGFW_dataDrag           , 
        data_drop              = ::RGFW_dataDrop           , 
        key_character          = ::RGFW_keyChar            , 
        key_pressed            = ::RGFW_keyPressed         , 
        key_released           = ::RGFW_keyReleased        , 
        monitor_connected      = ::RGFW_monitorConnected   , 
        monitor_disconnected   = ::RGFW_monitorDisconnected, 
        mouse_button_pressed   = ::RGFW_mouseButtonPressed , 
        mouse_button_released  = ::RGFW_mouseButtonReleased, 
        mouse_enter            = ::RGFW_mouseEnter         , 
        mouse_leave            = ::RGFW_mouseLeave         , 
        mouse_motion           = ::RGFW_mouseMotion        , 
        mouse_motion_raw       = ::RGFW_mouseRawMotion     , 
        mouse_scroll           = ::RGFW_mouseScroll        , 
        none                   = ::RGFW_eventNone          , 
        scale_updated          = ::RGFW_scaleUpdated       , 
        window_close           = ::RGFW_windowClose        , 
        window_focus_in        = ::RGFW_windowFocusIn      , 
        window_focus_out       = ::RGFW_windowFocusOut     , 
        window_maximized       = ::RGFW_windowMaximized    , 
        window_minimized       = ::RGFW_windowMinimized    , 
        window_moved           = ::RGFW_windowMoved        , 
        window_refresh         = ::RGFW_windowRefresh      , 
        window_resized         = ::RGFW_windowResized      , 
        window_restored        = ::RGFW_windowRestored     , 
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
        close                  = ::RGFW_windowCloseFlag        , 
        data_drag              = ::RGFW_dataDragFlag           , 
        data_drop              = ::RGFW_dataDropFlag           , 
        focus_in               = ::RGFW_windowFocusInFlag      , 
        focus_out              = ::RGFW_windowFocusOutFlag     , 
        key_pressed            = ::RGFW_keyPressedFlag         , 
        key_released           = ::RGFW_keyReleasedFlag        , 
        mouse_button_pressed   = ::RGFW_mouseButtonPressedFlag , 
        mouse_button_released  = ::RGFW_mouseButtonReleasedFlag, 
        mouse_enter            = ::RGFW_mouseEnterFlag         , 
        mouse_leave            = ::RGFW_mouseLeaveFlag         , 
        mouse_position_changed = ::RGFW_mousePosChangedFlag    , 
        mouse_scroll           = ::RGFW_mouseScrollFlag        , 
        scale_updated          = ::RGFW_scaleUpdatedFlag       , 
        window_maximized       = ::RGFW_windowMaximizedFlag    , 
        window_minimized       = ::RGFW_windowMinimizedFlag    , 
        window_moved           = ::RGFW_windowMovedFlag        , 
        window_refresh         = ::RGFW_windowRefreshFlag      , 
        window_resized         = ::RGFW_windowResizedFlag      , 
        window_restored        = ::RGFW_windowRestoredFlag     , 

        all_events             = ::RGFW_allEventFlags          , 
        data_drop_events       = ::RGFW_dataDragDropEventsFlag , 
        focus_events           = ::RGFW_windowFocusEventsFlag  , 
        key_events             = ::RGFW_keyEventsFlag          , 
        mouse_events           = ::RGFW_mouseEventsFlag        , 
        window_events          = ::RGFW_windowEventsFlag       , 
    };
    enum class window_display_mode_e
    {
        windowed  , 
        borderless, 
        fullscreen, 
    };
    enum class window_flags_e : ::RGFW_windowFlags
    {
        none                                             , 
        allow_drag_and_drop = ::RGFW_windowAllowDND      , 
        borderless          = ::RGFW_windowedFullscreen  , 
        center              = ::RGFW_windowCenter        , 
        center_cursor       = ::RGFW_windowCenterCursor  , 
        floating            = ::RGFW_windowFloating      , 
        focus               = ::RGFW_windowFocus         , 
        focus_on_show       = ::RGFW_windowFocusOnShow   , 
        fullscreen          = ::RGFW_windowFullscreen    , 
        hidden              = ::RGFW_windowHide          , 
        hide_mouse          = ::RGFW_windowHideMouse     , 
        maximize            = ::RGFW_windowMaximize      , 
        minimize            = ::RGFW_windowMinimize      , 
        no_border           = ::RGFW_windowNoBorder      , 
        no_resize           = ::RGFW_windowNoResize      , 
        scale_to_monitor    = ::RGFW_windowScaleToMonitor, 
        transparent         = ::RGFW_windowTransparent   , 
    };





    enum class flag_operation_e
    {
        none         = 0u << 0u                                             , 

        addition     = 1u << 0u                                             , 
        subtraction  = 1u << 1u                                             , 

        bitwise_and  = 1u << 2u                                             , 
        bitwise_or   = 1u << 3u                                             , 
        bitwise_xor  = 1u << 4u                                             , 
        bitwise_not  = 1u << 5u                                             , 

        compare      = 1u << 6u                                             , 

        arithmetic   = addition    | subtraction                            , 
        bitwise      = bitwise_and | bitwise_or  | bitwise_xor | bitwise_not, 
        all          = arithmetic  | bitwise                                , 
    };
    
    auto constexpr operator&         (rgfw::flag_operation_e first    , rgfw::flag_operation_e second) -> rgfw::flag_operation_e { return std::bit_cast<rgfw::flag_operation_e>(std::to_underlying(first) & std::to_underlying(second)); }
    auto constexpr operator|         (rgfw::flag_operation_e first    , rgfw::flag_operation_e second) -> rgfw::flag_operation_e { return std::bit_cast<rgfw::flag_operation_e>(std::to_underlying(first) | std::to_underlying(second)); }
    auto constexpr supports_operation(rgfw::flag_operation_e operation, rgfw::flag_operation_e check ) -> rgfw::bool_t           { return (operation & check) == check; }

    template<typename enum_t> struct enum_operation { static auto constexpr value = rgfw::flag_operation_e::none; };
    template<typename enum_t> auto constexpr enum_operation_v = rgfw::enum_operation<enum_t>::value;

    template<typename enum_t> concept has_addition    = std::is_enum_v<enum_t> && rgfw::supports_operation(rgfw::enum_operation_v<enum_t>, rgfw::flag_operation_e::addition   );
    template<typename enum_t> concept has_subtraction = std::is_enum_v<enum_t> && rgfw::supports_operation(rgfw::enum_operation_v<enum_t>, rgfw::flag_operation_e::subtraction);
    template<typename enum_t> concept has_bitwise_and = std::is_enum_v<enum_t> && rgfw::supports_operation(rgfw::enum_operation_v<enum_t>, rgfw::flag_operation_e::bitwise_and);
    template<typename enum_t> concept has_bitwise_or  = std::is_enum_v<enum_t> && rgfw::supports_operation(rgfw::enum_operation_v<enum_t>, rgfw::flag_operation_e::bitwise_or );
    template<typename enum_t> concept has_bitwise_xor = std::is_enum_v<enum_t> && rgfw::supports_operation(rgfw::enum_operation_v<enum_t>, rgfw::flag_operation_e::bitwise_xor);
    template<typename enum_t> concept has_bitwise_not = std::is_enum_v<enum_t> && rgfw::supports_operation(rgfw::enum_operation_v<enum_t>, rgfw::flag_operation_e::bitwise_not);
    template<typename enum_t> concept has_compare     = std::is_enum_v<enum_t> && rgfw::supports_operation(rgfw::enum_operation_v<enum_t>, rgfw::flag_operation_e::compare    );

    template<rgfw::has_addition    enum_t                          > auto constexpr operator+ (enum_t  first, enum_t     second) noexcept -> enum_t       { return static_cast<enum_t>(std::to_underlying(first) +  std::to_underlying(second)); }
    template<rgfw::has_addition    enum_t, std::integral integral_t> auto constexpr operator+ (enum_t  first, integral_t second) noexcept -> enum_t       { return static_cast<enum_t>(std::to_underlying(first) +                     second ); }
    template<rgfw::has_subtraction enum_t                          > auto constexpr operator- (enum_t  first, enum_t     second) noexcept -> enum_t       { return static_cast<enum_t>(std::to_underlying(first) -  std::to_underlying(second)); }
    template<rgfw::has_subtraction enum_t, std::integral integral_t> auto constexpr operator- (enum_t  first, integral_t second) noexcept -> enum_t       { return static_cast<enum_t>(std::to_underlying(first) -                     second ); }
    template<rgfw::has_bitwise_and enum_t                          > auto constexpr operator& (enum_t  first, enum_t     second) noexcept -> enum_t       { return static_cast<enum_t>(std::to_underlying(first) &  std::to_underlying(second)); }
    template<rgfw::has_bitwise_or  enum_t                          > auto constexpr operator| (enum_t  first, enum_t     second) noexcept -> enum_t       { return static_cast<enum_t>(std::to_underlying(first) |  std::to_underlying(second)); }
    template<rgfw::has_bitwise_xor enum_t                          > auto constexpr operator^ (enum_t  first, enum_t     second) noexcept -> enum_t       { return static_cast<enum_t>(std::to_underlying(first) ^  std::to_underlying(second)); }
    template<rgfw::has_bitwise_not enum_t                          > auto constexpr operator~ (               enum_t     second) noexcept -> enum_t       { return static_cast<enum_t>(                          ~  std::to_underlying(second)); }          
    template<rgfw::has_addition    enum_t                          > auto constexpr operator+=(enum_t& first, enum_t     second) noexcept -> enum_t&      { return first = first + second; }
    template<rgfw::has_addition    enum_t, std::integral integral_t> auto constexpr operator+=(enum_t& first, integral_t second) noexcept -> enum_t&      { return first = first + second; }
    template<rgfw::has_subtraction enum_t                          > auto constexpr operator-=(enum_t& first, enum_t     second) noexcept -> enum_t&      { return first = first - second; }
    template<rgfw::has_subtraction enum_t, std::integral integral_t> auto constexpr operator-=(enum_t& first, integral_t second) noexcept -> enum_t&      { return first = first - second; }
    template<rgfw::has_bitwise_and enum_t                          > auto constexpr operator&=(enum_t& first, enum_t     second) noexcept -> enum_t&      { return first = first & second; }
    template<rgfw::has_bitwise_or  enum_t                          > auto constexpr operator|=(enum_t& first, enum_t     second) noexcept -> enum_t&      { return first = first | second; }
    template<rgfw::has_bitwise_xor enum_t                          > auto constexpr operator^=(enum_t& first, enum_t     second) noexcept -> enum_t&      { return first = first ^ second; }
    template<rgfw::has_compare     enum_t                          > auto constexpr operator< (enum_t  first, enum_t     second) noexcept -> rgfw::bool_t { return std::to_underlying(first) <  std::to_underlying(second) ; }
    template<rgfw::has_compare     enum_t                          > auto constexpr operator> (enum_t  first, enum_t     second) noexcept -> rgfw::bool_t { return std::to_underlying(first) >  std::to_underlying(second) ; }
    template<rgfw::has_compare     enum_t                          > auto constexpr operator<=(enum_t  first, enum_t     second) noexcept -> rgfw::bool_t { return std::to_underlying(first) <= std::to_underlying(second) ; }
    template<rgfw::has_compare     enum_t                          > auto constexpr operator>=(enum_t  first, enum_t     second) noexcept -> rgfw::bool_t { return std::to_underlying(first) >= std::to_underlying(second) ; }



    template<> struct rgfw::enum_operation<rgfw::window_flags_e> { static auto constexpr value = rgfw::flag_operation_e::bitwise; };
}
