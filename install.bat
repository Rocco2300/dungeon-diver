@mkdir lib
@mkdir build
@mkdir lib\bin
@mkdir lib\SFML
@git clone --branch 2.5.1 https://github.com/SFML/SFML.git
@cmake -G "MinGW Makefiles" -S SFML -B build
@mingw32-make -C ./build
@move build\lib\*.a lib\SFML
@move build\lib\*.dll .\lib\bin
@move SFML\include\SFML include
@move SFML\extlibs\bin\x64\openal32.dll .\lib\bin
@rd /q /s build
@rd /q /s SFML
@mkdir build
