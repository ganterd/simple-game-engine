#include "mesh.hpp"

namespace SGE
{
	Mesh::Mesh()
	{
		glGenVertexArrays(1, &vao);
	}

	void Mesh::draw()
	{
		renderGL();
	}

	void Mesh::renderGL()
	{
		if(mMaterial)
			mMaterial->bindAllTextures();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, numTris * 3, GL_UNSIGNED_INT, (void*)0);
		if(mMaterial)
			mMaterial->unbindAllTextures();
	}

	void Mesh::setVBOData(GLfloat* vboData, int numVerts)
	{
		GLuint bufferIndex;
		glBindVertexArray(vao);
		glGenBuffers(1, &bufferIndex);

		glBindBuffer(GL_ARRAY_BUFFER, bufferIndex);
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
		glDeleteBuffers(1, &bufferIndex);

		/* Generate the AABB for this mesh */
		for(int i = 0; i < numVerts; ++i)
		{
			glm::vec3 p(
				vboData[i * 3 + 0],
				vboData[i * 3 + 1],
				vboData[i * 3 + 2]
			);
			mAABB += p;
		}
	}

	void Mesh::setNBOData(GLfloat* nboData, int numVerts)
	{
		GLuint bufferIndex;
		glBindVertexArray(vao);
		glGenBuffers(1, &bufferIndex);
		glBindBuffer(GL_ARRAY_BUFFER, bufferIndex);
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
		glDeleteBuffers(1, &bufferIndex);
	}

	void Mesh::setUVData(GLfloat* uvData, int numVerts)
	{
		GLuint bufferIndex;
		glBindVertexArray(vao);
		glGenBuffers(1, &bufferIndex);
		glBindBuffer(GL_ARRAY_BUFFER, bufferIndex);
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(GLfloat) * numVerts * 2,
			uvData,
			GL_STATIC_DRAW
		);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindVertexArray(0);
		glDeleteBuffers(1, &bufferIndex);
	}

	void Mesh::setTangentsData(GLfloat* tangentsData, int numVerts)
	{
		GLuint bufferIndex;
		glBindVertexArray(vao);
		glGenBuffers(1, &bufferIndex);
		glBindBuffer(GL_ARRAY_BUFFER, bufferIndex);
		glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(GLfloat) * numVerts * 3,
			tangentsData,
			GL_STATIC_DRAW
		);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(
		   3,
		   3,
		   GL_FLOAT,
		   GL_FALSE,
		   0,
		   (void*)0
		);
		glBindVertexArray(0);
		glDeleteBuffers(1, &bufferIndex);
	}

	void Mesh::setIBOData(unsigned int* iboData, int numTris)
	{
		GLuint bufferIndex;
		glBindVertexArray(vao);
		glGenBuffers(1, &bufferIndex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIndex);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			numTris * 3 * sizeof(unsigned int),
			&iboData[0],
			GL_STATIC_DRAW
		);
		this->iboData = iboData;
		this->numTris = numTris;
		glBindVertexArray(0);
		glDeleteBuffers(1, &bufferIndex);
	}
}
