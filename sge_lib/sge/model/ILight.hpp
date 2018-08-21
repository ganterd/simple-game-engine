#ifndef SGE_I_LIGHT_HPP
#define SGE_I_LIGHT_HPP

#include <glm/glm.hpp>

#include <sge/utils/export.hpp>
#include <sge/scene/entity/component.hpp>

namespace SGE
{
	class ILight : public EntityComponent
	{
	private:
		glm::vec3 mColor;
		glm::vec3 mAmbient;
		float mIntensity;

	public:
		Export ILight() : EntityComponent()
		{
			mComponentTypeString = "light";
			mColor = glm::vec3(1.0f, 1.0f, 1.0f);
			mAmbient = glm::vec3(0.0f);
			mIntensity = 0.1f;
		};

		Export void setColor(glm::vec3 c){ mColor = c; };
		Export void setAmbient(const glm::vec3& a){ mAmbient = a; };
		Export void setIntensity(float i){ mIntensity = i; };

		Export glm::vec3 getColor() { return mColor; };
		Export glm::vec3 getAmbient() { return mAmbient; };
		Export float getIntensity(){ return mIntensity; };
	};
}

#endif
