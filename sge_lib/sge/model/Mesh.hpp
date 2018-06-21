#ifndef SGE_MESH_HPP
#define SGE_MESH_HPP

#include <iostream>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <string.h>
#include <vector>

#include <sge/utils/export.hpp>

#include <sge/graphics/material/material.hpp>

namespace SGE
{
	class Export Mesh
	{
	private:
		GLuint vbo;
		GLuint nbo;
		GLuint ibo;
		GLuint uvbo;
		GLuint vao;

		int numVerts;
		int numTris;

		GLfloat* vboData;
		GLfloat* nboData;
		GLfloat* uvData;
		unsigned int* iboData;

		Material* mMaterial;

	public:
		Mesh();

		void renderGL();

		void setMaterial(Material* m);
		void setVBOData(GLfloat* vboData, int numVerts);
		void setNBOData(GLfloat* nboData, int numVerts);
		void setIBOData(unsigned int* iboData, int numTris);
		void setUVData(GLfloat* uvData, int numVerts);

		friend std::ostream& operator<< (std::ostream &out, const Mesh &mesh)
		{
			out << "Mesh v:" << mesh.numVerts << " f:" << mesh.numTris;
			return out;
		}
	};
}

#endif
