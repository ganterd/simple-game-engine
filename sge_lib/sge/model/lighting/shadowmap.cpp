#include "shadowmap.hpp"

namespace SGE{
ShadowMap::ShadowMap(ILight* light) : DrawableComponent()
{
    mComponentTypeString = "shadowmap";
    light->getEntity()->addComponent(this);
    mShader = new GLSLShader();
    mShader->addShaderFile("resources/shaders/shadowmapping/test.vert", Shader::Vertex);
    mShader->addShaderFile("resources/shaders/shadowmapping/test.frag", Shader::Fragment);

    mRenderTarget = new GLSLRenderTarget();
    mRenderTarget->addRenderBuffer("depth", IRenderBuffer::Position, ITexture::DataType::Float);
    mRenderTarget->addRenderBuffer("", IRenderBuffer::Depth, ITexture::DataType::Float);
    mShader->renderTarget(mRenderTarget);
}

void ShadowMap::update()
{
    /* Get a list of all drawable componetns in the scene */
    std::vector<DrawableComponent*> potentialShadowCasters;
    potentialShadowCasters = SceneManager::getActiveScene()->getComponentsOfType<DrawableComponent>();
    LOG_N_TIMES(1, INFO) << potentialShadowCasters.size() << " potentialShadowCasters...";

    /* Whittle the list down to just the shadow casters */
    std::vector<DrawableComponent*> actualShadowCasters;
    for(DrawableComponent* c : potentialShadowCasters)
    {
        if(c->castsShadows())
            actualShadowCasters.push_back(c);
    }
    LOG_N_TIMES(1, INFO) << actualShadowCasters.size() << " actualShadowCasters...";

    /* Determine the AABB of the shadow casters */

    mShadowCastersAABB = AABB();
    for(DrawableComponent* c : actualShadowCasters)
    {
        /* Convert the local AABB to the world AABB */
        AABB componentAABB = c->aabb();
        glm::vec3 min = (componentAABB.min)();
        glm::vec3 max = (componentAABB.max)();
        glm::vec4 p0(min.x, min.y, min.z, 1.0f);
        glm::vec4 p1(min.x, min.y, max.z, 1.0f);
        glm::vec4 p2(min.x, max.y, min.z, 1.0f);
        glm::vec4 p3(min.x, max.y, max.z, 1.0f);
        glm::vec4 p4(max.x, min.y, min.z, 1.0f);
        glm::vec4 p5(max.x, min.y, max.z, 1.0f);
        glm::vec4 p6(max.x, max.y, min.z, 1.0f);
        glm::vec4 p7(max.x, max.y, max.z, 1.0f);

        mShadowCastersAABB += glm::vec3(p0 * c->getEntity()->getWorldModelMat());
        mShadowCastersAABB += glm::vec3(p1 * c->getEntity()->getWorldModelMat());
        mShadowCastersAABB += glm::vec3(p2 * c->getEntity()->getWorldModelMat());
        mShadowCastersAABB += glm::vec3(p3 * c->getEntity()->getWorldModelMat());
        mShadowCastersAABB += glm::vec3(p4 * c->getEntity()->getWorldModelMat());
        mShadowCastersAABB += glm::vec3(p5 * c->getEntity()->getWorldModelMat());
        mShadowCastersAABB += glm::vec3(p6 * c->getEntity()->getWorldModelMat());
        mShadowCastersAABB += glm::vec3(p7 * c->getEntity()->getWorldModelMat());
    }

    mShadowCastersCentroid = (mShadowCastersAABB.min)() + (mShadowCastersAABB.max)();
    mShadowCastersCentroid *= 0.5f;

    glm::vec3 positionWorld = glm::vec3(glm::vec4(mEntity->getPosition(), 1.0f) * mEntity->getWorldModelMat());

    mLightViewMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, (sinf(Time::gameTime()) + 2.0f) * 10.0f)
        * glm::lookAt(
            positionWorld,
            mShadowCastersCentroid,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
}

void ShadowMap::render()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    ShaderManager::setCurrentShader(mShader);
    mRenderTarget->bind();
    mRenderTarget->clear();
    glm::vec3 positionWorld = glm::vec3(glm::vec4(mEntity->getPosition(), 1.0f) * mEntity->getWorldModelMat());
    //mShader->setVariable("inLightPosition", positionWorld);
    mShader->setVariable("inLightNearPlane", 1.0f);
    mShader->setVariable("inLightFarPlane", 20.0f);
    mShader->setVariable("viewProjectionMatrix", mLightViewMatrix);
    SceneManager::getActiveScene()->draw(mShader);
    ShaderManager::setCurrentShader(nullptr);
    mRenderTarget->unbind();
}

void ShadowMap::draw(bool debug)
{
    if(debug)
    {
        ShaderManager::getCurrentShader()->setVariable("modelMatrix", glm::mat4(1.0f));
        Frustum(mLightViewMatrix).draw();
        Point(mShadowCastersCentroid, glm::vec4(1.0f, 0.3f, 0.3f, 0.9f), 10.0f).draw();
        Box(mShadowCastersAABB, glm::vec4(1.0f, 0.4f, 0.4f, 0.9f)).drawLines();
    }
}
}
