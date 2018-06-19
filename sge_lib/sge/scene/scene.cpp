#include "scene.hpp"

namespace SGE
{
	Scene::Scene()
	{
		camera = new Camera();
		ShaderManager::init();
		Time::init();
	}

	void Scene::addEntity(Entity* entity)
	{
		this->entities.push_back(entity);
	}

	void Scene::update()
	{
		//glm::mat4 rotMat = glm::rotate(0.2f, 0.0f, 1.0f, 0.0f);
		//glm::vec4 camMat = camera->getPosition();
		//camera->setPosition(camMat);
		Time::tick();
		Input::Update();
		camera->update();
	}

	void Scene::draw()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glCullFace(GL_BACK);

		IShader* shader = ShaderManager::getCurrentShader();
		if(shader == NULL)
		{
			std::cout << "[Scene] No shader attached..." << std::endl;
			return;
		}
		glm::mat4 vpMat = this->camera->getVPMat();

		/* Draw the meshes */
		// TODO: Use acceleration structure
		int entities_count = entities.size();
		for(int i = 0; i < entities_count; ++i)
		{
			glm::mat4 mvpMat = vpMat * entities[i]->getModelMat();

			shader->setMVP(mvpMat);
			entities[i]->draw();
		}

		/* Gather lights. Don't use acceleration structure in case */
		/* lights are accidentally culled */
		sceneLights.empty();
		for(int i = 0; i < entities_count; ++i)
		{
			std::vector<ILight*> entityLights = entities[i]->getLights();
			for(int j = 0; j < entityLights.size(); ++j)
			{
				SceneLight l;
				l.light = entityLights[j];
				l.modelMat = entities[i]->getModelMat();
				sceneLights.push_back(l);
			}
		}
		lightScene();
	}

	void Scene::lightScene()
	{
		for(int i = 0; i < sceneLights.size(); ++i)
		{
			//shader->setLightPosition(sceneLights[i].light->getPosition());
		}
	}
}
