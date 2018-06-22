#ifndef SGE_I_LIGHT_HPP
#define SGE_I_LIGHT_HPP

#include <glm/glm.hpp>

#include <sge/utils/export.hpp>

namespace SGE
{
	class Entity;
	class ILight
	{
	private:
		glm::vec4 position;
		glm::vec3 color;
		float intensity;

	public:
		Entity* mParent;

		Export ILight()
		{
			this->position = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			this->color = glm::vec3(1.0f, 1.0f, 1.0f);
			intensity = 0.1f;
		};

		Export void setPosition(glm::vec4 p){ this->position = p; };
		Export void setColor(glm::vec3 c){ this->color = c; };
		Export void setIntensity(float i){ this->intensity = i; };

		Export glm::vec4 getPosition(){ return this->position; };
		Export glm::vec3 getColor() { return this->color; };
		Export float getIntensity(){ return this->intensity; };
	};
}

#endif
