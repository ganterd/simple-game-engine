#ifndef SGE_MODEL_IMPORTER_HPP
#define SGE_MODEL_IMPORTER_HPP

#include <iostream>
#include <string>
#include <vector>

#include <easylogging++.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <sge/model/ILight.hpp>
#include <sge/model/PointLight.hpp>
#include <sge/model/Mesh.hpp>

#include <sge/graphics/texture/ITexture.hpp>
#include <sge/graphics/texture/DiffuseTexture.hpp>
#include <sge/graphics/texture/OpacityTexture.hpp>



namespace SGE
{
	class ModelImporter
	{
	const aiScene* model;
	std::vector<Mesh*> meshes;
	std::vector<ILight*> lights;

	private:
		void printModelInfo();
		void extractMaterials();
		std::vector<ITexture*> extractMaterialTextures(aiMaterial* mat, aiTextureType type);
		void extractTriangles(float scale);
		void _nodeRecurse(aiNode* n, const aiMatrix4x4& m);
		void _processMesh(aiMesh*, const aiMatrix4x4& m);
		void extractLights();

	public:
		ModelImporter();

		bool importModel(std::string file);
		bool importModel(std::string file, float scale, bool makeLeftHanded);

		std::vector<Mesh*> getMeshes();
		std::vector<ILight*> getLights();
	};
};

#endif
