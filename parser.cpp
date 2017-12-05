#include "parser_impl.h"
#include "table.h"

double Parser::prim(bool get)		// handle primaries
{
	if (get) get_token();

	switch (curr_tok) {
	case Lexer::NUMBER:	// floating point constant
		get_token();
		return number_value;
	case Lexer::NAME:
	{	double& v = table[string_value];
  		if (get_token() == ASSIGN) v = expr(1);
  		return v;
	}
	case Lexer::MINUS:		// unary minus
		return -prim(1);
	case Lexer::LP:
	{	double e = expr(1);
		if (curr_tok != RP) throw Error::Syntax_error("`)' expected");
		get_token();			  // eat ')'
		return e;
	}
	case Lexer::END:
		return 1;
	default:
		throw Error::Syntax_error("primary expected");
	}
}

double Parser::term(bool get)		// multiply and divide
{
	double left = prim(get);

	for (;;)
		switch (curr_tok) {
		case Lexer::MUL:
			left *= prim(true);
			break;
		case Lexer::DIV:
			if (double d = prim(true)) {
				left /= d;
				break;
			}
			throw Error::Zero_divide();
		default:
			return left;
		}
}

double Parser::expr(bool get)		// add and subtract
{
	double left = term(get);

	for(;;)
		switch (curr_tok) {
		case Lexer::PLUS:
			left += term(true);
			break;
		case Lexer::MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
}
