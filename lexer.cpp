#include <iostream>
#include <cctype>

#include "lexer.h"
#include "error.h"


	Lexer::Token_value Lexer::curr_tok;
	double Lexer::number_value;
	std::string Lexer::string_value;

	Lexer::Token_value Lexer::get_token()
{
	char ch;

	do {
		if(!std::cin.get(ch)) return curr_tok = END;
	} while (ch!='\n' && isspace(ch));

	switch (ch) {
	case 0:
		return END;
	case ';':
	case '\n':
		return curr_tok=PRINT;
	case '*':
	case '/':
	case '+':
	case '-':
	case '(':
	case ')':
	case '=':
		return curr_tok=Token_value(ch);
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	case '.':
        std::cin.putback(ch);
		std::cin >> number_value;

		return curr_tok=NUMBER;
	default:			// NAME, NAME =, or error
		if (isalpha(ch)) {
			string_value = ch;
			while (std::cin.get(ch) && isalnum(ch))
				string_value += ch;

            std::cin.putback(ch);
			return curr_tok=NAME;
		}
		throw Error::Syntax_error("bad token");
	}
}
