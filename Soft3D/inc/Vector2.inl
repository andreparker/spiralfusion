#ifndef VECTOR_2
#define VECTOR_2

namespace MathUtil
{
	template< typename _realType >
	struct Vector2
	{
		_realType x,y;

		Vector2( void ){}
		Vector2( const Vector2& vec ):
		x(vec.x),y(vec.y){}
		Vector2( _realType _x, _realType _y ):
		x(_x),y(_y){}

		inline Vector2 operator+( const Vector2& vec )
		{
			return Vector2( x+vec.x,y+vec.y );
		}

		inline Vector2 operator-( const Vector2& vec )
		{
			return Vector2( x-vec.x,y-vec.y);
		}

		inline Vector2 operator*( const Vector2& vec )
		{
			return Vector2( x*vec.x,y*vec.y );
		}

		inline Vector2 operator/( const Vector2& vec )
		{
			return Vector2( x/vec.x,y/vec.y );
		}

		inline Vector2 operator+( _realType _val )
		{
			return Vector2( x+_val, y+_val );
		}

		inline Vector2 operator-( _realType _val )
		{
			return Vector2( x-_val, y-_val );
		}

		inline Vector2 operator*( _realType _val )
		{
			return Vector2( x*_val, y*_val );
		}

		inline Vector2 operator/( _realType _val )
		{
			return Vector2( x/_val, y/_val );
		}

		inline Vector2& operator+=( const Vector2& vec )
		{
			*this = *this + vec;
			return *this;
		}

		inline Vector2& operator-=( const Vector2& vec )
		{
			*this = *this - vec;
			return *this;
		}

		inline Vector2& operator*=( const Vector2& vec )
		{
			*this = *this * vec;
			return *this;
		}

		inline Vector2& operator/=( const Vector2& vec )
		{
			*this = *this / vec;
			return *this;
		}

		template< typename _custom >
		friend Vector2 operator+( _custom _val, const Vector2& vec )
		{
			return Vector2( _val+vec.x, _val+vec.y );
		}

		template< typename _custom >
		friend Vector2 operator-( _custom _val, const Vector2& vec )
		{
			return Vector2( _val-vec.x, _val-vec.y );
		}

		template< typename _custom >
		friend Vector2 operator*( _custom _val, const Vector2& vec )
		{
			return Vector2( _val*vec.x, _val*vec.y );
		}

		template< typename _custom >
		friend Vector2 operator/( _custom _val, const Vector2& vec )
		{
			return Vector2( _val/vec.x, _val/vec.y );
		}
	};

}

#endif