export module opengl:structures;

import std;
import :flags;
import :types;

export namespace gl
{
    struct texture_data_descriptor
    {
        gl::texture_base_format_e base_format = gl::texture_base_format_e::rgba;
        gl::pixel_data_type_e     data_type   = gl::pixel_data_type_e    ::byte;
    };
    struct compressed_texture_data_descriptor
    {
        gl::texture_compressed_base_format_e base_format = gl::texture_compressed_base_format_e::rgba;
        gl::pixel_data_type_e                data_type   = gl::pixel_data_type_e               ::byte;
    };
    struct buffer_data_descriptor
    {
        gl::buffer_base_format_e base_format = gl::buffer_base_format_e::rgba;
        gl::pixel_data_type_e    data_type   = gl::pixel_data_type_e   ::byte;
    };



    struct message_log
    {
        gl::uint32_t         id       = {};
        gl::debug_source_e   source   = {};
        gl::debug_type_e     type     = {};
        gl::debug_severity_e severity = {};
        std::string          message  = {};
    };
    struct binary_info
    {
        gl::enum_t              format = {};
        std::vector<gl::byte_t> binary = {}; 
    };
    struct uniform_info
    {
        std::string        name;
        gl::uniform_type_e type;
        gl::size_t         offset;
        gl::index_t        location;
        gl::index_t        block_index;
        gl::size_t         array_size;
        gl::size_t         array_stride;
        gl::size_t         matrix_stride;
        gl::bool_t         is_row_major;
    };
    struct uniform_block_info
    {
        std::string   name;
        gl::binding_t binding_point;
        gl::size_t    size;
        gl::count_t   active_uniforms;
    };
    struct draw_elements_indirect_command
    {
        gl::count_t count          = {};
        gl::count_t instance_count = {};
        gl::index_t first          = {};
        gl::index_t base_vertex    = {};
        gl::index_t base_instance  = {};
    };
    struct draw_arrays_indirect_command
    {
        gl::count_t count          = {};
        gl::count_t instance_count = {};
        gl::index_t first          = {};
        gl::index_t base_instance  = {};
    };
    struct dispatch_indirect_command
    {
        gl::vector_3u groups = {};
    };
}
