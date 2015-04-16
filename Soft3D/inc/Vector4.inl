#ifndef VECTOR_4
#define VECTOR_4

namespace MathUtil
{
	template< typename _realType >
	struct Vector4
	{
		_realType x,y,z,w;

		Vector4( void ){}
		Vector4( _realType _x, _realType _y, _realType _z, _realType _w ):
		x(_x),y(_y),z(_z),w(_w){}
		Vector4( const Vector4& vec ):
		x(vec.x),y(vec.y),z(vec.z),w(vec.w){}

		inline Vector4 operator+( const Vector4& vec )const
		{
			return Vector4( x+vec.x,y+vec.y,z+vec.z,w+vec.w );
		}

		inline Vector4 operator-( const Vector4& vec )const
		{
			return Vector4( x-vec.x,y-vec.y,z-vec.z,w-vec.w );
		}

		inline Vector4 operator*( const Vector4& vec )const
		{
			return Vector4( x*vec.x,y*vec.y,z*vec.z,w*vec.w );
		}

		inline Vector4 operator/( const Vector4& vec )const
		{
			return Vector4( x/vec.x,y/vec.y,z/vec.z,w/vec.w );
		}

		inline Vector4 operator+( _realType _val )const
		{
			return Vector4( x+_val,y+_val,z+_val,w+_val );
		}

		inline Vector4 operator*( _realType _val )const
		{
			return Vector4( x*_val,y*_val,z*_val,w*_val );
		}

		inline Vector4 operator-( _realType _val )const
		{
			return Vector4( x-_val,y-_val,z-_val,w-_val );
		}

		inline Vector4 operator/( _realType _val )const
		{
			return Vector4( x/_val,y/_val,z/_val,w/_val );
		}

		inline Vector4& operator+=( _realType _val )
		{
			*this = *this + _val;
			return *this;
		}

		inline Vector4& operator-=( _realType _val )
		{
			*this = *this - _val;
			return *this;
		}

		inline Vector4& operator*=( _realType _val )
		{
			*this = *this * _val;
			return *this;
		}

		inline Vector4& operator/=( _realType _val )
		{
			*this = *this / _val;
			return *this;
		}

		inline Vector4& operator+=( const Vector4& vec )
		{
			*this = *this + vec;
			return *this;
		}

		inline Vector4& operator-=( const Vector4& vec )
		{
			*this = *this - vec;
			return *this;
		}

		inline Vector4& operator*=( const Vector4& vec )
		{
			*this = *this * vec;
			return *this;
		}

		inline Vector4& operator/=( const Vector4& vec )
		{
			*this = *this / vec;
			return *this;
		}

		template< typename _custom >
		friend Vector4 operator+( _custom _val, const Vector4& vec )
		{
			return Vector4( _val+vec.x, _val+vec.y, _val+vec.z, _val+vec.w );
		}

		template< typename _custom >
		friend Vector4 operator-( _custom _val, const Vector4& vec )
		{
			return Vector4( _val-vec.x, _val-vec.y, _val-vec.z, _val-vec.w );
		}

		template< typename _custom >
		friend Vector4 operator*( _custom _val, const Vector4& vec )
		{
			return Vector4( _val*vec.x, _val*vec.y, _val*vec.z, _val*vec.w );
		}

		template< typename _custom >
		friend Vector4 operator/( _custom _val, const Vector4& vec )
		{
			return Vector4( _val/vec.x, _val/vec.y, _val/vec.z, _val/vec.w );
		}
	};

	template< typename T >
	inline T dotProduct( const Vector4< T >& vec0, const Vector4< T >& vec1 )
	{
		return vec0.x * vec1.x + vec0.y * vec1.y + vec0.z * vec1.z + vec0.w * vec1.w;
	}

    template< typename T >
    inline Vector4< T >& clamp( Vector4< T >& vec0, T val )
    {
        vec0.x = vec0.x > val ? val : ( vec0.x < 0.0f ? 0.0f : vec0.x );
        vec0.y = vec0.y > val ? val : ( vec0.y < 0.0f ? 0.0f : vec0.y );
        vec0.x = vec0.z > val ? val : ( vec0.z < 0.0f ? 0.0f : vec0.z );
        vec0.x = vec0.w > val ? val : ( vec0.w < 0.0f ? 0.0f : vec0.w );

        return vec0;
    }

	template< typename T >
	inline Vector4< T >& Normalize( const Vector4< T >& vec0, Vector4< T >& vecRet )
	{
		const T dist = vec0.x * vec0.x + vec0.y * vec0.y + vec0.z * vec0.z;
		const T s = 1.0f / sqrt( dist );

		vecRet.x = vec0.x * s;
		vecRet.y = vec0.y * s;
		vecRet.z = vec0.z * s;
		vecRet.w = vec0.w * s;

		return vecRet;
	}
}

#endif
