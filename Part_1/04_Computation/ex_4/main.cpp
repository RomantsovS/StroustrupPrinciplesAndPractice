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
    
    int min = 1, max = 101;

    while(true) {
    	cout << " is the number less than " << (max + min) / 2 << " ? (y/n)" << endl;
    	cout << min << " " << max << endl;
    	char ch;

    	cin >> ch;

    	if(ch == 'y') {
    		max = (max + min) / 2;
    	}
    	else if(ch == 'n') {
    		if(min == max - 1){
    			max = min;
    			break;
    		}

    		min = (max + min) / 2;
    	}
    	else
    		continue;

    	if(min == max) {
    		break;
    	}
    }

    cout << "your number is " << max << endl;

    return 0;
}
