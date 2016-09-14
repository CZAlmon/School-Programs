OBJECTS = Program4.o


Program4: $(OBJECTS)
	g++ $^ -o Program4

%.o: %.cpp $(HEADERS)
	g++ -g -Wall -c $< -o $@

clean:
	rm -f *.o Program4
