#include "../inc/MathTables.hpp"
#include "../inc/FixedPoint.inl"



using namespace std;
using namespace FixedPoint;

namespace MathUtil
{
	
	MathTableMgr::MathTableMgr()
	{
		// generates various look up tables
		boost::uint32_t angle = 0;
		BOOST_FOREACH( boost::int32_t& val, m_Sine )
		{
			// map 0-max_table_size to 0-360 then convert from degrees to radians
			const float rad = static_cast< float >( ( static_cast< float >( angle ) / (max_table_size-1) ) * 360.0f * degree_to_rad );

			// get sine value and convert it to 8.24 fixed
			val = static_cast< boost::uint32_t >( sin( rad ) * fixScale );

			BOOST_ASSERT( ( val >> 24 ) <= 1 && "Value is greater than one!" );
			++angle;
		}

		angle = 0;
		BOOST_FOREACH( boost::int32_t& val, m_Tan )
		{
			// map 0-max_table_size to 0-360 then convert from degrees to radians
			const float rad = static_cast< float >( ( static_cast< float >( angle ) / (max_table_size-1) ) * 360.0f * degree_to_rad );

			// get sine value and convert it to 8.24 fixed
			val = static_cast< boost::uint32_t >( tan( rad ) * fixScale );

			++angle;
		}
	}

	MathTableMgr::MathTableMgr( const MathTableMgr& m )
	{
	}

	MathTableMgr& MathTableMgr::operator=( const MathTableMgr& m )
	{
		return *this;
	}

	
	
}