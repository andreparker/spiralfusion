#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include "Setup.hpp"
#include "utility.hpp"
#include "Buffer.hpp"



namespace Soft3D
{
	
	// vertex buffer flags
	enum{
		VBFLAG_4C_NORMAL = BIT_INT_VALUE( 0 ),
		VBFLAG_4C_COLOR  = BIT_INT_VALUE( 1 ),
		VBFLAG_4C_UV1    = BIT_INT_VALUE( 2 ),
		VBFLAG_4C_UV2    = BIT_INT_VALUE( 3 ),
		VBFLAG_4C_UV3    = BIT_INT_VALUE( 4 ),
		VBFLAG_4C_UV4    = BIT_INT_VALUE( 5 ),
	};

	class VertexBuffer :
		public Buffer< Real >
	{
		private:
			VertexBuffer& operator=( const VertexBuffer& buffer );

			boost::uint32_t _vertexFormatSize( const bit32& flags );

			void _setValid( bool valid ){ m_isValid = valid; }
		public:
			explicit VertexBuffer( const VertexBuffer& buffer );
			explicit VertexBuffer( const bit32& flags, boost::uint32_t size );
			virtual ~VertexBuffer();

			void SetAttributes( const bit32& flags ){ m_flags = flags; }
			const bit32& GetAttributes()const{ return m_flags; }

			bool isValid()const{ return m_isValid; }
		protected:
			bit32 m_flags;
			bool m_isValid;
	};
}

#endif