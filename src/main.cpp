#include "Application.h"

#include <random>

int main()
{
    srand(time(nullptr));
    // Suppres false Failed to set DirectInput device axis mode: 1 error 
    sf::err().rdbuf(nullptr);

    Application application;
    application.run();
    return 0;
}
