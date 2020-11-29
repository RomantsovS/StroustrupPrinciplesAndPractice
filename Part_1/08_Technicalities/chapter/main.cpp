#include <iostream>
#include <cmath>
#include <string>
#include <exception>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

const char number = '8';
const char quit = 'q';
const char print = ';';
const char prompt = '>';
const char result = '=';

const string declkey = "let";
const char name = 'a';
const char let = 'L';

class Variable
{
public:
	Variable(const string &str, double val) : name(str), value(val) {}
	string name;
	double value;
};

std::vector<Variable> var_table;

double get_value(string s)
// return the value of the Variable named s
{
	for (const Variable &v : var_table)
		if (v.name == s)
			return v.value;
	throw std::invalid_argument("get: undefined variable " + s);
}

void set_value(string s, double d)
// set the Variable named s to d
{
	for (Variable &v : var_table)
		if (v.name == s)
		{
			v.value = d;
			return;
		}
	throw std::invalid_argument("set: undefined variable" + s);
}

class Token
{
public:
	char kind;
	double value;
	string name;

	Token() = default;
	Token(char ch) // make a Token from a char
		: kind(ch), value(0)
	{
	}
	Token(char ch, double val) : kind{ch}, value{val} {} // initialize kind and value
	Token(char ch, string n) : kind{ch}, name{n} {}		 // initialize kind and name
};

class Token_stream
{
public:
	Token get();
	// get a Token (get() is defined in §6.8.2)
	void putback(Token t); // put a Token back
	void ignore(char c);

private:
	bool full{false};
	// is there a Token in the buffer?
	Token buffer; // here is where we keep a Token put back using putback()
};

void Token_stream::putback(Token t)
{
	buffer = t;
	// copy t to buffer
	full = true;
	// buffer is now full
}

Token Token_stream::get()
{
	if (full)
	{
		// do we already have a Token ready?
		full = false;
		// remove Token from buffer
		return buffer;
	}
	char ch;
	cin >> ch;
	// note that >> skips whitespace (space, newline, tab, etc.)
	switch (ch)
	{
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
	case '{':
	case '}':
	case '!':
	case '%':
	case '=':
		return Token{ch};
	// let each character represent itself
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		cin.putback(ch);
		// put digit back into the input stream
		double val;
		cin >> val;
		// read a floating-point number
		return Token{number, val};
		// let ‘8’ represent “a number”
	}
	default:
		if (isalpha(ch))
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
				s += ch;
			cin.putback(ch);
			if (s == declkey)
				return Token{let}; // declaration keyword
			return Token{name, s};
		}
		throw std::invalid_argument("Bad token");
	}
}

void Token_stream::ignore(char c) // c represents the kind of Token
{
	// first look in buffer:
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;
	// now search input:
	char ch = 0;
	while (cin >> ch)
		if (ch == c)
			return;
}

Token_stream ts;	 // provides get() and putback()
double expression(Token_stream& ts); // declaration so that primary() can call expression()

int factorial(int x)
{
	if (x == 0)
		return 1;
	return factorial(x - 1) * x;
}

double primary(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(': // handle ‘(‘ expression ‘)’
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')')
			throw std::invalid_argument("')' expected");
		return d;
	}
	case '{': // handle ‘{‘ expression ‘}’
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != '}')
			throw std::invalid_argument("'}' expected");
		return d;
	}
	case number:
	{
		Token tok = ts.get();
		if (tok.kind == '!')
			return factorial(t.value);
		else
		{
			ts.putback(tok);
			// we use ‘8’ to represent a number
			return t.value;
		}
		// return the number’s value
	}
	case name:
		return get_value(t.name);
	case '-':
		return -primary(ts);
	case '+':
		return primary(ts);
	default:
		auto str = string("primary expected: ").append(1, t.kind);
		throw(std::invalid_argument(str));
	}
}

double term(Token_stream& ts)
{
	double left = primary(ts);
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary(ts);
			t = ts.get(); // get the next Token from the Token streamt = ts.get();
			break;
		case '/':
		{
			double d = primary(ts);
			if (d == 0)
				throw(std::invalid_argument("divide by zero"));
			left /= d;
			t = ts.get();
			break;
		}
		case '!':
			return factorial(left);
			break;
		case '%':
		{
			int i1 = static_cast<int>(left);
			int i2 = static_cast<int>(primary(ts));
			if (i2 == 0)
				throw("%: divide by zero");
			left = i1 % i2;
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

double expression(Token_stream& ts)
{
	double left = term(ts);
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term(ts);
			t = ts.get();
			break;
		case '-':
			left -= term(ts);
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

bool is_declared(string var)
// is var already in var_table?
{
	for (const Variable &v : var_table)
		if (v.name == var)
			return true;
	return false;
}

double define_name(string var, double val)
// add (var,val) to var_table
{
	if (is_declared(var))
		throw std::invalid_argument(var + " declared twice");
	var_table.push_back(Variable(var, val));
	return val;
}

double declaration()
// assume we have seen "let”
// handle: name = expression
// declare a variable called "name” with the initial value "expression”
{
	Token t = ts.get();
	if (t.kind != name)
		throw std::invalid_argument("name expected in declaration");
	string var_name = t.name;
	Token t2 = ts.get();
	if (t2.kind != '=')
		throw std::invalid_argument("= missing in declaration of " + var_name);
	double d = expression(ts);
	define_name(var_name, d);
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression(ts);
	}
}

void clean_up_mess()
// naive
{
	ts.ignore(print);
}

void calculate()
{
	while (cin)
		try
		{
			cout << prompt;
			Token t = ts.get();
			// ‘q’ for “quit”
			while (t.kind == print)
				t = ts.get();
			if (t.kind == quit)
				break;
			ts.putback(t);
			cout << result << statement() << endl;
		}
		catch (std::exception &e)
		{
			cerr << e.what() << endl;
			clean_up_mess();
		}
}

int main()
{
	try
	{
		// predefine names:
		define_name("pi", 3.1415926535);
		define_name("e", 2.7182818284);

		calculate();
	}
	catch (std::exception &e)
	{
		cerr << e.what() << '\n';
		// keep_window_open():
		cout << "Please enter the character ~ to close the window\n";
		for (char ch; cin >> ch;)
			// keep reading until we find a ~
			if (ch == '~')
				return 1;
	}
	catch (...)
	{
		cerr << "exception \n";

		return 2;
	}
}
