#ifndef POLYGONGRADIENT_INL
#define POLYGONGRADIENT_INL

#include "Setup.hpp"
#include "VertexTypes.hpp"
#include "GeometryMath.hpp"

#include "VertexTypes.hpp"

namespace Soft3D
{
	template< class _Real, class VertexType >
	class PolygonGradient
	{
		protected:
			_Real m_wGradient;
		
		public:

			struct GradientData
			{
				_Real w;
			};

			PolygonGradient(): m_wGradient(0){}

			PolygonGradient( const VertexType& v0, const VertexType& v1, const VertexType& v2 )
			{
				SetupGradients( v0, v1, v2 );
			}

			GradientData GetGradientData()const
			{
				GradientData data;
				data.w = m_wGradient;
				
				return data;
			}

			void SetupGradients( const VertexType& v0, const VertexType& v1, const VertexType& v2 )
			{
				// calculate texture u,v,n,t,w gradients based of y
				MathUtil::Vector2< _Real > c0( v0.x, v0.y ), c1( v1.x, v1.y ), c2( v2.x, v2.y );
				// inverse w for perspective correction
				MathUtil::Vector2< _Real > w0( 1/v0.w, v0.y ), w1( 1/v1.w, v1.y ), w2( 1/v2.w, v2.y );

				// calculate determinants
				_Real ydet = TriangleGradient( c0, c1, c2 );
				_Real wdet = TriangleGradient( w0, w1, w2 );

				// divide by y to get gradient
				m_wGradient = wdet / ydet;
			}
	};

	template< class _Real >
	class PolygonGradient< _Real, Tex1VertexType >
	{
		protected:
			_Real m_uGradient;
			_Real m_vGradient;
			_Real m_nGradient;
			_Real m_tGradient;
			_Real m_wGradient;
		
		public:

			struct GradientData
			{
				_Real u,v,n,t,w;
			};

			PolygonGradient(): m_uGradient(0),m_vGradient(0),
				m_nGradient(0),m_tGradient(0),m_wGradient(0){}

			PolygonGradient( const Tex1VertexType& v0, const Tex1VertexType& v1, const Tex1VertexType& v2 )
			{
				SetupGradients( v0, v1, v2 );
			}

			GradientData GetGradientData()const
			{
				GradientData data;
				data.u = m_uGradient;
				data.v = m_vGradient;
				data.n = m_nGradient;
				data.t = m_tGradient;
				data.w = m_wGradient;
				

				return data;
			}

			void SetupGradients( const Tex1VertexType& v0, const Tex1VertexType& v1, const Tex1VertexType& v2 )
			{
				// calculate texture u,v,n,t,w gradients based of y
				MathUtil::Vector2< _Real > c0( v0.x, v0.y ), c1( v1.x, v1.y ), c2( v2.x, v2.y );
				MathUtil::Vector2< _Real > u0( v0.u, v0.y ), u1( v1.u, v1.y ), u2( v2.u, v2.y );
				MathUtil::Vector2< _Real > v0( v0.v, v0.y ), v1( v1.v, v1.y ), v2( v2.v, v2.y );
				MathUtil::Vector2< _Real > n0( v0.n, v0.y ), n1( v1.n, v1.y ), n2( v2.n, v2.y );
				MathUtil::Vector2< _Real > t0( v0.t, v0.y ), t1( v1.t, v1.y ), t2( v2.t, v2.y );

				// inverse w for perspective correction
				MathUtil::Vector2< _Real > w0( 1/v0.w, v0.y ), w1( 1/v1.w, v1.y ), w2( 1/v2.w, v2.y );

				// calculate determinants
				_Real inv_ydet = 1 / TriangleGradient( c0, c1, c2 );
				_Real udet = TriangleGradient( u0, u1, u2 );
				_Real vdet = TriangleGradient( v0, v1, v2 );
				_Real ndet = TriangleGradient( n0, n1, n2 );
				_Real tdet = TriangleGradient( t0, t1, t2 );
				_Real wdet = TriangleGradient( w0, w1, w2 );

				// divide by y to get gradient
				m_uGradient = udet * inv_ydet;
				m_vGradient = vdet * inv_ydet;
				m_nGradient = ndet * inv_ydet;
				m_tGradient = tdet * inv_ydet;
				m_wGradient = wdet * inv_ydet;
			}
	};
}

#endif