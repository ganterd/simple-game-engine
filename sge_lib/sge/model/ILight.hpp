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
		glm::vec4 mPosition;
		glm::vec3 mColor;
		glm::vec3 mAmbient;
		float mIntensity;

	public:
		Entity* mParent;

		Export ILight()
		{
			mPosition = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			mColor = glm::vec3(1.0f, 1.0f, 1.0f);
			mAmbient = glm::vec3(0.0f);
			mIntensity = 0.1f;
		};

		Export void setPosition(glm::vec4 p){ mPosition = p; };
		Export void setColor(glm::vec3 c){ mColor = c; };
		Export void setAmbient(const glm::vec3& a){ mAmbient = a; };
		Export void setIntensity(float i){ mIntensity = i; };

		Export glm::vec4 getPosition(){ return mPosition; };
		Export glm::vec3 getColor() { return mColor; };
		Export glm::vec3 getAmbient() { return mAmbient; };
		Export float getIntensity(){ return mIntensity; };
	};
}

#endif
