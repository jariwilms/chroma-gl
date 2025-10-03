export module opengl.flags;

import std;
import <glad/gl.h>;
import opengl.utility;
import opengl.types;

export namespace gl
{
    enum class atomic_counter_buffer_info_e : gl::enum_t
    {
        active_atomic_counter_indices                = GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES       , 
        active_atomic_counters                       = GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS              , 
        binding                                      = GL_ATOMIC_COUNTER_BUFFER_BINDING                             , 
        data_size                                    = GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE                           , 
        referenced_by_compute_shader                 = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER        , 
        referenced_by_fragment_shader                = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER       , 
        referenced_by_geometry_shader                = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER       , 
        referenced_by_tessellation_control_shader    = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER   , 
        referenced_by_tessellation_evaluation_shader = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER, 
        referenced_by_vertex_shader                  = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER         , 
    };
    enum class blending_equation_e : gl::enum_t
    {
        add              = GL_FUNC_ADD             , 
        subtract         = GL_FUNC_SUBTRACT        , 
        reverse_subtract = GL_FUNC_REVERSE_SUBTRACT, 
        
        minimum          = GL_MIN                  , 
        maximum          = GL_MAX                  , 
    };
    enum class blending_factor_e : gl::enum_t
    {
        zero                        = GL_ZERO                    , 
        one                         = GL_ONE                     , 
        
        source_color                = GL_SRC_COLOR               , 
        one_minus_source_color      = GL_ONE_MINUS_SRC_COLOR     , 
        destination_color           = GL_DST_COLOR               , 
        one_minus_destination_color = GL_ONE_MINUS_DST_COLOR     , 
        source_alpha                = GL_SRC_ALPHA               , 
        one_minus_source_alpha      = GL_ONE_MINUS_SRC_ALPHA     , 
        destination_alpha           = GL_DST_ALPHA               , 
        one_minus_destination_alpha = GL_ONE_MINUS_DST_ALPHA     , 
        constant_color              = GL_CONSTANT_COLOR          , 
        one_minus_constant_color    = GL_ONE_MINUS_CONSTANT_COLOR, 
        constant_alpha              = GL_CONSTANT_ALPHA          , 
        one_minus_constant_alpha    = GL_ONE_MINUS_CONSTANT_ALPHA, 
        source_alpha_saturate       = GL_SRC_ALPHA_SATURATE      , 
        source1_color               = GL_SRC1_COLOR              , 
        one_minus_source1_color     = GL_ONE_MINUS_SRC1_COLOR    , 
        source1_alpha               = GL_SRC1_ALPHA              , 
        one_minus_source1_alpha     = GL_ONE_MINUS_SRC1_ALPHA    , 
    };
    enum class buffer_base_format_e : gl::enum_t
    {
        r        = GL_RED            , 
        g        = GL_GREEN          , 
        b        = GL_BLUE           , 
        rg       = GL_RG             , 
        rgb      = GL_RGB            , 
        rgba     = GL_RGBA           , 
        bgr      = GL_BGR            , 
        bgra     = GL_BGRA           , 
        r_int    = GL_RED_INTEGER    , 
        g_int    = GL_GREEN_INTEGER  , 
        b_int    = GL_BLUE_INTEGER   , 
        rg_int   = GL_RG_INTEGER     , 
        rgb_int  = GL_RGB_INTEGER    , 
        rgba_int = GL_RGBA_INTEGER   , 
        bgr_int  = GL_BGR_INTEGER    , 
        bgra_int = GL_BGRA_INTEGER   , 
        d        = GL_DEPTH_COMPONENT, 
        s        = GL_STENCIL_INDEX  , 
        ds       = GL_DEPTH_STENCIL  , 
    };
    enum class buffer_base_target_e : gl::enum_t
    {
        uniform_buffer            = GL_UNIFORM_BUFFER           , 
        transform_feedback_buffer = GL_TRANSFORM_FEEDBACK_BUFFER, 
        shader_storage_buffer     = GL_SHADER_STORAGE_BUFFER    , 
        atomic_counter_buffer     = GL_ATOMIC_COUNTER_BUFFER    , 
    };
    enum class buffer_format_e : gl::enum_t
    {
        r_int8       = GL_R8I     , 
        r_int16      = GL_R16I    , 
        r_int32      = GL_R32I    , 
        r_uint8      = GL_R8UI    , 
        r_uint8_n    = GL_R8      , 
        r_uint16     = GL_R16UI   , 
        r_uint16_n   = GL_R16     , 
        r_uint32     = GL_R32UI   , 
        r_float16    = GL_R16F    , 
        r_float32    = GL_R32F    , 
        
        rg_int8      = GL_RG8I    , 
        rg_int16     = GL_RG16I   , 
        rg_int32     = GL_RG32I   , 
        rg_uint8     = GL_RG8UI   , 
        rg_uint8_n   = GL_RG8     , 
        rg_uint16    = GL_RG16UI  , 
        rg_uint16_n  = GL_RG16    , 
        rg_uint32    = GL_RG32UI  , 
        rg_float16   = GL_RG16F   , 
        rg_float32   = GL_RG32F   , 
        
        rgb_int32    = GL_RGB32I  , 
        rgb_uint32   = GL_RGB32UI , 
        rgb_float32  = GL_RGB32F  , 
        
        rgba_int8    = GL_RGBA8I  , 
        rgba_int16   = GL_RGBA16I , 
        rgba_int16_n = GL_RGBA16  , 
        rgba_int32   = GL_RGBA32I , 
        rgba_uint8   = GL_RGBA8UI , 
        rgba_uint8_n = GL_RGBA8   , 
        rgba_uint16  = GL_RGBA16UI, 
        rgba_uint32  = GL_RGBA32UI, 
        rgba_float16 = GL_RGBA16F , 
        rgba_float32 = GL_RGBA32F , 
    };
    enum class buffer_mask_e : gl::bitfield_t
    {
        color   = GL_COLOR_BUFFER_BIT    , 
        depth   = GL_DEPTH_BUFFER_BIT    , 
        stencil = GL_STENCIL_BUFFER_BIT  , 
        
        all     = color | depth | stencil, 
    };
    enum class buffer_mapping_access_e : gl::enum_t
    {
        read       = GL_READ_ONLY , 
        write      = GL_WRITE_ONLY, 
        read_write = GL_READ_WRITE, 
    };
    enum class buffer_mapping_access_flags_e : gl::enum_t
    {
        read       = GL_READ_ONLY , 
        write      = GL_WRITE_ONLY, 
        read_write = GL_READ_WRITE, 
    };
    enum class buffer_mapping_range_access_flags_e : gl::bitfield_t
    {
        read              = GL_MAP_READ_BIT                      , 
        write             = GL_MAP_WRITE_BIT                     , 
        persistent        = GL_MAP_PERSISTENT_BIT                , 
        coherent          = GL_MAP_COHERENT_BIT                  , 
        invalidate_buffer = GL_MAP_INVALIDATE_BUFFER_BIT         , 
        invalidate_range  = GL_MAP_INVALIDATE_RANGE_BIT          , 
        flush_explicit    = GL_MAP_FLUSH_EXPLICIT_BIT            , 
        unsynchronized    = GL_MAP_UNSYNCHRONIZED_BIT            , 
        
        read_write        = read  | write                        , 
        write_discard     = write | invalidate_buffer            , 
        shared            = read  | write | persistent | coherent, 
    };
    enum class buffer_parameter_e : gl::enum_t
    {
        access        = GL_BUFFER_ACCESS           , 
        access_flags  = GL_BUFFER_ACCESS_FLAGS     , 
        is_immutable  = GL_BUFFER_IMMUTABLE_STORAGE, 
        is_mapped     = GL_BUFFER_MAPPED           , 
        map_length    = GL_BUFFER_MAP_LENGTH       , 
        map_offset    = GL_BUFFER_MAP_OFFSET       , 
        size          = GL_BUFFER_SIZE             , 
        storage_flags = GL_BUFFER_STORAGE_FLAGS    , 
        usage         = GL_BUFFER_USAGE            , 
    };
    enum class buffer_storage_flags_e : gl::bitfield_t
    {
        none            = GL_NONE                             , 
        read            = GL_MAP_READ_BIT                     , 
        write           = GL_MAP_WRITE_BIT                    , 
        persistent      = GL_MAP_PERSISTENT_BIT               , 
        coherent        = GL_MAP_COHERENT_BIT                 , 
        dynamic_storage = GL_DYNAMIC_STORAGE_BIT              , 
        client_storage  = GL_CLIENT_STORAGE_BIT               , 
        
