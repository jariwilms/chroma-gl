export module vendor.rgfw.types;

import std;
import vendor.glm;
import <rgfw/rgfw.h>;

export namespace rgfw
{
    using void_t       =   void           ;
    using bool_t       = ::RGFW_bool      ;
    using char_t       =   char           ;
    using byte_t       = ::u8             ;
    using uint8_t      = ::uint8_t        ;
    using int8_t       = ::int8_t         ;
    using uint16_t     = ::uint16_t       ;
    using int16_t      = ::int16_t        ;
    using uint32_t     = ::uint32_t       ;
    using int32_t      = ::int32_t        ;
    using uint64_t     = ::uint64_t       ;
    using int64_t      = ::int64_t        ;
    using float32_t    =   float          ;
    using float64_t    =   double         ;

    using window_t     = ::RGFW_window    ;

    using key_t        = ::RGFW_key       ;
    using button_t     = ::RGFW_key       ;
    using modifier_t   = ::RGFW_keymod    ;

    using event_t      = ::RGFW_event     ;
    using event_type_t = ::RGFW_eventType ;
    using event_flag_t = ::RGFW_eventFlag ;
    using gl_context   = ::RGFW_glContext ;
    using egl_context  = ::RGFW_eglContext;

    enum : rgfw::bool_t
    {
        false_ = RGFW_FALSE, 
        true_  = RGFW_TRUE , 
    };



    template<typename T, rgfw::uint32_t Components>
    using vector_t    = glm::vec<Components, T, glm::packed_highp>;
    using vector_2i   = rgfw::vector_t<rgfw::int32_t  , 2u>;
    using vector_4i   = rgfw::vector_t<rgfw::int32_t  , 4u>;
    using vector_2u   = rgfw::vector_t<rgfw::uint32_t , 2u>;
    using vector_4u   = rgfw::vector_t<rgfw::uint32_t , 4u>;
    using vector_2f   = rgfw::vector_t<rgfw::float32_t, 2u>;
    using vector_4f   = rgfw::vector_t<rgfw::float32_t, 4u>;
    using vector_2d   = rgfw::vector_t<rgfw::float64_t, 2u>;
    using vector_4d   = rgfw::vector_t<rgfw::float64_t, 4u>;
}
