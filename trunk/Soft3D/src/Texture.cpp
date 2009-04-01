#include "../inc/Texture.hpp"
#include <memory.h>

namespace Soft3D
{
	Texture::Texture( boost::uint32_t width, boost::uint32_t height, boost::uint32_t bpp )
		: Buffer( new boost::uint8_t[ width * height * (bpp>>3)], width, height ), m_bpp( bpp )
	{
		_setRef( false );
	}

	Texture::Texture( boost::uint8_t* dataPtr, boost::uint32_t width, boost::uint32_t height, boost::uint32_t bpp )
		: Buffer( dataPtr , width, height ), m_bpp( bpp )
	{
	}

	Texture::Texture( const Texture& srcTexture )
	{
		boost::uint8_t* bufferPtr = NULL;
		if( srcTexture.lockBuffer( bufferPtr ) )
		{
			const boost::uint32_t sizeBytes = srcTexture.getWidth() * srcTexture.getHeight() * srcTexture.getBytes();
			boost::uint8_t* dataPtr = new boost::uint8_t[ sizeBytes ];

			//set the new data pointer
			_setBufferPtr( dataPtr );

			// duplicate the textures data
			memcpy( dataPtr, bufferPtr, static_cast< size_t >( sizeBytes ) );

			_setWidth( srcTexture.getWidth() );
			_setHeight( srcTexture.getHeight() );
			_setBpp( srcTexture.getBpp() );

			srcTexture.unlockBuffer();
		}
	}

	Texture::~Texture()
	{
	}

}