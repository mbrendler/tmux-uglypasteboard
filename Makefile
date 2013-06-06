UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
PASTEBOARD_SOURCE := pasteboard_x.c
else
PASTEBOARD_SOURCE := pasteboard.c
LDFLAGS := "-framework Carbon"
endif

all: libuglypasteboard.a uglypasteboard

pasteboard.o: $(PASTEBOARD_SOURCE) pasteboard.h
	cc -Wall $(CFLAGS) -o pasteboard.o -c $(PASTEBOARD_SOURCE)

libuglypasteboard.a: pasteboard.o
	ar rcs libuglypasteboard.a pasteboard.o

main.o: main.c pasteboard.h
	cc -Wall $(CFLAGS) -o main.o -c main.c

uglypasteboard: pasteboard.o main.o
	cc $(LDFLAGS) -o uglypasteboard pasteboard.o main.o

clean:
	rm -f libuglypasteboard.a
	rm -f *.o
	rm -f uglypasteboard
