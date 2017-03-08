%option noyywrap
%option nounput
%option yylineno
%{
#include <iostream>
#include "parser.tab.hpp"

%}


ID      [љњертзуиопшђасдфгхјклчћжжџцвбнмЉЊЕРТЗУИОПШЂАСДФГХЈКЛЧЋЖЖЏЦВБНМ_][љњертзуиопшђасдфгхјклчћжжџцвбнмЉЊЕРТЗУИОПШЂАСДФГХЈКЛЧЋЖЖЏЦВБНМ0-9_]+

%%

цео                          { std::cout<<yytext; return CEO; }
ако                          { std::cout<<yytext; return AKO; }
онда                         { std::cout<<yytext; return ONDA; }
врати                        { std::cout<<yytext; return VRATI; }
иначе                        { std::cout<<yytext; return INACE; }


{ID}                         { std::cout<<yytext; return ID; }
[0-9]+                       { std::cout<<yytext; return NUM; }
[<>,+/*():=!$|'-\[\]{}]       { std::cout<<yytext; return *yytext;}

[ \t\n]          { ECHO;  }
.                {
                   std::cerr<<"Leksicka greska: Neprepoznat karakter"<<yytext<<std::endl;
                    exit(EXIT_FAILURE);
                 }

%%

