#pragma once

#include <sge/input/input.hpp>

namespace SGE
{
	class Export SFMLInputHandler : public Input
    {
    protected:
        virtual void InternalUpdate();
        virtual bool InternalKeyPressed(Key k);

    private:
        std::map<Input::Key, sf::Keyboard::Key> SFMLKeyMapping;

        SFMLDisplay* mSFMLDisplay;

    public:
        SFMLInputHandler();
    };
}