        static_storage  = none                                , 
        read_write      = read | write                        , 
        shared          = read | write | persistent | coherent, 
    };
    enum class buffer_target_e : gl::enum_t
    {
        array_buffer              = GL_ARRAY_BUFFER             , 
        atomic_counter_buffer     = GL_ATOMIC_COUNTER_BUFFER    , 
        copy_read_buffer          = GL_COPY_READ_BUFFER         , 
        copy_write_buffer         = GL_COPY_WRITE_BUFFER        , 
        dispatch_indirect_buffer  = GL_DISPATCH_INDIRECT_BUFFER , 
        draw_indirect_buffer      = GL_DRAW_INDIRECT_BUFFER     , 
        element_array_buffer      = GL_ELEMENT_ARRAY_BUFFER     , 
        pixel_pack_buffer         = GL_PIXEL_PACK_BUFFER        , 
        pixel_unpack_buffer       = GL_PIXEL_UNPACK_BUFFER      , 
        query_buffer              = GL_QUERY_BUFFER             , 
        shader_storage_buffer     = GL_SHADER_STORAGE_BUFFER    , 
        texture_buffer            = GL_TEXTURE_BUFFER           , 
        transform_feedback_buffer = GL_TRANSFORM_FEEDBACK_BUFFER, 
        uniform_buffer            = GL_UNIFORM_BUFFER           , 
    };
    enum class buffer_usage_e : gl::enum_t
    {
        stream_draw  = GL_STREAM_DRAW , 
        stream_read  = GL_STREAM_READ , 
        stream_copy  = GL_STREAM_COPY , 
        static_draw  = GL_STATIC_DRAW , 
        static_read  = GL_STATIC_READ , 
        static_copy  = GL_STATIC_COPY , 
        dynamic_draw = GL_DYNAMIC_DRAW,  
        dynamic_read = GL_DYNAMIC_READ,  
        dynamic_copy = GL_DYNAMIC_COPY,  
    };
    enum class callback_pointer_e : gl::enum_t
    {
        debug_callback_function       = GL_DEBUG_CALLBACK_FUNCTION  , 
        debug_callback_user_parameter = GL_DEBUG_CALLBACK_USER_PARAM, 
    };
    enum class clamp_color_e : gl::enum_t
    {
        read = GL_CLAMP_READ_COLOR, 
    };
    enum class clipping_depth_mode_e : gl::enum_t
    {
        negative_one_to_one = GL_NEGATIVE_ONE_TO_ONE, 
        zero_to_one         = GL_ZERO_TO_ONE        , 
    };
    enum class clipping_origin_e : gl::enum_t
    {
        lower_left = GL_LOWER_LEFT, 
        upper_left = GL_UPPER_LEFT, 
    };
    enum class context_flags_e : gl::bitfield_t
    {
        forward_compatible = GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT,  
        debug              = GL_CONTEXT_FLAG_DEBUG_BIT             , 
        robust_access      = GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT     , 
        no_error           = GL_CONTEXT_FLAG_NO_ERROR_BIT          , 
    };
    enum class context_profile_e : gl::bitfield_t
    {
        core          = GL_CONTEXT_CORE_PROFILE_BIT         , 
        compatibility = GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, 
    };
    enum class context_property_e : gl::enum_t
    {
        extensions               = GL_EXTENSIONS              , 
        renderer                 = GL_RENDERER                , 
        shading_language_version = GL_SHADING_LANGUAGE_VERSION, 
        spir_v_extensions        = GL_SPIR_V_EXTENSIONS       , 
        vendor                   = GL_VENDOR                  , 
        version                  = GL_VERSION                 , 
    };
    enum class context_reset_strategy_e : gl::enum_t
    {
        no_notification = GL_NO_RESET_NOTIFICATION, 
        lose_context    = GL_LOSE_CONTEXT_ON_RESET, 
    };
    enum class cubemap_format_e : gl::enum_t
    {
        rgb_uint8_n  = GL_RGB8        , 
        rgb_float16  = GL_RGB16F      , 
        rgb_float32  = GL_RGB32F      , 
        rgba_uint8_n = GL_RGBA8       , 
        rgba_float16 = GL_RGBA16F     , 
        rgba_float32 = GL_RGBA32F     , 
        srgb_uint8   = GL_SRGB8       , 
        srgba_uint8  = GL_SRGB8_ALPHA8,  
    };
    enum class culling_facet_e : gl::enum_t
    {
        front          = GL_FRONT         , 
        back           = GL_BACK          , 
        front_and_back = GL_FRONT_AND_BACK, 
    };
    enum class data_e : gl::enum_t
    {
        aliased_line_width_range                              = GL_ALIASED_LINE_WIDTH_RANGE                 , 
        atomic_counter_buffer_binding                         = GL_ATOMIC_COUNTER_BUFFER_BINDING            , 
        blend_color                                           = GL_BLEND_COLOR                              , 
        blending_destination_alpha                            = GL_BLEND_DST_ALPHA                          , 
        blending_destination_rgb                              = GL_BLEND_DST_RGB                            , 
        blending_equation_alpha                               = GL_BLEND_EQUATION_ALPHA                     , 
        blending_equation_rgb                                 = GL_BLEND_EQUATION_RGB                       , 
        blending_source_alpha                                 = GL_BLEND_SRC_ALPHA                          , 
        blending_source_rgb                                   = GL_BLEND_SRC_RGB                            , 
        clipping_depth_mode                                   = GL_CLIP_DEPTH_MODE                          , 
        clipping_origin                                       = GL_CLIP_ORIGIN                              , 
        color_clear_value                                     = GL_COLOR_CLEAR_VALUE                        , 
        color_write_mask                                      = GL_COLOR_WRITEMASK                          , 
        context_flags                                         = GL_CONTEXT_FLAGS                            , 
        context_profile_mask                                  = GL_CONTEXT_PROFILE_MASK                     , 
        copy_read_buffer_binding                              = GL_COPY_READ_BUFFER_BINDING                 , 
        copy_write_buffer_binding                             = GL_COPY_WRITE_BUFFER_BINDING                , 
        current_program                                       = GL_CURRENT_PROGRAM                          , 
        debug_group_stack_depth                               = GL_DEBUG_GROUP_STACK_DEPTH                  , 
        debug_logged_messages                                 = GL_DEBUG_LOGGED_MESSAGES                    , 
        depth_clear_value                                     = GL_DEPTH_CLEAR_VALUE                        , 
        depth_function                                        = GL_DEPTH_FUNC                               , 
        depth_range                                           = GL_DEPTH_RANGE                              , 
        dispatch_indirect_buffer_binding                      = GL_DISPATCH_INDIRECT_BUFFER_BINDING         , 
        double_buffer                                         = GL_DOUBLEBUFFER                             , 
        draw_buffer                                           = GL_DRAW_BUFFER                              , 
        draw_frame_buffer_binding                             = GL_DRAW_FRAMEBUFFER_BINDING                 , 
        draw_indirect_buffer_binding                          = GL_DRAW_INDIRECT_BUFFER_BINDING             , 
        fragment_shader_derivative_hint                       = GL_FRAGMENT_SHADER_DERIVATIVE_HINT          , 
        image_binding_access                                  = GL_IMAGE_BINDING_ACCESS                     , 
        image_binding_format                                  = GL_IMAGE_BINDING_FORMAT                     , 
        image_binding_layer                                   = GL_IMAGE_BINDING_LAYER                      , 
        image_binding_level                                   = GL_IMAGE_BINDING_LEVEL                      , 
        image_binding_name                                    = GL_IMAGE_BINDING_NAME                       , 
        implementation_color_read_format                      = GL_IMPLEMENTATION_COLOR_READ_FORMAT         , 
        implementation_color_read_type                        = GL_IMPLEMENTATION_COLOR_READ_TYPE           , 
        index_array_buffer_binding                            = GL_ELEMENT_ARRAY_BUFFER_BINDING             , 
        layer_provoking_vertex                                = GL_LAYER_PROVOKING_VERTEX                   , 
        line_smooth_hint                                      = GL_LINE_SMOOTH_HINT                         , 
        line_width                                            = GL_LINE_WIDTH                               , 
        logic_operation_mode                                  = GL_LOGIC_OP_MODE                            , 
        major_version                                         = GL_MAJOR_VERSION                            , 
        maximum_3d_texture_size                               = GL_MAX_3D_TEXTURE_SIZE                      , 
        maximum_array_texture_layers                          = GL_MAX_ARRAY_TEXTURE_LAYERS                 , 
        maximum_clip_distances                                = GL_MAX_CLIP_DISTANCES                       , 
        maximum_color_attachments                             = GL_MAX_COLOR_ATTACHMENTS                    , 
        maximum_color_texture_samples                         = GL_MAX_COLOR_TEXTURE_SAMPLES                , 
        maximum_combined_atomic_counters                      = GL_MAX_COMBINED_ATOMIC_COUNTERS             , 
        maximum_combined_compute_uniform_components           = GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS  , 
        maximum_combined_fragment_uniform_components          = GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS , 
        maximum_combined_geometry_uniform_components          = GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS , 
        maximum_combined_shader_storage_blocks                = GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS       , 
        maximum_combined_texture_image_units                  = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS         , 
        maximum_combined_uniform_blocks                       = GL_MAX_COMBINED_UNIFORM_BLOCKS              , 
        maximum_combined_vertex_uniform_components            = GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS   , 
        maximum_compute_atomic_counter_buffers                = GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS       , 
        maximum_compute_atomic_counters                       = GL_MAX_COMPUTE_ATOMIC_COUNTERS              , 
        maximum_compute_shader_storage_blocks                 = GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS        , 
        maximum_compute_texture_image_units                   = GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS          , 
        maximum_compute_uniform_blocks                        = GL_MAX_COMPUTE_UNIFORM_BLOCKS               , 
        maximum_compute_uniform_components                    = GL_MAX_COMPUTE_UNIFORM_COMPONENTS           , 
        maximum_compute_work_group_count                      = GL_MAX_COMPUTE_WORK_GROUP_COUNT             , 
        maximum_compute_work_group_invocations                = GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS       , 
        maximum_compute_work_group_size                       = GL_MAX_COMPUTE_WORK_GROUP_SIZE              , 
        maximum_cubemap_texture_size                          = GL_MAX_CUBE_MAP_TEXTURE_SIZE                , 
        maximum_debug_group_stack_depth                       = GL_MAX_DEBUG_GROUP_STACK_DEPTH              , 
        maximum_debug_message_length                          = GL_MAX_DEBUG_MESSAGE_LENGTH                 , 
        maximum_depth_texture_samples                         = GL_MAX_DEPTH_TEXTURE_SAMPLES                , 
        maximum_draw_buffers                                  = GL_MAX_DRAW_BUFFERS                         , 
        maximum_dual_source_draw_buffers                      = GL_MAX_DUAL_SOURCE_DRAW_BUFFERS             , 
        maximum_element_index                                 = GL_MAX_ELEMENT_INDEX                        , 
        maximum_fragment_atomic_counters                      = GL_MAX_FRAGMENT_ATOMIC_COUNTERS             , 
        maximum_fragment_input_components                     = GL_MAX_FRAGMENT_INPUT_COMPONENTS            , 
        maximum_fragment_shader_storage_blocks                = GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS       , 
        maximum_fragment_uniform_blocks                       = GL_MAX_FRAGMENT_UNIFORM_BLOCKS              , 
        maximum_fragment_uniform_components                   = GL_MAX_FRAGMENT_UNIFORM_COMPONENTS          , 
        maximum_fragment_uniform_vectors                      = GL_MAX_FRAGMENT_UNIFORM_VECTORS             , 
        maximum_frame_buffer_height                           = GL_MAX_FRAMEBUFFER_HEIGHT                   , 
        maximum_frame_buffer_layers                           = GL_MAX_FRAMEBUFFER_LAYERS                   , 
        maximum_frame_buffer_samples                          = GL_MAX_FRAMEBUFFER_SAMPLES                  , 
        maximum_frame_buffer_width                            = GL_MAX_FRAMEBUFFER_WIDTH                    , 
        maximum_geometry_atomic_counters                      = GL_MAX_GEOMETRY_ATOMIC_COUNTERS             , 
        maximum_geometry_input_components                     = GL_MAX_GEOMETRY_INPUT_COMPONENTS            , 
        maximum_geometry_output_components                    = GL_MAX_GEOMETRY_OUTPUT_COMPONENTS           , 
        maximum_geometry_shader_storage_blocks                = GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS       , 
        maximum_geometry_texture_image_units                  = GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS         , 
        maximum_geometry_uniform_blocks                       = GL_MAX_GEOMETRY_UNIFORM_BLOCKS              , 
        maximum_geometry_uniform_components                   = GL_MAX_GEOMETRY_UNIFORM_COMPONENTS          , 
        maximum_index_elements                                = GL_MAX_ELEMENTS_INDICES                     , 
        maximum_integer_samples                               = GL_MAX_INTEGER_SAMPLES                      , 
        maximum_label_length                                  = GL_MAX_LABEL_LENGTH                         , 
        maximum_program_texel_offset                          = GL_MAX_PROGRAM_TEXEL_OFFSET                 , 
        maximum_rectangle_texture_size                        = GL_MAX_RECTANGLE_TEXTURE_SIZE               , 
        maximum_render_buffer_size                            = GL_MAX_RENDERBUFFER_SIZE                    , 
        maximum_sample_mask_words                             = GL_MAX_SAMPLE_MASK_WORDS                    , 
        maximum_server_wait_timeout                           = GL_MAX_SERVER_WAIT_TIMEOUT                  , 
        maximum_shader_storage_buffer_bindings                = GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS       , 
        maximum_tessellation_control_atomic_counters          = GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS         , 
        maximum_tessellation_control_shaders_torageblocks     = GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS   , 
        maximum_tessellation_evaluation_atomic_counters       = GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS      , 
        maximum_tessellation_evaluation_shader_storage_blocks = GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS, 
        maximum_texture_buffer_size                           = GL_MAX_TEXTURE_BUFFER_SIZE                  , 
        maximum_texture_image_units                           = GL_MAX_TEXTURE_IMAGE_UNITS                  , 
        maximum_texture_lod_bias                              = GL_MAX_TEXTURE_LOD_BIAS                     , 
        maximum_texture_size                                  = GL_MAX_TEXTURE_SIZE                         , 
        maximum_uniform_block_size                            = GL_MAX_UNIFORM_BLOCK_SIZE                   , 
        maximum_uniform_buffer_bindings                       = GL_MAX_UNIFORM_BUFFER_BINDINGS              , 
        maximum_uniform_locations                             = GL_MAX_UNIFORM_LOCATIONS                    , 
        maximum_varying_components                            = GL_MAX_VARYING_COMPONENTS                   , 
        maximum_varying_floats                                = GL_MAX_VARYING_FLOATS                       , 
        maximum_varying_vectors                               = GL_MAX_VARYING_VECTORS                      , 
        maximum_vertex_atomic_counters                        = GL_MAX_VERTEX_ATOMIC_COUNTERS               , 
        maximum_vertex_attribute_bindings                     = GL_MAX_VERTEX_ATTRIB_BINDINGS               , 
        maximum_vertex_attribute_relative_offset              = GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET        , 
        maximum_vertex_attributes                             = GL_MAX_VERTEX_ATTRIBS                       , 
        maximum_vertex_elements                               = GL_MAX_ELEMENTS_VERTICES                    , 
        maximum_vertex_output_components                      = GL_MAX_VERTEX_OUTPUT_COMPONENTS             , 
        maximum_vertex_shader_storage_blocks                  = GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS         , 
        maximum_vertex_texture_image_units                    = GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS           , 
        maximum_vertex_uniform_blocks                         = GL_MAX_VERTEX_UNIFORM_BLOCKS                , 
        maximum_vertex_uniform_components                     = GL_MAX_VERTEX_UNIFORM_COMPONENTS            , 
        maximum_vertex_uniform_vectors                        = GL_MAX_VERTEX_UNIFORM_VECTORS               , 
        maximum_viewport_dimensions                           = GL_MAX_VIEWPORT_DIMS                        , 
        maximum_viewports                                     = GL_MAX_VIEWPORTS                            , 
        minimum_map_buffer_alignment                          = GL_MIN_MAP_BUFFER_ALIGNMENT                 , 
        minimum_program_texel_offset                          = GL_MIN_PROGRAM_TEXEL_OFFSET                 , 
        minor_version                                         = GL_MINOR_VERSION                            , 
        number_compressed_texture_formats                     = GL_NUM_COMPRESSED_TEXTURE_FORMATS           , 
        number_extensions                                     = GL_NUM_EXTENSIONS                           , 
        number_program_binary_formats                         = GL_NUM_PROGRAM_BINARY_FORMATS               , 
        number_shader_binary_formats                          = GL_NUM_SHADER_BINARY_FORMATS                , 
        pack_alignment                                        = GL_PACK_ALIGNMENT                           , 
        pack_image_height                                     = GL_PACK_IMAGE_HEIGHT                        , 
        pack_row_length                                       = GL_PACK_ROW_LENGTH                          , 
        pack_skip_images                                      = GL_PACK_SKIP_IMAGES                         , 
        pack_skip_pixels                                      = GL_PACK_SKIP_PIXELS                         , 
        pack_skip_rows                                        = GL_PACK_SKIP_ROWS                           , 
        pack_swap_bytes                                       = GL_PACK_SWAP_BYTES                          , 
        parameter_buffer_binding                              = GL_PARAMETER_BUFFER_BINDING                 , 
        patch_default_inner_level                             = GL_PATCH_DEFAULT_INNER_LEVEL                , 
        patch_default_outer_level                             = GL_PATCH_DEFAULT_OUTER_LEVEL                , 
        pixel_pack_buffer_binding                             = GL_PIXEL_PACK_BUFFER_BINDING                , 
        pixel_unpack_buffer_binding                           = GL_PIXEL_UNPACK_BUFFER_BINDING              , 
        point_fade_threshold_size                             = GL_POINT_FADE_THRESHOLD_SIZE                , 
        point_size                                            = GL_POINT_SIZE                               , 
        point_size_granularity                                = GL_POINT_SIZE_GRANULARITY                   , 
        point_size_range                                      = GL_POINT_SIZE_RANGE                         , 
        polygon_offset_factor                                 = GL_POLYGON_OFFSET_FACTOR                    , 
        polygon_offset_units                                  = GL_POLYGON_OFFSET_UNITS                     , 
        polygon_smooth_hint                                   = GL_POLYGON_SMOOTH_HINT                      , 
        primitive_restart_index                               = GL_PRIMITIVE_RESTART_INDEX                  , 
        program_binary_formats                                = GL_PROGRAM_BINARY_FORMATS                   , 
        program_pipeline_binding                              = GL_PROGRAM_PIPELINE_BINDING                 , 
        provoking_vertex                                      = GL_PROVOKING_VERTEX                         , 
        query_buffer_binding                                  = GL_QUERY_BUFFER_BINDING                     , 
        read_buffer                                           = GL_READ_BUFFER                              , 
        read_frame_buffer_binding                             = GL_READ_FRAMEBUFFER_BINDING                 , 
        render_buffer_binding                                 = GL_RENDERBUFFER_BINDING                     , 
        reset_notification_strategy                           = GL_RESET_NOTIFICATION_STRATEGY              , 
        sample_buffers                                        = GL_SAMPLE_BUFFERS                           , 
        sample_coverage_invert                                = GL_SAMPLE_COVERAGE_INVERT                   , 
        sample_coverage_value                                 = GL_SAMPLE_COVERAGE_VALUE                    , 
        sample_mask_value                                     = GL_SAMPLE_MASK_VALUE                        , 
        sampler_binding                                       = GL_SAMPLER_BINDING                          , 
        samples                                               = GL_SAMPLES                                  , 
        scissor_box                                           = GL_SCISSOR_BOX                              , 
        shader_compiler                                       = GL_SHADER_COMPILER                          , 
        shader_storage_buffer_binding                         = GL_SHADER_STORAGE_BUFFER_BINDING            , 
        shader_storage_buffer_offset_alignment                = GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT   , 
        shader_storage_buffer_size                            = GL_SHADER_STORAGE_BUFFER_SIZE               , 
        shader_storage_buffer_start                           = GL_SHADER_STORAGE_BUFFER_START              , 
        smooth_line_width_granularity                         = GL_SMOOTH_LINE_WIDTH_GRANULARITY            , 
        smooth_line_width_range                               = GL_SMOOTH_LINE_WIDTH_RANGE                  , 
        stencil_back_fail                                     = GL_STENCIL_BACK_FAIL                        , 
        stencil_back_function                                 = GL_STENCIL_BACK_FUNC                        , 
        stencil_back_pass_depth_fail                          = GL_STENCIL_BACK_PASS_DEPTH_FAIL             , 
        stencil_back_pass_depth_pass                          = GL_STENCIL_BACK_PASS_DEPTH_PASS             , 
        stencil_back_reference                                = GL_STENCIL_BACK_REF                         , 
        stencil_back_value_mask                               = GL_STENCIL_BACK_VALUE_MASK                  , 
        stencil_back_write_mask                               = GL_STENCIL_BACK_WRITEMASK                   , 
        stencil_clear_value                                   = GL_STENCIL_CLEAR_VALUE                      , 
        stencil_fail                                          = GL_STENCIL_FAIL                             , 
        stencil_function                                      = GL_STENCIL_FUNC                             , 
        stencil_pass_depth_fail                               = GL_STENCIL_PASS_DEPTH_FAIL                  , 
        stencil_pass_depth_pass                               = GL_STENCIL_PASS_DEPTH_PASS                  , 
        stencil_reference                                     = GL_STENCIL_REF                              , 
        stencil_value_mask                                    = GL_STENCIL_VALUE_MASK                       , 
        stencil_write_mask                                    = GL_STENCIL_WRITEMASK                        , 
        stereo                                                = GL_STEREO                                   , 
        sub_pixel_bits                                        = GL_SUBPIXEL_BITS                            , 
        texture_binding_1d                                    = GL_TEXTURE_BINDING_1D                       , 
        texture_binding_1d_array                              = GL_TEXTURE_BINDING_1D_ARRAY                 , 
        texture_binding_2d                                    = GL_TEXTURE_BINDING_2D                       , 
        texture_binding_2d_array                              = GL_TEXTURE_BINDING_2D_ARRAY                 , 
        texture_binding_2d_multisample                        = GL_TEXTURE_BINDING_2D_MULTISAMPLE           , 
        texture_binding_2d_multisample_array                  = GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY     , 
        texture_binding_3d                                    = GL_TEXTURE_BINDING_3D                       , 
        texture_binding_buffer                                = GL_TEXTURE_BINDING_BUFFER                   , 
        texture_binding_cubemap                               = GL_TEXTURE_BINDING_CUBE_MAP                 , 
        texture_binding_rectangle                             = GL_TEXTURE_BINDING_RECTANGLE                , 
        texture_buffer_binding                                = GL_TEXTURE_BUFFER_BINDING                   , 
        texture_buffer_offset_alignment                       = GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT          , 
        texture_compression_hint                              = GL_TEXTURE_COMPRESSION_HINT                 , 
        timestamp                                             = GL_TIMESTAMP                                , 
        transform_feedback_binding                            = GL_TRANSFORM_FEEDBACK_BINDING               , 
        transform_feedback_buffer_binding                     = GL_TRANSFORM_FEEDBACK_BUFFER_BINDING        , 
        transform_feedback_buffer_size                        = GL_TRANSFORM_FEEDBACK_BUFFER_SIZE           , 
        transform_feedback_buffer_start                       = GL_TRANSFORM_FEEDBACK_BUFFER_START          , 
        uniform_buffer_binding                                = GL_UNIFORM_BUFFER_BINDING                   , 
        uniform_buffer_offset_alignment                       = GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT          , 
        uniform_buffer_size                                   = GL_UNIFORM_BUFFER_SIZE                      , 
        uniform_buffer_start                                  = GL_UNIFORM_BUFFER_START                     , 
        unpack_alignment                                      = GL_UNPACK_ALIGNMENT                         , 
        unpack_image_height                                   = GL_UNPACK_IMAGE_HEIGHT                      , 
        unpack_row_length                                     = GL_UNPACK_ROW_LENGTH                        , 
        unpack_skip_images                                    = GL_UNPACK_SKIP_IMAGES                       , 
        unpack_skip_pixels                                    = GL_UNPACK_SKIP_PIXELS                       , 
        unpack_skip_rows                                      = GL_UNPACK_SKIP_ROWS                         , 
        unpack_swap_bytes                                     = GL_UNPACK_SWAP_BYTES                        , 
        vertex_array_binding                                  = GL_VERTEX_ARRAY_BINDING                     , 
        vertex_binding_buffer                                 = GL_VERTEX_BINDING_BUFFER                    , 
        vertex_binding_divisor                                = GL_VERTEX_BINDING_DIVISOR                   , 
        vertex_binding_offset                                 = GL_VERTEX_BINDING_OFFSET                    , 
        vertex_binding_stride                                 = GL_VERTEX_BINDING_STRIDE                    , 
        viewport                                              = GL_VIEWPORT                                 , 
        viewport_bounds_range                                 = GL_VIEWPORT_BOUNDS_RANGE                    , 
        viewport_index_provoking_vertex                       = GL_VIEWPORT_INDEX_PROVOKING_VERTEX          , 
        viewport_sub_pixel_bits                               = GL_VIEWPORT_SUBPIXEL_BITS                   , 
    };
    enum class data_type_e : gl::enum_t
    {
        int8    = GL_BYTE          , 
        int16   = GL_SHORT         , 
        int32   = GL_INT           , 
        
