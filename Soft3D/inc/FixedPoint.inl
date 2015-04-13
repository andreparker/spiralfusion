#ifndef FIXEDPOINT_
#define FIXEDPOINT_

#include <cmath>
#include <climits>
#include <boost/assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>

// disabled to stop warning about fixed point convertsion overflows
#ifdef _MSC_VER
#pragma warning( disable: 4293 )
#endif

namespace FixedPoint
{

	//========================================================================

	inline void _inner_sqrt( boost::uint32_t& val,boost::uint32_t& g, boost::uint32_t& b, boost::uint32_t& bShift );

	//=========================================================================
	template< int _bits >
	struct fixed_data;
	/*{
		fixed_data( void ){}
		fixed_data( const char& _val ):
		data( _val ){}

		typedef boost::int8_t FIXED_TYPE;
		char data;
	};*/

	template<> struct fixed_data< 1 >
	{
		fixed_data( ){}
		fixed_data( const char& _val ):
		data( _val ){}

		typedef boost::int8_t FIXED_TYPE;
		char data;
	};

	template<> struct fixed_data< 2 >
	{
		fixed_data( ){}
		fixed_data( const short& _val ):
		data( _val ){}

		typedef boost::int16_t FIXED_TYPE;
		short data;
	};

	template<> struct fixed_data< 3 >
	{
		fixed_data( ){}
		fixed_data( const int& _val ):
		data( _val ){}

		typedef boost::int32_t FIXED_TYPE;
		int data;
	};

	template<> struct fixed_data< 4 >
	{
		fixed_data( ){}
		fixed_data( const long& _val ):
		data( _val ){}

		typedef boost::int32_t FIXED_TYPE;
		long data;
	};


	template< boost::uint32_t _whole,
		      boost::uint32_t _frac,
			  typename _Real =
			  fixed_data<
			  ( ( _whole + _frac) >= 32 ? 1 : 0 ) +
			  ( ( _whole + _frac) >= 24 ? 1 : 0 ) +
			  ( ( _whole + _frac) >= 16 ? 1 : 0 ) +
			  ( ( _whole + _frac) >= 8  ? 1 : 0 )
			  		    > >
	class fxReal
	{
	public:

		typedef typename _Real::FIXED_TYPE          data_type;

		BOOST_STATIC_ASSERT
			( boost::is_integral< data_type >::value == true &&
			  boost::is_floating_point< data_type >::value == false
			);

		typedef fxReal<_whole,_frac,_Real>          fixedType;



		static const boost::uint32_t _IntegerBits = _whole;
		static const boost::uint32_t _FracBits    = _frac;
		static const boost::uint32_t _HighMask = ( ( 1<< _whole )-1 ) << _frac;
		static const boost::uint32_t _LowMask  = ( ( 1<< _frac  )-1 );
		static const boost::uint32_t _FIX_ONE  = ( 1 << _frac );


		fxReal( void ){}

		fxReal( const fixedType& fixed )
		{
			AsRaw( fixed.Raw() );
		}

		fxReal( float f ):
		m_data(static_cast< data_type >(f * static_cast< float >(1 << _frac)))
		{}

		fxReal( double f ):
		m_data(static_cast< data_type >(f * static_cast< double >(1 << _frac)))
		{}

		template< typename _custom >
		fxReal( _custom _val ):
		m_data(static_cast< data_type >( _val << _frac ))
		{}

		inline fixedType const& operator=( fixedType fixed )
		{
			m_data.data = fixed.Raw();
			return *this;
		}

		inline data_type Raw( void )const { return m_data.data; }
		inline fixedType& AsRaw( data_type _val )
		{
			m_data.data = _val;
			return *this;
		}

		static fixedType AS_RAW( data_type _val )
		{
			return fixedType().AsRaw( _val );
		}

		inline fixedType Frac()const
		{
			return AS_RAW( Raw() & _LowMask );
		}

