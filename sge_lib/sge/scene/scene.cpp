#include "scene.hpp"

namespace SGE
{
	Scene::Scene()
	{
		camera = new Camera();
		ShaderManager::init();
		ShaderManager::loadShader("deferred_shading/geometry_pass");
		ShaderManager::loadShader("deferred_shading/lighting_pass");
		Time::init();
		overlayQuad = new OverlayQuad();

		int bufferWidth = DisplayManager::getDisplayInstance()->size().width;
		int bufferHeight = DisplayManager::getDisplayInstance()->size().height;
		renderTarget = new GLSLRenderTarget(bufferWidth, bufferHeight);
		renderTarget->addRenderBuffer(IRenderBuffer::BufferType::Color, ITexture::DataType::Float); // Albedo g-buffer
		renderTarget->addRenderBuffer(IRenderBuffer::BufferType::Color, ITexture::DataType::Float); // Specular g-buffer
		renderTarget->addRenderBuffer(IRenderBuffer::BufferType::Position, ITexture::DataType::Float); // Normals g-buffer
		renderTarget->addRenderBuffer(IRenderBuffer::BufferType::Position, ITexture::DataType::Float); // Position g-buffer
		renderTarget->addRenderBuffer(IRenderBuffer::BufferType::Depth, ITexture::DataType::Float);
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

		int entities_count = (int)entities.size();
		for(int i = 0; i < entities_count; ++i)
		{
			entities[i]->update();
		}
	}

	void Scene::draw()
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ShaderManager::useShader("deferred_shading/geometry_pass");
		IShader* shader = ShaderManager::getCurrentShader();
		glm::mat4 vpMat = this->camera->getVPMat();

		/* Draw the meshes */
		// TODO: Use acceleration structure
		int entities_count = (int)entities.size();
		renderTarget->bind();
		renderTarget->clear();
		for(int i = 0; i < entities_count; ++i)
		{
			glm::mat4 mvpMat = vpMat * entities[i]->getModelMat();
			shader->setMVP(mvpMat);
			entities[i]->draw(shader);
		}
		renderTarget->unbind();

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

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		ShaderManager::useShader("deferred_shading/lighting_pass");
		shader = ShaderManager::getCurrentShader();
		shader->setVariable("albedoTexture", 0);
		shader->setVariable("specularTexture", 1);
		shader->setVariable("normalsTexture", 2);
		shader->setVariable("positionsTexture", 3);
		renderTarget->getRenderBuffer(0)->bindTexture(0); // Albedo g-buffer
		renderTarget->getRenderBuffer(1)->bindTexture(1); // Specular g-buffer
		renderTarget->getRenderBuffer(2)->bindTexture(2); // Normals g-buffer
		renderTarget->getRenderBuffer(3)->bindTexture(3); // Position g-buffer
		overlayQuad->draw();
		renderTarget->getRenderBuffer(0)->unbindTexture();
		renderTarget->getRenderBuffer(1)->unbindTexture();
		renderTarget->getRenderBuffer(2)->unbindTexture();
		renderTarget->getRenderBuffer(3)->unbindTexture();
	}

	void Scene::lightScene()
	{
		for(int i = 0; i < sceneLights.size(); ++i)
		{
			//shader->setLightPosition(sceneLights[i].light->getPosition());
		}
	}
}
