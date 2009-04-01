#include "../inc/DepthBuffer32.hpp"
#include "../inc/utility.hpp"


namespace Soft3D
{
	DepthBuffer32::~DepthBuffer32()
	{
	}

	void DepthBuffer32::Clear( boost::uint32_t value )
	{
		boost::uint32_t* bufferPtr = NULL;

		if( lockBuffer( bufferPtr ) )
		{
			// Loop unrolling via Duff's device
			// http://en.wikipedia.org/wiki/Duff's_device
			duff_copy8( value, bufferPtr, getSize() );
			
			unlockBuffer();
		}
	}
}