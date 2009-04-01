#ifndef RASTERCOMMON_HPP
#define RASTERCOMMON_HPP

#include "Setup.hpp"

namespace Soft3D
{
	template< class VerticeType >
	struct TriangleVertices
	{
		VerticeType v0,v1,v2;
	};

	template< class FrameBufferType, class DepthBufferType  >
	struct SurfaceInfo
	{
		boost::uint32_t width,height;
		FrameBufferType* SurfaceDataPtr;
		DepthBufferType* DepthSurfaceDataPtr;

		void Step()
		{
			SurfaceDataPtr += width;
			DepthSurfaceDataPtr += width;
		}

		void Step( boost::uint32_t yPos )
		{
			SurfaceDataPtr += width * yPos;
			DepthSurfaceDataPtr += width * yPos;
		}
	};
}

#endif