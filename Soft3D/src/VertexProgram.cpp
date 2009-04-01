#include "../inc/VertexProgram.hpp"

namespace Soft3D
{
	VertexProgram::VertexProgram(){}
	VertexProgram::VertexProgram(const VertexProgram &prog)
	{
	}

	VertexProgram::VertexProgram( VertexBuffer &vertexInput, boost::uint32_t vertexCount):
		m_vertexStreamPtr( &vertexInput ), m_vertexCount( vertexCount ),m_dataPtr( NULL )
	{
	}

	void VertexProgram::BeginVectorAttr() // used to begin extraction
	{
		m_vertexStreamPtr->lockBuffer( m_dataPtr );
	}

	void VertexProgram::EndVectorAttr() // ends extraction
	{
		m_vertexStreamPtr->unlockBuffer();
	}

	void VertexProgram::LoadNextAttrSet() // called between begin/end to load next vertice info
	{
		// m_dataPtr is a locked pointer to the vertex data

		// this is a default way of getting vertex attributes
		// this can be optimized by writting a custom loader
		// by over loading this function in a derived class
		const bit32 flags = m_vertexStreamPtr->GetAttributes();

		// first attribute is always the vertex it self
		SetVectorAttr( VATTR_VERTEX, *( reinterpret_cast< Vec4* >( m_dataPtr ) ) );
		m_dataPtr += 4;

		// the current attribute bit we are on
		// see VertexBuffer.hpp, the bit flags
		boost::uint32_t bitNumber = 0;

		do
		{
			// the bit matches up with the attribute enum order
			// so we can use the bitNumber to index into the proper
			// attribute register array to set
			if( flags.test( bitNumber ) )
			{
				SetVectorAttr( bitNumber, *( reinterpret_cast< Vec4* >( m_dataPtr ) ) );
				m_dataPtr += 4;	// all attributes are multiples of 4 * (4 bytes) or vector4's
			}

		}while( ++bitNumber < VATTR_MAX_ATTR );
	}

	void VertexProgram::Exec()
	{
		// this is a standard example of a vertex program

		// we get the count of vertices/elements to iterate through
		boost::uint32_t vertexCount = GetVertexCount();

		// we grab the model * view * projection transform
		Mat4 modelViewProj = GetMatrixRegister( MREG_MVP_MATRIX );

		// used for transforming and storing a vertice
		Vec4 vertex;

		// must call begin/end to iterate through the vertex elements
		BeginVectorAttr();
		do
		{
			// get some vertex data
			LoadNextAttrSet();

			// grab vertex and transform it
			vertex = GetVectorAttr( VATTR_VERTEX );
			vertex = vertex * modelViewProj;

		}while( --vertexCount != 0 );
		EndVectorAttr();
	}
}