
PROGRAMS = tjdtodate unixtodate datetounix mjdtodate datetomjd wintounix

OBJECTS = $(PROGRAMS:=.o)
MANPAGES = $(PROGRAMS:=.1)

DESTBIN = $(HOME)/bin
DESTMAN = $(HOME)/man/man1

all: $(PROGRAMS)
	$(MAKE) man

man: $(MANPAGES)

$(MANPAGES): $(PROGRAMS)
	pod2man -c "Date utilities" $(@:.1=.c) $@

tjdtodate: tjdtodate.c
	gcc -o tjdtodate -g -Wall tjdtodate.c

unixtodate: unixtodate.c
	gcc -o unixtodate -g -Wall unixtodate.c

datetounix: datetounix.c
	gcc -o datetounix -g -Wall datetounix.c

mjdtodate: mjdtodate.c
	gcc -o mjdtodate -g -Wall mjdtodate.c

datetomjd: datetomjd.c
	gcc -o datetomjd -g -Wall datetomjd.c

wintounix: wintounix.c
	gcc -o wintounix -g -Wall wintounix.c

install:
	test -d $(DESTBIN) || mkdir -p $(DESTBIN)
	cp $(PROGRAMS) $(DESTBIN)
	test -f $(DESTMAN) || mkdir -p $(DESTMAN)
	cp $(MANPAGES) $(DESTMAN)

clean:
	rm -f $(PROGRAMS)
	rm -f $(OBJECTS)
	rm -f $(MANPAGES)