        uint8   = GL_UNSIGNED_BYTE , 
        uint16  = GL_UNSIGNED_SHORT, 
        uint32  = GL_UNSIGNED_INT  , 
        
        float32 = GL_FLOAT         , 
        float64 = GL_DOUBLE        , 
        
        byte    = uint8            , 
    };
    enum class debug_severity_e : gl::enum_t 
    {
        high          = GL_DEBUG_SEVERITY_HIGH        , 
        medium        = GL_DEBUG_SEVERITY_MEDIUM      , 
        low           = GL_DEBUG_SEVERITY_LOW         , 
        notification  = GL_DEBUG_SEVERITY_NOTIFICATION,  
        
        dont_care     = GL_DONT_CARE                  , 
    };
    enum class debug_source_e : gl::enum_t 
    {
        api             = GL_DEBUG_SOURCE_API            , 
        window_system   = GL_DEBUG_SOURCE_WINDOW_SYSTEM  , 
        shader_compiler = GL_DEBUG_SOURCE_SHADER_COMPILER, 
        third_party     = GL_DEBUG_SOURCE_THIRD_PARTY    , 
        application     = GL_DEBUG_SOURCE_APPLICATION    , 
        other           = GL_DEBUG_SOURCE_OTHER          , 
        
        dont_care       = GL_DONT_CARE                   , 
    };
    enum class debug_type_e : gl::enum_t 
    {
        error               = GL_DEBUG_TYPE_ERROR              , 
        deprecated_behavior = GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, 
        undefined_behavior  = GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR , 
        portability         = GL_DEBUG_TYPE_PORTABILITY        , 
        performance         = GL_DEBUG_TYPE_PERFORMANCE        , 
        other               = GL_DEBUG_TYPE_OTHER              , 
        
        marker              = GL_DEBUG_TYPE_MARKER             , 
        push_group          = GL_DEBUG_TYPE_PUSH_GROUP         , 
        pop_group           = GL_DEBUG_TYPE_POP_GROUP          , 
        
        dont_care           = GL_DONT_CARE                     , 
    };
    enum class depth_function_e : gl::enum_t
    {
        never         = GL_NEVER   , 
        less          = GL_LESS    , 
        equal         = GL_EQUAL   , 
        less_equal    = GL_LEQUAL  , 
        greater       = GL_GREATER , 
        not_equal     = GL_NOTEQUAL, 
        greater_equal = GL_GEQUAL  , 
        always        = GL_ALWAYS  , 
    };
    enum class draw_mode_e : gl::enum_t
    {
        points                   = GL_POINTS                  , 
        lines                    = GL_LINES                   , 
        line_loop                = GL_LINE_LOOP               , 
        line_strip               = GL_LINE_STRIP              , 
        triangles                = GL_TRIANGLES               , 
        triangle_strip           = GL_TRIANGLE_STRIP          , 
        triangle_fan             = GL_TRIANGLE_FAN            , 
        lines_adjacency          = GL_LINES_ADJACENCY         , 
        line_strip_adjacency     = GL_LINE_STRIP_ADJACENCY    , 
        triangles_adjacency      = GL_TRIANGLES_ADJACENCY     , 
        triangle_strip_adjacency = GL_TRIANGLE_STRIP_ADJACENCY, 
        patches                  = GL_PATCHES                 , 
    };
    enum class draw_type_e : gl::enum_t
    {
        uint8  = GL_UNSIGNED_BYTE , 
        uint16 = GL_UNSIGNED_SHORT, 
        uint32 = GL_UNSIGNED_INT  , 
    };
    enum class error_flag_e : gl::enum_t
    {
        no_error                       = GL_NO_ERROR                     , 
        
        invalid_enumeration            = GL_INVALID_ENUM                 , 
        invalid_value                  = GL_INVALID_VALUE                , 
        invalid_operation              = GL_INVALID_OPERATION            , 
        stack_overflow                 = GL_STACK_OVERFLOW               , 
        stack_underflow                = GL_STACK_UNDERFLOW              , 
        out_of_memory                  = GL_OUT_OF_MEMORY                , 
        invalid_frame_buffer_operation = GL_INVALID_FRAMEBUFFER_OPERATION, 
    };
    enum class error_graphics_reset_status_e : gl::enum_t
    {
        no_error         = GL_NO_ERROR              , 
        guilty_context   = GL_GUILTY_CONTEXT_RESET  , 
        innocent_context = GL_INNOCENT_CONTEXT_RESET, 
        unknown_context  = GL_UNKNOWN_CONTEXT_RESET , 
    };
    enum class error_sentinel_e : gl::enum_t
    {
        invalid_index = GL_INVALID_INDEX, 
    };
    enum class feature_e : gl::enum_t
    {
        blending                 = GL_BLEND                    , 
        clip_distance            = GL_CLIP_DISTANCE0           , 
        color_logic_operation    = GL_COLOR_LOGIC_OP           , 
        debug_output             = GL_DEBUG_OUTPUT             , 
        debug_output_synchronous = GL_DEBUG_OUTPUT_SYNCHRONOUS , 
        depth_clamp              = GL_DEPTH_CLAMP              , 
        depth_test               = GL_DEPTH_TEST               , 
        dither                   = GL_DITHER                   , 
        face_culling             = GL_CULL_FACE                , 
        multisampling            = GL_MULTISAMPLE              , 
        polygon_smooth           = GL_POLYGON_SMOOTH           , 
        program_point_size       = GL_PROGRAM_POINT_SIZE       , 
        rasterizer_discard       = GL_RASTERIZER_DISCARD       , 
        sample_alpha_to_coverage = GL_SAMPLE_ALPHA_TO_COVERAGE , 
        sample_alpha_to_one      = GL_SAMPLE_ALPHA_TO_ONE      , 
        sample_coverage          = GL_SAMPLE_COVERAGE          , 
        sample_mask              = GL_SAMPLE_MASK              , 
        sample_shading           = GL_SAMPLE_SHADING           , 
        scissor_test             = GL_SCISSOR_TEST             , 
        seamless_cubemap_texture = GL_TEXTURE_CUBE_MAP_SEAMLESS, 
        smooth_lines             = GL_LINE_SMOOTH              , 
        stencil_test             = GL_STENCIL_TEST             , 
    };
    enum class frame_buffer_attachment_e : gl::enum_t
    {
        none           = GL_NONE                    , 
        
