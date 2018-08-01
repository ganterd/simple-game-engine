#pragma once

#include <sge/graphics/ShaderManager.hpp>
#include <sge/scene/bvh/bvh.hpp>

namespace SGE
{
    namespace RT
    {
        class SSBO
        {
        public:
            struct Tri{
                glm::vec4 v0;
                glm::vec4 v1;
                glm::vec4 v2;
            };

            struct BVHNode {
                int leftIdx;
                int rightIdx;
                bool isLeaf;
                glm::vec4 aabbMin;
                glm::vec4 aabbMax;
            };

            static GLuint attachedBVHNodesSSBO;
            static GLuint attachedTrisSSBO;
            static struct SSBO::BVHNode* allocatedNodes;
            static struct SSBO::Tri* allocatedTris;
            static void toSSBO(BVH* bvh, GLuint bvhNodesLoc, GLuint trisLoc);
            static void freeSSBO();
        };
    }
}
