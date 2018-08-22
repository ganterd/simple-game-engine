#include <sge/model/ILight.hpp>
#include <sge/model/geometry/point.hpp>
#include <sge/scene/entity/entity.hpp>

namespace SGE
{
    void ILight::draw(bool debug)
    {
        if(debug)
        {
            Point(
                glm::vec3(0.0f),
                glm::vec4(mColor.r, mColor.g, mColor.b, 0.9f), 
                20.0f
            ).draw();
        }
    }
}