        color_0        = GL_COLOR_ATTACHMENT0       , 
        color_1        = GL_COLOR_ATTACHMENT1       , 
        color_2        = GL_COLOR_ATTACHMENT2       , 
        color_3        = GL_COLOR_ATTACHMENT3       , 
        color_4        = GL_COLOR_ATTACHMENT4       , 
        color_5        = GL_COLOR_ATTACHMENT5       , 
        color_6        = GL_COLOR_ATTACHMENT6       , 
        color_7        = GL_COLOR_ATTACHMENT7       , 
        
        depth          = GL_DEPTH_ATTACHMENT        , 
        stencil        = GL_STENCIL_ATTACHMENT      , 
        depth_stencil  = GL_DEPTH_STENCIL_ATTACHMENT,  
    };
    enum class frame_buffer_buffer_e : gl::enum_t
    {
        color   = GL_COLOR  , 
        depth   = GL_DEPTH  , 
        stencil = GL_STENCIL,  
    };
    enum class frame_buffer_filter_e : gl::enum_t
    {
        nearest = GL_NEAREST, 
        linear  = GL_LINEAR , 
    };
    enum class frame_buffer_format_e : gl::enum_t
    {
        r    = GL_RED            , 
        g    = GL_GREEN          , 
        b    = GL_BLUE           , 
        rgb  = GL_RGB            , 
        rgba = GL_RGBA           , 
        bgr  = GL_BGR            , 
        bgra = GL_BGRA           , 
        d    = GL_DEPTH_COMPONENT, 
        s    = GL_STENCIL_INDEX  , 
        ds   = GL_DEPTH_STENCIL  , 
    };
    enum class frame_buffer_parameter_e : gl::enum_t
    {
        color_read_format              = GL_IMPLEMENTATION_COLOR_READ_FORMAT          , 
        color_read_type                = GL_IMPLEMENTATION_COLOR_READ_TYPE            , 
        default_fixed_sample_locations = GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS, 
        default_height                 = GL_FRAMEBUFFER_DEFAULT_HEIGHT                , 
        default_layers                 = GL_FRAMEBUFFER_DEFAULT_LAYERS                , 
        default_samples                = GL_FRAMEBUFFER_DEFAULT_SAMPLES               , 
        default_width                  = GL_FRAMEBUFFER_DEFAULT_WIDTH                 , 
        doublebuffer                   = GL_DOUBLEBUFFER                              , 
        samplebuffers                  = GL_SAMPLE_BUFFERS                            , 
        samples                        = GL_SAMPLES                                   , 
        stereo                         = GL_STEREO                                    , 
    };
    enum class frame_buffer_source_e : gl::enum_t
    {
        none           = GL_NONE             , 
        
        front_left     = GL_FRONT_LEFT       , 
        front_right    = GL_FRONT_RIGHT      , 
        back_left      = GL_BACK_LEFT        , 
        back_right     = GL_BACK_RIGHT       , 
        front          = GL_FRONT            , 
        back           = GL_BACK             , 
        left           = GL_LEFT             , 
        right          = GL_RIGHT            , 
        front_and_back = GL_FRONT_AND_BACK   , 
        
        color_0        = GL_COLOR_ATTACHMENT0, 
        color_1        = GL_COLOR_ATTACHMENT1, 
        color_2        = GL_COLOR_ATTACHMENT2, 
        color_3        = GL_COLOR_ATTACHMENT3, 
        color_4        = GL_COLOR_ATTACHMENT4, 
        color_5        = GL_COLOR_ATTACHMENT5, 
        color_6        = GL_COLOR_ATTACHMENT6, 
        color_7        = GL_COLOR_ATTACHMENT7, 
    };
    enum class frame_buffer_status_e : gl::enum_t
    {
        complete                      = GL_FRAMEBUFFER_COMPLETE                     , 
        
        incomplete_attachment         = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT        , 
        incomplete_missing_attachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT, 
        incomplete_draw_buffer        = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER       , 
        incomplete_read_buffer        = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER       , 
        incomplete_multisample        = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE       , 
        incomplete_layer_targets      = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS     , 
        
        undefined                     = GL_FRAMEBUFFER_UNDEFINED                    , 
        unsupported                   = GL_FRAMEBUFFER_UNSUPPORTED                  , 
    };
    enum class frame_buffer_target_e : gl::enum_t
    {
        read        = GL_READ_FRAMEBUFFER, 
        write       = GL_DRAW_FRAMEBUFFER, 
        read_write  = GL_FRAMEBUFFER     , 
    };
    enum class frame_buffer_type_e : gl::enum_t
    {
        int8    = GL_BYTE          , 
        int16   = GL_SHORT         , 
        int32   = GL_INT           , 
        
        uint8   = GL_UNSIGNED_BYTE , 
        uint16  = GL_UNSIGNED_SHORT, 
        uint32  = GL_UNSIGNED_INT  , 
        
        float16 = GL_HALF_FLOAT    , 
        float32 = GL_FLOAT         , 

        byte    = uint8            , 
    };
    enum class input_primitive_e : gl::enum_t
    {
        points                   = GL_POINTS                  , 
        lines                    = GL_LINES                   , 
        line_loop                = GL_LINE_LOOP               , 
        line_strip               = GL_LINE_STRIP              , 
        triangles                = GL_TRIANGLES               , 
        triangle_strip           = GL_TRIANGLE_STRIP          , 
        triangle_fan             = GL_TRIANGLE_FAN            , 

        lines_adjacency          = GL_LINES_ADJACENCY         , 
        line_strip_adjacency     = GL_LINE_STRIP_ADJACENCY    , 
        triangles_adjacency      = GL_TRIANGLES_ADJACENCY     , 
        triangle_strip_adjacency = GL_TRIANGLE_STRIP_ADJACENCY, 
    };
    enum class output_primitive_e : gl::enum_t
    {
        points         = GL_POINTS        , 
        line_strip     = GL_LINE_STRIP    , 
        triangle_strip = GL_TRIANGLE_STRIP, 
    };
    enum class hint_mode_e : gl::enum_t
    {
        fastest   = GL_FASTEST  , 
        nicest    = GL_NICEST   , 
        
        dont_care = GL_DONT_CARE, 
    };
    enum class hint_target_e : gl::enum_t
    {
        line_smooth                = GL_LINE_SMOOTH_HINT               , 
        polygon_smooth             = GL_POLYGON_SMOOTH_HINT            , 
        texture_compression        = GL_TEXTURE_COMPRESSION_HINT       , 
        fragment_shader_derivative = GL_FRAGMENT_SHADER_DERIVATIVE_HINT, 
    };
    enum class image_access_e : gl::enum_t
    {
        read_only  = GL_READ_ONLY , 
        write_only = GL_WRITE_ONLY, 
        read_write = GL_READ_WRITE, 
    };
    enum class image_format_e : gl::enum_t
    {
        r_int8                   = GL_R8I           , 
        r_int8_n                 = GL_R8_SNORM      , 
        r_int16                  = GL_R16I          , 
        r_int16_n                = GL_R16_SNORM     , 
        r_int32                  = GL_R32I          , 
        r_uint8                  = GL_R8UI          , 
        r_uint8_n                = GL_R8            , 
        r_uint16                 = GL_R16UI         , 
        r_uint16_n               = GL_R16           , 
        r_uint32                 = GL_R32UI         , 
        r_float16                = GL_R16F          , 
        r_float32                = GL_R32F          , 
        
        rg_int8                  = GL_RG8I          , 
        rg_int8_n                = GL_RG8_SNORM     , 
        rg_int16                 = GL_RG16I         , 
        rg_int16_n               = GL_RG16_SNORM    , 
        rg_int32                 = GL_RG32I         , 
        rg_uint8                 = GL_RG8UI         , 
        rg_uint8_n               = GL_RG8           , 
        rg_uint16                = GL_RG16UI        , 
        rg_uint16_n              = GL_RG16          , 
        rg_uint32                = GL_RG32UI        , 
        rg_float16               = GL_RG16F         , 
        rg_float32               = GL_RG32F         , 
        
        rgb_float32_11_11_10     = GL_R11F_G11F_B10F, 
        
        rgba_int8                = GL_RGBA8I        , 
        rgba_int8_n              = GL_RGBA8_SNORM   , 
        rgba_int16               = GL_RGBA16I       , 
        rgba_int16_n             = GL_RGBA16_SNORM  , 
        rgba_int32               = GL_RGBA32I       , 
        rgba_uint8               = GL_RGBA8UI       , 
        rgba_uint8_n             = GL_RGBA8         , 
        rgba_uint16              = GL_RGBA16UI      , 
        rgba_uint16_n            = GL_RGBA16        , 
        rgba_uint32              = GL_RGBA32UI      , 
        rgba_uint32_10_10_10_2   = GL_RGB10_A2UI    , 
        rgba_uint32_10_10_10_2_n = GL_RGB10_A2      , 
        rgba_float16             = GL_RGBA16F       , 
        rgba_float32             = GL_RGBA32F       , 
    };
    enum class logical_pixel_operation_e : gl::enum_t
    {
        clear         = GL_CLEAR        , 
        and_          = GL_AND          , 
        and_reverse   = GL_AND_REVERSE  , 
        copy          = GL_COPY         , 
        and_inverted  = GL_AND_INVERTED , 
        noop          = GL_NOOP         , 
        xor_          = GL_XOR          , 
        or_           = GL_OR           , 
        nor           = GL_NOR          , 
        equivalent    = GL_EQUIV        , 
        invert        = GL_INVERT       , 
        or_reverse    = GL_OR_REVERSE   , 
        copy_inverted = GL_COPY_INVERTED,  
        or_inverted   = GL_OR_INVERTED  , 
        nand          = GL_NAND         , 
        set           = GL_SET          , 
    };
    enum class memory_barrier_e : gl::bitfield_t
    {
        atomic_counter         = GL_ATOMIC_COUNTER_BARRIER_BIT         , 
        buffer_update          = GL_BUFFER_UPDATE_BARRIER_BIT          , 
        client_mapped_buffer   = GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT   , 
        command                = GL_COMMAND_BARRIER_BIT                , 
        element_array          = GL_ELEMENT_ARRAY_BARRIER_BIT          , 
        frame_buffer           = GL_FRAMEBUFFER_BARRIER_BIT            , 
        pixel_buffer           = GL_PIXEL_BUFFER_BARRIER_BIT           , 
        query_buffer           = GL_QUERY_BUFFER_BARRIER_BIT           , 
        shader_global_access   = GL_SHADER_GLOBAL_ACCESS_BARRIER_BIT_NV, //extension
        shader_image_access    = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT    , 
        shader_storage         = GL_SHADER_STORAGE_BARRIER_BIT         , 
        texture_fetch          = GL_TEXTURE_FETCH_BARRIER_BIT          , 
        texture_update         = GL_TEXTURE_UPDATE_BARRIER_BIT         , 
        transform_feedback     = GL_TRANSFORM_FEEDBACK_BARRIER_BIT     , 
        uniform                = GL_UNIFORM_BARRIER_BIT                , 
        vertex_attribute_array = GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT    , 
        
        all                    = GL_ALL_BARRIER_BITS                   , 
    };
    enum class memory_regional_barrier_e : gl::bitfield_t
    {
        atomic_counter      = GL_ATOMIC_COUNTER_BARRIER_BIT_EXT , 
        frame_buffer        = GL_FRAMEBUFFER_BARRIER_BIT        , 
        shader_image_access = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT, 
        shader_storage      = GL_SHADER_STORAGE_BARRIER_BIT     , 
        texture_fetch       = GL_TEXTURE_FETCH_BARRIER_BIT      , 
        uniform             = GL_UNIFORM_BARRIER_BIT            , 
        
