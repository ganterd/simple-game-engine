#include "cameracontrol.hpp"

CameraControl::CameraControl() : SGE::EntityComponent()
{
    mCurrentVelocity = glm::vec3(0.0f);
}

void CameraControl::update()
{
	if (SGE::Input::isKeyPressed(SGE::Input::Key::N0))
	{
		SGE::DisplayManager::getDisplayInstance()->toggleGrabCursor();
	}

    glm::vec2 m = SGE::Input::mouseDelta() * mouseScale;
    glm::vec3 rot = mEntity->getLocalRotation();
    if(m.x != 0.0f || m.y != 0.0f)
    {
        rot.x += m.y;
        rot.y += m.x;

        std::cout << "Rotation: " << rot.x <<"," << rot.y << "," << rot.z << std::endl;
    }

    glm::vec3 p = mEntity->getPosition();
    glm::vec3 f = glm::vec3(mEntity->getModelMat() * glm::vec4(0, 0, 1, 0));
    glm::vec3 u = glm::vec3(mEntity->getModelMat() * glm::vec4(0, 1, 0, 0));
    glm::vec3 r = glm::normalize(glm::cross(f, u));
    float d = (float)SGE::Time::getDelta();

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

    mEntity->setRotation(rot);
    mEntity->setPosition(p);
    // printf(
    //     "P[%2.1f,%2.1f,%2.1f] R[%2.1f,%2.1f,%2.1f]\n",
    //     p.x, p.y, p.z,
    //     rot.x, rot.y, rot.z
    // );
}
