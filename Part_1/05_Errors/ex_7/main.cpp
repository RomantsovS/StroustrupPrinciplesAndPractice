#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {

    cout << "enter a b and c:\n";

    int a, b, c;

    cin >> a >> b >> c;

    double d = b * b - 4 * a * c;

    if(d < 0) {
    	cout << "d < 0" << endl;
    }
    else if (d == 0) {
    	cout << -b / 2 * a << endl;
    }
    else {
    	cout << (-b + sqrt(d)) / 2 * a << endl;
    	cout << (-b - sqrt(d)) / 2 * a << endl;
    }


    return 0;
}
