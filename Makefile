CXX = g++
CXXFLAGS = -g -O2 -Wall -std=c++17
TARGET = a

SRC = src/
OBJSRC = obj/
LIBSRC = lib
INCLSRC = include/

SRCS = $(wildcard $(SRC)*.cpp)
OBJS = $(SRCS:$(SRC)%.cpp=$(OBJSRC)%.o)
DEPS = $(OBJS:$(OBJSRC)%.o=$(BIN)%.d)

.PHONY: all clean install

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -L $(LIBSRC) -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio

$(OBJSRC)%.o: $(SRC)%.cpp
	$(CXX) $(CXXFLAGS) -I $(INCLSRC) -c $< -o $@

install:
	@build.bat
	@install.bat

clean: 
	del /f obj\\*.o
	del /f a.exe