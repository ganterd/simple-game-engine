#include <sge/input/input.hpp>
#include <sge/input/sfmlinputhandler.hpp>

SGE::Input* SGE::Input::mInstance = nullptr;
glm::vec2 SGE::Input::mMousePosition = glm::vec2(0);
glm::vec2 SGE::Input::mMouseDelta = glm::vec2(0);

SGE::Input* SGE::Input::Init()
{
    // Will handle other windowing/input systems here
    return new SFMLInputHandler();
}

SGE::Input* SGE::Input::GetInstance()
{
    if(mInstance == nullptr)
        mInstance = Init();
    return mInstance;
}

void SGE::Input::Update()
{
    GetInstance()->InternalUpdate();
}

bool SGE::Input::IsKeyPressed(Key k)
{
    return GetInstance()->InternalKeyPressed(k);
}
