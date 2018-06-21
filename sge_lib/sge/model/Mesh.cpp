#include "Mesh.hpp"

namespace SGE
{
	Mesh::Mesh()
	{
		glGenVertexArrays(1, &vao);
	}

	void Mesh::renderGL()
	{
		if(mMaterial)
			mMaterial->bindAllTextures();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, numTris * 3, GL_UNSIGNED_INT, (void*)0);
	}

	void Mesh::setVBOData(GLfloat* vboData, int numVerts)
	{
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		this->vboData = new GLfloat[numVerts * 3];
		memcpy(&this->vboData[0], &vboData[0], sizeof(GLfloat) * 3 * numVerts);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(GLfloat) * numVerts * 3,
			this->vboData,
			GL_STATIC_DRAW
		);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
		   0,
		   3,
		   GL_FLOAT,
		   GL_FALSE,
		   0,
		   (void*)0
		);

		this->numVerts = numVerts;
		glBindVertexArray(0);
	}

	void Mesh::setNBOData(GLfloat* nboData, int numVerts)
	{
		glBindVertexArray(vao);
		glGenBuffers(1, &nbo);
		glBindBuffer(GL_ARRAY_BUFFER, nbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(GLfloat) * numVerts * 3,
			nboData,
			GL_STATIC_DRAW
		);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
		   1,
		   3,
		   GL_FLOAT,
		   GL_FALSE,
		   0,
		   (void*)0
		);
		glBindVertexArray(0);
	}

	void Mesh::setUVData(GLfloat* uvData, int numVerts)
	{
		glBindVertexArray(vao);
		glGenBuffers(1, &uvbo);
		glBindBuffer(GL_ARRAY_BUFFER, uvbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(GLfloat) * numVerts * 2,
			uvData,
			GL_STATIC_DRAW
		);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindVertexArray(0);
	}

	void Mesh::setIBOData(unsigned int* iboData, int numTris)
	{
		glBindVertexArray(vao);
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			numTris * 3 * sizeof(unsigned int),
			&iboData[0],
			GL_STATIC_DRAW
		);
		this->iboData = iboData;
		this->numTris = numTris;
		glBindVertexArray(0);
	}
}