        all                 = GL_ALL_BARRIER_BITS               , 
    };
    enum class multisample_parameter_e : gl::enum_t
    {
        sample_position = GL_SAMPLE_POSITION, 
    };
    enum class object_type_e : gl::enum_t
    {
        texture            = GL_TEXTURE           , 
        vertex_array       = GL_VERTEX_ARRAY      , 
        buffer             = GL_BUFFER            , 
        shader             = GL_SHADER            , 
        program            = GL_PROGRAM           , 
        query              = GL_QUERY             , 
        program_pipeline   = GL_PROGRAM_PIPELINE  , 
        sampler            = GL_SAMPLER           , 
        frame_buffer       = GL_FRAMEBUFFER       , 
        render_buffer      = GL_RENDERBUFFER      , 
        transform_feedback = GL_TRANSFORM_FEEDBACK, 
    };
    enum class orientation_e : gl::enum_t
    {
        clockwise         = GL_CW , 
        counter_clockwise = GL_CCW, 
    };
    enum class packing_mode_e : gl::enum_t
    {
        pack_alignment                 = GL_PACK_ALIGNMENT                , 
        pack_compressed_block_depth    = GL_PACK_COMPRESSED_BLOCK_DEPTH   , 
        pack_compressed_block_height   = GL_PACK_COMPRESSED_BLOCK_HEIGHT  , 
        pack_compressed_block_size     = GL_PACK_COMPRESSED_BLOCK_SIZE    , 
        pack_compressed_block_width    = GL_PACK_COMPRESSED_BLOCK_WIDTH   , 
        pack_image_height              = GL_PACK_IMAGE_HEIGHT             , 
        pack_lsb_first                 = GL_PACK_LSB_FIRST                , 
        pack_row_length                = GL_PACK_ROW_LENGTH               , 
        pack_skip_images               = GL_PACK_SKIP_IMAGES              , 
        pack_skip_pixels               = GL_PACK_SKIP_PIXELS              , 
        pack_skip_rows                 = GL_PACK_SKIP_ROWS                , 
        pack_swap_bytes                = GL_PACK_SWAP_BYTES               , 
        unpack_alignment               = GL_UNPACK_ALIGNMENT              , 
        unpack_compressed_block_depth  = GL_UNPACK_COMPRESSED_BLOCK_DEPTH , 
        unpack_compressed_block_height = GL_UNPACK_COMPRESSED_BLOCK_HEIGHT, 
        unpack_compressed_block_size   = GL_UNPACK_COMPRESSED_BLOCK_SIZE  , 
        unpack_compressed_block_width  = GL_UNPACK_COMPRESSED_BLOCK_WIDTH , 
        unpack_image_height            = GL_UNPACK_IMAGE_HEIGHT           , 
        unpack_lsb_first               = GL_UNPACK_LSB_FIRST              , 
        unpack_row_length              = GL_UNPACK_ROW_LENGTH             , 
        unpack_skip_images             = GL_UNPACK_SKIP_IMAGES            , 
        unpack_skip_pixels             = GL_UNPACK_SKIP_PIXELS            , 
        unpack_skip_rows               = GL_UNPACK_SKIP_ROWS              , 
        unpack_swap_bytes              = GL_UNPACK_SWAP_BYTES             , 
    };
    enum class patch_parameter_e : gl::enum_t
    {
        patch_vertices            = GL_PATCH_VERTICES           , 
        patch_default_inner_level = GL_PATCH_DEFAULT_INNER_LEVEL, 
        patch_default_outer_level = GL_PATCH_DEFAULT_OUTER_LEVEL, 
    };
    enum class pixel_data_format_e : gl::enum_t
    {
        r               = GL_RED            , 
        g               = GL_GREEN          , 
        b               = GL_BLUE           , 
        rgb             = GL_RGB            , 
        rgba            = GL_RGBA           , 
        bgr             = GL_BGR            , 
        bgra            = GL_BGRA           , 
        d               = GL_DEPTH_COMPONENT, 
        s               = GL_STENCIL_INDEX  , 
        ds              = GL_DEPTH_STENCIL  , 
    };
    enum class pixel_data_type_e : gl::enum_t
    {
        int8                      = GL_BYTE                          , 
        int16                     = GL_SHORT                         , 
        int32                     = GL_INT                           , 
        
        uint8                     = GL_UNSIGNED_BYTE                 , 
        uint8_3_3_2               = GL_UNSIGNED_BYTE_3_3_2           , 
        uint8_2_3_3_r             = GL_UNSIGNED_BYTE_2_3_3_REV       , 
        uint16                    = GL_UNSIGNED_SHORT                , 
        uint16_4_4_4_4            = GL_UNSIGNED_SHORT_4_4_4_4        , 
        uint16_4_4_4_4_r          = GL_UNSIGNED_SHORT_4_4_4_4_REV    , 
        uint16_5_5_5_1            = GL_UNSIGNED_SHORT_5_5_5_1        , 
        uint16_1_5_5_5_r          = GL_UNSIGNED_SHORT_1_5_5_5_REV    , 
        uint16_5_6_5              = GL_UNSIGNED_SHORT_5_6_5          , 
        uint16_5_6_5_r            = GL_UNSIGNED_SHORT_5_6_5_REV      , 
        uint32                    = GL_UNSIGNED_INT                  , 
        uint32_8_8_8_8            = GL_UNSIGNED_INT_8_8_8_8          , 
        uint32_8_8_8_8_r          = GL_UNSIGNED_INT_8_8_8_8_REV      , 
        uint32_10_10_10_2         = GL_UNSIGNED_INT_10_10_10_2       , 
        uint32_2_10_10_10_r       = GL_UNSIGNED_INT_2_10_10_10_REV   , 
        uint32_24_8               = GL_UNSIGNED_INT_24_8             , 
        uint32_float32_10_11_11_r = GL_UNSIGNED_INT_10F_11F_11F_REV  , 
        uint32_5_9_9_9_r          = GL_UNSIGNED_INT_5_9_9_9_REV      , 
        
        float16                   = GL_HALF_FLOAT                    , 
        float32                   = GL_FLOAT                         , 
        float32_uint32_24_8_r     = GL_FLOAT_32_UNSIGNED_INT_24_8_REV, 
        
        byte                      = uint8                            , 
    };
    enum class polygon_face_e : gl::enum_t
    {
        front_and_back = GL_FRONT_AND_BACK, 
    };
    enum class polygon_mode_e : gl::enum_t
    {
        point = GL_POINT, 
        line  = GL_LINE , 
        fill  = GL_FILL , 
    };
    enum class point_origin_e : gl::enum_t
    {
        lower_left = GL_LOWER_LEFT, 
        upper_left = GL_UPPER_LEFT, 
    };
    enum class point_parameter_e : gl::enum_t
    {
        fade_threshold_size      = GL_POINT_FADE_THRESHOLD_SIZE, 
        sprite_coordinate_origin = GL_POINT_SPRITE_COORD_ORIGIN, 
    };
    enum class pipeline_property_e : gl::enum_t
    {
        active_program                 = GL_ACTIVE_PROGRAM        , 
        compute_shader                 = GL_COMPUTE_SHADER        , 
        fragment_shader                = GL_FRAGMENT_SHADER       , 
        geometry_shader                = GL_GEOMETRY_SHADER       , 
        info_log_length                = GL_INFO_LOG_LENGTH       , 
        tessellation_control_shader    = GL_TESS_CONTROL_SHADER   , 
        tessellation_evaluation_shader = GL_TESS_EVALUATION_SHADER, 
        validate_status                = GL_VALIDATE_STATUS       , 
        vertex_shader                  = GL_VERTEX_SHADER         , 
    };
    enum class program_interface_e : gl::enum_t
    {
        atomic_counter_buffer                      = GL_ATOMIC_COUNTER_BUFFER             , 
        buffer_variable                            = GL_BUFFER_VARIABLE                   , 
        compute_subroutine                         = GL_COMPUTE_SUBROUTINE                , 
        compute_subroutine_uniform                 = GL_COMPUTE_SUBROUTINE_UNIFORM        , 
        fragment_subroutine                        = GL_FRAGMENT_SUBROUTINE               , 
        fragment_subroutine_uniform                = GL_FRAGMENT_SUBROUTINE_UNIFORM       , 
        geometry_subroutine                        = GL_GEOMETRY_SUBROUTINE               , 
        geometry_subroutine_uniform                = GL_GEOMETRY_SUBROUTINE_UNIFORM       , 
        program_input                              = GL_PROGRAM_INPUT                     , 
        program_output                             = GL_PROGRAM_OUTPUT                    , 
        shader_storage_block                       = GL_SHADER_STORAGE_BLOCK              , 
        tessellation_control_subroutine            = GL_TESS_CONTROL_SUBROUTINE           , 
        tessellation_control_subroutine_uniform    = GL_TESS_CONTROL_SUBROUTINE_UNIFORM   , 
        tessellation_evaluation_subroutine         = GL_TESS_EVALUATION_SUBROUTINE        , 
        tessellation_evaluation_subroutine_uniform = GL_TESS_EVALUATION_SUBROUTINE_UNIFORM, 
        transform_feedback_buffer                  = GL_TRANSFORM_FEEDBACK_BUFFER         , 
        transform_feedback_varying                 = GL_TRANSFORM_FEEDBACK_VARYING        , 
        uniform                                    = GL_UNIFORM                           , 
        uniform_block                              = GL_UNIFORM_BLOCK                     , 
        vertex_subroutine                          = GL_VERTEX_SUBROUTINE                 , 
        vertex_subroutine_uniform                  = GL_VERTEX_SUBROUTINE_UNIFORM         , 
    };
    enum class program_parameter_e : gl::enum_t
    {
        active_atomic_counter_buffers             = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS        , 
        active_attribute_maximum_length           = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH          , 
        active_attributes                         = GL_ACTIVE_ATTRIBUTES                    , 
        active_uniform_block_maximum_name_length  = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH , 
        active_uniform_blocks                     = GL_ACTIVE_UNIFORM_BLOCKS                , 
        active_uniform_maximum_length             = GL_ACTIVE_UNIFORM_MAX_LENGTH            , 
        active_uniforms                           = GL_ACTIVE_UNIFORMS                      , 
        attached_shaders                          = GL_ATTACHED_SHADERS                     , 
        binary_length                             = GL_PROGRAM_BINARY_LENGTH                , 
        compute_work_group_size                   = GL_COMPUTE_WORK_GROUP_SIZE              , 
        delete_status                             = GL_DELETE_STATUS                        , 
        geometry_input_type                       = GL_GEOMETRY_INPUT_TYPE                  , 
        geometry_output_type                      = GL_GEOMETRY_OUTPUT_TYPE                 , 
        geometry_shader_invocations               = GL_GEOMETRY_SHADER_INVOCATIONS          , 
        geometry_vertices_out                     = GL_GEOMETRY_VERTICES_OUT                , 
        info_log_length                           = GL_INFO_LOG_LENGTH                      , 
        is_binary_retrievable                     = GL_PROGRAM_BINARY_RETRIEVABLE_HINT      , 
        is_separable                              = GL_PROGRAM_SEPARABLE                    , 
        link_status                               = GL_LINK_STATUS                          , 
        tessellation_control_output_vertices      = GL_TESS_CONTROL_OUTPUT_VERTICES         , 
        tessellation_generation_mode              = GL_TESS_GEN_MODE                        , 
        tessellation_generation_point_mode        = GL_TESS_GEN_POINT_MODE                  , 
        tessellation_generation_spacing           = GL_TESS_GEN_SPACING                     , 
        tessellation_generation_vertex_order      = GL_TESS_GEN_VERTEX_ORDER                , 
        transform_feedback_buffer_mode            = GL_TRANSFORM_FEEDBACK_BUFFER_MODE       , 
        transform_feedback_varying_maximum_length = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH, 
        transform_feedback_varyings               = GL_TRANSFORM_FEEDBACK_VARYINGS          , 
        validate_status                           = GL_VALIDATE_STATUS                      , 
    };
    enum class program_property_e : gl::enum_t
    {
        active_resources               = GL_ACTIVE_RESOURCES              , 
        maximum_active_variables       = GL_MAX_NUM_ACTIVE_VARIABLES      , 
        maximum_compatible_subroutines = GL_MAX_NUM_COMPATIBLE_SUBROUTINES, 
        maximum_name_length            = GL_MAX_NAME_LENGTH               , 
    };
    enum class program_resource_e : gl::enum_t
    {
        active_variables                             = GL_ACTIVE_VARIABLES                    , 
        array_size                                   = GL_ARRAY_SIZE                          , 
        array_stride                                 = GL_ARRAY_STRIDE                        , 
        atomic_counter_buffer_index                  = GL_ATOMIC_COUNTER_BUFFER_INDEX         , 
        block_index                                  = GL_BLOCK_INDEX                         , 
        buffer_binding                               = GL_BUFFER_BINDING                      , 
        buffer_data_size                             = GL_BUFFER_DATA_SIZE                    , 
        compatible_subroutines                       = GL_COMPATIBLE_SUBROUTINES              , 
        is_per_patch                                 = GL_IS_PER_PATCH                        , 
        is_row_major                                 = GL_IS_ROW_MAJOR                        , 
        location                                     = GL_LOCATION                            , 
        location_component                           = GL_LOCATION_COMPONENT                  , 
        location_index                               = GL_LOCATION_INDEX                      , 
        matrix_stride                                = GL_MATRIX_STRIDE                       , 
        name_length                                  = GL_NAME_LENGTH                         , 
        number_active_variables                      = GL_NUM_ACTIVE_VARIABLES                , 
        number_compatible_subroutines                = GL_NUM_COMPATIBLE_SUBROUTINES          , 
        offset                                       = GL_OFFSET                              , 
        referenced_by_compute_shader                 = GL_REFERENCED_BY_COMPUTE_SHADER        , 
        referenced_by_fragment_shader                = GL_REFERENCED_BY_FRAGMENT_SHADER       , 
        referenced_by_geometry_shader                = GL_REFERENCED_BY_GEOMETRY_SHADER       , 
        referenced_by_tessellation_control_shader    = GL_REFERENCED_BY_TESS_CONTROL_SHADER   , 
        referenced_by_tessellation_evaluation_shader = GL_REFERENCED_BY_TESS_EVALUATION_SHADER, 
        referenced_by_vertex_shader                  = GL_REFERENCED_BY_VERTEX_SHADER         , 
        texture_buffer                               = GL_TEXTURE_BUFFER                      , 
        top_level_array_size                         = GL_TOP_LEVEL_ARRAY_SIZE                , 
        top_level_array_stride                       = GL_TOP_LEVEL_ARRAY_STRIDE              , 
        transform_feedback_buffer_index              = GL_TRANSFORM_FEEDBACK_BUFFER_INDEX     , 
        transform_feedback_buffer_stride             = GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE    , 
        type                                         = GL_TYPE                                , 
    };
    enum class program_specification_e : gl::enum_t
    {
        separable          = GL_PROGRAM_SEPARABLE              , 
        binary_retrievable = GL_PROGRAM_BINARY_RETRIEVABLE_HINT, 
    };
    enum class program_stage_e : gl::bitfield_t
    {
        vertex                  = GL_VERTEX_SHADER_BIT         , 
        fragment                = GL_FRAGMENT_SHADER_BIT       , 
        geometry                = GL_GEOMETRY_SHADER_BIT       , 
        tessellation_control    = GL_TESS_CONTROL_SHADER_BIT   , 
        tessellation_evaluation = GL_TESS_EVALUATION_SHADER_BIT, 
        compute                 = GL_COMPUTE_SHADER_BIT        , 
        
