#include "Context.h"

#include <random>

int main()
{
    srand(time(NULL));
    // Suppres false Failed to set DirectInput device axis mode: 1 error 
    sf::err().rdbuf(NULL);

    Context gameContext;
    gameContext.run();
    return 0;
}