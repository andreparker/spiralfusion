#ifndef MATRIX_INL
#define MATRIX_INL

#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>

#include "Vector3.inl"
#include "Vector4.inl"
#include "SineCosine.inl"
#include "Utility.hpp"
#include <iostream>

namespace MathUtil
{
	// matrices are in Col x Row
	// _m(Col)(Row)
	template< typename _realType >
	class Matrix4x4
	{
		public:
			Matrix4x4(){}

			_realType& operator()( boost::uint32_t row, boost::uint32_t col )const
			{
				return const_cast< _realType* >(&_m11)[ (col << 2) + row ];
			}

			_realType& operator[]( boost::uint32_t index )const
			{
				return const_cast< _realType* >(&_m11)[ index ];
			}

			Matrix4x4 operator*( const Matrix4x4& mat )const
			{
				Matrix4x4 result;

				result._m11 = _m11 * mat._m11 + _m12 * mat._m12 + _m13 * mat._m13 + _m14 * mat._m14;
				result._m12 = _m11 * mat._m21 + _m12 * mat._m22 + _m13 * mat._m23 + _m14 * mat._m24;
				result._m13 = _m11 * mat._m31 + _m12 * mat._m32 + _m13 * mat._m33 + _m14 * mat._m34;
				result._m14 = _m11 * mat._m41 + _m12 * mat._m42 + _m13 * mat._m43 + _m14 * mat._m44;

				result._m21 = _m21 * mat._m11 + _m22 * mat._m12 + _m23 * mat._m13 + _m24 * mat._m14;
				result._m22 = _m21 * mat._m21 + _m22 * mat._m22 + _m23 * mat._m23 + _m24 * mat._m24;
				result._m23 = _m21 * mat._m31 + _m22 * mat._m32 + _m23 * mat._m33 + _m24 * mat._m34;
				result._m24 = _m21 * mat._m41 + _m22 * mat._m42 + _m23 * mat._m43 + _m24 * mat._m44;

				result._m31 = _m31 * mat._m11 + _m32 * mat._m12 + _m33 * mat._m13 + _m34 * mat._m14;
				result._m32 = _m31 * mat._m21 + _m32 * mat._m22 + _m33 * mat._m23 + _m34 * mat._m24;
				result._m33 = _m31 * mat._m31 + _m32 * mat._m32 + _m33 * mat._m33 + _m34 * mat._m34;
				result._m34 = _m31 * mat._m41 + _m32 * mat._m42 + _m33 * mat._m43 + _m34 * mat._m44;

				result._m41 = _m41 * mat._m11 + _m42 * mat._m12 + _m43 * mat._m13 + _m44 * mat._m14;
				result._m42 = _m41 * mat._m21 + _m42 * mat._m22 + _m43 * mat._m23 + _m44 * mat._m24;
				result._m43 = _m41 * mat._m31 + _m42 * mat._m32 + _m43 * mat._m33 + _m44 * mat._m34;
				result._m44 = _m41 * mat._m41 + _m42 * mat._m42 + _m43 * mat._m43 + _m44 * mat._m44;

				return result;
			}

			Matrix4x4& operator*=( const Matrix4x4& mat )
			{
				*this = *this * mat;
				return *this;
			}

			Vector4< _realType > operator*( const Vector4< _realType >& vector )const
			{
				Vector4< _realType > result;

				result.x = vector.x * _m11 + vector.y * _m12 + vector.z * _m13 + vector.w * _m14;
				result.y = vector.x * _m21 + vector.y * _m22 + vector.z * _m23 + vector.w * _m24;
				result.z = vector.x * _m31 + vector.y * _m32 + vector.z * _m33 + vector.w * _m34;
				result.w = vector.x * _m41 + vector.y * _m42 + vector.z * _m43 + vector.w * _m44;

				return result;
			}

			friend Vector4< _realType > operator*( const Vector4< _realType >& vector, const Matrix4x4& mat )
			{
				Vector4< _realType > result;

				result.x = vector.x * mat._m11 + vector.y * mat._m12 + vector.z * mat._m13 + vector.w * mat._m14;
				result.y = vector.x * mat._m21 + vector.y * mat._m22 + vector.z * mat._m23 + vector.w * mat._m24;
				result.z = vector.x * mat._m31 + vector.y * mat._m32 + vector.z * mat._m33 + vector.w * mat._m34;
				result.w = vector.x * mat._m41 + vector.y * mat._m42 + vector.z * mat._m43 + vector.w * mat._m44;

				return result;
			}

