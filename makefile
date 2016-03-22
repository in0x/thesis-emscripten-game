#Files to be compiled
FILES = *.cpp

#Name of the executable to be produced
EXEC_NAME = -o triangle

#Compiler to be used
COMP = /usr/bin/g++

#Compiler Flags
COMPILER_F = -std=c++11 #-w

#Linker Flags
LINKER_F = -I/usr/local/include/SDL2  -lSDL2_gfx -lSDL2_ttf  -lSDL2

all:
	$(COMP) $(FILES) $(COMPILER_F) $(LINKER_F) $(EXEC_NAME)
