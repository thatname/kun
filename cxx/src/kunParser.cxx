#include "kunParser.h"
namespace kun
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
	Parser::Parser()
	{
		peg::Rules rules;
		std::string startRuleName;
		std::vector<peg::Grammar*> oldGrammars = { &peg::ParserGenerator::grammar() };
		parser = peg::parser(grammarText, sizeof(grammarText) - 1, rules, [&](size_t line, size_t col, const std::string & error) {
			std::cout << line << ' ' << col << ' ' << error;
			}, &oldGrammars);

		parser.enable_packrat_parsing();
		parser.enable_ast();
	}

	std::shared_ptr<peg::Ast> Parser::parse(const char* fileName, const char* source)
	{
		parser.log = [&](size_t line, size_t col, const std::string & error)
		{
			std::cout << line << ' ' << col << ' ' << error;
		};
		std::shared_ptr<peg::Ast> ast;
		bool success = parser.parse(source, ast);
		if (success)
		{
			return ast;
		}
		return nullptr;
	}

}