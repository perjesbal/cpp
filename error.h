#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

namespace Error {

	struct Zero_divide { };

	struct Syntax_error {
		const char* p;
		Syntax_error(const char* q) { p = q; }
	};
}

#endif // ERROR_H_INCLUDED
