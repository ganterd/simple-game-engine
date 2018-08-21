#include <sge/scene/importer/sceneimporter.hpp>
#include <sge/scene/scenemanager.hpp>

namespace SGE
{
	Scene* SceneImporter::importSceneFromFile(std::string sceneFile)
	{
		Processors::listRegisteredProcessors();

		/* Import the scene text data */
		const char* text = Utils::readFile(sceneFile.c_str());
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
		SceneManager::setActiveScene(scene);

		/* Get the scene name, if any */
		std::string sceneName = _getSceneName(root);
		if(sceneName != "")
			LOG(DEBUG) << "Scene name is '" << sceneName << "'";

		processShaders(root);

		std::vector<Entity*> entities = _getSceneEntities(root);
		for(unsigned int i = 0; i < entities.size(); ++i)
		{
			scene->addEntity(entities[i]);
		}



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
		// LOG(DEBUG) << "Getting shaders...";
		//
		// const tinyxml2::XMLElement* shadersNode = root->FirstChildElement("shaders");
		// if(shadersNode == NULL)
		// {
		// 	LOG(WARNING) << "Scene has no shaders listed";
		// 	return;
		// }
		//
		// const tinyxml2::XMLElement* shaderNode = shadersNode->FirstChildElement("shader");
		// if(shaderNode == NULL)
		// {
		// 	LOG(WARNING) << "Scene has no shaders listed!";
		// 	return;
		// }
		//
		// for(; shaderNode; shaderNode = shaderNode->NextSiblingElement("shader"))
		// {
		// 	Shader* shader = new Shader();
		//
		// 	const char* shaderName = shaderNode->Attribute("name");
		// 	shader->setName(shaderName);
		//
		// 	const tinyxml2::XMLElement* subShaderNode = shaderNode->FirstChildElement("subShader");
		// 	while(subShaderNode)
		// 	{
		// 		const char* subShaderName = subShaderNode->Attribute("name");
		// 		SubShader* subShader = new GLSLShader();
		// 		subShader->setName(subShaderName);
		//
		// 		/* Create render targets if any */
		// 		XMLElement* renderTargetNode = subShaderNode->FirstChildElement("renderTarget");
		// 		if(renderTargetNode)
		// 		{
		// 			subShader->setToRenderTarget(true);
		//
		// 			XMLElement* renderBufferNode = renderTargetNode->FirstChildElement("buffer");
		// 			while(renderBufferNode)
		// 			{
		// 				std::string bufferName = renderBufferNode->Attribute("name");
		// 				std::string bufferTypeString = renderBufferNode->Attribute("type");
		//
		// 				IRenderBuffer::BufferType bufferType;
		// 				if(bufferTypeString == "rgb")
		// 					bufferType = IRenderBuffer::BufferType::Color;
		// 				else if(bufferTypeString == "rgb32")
		// 					bufferType = IRenderBuffer::BufferType::Position;
		// 				else if(bufferTypeString == "depth")
		// 					bufferType = IRenderBuffer::BufferType::Depth;
		// 				else
		// 				{
		// 					LOG(ERROR) << "Unkown render buffer type '" << bufferTypeString << "'";
		// 					continue;
		// 				}
		//
		// 				subShader->getRenderTarget()->addRenderBuffer(bufferName, bufferType, ITexture::DataType::Float);
		//
		// 				renderBufferNode = renderBufferNode->NextSiblingElement();
		// 			}
		// 		}
		//
		// 		/* Import GLSL shader files */
		// 		const tinyxml2::XMLElement* shaderFileNode = subShaderNode->FirstChildElement("file");
		// 		while(shaderFileNode)
		// 		{
		// 			std::string shaderFileType = shaderFileNode->Attribute("type");
		// 			std::string shaderFilePath = shaderFileNode->GetText();
		//
		// 			SubShader::ShaderType shaderType = SubShader::Vertex;
		// 			if(shaderFileType == "vert")
		// 				shaderType = SubShader::Vertex;
		// 			else if(shaderFileType == "geom")
		// 				shaderType = SubShader::Geometry;
		// 			else if(shaderFileType == "frag")
		// 				shaderType = SubShader::Fragment;
		// 			else
		// 			{
		// 				LOG(WARNING) << "Unknown shader type '" << shaderFileType << "'";
		// 				continue;
		// 			}
		//
		//
		// 			subShader->addShaderFile(shaderFilePath, shaderType);
		// 			shaderFileNode = shaderFileNode->NextSiblingElement();
		// 		}
		//
		// 		/* Create render targets if any */
		// 		XMLElement* inputBuffers = subShaderNode->FirstChildElement("inputBuffers");
		// 		if(inputBuffers)
		// 		{
		// 			XMLElement* bufferNode = inputBuffers->FirstChildElement("buffer");
		// 			while(bufferNode)
		// 			{
		// 				std::string bufferSourceShader = shaderName;
		// 				if(bufferNode->Attribute("sourceShader"))
		// 					bufferSourceShader = bufferNode->Attribute("sourceShader");
		// 				std::string bufferSourceSubShader = bufferNode->Attribute("sourceSubShader");
		// 				std::string bufferName = bufferNode->Attribute("name");
		// 				std::string bufferSampler = bufferNode->Attribute("sampler");
		//
		// 				subShader->addRenderBufferLink(
		// 					bufferSourceShader,
		// 					bufferSourceSubShader,
		// 					bufferName,
		// 					bufferSampler
		// 				);
		//
		// 				bufferNode = bufferNode->NextSiblingElement();
		// 			}
		// 		}
		//
		// 		XMLElement* screenSpaceShaderNode = subShaderNode->FirstChildElement("screenSpace");
		// 		if(screenSpaceShaderNode)
		// 		{
		// 			std::string screenSpaceString = screenSpaceShaderNode->GetText();
		// 			if(screenSpaceString == "true")
		// 				subShader->setIsScreenSpaceShader(true);
		// 		}
		//
		// 		shader->addSubShader(subShaderName, subShader);
		// 		subShaderNode = subShaderNode->NextSiblingElement();
		// 	}
		//
		// 	ShaderManager::addShader(shaderName, shader);
		// }
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
