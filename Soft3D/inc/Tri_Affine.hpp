#ifndef TRI_AFFINE_HPP
#define TRI_AFFINE_HPP

#include <boost/cstdint.hpp>
#include "Setup.hpp"
#include "Vector3.inl"
#include "PolygonEdge.inl"
#include "PolygonGradient.inl"
#include "GeometryMath.hpp"
#include "RasterCommon.hpp"
#include "Tri_Affine_InnerLoop.inl"

#include "Profiler.hpp"

namespace Soft3D
{

	//------------------------------------------------------------------------------------------------------
	// all drawing functions assume sorted vertice's by least to greatest Y
	//

	// VerticeType - must contain a x,y,w member
	// x,y - screen space
	// w - perspective w for 1/w perspective texture correction ( NOTE: optional in some rendering modes)
	template< class VertexType, class FrameBufferType,class DepthBufferType, class _Real >
	void DrawTriangleAffine( SurfaceInfo< FrameBufferType, DepthBufferType >& Info, 
							TriangleVertices< VertexType >& verticeList,
							FragmentProgram& fragmentProg )
	{
		PROFILE_FUNCTION();
		VertexType  v0 = verticeList.v0, 
					v1 = verticeList.v1,
					v2 = verticeList.v2;

		// determine which edge of the triangle is on the left and right
		//----------------------------------------------------------------------
		MathUtil::Vector2< _Real > c0( v0.x, v0.y ),c1( v1.x, v1.y ),c2( v2.x, v2.y );
		_Real handednes = TriangleGradient( c0, c1, c2 );	// triangle winding

		PolygonEdge< _Real, VertexType > leftEdge, rightEdge;
		PolygonGradient< _Real, VertexType > gradient;		// whole triangle gradients

		if( handednes <= 0 )
		{
			leftEdge.SetupInterpolants( v1, v0 );
			rightEdge.SetupInterpolants( v2, v0 );
			gradient.SetupGradients( v0, v1, v2 );
		}else
		{
			leftEdge.SetupInterpolants( v2, v0 );
			rightEdge.SetupInterpolants( v1, v0 );
			gradient.SetupGradients( v0,v2,v1 );
		}
		//------------------------------------------------------------------------

		// duplicate suface info
		SurfaceInfo< FrameBufferType, DepthBufferType > tmpInfo = Info;

		// goto first scan line
		tmpInfo.Step( static_cast< boost::uint32_t >( v0.y ) );

		// 2 part triangle render, only one if triangle top/bottom Y's match 
		RasterEdges_Affine< _Real, 
			FrameBufferType, 
			DepthBufferType, VertexType >( leftEdge, rightEdge, gradient, fragmentProg, tmpInfo );

		// make sure there is another piece to draw
		if( ( leftEdge.GetHeight() + rightEdge.GetHeight() ) )
		{
			if( handednes <= 0 )
				leftEdge.SetupInterpolants( v2, v1 );
			else
				rightEdge.SetupInterpolants( v2, v1 );

			RasterEdges_Affine< _Real, 
				FrameBufferType, 
				DepthBufferType, VertexType >( leftEdge, rightEdge, gradient, fragmentProg, tmpInfo );

		}
		
	}
}

#endif