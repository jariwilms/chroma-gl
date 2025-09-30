export module vendor.glfw.input.code;

import std;
import opengl.types;

export namespace vendor::glfw
{
    enum class button_e : gl::int32_t
    {
        button1      = 0, 
        button2      = 1, 
        button3      = 2, 
        button4      = 3, 
        button5      = 4, 
        button6      = 5,
        button7      = 6,
        button8      = 7,

        left_mouse   = button1, 
        right_mouse  = button2, 
        middle_mouse = button3, 
        back         = button4, 
        forward      = button5, 
    };
    enum class controller_e : gl::int32_t
    {
        hat_centered   = 0x0 << 0u, 
        hat_up         = 0x1 << 0u, 
        hat_right      = 0x1 << 1u, 
        hat_down       = 0x1 << 2u, 
        hat_left       = 0x1 << 3u, 

        hat_right_up   = hat_right | hat_up  , 
        hat_right_down = hat_right | hat_down, 
        hat_left_up    = hat_left  | hat_up  , 
        hat_left_down  = hat_left  | hat_down, 
    };
    enum class key_e : gl::int32_t
    {
        space        =  32, apostrophe    =  39, 
        comma        =  44, minus         =  45, 
        period       =  46, slash         =  47, 
        
        d0           =  48, d1            =  49, 
        d2           =  50, d3            =  51, 
        d4           =  52, d5            =  53, 
        d6           =  54, d7            =  55, 
        d8           =  56, d9            =  57, 
        
        semicolon    =  59, equal         =  61, 
        
        a            =  65, b             =  66, 
        c            =  67, d             =  68, 
        e            =  69, f             =  70, 
        g            =  71, h             =  72, 
        i            =  73, j             =  74, 
        k            =  75, l             =  76, 
        m            =  77, n             =  78, 
        o            =  79, p             =  80, 
        q            =  81, r             =  82, 
        s            =  83, t             =  84, 
        u            =  85, v             =  86, 
        w            =  87, x             =  88, 
        y            =  89, z             =  90, 
        
        leftbracket  =  91, backslash     =  92, 
        rightbracket =  93, graveaccent   =  96, 

        world1       = 161, world2        = 162, 
        
        escape       = 256, enter         = 257, 
        tab          = 258, backspace     = 259, 
        insert       = 260, delete_       = 261, 
        right        = 262, left          = 263, 
        down         = 264, up            = 265, 
        pageup       = 266, pagedown      = 267, 
        home         = 268, end           = 269, 
        capslock     = 280, scrolllock    = 281, 
        numlock      = 282, printscreen   = 283, 
        pause        = 284, 
        
        f1           = 290, f2            = 291, 
        f3           = 292, f4            = 293, 
        f5           = 294, f6            = 295, 
        f7           = 296, f8            = 297, 
        f9           = 298, f10           = 299, 
        f11          = 300, f12           = 301, 
        f13          = 302, f14           = 303, 
        f15          = 304, f16           = 305, 
        f17          = 306, f18           = 307, 
        f19          = 308, f20           = 309, 
        f21          = 310, f22           = 311, 
        f23          = 312, f24           = 313, 
        f25          = 314, 
        
        kp0          = 320, kp1           = 321, 
        kp2          = 322, kp3           = 323, 
        kp4          = 324, kp5           = 325, 
        kp6          = 326, kp7           = 327, 
        kp8          = 328, kp9           = 329, 
        kp_decimal   = 330, kp_divide     = 331, 
        kp_multiply  = 332, kp_subtract   = 333, 
        kp_add       = 334, kp_enter      = 335, 
        kp_equal     = 336, 
        
        left_shift   = 340, left_control  = 341, 
        left_alt     = 342, left_super    = 343, 
        right_shift  = 344, right_control = 345, 
        right_alt    = 346, right_super   = 347, 
        menu         = 348, 
    };
    enum class modifier_e : gl::int32_t
    {
        none      = 0x0, 

        shift     = 0x1 << 0u, 
        control   = 0x1 << 1u, 
        alt       = 0x1 << 2u, 
        super     = 0x1 << 3u, 
        caps_lock = 0x1 << 4u, 
        num_lock  = 0x1 << 5u, 
    };

    constexpr auto button_min     = glfw::button_e    ::button1;
    constexpr auto button_max     = glfw::button_e    ::button8;
    constexpr auto controller_min = glfw::controller_e::hat_centered;
    constexpr auto controller_max = glfw::controller_e::hat_left;
    constexpr auto key_min        = glfw::key_e       ::space;
    constexpr auto key_max        = glfw::key_e       ::menu;
    constexpr auto modifier_min   = glfw::modifier_e  ::shift;
    constexpr auto modifier_max   = glfw::modifier_e  ::num_lock;
}
