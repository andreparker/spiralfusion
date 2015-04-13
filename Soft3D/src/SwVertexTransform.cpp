#include "../inc/SwVertexTransform.hpp"

namespace Soft3D
{
	void SwVertexTransform::Process( ElementData* dataPtr )
	{
		GetComponent()->Process( dataPtr );
	}
}
