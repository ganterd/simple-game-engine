#pragma once

#include <easylogging++.h>
#include <tinyxml2.h>

#include <sge/model/Entity.hpp>

namespace SGE
{
    typedef const tinyxml2::XMLElement XMLElement;

    class ImportProcessor
    {
    public:
        std::string mNodeName;

        ImportProcessor(std::string nodeName);

        virtual void process(XMLElement* node, Entity* entity) = 0;
    };

    class Processors
    {
    private:
        std::map<std::string, ImportProcessor*> mProcessors;

        static Processors* mInstance;

        static Processors* getInstance()
        {
            if(mInstance == nullptr)
            {
                mInstance = new Processors();
            }
            return mInstance;
        }

    public:

        static void registerProcessor(std::string targetNodes, ImportProcessor* processor);
        static void listRegisteredProcessors();
        static void process(XMLElement* node, Entity* entity);
    };
}
