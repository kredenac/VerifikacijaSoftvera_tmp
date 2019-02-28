// A Bison parser, made by GNU Bison 3.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

// //                    "%code top" blocks.
#line 13 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.y" // lalr1.cc:425

    #include "lexer.h"

    static yy::parser::symbol_type yylex(yy::Lexer &lexer)
    {
        return lexer.get_next_token();
    }

#line 47 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.cpp" // lalr1.cc:425


// First part of user prologue.
#line 26 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.y" // lalr1.cc:431

#include <iostream>
#include <string>
#include <map>
#include "TestFinder.h"

int last_id_line;
int beginL;

void yy::parser::error(const std::string &message)
{
    std::cerr << "Error: " << message << std::endl;
}


#line 67 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.cpp" // lalr1.cc:431

#include "parser.hpp"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 147 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.cpp" // lalr1.cc:512

  /// Build a parser object.
  parser::parser (yy::Lexer &lexer_yyarg, const std::string &path_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      path (path_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.type_get ())
    {
      case 16: // ID
      case 27: // Id
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if defined __cplusplus && 201103L <= __cplusplus
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.type_get ())
    {
      case 16: // ID
      case 27: // Id
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if defined __cplusplus && __cplusplus < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 16: // ID
      case 27: // Id
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if defined __cplusplus && 201103L <= __cplusplus
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (lexer));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 16: // ID
      case 27: // Id
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 26:
#line 113 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.y" // lalr1.cc:906
    { last_id_line = lexer.line_num; yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 514 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.cpp" // lalr1.cc:906
    break;

  case 27:
#line 114 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.y" // lalr1.cc:906
    { last_id_line = lexer.line_num; yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 520 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.cpp" // lalr1.cc:906
    break;

  case 33:
#line 129 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.y" // lalr1.cc:906
    { TestFinder::testFunctionNames[yystack_[2].value.as< std::string > ()] = lexer.line_num; }
#line 526 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.cpp" // lalr1.cc:906
    break;

  case 34:
#line 131 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.y" // lalr1.cc:906
    { if (TestFinder::testFunctionNames.find(yystack_[1].value.as< std::string > ()) == TestFinder::testFunctionNames.cend())
                TestFinder::testFunctionNames[yystack_[1].value.as< std::string > ()] = lexer.line_num;
              beginL = last_id_line;
            }
#line 535 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.cpp" // lalr1.cc:906
    break;

  case 35:
#line 134 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.y" // lalr1.cc:906
    { TestFinder::testovi.push_back(TestCase(yystack_[3].value.as< std::string > (), path, TestFinder::testFunctionNames[yystack_[3].value.as< std::string > ()], beginL, lexer.line_num)); }
#line 541 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.cpp" // lalr1.cc:906
    break;


#line 545 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.cpp" // lalr1.cc:906
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -10;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
     -10,    28,    31,   -10,    14,   -10,   -10,   -10,   -10,   -10,
      22,   -10,   -10,   -10,   -10,   -10,   -10,    29,   -10,     7,
      -1,    29,    34,   -10,    26,   -10,    35,   -10,    31,    13,
      22,    22,    18,    22,   -10,    29,    43,   -10,    46,    45,
      29,    29,   -10,    51,    29,   -10,    -6,    49,    -5,   -10,
      19,    22,    22,   -10,    29,   -10,   -10,    47,    29,    29,
      31,    31,    31,   -10
  };

  const unsigned char
  parser::yydefact_[] =
  {
       4,     0,     2,     1,     0,    10,    11,     4,    15,    14,
       0,    27,     3,     5,     7,     8,     6,    13,     9,     0,
       0,    32,     0,     4,     0,    12,    34,    26,    18,     0,
       0,     0,     0,     0,    33,    31,     0,    29,    29,     0,
      24,    25,     4,     0,    30,    35,     0,     0,     0,    16,
       0,     0,     0,     4,    28,     4,     4,     0,    22,    23,
      19,    21,    20,    17
  };

  const signed char
  parser::yypgoto_[] =
  {
     -10,   -10,     0,   -10,   -10,    27,   -10,   -10,    20,   -10,
      -9,    30,   -10,   -10,   -10
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     1,    28,    12,    13,    14,    15,    16,    29,    32,
      17,    46,    26,    18,    36
  };

  const unsigned char
  parser::yytable_[] =
  {
       2,    21,     4,     5,     6,    53,    56,    20,     7,    25,
      11,    11,     8,     9,    10,    11,    23,    35,    24,    37,
      38,    40,    41,    39,    44,    37,    38,    42,     3,    57,
      19,    43,    30,    31,     4,     5,     6,    54,    11,    54,
       7,    22,    58,    59,     8,     9,    10,    11,    33,    34,
      27,    11,     7,    60,    47,    61,    62,    51,    52,    49,
      55,    63,    50,    45,     0,     0,     0,     0,    48
  };

  const signed char
  parser::yycheck_[] =
  {
       0,    10,     3,     4,     5,    11,    11,     7,     9,    10,
      16,    16,    13,    14,    15,    16,     9,    26,    11,     6,
       7,    30,    31,    10,    33,     6,     7,     9,     0,    10,
      16,    13,     6,     7,     3,     4,     5,    46,    16,    48,
       9,    12,    51,    52,    13,    14,    15,    16,    13,    14,
      16,    16,     9,    53,     8,    55,    56,     6,     7,    14,
      11,    14,    42,    36,    -1,    -1,    -1,    -1,    38
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    18,    19,     0,     3,     4,     5,     9,    13,    14,
      15,    16,    20,    21,    22,    23,    24,    27,    30,    16,
      19,    27,    12,     9,    11,    10,    29,    16,    19,    25,
       6,     7,    26,    13,    14,    27,    31,     6,     7,    10,
      27,    27,     9,    13,    27,    22,    28,     8,    28,    14,
      25,     6,     7,    11,    27,    11,    11,    10,    27,    27,
      19,    19,    19,    14
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    17,    18,    19,    19,    20,    20,    20,    20,    20,
      21,    21,    22,    23,    23,    23,    24,    24,    25,    25,
      25,    25,    26,    26,    26,    26,    27,    27,    28,    28,
      29,    29,    29,    30,    31,    30
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     6,     8,     1,     5,
       5,     5,     4,     4,     2,     2,     3,     1,     2,     0,
       3,     2,     0,     4,     0,     5
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "END", "error", "$undefined", "CLASS", "INCLUDE_QT_TEST",
  "PREPROCESSOR", "MODIFIER", "PRIVATE", "Q_SLOTS", "OVZAGRADA",
  "ZVZAGRADA", "DVOTACKA", "DVEDVOTACKE", "ZAPETA", "TACKAZAPETA", "VOID",
  "ID", "$accept", "Program", "NizNaredbi", "Naredba", "Pretprocesor",
  "Blok", "Skip", "DefinicijaTipa", "NizDeklaracijaUTipu",
  "NizNasledjivaja", "Id", "NizID", "NizArgumenata", "Test", "$@1", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,    62,    62,    66,    67,    71,    72,    73,    74,    75,
      79,    80,    84,    88,    89,    90,    94,    95,    99,   100,
     101,   102,   106,   107,   108,   109,   113,   114,   118,   119,
     123,   124,   125,   129,   131,   130
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 862 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.cpp" // lalr1.cc:1217
#line 137 "/home/dimitrije/Documents/VS/redundant-test-cases/src/rtc/parser.y" // lalr1.cc:1218

