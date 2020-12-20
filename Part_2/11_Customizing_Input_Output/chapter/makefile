LINK_TARGET = main.exe
CFLAGS = -Wall
OBJS = main.o punct_stream.o

all: $(LINK_TARGET)
	echo all done

$(LINK_TARGET): $(OBJS)
	 g++ $(CFLAGS) -g -o $@ $^ 

main.o : main.cpp punct_stream.h
	g++ $(CFLAGS) -g -c $<

punct_stream.o : punct_stream.cpp punct_stream.h
	g++ $(CFLAGS) -g -c $<
     
clean:
	 rm *.o $(LINK_TARGET)