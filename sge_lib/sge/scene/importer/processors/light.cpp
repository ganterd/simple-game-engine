#include <sge/scene/importer/processors.hpp>

namespace SGE
{
    class LightProcessor : public ImportProcessor
    {
    public:
        LightProcessor() : ImportProcessor("light") {};

        virtual void process(XMLElement* node, Entity* entity)
    	{
    		PointLight* p = new PointLight();

    		/* Extract the diffuse light colour */
    		float r, g, b, power;
    		std::string rString = node->Attribute("r");
    		std::string gString = node->Attribute("g");
    		std::string bString = node->Attribute("b");
    		std::string pString = node->Attribute("power");

    		if(!rString.length() || !gString.length() || !bString.length())
    		{
    			LOG(ERROR) << "Missing channel value in diffuse colour";
    		}
    		else
    		{
    			r = std::stof(rString);
    			g = std::stof(gString);
    			b = std::stof(bString);

    			p->setColor(glm::vec3(r, g, b));
    		}

    		/* Extract the light power */
    		if(!pString.length())
    		{
    			LOG(ERROR) << "Light power node has no content!";
    		}
    		else
    		{
    			float power = std::stof(pString);
    			p->setIntensity(power);
    		}

    		entity->addLight(p);
    	}
    };

    static LightProcessor* instantiatedLightProcessor = new LightProcessor();
}
