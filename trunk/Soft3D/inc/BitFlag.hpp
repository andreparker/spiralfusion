#ifndef BITFLAG_HPP
#define BITFLAG_HPP

#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>

template< class T >
class BitFlag
{
public:

	// check for interger types
	BOOST_STATIC_ASSERT( boost::is_integral< T >::value == true );

	BitFlag(T flags):m_flags(flags) {}

	BitFlag():m_flags(0){}
	~BitFlag(void){}

	operator T()
	{
		return m_flags;
	}

	template< class R >
	BitFlag<T>& operator>>(R s)
	{
		BOOST_STATIC_ASSERT( boost::is_integral< R >::value == true );
		m_flags = m_flags >> s;
		return *this;
	}

	template< class R >
	BitFlag<T>& operator<<(R s)
	{
		BOOST_STATIC_ASSERT( boost::is_integral< R >::value == true );
		m_flags = m_flags << s;
		return *this;
	}

	template< class R >
	inline bool Test(R bit)const
	{
		BOOST_STATIC_ASSERT( boost::is_integral< R >::value == true );
		return ((1<<bit) & m_flags) > 0;
	}

	template< class R >
	inline void Clear(R bit)
	{ 
		BOOST_STATIC_ASSERT( boost::is_integral< R >::value == true );
		m_flags &= ~(1<<bit);
	}

	template< class R >
	void Set(R bit)
	{
		BOOST_STATIC_ASSERT( boost::is_integral< R >::value == true );
		if( !Test(bit) )
			m_flags |= (1<<bit);
	}

	inline bool TestAbsoluete(const T& val)const
	{
		return (m_flags & val) > 0;
	}

	void SetAbsoluete(const T& val )
	{
		if(!TestAbsoluete(val))
			m_flags |= val;
	}

	inline void ClearAbsoluete(const T& val )
	{
		m_flags = ~(val) & m_flags;
	}

	BitFlag<T>& operator=(const BitFlag<T>& f)
	{
		m_flags = f.m_flags;
		return *this;
	}

	template< class R >
	BitFlag<T>& operator=(const T& val)
	{
		m_flags = val;
		return *this;
	}

	BitFlag<T>& operator|=(const T& val)
	{
		m_flags |= val;
		return *this;
	}

	BitFlag<T> operator|(const T& val)
	{
		return BitFlag( m_flags | val );
	}

	template< class R >
	R BitSetCount()const
	{
		BOOST_STATIC_ASSERT( boost::is_integral< R >::value == true );

		R totalCount = 0;
		T bits = m_flags;
		while( bits )
		{
			bits &= bits - 1;
			++totalCount;
		}

		return totalCount;
	}
protected:
	T m_flags;
};

typedef BitFlag<boost::uint32_t> Bit32;
typedef BitFlag<boost::uint16_t> Bit16;
typedef BitFlag<boost::uint8_t> Bit8;
#endif
