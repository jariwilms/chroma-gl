export module chroma_gl;
export import chroma_gl.io;
export import opengl;
export import opengl.context;
export import opengl.io.image;
export import opengl.object.buffer;
export import opengl.object.cubemap;
export import opengl.object.frame_buffer;
export import opengl.object.pipeline;
export import opengl.object.query;
export import opengl.object.render_buffer;
export import opengl.object.sampler;
export import opengl.object.shader;
export import opengl.object.texture;
export import opengl.object.vertex_array;
export import opengl.projection;
export import opengl.vertex;

import std;

export namespace gl
{
    auto create_pipeline_from_files(const std::unordered_map<gl::shader::type_e, std::string_view>& filenames) -> gl::pipeline
    {
        auto shaders = std::vector<std::shared_ptr<gl::shader>>{};
        std::ranges::for_each(filenames, [&](auto iterator)
            {
                auto const binary = gl::io::read(iterator.second);
                shaders.emplace_back(std::make_shared<gl::shader>(iterator.first, "main", binary));
            });

        return gl::pipeline{ shaders };
    }
}
