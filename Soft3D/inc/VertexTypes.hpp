#ifndef VERTEXTYPES_HPP
#define VERTEXTYPES_HPP

#include "Setup.hpp"
#include "Vector4.inl"

namespace Soft3D
{
	// standard fill
	struct DefaultVertexType
	{
		DefaultVertexType(){}
		DefaultVertexType( Real _x, Real _y, Real _z, Real _w ):
		x(_x),y(_y),z(_z),w(_w ){}

		Real x,y,z,w;
	};

	// textured triangle
	struct Tex1VertexType
	{
		Real x,y,z,w;
		Real u,v,n,t;
	};

	// gourad shaded Triangle
	struct GouradVertexType
	{
        GouradVertexType(){}
        GouradVertexType( Real _x, Real _y, Real _z, Real _w,
         Real _r, Real _g, Real _b, Real _a):
         x(_x), y(_y), z(_z), w(_w), r(_r), g(_g), b(_b), a(_a){}

		Real x,y,z,w;
		Real r,g,b,a;
	};
}

#endif
