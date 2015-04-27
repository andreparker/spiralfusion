#include "../inc/VertexTransform.hpp"
#include "../inc/VertexBuffer.hpp"
#include "../inc/VertexProgram.hpp"

using namespace Soft3D;
using namespace MathUtil;

VertexTransform::VertexTransform(VertexProgram* program, const MathUtil::Matrix4x4<Real>& model,
                                const MathUtil::Matrix4x4<Real>& view,
                                const MathUtil::Matrix4x4<Real>& projection) : m_vertexProgram(program),
                                m_model(model), m_view(view), m_projection(projection)
{

}


void VertexTransform::Update(const MathUtil::Matrix4x4<Real>& model,
                             const MathUtil::Matrix4x4<Real>& view,
                             const MathUtil::Matrix4x4<Real>& projection)
{
    m_model = model;
    m_view = view;
    m_projection = projection;
}

void VertexTransform::SetShader(VertexProgram* vertexProgram)
{
    m_vertexProgram = vertexProgram;
}

void VertexTransform::ProcessImpl(VertexBuffer* v0, VertexBuffer* v1)
{
    Vector4<Real> *v0Ptr, *v1Ptr;
    Real *ptr0, *ptr1;
    boost::uint32_t size = v0->getSize() / v0->GetElementCount();

    if(m_vertexProgram != nullptr)
    {
        m_vertexProgram->SetVertexInput(*v0);
        m_vertexProgram->SetVertexCount(size);
        m_vertexProgram->Exec();
    }
    else
    {
        if(v0->lockBuffer(ptr0) && v1->lockBuffer(ptr1))
        {

            v0Ptr = reinterpret_cast<Vector4<Real>*>(ptr0);
            v1Ptr = reinterpret_cast<Vector4<Real>*>(ptr1);

            Matrix4x4<Real> mvp = m_model * m_view * m_projection;
            boost::uint32_t inc0 = v0->GetElementCount() / 4;
            boost::uint32_t inc1 = v1->GetElementCount() / 4;


            for(boost::uint32_t i = 0; i < size; ++i)
            {
                *v1Ptr = *v0Ptr * mvp;

                v0Ptr += inc0;
                v1Ptr += inc1;
            }

            v0->unlockBuffer();
            v1->unlockBuffer();
        }
    }
}
