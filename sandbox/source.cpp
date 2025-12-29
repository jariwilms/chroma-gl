import std;
import chroma_gl;
import rgfw;

#include "examples/compute.hpp"
#include "examples/cube.hpp"
#include "examples/frame_buffer.hpp"
#include "examples/instance_id.hpp"
#include "examples/instanced.hpp"
#include "examples/texture.hpp"
#include "examples/triangle.hpp"

auto main() -> int
{
    ::triangle();
    //::cube();
    //::texture();
    //::frame_buffer();
    //::instanced();
    //::instance_id();
    //::compute();

    return 0;
}
