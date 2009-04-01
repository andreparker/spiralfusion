#include "../inc/VertexBuffer.hpp"
#include "../inc/utility.hpp"

namespace Soft3D
{
			
	VertexBuffer::VertexBuffer( const bit32& flags, boost::uint32_t size ):
		Buffer( new Real[ _vertexFormatSize( flags ) * size ] , _vertexFormatSize( flags ) * size, 1 ),
			m_flags( flags )
	{
		// set to false so our base knows to delete the data
		_setRef( false );
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	VertexBuffer::VertexBuffer( const VertexBuffer& buffer )
	{
		Real* dataPtr;

		// set valid buffer to false
		_setValid( false );

		// lock and get a pointer to the data
		if( buffer.lockBuffer( dataPtr ) )
		{
			const boost::uint32_t  elementCount = buffer.getSize();
			Real* dstPtr = new Real[ elementCount ];

			// set the new pointer to data
			_setBufferPtr( dstPtr );

			// duff's device
			// http://en.wikipedia.org/wiki/Duff's_device
			duff_copy8( dataPtr, dstPtr, elementCount );
		
			// set the new attributes
			_setWidth( buffer.getWidth() );
			_setHeight( buffer.getHeight() );

			// set to false so our parent knows to delete the data
			_setRef( false );

			// unlock the data
			buffer.unlockBuffer();

			// mark this buffer as valid
			_setValid( true );

			// copy the buffers format
			SetAttributes( buffer.GetAttributes() );
		}
	}

	VertexBuffer& VertexBuffer::operator=( const VertexBuffer& buffer ){ return *this; }


	boost::uint32_t VertexBuffer::_vertexFormatSize( const bit32& flags )
	{
		return 4 * static_cast< boost::uint32_t >( flags.count() );
	}
}