all: main

main: RayCasting.o vector.o
	g++ RayCasting.o vector.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -std=c++20

RayCasting.o: RayCasting.cpp
	g++ -c RayCasting.cpp

vector.o: vector.cpp
	g++ -c vector.cpp

clean:
	rm -rf *.o main

