PROG = parser
CC = g++
LEX = flex
YACC = bison
CFLAGS = -Wall -std=c++11

$(PROG): parser.tab.o lex.yy.o
	$(CC) $(CFLAGS) -o $@ $^
parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
parser.tab.cpp parser.tab.hpp	 : parser.ypp
	$(YACC) -d --debug --verbose $<
lex.yy.o: lex.yy.c parser.tab.hpp
	$(CC) $(CFLAGS) -c -o $@ $<
lex.yy.c: lex.lex
	$(LEX) $<

.PHONY: clean

clean:
	-rm *~ lex.yy.c parser.tab.cpp parser.tab.hpp parser.output *.o $(PROG)
