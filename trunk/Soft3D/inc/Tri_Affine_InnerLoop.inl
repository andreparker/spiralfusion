#ifndef TRI_AFFINE_INNERLOOP_INL
#define TRI_AFFINE_INNERLOOP_INL

#include <algorithm>
#include "Setup.hpp"
#include "VertexTypes.hpp"
#include "PolygonEdge.inl"
#include "PolygonGradient.inl"
#include "FragmentProgram.hpp"
#include "RasterCommon.hpp"
#include "utility.hpp"

#include "Profiler.hpp"
namespace Soft3D
{

	template< class _Real, class FrameBufferType, class DepthBufferType, class VertexType >
	void RasterEdges_Affine(
							PolygonEdge< _Real, VertexType >& left,
							PolygonEdge< _Real, VertexType >& right,
							PolygonGradient< _Real, VertexType >& gradient,
							FragmentProgram& fragmentProg,
							SurfaceInfo< FrameBufferType, DepthBufferType >& info )
	{
		typedef PolygonEdge< _Real, VertexType >::EdgeData EdgeData;
		typedef PolygonGradient< _Real, VertexType >::GradientData GradientData;

		PROFILE_FUNCTION();

		// get raster height
		boost::uint32_t height = static_cast< boost::uint32_t> ( std::min( static_cast< boost::int32_t >( left.GetHeight() ),
												 static_cast< boost::int32_t >( right.GetHeight() ) ) );
		left.SubtractHeight( height );
		right.SubtractHeight( height );

		GradientData gradients = gradient.GetGradientData();

		EdgeData leftData,rightData;
		boost::uint32_t leftX,scanSize;
		FrameBufferType* currentScanLinePtr;
		FrameBufferType  currentPixel = fragmentProg.Sample().color;

		while( height-- != 0 )
		{
			leftData = left.GetEdgeData();
			rightData = right.GetEdgeData();

			leftX = static_cast< boost::uint32_t >( FixedPoint::Ceil(leftData.x) );
			scanSize = static_cast< boost::uint32_t >( FixedPoint::Ceil(rightData.x) ) - leftX;

			currentScanLinePtr = &info.SurfaceDataPtr[ leftX ];

			Soft3D::duff_copy4( currentPixel, currentScanLinePtr, scanSize );

			currentScanLinePtr += scanSize;

			left.Step();
			right.Step();
			info.Step();

		}
	}
}

#endif