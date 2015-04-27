#ifndef VERTEXCLIPPER_HPP
#define VERTEXCLIPPER_HPP

#include "IVertexProcessor.hpp"
#include "Matrix.inl"

namespace Soft3D
{
    class VertexBuffer;
    class VertexClipper : public IVertexProcessor
    {
        public:
            VertexClipper(const MathUtil::Matrix4x4<Real>& projection);


        private:
            virtual void ProcessImpl(VertexBuffer* v0, VertexBuffer* v1);
    };
}
#endif
