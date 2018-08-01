#include "scene.hpp"

namespace SGE
{
	Scene::Scene()
	{
		camera = new Camera();
		ShaderManager::init();
		ShaderManager::loadShader("deferred_shading/geometry_pass");
		ShaderManager::loadShader("deferred_shading/lighting_pass");
		ShaderManager::loadShader("deferred_shading/debug_light");
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
		renderTarget->addRenderBuffer(IRenderBuffer::BufferType::Color, ITexture::DataType::Float); // emmisiveGBuffer g-buffer

		lightDebugModel = new Entity();
		lightDebugModel->loadFromFile("resources/models/cube/cube.obj");

		mRootEntity = new Entity();
	}

	void Scene::addEntity(Entity* entity)
	{
		mRootEntity->addChild(entity);
	}

	void Scene::update()
	{
		Time::tick();
		Input::update();
		camera->update();

		mRootEntity->update();
		if(mBVH.mTargetSceneRoot != mRootEntity)
		{
			mBVH.construct(mRootEntity);
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

		/* Draw the meshes */
		// TODO: Use acceleration structure
		int entities_count = (int)entities.size();
		renderTarget->bind();
		renderTarget->clear();

		shader->setVariable("viewProjectionMatrix", camera->getVPMat());
		mRootEntity->draw(shader);


		/* Gather lights. Don't use acceleration structure in case */
		/* lights are accidentally culled */
		ShaderManager::useShader("deferred_shading/debug_light");
		shader = ShaderManager::getCurrentShader();
		renderTarget->bind();
		shader->setVariable("viewProjectionMatrix", camera->getVPMat());

		std::vector<SceneLight> sceneLights = extractLights();
		// for(int i = 0; i < sceneLights.size(); ++i)
		// {
		// 	glm::vec3 c(
		// 		sceneLights[i].colour.x,
		// 		sceneLights[i].colour.y,
		// 		sceneLights[i].colour.z
		// 	);
		// 	shader->setVariable("lightColour", c);
		//
		// 	glm::vec3 p(
		// 		sceneLights[i].position.x,
		// 		sceneLights[i].position.y,
		// 		sceneLights[i].position.z
		// 	);
		// 	lightDebugModel->setPosition(p);
		// 	lightDebugModel->draw(shader);
		// }
		renderTarget->unbind();

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		ShaderManager::useShader("deferred_shading/lighting_pass");
		shader = ShaderManager::getCurrentShader();

		int numLights = sceneLights.size();
		shader->setVariable("numLights", numLights);

		GLuint sceneLightsSSBO;
		glGenBuffers(1, &sceneLightsSSBO);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, sceneLightsSSBO);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(SceneLight) * numLights, &sceneLights[0], GL_DYNAMIC_COPY);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 9, sceneLightsSSBO);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);


		shader->setVariable("albedoTexture", 0);
		shader->setVariable("specularTexture", 1);
		shader->setVariable("normalsTexture", 2);
		shader->setVariable("positionsTexture", 3);
		shader->setVariable("cameraPosition", camera->getPosition());
		renderTarget->getRenderBuffer(0)->bindTexture(0); // Albedo g-buffer
		renderTarget->getRenderBuffer(1)->bindTexture(1); // Specular g-buffer
		renderTarget->getRenderBuffer(2)->bindTexture(2); // Normals g-buffer
		renderTarget->getRenderBuffer(3)->bindTexture(3); // Position g-buffer
		renderTarget->getRenderBuffer(4)->bindTexture(4); // Position g-buffer
		overlayQuad->draw();
		renderTarget->getRenderBuffer(0)->unbindTexture();
		renderTarget->getRenderBuffer(1)->unbindTexture();
		renderTarget->getRenderBuffer(2)->unbindTexture();
		renderTarget->getRenderBuffer(3)->unbindTexture();
		renderTarget->getRenderBuffer(4)->unbindTexture();

		glDeleteBuffers(1, &sceneLightsSSBO);
	}

	std::vector<Scene::SceneLight> Scene::extractLights()
	{
		std::vector<SceneLight> sceneLights;
		recursiveExtractLights(mRootEntity, glm::mat4(1.0f), sceneLights);
		return sceneLights;
	}

	void Scene::recursiveExtractLights(Entity* n, glm::mat4 mat, std::vector<Scene::SceneLight>& sceneLights)
	{
		mat *= n->modelMat;
		std::vector<ILight*> entityLights = n->getLights();
		for(int j = 0; j < entityLights.size(); ++j)
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

		for(int i = 0; i < n->mChildren.size(); ++i)
		{
			recursiveExtractLights(n->mChildren[i], mat, sceneLights);
		}
	}
}
