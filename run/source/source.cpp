import std;
import opengl;

auto main() -> int
{
    //enum class buffer_t        : std::underlying_type_t<gl::handle_t>;
    //enum class frame_buffer_t  : std::underlying_type_t<gl::handle_t>;
    //enum class query_t         : std::underlying_type_t<gl::handle_t>;
    //enum class render_buffer_t : std::underlying_type_t<gl::handle_t>;
    //enum class sampler_t       : std::underlying_type_t<gl::handle_t>;
    //enum class shader_t        : std::underlying_type_t<gl::handle_t>;
    //enum class texture_t       : std::underlying_type_t<gl::handle_t>;

    auto buffer = gl::create_buffer();

    return 0;
}
