%option noyywrap
%option nounput
%option yylineno
%{
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include "classes/naredba.hpp"
#include "classes/izraz.hpp"
#include <vector>

#include "parser.tab.hpp"

#define ISPIS /*ECHO;*/

void smanji_slova(string &s) {
  for (auto &c: s)
      c = tolower(c);
}

%}


ID      [љњертзуиопшђасдфгхјклчћжжџцвбнмЉЊЕРТЗУИОПШЂАСДФГХЈКЛЧЋЖЖЏЦВБНМ_][љњертзуиопшђасдфгхјклчћжжџцвбнмЉЊЕРТЗУИОПШЂАСДФГХЈКЛЧЋЖЖЏЦВБНМ0-9_]+

%%

цео                          { ISPIS; return CEO; }
ако                          { ISPIS; return AKO; }
онда                         { ISPIS; return ONDA; }
врати                        { ISPIS; return VRATI; }
иначе                        { ISPIS; return INACE; }

{ID}                         { ISPIS;   yylval.s = new string(yytext);
                                        smanji_slova(*(yylval.s));
                                        return ID; }
[0-9]+                       { ISPIS; return NUM; }
[<>,+/*():=!$|'-\[\]{}]      { ISPIS; return *yytext;}

[ \t\n]                      { ISPIS;  }
.                            {
                               std::cerr<<"Leksicka greska: Neprepoznat karakter"<<yytext<<std::endl;
                               exit(EXIT_FAILURE);
                             }

%%

