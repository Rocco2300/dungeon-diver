# Dungeon diver

## Overview

This is a work in progress game in which you have to find as much treasure as possible by going in the depth of a
treacherous dungeon, only the strongest survive.

### Disclaimer:

The game is inspired by the series of [LazyDevs](https://www.youtube.com/c/LazyDevs) on the game PorkLike, at the moment
some of the sprites are inspired heavily by his game, that will change with time as I start working on the graphics.

## Screenshots

![Game](./game.png)

## Dependencies

- mingw32-make \ make
- cmake
- sfml (installed with bat files)

## How to build

The only supported platform for the install script is windows, you can also install on linux, but you will have to
manually build SFML.

You can install the sfml library using the bat file in the source dir. Also you can modify it, if you are using gnu
win32 make instead of mingw32-make, or for any other reason.

```
cd dungeon-diver
./install.bat
```

Then you will be able to generate the build files, and build the project:

```
cd build
cmake ..
cmake --build .
```

Note: you should be able to use any generator with cmake (-G).

## Working on

- [X] Add death
- [ ] User interface
    - [X] Add ui components
    - [ ] Main Menu
    - [ ] Settings Menu
    - [X] HP UI
    - [X] Death screen
    - [X] Animate inventory and ui
- [ ] Better enemy ai (pathfinding)
    - [X] Stop enemies from running over eachother
    - [X] Treat entities as obstacles in pathfinding
- [X] Inventory and items
- [ ] Refactor the map generator and finish it
- [ ] Visual effects and juice
    - [ ] UI effects
    - [X] Hit effects for enemies
    - [ ] Fog of war and light
- [X] State management
- [ ] General refactoring
    - [X] Refactoring the game and world classes
    - [X] "Refactor" project directory structure
    - [ ] Improve attacking by using an "event manager"
    - [ ] Implement game manager to keep track of damage and items?
- [X] Improve turn taking
