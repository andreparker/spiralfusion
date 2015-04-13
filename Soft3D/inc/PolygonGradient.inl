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

    //==================================================================================================
    template< class _Real >
	class PolygonGradient< _Real, GouradVertexType >
	{
		protected:
			_Real m_wGradient;

		public:

			struct GradientData
			{
				_Real w;
			};

			PolygonGradient(): m_wGradient(0){}

			PolygonGradient( const GouradVertexType& v0, const GouradVertexType& v1, const GouradVertexType& v2 )
			{
				SetupGradients( v0, v1, v2 );
			}

			GradientData GetGradientData()const
			{
				GradientData data;
				data.w = m_wGradient;

				return data;
			}

			void SetupGradients( const GouradVertexType& v0, const GouradVertexType& v1, const GouradVertexType& v2 )
			{
				// calculate texture u,v,n,t,w gradients based of y
				MathUtil::Vector3< _Real > c0( v0.x, v0.y, 1.0f ), c1( v1.x, v1.y, 1.0f ), c2( v2.x, v2.y, 1.0f );
				// inverse w for perspective correction
				MathUtil::Vector3< _Real > w0( v0.r, v0.g, v0.b ), w1( v1.r, v1.g, v1.b ), w2( v2.r, v2.g, v2.b );

				// calculate determinants
				_Real ydet = TriangleGradient( c0, c1, c2 );
				_Real wdet = TriangleGradient( w0, w1, w2 );

				// divide by y to get gradient
				m_wGradient = wdet / ydet;
			}
	};
	//===========================================================================================================
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
				MathUtil::Vector2< _Real > _c0( v0.x, v0.y ), _c1( v1.x, v1.y ), _c2( v2.x, v2.y );
				MathUtil::Vector2< _Real > _u0( v0.u, v0.y ), _u1( v1.u, v1.y ), _u2( v2.u, v2.y );
				MathUtil::Vector2< _Real > _v0( v0.v, v0.y ), _v1( v1.v, v1.y ), _v2( v2.v, v2.y );
				MathUtil::Vector2< _Real > _n0( v0.n, v0.y ), _n1( v1.n, v1.y ), _n2( v2.n, v2.y );
				MathUtil::Vector2< _Real > _t0( v0.t, v0.y ), _t1( v1.t, v1.y ), _t2( v2.t, v2.y );

				// inverse w for perspective correction
				MathUtil::Vector2< _Real > _w0( 1/v0.w, v0.y ), _w1( 1/v1.w, v1.y ), _w2( 1/v2.w, v2.y );

				// calculate determinants
				_Real inv_ydet = 1 / TriangleGradient( _c0, _c1, _c2 );
				_Real udet = TriangleGradient( _u0, _u1, _u2 );
				_Real vdet = TriangleGradient( _v0, _v1, _v2 );
				_Real ndet = TriangleGradient( _n0, _n1, _n2 );
				_Real tdet = TriangleGradient( _t0, _t1, _t2 );
				_Real wdet = TriangleGradient( _w0, _w1, _w2 );

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
