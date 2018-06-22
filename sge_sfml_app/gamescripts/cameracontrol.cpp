#include "cameracontrol.hpp"

CameraControl::CameraControl()
{
    mCurrentVelocity = glm::vec3(0.0f);
}

void CameraControl::update()
{
	if (SGE::Input::isKeyPressed(SGE::Input::Key::N0))
	{
		SGE::DisplayManager::getDisplayInstance()->toggleGrabCursor();
	}

    glm::vec3 p = mCamera->getPosition();
    glm::vec3 f = mCamera->getForwardVector();
    glm::vec3 u = mCamera->getUpVector();
    glm::vec3 r = glm::normalize(glm::cross(f, u));
    float d = (float)SGE::Time::getDelta();

    glm::vec2 m = SGE::Input::mouseDelta();
    if(m.x != 0.0f || m.y != 0.0f)
    {
        m *= mouseScale;
        f = glm::rotate(f, -m.y, r);
        f = glm::rotate(f, -m.x, u);
    }

    mCurrentVelocity -= mCurrentVelocity * decelerationPercentPerSecond * d;

    if(SGE::Input::isKeyPressed(SGE::Input::Key::W))
        mCurrentVelocity += f * d * accelerationPerSecond;
    if(SGE::Input::isKeyPressed(SGE::Input::Key::S))
        mCurrentVelocity -= f * d * accelerationPerSecond;
    if(SGE::Input::isKeyPressed(SGE::Input::Key::A))
        mCurrentVelocity -= r * d * accelerationPerSecond;
    if(SGE::Input::isKeyPressed(SGE::Input::Key::D))
        mCurrentVelocity += r * d * accelerationPerSecond;
    if(SGE::Input::isKeyPressed(SGE::Input::Key::Space))
        mCurrentVelocity += u * d * accelerationPerSecond;
    if(SGE::Input::isKeyPressed(SGE::Input::Key::LeftControl))
        mCurrentVelocity -= u * d * accelerationPerSecond;

    float speed = glm::length(mCurrentVelocity);
    if(speed > maxSpeedPerSecond)
        mCurrentVelocity = glm::normalize(mCurrentVelocity) * maxSpeedPerSecond;

    mCamera->setPosition(p + mCurrentVelocity * d);
    mCamera->setLookVector(f);
}
