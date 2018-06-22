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
			aiProcess_FlipUVs |
			(makeLeftHanded ? aiProcess_MakeLeftHanded : 0)
		);

		if(!model)
		{
			LOG(ERROR) << "Error importing '" << file
				<< "': " << importer.GetErrorString() ;
			return false;
		}

		Utils::splitFilename(file, mDirectory, mFileName);

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
		for(unsigned int i = 0; i < model->mNumMaterials; ++i)
		{
			/* Get textures */
			SGE::Material* newMaterial = new SGE::Material();
			aiMaterial* material = model->mMaterials[i];

			aiString matName;
			material->Get<aiString>(AI_MATKEY_NAME, matName);
			LOG(DEBUG) << "  |- [" << i << "] '" << matName.C_Str() << "'";

			std::vector<ITexture*> textures;
			for(int t = aiTextureType_DIFFUSE; t <= aiTextureType_UNKNOWN; ++t)
			{
				extractMaterialTextures(material, (aiTextureType)t, textures);
			}

			for(int t = 0; t < textures.size(); ++t)
			{
				newMaterial->addTexture(textures[t]);
			}
			mMaterials.push_back(newMaterial);
		}
	}

	void ModelImporter::extractMaterialTextures(
		aiMaterial* mat,
		aiTextureType type,
		std::vector<ITexture*>& textures
	) {
		aiString p;
		for(unsigned int j = 0; j < mat->GetTextureCount(type); ++j)
		{
			mat->GetTexture(type, j, &p);
			std::string path = mDirectory + "/" + std::string(p.C_Str());
			ITexture* tex = NULL;
			switch(type)
			{
				case aiTextureType_DIFFUSE:
					LOG(INFO) << "   |- Diffuse: " << path;
					tex = TextureFactory::newTexture();
					tex->loadFromFile(path, ITexture::Type::Diffuse);
					break;
				case aiTextureType_SPECULAR:
					LOG(INFO) << "   |- Specular: " << path;
					break;
				case aiTextureType_AMBIENT:
					LOG(INFO) << "   |- Ambient: " << path;
					break;
				case aiTextureType_EMISSIVE:
					LOG(INFO) << "   |- Emissive: " << path;
					break;
				case aiTextureType_HEIGHT:
					LOG(INFO) << "   |- Height: " << path;
					break;
				case aiTextureType_NORMALS:
					LOG(INFO) << "   |- Normals: " << path;
					tex = TextureFactory::newTexture();
					tex->loadFromFile(path, ITexture::Type::Normals);
					break;
				case aiTextureType_SHININESS:
					LOG(INFO) << "   |- Shininess: " << path;
					break;
				case aiTextureType_OPACITY:
					LOG(INFO) << "   |- Opacity: " << path;
					tex = TextureFactory::newTexture();
					tex->loadFromFile(path, ITexture::Type::Opacity);
					break;
				case aiTextureType_DISPLACEMENT:
					LOG(INFO) << "   |- Displacement: " << path;
					break;
				case aiTextureType_LIGHTMAP:
					LOG(INFO) << "   |- Lightmap (AO): " << path;
					break;
				case aiTextureType_REFLECTION:
					LOG(INFO) << "   |- Reflection: " << path;
					break;
				case aiTextureType_UNKNOWN:
					LOG(WARNING) << "   |- Unknown texture type (" << path << ")";
				default:
					LOG(WARNING) << "   |- Unhandled texture type (" << path << ")";
			}

			if(tex)
			{
				textures.push_back(tex);
			}
		}
	}

	void ModelImporter::extractTriangles(float scale)
	{
		LOG(INFO) << " |-Meshes: " << model->mNumMeshes ;

		aiMatrix4x4 identity;
		_nodeRecurse(model->mRootNode, identity, scale);
	}

	void ModelImporter::_nodeRecurse(aiNode* n, const aiMatrix4x4& t, float scale)
	{
		aiMatrix4x4 currentTransform =  n->mTransformation * t;
		for(unsigned int m = 0; m < n->mNumMeshes; ++m)
		{
			_processMesh(model->mMeshes[n->mMeshes[m]], currentTransform, scale);
		}

		for(unsigned int c = 0; c < n->mNumChildren; ++c)
		{
			_nodeRecurse(n->mChildren[c], currentTransform, scale);
		}
	}

	void ModelImporter::_processMesh(aiMesh* mesh, const aiMatrix4x4& m, float scale)
	{
		GLfloat* meshVertexData = new GLfloat[mesh->mNumVertices * 3];
		GLfloat* meshNormalsData = new GLfloat[mesh->mNumVertices * 3];


		/* Direct copy VBO from mesh */
		for(unsigned int j = 0; j < mesh->mNumVertices; ++j)
		{
			aiVector3D v = m * (mesh->mVertices[j] * scale);
			meshVertexData[(j * 3) + 0] = v.x;
			meshVertexData[(j * 3) + 1] = v.y;
			meshVertexData[(j * 3) + 2] = v.z;


			meshNormalsData[(j * 3) + 0] = mesh->mNormals[j].x;
			meshNormalsData[(j * 3) + 1] = mesh->mNormals[j].y;
			meshNormalsData[(j * 3) + 2] = mesh->mNormals[j].z;
		}

		/* Extract the VBI from faces */
		unsigned int* meshIndexData = new unsigned int[mesh->mNumFaces * 3];
		for(unsigned int j = 0; j < mesh->mNumFaces; ++j)
		{
			meshIndexData[(j * 3) + 0] = mesh->mFaces[j].mIndices[0];
			meshIndexData[(j * 3) + 1] = mesh->mFaces[j].mIndices[1];
			meshIndexData[(j * 3) + 2] = mesh->mFaces[j].mIndices[2];
		}

		GLfloat* meshUVData = nullptr;
		if(mesh->mNumUVComponents[0] > 0)
		{
			meshUVData = new GLfloat[mesh->mNumVertices * 2];
			for(unsigned int j = 0; j < mesh->mNumVertices; ++j)
			{
				meshUVData[(j * 2) + 0] = mesh->mTextureCoords[0][j].x;
				meshUVData[(j * 2) + 1] = mesh->mTextureCoords[0][j].y;
			}
		}



		/* Create a local mesh */
		SGE::Mesh* resultMesh = new SGE::Mesh();
		resultMesh->setVBOData(meshVertexData, mesh->mNumVertices);
		resultMesh->setNBOData(meshNormalsData, mesh->mNumVertices);
		resultMesh->setIBOData(meshIndexData, mesh->mNumFaces);
		resultMesh->setUVData(meshUVData, mesh->mNumVertices);
		resultMesh->setMaterial(mMaterials[mesh->mMaterialIndex]);
		//LOG(DEBUG) << "   |-" << (*resultMesh);
		meshes.push_back(resultMesh);
	}

	void ModelImporter::extractLights()
	{
		LOG(INFO) << " |-Lights: " << model->mNumLights ;
		for(unsigned int i = 0; i < model->mNumLights; ++i)
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
