#pragma once

#include <glm/glm.hpp>

#include <sge/scene/bvh/aabb.hpp>

namespace SGE
{
    namespace RT
    {
        class Tri
        {
        public:
            glm::vec4 mV0;
            glm::vec4 mV1;
            glm::vec4 mV2;
            glm::vec2 mUV0;
            glm::vec2 mUV1;
            glm::vec2 mUV2;
            glm::vec4 mCentroid;
            AABB mAABB;
            unsigned long int mTriIndex;

            Tri()
            {

            }

            Tri(
                const glm::vec4& v0, const glm::vec4& v1, const glm::vec4& v2,
                const glm::vec2& uv0, const glm::vec2& uv1, const glm::vec2& uv2
            )
            {
                mV0 = v0;
                mV1 = v1;
                mV2 = v2;
                mUV0 = uv0;
                mUV1 = uv1;
                mUV2 = uv2;

                mAABB = AABB::infinity();
                mAABB.grow(v0);
                mAABB.grow(v1);
                mAABB.grow(v2);

                mCentroid = (mV0 + mV1 + mV2) / 3.0f;
            }
        };
    }
}
