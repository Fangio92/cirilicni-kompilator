PROG = parser
CC = g++
LEX = flex
YACC = bison
CFLAGS = -Wall -std=c++11  -g 

$(PROG): parser.tab.o lex.yy.o izraz.o naredba.o
	$(CC) $(CFLAGS) -o $@ $^
parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
parser.tab.cpp parser.tab.hpp	 : parser.ypp
	$(YACC) -d --debug --verbose $<
lex.yy.o: lex.yy.c parser.tab.hpp
	$(CC) $(CFLAGS) -c -o $@ $< -Wno-sign-compare
lex.yy.c: lex.lex
	$(LEX) $<
izraz.o: classes/izraz.cpp classes/izraz.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
naredba.o: classes/naredba.cpp classes/naredba.hpp classes/izraz.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	-rm *~ lex.yy.c parser.tab.cpp parser.tab.hpp parser.output *.o $(PROG)
