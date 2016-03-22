#include "stdafx.h"
#include "Game.h"

#ifdef __EMSCRIPTEN__
#include "Emscripten.h"

// Used when compiling for emscripten, to conform with requestAnimationFrame()
void emscriptenLoop(void* gameInstance)
{
    Game* game = (Game*)gameInstance;
    game->update();
    game->render();
}

#endif

int main(int argc, char const *argv[])
{

    Game game{1600,900};

    if (!game.init("Test"))
    {
        std::cout << "Game init failed" << std::endl;
        return -1;
    };

    bool gameShouldEnd = false;

    #ifdef __EMSCRIPTEN__

    emscripten_set_main_loop_arg(emscriptenLoop, &game, 0, 1);

    #else

    while (!gameShouldEnd)
    {
        gameShouldEnd = game.update();
        game.render();
    }

    #endif

    return 0;
}
