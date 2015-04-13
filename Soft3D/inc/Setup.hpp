#ifndef SETUP_HPP
#define SETUP_HPP

#include <boost/cstdint.hpp>
#include <bitset>
#include "FixedPoint.inl"

namespace Soft3D
{
#if 0
	typedef  FixedPoint::fxReal18_14 Real;
#else
	typedef	float Real;
#endif

	// number of registers allowed for programs
	const boost::uint32_t max_register_count = 8;

	// number of textures allowed in a fragment program
	const boost::uint32_t max_texture_count = 4;

	typedef std::bitset<32> bit32;
}

#endif
