EXEC = Run 
FILE = $(EXEC)
OBJECTC = $(wildcard src/*.cpp) $(wildcard res/*.cpp) main.cpp
CHANGES = $(OBJECTC) 

CFLAGS = -g

# -w wornings -lsdl2 for sdl 
$(EXEC): $(CHANGES)
	rm -f $(EXEC) 
	g++ $(OBJECTC) -w -lSDL2 -o $(FILE)
clean:
	rm -f $(OBJECTO) $(FILE)

run:
	./$(FILE)

rungdb:
	gdb ./$(FILE)

runvalgrind:
	valgrind --leak-check=full ./$(FILE)