export module chroma_gl:io;

import std;
import opengl;

export namespace gl::io
{
    auto read (const std::filesystem::path& path) -> std::vector<gl::byte_t>
    {
        auto const size   = std::filesystem::file_size(path);
        auto       buffer = std::vector<gl::byte_t>(size);
        auto       file   = std::ifstream(path, std::ios::binary);
        if (!file) throw std::runtime_error{ "failed to open file" };

        file.read(reinterpret_cast<gl::char_t*>(buffer.data()), size);
        return buffer;
    }
    void write(const std::filesystem::path& path, std::span<const gl::byte_t> memory)
    {
        auto file = std::ofstream(path, std::ios::binary | std::ios::trunc);
        if (!file) throw std::runtime_error{ "failed to open file" };

        file.write(reinterpret_cast<const gl::char_t*>(memory.data()), memory.size_bytes());
    }
}
