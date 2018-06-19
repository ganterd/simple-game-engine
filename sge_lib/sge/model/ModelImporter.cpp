#include "ModelImporter.hpp"

namespace SGE
{
	ModelImporter::ModelImporter()
	{
	}

	bool ModelImporter::importModel(std::string file)
	{
		return this->importModel(file, 1.0f, false);
	}

	bool ModelImporter::importModel(std::string file, float scale, bool makeLeftHanded)
	{
		LOG(INFO) << " Loading model: " << file ;
		LOG(DEBUG) << " |- Make Left Handed: " << (makeLeftHanded ? "true" : "false");

		Assimp::Importer importer;
		model = importer.ReadFile(file,
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			//aiProcess_FlipWindingOrder |
			(makeLeftHanded ? aiProcess_MakeLeftHanded : 0)
		);

		if(!model)
		{
			LOG(ERROR) << "Error importing '" << file
				<< "': " << importer.GetErrorString() ;
			return false;
		}

		this->printModelInfo();

		/* Initialise the Matrials for the model */
		this->extractMaterials();

		/* Create the VAOs for the model */
		this->extractTriangles(scale);

		/* Create light sources for the model */
		this->extractLights();

		return true;
	}

	void ModelImporter::printModelInfo()
	{
		LOG(INFO) << " |-Textures: " << model->mNumTextures;
		LOG(INFO) << " |-Cameras: " << model->mNumCameras;
		LOG(INFO) << " |-Animations: " << model->mNumAnimations;
	}

	void ModelImporter::extractMaterials()
	{
		LOG(INFO) << " |-Materials: " << model->mNumMaterials;
		for(int i = 0; i < model->mNumMaterials; ++i)
		{
			/* Get textures */
			aiMaterial* material = model->mMaterials[i];
			this->extractMaterialTextures(material, aiTextureType_DIFFUSE);
			this->extractMaterialTextures(material, aiTextureType_SPECULAR);
			this->extractMaterialTextures(material, aiTextureType_AMBIENT);
			this->extractMaterialTextures(material, aiTextureType_EMISSIVE);
			this->extractMaterialTextures(material, aiTextureType_SHININESS);
			this->extractMaterialTextures(material, aiTextureType_NORMALS);
			this->extractMaterialTextures(material, aiTextureType_OPACITY);
		}
	}

	std::vector<ITexture*> ModelImporter::extractMaterialTextures(aiMaterial* mat, aiTextureType type)
	{
		std::vector<ITexture*> textures;
		aiString path;
		for(int j = 0; j < mat->GetTextureCount(type); ++j)
		{
			mat->GetTexture(type, j, &path);
			ITexture* tex = NULL;
			switch(type)
			{
				case aiTextureType_DIFFUSE:
					tex = new DiffuseTexture();
					break;
				case aiTextureType_SPECULAR:
					LOG(WARNING) << "No handler for specular textures yet";
					break;
				case aiTextureType_AMBIENT:
					LOG(WARNING) << "No handler for ambient textures yet";
					break;
				case aiTextureType_EMISSIVE:
					LOG(WARNING) << "No handler for emissive textures yet";
					break;
				case aiTextureType_SHININESS:
					LOG(WARNING) << "No handler for shininess textures yet";
					break;
				case aiTextureType_NORMALS:
					LOG(WARNING) << "No handler for normals textures yet";
					break;
				case aiTextureType_OPACITY:
					tex = new OpacityTexture();
					break;
			}

			if(tex)
			{
				tex->LoadFromFile(path.data);
				LOG(INFO) << "     |-" << j << ": " << (*tex);
			}
		}

		return textures;
	}

	void ModelImporter::extractTriangles(float scale)
	{
		LOG(INFO) << " |-Meshes: " << model->mNumMeshes ;

		aiMatrix4x4 identity;
		_nodeRecurse(model->mRootNode, identity);
	}

	void ModelImporter::_nodeRecurse(aiNode* n, const aiMatrix4x4& t)
	{
		aiMatrix4x4 currentTransform =  n->mTransformation * t;
		for(unsigned int m = 0; m < n->mNumMeshes; ++m)
		{
			_processMesh(model->mMeshes[n->mMeshes[m]], currentTransform);
		}

		for(unsigned int c = 0; c < n->mNumChildren; ++c)
		{
			_nodeRecurse(n->mChildren[c], currentTransform);
		}
	}

	void ModelImporter::_processMesh(aiMesh* mesh, const aiMatrix4x4& m)
	{
		GLfloat* meshVertexData = new GLfloat[mesh->mNumVertices * 3];
		GLfloat* meshNormalsData = new GLfloat[mesh->mNumVertices * 3];

		/* Direct copy VBO from mesh */
		for(int j = 0; j < mesh->mNumVertices; ++j)
		{
			aiVector3D v = m * mesh->mVertices[j];
			meshVertexData[(j * 3) + 0] = v.x;
			meshVertexData[(j * 3) + 1] = v.y;
			meshVertexData[(j * 3) + 2] = v.z;


			meshNormalsData[(j * 3) + 0] = mesh->mNormals[j].x;
			meshNormalsData[(j * 3) + 1] = mesh->mNormals[j].y;
			meshNormalsData[(j * 3) + 2] = mesh->mNormals[j].z;
		}

		/* Extract the VBI from faces */
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
		LOG(DEBUG) << "   |-" << (*resultMesh);
		meshes.push_back(resultMesh);
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
