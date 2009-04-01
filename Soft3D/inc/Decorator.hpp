#ifndef DECORATOR_HPP
#define DECORATOR_HPP

#include <boost/shared_ptr.hpp>

// this can only be derived
template< class _ComponentClass >
class Decorator : public _ComponentClass
{
	public:
		void SetComponent( boost::shared_ptr< _ComponentClass >& componentPtr )
		{
			m_componentPtr = componentPtr;
		}

		const boost::shared_ptr< _ComponentClass >& GetComponent()const
		{
			return m_componentPtr;
		}

	protected:
		Decorator( boost::shared_ptr< _ComponentClass >& componentPtr ):
		  m_componentPtr( componentPtr ){}

		boost::shared_ptr< _ComponentClass > m_componentPtr;
};

#endif