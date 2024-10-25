#This Makefile assumes a structure of:
# |/build
# |/lib
# |____*.cpp
# |/include
# |____*.hpp
# etc.

#OBJS specifies which files to compile as part of the project
OBJS := $(shell find lib/ -type f -name '*.cpp')

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Iinclude makes sure the "include/" directory is compiled 
COMPILER_FLAGS = -w -Iinclude

#LINKER_FLAGS specifies the libraries we're linking against
# Add -lSDL2_image for SDL2_image, -lSDL2_ttf for SDL_tff etc.
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
# change "mygame" if you wish to have a seperate name
OBJ_NAME = mygame

#This is the target that compiles our executable
build:	$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

# this builds our executable and then runs it
run	:	$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)

# this debugs the program uses a new build with -g
debug :	$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -g
	gdb ./a.out
	run

# This uses valgrind to detect leaks
memleaks:	$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	valgrind --track-origins=yes --log-file=valgrind-out.txt ./$(OBJ_NAME) $(OBJ_NAME)

# This uses valgrind to detect leaks and shows all leaks (including LVM)
memleaks_full:	$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out-full.txt ./$(OBJ_NAME) $(OBJ_NAME)