		//==========================================================
		// float operators
		//==========================================================
		operator float( void )const{ return static_cast< float >(  Raw()  * ( 1.0f / _FIX_ONE ) ); };
		operator double( void )const{ return static_cast< double >(  Raw()  * ( 1.0 / _FIX_ONE ) ); };
		template< typename _custom > operator _custom( void )const{ return static_cast< _custom >( Raw() >> _frac ); }


		inline fixedType operator+( float fl )const
		{
			return *this + fixedType( fl );
		}

		inline fixedType operator-( float fl )const
		{
			return *this - fixedType( fl );
		}

		inline fixedType operator*( float fl )const
		{
			return *this * fixedType( fl );
		}

		inline fixedType operator/( float fl )const
		{
			return *this / fixedType( fl );
		}

		inline fixedType operator-()const
		{
			return AS_RAW( -Raw() );
		}
		//===========================================================
		inline fixedType& operator+=( float fl )
		{
			*this = *this + fixedType( fl );
			return *this;
		}

		inline fixedType& operator-=( float fl )
		{
			*this = *this - fixedType( fl );
			return *this;
		}

		inline fixedType& operator*=( float fl )
		{
			*this = *this * fixedType( fl );
			return *this;
		}

		inline fixedType& operator/=( float fl )
		{
			*this = *this / fixedType( fl );
			return *this;
		}
		//===========================================================

		//==========================================================
		// double operators
		//==========================================================
		inline fixedType operator+( double fl )const
		{
			return *this + fixedType( fl );
		}

		inline fixedType operator-( double fl )const
		{
			return *this - fixedType( fl );
		}

		inline fixedType operator*( double fl )const
		{
			return *this * fixedType( fl );
		}

		inline fixedType operator/( double fl )const
		{
			return *this / fixedType( fl );
		}

		//===========================================================
		inline fixedType& operator+=( double fl )
		{
			*this = *this + fixedType( fl );
			return *this;
		}

		inline fixedType& operator-=( double fl )
		{
			*this = *this - fixedType( fl );
			return *this;
		}

		inline fixedType& operator*=( double fl )
		{
			*this = *this * fixedType( fl );
			return *this;
		}

		inline fixedType& operator/=( double fl )
		{
			*this = *this / fixedType( fl );
			return *this;
		}
		//===========================================================
		//==========================================================
		// _custom operators
		//==========================================================
		template< typename _cType >
		fixedType operator+( _cType _val )const
		{
			return *this + fixedType( _val );
		}

		template< typename _cType >
		fixedType operator-( _cType _val )const
		{
			return *this - fixedType( _val );
		}

		template< typename _cType >
		fixedType operator*( _cType _val )const
		{
			return AS_RAW( Raw() * _val );
		}

		template< typename _cType >
		fixedType operator/( _cType _val )const
		{
			return AS_RAW( Raw() / _val );
		}

		//===========================================================
		template< typename _cType >
		fixedType& operator+=( _cType _val )
		{
			*this = *this + fixedType( _val );
			return *this;
		}

		template< typename _cType >
		fixedType& operator-=( _cType _val )
		{
			*this = *this - fixedType( _val );
			return *this;
		}

		template< typename _cType >
		fixedType& operator*=( _cType _val )
		{
			AsRaw( Raw() * _val );
			return *this;
		}

		template< typename _cType >
		fixedType& operator/=( _cType _val )
		{
			AsRaw( Raw() / _val );
			return *this;
		}
		//===========================================================

		bool operator<( fixedType fixed )const
		{
			return (Raw() < fixed.Raw()) ? true : false;
		}

		bool operator>( fixedType fixed )const
		{
			return (Raw() > fixed.Raw()) ? true : false;
		}

		bool operator<=( fixedType fixed )const
		{
			return (Raw() <= fixed.Raw()) ? true : false;
		}

		bool operator>=( fixedType fixed )const
		{
			return (Raw() >= fixed.Raw()) ? true : false;
		}

		inline bool operator<=( int val )const
		{
			return (Raw() <= val ) ? true : false;
		}

		inline bool operator>=( int val )const
		{
			return (Raw() >= val ) ? true : false;
		}

		inline bool operator<( int val )const
		{
			return (Raw() < val ) ? true : false;
		}

