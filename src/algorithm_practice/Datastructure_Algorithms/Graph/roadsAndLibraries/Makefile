CC=g++
PROGRAMS=main test2.in
CFLAGS= -g
all: $(PROGRAMS)

main: main.cpp
	$(CC) $^ -o $@ $(CFLAGS)

test2.in:
	curl https://domfarolino.com/large-assets/test2.in --output test2.in


clean:
	rm -r $(PROGRAMS) *.dSYM
