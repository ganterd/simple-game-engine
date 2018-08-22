#include "camera.hpp"

#include <sge/model/lighting/shadowmap.hpp>

namespace SGE
{
	Camera::Camera() : EntityComponent()
	{
		mComponentTypeString = "camera";

		this->fov = 45.0f;
		this->ratio = 4.0f/3.0f;
		this->nearPlane = 0.01f;
		this->farPlane = 1000.0f;

		mBackgroundColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		/* Create the render target for the geometry and debug geometry passes */
		IRenderTarget* geometryPassRT = new GLSLRenderTarget();
		geometryPassRT->addRenderBuffer("diffuse", IRenderBuffer::Color, ITexture::DataType::Float);
		geometryPassRT->addRenderBuffer("specular", IRenderBuffer::Color, ITexture::DataType::Float);
		geometryPassRT->addRenderBuffer("emissive", IRenderBuffer::Color, ITexture::DataType::Float);
		geometryPassRT->addRenderBuffer("normals", IRenderBuffer::Position, ITexture::DataType::Float);
		geometryPassRT->addRenderBuffer("positions", IRenderBuffer::Position, ITexture::DataType::Float);
		geometryPassRT->addRenderBuffer("depth", IRenderBuffer::Depth, ITexture::DataType::Float);

		/* Create the geometry pass shader, and link to the render target */
		geometryPass = new GLSLShader();
		geometryPass->addShaderFile("resources/shaders/deferred_shading/geometry_pass.vert", Shader::Vertex);
		geometryPass->addShaderFile("resources/shaders/deferred_shading/geometry_pass.frag", Shader::Fragment);
		geometryPass->renderTarget(geometryPassRT);
		geometryPass->linkOutputToRenderBuffer("outDiffuse", geometryPassRT->getRenderBuffer("diffuse"));
		geometryPass->linkOutputToRenderBuffer("outSpecular", geometryPassRT->getRenderBuffer("specular"));
		geometryPass->linkOutputToRenderBuffer("outEmissive", geometryPassRT->getRenderBuffer("emissive"));
		geometryPass->linkOutputToRenderBuffer("outNormals", geometryPassRT->getRenderBuffer("normals"));
		geometryPass->linkOutputToRenderBuffer("outPositions", geometryPassRT->getRenderBuffer("positions"));

		/* Create the debug geometry shader pass, and link to the render target */
		IRenderTarget* debugGeometryPassRT = new GLSLRenderTarget();
		debugGeometryPassRT->addRenderBuffer("emissive", IRenderBuffer::Color, ITexture::DataType::Float);
		debugGeometryPassRT->addRenderBuffer("depth", IRenderBuffer::Depth, ITexture::DataType::Float);

		debugGeometryPass = new GLSLShader();
		debugGeometryPass->addShaderFile("resources/shaders/deferred_shading/debug_geometry_pass.vert", Shader::Vertex);
		debugGeometryPass->addShaderFile("resources/shaders/deferred_shading/debug_geometry_pass.frag", Shader::Fragment);
		debugGeometryPass->renderTarget(debugGeometryPassRT);
		debugGeometryPass->linkOutputToRenderBuffer("outEmissive", debugGeometryPassRT->getRenderBuffer("emissive"));

		/* Create the lighting pass shader, link the inputs ffrom the geometry pass */
		lightingPass = new GLSLShader();
		lightingPass->addShaderFile("resources/shaders/deferred_shading/lighting_pass.vert", Shader::Vertex);
		lightingPass->addShaderFile("resources/shaders/deferred_shading/lighting_pass.frag", Shader::Fragment);
		lightingPass->linkInputFromRenderBuffer(geometryPassRT->getRenderBuffer("diffuse"), "inDiffuse");
		lightingPass->linkInputFromRenderBuffer(geometryPassRT->getRenderBuffer("specular"), "inSpecular");
		lightingPass->linkInputFromRenderBuffer(geometryPassRT->getRenderBuffer("normals"), "inNormal");
		lightingPass->linkInputFromRenderBuffer(geometryPassRT->getRenderBuffer("positions"), "inPosition");

		/* Create the ping-pong render target for the per-light lighting pass */
		IRenderTarget* lightingPassRT = new GLSLRenderTarget();
		lightingPassRT->addRenderBuffer("pingPong0", IRenderBuffer::Color, ITexture::DataType::Float);
		lightingPassRT->addRenderBuffer("pingPong1", IRenderBuffer::Color, ITexture::DataType::Float);
		lightingPass->renderTarget(lightingPassRT);

		/* Create the blit and gamma pass shader, and link the inputs from the */
		/* geometry pass. The specific input from the lighting pass will be decided  */
		/* during rendering, depending on how many lights are in the scene and which */
		/* ping-pong texture was the most-recently used */
		blitAndGammaPass = new GLSLShader();
		blitAndGammaPass->addShaderFile("resources/shaders/deferred_shading/blitAndGamma.vert", Shader::Vertex);
		blitAndGammaPass->addShaderFile("resources/shaders/deferred_shading/blitAndGamma.frag", Shader::Fragment);
		blitAndGammaPass->linkInputFromRenderBuffer(debugGeometryPassRT->getRenderBuffer("emissive"), "inEmissive");
	}

