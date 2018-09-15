LIB = -lGLEW -lGLU -lGL -lm

CC = gcc
CFLAGS = -I../Engine3D/include -Wall -Wextra -Werror -std=gnu11 -Wformat\
         -Wformat-security -D_FORTIFY_SOURCE=2 $(shell pkg-config --cflags glfw3)
LDFLAGS = $(shell pkg-config --static --libs glfw3) $(LIB)

.PHONY: all dbg clean

all: CFLAGS += -O3
all: | release
all: release/main

dbg: CFLAGS += -Og
dbg: | debug
dbg: debug/main

clean:
	rm -f debug/main release/main

release/main: main.c ../Engine3D/release/Engine3D.a
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
debug/main: main.c ../Engine3D/debug/Engine3D.a
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

debug:
	mkdir -p debug
release:
	mkdir -p release
