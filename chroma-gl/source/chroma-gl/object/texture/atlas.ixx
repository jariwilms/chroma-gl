export module opengl.object.texture_atlas;

import std;
import opengl;
import opengl.object.texture;

export namespace gl
{
    //void my_packing_algorithm(const gl::vector_2u atlas_area, const std::vector<gl::area_t>& texture_areas)
    //{
    //    
    //}

    class texture_atlas
    {
    public:
        texture_atlas() = default;
        
        void emplace(gl::texture_2d::format_e format, const gl::vector_2u& dimensions, gl::texture_data_descriptor texture_data_descriptor, std::span<const gl::byte_t> source)
        {
            auto& texture = textures_.emplace_back(format, dimensions, gl::true_);
            texture.upload(texture_data_descriptor, source);
        }

    private:

        std::vector<gl::texture_2d> textures_;
    };
}
