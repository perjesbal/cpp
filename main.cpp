#include <map>
#include <iostream>
#include <strstream>

#include <cctype>
#include <string>
#include <cstring>

#include "error.h"
#include "lexer.h"
#include "parser.h"
#include "table.h"
using namespace std;


int no_of_errors;
std::istream* input;

void skip()
{
no_of_errors++;

	while (*input) {
		char ch;
		input->get(ch);

		switch (ch) {
		case '\n':
		case ';':
			return;
		}
	}
}

int main(int argc, char* argv[])
{

	switch (argc) {
	case 1:			 // read from standard input
		input = &cin;
		break;
	case 2:			 // read argument string
		input = new istrstream(argv[1],strlen(argv[1]));
		break;
	default:
		cerr << "too many arguments\n";
		return 1;
	}

	// insert pre-defined names:
	table["pi"] = 3.1415926535897932385;
	table["e"]  = 2.7182818284590452354;

 	while (*input) {
		cout<<"new expression:\n";
		try {
			Lexer::get_token();
			if (Lexer::curr_tok == Lexer::END) break;
			if (Lexer::curr_tok == Lexer::PRINT) continue;
			cout << Parser::expr(false) << '\n';
		}
		catch(Error::Zero_divide) {
			cerr << "attempt to divide by zero\n";
			skip();
		}
		catch(Error::Syntax_error e) {
			cerr << "syntax error:" << e.p << "\n";
			skip();
		}
	}

	if (input != &std::cin) delete input;
	return no_of_errors;
}
