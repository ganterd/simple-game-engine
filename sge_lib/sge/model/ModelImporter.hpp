#ifndef SGE_MODEL_IMPORTER_HPP
#define SGE_MODEL_IMPORTER_HPP

#include <easylogging++.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <string>
#include <vector>

#include <sge/model/ILight.hpp>
#include <sge/model/PointLight.hpp>
#include <sge/model/Mesh.hpp>

namespace SGE
{
	class ModelImporter
	{
	const aiScene* model;
	std::vector<Mesh*> meshes;
	std::vector<ILight*> lights;
	
	private:
		void printModelInfo();
		void extractTriangles();
		void extractLights();
		
	public:
		ModelImporter();
		
		bool importModel(std::string file);
		std::vector<Mesh*> getMeshes();
		std::vector<ILight*> getLights();
	};
};

#endif
