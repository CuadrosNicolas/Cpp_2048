CC = g++
CFLAGS = -Wall -std=c++1z -g
EXEC_NAME = bin/game
OBJECTS = bin/objects/
DIR = bin bin/objects
OBJ_FILES =  $(OBJECTS)main.o $(OBJECTS)jeu.o

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)


$(EXEC_NAME) : $(DIR) $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(EXEC_NAME) $(OBJ_FILES) -lsfml-graphics -lsfml-window -lsfml-system

$(OBJECTS)%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< -lsfml-graphics -lsfml-window -lsfml-system

$(DIR) :
	mkdir bin
	mkdir bin/objects