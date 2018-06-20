#include "scene.hpp"

namespace SGE
{
	Scene::Scene()
	{
		camera = new Camera();
		ShaderManager::init();
		ShaderManager::loadShader("dl_pass");
		Time::init();
		overlayQuad = new OverlayQuad();
	}

	void Scene::addEntity(Entity* entity)
	{
		this->entities.push_back(entity);
	}

	void Scene::update()
	{
		Time::tick();
		Input::update();
		camera->update();
	}

	void Scene::draw()
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

		//ShaderManager::useShader("dl_pass");
		//overlayQuad->draw();
	}

	void Scene::lightScene()
	{
		for(int i = 0; i < sceneLights.size(); ++i)
		{
			//shader->setLightPosition(sceneLights[i].light->getPosition());
		}
	}
}
