#pragma once

#include <sge/model/Entity.hpp>

#include <sge/scene/bvh/aabb.hpp>
#include <sge/scene/bvh/node.hpp>
#include <sge/scene/bvh/tri.hpp>

#include <sge/utils/timer.hpp>

namespace SGE
{
    namespace RT
    {
        class BestSplit
        {
        public:
            int axis;
            int splitIndex;
            float cost;

            AABB AABBLeft;
            AABB AABBRight;
            AABB centroidAABB_L;
            AABB centroidAABB_R;
            int numPrimitives_L;
            int numPrimitives_R;

            BestSplit()
            {
                cost = std::numeric_limits<float>::max();
            }
        };

        class Bin
        {
        public:
            std::vector<Tri*> mTris;
            AABB mAABB;
            AABB mCentroidsAABB;

            // Centroid bounds
            float mLeft;
            float mRight;

            Bin()
            {
                mAABB = AABB::infinity();
                mCentroidsAABB = AABB::infinity();
            }
        };

        /**
         * Construction method is an implementation of Wald 2007 - "On fast construction
         * of SAH-based bounding volume hierarchies", just not as efficient...
         */
        class BVH
        {
        public:
            int mNumBins;
            Node* mRoot;
            Entity* mTargetSceneRoot;

            BVH();
            ~BVH();

            void construct(Entity* sceneRoot);

            Bin** mBins;
            std::vector<Tri> extractTris(Entity* sceneRoot);
            void recursiveExtractTris(Entity* n, glm::mat4 m, std::vector<Tri>& v);
            void createBins();
            void freeBins();
            int deepestLevel;
            int numSplitNodes;
            int numLeafNodes;

            AABB** totalAABBRight;
            AABB** totalCentroidAABBRight;
            int** totalPrimitivesRight;

            std::vector<Tri> mExtractedTris;
            Node* mAllocatedNodes;
            size_t mCurrentlyAllocatedNodes;

            Node* recursiveConstruct(Tri** tris, int numTris, const AABB& centroidAABB, int level);

            Node* newNode();
            BestSplit findBestSplit();
        };
    }

}
