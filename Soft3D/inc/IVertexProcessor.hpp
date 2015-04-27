#ifndef IVERTEX_PROCESSOR_HPP
#define IVERTEX_PROCESSOR_HPP

namespace Soft3D
{
    class VertexBuffer;

    class IVertexProcessor
    {
    public:
        void Process(VertexBuffer* vBuffer0, VertexBuffer* vBuffer1)
        {
            // do some checks if any
            // ...

            ProcessImpl(vBuffer0, vBuffer1);
        }
    private:
        virtual void ProcessImpl(VertexBuffer* vBuffer0, VertexBuffer* vBuffer1) = 0;
    };
}
#endif // IVERTEX_PROCESSOR_HPP
