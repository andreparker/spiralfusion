#ifndef POLYGONEDGE_INL
#define POLYGONEDGE_INL

#include "Setup.hpp"
#include "VertexTypes.hpp"
#include "FragmentProgram.hpp"

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

            PolygonEdge(const GouradVertexType& v1, const GouradVertexType& v0)
            {
                SetupInterpolants(v1,v0);
            }

            EdgeData GetEdgeData()const
            {
                EdgeData data;

                data.x = m_x;
                data.w = m_w;
                data.r = m_r;
                data.g = m_g;
                data.b = m_b;
                data.a = m_a;

                return data;
            }

            void Step()
            {
                m_x += m_xInterpolant;
                m_w += m_wInterpolant;
                m_r += m_rInterpolant;
                m_g += m_gInterpolant;
                m_b += m_bInterpolant;
                m_a += m_aInterpolant;
            }

            boost::uint32_t GetHeight()const{ return m_height; }
			void SubtractHeight( boost::uint32_t value ){ m_height -= value; }

            void SetupInterpolants(const GouradVertexType& v1, const GouradVertexType& v0)
            {

                _Real delta_y = v1.y - v0.y;
                if( delta_y > 0 )
                {
                    _Real inv_v0_w = 1 / v0.w;
                    _Real delta_w = 1 / v1.w - inv_v0_w;

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

                    m_x = v0.x;
                    m_w = inv_v0_w;
                    m_r = v0.r;
                    m_g = v0.g;
                    m_b = v0.b;
                    m_a = v0.a;
                }


                m_height = static_cast< boost::uint32_t >(delta_y);


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

	template< class FrameBufferType, class _Real, class _PolygonEdgeType >
	class InterpolateScanLine
	{
        public:
            InterpolateScanLine(const _PolygonEdgeType& edge0, const _PolygonEdgeType& edge1, FragmentProgram& program, FrameBufferType* scanLine)
            {
                typename _PolygonEdgeType::EdgeData edge_data0 = edge0.GetEdgeData();
                typename _PolygonEdgeType::EdgeData edge_data1 = edge1.GetEdgeData();

                boost::int32_t scanLineSize = static_cast< boost::int32_t >(FixedPoint::Ceil(edge_data1.x - edge_data0.x)) + 1;
                FrameBufferType pixel = program.Sample().Color();

                while( scanLineSize-- > 0)
                {
                    program.Execute();
                    *scanLine = pixel;
                    ++scanLine;
                }
            }
	};

	template< class FrameBufferType, class _Real >
	class InterpolateScanLine< FrameBufferType, _Real, PolygonEdge< _Real, Tex1VertexType > >
	{
        public:
            InterpolateScanLine(const PolygonEdge< _Real, Tex1VertexType >& edge0, const PolygonEdge< _Real, Tex1VertexType >& edge1, FragmentProgram& program, FrameBufferType* scanLine)
            {
                typename PolygonEdge< _Real, Tex1VertexType >::EdgeData edge_data0 = edge0.GetEdgeData();
                typename PolygonEdge< _Real, Tex1VertexType >::EdgeData edge_data1 = edge1.GetEdgeData();

                boost::int32_t scanLineSize = static_cast< boost::int32_t >(FixedPoint::Ceil(edge_data1.x - edge_data0.x)) + 1;

                _Real inv_scan = 1.0f / scanLineSize;

                _Real y_Interpolant = inv_scan * (edge_data1.y - edge_data0.y);
                _Real w_Interpolant = inv_scan * (edge_data1.w - edge_data0.w);
                _Real u_Interpolant = inv_scan * (edge_data1.u - edge_data0.u);
                _Real v_Interpolant = inv_scan * (edge_data1.v - edge_data0.v);
                _Real n_Interpolant = inv_scan * (edge_data1.n - edge_data0.n);
                _Real t_Interpolant = inv_scan * (edge_data1.t - edge_data0.t);

                _Real u = edge_data0.u, v = edge_data0.v, n = edge_data0.n, t = edge_data0.t, w = edge_data0.w;

                while( scanLineSize-- > 0)
                {
                    program.SetVector(FragmentProgram::FATTR_UV1, FragmentProgram::vec4(u * w,v * w,n * w,t * w));
                    program.Execute();
                    FrameBufferType pixel = program.Sample().Color();

                    u += u_Interpolant;
                    v += v_Interpolant;
                    n += n_Interpolant;
                    t += t_Interpolant;
                    w += w_Interpolant;

                    *scanLine = pixel;
                    ++scanLine;
                }
            }
	};

	template< class FrameBufferType, class _Real >
	class InterpolateScanLine< FrameBufferType, _Real, PolygonEdge< _Real, GouradVertexType > >
	{
        public:
            InterpolateScanLine(const PolygonEdge< _Real, GouradVertexType >& edge0, const PolygonEdge< _Real, GouradVertexType >& edge1,
            FragmentProgram& program, FrameBufferType* scanLine)
            {
                typename PolygonEdge< _Real, GouradVertexType >::EdgeData edge_data0 = edge0.GetEdgeData();
                typename PolygonEdge< _Real, GouradVertexType >::EdgeData edge_data1 = edge1.GetEdgeData();

                boost::int32_t scanLineSize = static_cast< boost::int32_t >(FixedPoint::Ceil(edge_data1.x - edge_data0.x)) + 1;
                _Real inv_scan = 1.0f / scanLineSize;

                _Real r_Interp = inv_scan * (edge_data1.r - edge_data0.r);
                _Real g_Interp = inv_scan * (edge_data1.g - edge_data0.g);
                _Real b_Interp = inv_scan * (edge_data1.b - edge_data0.b);
                _Real a_Interp = inv_scan * (edge_data1.a - edge_data0.a);
                _Real w_Interp = inv_scan * (edge_data1.w - edge_data0.w);

                _Real r = edge_data0.r, g = edge_data0.g, b = edge_data0.b, a = edge_data0.a, w = edge_data0.w;

                while( scanLineSize-- > 0)
                {
                    program.SetVector(FragmentProgram::FATTR_COLOR, FragmentProgram::vec4(r * w,g * w,b * w,a * w));

                    program.Execute();
                    FrameBufferType pixel = program.Sample().Color();
                    *scanLine = pixel;

                    r += r_Interp;
                    g += g_Interp;
                    b += b_Interp;
                    a += a_Interp;
                    w += w_Interp;

                    ++scanLine;
                }
            }
	};

	template< class FrameBufferType, class _Real >
	class InterpolateScanLine< FrameBufferType, _Real, PolygonEdge< _Real, DefaultVertexType > >
	{
        public:
            InterpolateScanLine(const PolygonEdge< _Real, DefaultVertexType >& edge0, const PolygonEdge< _Real, DefaultVertexType >& edge1,
            FragmentProgram& program, FrameBufferType* scanLine)
            {
                typename PolygonEdge< _Real, DefaultVertexType >::EdgeData edge_data0 = edge0.GetEdgeData();
                typename PolygonEdge< _Real, DefaultVertexType >::EdgeData edge_data1 = edge1.GetEdgeData();

                boost::int32_t scanLineSize = static_cast< boost::int32_t >(FixedPoint::Ceil(edge_data1.x - edge_data0.x)) + 1;
                FrameBufferType pixel = program.Sample().Color();

                while( scanLineSize-- > 0)
                {
                    program.Execute();
                    *scanLine = pixel;
                    ++scanLine;
                }
            }
	};
}

#endif
