LIB = -lGLEW -lGLU -lGL -lm

CC = gcc
CFLAGS = -I../Engine3D/include -Wall -Wextra -Werror -std=gnu11 -Wformat\
         -Wformat-security -D_FORTIFY_SOURCE=2 $(shell pkg-config --cflags glfw3)
LDFLAGS = $(shell pkg-config --static --libs glfw3) $(LIB)

.PHONY: all clean

all: main

clean:
	rm -f $(OBJFILES) main

main: main.c ../Engine3D/Engine3D.a
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) 
