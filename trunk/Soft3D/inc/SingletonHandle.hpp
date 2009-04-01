#ifndef SINGLETONHANDLE_HPP
#define SINGLETONHANDLE_HPP

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

template< class T, T& (*singleton)() >
class SingletonHandle
{
	private:

		// must be a class
		BOOST_STATIC_ASSERT( boost::is_class< T >::value == true );

		T* m_SingletonPtr;

		SingletonHandle(const SingletonHandle& h){}
		SingletonHandle& operator=(const SingletonHandle& h){}

	public:
		SingletonHandle():
		  m_SingletonPtr( &singleton() ){}


	  T* operator->()
	  {
		  return m_SingletonPtr;
	  }

};

#endif