		inline bool operator>( int val )const
		{
			return (Raw() > val ) ? true : false;
		}

		inline bool operator!=( int val)const
		{
			return (Raw() != val) ? true : false;
		}

		bool operator==( fixedType fixed )const
		{
			return (Raw() == fixed.Raw()) ? true : false;
		}

		bool operator!=( fixedType fixed )const
		{
			return (Raw() != fixed.Raw()) ? true : false;
		}

		inline fixedType operator*( fixedType fixed )const
		{
			return AS_RAW( static_cast< data_type >(
				(static_cast< boost::int64_t >( fixed.Raw() ) * Raw() ) >> _frac
				) );
		}

		inline fixedType operator/( fixedType fixed )const
		{
			return AS_RAW( static_cast< data_type >(
				( static_cast< boost::int64_t >( Raw() ) << _frac )  / fixed.Raw()
				) );
		}

		inline fixedType operator+( fixedType fixed )const
		{
			return AS_RAW( Raw() + fixed.Raw() );
		}

		inline fixedType operator-( fixedType fixed )const
		{
			return AS_RAW( Raw() - fixed.Raw() );
		}

		inline fixedType& operator*=( fixedType fixed )
		{
			*this = *this * fixed;
			return *this;
		}

		inline fixedType& operator/=( fixedType fixed )
		{
			*this = *this / fixed;
			return *this;
		}

		inline fixedType& operator+=( fixedType fixed )
		{
			*this = *this + fixed;
			return *this;
		}

		inline fixedType& operator-=( fixedType fixed )
		{
			*this = *this - fixed;
			return *this;
		}

		template< typename _cType >
		friend fixedType operator+( _cType _val, fixedType fixed )
		{
			return fixed + fixedType(_val);
		}

		template< typename _cType >
		friend fixedType operator-( _cType _val, fixedType fixed )
		{
			return fixedType( _val ) - fixed;
		}

		template< typename _cType >
		friend fixedType operator*( _cType _val, fixedType fixed )
		{
			return AS_RAW( static_cast< data_type>(fixed.Raw() * _val) );
		}

		friend fixedType operator*( const float _val, fixedType fixed )
		{
			return AS_RAW( static_cast< data_type>(fixed.Raw() * fixedType(_val)) );
		}

		friend fixedType operator*( const double _val, fixedType fixed )
		{
			return AS_RAW( static_cast< data_type>(fixed.Raw() * fixedType(_val)) );
		}

		template< typename _cType >
		friend fixedType operator/( _cType _val, fixedType fixed )
		{
			fixedType tmp( _val );
			return tmp / fixed;
		}

		friend fixedType Ceil( fixedType fixed )
		{
			return AS_RAW( (fixed.Raw() + fixedType::_LowMask) &
								fixedType::_HighMask
							);
		}


		friend fixedType Min( fixedType fixed0,
			                           fixedType fixed1 )
		{
			const fixedType value = fixed0 - fixed1;
			const fixedType::data_type signMask = value.Raw() >> ( (sizeof(fixedType::data_type) * CHAR_BIT) - 1 );
			return AS_RAW( ( fixed0.Raw() - ( value.Raw() & ~signMask )) );

		}

		friend fixedType Max( fixedType fixed0,
			fixedType fixed1 )
		{
			const fixedType value = fixed0 - fixed1;
			const fixedType::data_type signMask = value.Raw() >> ( (sizeof(fixedType::data_type) * CHAR_BIT) - 1 );
			return AS_RAW( ( fixed0.Raw() - ( value.Raw() & signMask )) );

		}

		friend const fixedType abs( fixedType val0 )
		{
			return AS_RAW(( val0.Raw() < 0 ? -val0.Raw() : val0.Raw() ) );
		}


	private:

		_Real m_data;
	};



	template< typename T >
	inline T Min( T val0,T val1 )
	{
		const T value = val0 - val1;
		const T signMask = value >> ( (sizeof(T) * CHAR_BIT) - 1 );
		return val0 - ( value & ~signMask );
	}

