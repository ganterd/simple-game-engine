#include <sge/scene/importer/processors.hpp>
#include <sge/scene/camera.hpp>

namespace SGE
{
    class CameraProcessor : public ImportProcessor
    {
    public:
        CameraProcessor() : ImportProcessor("camera") {};

        virtual void process(XMLElement* node, Entity* entity)
    	{
    		Camera* c = new Camera();

            const char* isMainCStr = node->Attribute("isMain");
            if(isMainCStr)
            {
                if(std::string(isMainCStr) == "true")
                {
                    c->setAsMainCamera();
                }
            }
            else
            {
                if(SceneManager::getActiveScene()->getMainCamera() == nullptr)
                {
                    c->setAsMainCamera();
                }
            }

            // XMLElement* shaderNode = node->FirstChildElement("shader");
            // while(shaderNode)
            // {
            //
            //     const char* shaderNameCStr = shaderNode->Attribute("shader");
            //     if(!shaderNameCStr)
            //     {
            //         LOG(ERROR) << "Camera shader has no name";
            //     }
            //     else
            //     {
            //         Shader* s = ShaderManager::getShader(shaderNameCStr);
            //         if(!s)
            //         {
            //             LOG(ERROR) << "No shader with name '" << shaderNameCStr <<"'";
            //         }
            //         else
            //         {
            //             LOG(DEBUG) << "Adding shader '" << shaderNameCStr << "' to camera";
            //             c->addShader(s);
            //         }
            //     }
            //     shaderNode = shaderNode->NextSiblingElement("shader");
            // }

    		entity->addComponent(c);
    	}
    };

    static CameraProcessor* instantiatedCameraProcessor = new CameraProcessor();
}
