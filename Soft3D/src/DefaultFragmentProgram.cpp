#include "../inc/DefaultFragmentProgram.hpp"
#include <math.h>

using namespace Soft3D;
void DefaultFragmentProgram::Execute()
{
    vec4 color = GetVector(FATTR_COLOR);

    color.x *= sin(color.y) * cos(color.x);

    SetVector(FATTR_COLOR,color);
}
