#include "camera.hpp"

namespace SGE
{
	Camera::Camera()
	{
		this->fov = 45.0f;
		this->ratio = 4.0f/3.0f;
		this->nearPlane = 0.01f;
		this->farPlane = 1000.0f;

		mPosition = glm::vec3(0.0f,0.0f,0.0f);
		mForwardVector = glm::vec3(1, 0, 0);
		mUpVector = glm::vec3(0,1,0);
		mBackgroundColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Camera::addShader(Shader* s)
	{
		mShaders.push_back(s);
	}

	void Camera::render()
	{
		setPosition(glm::vec3(5.0f, 2.0f, 5.0f));
		lookAt(glm::vec3(1.0f, 1.0f, 1.0f));
		if(mShaders.size() == 0)
		{
			LOG_N_TIMES(1, ERROR) << "No shader for camera to draw with...";
			return;
		}

		if(SceneManager::getActiveScene()->getMainCamera() == this)
		{
			SGE::GraphicsManager::OGLGraphicsManager::clearBuffer(mBackgroundColour);
		}

		for(Shader* shader : mShaders)
		{

			ShaderManager::setCurrentShader(shader);
			std::vector<SubShader*> subShaders = shader->getSubShaders();
			for(SubShader* subShader : subShaders)
			{
				shader->setCurrentSubShader(subShader);
				subShader->enable();
				subShader->setVariable("viewProjectionMatrix", getVPMat());

				if(subShader->isScreenSpaceShader())
				{
					glDisable(GL_CULL_FACE);
					glDisable(GL_DEPTH_TEST);

					/* TMP */
					std::vector<Scene::SceneLight> sceneLights = SceneManager::getActiveScene()->extractLights();

					int numLights = sceneLights.size();
					subShader->setVariable("numLights", numLights);

					GLuint ssboBinding = ((GLSLShader*)subShader)->getSSBOBinding("PointLightsBuffer");
					GLuint sceneLightsSSBO;
					if(ssboBinding != (GLuint)-1)
					{
						glGenBuffers(1, &sceneLightsSSBO);
						glBindBuffer(GL_SHADER_STORAGE_BUFFER, sceneLightsSSBO);
						glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Scene::SceneLight) * numLights, &sceneLights[0], GL_DYNAMIC_COPY);
						glBindBufferBase(GL_SHADER_STORAGE_BUFFER, ssboBinding, sceneLightsSSBO);
						glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
					}

					/* END TMP */
					OverlayQuad::draw();
					if(ssboBinding != (GLuint)-1)
						glDeleteBuffers(1, &sceneLightsSSBO);
				}
				else
				{
					glDepthMask(GL_TRUE);
					glEnable(GL_DEPTH_TEST);
					glDepthFunc(GL_LESS);

					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					glEnable(GL_CULL_FACE);
					glCullFace(GL_BACK);

					Scene* scene = SceneManager::getActiveScene();
					scene->draw(subShader);
				}

				subShader->disable();
			}
		}

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

	void Camera::lookAt(const glm::vec3& p)
	{
		mForwardVector = glm::normalize(p - mPosition);
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

	void Camera::setLookVector(const glm::vec3& l)
	{
		mForwardVector = glm::normalize(l);
		update();
	}

	void Camera::setPosition(const glm::vec3& p )
	{
		mPosition = p;
		update();
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

	glm::vec3 Camera::getPosition()
	{
		return mPosition;
	}

	glm::vec3 Camera::getForwardVector()
	{
		return mForwardVector;
	}

	glm::vec3 Camera::getUpVector()
	{
		return mUpVector;
	}

	glm::mat4 Camera::getVPMat()
	{
		return this->vpMat;
	}
}
