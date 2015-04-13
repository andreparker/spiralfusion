#ifndef POLYGONEDGE_INL
#define POLYGONEDGE_INL

#include "Setup.hpp"
#include "VertexTypes.hpp"

namespace Soft3D
{


	template< class _Real, class VertexType >
	class PolygonEdge
	{
		protected:
			// interpolant and x coordinate
			_Real m_xInterpolant;
			_Real m_wInterpolant;
			_Real m_x;
			_Real m_w;

			boost::uint32_t m_height;
		public:

			// edge values
			struct EdgeData
			{
				_Real x;
				_Real w;
			};

			PolygonEdge():m_xInterpolant(0),m_x(0),m_w(0),m_height(0){}
			PolygonEdge( const VertexType& v1, const VertexType& v0 )
			{
				SetupInterpolants( v1, v0 );
			}

			EdgeData GetEdgeData()const
			{
				EdgeData data;
				data.w = m_w;
				data.x = m_x;
				return data;
			}

			void Step()
			{
				m_x += m_xInterpolant;
				m_w += m_wInterpolant;
			}

			boost::uint32_t GetHeight()const{ return m_height; }
			void SubtractHeight( boost::uint32_t value ){ m_height -= value; }

			void SetupInterpolants( const VertexType& v1, const VertexType& v0 )
			{
				_Real delta_y = v1.y - v0.y;

				if( delta_y > 0 )
				{
					_Real v0_inv_w = 1 / v0.w;

					_Real delta_x = v1.x - v0.x;
					_Real delta_w = 1 / v1.w - v0_inv_w;

					_Real inv_delta_y = 1 / delta_y;

					m_xInterpolant = delta_x * inv_delta_y;
					m_wInterpolant = delta_w * inv_delta_y;

					m_x = v0.x;
					m_w = v0_inv_w;
				}

				m_height = static_cast< boost::uint32_t >( delta_y );

			}
	};


    template< class _Real >
    class PolygonEdge< _Real, GouradVertexType >
    {
        protected:

            _Real m_xInterpolant;
            _Real m_wInterpolant;
            _Real m_rInterpolant;
            _Real m_gInterpolant;
            _Real m_bInterpolant;
            _Real m_aInterpolant;

            _Real m_x;
            _Real m_w;
            _Real m_r;
            _Real m_g;
            _Real m_b;
            _Real m_a;

            boost::uint32_t m_height;

        public:

            struct EdgeData
            {
                _Real x,w,r,g,b,a;
            };

            PolygonEdge(): m_xInterpolant(0),
            m_wInterpolant(0), m_rInterpolant(0), m_gInterpolant(0), m_bInterpolant(0), m_aInterpolant(0),
            m_x(0), m_w(0), m_r(0), m_g(0), m_b(0), m_a(0), m_height(0){}

            PolygonEdge(const GouradVertexType& v0, const GouradVertexType& v1)
            {
                SetupInterpolants(v0,v1);
            }

            EdgeData GetEdgeData()const
            {
                EdgeData data;

                data.x = m_x;
                data.w = m_w;
                data.r = m_r;
                data.g = m_g;
                data.b = m_b;

                return data;
            }

            void Step()
            {
                m_x += m_xInterpolant;
                m_w += m_wInterpolant;
                m_r += m_rInterpolant;
                m_g += m_gInterpolant;
                m_b += m_bInterpolant;
            }

            boost::uint32_t GetHeight()const{ return m_height; }
			void SubtractHeight( boost::uint32_t value ){ m_height -= value; }

            void SetupInterpolants(const GouradVertexType& v0, const GouradVertexType& v1)
            {
                _Real inv_v0_w = 1 / v0.w;
                _Real delta_w = 1 / v1.w - inv_v0_w;
                _Real delta_y = v1.y - v0.y;
                _Real delta_x = v1.x - v0.x;
                _Real delta_r = v1.r - v0.r;
                _Real delta_g = v1.g - v0.g;
                _Real delta_b = v1.b - v0.b;
                _Real delta_a = v1.a - v0.a;

                _Real inv_delta_y = 1 / delta_y;

                m_xInterpolant = delta_x * inv_delta_y;
                m_wInterpolant = delta_w * inv_delta_y;
                m_rInterpolant = delta_r * inv_delta_y;
                m_gInterpolant = delta_g * inv_delta_y;
                m_bInterpolant = delta_b * inv_delta_y;
                m_aInterpolant = delta_a * inv_delta_y;

                m_height = static_cast< boost::uint32_t >(delta_y);

                m_x = v0.x;
                m_w = inv_v0_w;
                m_r = v0.r;
                m_g = v0.g;
                m_b = v0.b;
                m_a = v0.a;
            }
    };

	template< class _Real >
	class PolygonEdge< _Real, Tex1VertexType >
	{
		protected:

			_Real m_xInterpolant;
			_Real m_wInterpolant;
			_Real m_uInterpolant;
			_Real m_vInterpolant;
			_Real m_nInterpolant;
			_Real m_tInterpolant;

			_Real m_x;
			_Real m_w;
			_Real m_u;
			_Real m_v;
			_Real m_n;
			_Real m_t;

			boost::uint32_t m_height;
		public:

			// edge values
			struct EdgeData
			{
				_Real x,w,u,v,n,t;
			};

			PolygonEdge():m_xInterpolant(0),
				m_x(0),m_u(0),m_v(0),m_n(0),m_t(0),m_w(0),m_wInterpolant(0),m_uInterpolant(0),
				m_vInterpolant(0),m_nInterpolant(0),m_tInterpolant(0),m_height(0){}

			PolygonEdge( const Tex1VertexType& v1, const Tex1VertexType& v0 )
			{
				SetupInterpolants( v1, v0 );
			}

			EdgeData GetEdgeData()const
			{
				EdgeData data;

				data.w = m_w;
				data.x = m_x;
				data.u = m_u;
				data.v = m_v;
				data.n = m_n;
				data.t = m_t;

				return data;
			}

			void Step()
			{
				m_x += m_xInterpolant;
				m_w += m_wInterpolant;
				m_u += m_uInterpolant;
				m_v += m_vInterpolant;
				m_n += m_nInterpolant;
				m_t += m_tInterpolant;
			}

			boost::uint32_t GetHeight()const{ return m_height; }
			void SubtractHeight( boost::uint32_t value ){ m_height -= value; }

			void SetupInterpolants( const Tex1VertexType& v1, const Tex1VertexType& v0 )
			{
				_Real v0_inv_w = 1 / v0.w;
				_Real delta_w = 1 / v1.w - v0_inv_w;
				_Real delta_y = v1.y - v0.y;
				_Real delta_x = v1.x - v0.x;
				_Real delta_u = v1.u - v0.u;
				_Real delta_v = v1.v - v0.v;
				_Real delta_n = v1.n - v0.n;
				_Real delta_t = v1.t - v0.t;

				_Real inv_delta_y = 1 / delta_y;

				m_xInterpolant = delta_x * inv_delta_y;
				m_uInterpolant = delta_u * inv_delta_y;
				m_vInterpolant = delta_v * inv_delta_y;
				m_nInterpolant = delta_n * inv_delta_y;
				m_tInterpolant = delta_t * inv_delta_y;
				m_wInterpolant = delta_w * inv_delta_y;

				m_height = static_cast< boost::uint32_t >( delta_y );
				m_x = v0.x;
				m_w = v0_inv_w;
				m_u = v0.u;
				m_v = v0.v;
				m_n = v0.n;
				m_t = v0.t;
			}
	};
}

#endif
