CC=clang++
CFLAGS=-g $(shell llvm-config --cxxflags)
LDFLAGS=$(shell llvm-config --ldflags --system-libs --libs)

cirko: lex.yy.o parser.tab.o ast.o
	$(CC) -o $@ $^ $(LDFLAGS)
parser.tab.o: parser.tab.cpp parser.tab.hpp ast.hpp
	$(CC) -Wno-unknown-warning-option $(CFLAGS) -c -o $@ $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v $<
lex.yy.o: lex.yy.c parser.tab.hpp ast.hpp
	$(CC) -Wno-unknown-warning-option $(CFLAGS) -Wno-sign-compare -c -o $@ $<
lex.yy.c: lex.lex
	flex $<
ast.o: ast.cpp ast.hpp
	$(CC) -Wno-unknown-warning-option $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf *~ *tab* lex.yy.* *.o cirko *.output *.dwo *.ll *.out
