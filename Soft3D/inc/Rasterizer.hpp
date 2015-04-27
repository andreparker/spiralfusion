#ifndef RASTERIZER_HPP
#define RASTERIZER_HPP


#include "IVertexProcessor.hpp"

namespace Soft3D
{
    template< class FrameBufferType, class DepthBufferType  >
	struct SurfaceInfo;

	class FragmentProgram;

    class Rasterizer : public IVertexProcessor
    {
        public:
            Rasterizer(FragmentProgram* fragProg, SurfaceInfo< boost::uint32_t, boost::uint32_t >& surface);

            void SetShader(FragmentProgram* fragProg)
            {
                m_fragProg = fragProg;
            }
        private:
            virtual void ProcessImpl(VertexBuffer* v0, VertexBuffer* v1);

            FragmentProgram* m_fragProg;
    };
}
#endif
