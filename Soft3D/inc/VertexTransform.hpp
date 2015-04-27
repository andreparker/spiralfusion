#ifndef VERTEXTRANSFORM_HPP
#define VERTEXTRANSFORM_HPP

#include "Setup.hpp"
#include "IVertexProcessor.hpp"
#include "Matrix.inl"

namespace Soft3D
{
    class VertexProgram;
    class VertexTransform : public IVertexProcessor
    {
        public:
            VertexTransform(VertexProgram* program, const MathUtil::Matrix4x4< Real >& model,
                            const MathUtil::Matrix4x4< Real >& view,
                            const MathUtil::Matrix4x4< Real >& projection);


             void Update(const MathUtil::Matrix4x4< Real >& model, const MathUtil::Matrix4x4< Real >& view, const MathUtil::Matrix4x4< Real >& projection);

             void SetShader(VertexProgram* vertexProgram);
        private:
            virtual void ProcessImpl(VertexBuffer* v0, VertexBuffer* v1);
            VertexProgram* m_vertexProgram;

            MathUtil::Matrix4x4<Real> m_model, m_view, m_projection;
    };
}
#endif
