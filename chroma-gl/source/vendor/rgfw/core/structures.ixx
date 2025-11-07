export module vendor.rgfw.structures;

import std;
import vendor.rgfw.flags;
import vendor.rgfw.types;
import vendor.rgfw.code;

export namespace rgfw
{
    struct common_event
    {
        rgfw::event_type_e type;
        rgfw::window_t*    window;
    };
    struct data_drag_event
    {
        rgfw::event_type_e type;
        rgfw::window_t*    window;
        rgfw::int32_t      x;
        rgfw::int32_t      y;
    };
    struct data_drop_event
    {
        rgfw::event_type_e             type;
        rgfw::window_t*                window;
        std::span<rgfw::char_t const*> files;
    };
    struct gl_hints
    {
        rgfw::int32_t               stencil;
        rgfw::int32_t               samples;
        rgfw::int32_t               stereo;
        rgfw::int32_t               auxiliary_buffers;
        rgfw::int32_t               double_buffer;
        rgfw::int32_t               red;
        rgfw::int32_t               green;
        rgfw::int32_t               blue;
        rgfw::int32_t               alpha;
        rgfw::int32_t               depth;
        rgfw::int32_t               accumulation_red;
        rgfw::int32_t               accumulation_green;
        rgfw::int32_t               accumulation_blue;
        rgfw::int32_t               accumulation_alpha;
        rgfw::bool_t                srgb;
        rgfw::bool_t                robustness;
        rgfw::bool_t                debug;
        rgfw::bool_t                no_error;
        rgfw::gl_release_behavior_e release_behavior;
        rgfw::gl_profile_e          profile;
        rgfw::int32_t               major;
        rgfw::int32_t               minor;
        rgfw::gl_context *          share;
        rgfw::egl_context*          share_egl;
        rgfw::gl_renderer_e         renderer;
    };
    struct key_event
    {
        rgfw::event_type_e type;
        rgfw::window_t*    window;
        rgfw::key_t        value;
        rgfw::uint8_t      symbol;
        rgfw::bool_t       is_repeating;
        rgfw::modifier_t   modifier;
    };
    struct mouse_button_event
    {
        rgfw::event_type_e type;
        rgfw::window_t*    window;
        rgfw::uint8_t      value;
    };
    struct mouse_position_event
    {
        rgfw::event_type_e type;
        rgfw::window_t*    window;
        rgfw::int32_t      x;
        rgfw::int32_t      y;
        rgfw::float32_t    x_raw;
        rgfw::float32_t    y_raw;
    };
    struct mouse_scroll_event
    {
        rgfw::event_type_e type;
        rgfw::window_t*    window;
        rgfw::float32_t    x;
        rgfw::float32_t    y;
    };
    struct scale_updated_event
    {
        rgfw::event_type_e type;
        rgfw::window_t*    window;
        rgfw::float32_t    x;
        rgfw::float32_t    y;
    };
    
    union  event
    {
        rgfw::event_type_e         type;
        rgfw::common_event         common;
        rgfw::mouse_button_event   mouse_button;
        rgfw::mouse_scroll_event   mouse_scroll;
        rgfw::mouse_position_event mouse_position;
        rgfw::key_event            key;
        rgfw::data_drop_event      data_drop;
        rgfw::data_drag_event      data_drag;
        rgfw::scale_updated_event  scale_updated;
    };
}
