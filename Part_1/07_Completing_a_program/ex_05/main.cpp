
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "../../../std_lib_facilities.h"

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string n) :kind(ch), name(n) { }
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

const char let = 'L';
const char const_token = 'C';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const string declkey = "let";
const string declconstkey = "const";
const string sqrt_key = "sqrt";
const char sqrt_token = 'S';
const string pow_key = "pow";
const char pow_token = 'P';

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	cin.get(ch);

	switch (ch) {
		case quit:
		case print:
		case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case ',':
		return Token(ch);
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
	{	cin.unget();
	double val;
	cin >> val;
	return Token(number, val);
	}
	default: {
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			cin.unget();
			if (s == declkey) return Token(let);
			else if(s == sqrt_key) return Token(sqrt_token);
			else if(s == pow_key) return Token(pow_token);
			else if(s == declconstkey) return Token(const_token);

			return Token(name, s);
		}
		else if (isspace(ch)) {
        	if (ch == '\n') return Token{print};
			break;
        }
		error("Bad token");
	}
}
return Token('e');
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	double value;
	bool constant;
	Variable(string n, double v, bool c = false) :name(n), value(v),
	constant(c) { }
};

class Symbol_table {
public:
	double get_value(string s);	
	void set_value(string s, double d);
	bool is_declared(string s);
	double define_name(string s, double val, bool const_par = false);
private:
	vector<Variable> var_table;
};

double Symbol_table::get_value(string s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined name ", s);

	return 0.0;
}

void Symbol_table::set_value(string s, double d)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) {
			if(var_table[i].constant)
				error("set: constant name ", s);

			var_table[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return true;
	return false;
}

double Symbol_table::define_name(string s, double val, bool const_par)
    // add (s,val,var) to var_table
{
    if (is_declared(s)) error(s," declared twice");
    var_table.push_back(Variable(s,val,const_par));
    return val;
}

Token_stream ts;

Symbol_table symb_table;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
	t = ts.get();
	if (t.kind != ')') error("'(' expected");
	return d;
	}
	case '-':
		return -primary();
	case number:
		return t.value;
	case name:
	{
		Token tt = ts.get();
		if(tt.kind == '=') {
			double d = expression();
			symb_table.set_value(t.name, d);
			return d;
		}
		ts.unget(tt);
		return symb_table.get_value(t.name);
	}
	case sqrt_token:
		{
			double d = primary();
			if(d < 0) error("can't sqrt negative number");
			return sqrt(d);
		}
	case pow_token:
		{
			Token tt = ts.get();
			if(tt.kind != '(') error("pow require (");
			double d = expression();
			tt = ts.get();
			if(tt.kind != ',') error("pow require ,");
			int multiplier = static_cast<int>(expression());
			tt = ts.get();
			if(tt.kind != ')') error("pow require )");
			return pow(d, multiplier);			
		}
	default:
		error("primary expected");
	}

	return 0.0;
}

double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration(const Token tok)
{
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");
	string name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);

	double d = expression();
	symb_table.define_name(name, d, tok.kind == const_token);
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let: case const_token:
		return declaration(t);
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main() {
try {
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}
return 0;
}