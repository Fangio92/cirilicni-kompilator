%option noyywrap
%option nounput
%option yylineno
%{
#include <iostream>
#include "parser.tab.hpp"

#define ISPIS /*ECHO;*/

%}


ID      [љњертзуиопшђасдфгхјклчћжжџцвбнмЉЊЕРТЗУИОПШЂАСДФГХЈКЛЧЋЖЖЏЦВБНМ_][љњертзуиопшђасдфгхјклчћжжџцвбнмЉЊЕРТЗУИОПШЂАСДФГХЈКЛЧЋЖЖЏЦВБНМ0-9_]+

%%

цео                          { ISPIS; return CEO; }
ако                          { ISPIS; return AKO; }
онда                         { ISPIS; return ONDA; }
врати                        { ISPIS; return VRATI; }
иначе                        { ISPIS; return INACE; }


{ID}                         { ISPIS; return ID; }
[0-9]+                       { ISPIS; return NUM; }
[<>,+/*():=!$|'-\[\]{}]      { ISPIS; return *yytext;}

[ \t\n]                      { ISPIS;  }
.                            {
                               std::cerr<<"Leksicka greska: Neprepoznat karakter"<<yytext<<std::endl;
                               exit(EXIT_FAILURE);
                             }

%%

