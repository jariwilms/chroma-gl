export module rgfw:code;

import std;
import :types;

export namespace rgfw
{
    enum class key_e : rgfw::key_t
    {
        null            = ::RGFW_keyNULL        , 
        backspace       = ::RGFW_keyBackSpace   , 
        horizontal_tab  = ::RGFW_keyTab         , 
        enter           = ::RGFW_keyEnter       , 
        return_         = ::RGFW_keyReturn      , 

        escape          = ::RGFW_keyEscape      , 
        space           = ::RGFW_keySpace       , 

        apostrophe      = ::RGFW_keyApostrophe  , 
        comma           = ::RGFW_keyComma       , 
        period          = ::RGFW_keyPeriod      , 
        slash           = ::RGFW_keySlash       , 

        zero            = ::RGFW_key0           , 
        one             = ::RGFW_key1           , 
        two             = ::RGFW_key2           , 
        three           = ::RGFW_key3           , 
        four            = ::RGFW_key4           , 
        five            = ::RGFW_key5           , 
        six             = ::RGFW_key6           , 
        seven           = ::RGFW_key7           , 
        eight           = ::RGFW_key8           , 
        nine            = ::RGFW_key9           , 

        minus           = ::RGFW_keyMinus       , 
        semicolon       = ::RGFW_keySemicolon   , 
        equals          = ::RGFW_keyEquals      , 
        
        backtick        = ::RGFW_keyBacktick    , 

        a               = ::RGFW_keyA           , 
        b               = ::RGFW_keyB           , 
        c               = ::RGFW_keyC           , 
        d               = ::RGFW_keyD           , 
        e               = ::RGFW_keyE           , 
        f               = ::RGFW_keyF           , 
        g               = ::RGFW_keyG           , 
        h               = ::RGFW_keyH           , 
        i               = ::RGFW_keyI           , 
        j               = ::RGFW_keyJ           , 
        k               = ::RGFW_keyK           , 
        l               = ::RGFW_keyL           , 
        m               = ::RGFW_keyM           , 
        n               = ::RGFW_keyN           , 
        o               = ::RGFW_keyO           , 
        p               = ::RGFW_keyP           , 
        q               = ::RGFW_keyQ           , 
        r               = ::RGFW_keyR           , 
        s               = ::RGFW_keyS           , 
        t               = ::RGFW_keyT           , 
        u               = ::RGFW_keyU           , 
        v               = ::RGFW_keyV           , 
        w               = ::RGFW_keyW           , 
        x               = ::RGFW_keyX           , 
        y               = ::RGFW_keyY           , 
        z               = ::RGFW_keyZ           , 

        bracket         = ::RGFW_keyBracket     , 
        backslash       = ::RGFW_keyBackSlash   , 
        close_bracket   = ::RGFW_keyCloseBracket, 

        delete_         = ::RGFW_keyDelete      , 

        function_01     = ::RGFW_keyF1          , 
        function_02     = ::RGFW_keyF2          , 
        function_03     = ::RGFW_keyF3          , 
        function_04     = ::RGFW_keyF4          , 
        function_05     = ::RGFW_keyF5          , 
        function_06     = ::RGFW_keyF6          , 
        function_07     = ::RGFW_keyF7          , 
        function_08     = ::RGFW_keyF8          , 
        function_09     = ::RGFW_keyF9          , 
        function_10     = ::RGFW_keyF10         , 
        function_11     = ::RGFW_keyF11         , 
        function_12     = ::RGFW_keyF12         , 
        function_13     = ::RGFW_keyF13         , 
        function_14     = ::RGFW_keyF14         , 
        function_15     = ::RGFW_keyF15         , 
        function_16     = ::RGFW_keyF16         , 
        function_17     = ::RGFW_keyF17         , 
        function_18     = ::RGFW_keyF18         , 
        function_19     = ::RGFW_keyF19         , 
        function_20     = ::RGFW_keyF20         , 
        function_21     = ::RGFW_keyF21         , 
        function_22     = ::RGFW_keyF22         , 
        function_23     = ::RGFW_keyF23         , 
        function_24     = ::RGFW_keyF24         , 
        function_25     = ::RGFW_keyF25         , 

