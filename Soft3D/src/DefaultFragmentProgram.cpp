#include "../inc/DefaultFragmentProgram.hpp"
#include <math.h>

using namespace Soft3D;
void DefaultFragmentProgram::Execute()
{

    vec4 color = GetVector(FATTR_COLOR);
    vec4 reg = GetVector(FATTR_REG0);

    color.x = reg.x * color.x;
    color.y = reg.w * color.y;
    color.z = reg.z * color.z;
    color = clamp(color,255.0f);

    SetVector(FATTR_COLOR,color);

}
