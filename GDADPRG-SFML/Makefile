# Replace this with the path you get from `brew info sfml`
SFML_PATH = /opt/homebrew/opt/sfml

# Replace "src" with the name of the folder where all your cpp code is
cppFileNames := $(shell find ./src -type f -name "*.cpp")

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -I$(SFML_PATH)/include
LDFLAGS = -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: compile

compile:
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(cppFileNames) -o bin/main $(LDFLAGS)
