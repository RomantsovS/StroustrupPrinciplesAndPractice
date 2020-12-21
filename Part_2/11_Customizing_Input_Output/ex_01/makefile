LINK_TARGET = main.exe
CFLAGS = -Wall
OBJS = main.o

all: $(LINK_TARGET)
	echo all done

$(LINK_TARGET): $(OBJS)
	 g++ $(CFLAGS) -g -o $@ $^ 

main.o : main.cpp
	g++ $(CFLAGS) -g -c $<
     
clean:
	 rm *.o $(LINK_TARGET)