#ifndef SGE_I_LIGHT_HPP
#define SGE_I_LIGHT_HPP

#include <glm/glm.hpp>

#include <sge/utils/export.hpp>

namespace SGE
{
	class Export ILight
	{
	private:
		glm::vec4 position;
		glm::vec3 color;
		float intensity;
		
	public:
		ILight()
		{
			this->position = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			this->color = glm::vec3(1.0f, 1.0f, 1.0f);
			intensity = 1.0f;
		};
		
		void setPosition(glm::vec4 p){ this->position = p; };
		void setColor(glm::vec3 c){ this->color = c; };
		void setIntesnsity(float i){ this->intensity = i; };
		
		glm::vec4 getPosition(){ return this->position; };
		glm::vec3 getColor() { return this->color; };
		float getIntensity(){ return this->intensity; };
	};
}

#endif
