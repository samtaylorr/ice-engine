#This Makefile assumes a structure of:
# |/build
# |/lib
# |____*.cpp
# |/include
# |____*.h

#OBJS specifies which files to compile as part of the project
OBJS := $(wildcard lib/*.cpp)

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Iinclude makes sure the "include/" directory is compiled 
COMPILER_FLAGS = -w -Iinclude -Iinclude/utils -Iinclude/ice

#LINKER_FLAGS specifies the libraries we're linking against
# Add -lSDL2_image for SDL2_image, -lSDL2_ttf for SDL_tff etc.
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
# change "mygame" if you wish to have a seperate name
OBJ_NAME = mygame

#This is the target that compiles our executable
all	:	$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)

debug :	$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -g
	gdb ./a.out
	run
	
#run make all in the same directory as this Makefile