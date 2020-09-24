#include <iostream>
#include <cmath>
#include <string>
#include <exception>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::cerr;

const char number = '8';
const char quit = 'q';
const char print = ';';
const char prompt = '>';
const char result = '=';

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
	void ignore(char c);
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
	case print:
		// for “print”
	case quit:
		// for “quit”
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '{' :
	case '}' :
	case '!' :
	case '%':
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
		return Token{number,val};
		// let ‘8’ represent “a number”
	}
	default:
		throw std::invalid_argument("Bad token");
	}
}

void Token_stream::ignore(char c) // c represents the kind of Token
{
	// first look in buffer:
	if (full && c==buffer.kind) {
		full = false;
		return;
	}
	full = false;
	// now search input:
	char ch = 0;
	while (cin>>ch)
		if (ch==c) return;
}

Token_stream ts; // provides get() and putback()
double expression(); // declaration so that primary() can call expression()

int factorial(int x) {
	if(x == 0)
		return 1;
	return factorial(x - 1) * x;
}

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(': // handle ‘(‘ expression ‘)’
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') throw std::invalid_argument("')' expected");
		return d;
	}
	case '{': // handle ‘{‘ expression ‘}’
	{
		double d = expression();
		t = ts.get();
		if (t.kind != '}') throw std::invalid_argument("'}' expected");
		return d;
	}
	case number: {
		Token tok = ts.get();
		if(tok.kind == '!')
			return factorial(t.value);
		else {
			ts.putback(tok);
		// we use ‘8’ to represent a number
			return t.value;
		}
		// return the number’s value
	}
	case '-':
		return -primary();
	case '+':
		return primary();
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
		case '!':
			return factorial(left);
			break;
		case '%': {
			int i1 = static_cast<int>(left);
			int i2 = static_cast<int>(primary());
			if (i2 == 0) throw("%: divide by zero");
			left = i1%i2;
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

void clean_up_mess()
// naive
{
	ts.ignore(print);
}

void calculate() {
	while (cin) 
	try {
		cout << prompt;
		Token t = ts.get();
		// ‘q’ for “quit”
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) break;
		ts.putback(t);
		cout << result << expression() << endl;
	}
	catch(std::exception& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main() {
    try {
		calculate();
	}
	catch (std::exception& e) {
		cerr << e.what() << '\n';
		// keep_window_open():
		cout << "Please enter the character ~ to close the window\n";
		for (char ch; cin >> ch; )
		// keep reading until we find a ~
		if (ch=='~') return 1;
	}
	catch (...) {
		cerr << "exception \n";

		return 2;
	}
}
