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

.PHONY: all dbg prf clean cleanlib

all: CFLAGS += -O3
all: | release
all: release/$(FINAL)

dbg: CFLAGS += -Og
dbg: | debug
dbg: debug/$(FINAL)

prf: CFLAGS += -pg
prf: | profile
prf: profile/$(FINAL)

cleanlib:
	rm -f debug/Engine3D.a release/Engine3D.a profile/Engine3D.a
clean: cleanlib
	rm -f debug/*.o release/*.o profile/*.o

debug/$(FINAL): $(DBGOBJFILES)
	ar rcs $@ $^
release/$(FINAL): $(RELOBJFILES)
	ar rcs $@ $^
profile/$(FINAL): $(PRFOBJFILES)
	ar rcs $@ $^

debug:
	mkdir -p debug
release:
	mkdir -p release
profile:
	mkdir -p profile

debug/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
release/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
profile/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
