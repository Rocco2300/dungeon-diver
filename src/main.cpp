#include "Game.h"

int main()
{
    // Suppres false Failed to set DirectInput device axis mode: 1 error 
    sf::err().rdbuf(NULL);

    Game game;
    game.run();
    return 0;
}