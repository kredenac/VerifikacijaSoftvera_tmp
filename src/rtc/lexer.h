#ifndef LEXER_H
#define LEXER_H

#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer yyFlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL yy::parser::symbol_type yy::Lexer::get_next_token()

#include "parser.hpp"

namespace yy {

class Lexer: public yyFlexLexer
{
public:
    Lexer() : line_num(1) {}
    virtual ~Lexer() {}
    virtual yy::parser::symbol_type get_next_token();
private:
    int line_num;
    friend class yy::parser;
};

}

#endif // LEXER_H
