import std;
import chroma_gl;
import rgfw;

#include "examples/compute.hpp"
#include "examples/frame_buffer.hpp"
#include "examples/instance_id.hpp"
#include "examples/instanced.hpp"
#include "examples/texture.hpp"
#include "examples/triangle.hpp"

auto main() -> int
{
    ::triangle();
    //::texture();
    //::frame_buffer();
    //::instanced();
    //::instance_id();
    //::compute();

    return 0;
}
