#g++ main.c -IC:\MinGW\include\SDL2 -LC:\MinGW\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o main
#OBJS specifies which files to compile as part of the project

OBJS = main.c


#CC specifies which compiler we're using

CC = g++


#INCLUDE_PATHS specifies the additional include paths we'll need

INCLUDE_PATHS = -IC:\MinGW\include\SDL2


#LIBRARY_PATHS specifies the additional library paths we'll need

LIBRARY_PATHS = -LC:\MinGW\lib


#COMPILER_FLAGS specifies the additional compilation options we're using

# -w suppresses all warnings

# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w -Wl,-subsystem,windows


#LINKER_FLAGS specifies the libraries we're linking against

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2


#OBJ_NAME specifies the name of our exectuable

OBJ_NAME = main


#This is the target that compiles our executable

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)