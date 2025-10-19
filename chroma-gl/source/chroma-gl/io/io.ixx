export module opengl.io;

import std;
import opengl;

export namespace gl
{
    auto load_file(const std::filesystem::path& filepath) -> std::vector<gl::byte_t>
    {
              auto file   = std::ifstream{ filepath, std::ios::binary | std::ios::ate };
        if (!file) throw std::runtime_error("failed to open file: " + filepath.string());

        const auto size   = file.tellg();
              auto buffer = std::vector<gl::byte_t>(static_cast<gl::size_t>(size));

        file.seekg(0, std::ios::beg);
        file.read(std::bit_cast<gl::char_t*>(buffer.data()), size);

        return buffer;
    }
}
