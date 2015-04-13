#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Buffer.hpp"

namespace Soft3D
{
	// Supports 32,16,8 bit depths

	class Texture :
		public Buffer< boost::uint8_t >
	{
		private:
			Texture();
		public:
			virtual ~Texture();
			Texture( boost::uint32_t width, boost::uint32_t height, boost::uint32_t bpp );
			Texture( boost::uint8_t* dataPtr, boost::uint32_t width, boost::uint32_t height, boost::uint32_t bpp );
			Texture( const Texture& srcTexture );

			boost::uint32_t getBpp()const{ return m_bpp; }
			boost::uint32_t getBytes()const{ return (m_bpp >> 3 ); }
		private:

			void _setBpp( boost::uint32_t bpp ) { m_bpp = bpp; }

			boost::uint32_t m_bpp; // bits per pix
	};
}

#endif