			Vector3< _realType > operator*( const Vector3< _realType >& vector )const
			{
				Vector3< _realType > result;

				result.x = vector.x * _m11 + vector.y * _m12 + vector.z * _m13 + vector.w * _m14;
				result.y = vector.x * _m21 + vector.y * _m22 + vector.z * _m23 + vector.w * _m24;
				result.z = vector.x * _m31 + vector.y * _m32 + vector.z * _m33 + vector.w * _m34;

				return result;
			}

			friend Vector3< _realType > operator*( const Vector3< _realType >& vector, const Matrix4x4& mat )
			{
				Vector3< _realType > result;

				result.x = vector.x * _m11 + vector.y * _m12 + vector.z * _m13 + vector.w * _m14;
				result.y = vector.x * _m21 + vector.y * _m22 + vector.z * _m23 + vector.w * _m24;
				result.z = vector.x * _m31 + vector.y * _m32 + vector.z * _m33 + vector.w * _m34;

				return result;
			}

			Matrix4x4 operator-( const Matrix4x4& mat )const
			{
				Matrix4x4 result;

				result._m11 = _m11 - mat._m11;result._m21 = _m21 - mat._m21;result._m31 = _m31 - mat._m31;result._m41 = _m41 - mat._m41;
				result._m12 = _m12 - mat._m12;result._m22 = _m22 - mat._m22;result._m32 = _m32 - mat._m32;result._m42 = _m42 - mat._m42;
				result._m13 = _m13 - mat._m13;result._m23 = _m23 - mat._m23;result._m33 = _m33 - mat._m33;result._m43 = _m43 - mat._m43;
				result._m14 = _m14 - mat._m14;result._m24 = _m24 - mat._m24;result._m34 = _m34 - mat._m34;result._m44 = _m44 - mat._m44;

				return result;
			}

			Matrix4x4& operator-=( const Matrix4x4& mat )
			{
				*this = *this - mat;
				return *this;
			}

			Matrix4x4 operator+( const Matrix4x4& mat )const
			{
				Matrix4x4 result;

				result._m11 = _m11 + mat._m11;result._m21 = _m21 + mat._m21;result._m31 = _m31 + mat._m31;result._m41 = _m41 + mat._m41;
				result._m12 = _m12 + mat._m12;result._m22 = _m22 + mat._m22;result._m32 = _m32 + mat._m32;result._m42 = _m42 + mat._m42;
				result._m13 = _m13 + mat._m13;result._m23 = _m23 + mat._m23;result._m33 = _m33 + mat._m33;result._m43 = _m43 + mat._m43;
				result._m14 = _m14 + mat._m14;result._m24 = _m24 + mat._m24;result._m34 = _m34 + mat._m34;result._m44 = _m44 + mat._m44;

				return result;
			}

			Matrix4x4& operator+=( const Matrix4x4& mat )
			{
				*this = *this + mat;
				return *this;
			}

			Matrix4x4 operator*( const _realType& val )const
			{
				Matrix4x4 result;

				result._m11 = val * _m11;result._m21 = val * _m21;result._m31 = val * _m31;result._m41 = val * _m41;
				result._m12 = val * _m12;result._m22 = val * _m22;result._m32 = val * _m32;result._m42 = val * _m42;
				result._m13 = val * _m13;result._m23 = val * _m23;result._m33 = val * _m33;result._m43 = val * _m43;
				result._m14 = val * _m14;result._m24 = val * _m24;result._m34 = val * _m34;result._m44 = val * _m44;
				return result;
			}

			Matrix4x4& operator*=( const _realType& val )
			{
				*this = *this * val;
				return *this;
			}

			friend Matrix4x4 operator*( const _realType& val, const Matrix4x4& mat )
			{
				Matrix4x4 result;

				result._m11 = val * mat._m11;result._m21 = val * mat._m21;result._m31 = val * mat._m31;result._m41 = val * mat._m41;
				result._m12 = val * mat._m12;result._m22 = val * mat._m22;result._m32 = val * mat._m32;result._m42 = val * mat._m42;
				result._m13 = val * mat._m13;result._m23 = val * mat._m23;result._m33 = val * mat._m33;result._m43 = val * mat._m43;
				result._m14 = val * mat._m14;result._m24 = val * mat._m24;result._m34 = val * mat._m34;result._m44 = val * mat._m44;
				return result;
			}

