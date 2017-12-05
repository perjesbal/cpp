#include "parser.h"
#include "error.h"
#include "lexer.h"

#ifndef PARSER_IMPL_H_INCLUDED
#define PARSER_IMPL_H_INCLUDED

namespace Parser {
	double prim(bool get);		// handle primaries
	double term(bool get);		// multiply and divide
	double expr(bool get);		// add and subtract

	using namespace Lexer;
	using namespace Error;
}


#endif // PARSER_IMPL_H_INCLUDED
