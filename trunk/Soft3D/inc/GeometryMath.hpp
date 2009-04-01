#ifndef GEOMETRYMATH_HPP
#define GEOMETRYMATH_HPP

#include "FixedPoint.inl"
#include "Vector3.inl"
#include "Vector2.inl"


namespace Soft3D
{
	typedef enum
	{
		PPC_POSITIVE = 1,
		PPC_NEGATIVE,
		PPC_ONPLANE,
	}ePointPlaneClassify_t;

	template< class T >
	inline ePointPlaneClassify_t pointToPlane( const MathUtil::Vector3< T >& point, const MathUtil::Vector4< T >& plane )
	{
		MathUtil::Vector3< T > planeNormal( plane.x, plane.y, plane.z );

		T distance = dotProduct( point, planeNormal );

		return ( distance > plane.w ? PPC_POSITIVE : ( distance < plane.w ? PPC_NEGATIVE : PPC_ONPLANE ) );
	}

	// point1 is on the positive side of the plane
	// point0 is on the negative side of the plane
	template< class T >
	inline T DistanceRatio( const MathUtil::Vector3< T >& point1, const MathUtil::Vector3< T >& point0, const MathUtil::Vector4< T >& plane )
	{
		MathUtil::Vector3< T > planeNormal( plane.x, plane.y, plane.z );

		const T distance1 = dotProduct( point1, planeNormal );
		const T distance0 = dotProduct( point0, planeNormal );

		return (plane.w - distance0)/(distance1 - distance0);
	}

	template< class _Real >
	inline _Real TriangleGradient(const MathUtil::Vector2< _Real >& v0, const MathUtil::Vector2< _Real >& v1, const MathUtil::Vector2< _Real >& v2 )
	{
		MathUtil::Vector2< _Real > n0( v2.x - v1.x, v0.y - v1.y );
		MathUtil::Vector2< _Real > n1( v0.x - v1.x, v2.y - v1.y );

		return n0.y * n0.x - n1.y * n1.x;
	}

}

#endif