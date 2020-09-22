// MIT License
// 
// Copyright (c) 2020 ZHOU He
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "peglib.h"
#include <iostream>
/*
	MULTITIVE_EXPRESSION  <-  PREFIX_EXPRESSION ( MULTITIVE_OPERATOR PREFIX_EXPRESSION)*
	 ADDITIVE_EXPRESSION  <-  MULTITIVE_EXPRESSION ( ADDITIVE_OPERATOR MULTITIVE_EXPRESSION )*
		SHIFT_EXPRESSION  <-  ADDITIVE_EXPRESSION (SHIFT_OPERATOR ADDITIVE_EXPRESSION)*
   RELATIONAL_EXPRESSION  <-  SHIFT_EXPRESSION (RELATIONAL_OPERATOR SHIFT_EXPRESSION)*
	 EQUALITY_EXPRESSION  <-  RELATIONAL_EXPRESSION (EQUALITY_OPERATOR RELATIONAL_EXPRESSION)*
  BITWISE_AND_EXPRESSION  <-  EQUALITY_EXPRESSION (BITWISE_AND_OPERATOR EQUALITY_EXPRESSION)*
  BITWISE_XOR_EXPRESSION  <-  BITWISE_AND_EXPRESSION (BITWISE_XOR_OPERATOR  BITWISE_AND_EXPRESSION)*
   BITWISE_OR_EXPRESSION  <-  BITWISE_XOR_EXPRESSION (BITWISE_OR_OPERATOR  BITWISE_XOR_EXPRESSION)*
  LOGICAL_AND_EXPRESSION  <-  BITWISE_OR_EXPRESSION (LOGICAL_AND_OPERATOR  BITWISE_OR_EXPRESSION)*
   LOGICAL_OR_EXPRESSION  <-  LOGICAL_AND_EXPRESSION (LOGICAL_OR_OPERATOR  LOGICAL_AND_EXPRESSION)*
	   TENARY_EXPRESSION  <-  LOGICAL_OR_EXPRESSION '?'  LOGICAL_OR_EXPRESSION ':'  LOGICAL_OR_EXPRESSION / LOGICAL_OR_EXPRESSION
   ASSIGNMENT_EXPRESSION  <-  TENARY_EXPRESSION ASSIGNMENT_OPERATOR ASSIGNMENT_EXPRESSION / TENARY_EXPRESSION
			  EXPRESSION  <-  ASSIGNMENT_EXPRESSION (',' ASSIGNMENT_EXPRESSION)*
	 ASSIGNMENT_OPERATOR  <-  <('='/ '+='/ '-=' / '*=' / '/=' / '%=' / '&=' / '^=' / '|=' / '<<=' / '>>=')>
		  SHIFT_OPERATOR  <-  <('<<'/'>>')>
	   ADDITIVE_OPERATOR  <-  <[-+]>
	  MULTITIVE_OPERATOR  <-  <[*%/]>
	   EQUALITY_OPERATOR  <-  <( '==' / '!=' )>
	 RELATIONAL_OPERATOR  <-  <('>=' / '<=' / '>' / '<')>
	BITWISE_AND_OPERATOR  <-  !'&&' <'&'>
	BITWISE_XOR_OPERATOR  <-  <'^'>
	 BITWISE_OR_OPERATOR  <-  <'|'>
	LOGICAL_AND_OPERATOR  <-  <'&&'>
	 LOGICAL_OR_OPERATOR  <-  <'||'>
  MEMBER_ACCESS_OPERATOR  <-  <'.' / '->' / '?.' / '?->' / '::'/ '?::'>

*/

