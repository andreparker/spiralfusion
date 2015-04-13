#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <boost/cstdint.hpp>

namespace Soft3D
{
	template< class T, int bit >
	struct Bit_value
	{
		static const T value = 1 << bit;
	};

	// duff's device
	// http://en.wikipedia.org/wiki/Duff's_device
	template< class T >
	inline void duff_copy8( const T* srcPtr, T* dstPtr, boost::uint32_t count )
	{
		if( count )
		{
			boost::int32_t wholeCount = static_cast<boost::int32_t>((count + 7) >> 3); // count + 7 / 8

			switch( count & 7 ) // count % 8
			{

					do
					{
				case 0: *dstPtr++ = *srcPtr++;
				case 7: *dstPtr++ = *srcPtr++;
				case 6: *dstPtr++ = *srcPtr++;
				case 5: *dstPtr++ = *srcPtr++;
				case 4: *dstPtr++ = *srcPtr++;
				case 3: *dstPtr++ = *srcPtr++;
				case 2: *dstPtr++ = *srcPtr++;
				case 1: *dstPtr++ = *srcPtr++;
					}while( --wholeCount > 0);
			}
		}
	}

	template< class T >
	inline void duff_copy4( const T* srcPtr, T* dstPtr, boost::uint32_t count )
	{
		if( count )
		{
			boost::int32_t wholeCount = static_cast<boost::int32_t>((count + 3) >> 2); // count + 3 / 4

			switch( count & 3 ) // count % 4
			{

					do
					{
				case 0: *dstPtr++ = *srcPtr++;
				case 3: *dstPtr++ = *srcPtr++;
				case 2: *dstPtr++ = *srcPtr++;
				case 1: *dstPtr++ = *srcPtr++;
					}while( --wholeCount > 0);
			}
		}
	}

	//---------------------------------------------------------------------------------
	// copy single value

	template< class T >
	inline void duff_copy8( const T& value, T* dstPtr, boost::uint32_t count )
	{
		if( count )
		{
			boost::int32_t wholeCount = static_cast<boost::int32_t>((count + 7) >> 3); // count + 7 / 8

			switch( count & 7 ) // count % 8
			{

					do
					{
				case 0: *dstPtr++ = value;
				case 7: *dstPtr++ = value;
				case 6: *dstPtr++ = value;
				case 5: *dstPtr++ = value;
				case 4: *dstPtr++ = value;
				case 3: *dstPtr++ = value;
				case 2: *dstPtr++ = value;
				case 1: *dstPtr++ = value;
					}while( --wholeCount > 0);
			}
		}
	}

	template< class T >
	inline void duff_copy4( const T& value, T* dstPtr, boost::uint32_t count )
	{
		if( count )
		{
			boost::int32_t wholeCount = static_cast<boost::int32_t>((count + 3) >> 2); // count + 3 / 4

			switch( count & 3 ) // count % 4
			{

					do
					{
				case 0: *dstPtr++ = value;
				case 3: *dstPtr++ = value;
				case 2: *dstPtr++ = value;
				case 1: *dstPtr++ = value;
					}while( --wholeCount > 0);
			}
		}
	}
}

#define BIT_INT_VALUE( bit ) Soft3D::Bit_value< boost::uint32_t , bit >::value

#endif
