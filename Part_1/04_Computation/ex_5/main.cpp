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
    
    double val1, val2;
    char ch;

    cout << "enter two doubles and operation: ";
    cin >> val1 >> val2 >> ch;

    if(ch == '+')
    	cout << "sum is " << val1 + val2 << endl;
    else if(ch == '-')
    	cout << "substract is " << val1 - val2 << endl;
    else if(ch == '*')
    	cout << "multiple is " << val1 * val2 << endl;
    else if(ch == '/')
    	cout << "division is " << val1 / val2 << endl;
    else
    	cout << "wrong input\n";

    return 0;
}
