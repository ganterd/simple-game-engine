#include "scene.hpp"

namespace SGE
{
	Scene::Scene()
	{
		mMainCamera = nullptr;
		mRootEntity = new Entity();
		ShaderManager::init();

		Time::init();
	}

	void Scene::addEntity(Entity* entity)
	{
		mRootEntity->addChild(entity);
	}

	void Scene::update()
	{
		Time::tick();
		Input::update();
		//camera->update();

		mRootEntity->update();
	}

	// 	/* Gather lights. */
	// 	// ShaderManager::useShader("deferredShading", "lightingPass");
	// 	// shader = ShaderManager::getCurrentSubShader();
	// 	// renderTarget->bind();
	// 	// shader->setVariable("viewProjectionMatrix", camera->getVPMat());
	// 	//
	// 	std::vector<SceneLight> sceneLights = extractLights();
	// 	// for(SceneLight l : sceneLights)
	// 	// {
	// 	// 	shader->setVariable("lightColour", glm::vec3(l.colour.r, l.colour.y, l.colour.z));
	// 	// 	lightDebugModel->setPosition(l.position);
	// 	// 	lightDebugModel->draw(shader);
	// 	// }
	//
	// 	int numLights = sceneLights.size();
	// 	shader->setVariable("numLights", numLights);
	//
	// 	GLuint sceneLightsSSBO;
	// 	glGenBuffers(1, &sceneLightsSSBO);
	// 	glBindBuffer(GL_SHADER_STORAGE_BUFFER, sceneLightsSSBO);
	// 	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(SceneLight) * numLights, &sceneLights[0], GL_DYNAMIC_COPY);
	// 	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 9, sceneLightsSSBO);
	// 	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	//
	// 	glDeleteBuffers(1, &sceneLightsSSBO);
	// }

	void Scene::draw(SubShader* targetShader)
	{
		std::cout << "Drawing scene" << std::endl;
		mRootEntity->draw(targetShader);
	}

	std::vector<Scene::SceneLight> Scene::extractLights()
	{
		std::vector<SceneLight> sceneLights;
		recursiveExtractLights(mRootEntity, glm::mat4(1.0f), sceneLights);
		return sceneLights;
	}

	void Scene::recursiveExtractLights(Entity* n, glm::mat4 mat, std::vector<Scene::SceneLight>& sceneLights)
	{
		mat *= n->getModelMat();
		std::vector<ILight*> entityLights = n->getLights();
		for(unsigned int j = 0; j < entityLights.size(); ++j)
		{
			ILight* l = entityLights[j];
			glm::vec3 lightPosition = l->getPosition();
			glm::vec4 p(lightPosition.x, lightPosition.y, lightPosition.z, 1.0f);
			p = mat * p;

			glm::vec3 c = l->getColor();

			SceneLight sceneLight;
			sceneLight.position = p;
			sceneLight.colour.r = c.r;
			sceneLight.colour.g = c.g;
			sceneLight.colour.b = c.b;
			sceneLight.colour.a = l->getIntensity();
			sceneLights.push_back(sceneLight);
		}

		std::vector<Entity*> nChildren = n->getChildren();
		for(unsigned int i = 0; i < nChildren.size(); ++i)
		{
			recursiveExtractLights(nChildren[i], mat, sceneLights);
		}
	}
}
