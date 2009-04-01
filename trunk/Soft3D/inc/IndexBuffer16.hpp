#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include "Buffer.hpp"
#include <boost/cstdint.hpp>

namespace Soft3D
{
	class IndexBuffer16 :
		public Buffer< boost::uint16_t >
	{
		public:
			explicit IndexBuffer16( boost::uint32_t elementCount );
			explicit IndexBuffer16( const IndexBuffer16& indexBuffer );
			virtual ~IndexBuffer16();
	};
}

#endif