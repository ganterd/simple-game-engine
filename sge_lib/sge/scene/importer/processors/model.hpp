#pragma once

#include <sge/scene/importer/processors.hpp>

namespace SGE
{
    class ModelImportProcessor : public ImportProcessor
    {
    public:
        ModelImportProcessor();

        virtual void process(XMLElement* node, Entity* entity);
    };
}
