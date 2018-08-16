#include <sge/scene/importer/processors.hpp>

namespace SGE
{
    class TransformProcessor : public ImportProcessor
    {
    public:
        TransformProcessor() : ImportProcessor("transform") {};

        virtual void process(XMLElement* node, Entity* entity)
        {
            XMLElement* rotationNode = node->FirstChildElement("rotation");
            if(rotationNode)
            {
                const char* xCString = rotationNode->Attribute("x");
                const char* yCString = rotationNode->Attribute("y");
                const char* zCString = rotationNode->Attribute("z");
                if(!xCString || !yCString || !zCString)
                {
                    LOG(ERROR) << "Missing rotation coordinate attribute";
                }
                else
                {
                    float x = std::stof(xCString);
                    float y = std::stof(yCString);
                    float z = std::stof(zCString);

                    std::cout << "ROTATION" << x <<"," << y <<"," << z << std::endl;

                    entity->setRotation(x, y, z);
                }
            }

            XMLElement* translationNode = node->FirstChildElement("translation");
            if(translationNode)
            {
                const char* xCString = translationNode->Attribute("x");
                const char* yCString = translationNode->Attribute("y");
                const char* zCString = translationNode->Attribute("z");
                if(!xCString || !yCString || !zCString)
                {
                    LOG(ERROR) << "Missing translation coordinate attribute";
                }
                else
                {
                    float x = std::stof(xCString);
                    float y = std::stof(yCString);
                    float z = std::stof(zCString);

                    entity->setPosition(glm::vec3(x, y, z));
                }
            }
        }
    };

    static TransformProcessor* instantiatedTransformProcessor = new TransformProcessor();
}
