#ifndef GEOMETRYUTILS_INL
#define GEOMETRYUTILS_INL

#include <algorithm>
#include "RasterCommon.hpp"

namespace Soft3D
{
	// vertextype must have a y member
	template< class VertexType >
	void VertexSort( const VertexType& v0,
					 const VertexType& v1,
					 const VertexType& v2,
					 TriangleVertices< VertexType >& list )
	{
		VertexType tmp0 = v0,
					tmp1 = v1,
					tmp2 = v2;

		// sort vertices based on least to greatest y's
		if( tmp0.y > tmp1.y )
			std::swap( tmp0, tmp1 );
		if( tmp0.y > tmp2.y )
			std::swap( tmp0, tmp2 );
		if( tmp1.y > tmp2.y )
			std::swap( tmp1, tmp2 );

		list.v0 = tmp0;
		list.v1 = tmp1;
		list.v2 = tmp2;

	}
}

#endif