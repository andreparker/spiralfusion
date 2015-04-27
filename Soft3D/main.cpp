#include <SDL.h>
#include "SDL_Wrapper/sdlmm.h"
#include "inc/Soft3D.hpp"
#include "inc/DefaultFragmentProgram.hpp"
#include "inc/Tri_Affine.hpp"
#include "inc/GeometryUtils.inl"
#include "inc/VertexTypes.hpp"
#include "inc/Profiler.hpp"
#include <stdlib.h>
#include <math.h>

#pragma comment(lib,"Sdlmain")
#pragma comment(lib,"sdl")

using namespace Soft3D;

const boost::uint32_t screen_width = 640;
const boost::uint32_t screen_height = 480;

// a fragment program to use
DefaultFragmentProgram fragProg;

// event handler for handling window events
class eventHandler : public SDLmm::EventHandler
{
    public:

        virtual bool HandleQuitEvent()
        {
            return true;
        }
};

// Triangle Raster Testing
static void TestAffineDraw( SurfaceInfo< boost::uint32_t, boost::uint32_t >& info  )
{
	PROFILE_FUNCTION();
	TriangleVertices< GouradVertexType >  vertices;
	GouradVertexType v0( static_cast< Real >( screen_width/4 ), 0, 0, 1,
                        255.0f, 0.0f, 0.0f, 255.0f),
						v1( static_cast< Real >( screen_width ), static_cast< Real >( screen_height/2 ), 0, 1,
                            0.0f, 255.0f, 0.0f, 255.0f),
						v2( 0, static_cast< Real >( screen_height ), 0, 1,
						    0.0f, 0.0f, 255.0f, 255.0f);

	// sort vertices into a vertex list
	VertexSort( v0, v1, v2, vertices );

	DrawTriangleAffine< GouradVertexType, boost::uint32_t, boost::uint32_t, Real >( info, vertices, fragProg );
}

int main( int argc, char** argv )
{
	PROFILE_FUNCTION();
	Soft3DMgrHdl mgrHandle;


	// allocate a vertex buffer of 3 verts
	VertexBuffer vertexBuffer0( VBFLAG_4C_COLOR | VBFLAG_4C_UV1 , 3 );
	VertexBuffer vertexBuffer1( vertexBuffer0 );
	VertexBuffer vertexBuffer2( vertexBuffer1 );
	VertexBuffer vertexBuffer3( vertexBuffer2 );

	// 8 bit texture
	Texture texture8x8( 8, 8, 8 );

	fragProg.SetVector( FragmentProgram::FATTR_COLOR, FragmentProgram::vec4( 255.0f, 0, 0, 255.0f ) );

	if( SDLmm::Init( SDL_INIT_VIDEO ))
	{
		SDLmm::Display& screen = SDLmm::Display::GetDisplay();
		SurfaceInfo< boost::uint32_t, boost::uint32_t > displayInfo;

		displayInfo.width = screen_width;
		displayInfo.height = screen_height;

		if( screen.SetVideoMode( screen_width, screen_height, 32, SDL_HWSURFACE ) )
		{
			while( true )
			{
				// get the events
				SDLmm::Event::PumpEvents();

				Uint8* keyStatePtr = SDLmm::Event::GetKeyState();

            if( keyStatePtr[ SDLK_ESCAPE ]  )
					break;

				// fill to solid blue
				screen.Fill( 0, 0, 255 );

				if( screen.Lock() )
				{
					displayInfo.SurfaceDataPtr = reinterpret_cast< boost::uint32_t* >( screen.pixels() );
					displayInfo.DepthSurfaceDataPtr = NULL;


                    static Real t = 0.5f;
                    Real c = cos(t * 180 / 3.14) * 0.1f;
                    Real s = sin(t * 180 / 3.14) * 0.1f;
                    Real w = tan(t * 180 / 3.14) * 0.1f;

                    t += 1.01f;
                    fragProg.SetVector(FragmentProgram::FATTR_REG0, FragmentProgram::vec4(c,s,t,w));
					TestAffineDraw( displayInfo );
					screen.Unlock();
				}

				screen.Flip();
			}

		}

		// shut down the 3d manager
		mgrHandle->Shutdown();

		SDLmm::Quit();
	}

   PROFILE_WRITE_DATA();
	return 0;
}