	void Camera::render()
	{
		if(SceneManager::getActiveScene()->getMainCamera() == this)
		{
			SGE::GraphicsManager::OGLGraphicsManager::clearBuffer(mBackgroundColour);
		}

		/* Geometry Pass */
		ShaderManager::setCurrentShader(geometryPass);
		geometryPass->renderTarget()->clear();
		geometryPass->setVariable("viewProjectionMatrix", getVPMat());
		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		Scene* scene = SceneManager::getActiveScene();
		scene->draw(geometryPass);

		debugGeometryPass->renderTarget()->bind();
		debugGeometryPass->renderTarget()->clear();
		if(mDrawDebug)
		{
			ShaderManager::setCurrentShader(debugGeometryPass);
			debugGeometryPass->setVariable("viewProjectionMatrix", getVPMat());
			scene->draw(debugGeometryPass, true);
		}

		/* Shadow passes */
		std::vector<ILight*> lights = scene->getComponentsOfType<ILight>();
		for(ILight* light : lights)
		{
			std::vector<ShadowMap*> shaddowMappers = light->getEntity()->getComponentsOfType<ShadowMap>();
			if(shaddowMappers.size())
			{
				ShadowMap* m = shaddowMappers[0];
				//m->render();
			}
		}

		/* Lighting Passes */
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		ShaderManager::setCurrentShader(lightingPass);
		lightingPass->renderTarget()->clear();
		std::vector<Scene::SceneLight> sceneLights = SceneManager::getActiveScene()->extractLights();
		IRenderBuffer* fromBuffer = lightingPass->renderTarget()->getRenderBuffer("pingPong0");
		IRenderBuffer* toBuffer = lightingPass->renderTarget()->getRenderBuffer("pingPong1");
		for(ILight* light : lights)
		{
			lightingPass->linkInputFromRenderBuffer(fromBuffer,	"inLightAccumulation");
			lightingPass->linkOutputToRenderBuffer("outLightAccumulation", toBuffer);

			/* Set light information */
			glm::vec3 lightPosition = glm::vec3(light->getEntity()->getWorldModelMat() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			lightingPass->setVariable("inLightColour", light->getColor());
			lightingPass->setVariable("inLightPosition", lightPosition);
			lightingPass->setVariable("inLightAmbient", light->getAmbient());
			lightingPass->setVariable("inLightPower", light->getIntensity());

			std::vector<ShadowMap*> shaddowMappers = light->getEntity()->getComponentsOfType<ShadowMap>();
			if(shaddowMappers.size())
			{
				ShadowMap* m = shaddowMappers[0];
				lightingPass->setVariable("inLightHasShadowMap", 1);
				lightingPass->setVariable("inLightViewMatrix", m->lightViewMatrix());
				lightingPass->linkInputFromRenderBuffer(m->renderBuffer(), "inLightShadowMap");
			}
			else
			{
				lightingPass->setVariable("inLightHasShadowMap", 0);
			}

			/* Do a whole screen-space render pass */
			/* TODO: Change this to only the light-affected screen region */
			OverlayQuad::draw();

			/* Ping-pong the textures */
			IRenderBuffer* tmp = fromBuffer;
			fromBuffer = toBuffer;
			toBuffer = tmp;
		}

		/* Blit and gamma correction pass */
		ShaderManager::setCurrentShader(blitAndGammaPass);
		blitAndGammaPass->linkInputFromRenderBuffer(fromBuffer, "inColour");
		//blitAndGammaPass->linkInputFromRenderBuffer(geometryPass->renderTarget()->getRenderBuffer("diffuse"), "inColour");
		OverlayQuad::draw();

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		checkGLErrors();

		if(SceneManager::getActiveScene()->getMainCamera() == this)
		{
			SGE::DisplayManager::getDisplayInstance()->swapBuffers();
		}
	}

	void Camera::setAsMainCamera()
	{
		SceneManager::getActiveScene()->setMainCamera(this);
	}

	void Camera::update()
	{
		updateProjectionMat();
		vpMat = projectionMat *  glm::inverse(mEntity->getWorldModelMat());
	}

	void Camera::updateProjectionMat()
	{
		projectionMat = glm::perspective(fov, ratio, nearPlane, farPlane);
	}

	void Camera::setFoV(float fov)
	{
		this->fov = fov;
		this->updateProjectionMat();
	}

	void Camera::setAspectRatio(float r)
	{
		this->ratio = r;
		this->updateProjectionMat();
	}

	void Camera::setNearPlaneDistance(float p)
	{
		this->nearPlane = p;
		this->updateProjectionMat();
	}

	void Camera::setFarPlaneDistance(float p)
	{
		this->farPlane = p;
		this->updateProjectionMat();
	}

	glm::mat4 Camera::getVPMat()
	{
		return this->vpMat;
	}
}
