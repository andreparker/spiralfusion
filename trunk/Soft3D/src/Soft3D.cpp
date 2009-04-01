#include <boost/foreach.hpp>
#include "../inc/Soft3D.hpp"
#include "../inc/DefaultVertexProgram.hpp"
#include "../inc/DefaultFragmentProgram.hpp"


namespace Soft3D
{
	DefaultVertexProgram _DefaultVertexProgram;
	DefaultFragmentProgram _DefaultFramentProgram;

	const bit32 Soft3DManager::_Default_Render_Flags = S3D_BackBuffer32 | S3D_DepthBuffer32;

	const boost::uint32_t _default_vb_flags = VBFLAG_4C_NORMAL | VBFLAG_4C_COLOR | VBFLAG_4C_UV1 |
												VBFLAG_4C_UV2 | VBFLAG_4C_UV3 | VBFLAG_4C_UV4;

	Soft3DManager::Soft3DManager():
		m_vertexStreamPtr( NULL ), m_indexBufferPtr( NULL ),
			m_vertexSourcePtr( NULL ),m_vertexProgramPtr( &_DefaultVertexProgram )
	{
		BOOST_FOREACH( mat4& matrix, m_Matrices )
		{
			// set matrices to identity
			matrix.LoadIdentity();
		}
	}

	Soft3DManager& Soft3DManager::operator=(const Soft3DManager& m)
	{
		return *this;
	}

	Soft3DManager::Soft3DManager(const Soft3DManager& m)
	{
	}

	Soft3DManager::~Soft3DManager()
	{
		Shutdown();
	}

	//==========================================================


	bool Soft3DManager::Init( boost::uint32_t vertexPoolSize,
						const bufferInfo& info, const bit32& flags /*= bit32(0)*/ )
	{
		m_vertexStreamPtr = new VertexBuffer( _default_vb_flags, vertexPoolSize );
		return true;
	}

	void Soft3DManager::Shutdown()
	{
		if( m_vertexStreamPtr )
			delete m_vertexStreamPtr;
	}

	void Soft3DManager::SetRenderState( eRenderState_t renderState, boost::int32_t value )
	{
		m_renderStates[ renderState ] = value;
	}

	void Soft3DManager::GetRenderState( eRenderState_t renderState, boost::int32_t& value )
	{
		value = m_renderStates[ renderState ];
	}

	// copy data to our main vertex buffer
	void Soft3DManager::_CopyVertexData()
	{
		BOOST_ASSERT( m_vertexStreamPtr != NULL );
		BOOST_ASSERT( m_vertexStreamPtr->getSize() > m_vertexSourcePtr->getSize() );

		Real* vertexStreamPtr = NULL;
		Real* vertexSourcePtr = NULL;

		bool isLockedSource = m_vertexSourcePtr->lockBuffer( vertexSourcePtr );
		bool isLockedStream = m_vertexStreamPtr->lockBuffer( vertexStreamPtr );

		if( isLockedSource && isLockedStream )
		{
			const boost::uint32_t sizeBytes = m_vertexSourcePtr->getSizeBytes();
			memcpy( vertexStreamPtr, vertexSourcePtr, sizeBytes );


			// unlock
			m_vertexSourcePtr->unlockBuffer();
			m_vertexStreamPtr->unlockBuffer();

			// copy the attributes of the source to the stream so we know what attributes to traverse
			m_vertexStreamPtr->SetAttributes( m_vertexSourcePtr->GetAttributes() );
		}
	}

	void Soft3DManager::SetVertexProgram( VertexProgram* vertexProgPtr )
	{
		if( vertexProgPtr == NULL )
		{
			m_vertexProgramPtr = &_DefaultVertexProgram;
		}else
		{
			m_vertexProgramPtr = vertexProgPtr;
		}
	}

	void Soft3DManager::SetFragmentProgram( FragmentProgram* fragmentProgPtr )
	{
		if( fragmentProgPtr == NULL )
		{
			m_fragmentProgramPtr = &_DefaultFramentProgram;
		}else
		{
			m_fragmentProgramPtr = fragmentProgPtr;
		}
	}

	void Soft3DManager::SetMatrix( eMatrixMode_t matrixMode, const MathUtil::Matrix4x4< Real >& matrix )
	{
		m_Matrices[ matrixMode ] = matrix;
	}

	void Soft3DManager::MulMatrix( eMatrixMode_t matrixMode, const MathUtil::Matrix4x4< Real >& matrix )
	{
		m_Matrices[ matrixMode ] = matrix * m_Matrices[ matrixMode ];
	}

	void Soft3DManager::GetMatrix( eMatrixMode_t matrixMode, MathUtil::Matrix4x4< Real >& matrix )
	{
		matrix = m_Matrices[ matrixMode ];
	}

	void Soft3DManager::DrawPrimitive( ePrimitive_t primitive, boost::uint32_t elementCount )
	{
	}

}