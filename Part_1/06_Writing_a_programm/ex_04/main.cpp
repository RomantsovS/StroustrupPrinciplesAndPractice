#include <iostream>
#include <cmath>
#include <string>
#include <exception>
#include <vector>
#include <iterator>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::cerr;

class Name_Value {
public:
	string name;
	int value;
};

std::vector<Name_Value> nv_vec;

int main() {
    try {
		string name;
		int val;
		while (cin >> name >> val) {
			Name_Value n_v({name, val});
			nv_vec.push_back(n_v);
		}

		for(auto n_v : nv_vec) {
			cout << n_v.name << " " << n_v.value << endl;
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