	template< typename T >
	inline T Max( T val0,T val1 )
	{
		const T value = val0 - val1;
		const T signMask = value >> ( (sizeof(T) * CHAR_BIT) - 1 );
		return val0 - ( value & signMask );
	}

	template<>
	inline float Min( float val0,float val1 )
	{
		return ( val0 < val1 ? val0 : val1 );
	}

	template<>
	inline float Max( float val0,float val1 )
	{
		return ( val0 > val1 ? val0 : val1 );
	}

	template<>
	inline double Min( double val0,double val1 )
	{
		return ( val0 < val1 ? val0 : val1 );
	}

	template<>
	inline double Max( double val0,double val1 )
	{
		return ( val0 > val1 ? val0 : val1 );
	}

	inline float Ceil( float fval )
	{
		return ceilf( fval );
	}

	// convert Current fractional, to New Fractional
	// C = current frac bits
	// N = new frac bits
	template< typename T, boost::uint32_t C, boost::uint32_t N >
	T ConvertFixed( T val )
	{
		BOOST_STATIC_ASSERT( boost::is_integral< T >::value == true );

		return ( N > C ? val << (N-C) : ( C > N ? val >> (C-N) : val ) );
	}

	inline void _inner_sqrt( boost::uint32_t& val,boost::uint32_t& g, boost::uint32_t& b, boost::uint32_t& bShift )
	{
		const boost::uint32_t compare = ((( g << 1 ) + b) << bShift);
		--bShift;
		if( val >= compare )
		{
			g += b;
			val -= compare;
		}
	}

	template< boost::uint32_t w,
				boost::uint32_t f >
	fxReal<w,f> sqrt( fxReal<w,f> val0 )
	{
		fxReal<w,f> value;
		boost::uint32_t shift	= ( sizeof( fxReal<w,f>::data_type ) * CHAR_BIT ) / 2 - 1;
		boost::uint32_t b		= ( 1 << shift );
		boost::uint32_t g		= 0;
		boost::uint32_t val		= static_cast< boost::uint32_t >( val0.Raw() );

		do
		{
			_inner_sqrt( val, g, b, shift );
		}while( b >>= 1 );

		return fxReal<w,f>::AS_RAW( ConvertFixed< fxReal<w,f>::data_type,
									(fxReal<w,f>::_FracBits >> 1),
									fxReal<w,f>::_FracBits >( static_cast< typename fxReal<w,f>::data_type >( g ) ) );
	}

	template< typename T >
	inline T power( T val, boost::uint32_t p )
	{
		const boost::uint32_t count = p - 1;
		boost::uint32_t wCount = ( count + 3 ) >> 2;
		T retVal = val;

		if( p == 1 ) return static_cast< T >( 1 );

		switch( count & 3 )
		{
			do
			{
		        case 0: retVal *= val;
		        case 3: retVal *= val;
		        case 2: retVal *= val;
		        case 1: retVal *= val;
			}while( --wCount != 0 );

		}

		return retVal;
	}

	template< typename T >
	inline T factorial( boost::uint32_t val )
	{
		const boost::uint32_t count = (val-1);
		boost::uint32_t wCount = ( count + 3) >> 2;
		boost::uint32_t factorialCount = 2;
		T factorialNumber = 1;

		if( val == 1 ) return static_cast< T >( 1 );

		switch( count & 3 )
		{
			do
			{
		        case 0: factorialNumber *= factorialCount++;
		        case 3: factorialNumber *= factorialCount++;
		        case 2: factorialNumber *= factorialCount++;
		        case 1: factorialNumber *= factorialCount++;
			}while( --wCount != 0 );
		}

		return factorialNumber;
	}

	// custum defined types
	typedef fxReal< 16, 16 > fxReal16_16;
	typedef fxReal< 24, 8 >  fxReal24_8;
	typedef fxReal< 8, 24 > fxReal8_24;
	typedef fxReal< 1, 30 > fxReal1_30;
	typedef fxReal< 18, 14 > fxReal18_14;
	typedef fxReal< 8, 8 >   fxReal8_8;


}

#endif
