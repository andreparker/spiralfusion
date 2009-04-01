#ifndef INTERPOLATION_INL
#define INTERPOLATION_INL

namespace MathUtil
{
	template< class T >
	inline T lerp( T dst ,T src , T percent )
	{
		// final = s1 + t( s2 - s1 );
		return src + percent * ( dst - src );
	}

}

#endif