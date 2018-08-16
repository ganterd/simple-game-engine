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

    if(SGE::Input::isKeyPressed(SGE::Input::Key::W))
        p += f * d * accelerationPerSecond;
    if(SGE::Input::isKeyPressed(SGE::Input::Key::S))
        p -= f * d * accelerationPerSecond;
    if(SGE::Input::isKeyPressed(SGE::Input::Key::A))
        p -= r * d * accelerationPerSecond;
    if(SGE::Input::isKeyPressed(SGE::Input::Key::D))
        p += r * d * accelerationPerSecond;
    if(SGE::Input::isKeyPressed(SGE::Input::Key::Space))
        p += u * d * accelerationPerSecond;
    if(SGE::Input::isKeyPressed(SGE::Input::Key::LeftControl))
        p -= u * d * accelerationPerSecond;

    mCamera->setPosition(p);
    mCamera->setLookVector(f);
}