        all                     = GL_ALL_SHADER_BITS           , 
    };
    enum class program_stage_property_e : gl::enum_t
    {
        active_subroutine_maximum_length         = GL_ACTIVE_SUBROUTINE_MAX_LENGTH        , 
        active_subroutine_uniform_locations      = GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS , 
        active_subroutine_uniform_maximum_length = GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, 
        active_subroutine_uniforms               = GL_ACTIVE_SUBROUTINE_UNIFORMS          , 
        active_subroutines                       = GL_ACTIVE_SUBROUTINES                  , 
    };
    enum class provoking_vertex_convention_e : gl::enum_t
    {
        first_vertex     = GL_FIRST_VERTEX_CONVENTION, 
        last_vertex      = GL_LAST_VERTEX_CONVENTION , 
        provoking_vertex = GL_PROVOKING_VERTEX       , 
    };
    enum class provoking_vertex_mode_e : gl::enum_t
    {
        first_vertex = GL_FIRST_VERTEX_CONVENTION, 
        last_vertex  = GL_LAST_VERTEX_CONVENTION , 
    };
    enum class query_counter_e : gl::enum_t
    {
        timestamp = GL_TIMESTAMP, 
    };
    enum class query_mode_e : gl::enum_t
    {
        wait             = GL_QUERY_WAIT             , 
        no_wait          = GL_QUERY_NO_WAIT          , 
        region_wait      = GL_QUERY_BY_REGION_WAIT   , 
        region_no_wait   = GL_QUERY_BY_REGION_NO_WAIT, 
        wait_inverted    = GL_QUERY_WAIT_INVERTED    , 
        no_wait_inverted = GL_QUERY_NO_WAIT_INVERTED , 
    };
    enum class query_parameter_e : gl::enum_t
    {
        target           = GL_QUERY_TARGET          , 
        
        result           = GL_QUERY_RESULT          , 
        result_available = GL_QUERY_RESULT_AVAILABLE, 
        result_no_wait   = GL_QUERY_RESULT_NO_WAIT  , 
    };
    enum class query_symbol_e : gl::enum_t
    {
        counter_bits = GL_QUERY_COUNTER_BITS, 
        current      = GL_CURRENT_QUERY     , 
    };
    enum class query_target_e : gl::enum_t
    {
        any_samples_passed                         = GL_ANY_SAMPLES_PASSED                   , 
        any_samples_passed_conservative            = GL_ANY_SAMPLES_PASSED_CONSERVATIVE      , 
        clipping_input_primitives                  = GL_CLIPPING_INPUT_PRIMITIVES            , 
        clipping_output_primitives                 = GL_CLIPPING_OUTPUT_PRIMITIVES           , 
        compute_shader_invocations                 = GL_COMPUTE_SHADER_INVOCATIONS           , 
        fragment_shader_invocations                = GL_FRAGMENT_SHADER_INVOCATIONS          , 
        geometry_shader_invocations                = GL_GEOMETRY_SHADER_INVOCATIONS          , 
        geometry_shader_primitives_emitted         = GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED   , 
        primitives_generated                       = GL_PRIMITIVES_GENERATED                 , 
        primitives_submitted                       = GL_PRIMITIVES_SUBMITTED                 , 
        samples_passed                             = GL_SAMPLES_PASSED                       , 
        tessellation_control_shader_patches        = GL_TESS_CONTROL_SHADER_PATCHES          , 
        tessellation_evaluation_shader_invocations = GL_TESS_EVALUATION_SHADER_INVOCATIONS   , 
        time_elapsed                               = GL_TIME_ELAPSED                         , 
        timestamp                                  = GL_TIMESTAMP                            , 
        transform_feedback_overflow                = GL_TRANSFORM_FEEDBACK_OVERFLOW          , 
        transform_feedback_primitives_written      = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, 
        transform_feedback_stream_overflow         = GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW   , 
        vertex_shader_invocations                  = GL_VERTEX_SHADER_INVOCATIONS            , 
        vertices_submitted                         = GL_VERTICES_SUBMITTED                   , 
    };
    enum class render_buffer_format_e : gl::enum_t
    {
        r_uint8_n         = GL_R8               , 
        
        rg_uint8_n        = GL_RG8              , 
        
        rgb_uint8_n       = GL_RGB8             , 
        
        rgba_uint8_n      = GL_RGBA8            , 
        rgba_uint8_s      = GL_SRGB8_ALPHA8     , 
        
        d_uint16_n        = GL_DEPTH_COMPONENT16, 
        d_uint24_n        = GL_DEPTH_COMPONENT24, 
        d_float32         = GL_DEPTH_COMPONENT32, 
        s_uint8           = GL_STENCIL_INDEX8   , 
        ds_uint32_24_8    = GL_DEPTH24_STENCIL8 , 
        ds_float32_uint8  = GL_DEPTH32F_STENCIL8, 
    };
    enum class render_buffer_parameter_e : gl::enum_t
    {
        alpha_size      = GL_RENDERBUFFER_ALPHA_SIZE     , 
        blue_size       = GL_RENDERBUFFER_BLUE_SIZE      , 
        depth_size      = GL_RENDERBUFFER_DEPTH_SIZE     , 
        green_size      = GL_RENDERBUFFER_GREEN_SIZE     , 
        height          = GL_RENDERBUFFER_HEIGHT         , 
        internal_format = GL_RENDERBUFFER_INTERNAL_FORMAT, 
        red_size        = GL_RENDERBUFFER_RED_SIZE       , 
        samples         = GL_RENDERBUFFER_SAMPLES        , 
        stencil_size    = GL_RENDERBUFFER_STENCIL_SIZE   , 
        width           = GL_RENDERBUFFER_WIDTH          , 
    };
    enum class render_buffer_target_e : gl::enum_t
    {
        render_buffer = GL_RENDERBUFFER, 
    };
    enum class reset_notification_strategy_e : gl::enum_t
    {
        lose_context    = GL_LOSE_CONTEXT_ON_RESET, 
        no_notification = GL_NO_RESET_NOTIFICATION, 
    };
    enum class sampler_parameter_e : gl::enum_t
    {
        border_color         = GL_TEXTURE_BORDER_COLOR  , 
        compare_function     = GL_TEXTURE_COMPARE_FUNC  , 
        compare_mode         = GL_TEXTURE_COMPARE_MODE  , 
        lod_bias             = GL_TEXTURE_LOD_BIAS      , 
        magnification_filter = GL_TEXTURE_MAG_FILTER    , 
        maximum_anisotropy   = GL_TEXTURE_MAX_ANISOTROPY, 
        maximum_lod          = GL_TEXTURE_MAX_LOD       , 
        minification_filter  = GL_TEXTURE_MIN_FILTER    , 
        minimum_lod          = GL_TEXTURE_MIN_LOD       , 
        wrapping_r           = GL_TEXTURE_WRAP_R        , 
        wrapping_s           = GL_TEXTURE_WRAP_S        , 
        wrapping_t           = GL_TEXTURE_WRAP_T        , 
    };
    enum class shader_parameter_e : gl::enum_t
    {
        compile_status  = GL_COMPILE_STATUS      , 
        delete_status   = GL_DELETE_STATUS       , 
        info_log_length = GL_INFO_LOG_LENGTH     , 
        source_length   = GL_SHADER_SOURCE_LENGTH, 
        spir_v_binary   = GL_SPIR_V_BINARY       , 
        type            = GL_SHADER_TYPE         , 
    };
    enum class shader_precision_format_e : gl::enum_t
    {
        low_integer    = GL_LOW_INT     , 
        medium_integer = GL_MEDIUM_INT  , 
        high_integer   = GL_HIGH_INT    , 
        low_float      = GL_LOW_FLOAT   , 
        medium_float   = GL_MEDIUM_FLOAT, 
        high_float     = GL_HIGH_FLOAT  , 
    };
    enum class shader_type_e : gl::enum_t
    {
        vertex                  = GL_VERTEX_SHADER         , 
        tessellation_control    = GL_TESS_CONTROL_SHADER   , 
        tessellation_evaluation = GL_TESS_EVALUATION_SHADER, 
        geometry                = GL_GEOMETRY_SHADER       , 
        fragment                = GL_FRAGMENT_SHADER       , 
        compute                 = GL_COMPUTE_SHADER        , 
    };
    enum class stencil_action_e : gl::enum_t
    {
        zero           = GL_ZERO     , 
        invert         = GL_INVERT   , 
        keep           = GL_KEEP     , 
        replace        = GL_REPLACE  , 
        increment      = GL_INCR     , 
        decrement      = GL_DECR     , 
        increment_wrap = GL_INCR_WRAP, 
        decrement_wrap = GL_DECR_WRAP, 
    };
    enum class stencil_face_e : gl::enum_t
    {
        front          = GL_FRONT         , 
        back           = GL_BACK          , 
        front_and_back = GL_FRONT_AND_BACK, 
    };
    enum class stencil_function_e : gl::enum_t
    {
        never         = GL_NEVER   , 
        less          = GL_LESS    , 
        equal         = GL_EQUAL   , 
        less_equal    = GL_LEQUAL  , 
        greater       = GL_GREATER , 
        not_equal     = GL_NOTEQUAL, 
        greater_equal = GL_GEQUAL  , 
        always        = GL_ALWAYS  , 
    };
    enum class synchronization_command_e : gl::bitfield_t
    {
        none  = GL_NONE                   , 
        flush = GL_SYNC_FLUSH_COMMANDS_BIT, 
    };
    enum class synchronization_object_condition_e : gl::enum_t
    {
        gpu_commands_complete = GL_SYNC_GPU_COMMANDS_COMPLETE, 
    };
    enum class synchronization_object_flags_e : gl::enum_t
    {
        none = GL_NONE, 
    };
    enum class synchronization_object_status_e : gl::enum_t
    {
        unsignaled = GL_UNSIGNALED, 
        signaled   = GL_SIGNALED  , 
    };
    enum class synchronization_object_type_e : gl::enum_t
    {
        fence = GL_SYNC_FENCE, 
    };
    enum class synchronization_property_e : gl::enum_t
    {
        condition = GL_SYNC_CONDITION, 
        flags     = GL_SYNC_FLAGS    , 
        status    = GL_SYNC_STATUS   , 
        type      = GL_OBJECT_TYPE   , 
    };
    enum class synchronization_status_e : gl::enum_t
    {
        already_signaled    = GL_ALREADY_SIGNALED   , 
        condition_satisfied = GL_CONDITION_SATISFIED, 
        timeout_expired     = GL_TIMEOUT_EXPIRED    , 
        wait_failed         = GL_WAIT_FAILED        , 
    };
    enum class synchronization_timeout_e : gl::uint64_t
    {
        ignored = GL_TIMEOUT_IGNORED, 
    };
    enum class texture_base_format_e : gl::enum_t
    {
        r       = GL_RED            , 
        rg      = GL_RG             , 
        rgb     = GL_RGB            , 
        rgba    = GL_RGBA           , 
        d       = GL_DEPTH_COMPONENT, 
        s       = GL_STENCIL_INDEX  , 
    };
    enum class texture_compare_function_e : gl::enum_t
    {
        never         = GL_NEVER   , 
        less          = GL_LESS    , 
        equal         = GL_EQUAL   , 
        less_equal    = GL_LEQUAL  , 
        greater       = GL_GREATER , 
        not_equal     = GL_NOTEQUAL, 
        greater_equal = GL_GEQUAL  , 
        always        = GL_ALWAYS  , 
    };
    enum class texture_compare_mode_e : gl::enum_t
    {
        none      = GL_NONE                  , 
        reference = GL_COMPARE_REF_TO_TEXTURE, 
    };
    enum class texture_compressed_format_e : gl::enum_t
    {
        rgb_s3tc_dxt1   = GL_COMPRESSED_RGB_S3TC_DXT1_EXT       , 
        rgba_s3tc_dxt1  = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT      , 
        rgba_s3tc_dxt3  = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT      , 
        rgba_s3tc_dxt5  = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT      , 
        srgb_s3tc_dxt1  = GL_COMPRESSED_SRGB_S3TC_DXT1_EXT      , 
        srgba_s3tc_dxt1 = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT, 
        srgba_s3tc_dxt3 = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT, 
        srgba_s3tc_dxt5 = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT, 
    };
    enum class texture_format_e : gl::enum_t
    {
        r_int8_n          = GL_R8_SNORM          , 
        r_int16_n         = GL_R16_SNORM         , 
        r_uint8_n         = GL_R8                , 
        r_uint16_n        = GL_R16               , 
        r_float16         = GL_R16F              , 
        r_float32         = GL_R32F              , 
        
        rg_int8_n         = GL_RG8_SNORM         , 
        rg_int16_n        = GL_RG16_SNORM        , 
        rg_uint8_n        = GL_RG8               , 
        rg_uint16_n       = GL_RG16              , 
        rg_float16        = GL_RG16F             , 
        rg_float32        = GL_RG32F             , 
        
