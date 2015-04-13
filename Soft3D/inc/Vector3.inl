#ifndef VECTOR_3
#define VECTOR_3

namespace MathUtil
{
	template< typename _realType >
	struct Vector3
	{
		_realType x,y,z,pad;

		Vector3( void ){}
		Vector3( const Vector3& vec ):
		x(vec.x),y(vec.y),z(vec.z){}
		Vector3( _realType _x, _realType _y, _realType _z ):
		x(_x),y(_y),z(_z){}

		inline Vector3 operator+( const Vector3& vec )
		{
			return Vector3( x+vec.x,y+vec.y,z+vec.z );
		}

		inline Vector3 operator-( const Vector3& vec )
		{
			return Vector3( x-vec.x,y-vec.y,z-vec.z );
		}

		inline Vector3 operator*( const Vector3& vec )
		{
			return Vector3( x*vec.x,y*vec.y,z*vec.z );
		}

		inline Vector3 operator/( const Vector3& vec )
		{
			return Vector3( x/vec.x,y/vec.y,z/vec.z );
		}

		inline Vector3 operator+( _realType _val )
		{
			return Vector3( x+_val,y+_val,z+_val );
		}

		inline Vector3 operator*( _realType _val )
		{
			return Vector3( x*_val,y*_val,z*_val );
		}

		inline Vector3 operator-( _realType _val )
		{
			return Vector3( x-_val,y-_val,z-_val );
		}

		inline Vector3 operator/( _realType _val )
		{
			return Vector3( x/_val,y/_val,z/_val );
		}

		inline Vector3& operator+=( _realType _val )
		{
			*this = *this + _val;
			return *this;
		}

		inline Vector3& operator-=( _realType _val )
		{
			*this = *this - _val;
			return *this;
		}

		inline Vector3& operator*=( _realType _val )
		{
			*this = *this * _val;
			return *this;
		}

		inline Vector3& operator/=( _realType _val )
		{
			*this = *this / _val;
			return *this;
		}

		inline Vector3& operator+=( const Vector3& vec )
		{
			*this = *this + vec;
			return *this;
		}

		inline Vector3& operator-=( const Vector3& vec )
		{
			*this = *this - vec;
			return *this;
		}

		inline Vector3& operator*=( const Vector3& vec )
		{
			*this = *this * vec;
			return *this;
		}

		inline Vector3& operator/=( const Vector3& vec )
		{
			*this = *this / vec;
			return *this;
		}

		template< typename _custom >
		friend Vector3 operator+( _custom _val, const Vector3& vec )
		{
			return Vector3( _val+vec.x, _val+vec.y, _val+vec.z );
		}

		template< typename _custom >
		friend Vector3 operator-( _custom _val, const Vector3& vec )
		{
			return Vector3( _val-vec.x, _val-vec.y, _val-vec.z );
		}


		friend Vector3 operator-( const Vector3& vec0, const Vector3& vec1 )
		{
			return Vector3( vec0.x-vec1.x, vec0.y-vec1.y, vec0.z-vec1.z );
		}

		template< typename _custom >
		friend Vector3 operator*( _custom _val, const Vector3& vec )
		{
			return Vector3( _val*vec.x, _val*vec.y, _val*vec.z );
		}

		template< typename _custom >
		friend Vector3 operator/( _custom _val, const Vector3& vec )
		{
			return Vector3( _val/vec.x, _val/vec.y, _val/vec.z );
		}
	};

	template< typename T >
	inline Vector3< T >& Normalize( const Vector3< T >& vec0, Vector3< T >& vecRet )
	{
		const T dist = vec0.x * vec0.x + vec0.y * vec0.y + vec0.z * vec0.z;
		const T s = 1.0f / sqrt( dist );

		vecRet.x = vec0.x * s;
		vecRet.y = vec0.y * s;
		vecRet.z = vec0.z * s;

		return vecRet;
	}

	template< typename T >
	inline T dotProduct( const Vector3< T >& vec0, const Vector3< T >& vec1 )
	{
		return vec0.x * vec1.x + vec0.y * vec1.y + vec0.z * vec1.z;
	}
}

#endif
