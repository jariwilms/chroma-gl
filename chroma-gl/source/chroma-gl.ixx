export module chroma_gl;
export import opengl;
export import :color;
export import :io.image;
export import :io;
export import :object.buffer;
export import :object.cubemap;
export import :object.frame_buffer;
export import :object.pipeline;
export import :object.query;
export import :object.render_buffer;
export import :object.sampler;
export import :object.shader.uniform_cache;
export import :object.shader;
export import :object.texture;
export import :object.vertex_array;
export import :object;
export import :projection;
export import :vertex;

import std;

export namespace gl
{
    auto create_texture_from_file  (std::filesystem::path const& path) -> gl::texture_2d
    {
        auto       image_data            = gl::io::read(path);
        auto       image                 = gl::image::decode(gl::image::format_e::rgba_uint8, image_data);
        auto       texture               = gl::texture_2d{ gl::texture_2d::format_e::rgba_uint8_n, image.dimensions() };
        auto const pixel_data_descriptor = gl::pixel_data_descriptor{ gl::texture_base_format_e::rgba, gl::pixel_data_type_e::byte };
        texture.upload          (pixel_data_descriptor, image.data());
        texture.generate_mipmaps();

        return texture;
    }
    auto create_pipeline_from_files(std::unordered_map<gl::shader::type_e, std::filesystem::path> const& file_names) -> gl::pipeline
    {
        auto shaders = std::vector<std::shared_ptr<gl::shader>>{};
        std::ranges::for_each(file_names, [&](auto const iterator)
            {
                auto const binary = gl::io::read(iterator.second);
                shaders.emplace_back(std::make_shared<gl::shader>(iterator.first, "main", binary));
            });

        return gl::pipeline{ shaders };
    }
}
