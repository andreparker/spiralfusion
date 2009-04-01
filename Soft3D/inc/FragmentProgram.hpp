#ifndef FRAGMENTPROGRAM_HPP
#define FRAGMENTPROGRAM_HPP

#include "Setup.hpp"
#include "Matrix.inl"
#include "Vector4.inl"
#include "Texture.hpp"
#include <boost/cstdint.hpp>

namespace Soft3D
{
	struct RGBAColor
	{
		RGBAColor():color(0){}

		RGBAColor( 
					boost::uint8_t _r,
					boost::uint8_t _g,
					boost::uint8_t _b,
					boost::uint8_t _a ):
		r(_r),g(_g),b(_b),a(_a){}

		RGBAColor( boost::uint32_t _clr ):
		color(_clr){}

		static boost::uint8_t Extract_Red( boost::uint32_t clr )
		{
			return static_cast< boost::uint8_t >( (clr >> 16) & 0xff );
		}

		static boost::uint8_t Extract_Green( boost::uint32_t clr )
		{
			return static_cast< boost::uint8_t >( (clr >> 8) & 0xff );
		}

		static boost::uint8_t Extract_Blue( boost::uint32_t clr )
		{
			return static_cast< boost::uint8_t >( clr & 0xff );
		}

		static boost::uint8_t Extract_Alpha( boost::uint32_t clr )
		{
			return static_cast< boost::uint8_t >( (clr >> 24) );
		}

		union{
			boost::uint32_t color;
			struct{
				boost::uint8_t b;
				boost::uint8_t g;
				boost::uint8_t r;
				boost::uint8_t a;
			};
		};
	};

	class FragmentProgram
	{
		public:
			typedef MathUtil::Vector4< Real > vec4;
			typedef MathUtil::Matrix4x4< Real > Mat4;

		protected:
			FragmentProgram();

			vec4	m_Vectors[ max_register_count ];	// used for uv's and colors
			Mat4	m_Matrices[ max_register_count ];  // used for custom programs
			Texture* m_Textures[ max_texture_count ]; // used for color sampling

			vec4	GetVector( boost::uint32_t index )const{ return m_Vectors[ index ]; }
			Mat4	GetMatrix( boost::uint32_t index )const{ return m_Matrices[ index ]; }

			// get a color from a texture at u,v position
			// index is the current texture index to sample from
			RGBAColor GetSample2D( boost::uint32_t index, Real u, Real v );
		public:

			// attributes assigned to vector indices
			enum{
				FATTR_UV1,
				FATTR_UV2,
				FATTR_UV3,
				FATTR_UV4,
				FATTR_COLOR,
			};

			// used to return a sample
			virtual RGBAColor Sample()
			{
				vec4 color = GetVector( FATTR_COLOR );
				return RGBAColor( 
					static_cast< boost::uint8_t >( color.x ),
					static_cast< boost::uint8_t >( color.y ),
					static_cast< boost::uint8_t >( color.z ),
					static_cast< boost::uint8_t >( color.w ));

			}


			void SetVector( boost::uint32_t index, const vec4& vec ){ m_Vectors[ index ] = vec; }
			void SetMatrice( boost::uint32_t index, const Mat4& mat ){ m_Matrices[ index ] = mat; }
			void SetTexture( boost::uint32_t index, Texture* texturePtr ){ m_Textures[ index ] = texturePtr; }
	};
}

#endif