#ifndef DEFAULTFRAGMENTPROGRAM_HPP
#define DEFAULTFRAGMENTPROGRAM_HPP

#include "FragmentProgram.hpp"

namespace Soft3D
{
	class DefaultFragmentProgram :
		public FragmentProgram
	{
		public:
			DefaultFragmentProgram(){}

			virtual void Execute();
	};
}

#endif
