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
		ShaderManager::loadShader("deferred_shading/blit");
		Time::init();
		overlayQuad = new OverlayQuad();

		int bufferWidth = DisplayManager::getDisplayInstance()->size().width;
		int bufferHeight = DisplayManager::getDisplayInstance()->size().height;
		renderTarget = new GLSLRenderTarget(bufferWidth, bufferHeight);
		renderTarget->addRenderBuffer(IRenderBuffer::BufferType::Position, ITexture::DataType::Float); // Position g-buffer
		renderTarget->addRenderBuffer(IRenderBuffer::BufferType::Depth, ITexture::DataType::Float);

		cachedFrames[0] = new GLSLRenderTarget(bufferWidth, bufferHeight);
		cachedFrames[0]->addRenderBuffer(IRenderBuffer::BufferType::Color, ITexture::DataType::Float);
		cachedFrames[0]->addRenderBuffer(IRenderBuffer::BufferType::Depth, ITexture::DataType::Float);
		cachedFrames[0]->clear();

		cachedFrames[1] = new GLSLRenderTarget(bufferWidth, bufferHeight);
		cachedFrames[1]->addRenderBuffer(IRenderBuffer::BufferType::Color, ITexture::DataType::Float);
		cachedFrames[1]->addRenderBuffer(IRenderBuffer::BufferType::Depth, ITexture::DataType::Float);
		cachedFrames[1]->clear();
		currentFrame = 0;

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
			mBVHSSBO.toSSBO(&mBVH);
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

		mBVHSSBO.bind(11, 10);

		int fromBuffer = currentFrame % 2;
		int toBuffer = (currentFrame + 1) % 2;
		shader->setVariable("positionsTexture", 0);
		shader->setVariable("cachedFrame", 1);
		shader->setVariable("cameraPosition", camera->getPosition());
		shader->setVariable("gameTime", (float)Time::gameTime());
		shader->setVariable("frames", currentFrame);

		renderTarget->getRenderBuffer(0)->bindTexture(0); // Position g-buffer
		cachedFrames[toBuffer]->bind();
		cachedFrames[fromBuffer]->getRenderBuffer(0)->bindTexture(1); // Position g-buffer
		overlayQuad->draw();
		renderTarget->getRenderBuffer(0)->unbindTexture();
		cachedFrames[fromBuffer]->getRenderBuffer(0)->unbindTexture(); // Position g-buffer
		cachedFrames[toBuffer]->unbind();
		//pingPongFrame++;

		glDeleteBuffers(1, &sceneLightsSSBO);


		/* Blit rendertarget to framebuffer */
		ShaderManager::useShader("deferred_shading/blit");
		shader = ShaderManager::getCurrentShader();
		shader->setVariable("colourFrame", 0);
		cachedFrames[toBuffer]->getRenderBuffer(0)->bindTexture(0);
		overlayQuad->draw();
		cachedFrames[toBuffer]->getRenderBuffer(0)->unbindTexture();

		currentFrame++;
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
