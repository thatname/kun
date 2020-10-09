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


	// (*grammar)[startRuleName].enablePackratParsing = true;
	// std::shared_ptr<peg::Ast> ast;
	// bool success = parser.parse(R"~(class p{int t;};)~", ast);
	// if (success)
	// {
	// 
	// }
}