#pragma once

import std;
import chroma_gl;

static auto load_file(std::filesystem::path const& filepath) -> std::vector<gl::byte_t>
{
    auto file = std::ifstream{ filepath, std::ios::binary | std::ios::ate };
    if (!file) throw std::runtime_error{ "failed to open file: " + filepath.string() };

    auto const size = file.tellg();
    auto       buffer = std::vector<gl::byte_t>(static_cast<gl::size_t>(size));

    file.seekg(0u, std::ios::beg);
    file.read(std::bit_cast<gl::char_t*>(buffer.data()), size);

    return buffer;
}
auto load_file_to_string(std::filesystem::path const& filepath) -> std::string
{
    auto file   = std::ifstream{ filepath };
    auto buffer = std::ostringstream{};
    if (!file) throw std::runtime_error("failed to open file: " + filepath.string());

    buffer << file.rdbuf();
    return buffer.str();
}