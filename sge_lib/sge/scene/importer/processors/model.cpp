#include <sge/scene/importer/processors/model.hpp>

namespace SGE
{
    static ModelImportProcessor* _instantiatedModelImportProcessor = new ModelImportProcessor();

    SGE::ModelImportProcessor::ModelImportProcessor() : SGE::ImportProcessor("model")
    {

    }

    void SGE::ModelImportProcessor::process(XMLElement* node, Entity* entity)
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

        entity->loadFromFile(modelPath, scale, false);
    }
}
