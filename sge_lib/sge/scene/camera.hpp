#ifndef SGE_CAMERA_HPP
#define SGE_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <sge/utils/export.hpp>
#include <sge/graphics/shaders/ShaderManager.hpp>
#include <sge/scene/scenemanager.hpp>
#include <sge/scene/entity/component.hpp>
#include <sge/model/geometry/overlayquad.hpp>

namespace SGE
{
	class Camera : public EntityComponent
	{
	private:
		glm::vec4 mBackgroundColour;
		bool mDrawDebug = false;

		Shader* geometryPass;
		Shader* debugGeometryPass;
		Shader* lightingPass;
		Shader* blitAndGammaPass;

		float fov;
		float ratio;
		float nearPlane;
		float farPlane;

		glm::mat4 projectionMat;
		glm::mat4 viewMat;
		glm::mat4 vpMat;

		void updateProjectionMat();
	public:
		Export Camera();

		Export void setFoV(float fov);
		Export void setAspectRatio(float r);
		Export void setNearPlaneDistance(float p);
		Export void setFarPlaneDistance(float p);
		Export void setAsMainCamera();

		Export bool drawDebug() const { return mDrawDebug; };
		Export void drawDebug(bool b){ mDrawDebug = b; };

		Export glm::mat4 getVPMat();

		virtual void update();
		Export void render();
	};
}

#endif
