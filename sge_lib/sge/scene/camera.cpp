#include "camera.hpp"

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

		deferredShadingShader = new Shader();
		geometryPass = new GLSLShader();
		geometryPass->addShaderFile("resources/shaders/deferred_shading/geometry_pass.vert", SubShader::Vertex);
		geometryPass->addShaderFile("resources/shaders/deferred_shading/geometry_pass.frag", SubShader::Fragment);

		IRenderTarget* geometryPassRT = new GLSLRenderTarget();
		geometryPassRT->addRenderBuffer("diffuse", IRenderBuffer::Color, ITexture::DataType::Float);
		geometryPassRT->addRenderBuffer("specular", IRenderBuffer::Color, ITexture::DataType::Float);
		geometryPassRT->addRenderBuffer("emissive", IRenderBuffer::Color, ITexture::DataType::Float);
		geometryPassRT->addRenderBuffer("normals", IRenderBuffer::Position, ITexture::DataType::Float);
		geometryPassRT->addRenderBuffer("positions", IRenderBuffer::Position, ITexture::DataType::Float);
		geometryPassRT->addRenderBuffer("depth", IRenderBuffer::Depth, ITexture::DataType::Float);
		geometryPass->renderTarget(geometryPassRT);
		geometryPass->linkOutputToRenderBuffer("outDiffuse", geometryPassRT->getRenderBuffer("diffuse"));
		geometryPass->linkOutputToRenderBuffer("outSpecular", geometryPassRT->getRenderBuffer("specular"));
		geometryPass->linkOutputToRenderBuffer("outEmissive", geometryPassRT->getRenderBuffer("emissive"));
		geometryPass->linkOutputToRenderBuffer("outNormals", geometryPassRT->getRenderBuffer("normals"));
		geometryPass->linkOutputToRenderBuffer("outPositions", geometryPassRT->getRenderBuffer("positions"));
		deferredShadingShader->addSubShader("geometryPass", geometryPass);

		lightingPass = new GLSLShader();
		lightingPass->addShaderFile("resources/shaders/deferred_shading/lighting_pass.vert", SubShader::Vertex);
		lightingPass->addShaderFile("resources/shaders/deferred_shading/lighting_pass.frag", SubShader::Fragment);
		lightingPass->linkInputFromRenderBuffer(geometryPassRT->getRenderBuffer("diffuse"), "inDiffuse");
		lightingPass->linkInputFromRenderBuffer(geometryPassRT->getRenderBuffer("specular"), "inSpecular");
		lightingPass->linkInputFromRenderBuffer(geometryPassRT->getRenderBuffer("emissive"), "inEmissive");
		lightingPass->linkInputFromRenderBuffer(geometryPassRT->getRenderBuffer("normals"), "inNormal");
		lightingPass->linkInputFromRenderBuffer(geometryPassRT->getRenderBuffer("positions"), "inPosition");
		IRenderTarget* lightingPassRT = new GLSLRenderTarget();
		lightingPassRT->addRenderBuffer("pingPong0", IRenderBuffer::Color, ITexture::DataType::Float);
		lightingPassRT->addRenderBuffer("pingPong1", IRenderBuffer::Color, ITexture::DataType::Float);
		lightingPass->renderTarget(lightingPassRT);
		deferredShadingShader->addSubShader("lightingPass", lightingPass);

		blitAndGammaPass = new GLSLShader();
		blitAndGammaPass->addShaderFile("resources/shaders/deferred_shading/blitAndGamma.vert", SubShader::Vertex);
		blitAndGammaPass->addShaderFile("resources/shaders/deferred_shading/blitAndGamma.frag", SubShader::Fragment);
		deferredShadingShader->addSubShader("blitAndGammaPass", blitAndGammaPass);

	}

	void Camera::render()
	{
		if(SceneManager::getActiveScene()->getMainCamera() == this)
		{
			SGE::GraphicsManager::OGLGraphicsManager::clearBuffer(mBackgroundColour);
		}

		/* Geometry Pass */
		ShaderManager::setCurrentShader(deferredShadingShader);
		deferredShadingShader->setCurrentSubShader(geometryPass);
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

		/* Lighting Passes */
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		deferredShadingShader->setCurrentSubShader(lightingPass);
		std::vector<Scene::SceneLight> sceneLights = SceneManager::getActiveScene()->extractLights();
		IRenderBuffer* fromBuffer = lightingPass->renderTarget()->getRenderBuffer("pingPong0");
		IRenderBuffer* toBuffer = lightingPass->renderTarget()->getRenderBuffer("pingPong1");
		for(unsigned int i = 0; i < sceneLights.size(); ++i)
		{
			lightingPass->linkInputFromRenderBuffer(fromBuffer,	"inLightAccumulation");
			lightingPass->linkOutputToRenderBuffer("outLightAccumulation", toBuffer);

			/* Set light information */
			Scene::SceneLight light = sceneLights[i];
			lightingPass->setVariable("inLightColour", glm::vec3(light.colour));
			lightingPass->setVariable("inLightPosition", glm::vec3(light.position));
			lightingPass->setVariable("inLightPower", light.colour.w);

			/* Do a whole screen-space render pass */
			/* TODO: Change this to only the light-affected screen region */
			OverlayQuad::draw();

			/* Ping-pong the textures */
			IRenderBuffer* tmp = fromBuffer;
			fromBuffer = toBuffer;
			toBuffer = tmp;
		}

		/* Blit and gamma correction pass */
		deferredShadingShader->setCurrentSubShader(blitAndGammaPass);
		blitAndGammaPass->linkInputFromRenderBuffer(fromBuffer, "inColour");
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
