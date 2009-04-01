#include <boost/foreach.hpp>
#include "../inc/FragmentProgram.hpp"


namespace Soft3D
{
	FragmentProgram::FragmentProgram()
	{
		BOOST_FOREACH( Mat4& matrix, m_Matrices )
		{
			matrix.LoadIdentity();
		}
	}
}