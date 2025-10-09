export module vendor.glad;

import std;
import <glad/gl.h>;
import vendor.glfw.functions;

export namespace glad
{
    void initialize()
    {
        if (!::gladLoadGL(glfw::function_address)) throw std::runtime_error{ "failed to initialize GLAD" };
    }
}
