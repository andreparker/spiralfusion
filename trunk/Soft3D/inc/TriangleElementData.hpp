#ifndef TRIANGLEELEMENTDATA_HPP
#define TRIANGLEELEMENTDATA_HPP

#include <vector>
#include "Setup.hpp"
#include "ElementData.hpp"
#include "Vector4.inl"

class TriangleElementData : 
	public ElementData
{
	public:
		void Process( ElementProcessComponent* elementComponentPtr );


	protected:
		std::vector< Soft3D::Real > m_elementVector;
		boost::uint32_t	m_elementSizeCount;		// 4 bytes per element

		std::vector< boost::uint32_t >	m_indexVector;
		
};

#endif