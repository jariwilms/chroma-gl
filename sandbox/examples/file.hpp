#pragma once

import std;
import chroma_gl;

static auto read_file(std::filesystem::path const& filepath) -> std::vector<gl::byte_t>
{
    auto file   = std::ifstream{ filepath, std::ios::binary | std::ios::ate };
    if (!file) throw std::runtime_error{ "failed to open file" };

    auto buffer = std::vector<gl::byte_t>(static_cast<gl::size_t>(file.tellg()));
    file.seekg(0u);
    file.read(reinterpret_cast<gl::char_t*>(buffer.data()), buffer.size());
    
    return buffer;
}
static void write_file(std::filesystem::path const& filename, std::vector<gl::byte_t> const& memory) 
{
    auto file = std::ofstream{ filename, std::ios::binary };
    if (!file.is_open()) throw std::runtime_error{ "failed to open file" };

    file.write(reinterpret_cast<gl::char_t const*>(memory.data()), memory.size());
}
