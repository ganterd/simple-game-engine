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

	void Scene::draw(SubShader* targetShader)
	{
		// std::cout << "Drawing scene" << std::endl;
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
		std::vector<ILight*> entityLights = n->getComponentsOfType<ILight>();
		for(unsigned int j = 0; j < entityLights.size(); ++j)
		{
			ILight* l = entityLights[j];
			glm::vec4 p(0.0f, 0.0f, 0.0f, 1.0f);
			p = mat * p;

			glm::vec3 c = l->getColor();
			glm::vec3 a = l->getAmbient();

			SceneLight sceneLight;
			sceneLight.position = p;
			sceneLight.colour.r = c.r;
			sceneLight.colour.g = c.g;
			sceneLight.colour.b = c.b;
			sceneLight.colour.a = l->getIntensity();
			sceneLight.ambient.r = a.r;
			sceneLight.ambient.g = a.g;
			sceneLight.ambient.b = a.b;

			sceneLights.push_back(sceneLight);
		}

		std::vector<Entity*> nChildren = n->getChildren();
		for(unsigned int i = 0; i < nChildren.size(); ++i)
		{
			recursiveExtractLights(nChildren[i], mat, sceneLights);
		}
	}
}
