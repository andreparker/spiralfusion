#ifndef ELEMENTPROCESSCOMPONENT_HPP
#define	ELEMENTPROCESSCOMPONENT_HPP

#include "Setup.hpp"
#include "ElementData.hpp"

class ElementProcessComponent
{
	public:

		// used to process ElementData
		virtual void Process( ElementData* dataPtr ) = 0;
		//{
			// let the data choose how it is processed by this class
		//	dataPtr->Process( this );
		//}
};

#endif
 