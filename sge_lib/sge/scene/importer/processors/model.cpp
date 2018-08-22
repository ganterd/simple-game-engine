#include <sge/scene/importer/processors.hpp>
#include <sge/model/model.hpp>

namespace SGE
{
    class ModelImportProcessor : public ImportProcessor
    {
    public:
        ModelImportProcessor() : ImportProcessor("model")
        {

        }

        void process(XMLElement* node, Entity* entity)
        {
            const XMLElement* modelPathNode = node->FirstChildElement("path");
            if(modelPathNode == NULL)
            {
                LOG(ERROR) << "A model has no path!";
                return;
            }

            std::string modelPath(modelPathNode->GetText());
            LOG(DEBUG) << "Model: " << modelPath;

            float scale = 1.0f;
            const char* scaleCString = node->Attribute("scale");
            if(scaleCString)
            {
                scale = std::stof(scaleCString);
                LOG(DEBUG) << "Scale: " << scale;
            }

            Model* model = new Model();
            model->loadFromFile(modelPath, scale, false);

            const XMLElement* shadowsNode = node->FirstChildElement("shadowCaster");
            if(shadowsNode)
            {
                const char* text = shadowsNode->GetText();
                if(text)
                {
                    if(std::string(text) == "true")
                        model->castsShadows(true);
                }
            }

            entity->addComponent(model);
        }
    };

    static ModelImportProcessor* _instantiatedModelImportProcessor = new ModelImportProcessor();
}
