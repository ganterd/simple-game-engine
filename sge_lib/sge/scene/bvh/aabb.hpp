#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>

namespace SGE
{
    namespace RT
    {
        class AABB
        {
        public:
            glm::vec3 mMin;
            glm::vec3 mMax;
            glm::vec3 mSize;

            AABB()
            {
                mMin = glm::vec3(0.0f);
                mMax = glm::vec3(0.0f);
                mSize = glm::vec3(0.0f);
            }

            /**
             * Grow to accommodate point p
             */
            void grow(const glm::vec3& p)
            {
                mMin = glm::min(mMin, p);
                mMax = glm::max(mMax, p);
                mSize = mMax - mMin;
            }

            /**
             * Grow to accommodate another AABB
             */
            void grow(const AABB& other)
            {
                mMin = glm::min(mMin, other.mMin);
                mMax = glm::max(mMax, other.mMax);
                mSize = mMax - mMin;
            }

            float surfaceArea()
            {
                float sa = 2.0f * mSize.y * mSize.x;
                sa += 2.0f * mSize.y * mSize.z;
                sa += 2.0f * mSize.x * mSize.z;
                return sa;
            }

            static AABB infinity()
            {
                AABB newAABB;
                newAABB.mMin = glm::vec3(
                    +std::numeric_limits<float>::infinity()
                );
                newAABB.mMax = glm::vec3(
                    -std::numeric_limits<float>::infinity()
                );
                newAABB.mSize = glm::vec3(0.0f);
                return newAABB;
            }

            friend std::ostream& operator<< (std::ostream& os, const AABB& a)
            {
                os << "[" << a.mMin[0] << "," << a.mMin[1] << "," << a.mMin[2] << "]->";
                os << "[" << a.mMax[0] << "," << a.mMax[1] << "," << a.mMax[2] << "]";
                return os;
            }
        };
    }
}
