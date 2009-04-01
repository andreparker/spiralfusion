#ifndef SWVERTEXTRANSFORM_HPP
#define SWVERTEXTRANSFORM_HPP

#include "ElementProcessComponent.hpp"
#include "Decorator.hpp"

namespace Soft3D
{
	class SwVertexTransform : 
		public Decorator< ElementProcessComponent >
	{
		public:
			SwVertexTransform( ElementProcessComponent* elemntProcessPtr ):
			  Decorator( boost::shared_ptr< ElementProcessComponent >(elemntProcessPtr) ){}

			virtual void Process( ElementData* dataPtr );
	};
}

#endif