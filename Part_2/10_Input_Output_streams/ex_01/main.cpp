#include "../../../std_lib_facilities.h"

void end_of_loop(istream &ist, char term, const string &message) {
	if (ist.fail())
	{
		// use term as terminator and/or separator
		ist.clear();
		char ch;
		if (ist >> ch && ch == term)
			return;
		// all is fine
		error(message);
	}
}

int main() {
	// open an input file:
	cout << "Please enter input file name\n";
	string iname;
	cin >> iname;
	ifstream ifs{iname};
	if (!ifs)
		error("can't open input file", iname);
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	// throw for bad()
	// open an output file:

	int i, sum = 0;
	while (ifs >> i)
	{
		sum += i;
	}
	cout << "sum " << sum << endl;
}