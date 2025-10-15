export module opengl.structures;

import std;
import opengl.flags;
import opengl.types;

export namespace gl
{
    template<typename... Ts>
    struct overload_t : Ts... { using Ts::operator()...; };

    struct message_log
    {
        gl::uint32_t         id       = {};
        gl::string           message  = {};
        gl::debug_source_e   source   = {};
        gl::debug_type_e     type     = {};
        gl::debug_severity_e severity = {};
    };
    struct binary_info
    {
        gl::enum_t              format = {};
        gl::vector<gl::uint8_t> binary = {}; 
    };
    struct draw_elements_indirect_command
    {
        gl::count_t count          = {};
        gl::count_t instance_count = {};
        gl::index_t first_index    = {};
        gl::index_t base_vertex    = {};
        gl::index_t base_instance  = {};
    };
    struct draw_arrays_indirect_command
    {
        gl::count_t count          = {};
        gl::count_t instance_count = {};
        gl::index_t first_index    = {};
        gl::index_t base_instance  = {};
    };
    struct dispatch_indirect_command
    {
        gl::count_t groups_x;
        gl::count_t groups_y;
        gl::count_t groups_z;
    };
}
