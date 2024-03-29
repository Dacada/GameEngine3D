SRCDIR = src
INCDIR = include

CC = gcc
CFLAGS = -I$(INCDIR) -Wall -Wextra -Werror -std=gnu11 -Wformat\
         -Wformat-security -D_FORTIFY_SOURCE=2 -DENGINE3D_RES_PATH="\"Engine3D/res/"\"\
				 -DENGINE3D_USE_ES_SHADERS

SRCFILES = $(wildcard $(SRCDIR)/*.c)
INCFILES = $(wildcard $(INCDIR)/*.h)
DBGOBJFILES = $(patsubst $(SRCDIR)/%, debug/%, $(SRCFILES:.c=.o))
RELOBJFILES = $(patsubst $(SRCDIR)/%, release/%, $(SRCFILES:.c=.o))
PRFOBJFILES = $(patsubst $(SRCDIR)/%, profile/%, $(SRCFILES:.c=.o))

FINAL = Engine3D.a

.PHONY: all dbg clean cleanlib

all: CFLAGS += -O3
all: | release
all: release/$(FINAL)

dbg: CFLAGS += -Og -DDEBUG -fsanitize=address -fsanitize=undefined -fsanitize=leak -fno-omit-frame-pointer
dbg: | debug
dbg: debug/$(FINAL)

cleanlib:
	rm -f debug/Engine3D.a release/Engine3D.a profile/Engine3D.a
clean: cleanlib
	rm -f debug/*.o release/*.o profile/*.o

debug/$(FINAL): $(DBGOBJFILES)
	ar rcs $@ $^
release/$(FINAL): $(RELOBJFILES)
	ar rcs $@ $^

debug:
	mkdir -p debug
release:
	mkdir -p release

debug/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
release/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
