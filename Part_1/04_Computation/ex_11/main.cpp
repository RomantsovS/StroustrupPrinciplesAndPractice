#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {
    
    int max;

    cout << "enter max: ";
    cin >> max;
    cout << endl;

    vector<int> ivec{2};

    for(int i = 3; i <= max; ++i) {
    	bool finded = true;
    	for(const auto val : ivec) {
    		if(i % val == 0) {
    			finded = false;
    			break;
    		}
    	}

    	if(finded)
    		ivec.push_back(i);
    }

    cout << "primes:\n";

    for(const auto val : ivec) {
    	cout << val << endl;
    }

    return 0;
}
