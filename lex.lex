%option noyywrap
%option nounput
%option noinput

%option yylineno
%{
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string> 
#include <vector>
#include "ast.hpp"
using namespace std;
#include "parser.tab.hpp"


#define ISPIS //ECHO;

void smanji_slova(string &s) {
  for (auto &c: s)
      c = tolower(c);
}

%}


ID      [љњертзуиопшђасдфгхјклчћжжџцвбнмЉЊЕРТЗУИОПШЂАСДФГХЈКЛЧЋЖЖЏЦВБНМ_][љњертзуиопшђасдфгхјклчћжжџцвбнмЉЊЕРТЗУИОПШЂАСДФГХЈКЛЧЋЖЖЏЦВБНМ0-9_]+

%%

int                           {ISPIS; return int_token; }
double                        {ISPIS; return double_token; }
if                            {ISPIS; return if_token; }
else                          {ISPIS; return else_token; }
while                         {ISPIS; return while_token; }
print                         {ISPIS; return print_token; }
extern                        {ISPIS; return extern_token; }


[a-zA-Z_][a-zA-Z0-9_]*        {ISPIS;   yylval.s = new string(yytext);
                                        smanji_slova(*(yylval.s));
                                        return id_token; }
#.*                           {ISPIS; }                                        
[0-9]+                        {ISPIS; yylval.i=atoi(yytext); return numI_token; }
([0-9]+\.[0-9]+)              {ISPIS; yylval.d=atof(yytext); return numD_token; }

\".*\"                        {ISPIS; yylval.s = new string(yytext); return string_token; }
[@<>,+/*():=!$|'-\[\]{}]      {ISPIS; return *yytext;}

[ \t\n]                       {ISPIS; }
 .                            { std::cerr<<"Leksicka greska: Neprepoznat karakter"<<yytext<<std::endl;
                                exit(EXIT_FAILURE); }

%%

