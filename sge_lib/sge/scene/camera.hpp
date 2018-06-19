#ifndef SGE_CAMERA_HPP
#define SGE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <sge/graphics/IShader.hpp>
#include <sge/graphics/ShaderManager.hpp>

namespace SGE
{
	class Camera
	{
	private:
		glm::vec4 position;
		glm::vec4 lookingAt;
		glm::vec4 upVector;

		float fov;
		float ratio;
		float nearPlane;
		float farPlane;

		glm::mat4 projectionMat;
		glm::mat4 viewMat;
		glm::mat4 vpMat;

		void updateProjectionMat();
	public:
		Camera();

		void lookAt(glm::vec4 p);

		void setPosition(glm::vec4 p);
		void setFoV(float fov);
		void setAspectRatio(float r);
		void setNearPlaneDistance(float p);
		void setFarPlaneDistance(float p);

		glm::vec4 getPosition();
		glm::mat4 getVPMat();

		void update();
	};
}

#endif
