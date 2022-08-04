# Dungeon diver

This is a work in progress game in which you have to find as much treasure as possible by going in the depth of a treacherous dungeon, only the strongest survive.

## Dependencies

- mingw-w64
- cmake
- sfml (installed with bat files)0

## How to build

The only supported platform for the moment is windows, you can install the sfml library using the two bat files:

```
cd dungeon-diver
./build.bat
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