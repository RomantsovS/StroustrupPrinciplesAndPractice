all: main.exe

main.exe: main.o
	 g++ -g -o main.exe main.o

main.o: main.cpp
	 g++ -g -c main.cpp
     
clean:
	 rm *.o main.exe
