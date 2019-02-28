%{
#include <string>
#include "lexer.h"
#include "parser.hpp"

#define yyterminate() yy::parser::make_END();
%}

%option c++
%option nodefault
%option noinput
%option nounput
%option noyywrap
%option yyclass="Scanner"

id [a-zA-Z_][a-zA-Z_0-9]*

%x komentar

%%
"/*" BEGIN(komentar);
<komentar>[^*\n]*
<komentar>"*"+[^*/\n]*
<komentar>\n ++line_num;
<komentar>"*"+"/" BEGIN(INITIAL);
"class"|"struct" return yy::parser::make_CLASS();
"#[ \t]*include"[ \t]*"<QtTest>"[ \t]*\r?\n { ++line_num; return yy::parser::make_INCLUDE_QT_TEST(); }
"#"[^\n]*\n { ++line_num; return yy::parser::make_PREPROCESSOR(); }
"public"|"protected" return yy::parser::make_MODIFIER();
"private" return yy::parser::make_PRIVATE();
"Q_SLOTS" return yy::parser::make_Q_SLOTS();
"void" return yy::parser::make_VOID();
"::" return yy::parser::make_DVEDVOTACKE();
{id} { return yy::parser::make_ID(yytext); }
":" return yy::parser::make_DVOTACKA();
"," return yy::parser::make_ZAPETA();
"{" return yy::parser::make_OVZAGRADA();
"}" return yy::parser::make_ZVZAGRADA();
";" return yy::parser::make_TACKAZAPETA();
[ \t]
\n ++line_num;
<<EOF>> return yy::parser::make_END();
.

%%
