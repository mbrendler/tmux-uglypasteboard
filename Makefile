
all: libuglypasteboard.a uglypasteboard

pasteboard.o: pasteboard.c pasteboard.h
	cc -o pasteboard.o -c pasteboard.c

libuglypasteboard.a: pasteboard.o
	ar rcs libuglypasteboard.a pasteboard.o

main.o: main.c pasteboard.h
	cc -o main.o -c main.c

uglypasteboard: pasteboard.o main.o
	cc -framework Carbon -o uglypasteboard pasteboard.o main.o

clean:
	rm libuglypasteboard.a
	rm *.o
	rm uglypasteboard
