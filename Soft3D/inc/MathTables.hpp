#ifndef MATHTABLES_HPP
#define MATHTABLES_HPP

#include <cmath>
#include <boost/foreach.hpp>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>


namespace MathUtil
{
	// some math constants
	const float pi = 3.1415926535897932384626433832795f;
	const float rad_to_degree = 180 / pi;
	const float degree_to_rad = pi / 180;

	const boost::uint32_t max_table_size = 256;
	const float fixScale = 16777216.0f;

	class MathTableMgr 
	{
		private:
			MathTableMgr();
			MathTableMgr( const MathTableMgr& m );
			MathTableMgr& operator=( const MathTableMgr& m );

			boost::int32_t m_Sine[ max_table_size ];
			boost::int32_t m_Tan[ max_table_size ];

		public:

			static MathTableMgr& singleton()
			{
				static MathTableMgr _instance;

				return _instance;
			}

			const boost::int32_t* GetSineTable()const
			{
				return &m_Sine[0];
			}

			const boost::int32_t* GetTanTable()const
			{
				return &m_Tan[0];
			}
	};
}

#endif