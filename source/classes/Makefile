CC=g++
CFLAGS=-Wall -std=c++11

pseudokod: lex.yy.o parser.tab.o izraz.o naredba.o
	$(CC) $(CFLAGS) -o $@ $^
parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<
lex.yy.o: lex.yy.c parser.tab.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
lex.yy.c: lexer.lex
	flex $<
izraz.o: izraz.cpp izraz.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
naredba.o: naredba.cpp naredba.hpp izraz.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf *~ *tab* lex.yy.* *.o pseudokod *.output

