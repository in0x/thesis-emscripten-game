#include "KeyBindings.h"

KeyBindings& KeyBindings::getInstance()
{
    static std::shared_ptr<KeyBindings> instance = nullptr;

    if (instance == nullptr)
    {
        instance = std::make_shared<KeyBindings>();
    }

    return *instance;
}


void KeyBindings::bind(Action action, int SDL_KeyCode)
{
    bindings.emplace(action, SDL_KeyCode);
}

void KeyBindings::getKeysPressed(const Uint8* keystates, std::vector<Action>& inputs)
{
    for (auto& bind : bindings)
    {
        if (keystates[bind.second])
        {
            inputs.push_back(bind.first);
        }
    }
}
