#ifndef SINECOSINE_INL
#define SINECOSINE_INL

#include <cmath>
#include <boost/cstdint.hpp>
#include "MathTables.hpp"
#include "FixedPoint.inl"
#include "Interpolation.inl"

namespace MathUtil
{

	template< boost::uint32_t W, boost::uint32_t F, const boost::uint32_t TABLE_SIZE  >
	inline FixedPoint::fxReal< W, F > mathTable( const boost::int32_t* tablePtr, const FixedPoint::fxReal< W, F >& val )
	{
		const FixedPoint::fxReal< W, F > degree = val * rad_to_degree;
		const boost::int32_t iDegree =  static_cast< boost::int32_t >( degree );
		const float pc = static_cast< float >( ( iDegree % 360 ) / 360.f );
		const boost::uint32_t whole = ( static_cast< boost::int32_t >( pc * (TABLE_SIZE-1) ) + (TABLE_SIZE-1) ) & (TABLE_SIZE - 1);
		const FixedPoint::fxReal< W, F > frac = degree.Frac();

		FixedPoint::fxReal< W, F > baseVal;
		FixedPoint::fxReal< W, F > nextVal;

		const boost::int32_t bVal = FixedPoint::ConvertFixed< boost::int32_t, 24, F >( tablePtr[ (whole + 1) & (TABLE_SIZE-1) ] );
 		const boost::int32_t nVal = FixedPoint::ConvertFixed< boost::int32_t, 24, F >( tablePtr[ whole ] );

		return lerp( nextVal.AsRaw(  bVal ),baseVal.AsRaw( nVal ), frac );
	}

	template< boost::uint32_t W, boost::uint32_t F >
	inline FixedPoint::fxReal< W, F > sine( const FixedPoint::fxReal< W, F >& val )
	{
		const boost::int32_t* sineTablePtr = MathTableMgr::singleton().GetSineTable();

		return mathTable< W, F, max_table_size >(  sineTablePtr, val );
	}

	template< boost::uint32_t W, boost::uint32_t F >
	inline FixedPoint::fxReal< W, F > cosine( const FixedPoint::fxReal< W, F >& val )
	{
		return sine< W, F >( val ) - 1.0f;
	}

	template< boost::uint32_t W, boost::uint32_t F >
	inline FixedPoint::fxReal< W, F > tangent( const FixedPoint::fxReal< W, F >& val )
	{
		const boost::int32_t* tangentTablePtr = MathTableMgr::singleton().GetTanTable();

		return mathTable< W, F, max_table_size >( tangentTablePtr, val );
	}

	inline float sine( float val )
	{
		return std::sin( val );
	}

	inline float cosine( float val )
	{
		return std::cos( val );
	}

	inline float tangent( float val )
	{
		return std::tan( val );
	}
}

#endif