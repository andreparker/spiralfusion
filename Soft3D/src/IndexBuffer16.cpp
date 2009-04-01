#include "../inc/IndexBuffer16.hpp"


namespace Soft3D
{
	IndexBuffer16::IndexBuffer16( boost::uint32_t elementCount ):
		Buffer( elementCount, 1 ) 
	{
	}

	IndexBuffer16::IndexBuffer16( const IndexBuffer16& indexBuffer )
	{
		const boost::uint32_t sizeBytes = indexBuffer.getSizeBytes();
		boost::uint16_t* dataPtr = new boost::uint16_t[ indexBuffer.getSize() ];

		boost::uint16_t* sourcePtr = NULL;
		if( dataPtr && indexBuffer.lockBuffer( sourcePtr ) )
		{
			

			memcpy( dataPtr, sourcePtr, sizeBytes );

			indexBuffer.unlockBuffer();

			_setBufferPtr( dataPtr );
			_setWidth( indexBuffer.getSize() );
			_setHeight( 1 );
		}
	}

	IndexBuffer16::~IndexBuffer16(){}
}