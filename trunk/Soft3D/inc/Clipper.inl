#ifndef CLIPPER_INL
#define CLIPPER_INL


#include "Vector3.inl"
#include "Vector4.inl"
#include "GeometryMath.hpp"


namespace Soft3D
{
	template< typename _real, typename VertexType = DefaultVertexType >
	class VertexClipper
	{
		public:
			typedef MathUtil::Vector4< _real > vec4;
			typedef MathUtil::Vector3< _real > vec3;

			VertexClipper( const vec4& plane ):m_plane( plane ){}

			VertexType Clip( const VertexType& v1, const VertexType& v0 )const
			{
				_real ratio = InitClip( v1, v0 );
				return VertexType( 
								lerp( v1.x, v0.x, ratio ),
								lerp( v1.y, v0.y, ratio ),
								lerp( v1.z, v0.z, ratio ),
								v0.w );
			}

		protected:
			inline _real InitClip( const VertexType& v1, const VertexType& v0 )
			{
				vec3 c0( v0.x, v0.y, v0.z ), c1( v1.x, v1.y, v1.z );
				return DistanceRatio( c1, c0, m_plane );`
			}

			vec4 m_plane;
	};


	template< typename _real >
	class VertexClipper< Tex1VertexType >
	{
		public:
			typedef MathUtil::Vector4< _real > vec4;
			typedef MathUtil::Vector3< _real > vec3;

			VertexClipper( const vec4& plane ):m_plane( plane ){}

			VertexType Clip( const Tex1VertexType& v1, const Tex1VertexType& v0 )const
			{
				Tex1VertexType clipVert;
				_real ratio = InitClip( v1, v0 );

				clipVert.w = v0.w;
				clipVert.x = lerp( v1.x, v0.x, ratio );
				clipVert.y = lerp( v1.y, v0.y, ratio );
				clipVert.z = lerp( v1.z, v0.z, ratio );
				clipVert.t = lerp( v1.t, v0.t, ratio );
				clipVert.n = lerp( v1.n, v0.n, ratio );
				clipVert.u = lerp( v1.u, v0.u, ratio );
				
				return clipVert;
			}

		protected:
			inline _real InitClip( const Tex1VertexType& v1, const Tex1VertexType& v0 )
			{
				vec3 c0( v0.x, v0.y, v0.z ), c1( v1.x, v1.y, v1.z );
				return DistanceRatio( c1, c0, m_plane );`
			}

			vec4 m_plane;
	};

	template< typename _real >
	class VertexClipper< GouradVertexType >
	{
		public:
			typedef MathUtil::Vector4< _real > vec4;
			typedef MathUtil::Vector3< _real > vec3;

			VertexClipper( const vec4& plane ):m_plane( plane ){}

			VertexType Clip( const GouradVertexType& v1, const GouradVertexType& v0 )const
			{
				GouradVertexType clipVert;
				_real ratio = InitClip( v1, v0 );

				clipVert.w = v0.w;
				clipVert.x = lerp( v1.x, v0.x, ratio );
				clipVert.y = lerp( v1.y, v0.y, ratio );
				clipVert.z = lerp( v1.z, v0.z, ratio );
				clipVert.a = lerp( v1.a, v0.a, ratio );
				clipVert.r = lerp( v1.r, v0.r, ratio );
				clipVert.g = lerp( v1.g, v0.g, ratio );
				clipVert.b = lerp( v1.b, v0.b, ratio );
				
				return clipVert;
			}

		protected:
			inline _real InitClip( const GouradVertexType& v1, const GouradVertexType& v0 )
			{
				vec3 c0( v0.x, v0.y, v0.z ), c1( v1.x, v1.y, v1.z );
				return DistanceRatio( c1, c0, m_plane );`
			}

			vec4 m_plane;
	};
}

#endif