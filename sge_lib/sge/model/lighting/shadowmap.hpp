#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include <sge/model/ILight.hpp>
#include <sge/model/aabb.hpp>
#include <sge/model/geometry/box.hpp>
#include <sge/model/geometry/frustum.hpp>
#include <sge/model/geometry/point.hpp>
#include <sge/scene/entity/drawablecomponent.hpp>
#include <sge/scene/entity/entity.hpp>
#include <sge/scene/scene.hpp>
#include <sge/scene/scenemanager.hpp>

namespace SGE
{
    class ShadowMap : public DrawableComponent
    {
    private:
        glm::mat4 mLightViewMatrix;
        AABB mShadowCastersAABB;
        glm::vec3 mShadowCastersCentroid;

        Shader* mShader;
        IRenderTarget* mRenderTarget;

    public:
        ShadowMap(ILight* light);

        void update();
        void draw(bool debug = false);
        void render();
        IRenderBuffer* renderBuffer(){ return mRenderTarget->getRenderBuffer("depth"); };
        glm::mat4 lightViewMatrix(){ return mLightViewMatrix; };
    };
}
