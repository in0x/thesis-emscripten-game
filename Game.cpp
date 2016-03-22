#include "Game.h"

Game::Game(){}

// Game.init()
// Creates the games window and draw surface
// Return false if initialization fails at any point
bool Game::init(std::string windowTitle)
{
    srand(time(nullptr));

    // Returns 0 on success
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to init SDL " << SDL_GetError() << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, SDL_WINDOW_SHOWN);

    if (m_window == nullptr)
    {
        std::cout << "Failed to open Window " << SDL_GetError() << std::endl;
        return false;
    }

    // Second argument is a driver related argument.
    // -1 tells SDL to use the first one to support the selected flags.
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (m_renderer == nullptr)
    {
        std::cout << "Failed to init Renderer " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() != 0)
    {
    	std::cout << "TTF_Init failed" << std::endl;
    	return false;
    }

    SDL_SetRenderDrawColor(m_renderer, 0x00, 0xFF, 0xFF, 0xFF);

    // Start up GameObjectManager and spawnPlayer.
    Vec2f spawnPos{400,300};
    goManager.spawnPlayer(spawnPos);
    goManager.createRenderText("Testerino", "Assets/slkscr.ttf", SDL_Color{255, 0, 0, 0}, m_renderer, 100, 10, 10, 200, 20);

    // Movement bindings.
    keyBindings.bind(Action::MoveUp, SDL_SCANCODE_W);
    keyBindings.bind(Action::MoveDown, SDL_SCANCODE_S);
    keyBindings.bind(Action::MoveLeft, SDL_SCANCODE_A);
    keyBindings.bind(Action::MoveRight, SDL_SCANCODE_D);

    // Shooting bindings.
    keyBindings.bind(Action::ShootUp, SDL_SCANCODE_UP);
    keyBindings.bind(Action::ShootDown, SDL_SCANCODE_DOWN);
    keyBindings.bind(Action::ShootLeft, SDL_SCANCODE_LEFT);
    keyBindings.bind(Action::ShootRight, SDL_SCANCODE_RIGHT);

    m_clock.start();

    return true;
}

// Game.update()
// Querrys key presses and returns true if the game should be quit
// Otherwise false will be returned
bool Game::update()
{
    bool shouldQuit = false;

    SDL_Event ev;

    while (SDL_PollEvent(&ev))
    {
        if( ev.type == SDL_QUIT )
        {
            shouldQuit = true;
        }
    }

    // Prefered over event based approached since it doesnt seem to cancel out keyholds when interrupted by other presses
    const Uint8* keystates = SDL_GetKeyboardState(nullptr);
    std::vector<Action> playerActions {};

    keyBindings.getKeysPressed(keystates, playerActions);

    goManager.updateAll(m_clock.restart(), playerActions);

    if (goManager.checkCollisions()) return true;

    return shouldQuit;
}

// Game.clear()
// Clears the render surface
void Game::clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_RenderClear( m_renderer );
}

// Game.render()
// Draws the games state on to the surface and displays is
void Game::render()
{
    clear();

    goManager.renderAll(m_renderer);

    SDL_RenderPresent( m_renderer );
}
