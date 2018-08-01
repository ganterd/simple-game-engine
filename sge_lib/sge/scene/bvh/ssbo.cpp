#include <sge/scene/bvh/ssbo.hpp>

struct SGE::RT::SSBO::BVHNode* SGE::RT::SSBO::allocatedNodes = nullptr;
struct SGE::RT::SSBO::Tri* SGE::RT::SSBO::allocatedTris = nullptr;
GLuint SGE::RT::SSBO::attachedTrisSSBO = -1;
GLuint SGE::RT::SSBO::attachedBVHNodesSSBO = -1;

void SGE::RT::SSBO::toSSBO(BVH* bvh, GLuint nodesLoc, GLuint trisLoc)
{
    /* 1: Extract nodes in simple format */
    if(allocatedNodes)
        delete[] allocatedNodes;
    allocatedNodes = new struct SSBO::BVHNode[bvh->mCurrentlyAllocatedNodes];
    for(int i = 0; i < bvh->mCurrentlyAllocatedNodes; ++i)
    {
        Node n = bvh->mAllocatedNodes[i];

        int nodeIdx = n.mNodeIndex;
        allocatedNodes[nodeIdx].aabbMin = glm::vec4(n.mAABB.mMin.x, n.mAABB.mMin.y, n.mAABB.mMin.z, 0.0f);
        allocatedNodes[nodeIdx].aabbMax = glm::vec4(n.mAABB.mMax.x, n.mAABB.mMax.y, n.mAABB.mMax.z, 0.0f);
        allocatedNodes[nodeIdx].isLeaf = n.mIsLeaf;
        if(n.mIsLeaf)
        {
            allocatedNodes[nodeIdx].leftIdx = n.mTris[0] == nullptr ? -1 : n.mTris[0]->mTriIndex;
            allocatedNodes[nodeIdx].rightIdx = n.mTris[1] == nullptr ? -1 : n.mTris[1]->mTriIndex;
        }
        else
        {
            allocatedNodes[nodeIdx].leftIdx = n.mLeft->mNodeIndex;
            allocatedNodes[nodeIdx].rightIdx = n.mRight->mNodeIndex;
        }
    }

    GLuint sceneLightsSSBO;
    glGenBuffers(1, &attachedBVHNodesSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, attachedBVHNodesSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(struct SSBO::BVHNode) * bvh->mCurrentlyAllocatedNodes, &allocatedNodes[0], GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, nodesLoc, attachedBVHNodesSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SGE::RT::SSBO::freeSSBO()
{
    glDeleteBuffers(1, &attachedBVHNodesSSBO);
    glDeleteBuffers(1, &attachedTrisSSBO);
}
