#include <iostream>
#include <cmath>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
    double min = INFINITY, max = -INFINITY;
    string temp;

    cout << "enter double: ";
    while(cin >> temp)
    {
        if(temp == "|")
            break;

		double val;

        if(temp.size() > 2)
        {
        	string val_str, unit;

        	for(auto ch : temp)
        	{
        		if(ch >= '0' && ch <= '9')
        		{
        			val_str += ch;
        		}
        		else if (ch >= 'a' && ch <= 'z')
        		{
        			unit += ch;
        		}
        	}

        	if(unit == "cm")
        	{
        		val = std::stod(val_str);
        		val = 0.01 * val;
        	}
        	else if(unit == "in")
        	{
        		val = std::stod(val_str);
        		val = 2.54 * 0.01 * val;
        	}
        	else if(unit == "ft")
        	{
        		val = std::stod(val_str);
        		val = 12 * 2.54 * 0.01 * val;
        	}
        	else if(unit == "m")
        	{

        	}
        	else
        	{
        		cout << "incorect unit\n";
        		continue;
        	}

        }
        else
        {
        	cout << "incorect unit\n";
        	continue;
        }

        cout << val << " m\n";

        if(val <= min)
        	min = val;
        if(val >= max)
        	max = val;

        cout << "enter double: ";
    }

    cout << "the smaller value is " << min << endl;
    cout << "the larger value is " << max << endl;

    return 0;
}
