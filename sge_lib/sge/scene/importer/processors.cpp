#include <sge/scene/importer/processors.hpp>

namespace SGE
{
    Processors* Processors::mInstance = nullptr;

    ImportProcessor::ImportProcessor(std::string nodeName)
    {
        mNodeName = nodeName;
        Processors::registerProcessor(mNodeName, this);
    }

    void Processors::process(XMLElement* node, Entity* entity)
    {
        Processors* ins = Processors::getInstance();
        if(ins->mProcessors.find(node->Name()) != ins->mProcessors.end())
        {
            ins->mProcessors[node->Name()]->process(node, entity);
        }
        else
        {
            LOG(WARNING) << "No processor found for '" << node->Name() << "'";
        }
    }

    void Processors::registerProcessor(std::string targetNodes, ImportProcessor* processor)
    {
        Processors* ins = Processors::getInstance();
        std::cout << "Registering processor for '" << targetNodes << "'" << std::endl;
        ins->mProcessors[targetNodes] = processor;
    }

    void Processors::listRegisteredProcessors()
    {
        std::map<std::string, ImportProcessor*>::iterator it;
        Processors* instance = Processors::getInstance();

        LOG(DEBUG) << "Registered processors:";
        for(it = instance->mProcessors.begin(); it != instance->mProcessors.end(); ++it)
        {
            LOG(DEBUG) << "|- '" << it->first << "' [" << it->second << "]";
        }
    }
}
