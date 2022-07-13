all : programme
programme : main.o
	g++ main.o -o programme
main.o : main.cpp
	g++ -c main.cpp