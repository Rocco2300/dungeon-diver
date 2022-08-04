# Dungeon diver

## Overview

This is a work in progress game in which you have to find as much treasure as possible by going in the depth of a treacherous dungeon, only the strongest survive.

### Disclaimer: 

The game is inspired by the series of [LazyDevs](https://www.youtube.com/c/LazyDevs) on the game PorkLike, at the moment some of the sprites are inspired heavily by his game, that will change with time as I start working on the graphics.

## Screenshots

![Game](./game.png)

## Dependencies

- mingw-w64
- cmake
- sfml (installed with bat files)

## How to build

The only supported platform for the moment is windows, you can install the sfml library using the two bat files:

```
cd dungeon-diver
./install.bat
```

Then you can build the binaries using `mingw32-make` and run it `./a`.

## Working on

- [ ] User interface
- [ ] Better enemy ai (pathfinding)
- [ ] Inventory and items
- [ ] Refactor the map generator and finish it
- [ ] Visual effects and juice
    - [ ] UI effects
    - [ ] Hit effects for enemies
    - [ ] Fog of war and light
- [X] State management
- [ ] General refactoring
    - [ ] Refactoring the game and world classes