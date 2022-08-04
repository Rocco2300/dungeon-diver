@mkdir obj
@mkdir lib
@mkdir build
@git clone --branch 2.5.1 https://github.com/SFML/SFML.git
@cmake -G "MinGW Makefiles" -S SFML -B build
@mingw32-make -C ./build
@move build\lib\*.a lib
@move build\lib\*.dll .
@move SFML\include\SFML include
@move SFML\extlibs\bin\x64\openal32.dll .
@rd /s /q build
@rd /s /q SFML
