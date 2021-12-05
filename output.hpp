#ifndef _236360_2_
#define _236360_2_

#include <string>

#define YYSTYPE int

extern char* yytext;
extern int yylineno;
extern int yyleng;
extern int yylex();

namespace output {
    extern const std::string rules[];
    void printProductionRule(const int ruleno);
    void errorLex(const int lineno);
    void errorSyn(const int lineno);
};

#endif