        rgb_int8_n        = GL_RGB8_SNORM        , 
        rgb_int16_n       = GL_RGB16_SNORM       , 
        rgb_uint8_n       = GL_RGB8              , 
        rgb_uint16_n      = GL_RGB16             , 
        rgb_float16       = GL_RGB16F            , 
        rgb_float32       = GL_RGB32F            , 
        
        rgba_int8_n       = GL_RGBA8_SNORM       , 
        rgba_int16_n      = GL_RGBA16_SNORM      , 
        rgba_uint8_n      = GL_RGBA8             , 
        rgba_uint16_n     = GL_RGBA16            , 
        rgba_float16      = GL_RGBA16F           , 
        rgba_float32      = GL_RGBA32F           , 
        
        srgb_uint8        = GL_SRGB8             , 
        srgba_uint8       = GL_SRGB8_ALPHA8      , 
        
        d_uint16_n        = GL_DEPTH_COMPONENT16 , 
        d_uint24_n        = GL_DEPTH_COMPONENT24 , 
        d_float32         = GL_DEPTH_COMPONENT32F, 
        s_uint8           = GL_STENCIL_INDEX8    , 
        ds_uint24_n_uint8 = GL_DEPTH24_STENCIL8  , 
        ds_float32_uint8  = GL_DEPTH32F_STENCIL8 , 
    };
    enum class texture_magnification_filter_e : gl::enum_t
    {
        nearest = GL_NEAREST, 
        linear  = GL_LINEAR , 
    };
    enum class texture_minification_filter_e : gl::enum_t
    {
        nearest                = GL_NEAREST               , 
        linear                 = GL_LINEAR                ,  
        
        nearest_mipmap_nearest = GL_NEAREST_MIPMAP_NEAREST, 
        linear_mipmap_nearest  = GL_LINEAR_MIPMAP_NEAREST , 
        nearest_mipmap_linear  = GL_NEAREST_MIPMAP_LINEAR , 
        linear_mipmap_linear   = GL_LINEAR_MIPMAP_LINEAR  , 
    };
    enum class texture_parameter_e : gl::enum_t
    {
        base_level           = GL_TEXTURE_BASE_LEVEL        , 
        border_color         = GL_TEXTURE_BORDER_COLOR      , 
        compare_function     = GL_TEXTURE_COMPARE_FUNC      , 
        compare_mode         = GL_TEXTURE_COMPARE_MODE      , 
        depth_stencil_mode   = GL_DEPTH_STENCIL_TEXTURE_MODE, 
        lod_bias             = GL_TEXTURE_LOD_BIAS          , 
        magnification_filter = GL_TEXTURE_MAG_FILTER        , 
        maximum_anisotropy   = GL_TEXTURE_MAX_ANISOTROPY    , 
        maximum_level        = GL_TEXTURE_MAX_LEVEL         , 
        maximum_lod          = GL_TEXTURE_MAX_LOD           , 
        minification_filter  = GL_TEXTURE_MIN_FILTER        , 
        minimum_lod          = GL_TEXTURE_MIN_LOD           , 
        swizzle_a            = GL_TEXTURE_SWIZZLE_A         , 
        swizzle_b            = GL_TEXTURE_SWIZZLE_B         , 
        swizzle_g            = GL_TEXTURE_SWIZZLE_G         , 
        swizzle_r            = GL_TEXTURE_SWIZZLE_R         , 
        swizzle_rgba         = GL_TEXTURE_SWIZZLE_RGBA      , 
        wrapping_r           = GL_TEXTURE_WRAP_R            , 
        wrapping_s           = GL_TEXTURE_WRAP_S            , 
        wrapping_t           = GL_TEXTURE_WRAP_T            , 
    };
    enum class texture_swizzle_e : gl::enum_t
    {
        zero  = GL_ZERO , 
        one   = GL_ONE  , 
        
        red   = GL_RED  , 
        green = GL_GREEN,  
        blue  = GL_BLUE , 
        alpha = GL_ALPHA,  
    };
    enum class texture_target_e : gl::enum_t
    {
        _1d                   = GL_TEXTURE_1D                  , 
        _2d                   = GL_TEXTURE_2D                  , 
        _3d                   = GL_TEXTURE_3D                  , 
        _1d_array             = GL_TEXTURE_1D_ARRAY            , 
        _2d_array             = GL_TEXTURE_2D_ARRAY            , 
        _2d_multisample       = GL_TEXTURE_2D_MULTISAMPLE      , 
        _2d_multisample_array = GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 
        
        cubemap               = GL_TEXTURE_CUBE_MAP            , 
        cubemap_array         = GL_TEXTURE_CUBE_MAP_ARRAY      , 
        
        rectangle             = GL_TEXTURE_RECTANGLE           , 
        buffer                = GL_TEXTURE_BUFFER              , 
    };
    enum class texture_type_e : gl::enum_t
    {
        int8    = GL_BYTE          , 
        int16   = GL_SHORT         , 
        int32   = GL_INT           , 
        
        uint8   = GL_UNSIGNED_BYTE , 
        uint16  = GL_UNSIGNED_SHORT, 
        uint32  = GL_UNSIGNED_INT  , 
        
        float32 = GL_FLOAT         , 
        
        byte    = uint8            , 
    };
    enum class texture_wrapping_e : gl::enum_t
    {
        repeat                 = GL_REPEAT              , 
        clamp_to_border        = GL_CLAMP_TO_BORDER     , 
        clamp_to_edge          = GL_CLAMP_TO_EDGE       , 
        mirrored_repeat        = GL_MIRRORED_REPEAT     , 
        mirrored_clamp_to_edge = GL_MIRROR_CLAMP_TO_EDGE, 
    };
    enum class tessellation_generation_e : gl::enum_t
    {
        triangles = GL_TRIANGLES, 
        quads     = GL_QUADS    , 
        isolines  = GL_ISOLINES , 
    };
    enum class tessellation_spacing_e : gl::enum_t
    {
        equal           = GL_EQUAL          ,  
        fractional_odd  = GL_FRACTIONAL_ODD , 
        fractional_even = GL_FRACTIONAL_EVEN, 
    };
    enum class tessellation_vertex_order_e : gl::enum_t
    {
        clockwise         = GL_CW , 
        counter_clockwise = GL_CCW, 
    };
    enum class transform_feedback_buffer_mode_e : gl::enum_t
    {
        interleaved_attributes = GL_INTERLEAVED_ATTRIBS,  
        separate_attributes    = GL_SEPARATE_ATTRIBS   , 
    };
    enum class transform_feedback_primitive_mode_e : gl::enum_t
    {
        points    = GL_POINTS   , 
        lines     = GL_LINES    , 
        triangles = GL_TRIANGLES, 
    };
    enum class transform_feedback_property_e : gl::enum_t
    {
        active         = GL_TRANSFORM_FEEDBACK_ACTIVE        , 
        buffer_binding = GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, 
        buffer_size    = GL_TRANSFORM_FEEDBACK_BUFFER_SIZE   , 
        buffer_start   = GL_TRANSFORM_FEEDBACK_BUFFER_START  , 
        paused         = GL_TRANSFORM_FEEDBACK_PAUSED        , 
    };
    enum class uniform_property_e : gl::enum_t
    {
        array_stride                = GL_UNIFORM_ARRAY_STRIDE               , 
        atomic_counter_buffer_index = GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX, 
        block_index                 = GL_UNIFORM_BLOCK_INDEX                , 
        is_row_major                = GL_UNIFORM_IS_ROW_MAJOR               , 
        matrix_stride               = GL_UNIFORM_MATRIX_STRIDE              , 
        name_length                 = GL_UNIFORM_NAME_LENGTH                , 
        offset                      = GL_UNIFORM_OFFSET                     , 
        size                        = GL_UNIFORM_SIZE                       , 
        type                        = GL_UNIFORM_TYPE                       , 
    };
    enum class uniform_type_e : gl::enum_t
    {
        bool_                            = GL_BOOL                                     , 
        
        float32                          = GL_FLOAT                                    , 
        float64                          = GL_DOUBLE                                   , 
        
        image_buffer                     = GL_IMAGE_BUFFER                             , 
        image_cube                       = GL_IMAGE_CUBE                               , 
        image1d                          = GL_IMAGE_1D                                 , 
        image1d_array                    = GL_IMAGE_1D_ARRAY                           , 
        image2d                          = GL_IMAGE_2D                                 , 
        image2d_array                    = GL_IMAGE_2D_ARRAY                           , 
        image2d_multisample              = GL_IMAGE_2D_MULTISAMPLE                     , 
        image2d_multisample_array        = GL_IMAGE_2D_MULTISAMPLE_ARRAY               , 
        image2d_rectangle                = GL_IMAGE_2D_RECT                            , 
        image3d                          = GL_IMAGE_3D                                 , 
        
        int_image_buffer                 = GL_INT_IMAGE_BUFFER                         , 
        int_image_cube                   = GL_INT_IMAGE_CUBE                           , 
        int_image1d                      = GL_INT_IMAGE_1D                             , 
        int_image1d_array                = GL_INT_IMAGE_1D_ARRAY                       , 
        int_image2d                      = GL_INT_IMAGE_2D                             , 
        int_image2d_array                = GL_INT_IMAGE_2D_ARRAY                       , 
        int_image2d_multisample          = GL_INT_IMAGE_2D_MULTISAMPLE                 , 
        int_image2d_multisample_array    = GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY           , 
        int_image2d_rectangle            = GL_INT_IMAGE_2D_RECT                        , 
        int_image3d                      = GL_INT_IMAGE_3D                             , 
        int_sampler_buffer               = GL_INT_SAMPLER_BUFFER                       , 
        int_sampler_cube                 = GL_INT_SAMPLER_CUBE                         , 
        int_sampler1d                    = GL_INT_SAMPLER_1D                           , 
        int_sampler1d_array              = GL_INT_SAMPLER_1D_ARRAY                     , 
        int_sampler2d                    = GL_INT_SAMPLER_2D                           , 
        int_sampler2d_array              = GL_INT_SAMPLER_2D_ARRAY                     , 
        int_sampler2d_multisample        = GL_INT_SAMPLER_2D_MULTISAMPLE               , 
        int_sampler2d_multisample_array  = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY         , 
        int_sampler2d_rectangle          = GL_INT_SAMPLER_2D_RECT                      , 
        int_sampler3d                    = GL_INT_SAMPLER_3D                           , 
        int32                            = GL_INT                                      , 
        
        matrix2d                         = GL_DOUBLE_MAT2                              , 
        matrix2f                         = GL_FLOAT_MAT2                               , 
        matrix2x3d                       = GL_DOUBLE_MAT2x3                            , 
        matrix2x3f                       = GL_FLOAT_MAT2x3                             , 
        matrix2x4d                       = GL_DOUBLE_MAT2x4                            , 
        matrix2x4f                       = GL_FLOAT_MAT2x4                             , 
        matrix3d                         = GL_DOUBLE_MAT3                              , 
        matrix3f                         = GL_FLOAT_MAT3                               , 
        matrix3x2d                       = GL_DOUBLE_MAT3x2                            , 
        matrix3x2f                       = GL_FLOAT_MAT3x2                             , 
        matrix3x4d                       = GL_DOUBLE_MAT3x4                            , 
        matrix3x4f                       = GL_FLOAT_MAT3x4                             , 
        matrix4d                         = GL_DOUBLE_MAT4                              , 
        matrix4f                         = GL_FLOAT_MAT4                               , 
        matrix4x2d                       = GL_DOUBLE_MAT4x2                            , 
        matrix4x2f                       = GL_FLOAT_MAT4x2                             , 
        matrix4x3d                       = GL_DOUBLE_MAT4x3                            , 
        matrix4x3f                       = GL_FLOAT_MAT4x3                             , 
        
        sampler_buffer                   = GL_SAMPLER_BUFFER                           , 
        sampler_cube                     = GL_SAMPLER_CUBE                             , 
        sampler_cube_shadow              = GL_SAMPLER_CUBE_SHADOW                      , 
        sampler1d                        = GL_SAMPLER_1D                               , 
        sampler1d_array                  = GL_SAMPLER_1D_ARRAY                         , 
        sampler1d_array_shadow           = GL_SAMPLER_1D_ARRAY_SHADOW                  , 
        sampler1d_shadow                 = GL_SAMPLER_1D_SHADOW                        , 
        sampler2d                        = GL_SAMPLER_2D                               , 
        sampler2d_array                  = GL_SAMPLER_2D_ARRAY                         , 
        sampler2d_array_shadow           = GL_SAMPLER_2D_ARRAY_SHADOW                  , 
        sampler2d_multisample            = GL_SAMPLER_2D_MULTISAMPLE                   , 
        sampler2d_multisample_array      = GL_SAMPLER_2D_MULTISAMPLE_ARRAY             , 
        sampler2d_rectangle              = GL_SAMPLER_2D_RECT                          , 
        sampler2d_rectangle_shadow       = GL_SAMPLER_2D_RECT_SHADOW                   , 
        sampler2d_shadow                 = GL_SAMPLER_2D_SHADOW                        , 
        sampler3d                        = GL_SAMPLER_3D                               , 
        
