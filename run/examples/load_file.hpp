#pragma once

import std;
import chroma_gl;

static auto load_file(std::filesystem::path const& filepath) -> std::vector<gl::byte_t>
{
    auto file   = std::ifstream{ filepath, std::ios::binary | std::ios::ate };
    if (!file) throw std::runtime_error{ "failed to open file" };

    auto buffer = std::vector<gl::byte_t>(file.tellg());
    file.seekg(0u);
    file.read (reinterpret_cast<gl::char_t*>(buffer.data()), buffer.size());
    
    return buffer;
}
