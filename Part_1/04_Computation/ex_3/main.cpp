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
    vector<double> dvec;
    double temp;

    cout << "enter double: ";
    while(cin >> temp)
    {
        dvec.push_back(temp);

        
    }

    double sum = std::accumulate(dvec.begin(), dvec.end(), 0.0);
    cout << "sum " << sum << endl;

    double min = INFINITY, max = -INFINITY;

    for(const auto d : dvec)
    {
    	if(d < min)
    		min = d;

    	if(d > max)
    		max = d;
    }

    cout << "min " << min << endl;
    cout << "max " << max << endl;

    cout << "average " << sum / dvec.size() << endl;

    return 0;
}
