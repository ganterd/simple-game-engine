#ifndef SGE_SCENE_HPP
#define SGE_SCENE_HPP

#include <vector>

#include <sge/time/time.hpp>
#include <sge/input/input.hpp>
#include <sge/model/Entity.hpp>
#include <sge/graphics/IShader.hpp>
#include <sge/graphics/ShaderManager.hpp>
#include <sge/scene/camera.hpp>
#include <sge/scene/geometry/overlayquad.hpp>

namespace SGE
{
	class Export Scene
	{
	private:
		std::vector<Entity*> entities;
		ShaderManager* shaderManager;

		struct SceneLight{
			glm::vec4 position; // Note: Keep as vec4, because OpenGL will align the buffer to vec4
			glm::vec4 colour;
		};

	public:
		Camera* camera;
		OverlayQuad* overlayQuad;
		GLSLRenderTarget* renderTarget;
		Entity* lightDebugModel;

		Scene();

		void addEntity(Entity* entity);
		void update();
		void draw();
		void lightScene();
	};
}

#endif
