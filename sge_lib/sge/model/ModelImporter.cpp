#include "ModelImporter.hpp"

namespace SGE
{
	ModelImporter::ModelImporter()
	{
	}
	
	bool ModelImporter::importModel(std::string file)
	{
		LOG(INFO) << " Loading model: " << file ;
		std::cout;
		Assimp::Importer importer;
		
		model = importer.ReadFile(file,
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_FlipWindingOrder
		);
		
		if(!model)
		{
			LOG(ERROR) << "Error importing '" << file
				<< "': " << importer.GetErrorString() ;
			return false;
		}
		
		this->printModelInfo();
		
		/* Create the VAOs for the model */
		this->extractTriangles();
		
		/* Create light sources for the model */
		this->extractLights();
		
		return true;
	}
	
	void ModelImporter::printModelInfo()
	{
		
		LOG(INFO) << " |-Materials: " << model->mNumMaterials ;
		LOG(INFO) << " |-Textures: " << model->mNumTextures ;
		LOG(INFO) << " |-Cameras: " << model->mNumCameras ;
		LOG(INFO) << " |-Animations: " << model->mNumAnimations ;
		std::cout;
	}
	
	void ModelImporter::extractTriangles()
	{
		LOG(INFO) << " |-Meshes: " << model->mNumMeshes ;
		for(int i = 0; i < model->mNumMeshes; ++i)
		{
			aiMesh* mesh = model->mMeshes[i];
			
			LOG(DEBUG) << "   |-Mesh " << i ;
			LOG(DEBUG) << "     |-Verts: " << mesh->mNumVertices
				;

			GLfloat* meshVertexData = new GLfloat[mesh->mNumVertices * 3];
			GLfloat* meshNormalsData = new GLfloat[mesh->mNumVertices * 3];
			
			/* Direct copy VBO from mesh */
			for(int j = 0; j < mesh->mNumVertices; ++j)
			{
				meshVertexData[(j * 3) + 0] = mesh->mVertices[j].x;
				meshVertexData[(j * 3) + 1] = mesh->mVertices[j].z;
				meshVertexData[(j * 3) + 2] = mesh->mVertices[j].y;
				

				meshNormalsData[(j * 3) + 0] = mesh->mNormals[j].x;
				meshNormalsData[(j * 3) + 1] = mesh->mNormals[j].z;
				meshNormalsData[(j * 3) + 2] = mesh->mNormals[j].y;
			}
			
			/* Extract the VBI from faces */
			LOG(DEBUG) << "     |-Polys: " << mesh->mNumFaces
				;
			unsigned int* meshIndexData = new unsigned int[mesh->mNumFaces * 3];
			for(int j = 0; j < mesh->mNumFaces; ++j)
			{
				meshIndexData[(j * 3) + 0] = mesh->mFaces[j].mIndices[0];
				meshIndexData[(j * 3) + 1] = mesh->mFaces[j].mIndices[1];
				meshIndexData[(j * 3) + 2] = mesh->mFaces[j].mIndices[2];
			}
			
			/* Create a local mesh */
			SGE::Mesh* resultMesh = new SGE::Mesh();
			resultMesh->setVBOData(meshVertexData, mesh->mNumVertices);
			resultMesh->setNBOData(meshNormalsData, mesh->mNumVertices);
			resultMesh->setIBOData(meshIndexData, mesh->mNumFaces);
			meshes.push_back(resultMesh);
		}
	}
	
	void ModelImporter::extractLights()
	{
		LOG(INFO) << " |-Lights: " << model->mNumLights ;
		for(int i = 0; i < model->mNumLights; ++i)
		{
			LOG(DEBUG) << "   |-Light " << i ;
			aiLight* light = model->mLights[i];
		
			LOG(DEBUG) << "     |-Type: ";
			ILight* l;
			if(light->mType == aiLightSource_POINT)
			{
				LOG(DEBUG) << "Point" ;
				l = new PointLight();
			}
			
			lights.push_back(l);
		}
	}
	
	std::vector<Mesh*> ModelImporter::getMeshes()
	{
		return this->meshes;
	}
	
	std::vector<ILight*> ModelImporter::getLights()
	{
		return this->lights;
	}
}