int main(int argc, char** argv)
{
	const char grammarText[] = R"~(
            TRANSLATION_UNIT  <-  _ STATEMENT*
                          ~_  <-  [ \t\n\r]*
                         ~__  <-  ![_a-zA-Z0-9] _
             NUMERIC_LITERAL  <-  <[0-9]+('.'[0-9]+)?> IDENTIFIER?_
                      STRING  <-  '"' <('\\"'/[^"])*> '"'_
              STRING_LITERAL  <-  (STRING _)+ IDENTIFIER?_
                  IDENTIFIER  <-  <[_a-zA-Z] [_a-zA-Z0-9]*>__
    # Statements
    
                   STATEMENT  <-  IF_STATEMENT / BLANK_STATEMENT / COMPOUND_STATEMENT / DEFINITION_STATEMENT / EXPRESSION_STATEMENT 
             BLANK_STATEMENT  <-  ';'_
          COMPOUND_STATEMENT  <-  '{'_ STATEMENT* '}'_
        EXPRESSION_STATEMENT  <-  EXPRESSION ';'
                IF_STATEMENT  <-  'if'__'('_ EXPRESSION ')'_ STATEMENT ('else'__ STATEMENT)?
    # Types
                  DEFINITION  <-  VARIABLE_DEFINITION / FUNCTION_DEFINITION
         VARIABLE_DEFINITION  <-  SPECIFIER+ (DECLARATOR (','_ DECLARATOR)*)?
        PARAMETER_DEFINITION  <-  SPECIFIER+ DECLARATOR?
                   SPECIFIER  <-  STORAGE_CLASS __/ QUALIFIER __ / TYPE_SPECIFIER TYPE_POSTFIX*
        DEFINITION_STATEMENT  <-  DEFINITION ';'_
              PARAMETER_LIST  <-  PARAMETER_DEFINITION (','_ PARAMETER_DEFINITION)*
         FUNCTION_DEFINITION  <-  SPECIFIER+ IDENTIFIER '('_ PARAMETER_LIST')'_ ('{'_ STATEMENT* '}'_)?
                  DECLARATOR  <-  IDENTIFIER ('='_ INFIX_EXPRESSION)?
              TYPE_SPECIFIER  <-  NAMED_TYPE __/ NUMERIC_TYPE <[0-9]*> _ / RECORD_TYPE_SPECIFIER #/ TUPLE_TYPE / ENUM_TYPE
                TYPE_POSTFIX  <-  <'*'>_ / <'&'>_ / <'&&'>_ / <'('>_ PARAMETER_LIST')'_ / <'['>_ EXPRESSION ']'_
                NUMERIC_TYPE  <-  'bool' | 'char' | 'uchar' | 'short' | 'ushort' | 'int' | 'uint' | 'long' | 'ulong' |'half' | 'float' | 'double'
                   QUALIFIER  <-  'var' | 'const' | 'volatile' | 'mutable'
             META_CLASS_NAME  <-  'class' | 'union' | 'struct'
       RECORD_TYPE_SPECIFIER  <-  META_CLASS_NAME __ IDENTIFIER '{'_ DEFINITION_STATEMENT* '}'_
               STORAGE_CLASS  <-  'static' | 'extern' | 'auto'
                  NAMED_TYPE  <-  'void' | 'bbb'
                # TUPLE_TYPE  <-  META_CLASS_NAME __ IDENTIFIER __ '('_ TYPE_NAME* ')'_
                #  ENUM_ITEM  <-  IDENTIFIER ('='_ EXPRESSION)? '{'_ DEFINITION_STATEMENT* '}'_
                #  ENUM_TYPE  <-  META_ENUM_NAME IDENTIFIER '{'_ (ENUM_ITEM ','_)* ENUM_ITEM? '}'_
    # Expressions
                  EXPRESSION  <-  INFIX_EXPRESSION (','_ INFIX_EXPRESSION)*
            INFIX_EXPRESSION  <-  PREFIX_EXPRESSION (BINARY_OPERATOR PREFIX_EXPRESSION)* {  precedence 
    R = -= += *= /= %= |= &= ^= R ? L || L && L | L ^ L & L == != L >= <= > < L << >> L + - L * / % }
             BINARY_OPERATOR  <-  < '&&' / '||' / ('>>' / '<<' / [-+*/%|&^<>=!])'='?>_ /  <'?'>_ EXPRESSION ':'_
               UNARY_POSTFIX  <-  <'++' / '--'>_ / <'['>_ EXPRESSION ']'_ / <'('>_ EXPRESSION? ')'_ / <'?'?'.''*'? / '?'?'->''*'? / '::''*'?>_ IDENTIFIER
                UNARY_PREFIX  <-  <'++' / '--' / [-+!~*&]>_
                
          PRIMARY_EXPRESSION  <-  IDENTIFIER / NUMERIC_LITERAL / STRING_LITERAL / '('_ EXPRESSION ')'_
          POSTFIX_EXPRESSION  <-  PRIMARY_EXPRESSION UNARY_POSTFIX*
           PREFIX_EXPRESSION  <-  UNARY_PREFIX PREFIX_EXPRESSION / POSTFIX_EXPRESSION
    
    # Extensions
    
           SYNTAX_STATEMENT   <-  'syntax'__ IDENTIFIER? '{'_ Grammar '}'_';'_
)~";
	peg::Rules rules;
	std::string startRuleName;
	std::vector<peg::Grammar*> oldGrammars = { &peg::ParserGenerator::grammar() };
	auto parser = peg::parser(grammarText, sizeof(grammarText) - 1, rules, [&](size_t line, size_t col, const std::string & error) {
		std::cout << line << ' ' << col << ' ' << error;
	}, &oldGrammars);
	parser.log = [&](size_t line, size_t col, const std::string & error)
	{
		std::cout << line << ' ' << col << ' ' << error;
	};
	parser.enable_packrat_parsing();
	parser.enable_ast();
	// (*grammar)[startRuleName].enablePackratParsing = true;
	std::shared_ptr<peg::Ast> ast;
	bool success = parser.parse(R"~(class p{int t;};)~", ast);
	if (success)
	{

	}
}