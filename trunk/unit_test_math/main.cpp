#define BOOST_TEST_MAIN
#include <cmath>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "inc/FixedPoint.inl"
#include "inc/Vector3.inl"
#include "inc/Matrix.inl"
#include "inc/SineCosine.inl"
#include "inc/PolygonEdge.inl"

#include <iostream>


using namespace std;
using namespace FixedPoint;
using namespace MathUtil;
using namespace Soft3D;

const float espilon = 0.4f;

BOOST_AUTO_TEST_CASE( fixedSqrt )
{
	for( boost::uint32_t i = 1; i < 100; ++i )
	{
		const float	fVal  = static_cast< float >( i );
		fxReal16_16	fx16Val = fVal;
		fxReal18_14	fx14Val = fVal;

		BOOST_CHECK_CLOSE_FRACTION( static_cast< float >( sqrt( fx16Val ) ), sqrt( fVal ), espilon );
		BOOST_CHECK_CLOSE_FRACTION( static_cast< float >( sqrt( fx14Val ) ), sqrt( fVal ), espilon );
	
	}
	
}

BOOST_AUTO_TEST_CASE( VectorMath )
{
	Vector3< fxReal18_14 > vfxNormal14( 1.0f, -2.0f, 0.567f );
	Vector3< fxReal16_16 > vfxNormal16( 1.0f, -2.0f, 0.567f );
	Vector3< float > vNormal( 1.0f, -2.0f, 0.567f );

	Normalize( vfxNormal14, vfxNormal14 );
	Normalize( vfxNormal16, vfxNormal16 );
	Normalize( vNormal, vNormal );

	BOOST_CHECK_CLOSE_FRACTION( static_cast< float >( vfxNormal14.x ), vNormal.x, espilon );
	BOOST_CHECK_CLOSE_FRACTION( static_cast< float >( vfxNormal14.y ), vNormal.y, espilon );
	BOOST_CHECK_CLOSE_FRACTION( static_cast< float >( vfxNormal14.z ), vNormal.z, espilon );

	BOOST_CHECK_CLOSE_FRACTION( static_cast< float >( vfxNormal16.x ), vNormal.x, espilon );
	BOOST_CHECK_CLOSE_FRACTION( static_cast< float >( vfxNormal16.y ), vNormal.y, espilon );
	BOOST_CHECK_CLOSE_FRACTION( static_cast< float >( vfxNormal16.z ), vNormal.z, espilon );

}

BOOST_AUTO_TEST_CASE( MathFunc )
{
	// check factorial math functions and pow etc..
	boost::uint32_t factorial5 = factorial< boost::uint32_t >( 5 );

	BOOST_CHECK_EQUAL( factorial5, 120 );

	fxReal16_16 power10 = power( fxReal16_16(10) , 3 );
	
	BOOST_CHECK_EQUAL( static_cast< boost::uint32_t >( power10 ) , 1000 );

	// sine
	float s = sin( 90.6f * degree_to_rad );
	fxReal16_16 sf = sine( fxReal16_16( -270.6f * degree_to_rad ) );

	BOOST_CHECK_CLOSE( static_cast< float >( sf ), s, espilon );

	// tangent
	float t = tan( 45.0f * degree_to_rad );
	fxReal16_16 tf = tangent( fxReal16_16( 45.0f * degree_to_rad ) );

	BOOST_CHECK_CLOSE( static_cast< float >( tf ), t, espilon );
}


BOOST_AUTO_TEST_CASE( Matrix_Inverse )
{
	Matrix4x4< fxReal16_16 > matrix,identity;

	matrix.LoadIdentity();

	matrix = matrix * 4.0f;

	cout << "matrix 0" << endl;
	cout << matrix << endl; 

	Inverse( matrix, identity );

	cout << "inverse of matrix 0" << endl;
	cout << identity << endl;

	identity =identity  * matrix; 

	cout << " matrix 0 * inverse" << endl;
	cout << identity << endl;
}