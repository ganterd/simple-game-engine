#include <sge/input/sfmlinputhandler.hpp>

SGE::SFMLInputHandler::SFMLInputHandler()
{
    LOG(INFO) << "Initiliasing input handler...";
    mSFMLDisplay = dynamic_cast<SGE::SFMLDisplay*>(SGE::DisplayManager::getDisplayInstance());
    if(mSFMLDisplay == nullptr)
    {
        LOG(ERROR) << "Tried to create an SFML Input handler on a non-SFML display";
        return;
    }

    SFMLKeyMapping[Input::Key::A] = sf::Keyboard::A;
	SFMLKeyMapping[Input::Key::B] = sf::Keyboard::B;
	SFMLKeyMapping[Input::Key::C] = sf::Keyboard::C;
	SFMLKeyMapping[Input::Key::D] = sf::Keyboard::D;
	SFMLKeyMapping[Input::Key::E] = sf::Keyboard::E;
	SFMLKeyMapping[Input::Key::F] = sf::Keyboard::F;
	SFMLKeyMapping[Input::Key::G] = sf::Keyboard::G;
	SFMLKeyMapping[Input::Key::H] = sf::Keyboard::H;
	SFMLKeyMapping[Input::Key::I] = sf::Keyboard::I;
	SFMLKeyMapping[Input::Key::J] = sf::Keyboard::J;
	SFMLKeyMapping[Input::Key::K] = sf::Keyboard::K;
	SFMLKeyMapping[Input::Key::L] = sf::Keyboard::L;
	SFMLKeyMapping[Input::Key::M] = sf::Keyboard::M;
	SFMLKeyMapping[Input::Key::N] = sf::Keyboard::N;
	SFMLKeyMapping[Input::Key::O] = sf::Keyboard::O;
	SFMLKeyMapping[Input::Key::P] = sf::Keyboard::P;
	SFMLKeyMapping[Input::Key::Q] = sf::Keyboard::Q;
	SFMLKeyMapping[Input::Key::R] = sf::Keyboard::R;
	SFMLKeyMapping[Input::Key::S] = sf::Keyboard::S;
	SFMLKeyMapping[Input::Key::T] = sf::Keyboard::T;
	SFMLKeyMapping[Input::Key::U] = sf::Keyboard::U;
	SFMLKeyMapping[Input::Key::V] = sf::Keyboard::V;
	SFMLKeyMapping[Input::Key::W] = sf::Keyboard::W;
	SFMLKeyMapping[Input::Key::X] = sf::Keyboard::X;
	SFMLKeyMapping[Input::Key::Y] = sf::Keyboard::Y;
	SFMLKeyMapping[Input::Key::Z] = sf::Keyboard::Z;
	SFMLKeyMapping[Input::Key::Space] = sf::Keyboard::Space;
	SFMLKeyMapping[Input::Key::N0] = sf::Keyboard::Num0;
	SFMLKeyMapping[Input::Key::N1] = sf::Keyboard::Num1;
	SFMLKeyMapping[Input::Key::N2] = sf::Keyboard::Num2;
	SFMLKeyMapping[Input::Key::N3] = sf::Keyboard::Num3;
	SFMLKeyMapping[Input::Key::N4] = sf::Keyboard::Num4;
	SFMLKeyMapping[Input::Key::N5] = sf::Keyboard::Num5;
	SFMLKeyMapping[Input::Key::N6] = sf::Keyboard::Num6;
	SFMLKeyMapping[Input::Key::N7] = sf::Keyboard::Num7;
	SFMLKeyMapping[Input::Key::N8] = sf::Keyboard::Num8;
	SFMLKeyMapping[Input::Key::N9] = sf::Keyboard::Num9;
	SFMLKeyMapping[Input::Key::Left] = sf::Keyboard::Left;
	SFMLKeyMapping[Input::Key::Right] = sf::Keyboard::Right;
	SFMLKeyMapping[Input::Key::Up] = sf::Keyboard::Up;
	SFMLKeyMapping[Input::Key::Down] = sf::Keyboard::Down;
    SFMLKeyMapping[Input::Key::LeftControl] = sf::Keyboard::LControl;

    sf::Vector2i p = sf::Mouse::getPosition();
    mMousePosition = glm::vec2((float)p.x, (float)p.y);
    mMouseDelta = glm::vec2(0.0f);
}

void SGE::SFMLInputHandler::InternalUpdate()
{
    SFMLDisplay* d = dynamic_cast<SFMLDisplay*>(DisplayManager::getDisplayInstance());
    if(d == nullptr)
    {
        LOG(ERROR) << "No SFML window to get input from?";
        return;
    }

    glm::vec2 center(d->mWindowSize.width / 2,  d->mWindowSize.height / 2);
    sf::Vector2i p = sf::Mouse::getPosition(*d->window);
    glm::vec2 newMousePos = glm::vec2((float)p.x, (float)p.y);
    mMouseDelta = newMousePos - center;
    mMousePosition = center;
    sf::Mouse::setPosition(sf::Vector2i((int)center.x, (int)center.y), *d->window);
}

bool SGE::SFMLInputHandler::InternalKeyPressed(Key k)
{
    sf::Keyboard::Key sfmlKey = SFMLKeyMapping[k];
    return sf::Keyboard::isKeyPressed(sfmlKey);
}
