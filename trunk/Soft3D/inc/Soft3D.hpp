#ifndef SOFT3D_HPP
#define SOFT3D_HPP

#include "Setup.hpp"
#include "SingletonHandle.hpp"
#include "utility.hpp"

#include "VertexBuffer.hpp"
#include "IndexBuffer16.hpp"
#include "DepthBuffer32.hpp"
#include "VertexProgram.hpp"
#include "FragmentProgram.hpp"

#include "Matrix.inl"

#include "Texture.hpp"

namespace Soft3D
{

	// flags
	enum
	{
		// screen buffer type
		S3D_BackBuffer32 = BIT_INT_VALUE( 0 ),
		S3D_BackBuffer16 = BIT_INT_VALUE( 1 ),

		// depth buffer type
		S3D_DepthBuffer32 = BIT_INT_VALUE( 2 ),
		S3D_DepthBuffer16 = BIT_INT_VALUE( 3 ),

		// stencil buffer
		S3D_StencilBuffer8 = BIT_INT_VALUE( 4 ),
	};

	// render states
	typedef enum
	{
		S3D_RS_NONE = 0,
		S3D_RS_MAX,
	}eRenderState_t;

	// matrix types
	typedef enum
	{
		S3D_MM_MODEL,
		S3D_MM_VIEW,
		S3D_MM_PROJECTION,
		S3D_MM_TEXTURE,
	}eMatrixMode_t;

	typedef enum
	{
		S3D_PT_TRIANGLE = 1,
	}ePrimitive_t;

	class Soft3DManager
	{
		private:

			// instancing is not allowed
			Soft3DManager& operator=(const Soft3DManager&);
			Soft3DManager(const Soft3DManager&);
			Soft3DManager();

			// default flags for Initialization
			static const bit32 _Default_Render_Flags;
			static const boost::uint32_t maxMatrices = 4;
		public:
			typedef MathUtil::Matrix4x4< Real > mat4;

			~Soft3DManager();

			static Soft3DManager& singleton()
			{
				// a static instance
				static Soft3DManager instance;

				return instance;
			}

			struct bufferInfo
			{
				boost::uint32_t scrWidth, scrHeight;
				boost::uint8_t* scrBufferPtr;
			};

		public:

			bool Init( boost::uint32_t vertexPoolSize,
				const bufferInfo& info, const bit32& flags = _Default_Render_Flags );
			void Shutdown();
		
			// render state operations
			void SetRenderState( eRenderState_t renderState, boost::int32_t value );

			void GetRenderState( eRenderState_t renderState, boost::int32_t& value );

			void SetVertexSource( VertexBuffer& vertexBuffer ) { m_vertexSourcePtr = &vertexBuffer; } // this will be the source buffer to copy from
			void SetIndexSource( IndexBuffer16* indexBufferPtr ) { m_indexBufferPtr = indexBufferPtr; }

			// set to change how vertices get processed
			void SetVertexProgram( VertexProgram* vertexProgPtr );

			// set to change how fragment processing
			void SetFragmentProgram( FragmentProgram* fragmentProgPtr );

			// matrix operations
			void SetMatrix( eMatrixMode_t matrixMode, const MathUtil::Matrix4x4< Real >& matrix );

			void MulMatrix( eMatrixMode_t matrixMode, const MathUtil::Matrix4x4< Real >& matrix );

			void GetMatrix( eMatrixMode_t matrixMode, MathUtil::Matrix4x4< Real >& matrix );

			void DrawPrimitive( ePrimitive_t primitive, boost::uint32_t elementCount );

		private:

			// render states
			boost::int32_t m_renderStates[ S3D_RS_MAX ];

			// copy vertex data from source to main vertex pool
			void _CopyVertexData();
			// main vertex pool
			VertexBuffer* m_vertexStreamPtr;

			// index buffer pointer
			IndexBuffer16* m_indexBufferPtr;

			// vertex source
			VertexBuffer* m_vertexSourcePtr;

			// vertex program to process verts
			VertexProgram* m_vertexProgramPtr;

			// fragment program .......
			FragmentProgram* m_fragmentProgramPtr;

			// matrices
			mat4 m_Matrices[ maxMatrices ];
	};

	typedef SingletonHandle< Soft3DManager, Soft3DManager::singleton > Soft3DMgrHdl;
}

#endif