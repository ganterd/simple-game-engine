#include "camera.hpp"

namespace SGE
{
	Camera::Camera()
	{
		this->setFoV(45.0f);
		this->setAspectRatio(4.0f / 3.0f);
		this->setNearPlaneDistance(0.1);
		this->setFarPlaneDistance(1000.0f);
		
		position = glm::vec4(0.0f,-0.5f,5.0f,1.0f);
		lookingAt = glm::vec4(0,0,0,0);
		upVector = glm::vec4(0,1,0,0);
	}
	
	void Camera::lookAt(glm::vec4 p)
	{
		this->lookingAt = p;
	}
	
	void Camera::update()
	{
		viewMat = glm::lookAt(
			glm::vec3(position),
			glm::vec3(lookingAt),
			glm::vec3(upVector)
		);
		
		this->vpMat = projectionMat * viewMat;
	}
	
	void Camera::updateProjectionMat()
	{
		projectionMat = glm::perspective(
			this->fov, 
			this->ratio, 
			this->nearPlane, 
			this->farPlane
		);
	}
	
	void Camera::setPosition(glm::vec4 p )
	{
		this->position = p;
		this->update();
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
	
	glm::vec4 Camera::getPosition()
	{
		return this->position;
	}
	
	glm::mat4 Camera::getVPMat()
	{
		return this->vpMat;
	}
}
