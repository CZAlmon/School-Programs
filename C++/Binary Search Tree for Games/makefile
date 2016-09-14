OBJECTS = program3.o elements.o search_tree.o
HEADERS = elements.h search_tree.h

program3: $(OBJECTS)
	g++ $^ -o CS216PA3

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -f *.o CS216PA3