			friend std::ostream& operator<<( std::ostream& out, const Matrix4x4& mat )
			{
				out << "{" << static_cast< float >( mat._m11 ) << "," << static_cast< float >( mat._m21 ) << "," << static_cast< float >( mat._m31 ) << "," << static_cast< float >( mat._m41 ) << "}" << std::endl;
				out << "{" << static_cast< float >( mat._m12 ) << "," << static_cast< float >( mat._m22 ) << "," << static_cast< float >( mat._m32 ) << "," << static_cast< float >( mat._m42 ) << "}" << std::endl;
				out << "{" << static_cast< float >( mat._m13 ) << "," << static_cast< float >( mat._m23 ) << "," << static_cast< float >( mat._m33 ) << "," << static_cast< float >( mat._m43 ) << "}" << std::endl;
				out << "{" << static_cast< float >( mat._m14 ) << "," << static_cast< float >( mat._m24 ) << "," << static_cast< float >( mat._m34 ) << "," << static_cast< float >( mat._m44 ) << "}" << std::endl;

				return out;
			}

			void LoadIdentity()
			{
				_m11 = 1.0f;_m12 = 0.0f;_m13 = 0.0f;_m14 = 0.0f;
				_m21 = 0.0f;_m22 = 1.0f;_m23 = 0.0f;_m24 = 0.0f;
				_m31 = 0.0f;_m32 = 0.0f;_m33 = 1.0f;_m34 = 0.0f;
				_m41 = 0.0f;_m42 = 0.0f;_m43 = 0.0f;_m44 = 1.0f;
			}

			
		
			struct{

				_realType _m11,_m12,_m13,_m14;
				_realType _m21,_m22,_m23,_m24;
				_realType _m31,_m32,_m33,_m34;
				_realType _m41,_m42,_m43,_m44;
			};
			
	};

	//--------------------------------------------------------------------------------------------------------------------------------------
	// Martrix math functions
	// all angles are in radians
	//--------------------------------------------------------------------------------------------------------------------------------------
	template< class T >
	inline Matrix4x4< T > MakeRHProjection( T fov, T aspectRatio, T nearPlane, T farPlane )
	{
		Matrix4x4< T > result;


		T height = 1.0f / tangent( fov / 2 );
		T width  = aspectRatio / height;

		result.LoadIdentity();

		result._m11 = width;
		result._m22 = height;
		result._m33 = (nearPlane + farPlane)/(nearPlane - farPlane);
		result._m34 = -1.0f;
		result._m43 = 2 * nearPlane * farPlane / (nearPlane - farPlane);
		result._m44 = 0;

		return result;
	}

	template< class T >
	inline Matrix4x4< T > MakeRHFrustumProjection( T left,T right,T top,T bottom,T nearPlane,T farPlane )
	{
		Matrix4x4< T > result;


		result.LoadIdentity();

		T right_left = right - left;
		T top_bottom = top - bottom;
		T near_far = nearPlane - farPlane;
		T twoNear = 2 * nearPlane;

		result._m11 = twoNear / right_left;
		result._m22 = twoNear / top_bottom;
		result._m31 = (right + left)/right_left;
		result._m32 = (top + bottom)/top_bottom;
		result._m33 = (farPlane + nearPlane)/near_far;
		result._m34 = -1;
		result._m43 = (twoNear * farPlane) /near_far;
		result._m44 = 0;

		return result;
	}

	typedef enum
	{
		PLANE_LEFT,
		PLANE_RIGHT,
		PLANE_TOP,
		PLANE_BOTTOM,
		PLANE_NEAR,
		PLANE_FAR,
	}eFrustumPlane_t;

	// frustum plane extraction, opengl style
	// http://www2.ravensoft.com/users/ggribb/plane%20extraction.pdf
	template< class T >
	void ExtractFrustumPlanes( const Matrix4x4< T >& modelViewProj, Vector4< T >* planes, bool normalize )
	{
		typedef Vector4< T > vec4;
		planes[ PLANE_LEFT ] = vec4( modelViewProj[ 12 ] + modelViewProj[ 0 ],
									 modelViewProj[ 13 ] + modelViewProj[ 1 ],
									 modelViewProj[ 14 ] + modelViewProj[ 2 ],
									 modelViewProj[ 15 ] + modelViewProj[ 3 ] );

		planes[ PLANE_RIGHT ] = vec4( modelViewProj[ 12 ] - modelViewProj[ 0 ],
									  modelViewProj[ 13 ] - modelViewProj[ 1 ],
									  modelViewProj[ 14 ] - modelViewProj[ 2 ],
									  modelViewProj[ 15 ] - modelViewProj[ 3 ]);

		planes[ PLANE_TOP ] = vec4(	  modelViewProj[ 12 ] - modelViewProj[ 4 ] ,
									  modelViewProj[ 13 ] - modelViewProj[ 5 ],
									  modelViewProj[ 14 ] - modelViewProj[ 6 ],
									  modelViewProj[ 15 ] - modelViewProj[ 7 ]);

		planes[ PLANE_BOTTOM ] = vec4(modelViewProj[ 12 ] + modelViewProj[ 4 ],
									  modelViewProj[ 13 ] + modelViewProj[ 5 ],
									  modelViewProj[ 14 ] + modelViewProj[ 6 ],
									  modelViewProj[ 15 ] + modelViewProj[ 7 ]);

		planes[ PLANE_NEAR ] = vec4(  modelViewProj[ 12 ] + modelViewProj[ 8 ],
									  modelViewProj[ 13 ] + modelViewProj[ 9 ],
									  modelViewProj[ 14 ] + modelViewProj[ 10 ],
									  modelViewProj[ 15 ] + modelViewProj[ 11 ]);


		planes[ PLANE_FAR ] = vec4(  modelViewProj[ 12 ] - modelViewProj[ 8 ],
									  modelViewProj[ 13 ] - modelViewProj[ 9 ],
									  modelViewProj[ 14 ] - modelViewProj[ 10 ],
									  modelViewProj[ 15 ] - modelViewProj[ 11 ]);

		if( normalize )
		{
			Normalize( planes[ PLANE_LEFT ],planes[ PLANE_LEFT ]);
			Normalize( planes[ PLANE_RIGHT ],planes[ PLANE_RIGHT ]);
			Normalize( planes[ PLANE_TOP ],planes[ PLANE_TOP ]);
			Normalize( planes[ PLANE_BOTTOM ],planes[ PLANE_BOTTOM ]);
			Normalize( planes[ PLANE_NEAR ],planes[ PLANE_NEAR ]);
			Normalize( planes[ PLANE_FAR ],planes[ PLANE_FAR ]);
		}
	}

