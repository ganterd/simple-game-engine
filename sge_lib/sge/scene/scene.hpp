#ifndef SGE_SCENE_HPP
#define SGE_SCENE_HPP

#include <vector>

#include <sge/time/time.hpp>
#include <sge/input/input.hpp>
#include <sge/graphics/shaders/ShaderManager.hpp>
#include <sge/scene/entity/entity.hpp>
#include <sge/scene/camera.hpp>

namespace SGE
{
	class Camera;
	class Scene
	{
	private:
		std::vector<Entity*> entities;
		ShaderManager* shaderManager;

		struct SceneLight
		{
			glm::vec4 position; // Note: Keep as vec4, because OpenGL will align the buffer to vec4
			glm::vec4 colour;
			glm::vec4 ambient;
		};

		void recursiveExtractLights(Entity* n, glm::mat4 mat, std::vector<SceneLight>& l);

	public:
		Camera* mMainCamera;
		Entity* mRootEntity;

		Scene();

		Export Entity* getRoot(){ return mRootEntity; };
		Export void addEntity(Entity* entity);
		Export void update();
		//Export void draw();
		Export void draw(SubShader* targetShader);
		Export void lightScene();

		Export void setMainCamera(Camera* c){ mMainCamera = c; };
		Export Camera* getMainCamera(){ return mMainCamera; };

		Export std::vector<SceneLight> extractLights();
	};
}

#endif
