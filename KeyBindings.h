#ifndef KEYBINDINGS_HPP_INCLUDED
#define KEYBINDINGS_HPP_INCLUDED

#include "stdafx.h"
#include <unordered_map>

class KeyBindings
{
public:
    KeyBindings() {}

    static KeyBindings& getInstance();

    void bind(Action action, int SDL_KeyCode);

    void getKeysPressed(const Uint8* keystates, std::vector<Action>& inputs);

private:
    std::unordered_map<Action, int, EnumClassHash> bindings{};
};

#endif //KEYBINDINGS_HPP_INCLUDED
