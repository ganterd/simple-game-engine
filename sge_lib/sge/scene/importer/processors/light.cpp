#include <sge/scene/importer/processors.hpp>
#include <sge/model/lighting/shadowmap.hpp>

namespace SGE
{
    class LightProcessor : public ImportProcessor
    {
    public:
        LightProcessor() : ImportProcessor("light") {};

        glm::vec3 GetColourFromAttributes(XMLElement* node)
        {
            const char* rCString = node->Attribute("r");
            const char* gCString = node->Attribute("g");
            const char* bCString = node->Attribute("b");

            glm::vec3 c = glm::vec3(0.0f);
            if(rCString)
                c.r = std::stof(rCString);
            if(gCString)
                c.g = std::stof(gCString);
            if(bCString)
                c.b = std::stof(bCString);
            return c;
        }

        virtual void process(XMLElement* node, Entity* entity)
    	{
    		PointLight* p = new PointLight();

    		/* Extract the diffuse light colour */
            XMLElement* diffuseNode = node->FirstChildElement("diffuse");
            if(diffuseNode)
            {
                glm::vec3 lightColour = GetColourFromAttributes(diffuseNode);
                p->setColor(lightColour);

                const char* powerAttribute = diffuseNode->Attribute("power");
                if(powerAttribute)
                {
                    p->setIntensity(std::stof(powerAttribute));
                }
            }

            XMLElement* ambientNode = node->FirstChildElement("ambient");
            if(ambientNode)
            {
                glm::vec3 ambientColour = GetColourFromAttributes(ambientNode);
                p->setAmbient(ambientColour);
            }

    		entity->addComponent(p);

            const XMLElement* shadowsNode = node->FirstChildElement("shadows");
            if(shadowsNode)
            {
                const char* text = shadowsNode->GetText();
                if(text)
                {
                    if(std::string(text) == "true")
                        new ShadowMap(p);
                }
            }
    	}
    };

    static LightProcessor* instantiatedLightProcessor = new LightProcessor();
}
