#ifndef DEPTHBUFFER32_HPP
#define DEPTHBUFFER32_HPP

#include "Setup.hpp"
#include "Buffer.hpp"

namespace Soft3D
{
	class DepthBuffer32:
		public Buffer< boost::uint32_t >
	{
		private:

			DepthBuffer32(){}
		public:
			virtual ~DepthBuffer32();
			DepthBuffer32( boost::uint32_t* refPtr, boost::uint32_t width, boost::uint32_t height ):
			  Buffer< boost::uint32_t >( refPtr, width, height )
			{}

			  void Clear( boost::uint32_t value );
			
	};
}

#endif