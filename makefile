output: main.o vector.o contact.o contactbst.o
	g++ main.o vector.o contact.o contactbst.o -o output
main.o: main.cpp vector.h contact.h contactbst.h
	g++ -c main.cpp
vector.o: vector.h vector.cpp
	g++ -c vector.cpp
contact.o: contact.cpp contact.h
	g++ -c contact.cpp
contactbst.o: contactbst.cpp contactbst.h
	g++ -c contactbst.cpp
clean:
	rm *.o output