#ifndef SGE_CAMERA_HPP
#define SGE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <sge/utils/export.hpp>
#include <sge/graphics/IShader.hpp>
#include <sge/graphics/ShaderManager.hpp>

namespace SGE
{
	class Export Camera
	{
	private:
		glm::vec3 mPosition;
		glm::vec3 mForwardVector;
		glm::vec3 mUpVector;

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

		void lookAt(const glm::vec3& p);
		void setLookVector(const glm::vec3& l);
		void setPosition(const glm::vec3& p);
		void setFoV(float fov);
		void setAspectRatio(float r);
		void setNearPlaneDistance(float p);
		void setFarPlaneDistance(float p);

		glm::vec3 getPosition();
		glm::vec3 getForwardVector();
		glm::vec3 getUpVector();
		glm::mat4 getVPMat();

		void update();
	};
}

#endif
