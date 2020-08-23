#include <iostream>
#include <cmath>
#include <string>
#include <exception>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::cerr;

class Token {
public:
	char kind;
	double value;

	Token() = default;
	Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

class Token_stream {
public:
	Token get();
	// get a Token (get() is defined in §6.8.2)
	void putback(Token t); // put a Token back
private:
	bool full {false};
	// is there a Token in the buffer?
	Token buffer; // here is where we keep a Token put back using putback()
};

void Token_stream::putback(Token t) {
	buffer = t;
	// copy t to buffer
	full = true;
	// buffer is now full
}

Token Token_stream::get()
{
	if (full) {
		// do we already have a Token ready?
		full = false;
		// remove Token from buffer
		return buffer;
	}
	char ch;
	cin >> ch;
	// note that >> skips whitespace (space, newline, tab, etc.)
	switch (ch) {
	case ';':
		// for “print”
	case 'q':
		// for “quit”
	case '(': case ')': case '+': case '-': case '*': case '/': case '{' : case '}' :
		return Token{ch};
	// let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);
		// put digit back into the input stream
		double val;
		cin >> val;
		// read a floating-point number
		return Token{'8',val};
		// let ‘8’ represent “a number”
	}
	default:
		throw("Bad token");
	}
}

Token_stream ts; // provides get() and putback()
double expression(); // declaration so that primary() can call expression()

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(': // handle ‘(‘ expression ‘)’
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') throw("')' expected");
		return d;
	}
	case '{': // handle ‘{‘ expression ‘}’
	{
		double d = expression();
		t = ts.get();
		if (t.kind != '}') throw("'}' expected");
		return d;
	}
	case '8':
		// we use ‘8’ to represent a number
		return t.value;
		// return the number’s value
	default:
		auto str = string("primary expected").append(1, t.kind);
		throw(std::invalid_argument(str));
	}
}

double term()
{
	double left = primary();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get(); // get the next Token from the Token streamt = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) throw(std::invalid_argument("divide by zero"));
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			// put t back into the Token stream
			return left;
		}
	}
}

double expression() {
	double left = term();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
		return left;
		}
	}
// read and evaluate a Term
// get the next Token from the Token stream
// evaluate Term and add
// evaluate Term and subtract
// put t back into the token stream
// finally: no more + or –; return the answer
}

int main() {
    try {
    	double val = 0;
		while (cin) {
			Token t = ts.get();
			if (t.kind == 'q') break;
			// ‘q’ for “quit”
			if (t.kind == ';')
				// ‘;’ for “print now”
				cout << "=" << val << '\n';
			else
				ts.putback(t);
			val = expression();
		}

	}
	catch (std::exception& e) {
		cerr << e.what() << '\n';

		return 1;
	}
	catch (...) {
		cerr << "exception \n";

		return 2;
	}
}
