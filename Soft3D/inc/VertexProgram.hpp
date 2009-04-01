#ifndef VERTEXPROGRAM_HPP
#define VERTEXPROGRAM_HPP

#include "Setup.hpp"
#include "VertexBuffer.hpp"
#include "Matrix.inl"
#include "Vector4.inl"



namespace Soft3D
{

	class VertexProgram
	{
		protected:
			// class must be derived!
			VertexProgram();
			VertexProgram( const VertexProgram& prog );
			VertexProgram( VertexBuffer& vertexInput, boost::uint32_t vertexCount );

			typedef MathUtil::Matrix4x4< Real > Mat4;
			typedef MathUtil::Vector4< Real > Vec4;
		private:
			Mat4	m_Matrices[ max_register_count ]; // user defined matrix values
			Vec4	m_Vectors[ max_register_count ]; // user defined vector values
			Vec4*   m_VectorAttributes[ max_register_count ]; // holds a pointer to vertice information
			
			VertexBuffer* m_vertexStreamPtr;		// pointer to the vertex input
			boost::uint32_t m_vertexCount;			// input vertex count
			Real*		m_dataPtr;					// pointer to vertex elements
		protected:

			// sets the input source
			void SetVertexInput( VertexBuffer& vertexInput ) { m_vertexStreamPtr = &vertexInput; }
			// sets the vertex count
			void SetVertexCount( boost::uint32_t vertexCount ){ m_vertexCount = vertexCount; }

			// grabs the total vertex count
			// use this to iterate through the vertices and grab attributes
			boost::uint32_t GetVertexCount()const{ return m_vertexCount; }

			// used for extracting and modifying vertice information 

			void BeginVectorAttr(); // used to begin extraction
			void EndVectorAttr(); // ends extraction
			virtual void LoadNextAttrSet(); // called between begin/end to load next vertice info

			// used to grab currently loaded info and modify it
			Vec4& GetVectorAttr( boost::uint32_t index )const { return *m_VectorAttributes[ index ]; }

			// used to set attr
			void SetVectorAttr( boost::uint32_t index, Vec4& attr ) { m_VectorAttributes[ index ] = &attr; }

			// user defined 
			const Vec4& GetVectorRegister( boost::uint32_t index )const { return m_Vectors[ index ]; }
			const Mat4& GetMatrixRegister( boost::uint32_t index )const { return m_Matrices[ index ]; }

		public:

			// matrix register slots
			// used for SetMatrix
			enum{
				MREG_MODEL_MATRIX,
				MREG_VIEW_MATRIX,
				MREG_PROJECTION_MATRIX,
				MREG_MVP_MATRIX,
				MREG_TEXTURE_MATRIX,
			};

			// Vector Attribute indexs
			// used for GetVectorAttr, they specify what index that a current element resides in
			enum{

				VATTR_VERTEX,
				VATTR_NORMAL,
				VATTR_COLOR,
				VATTR_UV1,
				VATTR_UV2,
				VATTR_UV3,
				VATTR_UV4,
				VATTR_MAX_ATTR,
			};
			// setup for the program
			virtual void Begin() {}

			// this is called once per render call
			// all vertex information is modified in this function
			virtual void Exec();

			// this is for clean up after the call to Exec()
			virtual void End() {}

			// used to set user defined values
			void SetMatrix( boost::uint32_t index, const Mat4& mat ) { m_Matrices[ index ] = mat; }
			void SetVector( boost::uint32_t index, const Vec4& vector ) { m_Vectors[ index ] = vector; }
	};
}

#endif