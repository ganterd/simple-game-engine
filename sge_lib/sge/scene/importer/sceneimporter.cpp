#include "sceneimporter.hpp"

namespace SGE
{
	const char* SceneImporter::_readFile(const char* filePath){
		char* text;

		FILE *file = fopen(filePath, "r");

		if (file == NULL)
			return NULL;

		fseek(file, 0, SEEK_END);
		size_t count = ftell(file);
		rewind(file);


		if (count > 0) {
			text = (char*)malloc(sizeof(char) * (count + 1));
			count = fread(text, sizeof(char), count, file);
			text[count] = '\0';
		}
		fclose(file);

		return text;
	}

	Scene* SceneImporter::importSceneFromFile(std::string sceneFile)
	{
		Processors::listRegisteredProcessors();

		/* Import the scene text data */
		const char* text = this->_readFile(sceneFile.c_str());
		if(text == NULL)
		{
			LOG(WARNING) << "Couldn't read scene file: " << sceneFile;
			return NULL;
		}

		/* Parse the scene data */
		LOG(INFO) << "Parsing scene file: " << sceneFile;
		tinyxml2::XMLDocument doc;
		doc.Parse((char*)text);

		/* Get the root 'scene' node */
		const tinyxml2::XMLElement* root = doc.FirstChildElement("scene");
		if(root == NULL)
		{
			LOG(WARNING) << "Scene file doesn't have root 'scene' node!";
			return NULL;
		}
		LOG(DEBUG) << "Scene has root node...";
		Scene* scene = new Scene();

		/* Get the scene name, if any */
		std::string sceneName = _getSceneName(root);
		if(sceneName != "")
			LOG(DEBUG) << "Scene name is '" << sceneName << "'";

		std::vector<Entity*> entities = _getSceneEntities(root);
		for(int i = 0; i < entities.size(); ++i)
		{
			scene->addEntity(entities[i]);
		}

		processShaders(root);

		LOG(DEBUG) << "Finished parsing scene";
		return scene;
	}


	std::string SceneImporter::_getSceneName(const tinyxml2::XMLElement* root)
	{
		const tinyxml2::XMLAttribute* nameAttr = root->FindAttribute("name");

		if(nameAttr == NULL)
		{
			LOG(WARNING) << "Scene has no name attribute";
			return "";
		}

		return std::string(nameAttr->Value());
	}

	void SceneImporter::processShaders(const tinyxml2::XMLElement* root)
	{
		LOG(DEBUG) << "Getting shaders...";

		const tinyxml2::XMLElement* shadersNode = root->FirstChildElement("shaders");
		if(shadersNode == NULL)
		{
			LOG(WARNING) << "Scene has no shaders listed";
			return;
		}

		const tinyxml2::XMLElement* shaderNode = shadersNode->FirstChildElement("shader");
		if(shaderNode == NULL)
		{
			LOG(WARNING) << "Scene has no shaders listed!";
			return;
		}

		for(; shaderNode; shaderNode = shaderNode->NextSiblingElement("shader"))
		{
			IShader* shader = new GLSLShader();

			const char* shaderName = shaderNode->Attribute("name");

			for(
				const tinyxml2::XMLElement* shaderFileNode = shaderNode->FirstChildElement();
				shaderFileNode;
				shaderFileNode = shaderFileNode->NextSiblingElement()
			)
			{
				std::string shaderFileType = shaderFileNode->Name();
				std::string shaderFilePath = shaderFileNode->GetText();

				IShader::ShaderType shaderType;
				if(shaderFileType == "vert")
					shaderType = IShader::Vertex;
				if(shaderFileType == "geom")
					shaderType = IShader::Geometry;
				if(shaderFileType == "frag")
					shaderType = IShader::Fragment;

				shader->addShaderFile(shaderFilePath, shaderType);
			}

			ShaderManager::addShader(shaderName, shader);
		}
	}

	std::vector<Entity*> SceneImporter::_getSceneEntities(const tinyxml2::XMLElement* root)
	{
		LOG(DEBUG) << "Getting scene entities...";
		std::vector<Entity*> entities;
		const tinyxml2::XMLElement* entitiesNode = root->FirstChildElement("entities");
		if(entitiesNode == NULL)
		{
			LOG(WARNING) << "Scene has no entities node!";
			return entities;
		}

		const tinyxml2::XMLElement* entityNode = entitiesNode->FirstChildElement("entity");
		if(entityNode == NULL)
		{
			LOG(WARNING) << "Scene has no entities!";
			return entities;
		}

		for(; entityNode; entityNode = entityNode->NextSiblingElement("entity"))
		{
			Entity* entity = _getEntity(entityNode);
			if(entity != NULL)
			{
				entities.push_back(entity);
			}
		}

		return entities;
		LOG(DEBUG) << "Finished getting entities...";
	}

	Entity* SceneImporter::_getEntity(const tinyxml2::XMLElement* entityNode)
	{
		LOG(DEBUG) << "Parsing entity...";

		Entity* entity = new Entity();

		const tinyxml2::XMLElement* childNode = entityNode->FirstChildElement();
		if(childNode == NULL)
		{
			LOG(WARNING) << "An entity has no components!";
			return NULL;
		}

		for(; childNode; childNode = childNode->NextSiblingElement())
		{
			std::string nodeType(childNode->Name());
			if(nodeType == "entity")
			{
				Entity* childEntity = _getEntity(childNode);
				childEntity->setParent(entity);
				entity->addChild(childEntity);
			}
			else
			{
				Processors::process(childNode, entity);
			}
		}

		LOG(DEBUG) << "Finished parsing entity";

		return entity;
	}


}
