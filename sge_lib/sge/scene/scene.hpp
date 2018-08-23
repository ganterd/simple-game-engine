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
	public:
		struct SceneLight
		{
			glm::vec4 position; // Note: Keep as vec4, because OpenGL will align the buffer to vec4
			glm::vec4 colour;
			glm::vec4 ambient;
		};

	private:
		std::vector<Entity*> entities;
		ShaderManager* shaderManager;



		void recursiveExtractLights(Entity* n, glm::mat4 mat, std::vector<SceneLight>& l);

	public:

		Camera* mMainCamera;
		Entity* mRootEntity;

		Scene();

		Export Entity* getRoot(){ return mRootEntity; };
		Export void addEntity(Entity* entity);
		Export void update();
		Export void draw(Shader* targetShader, bool debug = false);
		Export void lightScene();

		Export void setMainCamera(Camera* c){ mMainCamera = c; };
		Export Camera* getMainCamera(){ return mMainCamera; };

		Export std::vector<SceneLight> extractLights();

		template <typename T> std::vector<T*> getComponentsOfType()
		{
			std::vector<Entity*> entityList;
			entityList.push_back(mRootEntity);

			std::vector<T*> matchingComponents;
			while(entityList.size())
			{
				Entity* entity = entityList.back();
				entityList.pop_back();

				for(Entity* child : entity->getChildren())
					entityList.push_back(child);

				std::vector<T*> entityMatchingComponents = entity->getComponentsOfType<T>();
				for(T* component : entityMatchingComponents)
					matchingComponents.push_back(component);
			}
			return matchingComponents;
		}


	};
}

#endif
