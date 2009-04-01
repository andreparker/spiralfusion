#ifndef ELEMENTDATA_HPP
#define ELEMENTDATA_HPP

class ElementProcessComponent;

class ElementData
{
	public:

		// used to process its own data by using methods from a ElementProcessComponent
		virtual void Process( ElementProcessComponent* elementComponentPtr ) = 0;
};

#endif