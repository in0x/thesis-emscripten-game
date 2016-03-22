#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "stdafx.h"
#include "GameObjectManager.h"
#include "KeyBindings.h"

class Game
{
public:
    Game();

    Game(unsigned int windowWidth, unsigned int windowHeight) : m_windowWidth(windowWidth), m_windowHeight(windowHeight) {}

    bool init(std::string windowTitle);

    bool update();

    void render();

    SDL_Window* m_window = nullptr;

private:
    void clear();

    unsigned int m_windowWidth;
    unsigned int m_windowHeight;

    SDL_Renderer* m_renderer = nullptr;

    GameObjectManager& goManager = GameObjectManager::getInstance();
    KeyBindings& keyBindings = KeyBindings::getInstance();

    Clock m_clock{};
};

#endif //GAME_HPP_INCLUDED
