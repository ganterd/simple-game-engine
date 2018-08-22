#pragma once

#include <limits>
#include <glm/glm.hpp>
#include <sge/utils/export.hpp>

namespace SGE
{
    class AABB
    {
    private:
        glm::vec3 mMin;
        glm::vec3 mMax;

    public:
        AABB()
        {
            mMin = glm::vec3(+std::numeric_limits<float>::infinity());
            mMax = glm::vec3(-std::numeric_limits<float>::infinity());
        }
        AABB(const glm::vec3& min, const glm::vec3& max)
        {
            mMin = min;
            mMax = max;
        }

        Export void min(const glm::vec3& min){ mMin = glm::min(min, mMin); };
        Export glm::vec3 min() const { return mMin; };
        Export void max(const glm::vec3& max){ mMax = glm::max(max, mMax); };
        Export glm::vec3 max() const { return mMax; };

        Export void operator+=(const glm::vec3& p)
        {
            mMin = glm::min(p, mMin);
            mMax = glm::max(p, mMax);
        }

        Export void operator+=(const AABB& other)
        {
            mMin = glm::min(other.mMin, mMin);
            mMax = glm::max(other.mMax, mMax);
        }
    };
}
