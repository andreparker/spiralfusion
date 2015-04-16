#include <boost/foreach.hpp>
#include "../inc/FragmentProgram.hpp"


namespace Soft3D
{
	FragmentProgram::FragmentProgram()
	{
		BOOST_FOREACH( Mat4& matrix, m_Matrices )
		{
			matrix.LoadIdentity();
		}
	}

	RGBAColor FragmentProgram::GetSample2D( boost::uint32_t index, Real u, Real v )
	{
        Texture* texture = m_Textures[index];

        if(texture != nullptr)
        {
            boost::uint32_t width,height;

            width = texture->getWidth();
            height = texture->getHeight();

            boost::uint32_t pixel_x = FixedPoint::Ceil(u * width);
            boost::uint32_t pixel_y = FixedPoint::Ceil(v * height);

            boost::uint8_t* pixelBuffer;

            if(texture->lockBuffer(pixelBuffer))
            {
                boost::uint32_t offset = pixel_x * (width * texture->getBytes()) + pixel_y;
                RGBAColor color(pixelBuffer[offset+2],pixelBuffer[offset+1],pixelBuffer[offset],pixelBuffer[offset+3]);
                texture->unlockBuffer();
                return color;
            }
        }

        return RGBAColor(0);
	}
}
