SRCDIR = src
INCDIR = include
OBJDIR = debug

CC = gcc
CFLAGS = -I$(INCDIR) -Wall -Wextra -Werror -std=gnu11 -Wformat\
         -Wformat-security -D_FORTIFY_SOURCE=2

SRCFILES = $(wildcard $(SRCDIR)/*.c)
INCFILES = $(wildcard $(INCDIR)/*.h)
OBJFILES = $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRCFILES:.c=.o))

FINAL = Engine3D.a

.PHONY: all dbg cleanlib

all: OBJDIR = release
all: CFLAGS += -O3
all: | $(OBJDIR)
all: $(FINAL)

dbg: OBJDIR = debug
dbg: CFLAGS += -Og
dbg: | $(OBJDIR)
dbg: $(FINAL)

cleanlib:
	rm -f $(FINAL)
clean: cleanlib
	rm -f $(OBJFILES)

$(FINAL): $(OBJFILES)
	ar rcs $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
