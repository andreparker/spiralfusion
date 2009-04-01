#ifndef DEFAULTVERTEXPROGRAM_HPP
#define DEFAULTVERTEXPROGRAM_HPP


#include "Setup.hpp"
#include "VertexProgram.hpp"

namespace Soft3D
{
	class DefaultVertexProgram :
		public VertexProgram
	{
		public:
			DefaultVertexProgram();
			DefaultVertexProgram( VertexBuffer& vertexInput, boost::uint32_t vertexCount );
			~DefaultVertexProgram();

			virtual void Begin();
			virtual void End();
	};
}

#endif