        caps_lock       = ::RGFW_keyCapsLock    , 
        left_shift      = ::RGFW_keyShiftL      , 
        left_control    = ::RGFW_keyControlL    , 
        left_alt        = ::RGFW_keyAltL        , 
        left_super      = ::RGFW_keySuperL      , 
        right_shift     = ::RGFW_keyShiftR      , 
        right_control   = ::RGFW_keyControlR    , 
        right_alt       = ::RGFW_keyAltR        , 
        right_super     = ::RGFW_keySuperR      , 

        up              = ::RGFW_keyUp          , 
        down            = ::RGFW_keyDown        , 
        left            = ::RGFW_keyLeft        , 
        right           = ::RGFW_keyRight       , 
        insert          = ::RGFW_keyInsert      , 
        menu            = ::RGFW_keyMenu        , 
        end             = ::RGFW_keyEnd         , 
        home            = ::RGFW_keyHome        , 
        page_up         = ::RGFW_keyPageUp      , 
        page_down       = ::RGFW_keyPageDown    , 
        num_lock        = ::RGFW_keyNumLock     , 

        keypad_slash    = ::RGFW_keyPadSlash    , 
        keypad_multiply = ::RGFW_keyPadMultiply , 
        keypad_plus     = ::RGFW_keyPadPlus     , 
        keypad_minus    = ::RGFW_keyPadMinus    , 
        keypad_equal    = ::RGFW_keyPadEqual    , 
        keypad_1        = ::RGFW_keyPad1        , 
        keypad_2        = ::RGFW_keyPad2        , 
        keypad_3        = ::RGFW_keyPad3        , 
        keypad_4        = ::RGFW_keyPad4        , 
        keypad_5        = ::RGFW_keyPad5        , 
        keypad_6        = ::RGFW_keyPad6        , 
        keypad_7        = ::RGFW_keyPad7        , 
        keypad_8        = ::RGFW_keyPad8        , 
        keypad_9        = ::RGFW_keyPad9        , 
        keypad_0        = ::RGFW_keyPad0        , 
        keypad_period   = ::RGFW_keyPadPeriod   , 
        keypad_return   = ::RGFW_keyPadReturn   , 

        scroll_lock     = ::RGFW_keyScrollLock  , 
        print_screen    = ::RGFW_keyPrintScreen , 
        pause           = ::RGFW_keyPause       , 
        world_1         = ::RGFW_keyWorld1      , 
        world_2         = ::RGFW_keyWorld2      , 
    };
    enum class button_e : rgfw::button_t
    {
        left            = ::RGFW_mouseLeft  , 
        middle          = ::RGFW_mouseMiddle, 
        right           = ::RGFW_mouseRight , 
        miscellaneous_1 = ::RGFW_mouseMisc1 , 
        miscellaneous_2 = ::RGFW_mouseMisc2 , 
        miscellaneous_3 = ::RGFW_mouseMisc3 , 
        miscellaneous_4 = ::RGFW_mouseMisc4 , 
        miscellaneous_5 = ::RGFW_mouseMisc5 , 
    };
    enum class modifier_e : rgfw::modifier_t
    {
        caps_lock   = ::RGFW_modCapsLock  , 
        num_lock    = ::RGFW_modNumLock   , 
        control     = ::RGFW_modControl   , 
        alt         = ::RGFW_modAlt       , 
        shift       = ::RGFW_modShift     , 
        super       = ::RGFW_modSuper     , 
        scroll_lock = ::RGFW_modScrollLock, 
    };

    auto constexpr operator>(rgfw::key_e      left, rgfw::key_e      right) noexcept -> rgfw::bool_t { return std::to_underlying(left) > std::to_underlying(right); }
    auto constexpr operator>(rgfw::button_e   left, rgfw::button_e   right) noexcept -> rgfw::bool_t { return std::to_underlying(left) > std::to_underlying(right); }
    auto constexpr operator>(rgfw::modifier_e left, rgfw::modifier_e right) noexcept -> rgfw::bool_t { return std::to_underlying(left) > std::to_underlying(right); }
}
