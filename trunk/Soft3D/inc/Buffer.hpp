#ifndef BUFFER_HPP
#define BUFFER_HPP


#include <boost/cstdint.hpp>

namespace Soft3D
{
	//=============================================
	// generic buffer base class

	template< class T >
	class Buffer
	{
		typedef boost::uint32_t u32;
		typedef boost::int32_t s32;

		protected:
			Buffer():
				 m_bufferPtr( NULL ),
				 m_isRef( false ){}

			Buffer( T* refPtr, u32 width, u32 height ):
			m_isRef( true ), m_width( width ), m_height( height ),
				m_bufferPtr( refPtr )
			{}

			Buffer( u32 width, u32 height ):
			m_isRef( false ), m_width( width ), m_height( height ),
				m_bufferPtr( new T[ m_width * m_height ] )
			{}

			virtual ~Buffer()
			{
				if( m_isRef == false &&
					m_bufferPtr != NULL )
				{
					delete [] m_bufferPtr;
					m_bufferPtr = NULL;
				}
			}

		protected:
			T* m_bufferPtr;
			u32 m_width, m_height;
			bool m_isRef;

			void _setWidth( u32 w ){ m_width = w; }
			void _setHeight( u32 h ){ m_height = h; }
			void _setBufferPtr( T* dataPtr ){ m_bufferPtr = dataPtr; }
			void _setRef( bool ref ){ m_isRef = ref; }
		public:

			u32 getSize()const{ return m_width * m_height; }
			u32 getSizeBytes()const{ return sizeof( T ) * getSize(); }
			u32 getWidth()const{ return m_width; }
			u32 getHeight()const{ return m_height; }
			u32 getBufferBits()const{ return sizeof( T ) << 3; }

			virtual bool lockBuffer( T*& retBufferPtr )const { retBufferPtr = m_bufferPtr; return true; }
			virtual void unlockBuffer()const {}
	};
}

#endif