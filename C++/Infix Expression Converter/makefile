OBJECTS = main.o class.o
HEADERS = class.h

program3: $(OBJECTS)
	g++ $^ -o CS216PA4

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@

clean:
	rm -f *.o CS216PA4

