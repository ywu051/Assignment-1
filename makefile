CC = g++
CC_FLAGS = -Wall -ansi -Werror -pedantic -std=c++11
EXEC = rshell
DIR = src
SOURCES = src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXEDIR = bin

all : $(EXEDIR) $(EXEDIR)/$(EXEC)

$(EXEDIR) : 
	mkdir $(EXEDIR)	

$(EXEDIR)/$(EXEC) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEDIR)/$(EXEC)

$(DIR)/%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@ 

clean:
	rm -f $(EXEC) $(OBJECTS) 

