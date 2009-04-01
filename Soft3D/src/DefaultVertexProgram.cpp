#include "..\inc\DefaultVertexProgram.hpp"


namespace Soft3D
{
	DefaultVertexProgram::DefaultVertexProgram( VertexBuffer& vertexInput, boost::uint32_t vertexCount ):
		VertexProgram( vertexInput, vertexCount ){}
			
	DefaultVertexProgram::~DefaultVertexProgram()
	{}

	DefaultVertexProgram::DefaultVertexProgram()
	{
	}

	void DefaultVertexProgram::Begin()
	{
	}

	void DefaultVertexProgram::End()
	{
	}
}