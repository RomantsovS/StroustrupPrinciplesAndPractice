all: main.exe

main.exe: calculator02buggy.o
	 g++ -g -o main.exe calculator02buggy.o

calculator02buggy.o: calculator02buggy.cpp
	 g++ -g -c calculator02buggy.cpp
     
clean:
	 rm *.o main.exe