	template< class T >
	inline boost::uint32_t _findMaxValue( const Matrix4x4< T >& matrix, boost::uint32_t col )
	{
		boost::uint32_t row = 1;
		boost::uint32_t rowRet = 0;

		T tmpValue;
		T maxValue = matrix(0,col);

		do
		{
			tmpValue = abs( matrix(row,col) );
			if( maxValue < tmpValue )
			{
				maxValue = tmpValue;
				rowRet = row;
			}
		}while( ++row < 4 );

		BOOST_ASSERT( maxValue != 0 );

		return rowRet;
	}

	template< class T >
	inline void _SwapRows( Matrix4x4< T >& matrix, boost::uint32_t dstRow, boost::uint32_t srcRow )
	{
		std::swap( matrix( dstRow, 0 ), matrix( srcRow, 0 ) );
		std::swap( matrix( dstRow, 1 ), matrix( srcRow, 1 ) );
		std::swap( matrix( dstRow, 2 ), matrix( srcRow, 2 ) );
		std::swap( matrix( dstRow, 3 ), matrix( srcRow, 3 ) );
	}

	template< class T >
	inline void _ScaleRow( Matrix4x4< T >& matrix, boost::uint32_t row, T value )
	{
		matrix( row, 0 ) *= value;
		matrix( row, 1 ) *= value;
		matrix( row, 2 ) *= value;
		matrix( row, 3 ) *= value;

	}

	template< class T >
	inline void _ScaleRowAdd( Matrix4x4< T >& matrix, boost::uint32_t srcRow, boost::uint32_t dstRow, T value )
	{
		Vector4< T > scaledRow( matrix( srcRow, 0 ) * value,
								matrix( srcRow, 1 ) * value,
								matrix( srcRow, 2 ) * value,
								matrix( srcRow, 3 ) * value );

		matrix( dstRow, 0 ) += scaledRow.x;
		matrix( dstRow, 1 ) += scaledRow.y;
		matrix( dstRow, 2 ) += scaledRow.z;
		matrix( dstRow, 3 ) += scaledRow.w;
	}

	template< class T >
	void Inverse( const Matrix4x4< T >& matrix, Matrix4x4< T >& matrixRet )
	{
		Matrix4x4< T > identity,tmpMatrix = matrix;
		identity.LoadIdentity();

		boost::uint32_t column = 0;
		boost::uint32_t row = 0;
		T inverseValue;

		do
		{
			// find absolute max value
			row = _findMaxValue( tmpMatrix, column );

			// swap rows
			if( row != column )
			{
				_SwapRows( tmpMatrix, row, column );
				_SwapRows( identity, row, column );
			}

			inverseValue = 1.0f / tmpMatrix( column, column );

			_ScaleRow( tmpMatrix, column, inverseValue );
			_ScaleRow( identity, column, inverseValue );

			row = 0;
			do
			{
				if( row != column )
				{
					T value = -tmpMatrix( row, column );
					_ScaleRowAdd( tmpMatrix, column, row, value );
					_ScaleRowAdd( identity, column, row, value );
				}
			}while( ++row < 4 );

		}while( ++column < 4 );

		// identity is now inverse
		matrixRet = identity;
	}
}

#endif