        uint_atomic_counter              = GL_UNSIGNED_INT_ATOMIC_COUNTER              , 
        uint_image_buffer                = GL_UNSIGNED_INT_IMAGE_BUFFER                , 
        uint_image_cube                  = GL_UNSIGNED_INT_IMAGE_CUBE                  , 
        uint_image1d                     = GL_UNSIGNED_INT_IMAGE_1D                    , 
        uint_image1d_array               = GL_UNSIGNED_INT_IMAGE_1D_ARRAY              , 
        uint_image2d                     = GL_UNSIGNED_INT_IMAGE_2D                    , 
        uint_image2d_array               = GL_UNSIGNED_INT_IMAGE_2D_ARRAY              , 
        uint_image2d_multisample         = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE        , 
        uint_image2d_multisample_array   = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY  , 
        uint_image2d_rectangle           = GL_UNSIGNED_INT_IMAGE_2D_RECT               , 
        uint_image3d                     = GL_UNSIGNED_INT_IMAGE_3D                    , 
        uint_sampler_buffer              = GL_UNSIGNED_INT_SAMPLER_BUFFER              , 
        uint_sampler_cube                = GL_UNSIGNED_INT_SAMPLER_CUBE                , 
        uint_sampler1d                   = GL_UNSIGNED_INT_SAMPLER_1D                  , 
        uint_sampler1d_array             = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY            , 
        uint_sampler2d                   = GL_UNSIGNED_INT_SAMPLER_2D                  , 
        uint_sampler2d_array             = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY            , 
        uint_sampler2d_multisample       = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE      , 
        uint_sampler2d_multisample_array = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, 
        uint_sampler2d_rectangle         = GL_UNSIGNED_INT_SAMPLER_2D_RECT             , 
        uint_sampler3d                   = GL_UNSIGNED_INT_SAMPLER_3D                  , 
        uint32                           = GL_UNSIGNED_INT                             , 
        
        vector2b                         = GL_BOOL_VEC2                                , 
        vector2d                         = GL_DOUBLE_VEC2                              , 
        vector2f                         = GL_FLOAT_VEC2                               , 
        vector2i                         = GL_INT_VEC2                                 , 
        vector2u                         = GL_UNSIGNED_INT_VEC2                        , 
        vector3b                         = GL_BOOL_VEC3                                , 
        vector3d                         = GL_DOUBLE_VEC3                              , 
        vector3f                         = GL_FLOAT_VEC3                               , 
        vector3i                         = GL_INT_VEC3                                 , 
        vector3u                         = GL_UNSIGNED_INT_VEC3                        , 
        vector4b                         = GL_BOOL_VEC4                                , 
        vector4d                         = GL_DOUBLE_VEC4                              , 
        vector4f                         = GL_FLOAT_VEC4                               , 
        vector4i                         = GL_INT_VEC4                                 , 
        vector4u                         = GL_UNSIGNED_INT_VEC4                        , 
    };
    enum class uniform_block_info_e : gl::enum_t
    {
        active_uniform_indices                       = GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES              , 
        active_uniforms                              = GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS                     , 
        binding                                      = GL_UNIFORM_BLOCK_BINDING                             , 
        data_size                                    = GL_UNIFORM_BLOCK_DATA_SIZE                           , 
        name_length                                  = GL_UNIFORM_BLOCK_NAME_LENGTH                         , 
        referenced_by_compute_shader                 = GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER        , 
        referenced_by_fragment_shader                = GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER       , 
        referenced_by_geometry_shader                = GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER       , 
        referenced_by_tessellation_control_shader    = GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER   , 
        referenced_by_tessellation_evaluation_shader = GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER, 
        referenced_by_vertex_shader                  = GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER         , 
    };
    enum class vertex_array_attribute_type_e : gl::enum_t
    {
        int8                       = GL_BYTE                        , 
        int16                      = GL_SHORT                       , 
        int32                      = GL_INT                         , 
        int32_2_10_10_10_r         = GL_INT_2_10_10_10_REV          , 
        
        uint8                      = GL_UNSIGNED_BYTE               , 
        uint16                     = GL_UNSIGNED_SHORT              , 
        uint32                     = GL_UNSIGNED_INT                , 
        uint32_2_10_10_10_r        = GL_UNSIGNED_INT_2_10_10_10_REV , 
        uint32_10_11_11_11_float_r = GL_UNSIGNED_INT_10F_11F_11F_REV,   
        
        fixed                      = GL_FIXED                       , 
        float16                    = GL_HALF_FLOAT                  , 
        float32                    = GL_FLOAT                       , 
        float64                    = GL_DOUBLE                      , 
    };
    enum class vertex_array_parameter_e : gl::enum_t
    {
        binding_offset               = GL_VERTEX_BINDING_OFFSET         , 
        divisor                      = GL_VERTEX_ATTRIB_ARRAY_DIVISOR   , 
        element_array_buffer_binding = GL_ELEMENT_ARRAY_BUFFER_BINDING  , 
        enabled                      = GL_VERTEX_ATTRIB_ARRAY_ENABLED   , 
        is_integer_data              = GL_VERTEX_ATTRIB_ARRAY_INTEGER   , 
        is_long_data                 = GL_VERTEX_ATTRIB_ARRAY_LONG      , 
        is_normalized                = GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, 
        relative_offset              = GL_VERTEX_ATTRIB_RELATIVE_OFFSET , 
        size                         = GL_VERTEX_ATTRIB_ARRAY_SIZE      , 
        stride                       = GL_VERTEX_ATTRIB_ARRAY_STRIDE    , 
        type                         = GL_VERTEX_ATTRIB_ARRAY_TYPE      , 
    };
    enum class vertex_attribute_address_e : gl::enum_t
    {
        pointer = GL_VERTEX_ATTRIB_ARRAY_POINTER, 
    };
    enum class vertex_attribute_parameter_e : gl::enum_t
    {
        binding         = GL_VERTEX_ATTRIB_BINDING             , 
        buffer_binding  = GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, 
        current         = GL_CURRENT_VERTEX_ATTRIB             , 
        divisor         = GL_VERTEX_ATTRIB_ARRAY_DIVISOR       , 
        enabled         = GL_VERTEX_ATTRIB_ARRAY_ENABLED       , 
        is_integer_data = GL_VERTEX_ATTRIB_ARRAY_INTEGER       , 
        is_long_data    = GL_VERTEX_ATTRIB_ARRAY_LONG          , 
        is_normalized   = GL_VERTEX_ATTRIB_ARRAY_NORMALIZED    , 
        relative_offset = GL_VERTEX_ATTRIB_RELATIVE_OFFSET     , 
        size            = GL_VERTEX_ATTRIB_ARRAY_SIZE          , 
        stride          = GL_VERTEX_ATTRIB_ARRAY_STRIDE        , 
        type            = GL_VERTEX_ATTRIB_ARRAY_TYPE          , 
    };
    enum class vertex_attribute_pointer_e : gl::enum_t
    {
        array = GL_VERTEX_ATTRIB_ARRAY_POINTER, 
    };





    enum class enum_operation_e : gl::uint32_t
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
    
    constexpr auto operator&              (gl::enum_operation_e left   , gl::enum_operation_e right) -> gl::enum_operation_e { return std::bit_cast<gl::enum_operation_e>(std::to_underlying(left) & std::to_underlying(right)); }
    constexpr auto operator|              (gl::enum_operation_e left   , gl::enum_operation_e right) -> gl::enum_operation_e { return std::bit_cast<gl::enum_operation_e>(std::to_underlying(left) | std::to_underlying(right)); }
    constexpr auto supports_enum_operation(gl::enum_operation_e enabled, gl::enum_operation_e check) -> gl::bool_t           { return (enabled & check) == check; }

    template<typename T> struct enum_operation { static constexpr auto value = gl::enum_operation_e::none; };
    template<typename T> constexpr auto enum_operation_v = gl::enum_operation<T>::value;

    template<typename T> concept has_addition    = std::is_enum_v<T> && gl::supports_enum_operation(gl::enum_operation_v<T>, gl::enum_operation_e::addition   );
    template<typename T> concept has_subtraction = std::is_enum_v<T> && gl::supports_enum_operation(gl::enum_operation_v<T>, gl::enum_operation_e::subtraction);
    template<typename T> concept has_bitwise_and = std::is_enum_v<T> && gl::supports_enum_operation(gl::enum_operation_v<T>, gl::enum_operation_e::bitwise_and);
    template<typename T> concept has_bitwise_or  = std::is_enum_v<T> && gl::supports_enum_operation(gl::enum_operation_v<T>, gl::enum_operation_e::bitwise_or );
    template<typename T> concept has_bitwise_xor = std::is_enum_v<T> && gl::supports_enum_operation(gl::enum_operation_v<T>, gl::enum_operation_e::bitwise_xor);
    template<typename T> concept has_bitwise_not = std::is_enum_v<T> && gl::supports_enum_operation(gl::enum_operation_v<T>, gl::enum_operation_e::bitwise_not);
    template<typename T> concept has_compare     = std::is_enum_v<T> && gl::supports_enum_operation(gl::enum_operation_v<T>, gl::enum_operation_e::compare    );

    template<gl::has_addition    T                 > constexpr auto operator+ (T  left, T right) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(left) +  std::to_underlying(right)); }
    template<gl::has_addition    T, std::integral U> constexpr auto operator+ (T  left, U right) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(left) + right); }
    template<gl::has_subtraction T                 > constexpr auto operator- (T  left, T right) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(left) -  std::to_underlying(right)); }
    template<gl::has_subtraction T, std::integral U> constexpr auto operator- (T  left, U right) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(left) - right); }
    template<gl::has_bitwise_and T                 > constexpr auto operator& (T  left, T right) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(left) &  std::to_underlying(right)); }
    template<gl::has_bitwise_or  T                 > constexpr auto operator| (T  left, T right) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(left) |  std::to_underlying(right)); }
    template<gl::has_bitwise_xor T                 > constexpr auto operator^ (T  left, T right) noexcept -> T          { return std::bit_cast<T>(std::to_underlying(left) ^  std::to_underlying(right)); }
    template<gl::has_bitwise_not T                 > constexpr auto operator~ (         T right) noexcept -> T          { return std::bit_cast<T>(                         ~  std::to_underlying(right)); }
                                                   
    template<gl::has_addition    T                 > constexpr auto operator+=(T& left, T right) noexcept -> T&         { return left = left + right; }
    template<gl::has_addition    T, std::integral U> constexpr auto operator+=(T& left, U right) noexcept -> T&         { return left = left + right; }
    template<gl::has_subtraction T                 > constexpr auto operator-=(T& left, T right) noexcept -> T&         { return left = left - right; }
    template<gl::has_subtraction T, std::integral U> constexpr auto operator-=(T& left, U right) noexcept -> T&         { return left = left - right; }
    template<gl::has_bitwise_and T                 > constexpr auto operator&=(T& left, T right) noexcept -> T&         { return left = left & right; }
    template<gl::has_bitwise_or  T                 > constexpr auto operator|=(T& left, T right) noexcept -> T&         { return left = left | right; }
    template<gl::has_bitwise_xor T                 > constexpr auto operator^=(T& left, T right) noexcept -> T&         { return left = left ^ right; }
                                                   
    template<gl::has_compare     T                 > constexpr auto operator< (T  left, T right) noexcept -> gl::bool_t { return                  std::to_underlying(left) <  std::to_underlying(right);  }
    template<gl::has_compare     T                 > constexpr auto operator> (T  left, T right) noexcept -> gl::bool_t { return                  std::to_underlying(left) >  std::to_underlying(right);  }
    template<gl::has_compare     T                 > constexpr auto operator<=(T  left, T right) noexcept -> gl::bool_t { return                  std::to_underlying(left) <= std::to_underlying(right);  }
    template<gl::has_compare     T                 > constexpr auto operator>=(T  left, T right) noexcept -> gl::bool_t { return                  std::to_underlying(left) >= std::to_underlying(right);  }

    template<> struct gl::enum_operation<gl::buffer_mapping_range_access_flags_e> { static constexpr auto value = gl::enum_operation_e::bitwise   ; };
    template<> struct gl::enum_operation<gl::buffer_mask_e                      > { static constexpr auto value = gl::enum_operation_e::bitwise   ; };
    template<> struct gl::enum_operation<gl::buffer_storage_flags_e             > { static constexpr auto value = gl::enum_operation_e::bitwise   ; };
    template<> struct gl::enum_operation<gl::context_flags_e                    > { static constexpr auto value = gl::enum_operation_e::bitwise   ; };
    template<> struct gl::enum_operation<gl::context_profile_e                  > { static constexpr auto value = gl::enum_operation_e::bitwise   ; };
    template<> struct gl::enum_operation<gl::feature_e                          > { static constexpr auto value = gl::enum_operation_e::arithmetic; };
    template<> struct gl::enum_operation<gl::frame_buffer_attachment_e          > { static constexpr auto value = gl::enum_operation_e::arithmetic; };
    template<> struct gl::enum_operation<gl::frame_buffer_source_e              > { static constexpr auto value = gl::enum_operation_e::arithmetic; };
    template<> struct gl::enum_operation<gl::memory_barrier_e                   > { static constexpr auto value = gl::enum_operation_e::bitwise   ; };
    template<> struct gl::enum_operation<gl::memory_regional_barrier_e          > { static constexpr auto value = gl::enum_operation_e::bitwise   ; };
    template<> struct gl::enum_operation<gl::program_stage_e                    > { static constexpr auto value = gl::enum_operation_e::bitwise   ; };
    template<> struct gl::enum_operation<gl::synchronization_command_e          > { static constexpr auto value = gl::enum_operation_e::bitwise   ; };
}
