%option noyywrap
%option nounput

%{
#include <iostream>
#include "parser.tab.hpp"

%}


ID      [љњертзуиопшђасдфгхјклчћжжџцвбнмЉЊЕРТЗУИОПШЂАСДФГХЈКЛЧЋЖЖЏЦВБНМ][љњертзуиопшђасдфгхјклчћжжџцвбнмЉЊЕРТЗУИОПШЂАСДФГХЈКЛЧЋЖЖЏЦВБНМ0-9]+

%%

цео                          { return CEO; }
ако                          { return AKO; }
онда                         { return ONDA; }
врати                        { return VRATI; }

{ID}                         { return ID; }
[0-9]+                       { return NUM; }
[<>,+*():=!$|'-\[\]{}]       { return *yytext;}

[ \t\n]          {  }
.                {
                   std::cerr<<"Leksicka greska: Neprepoznat karakter"<<yytext<<std::endl;
                    exit(EXIT_FAILURE);
                 }

%%

