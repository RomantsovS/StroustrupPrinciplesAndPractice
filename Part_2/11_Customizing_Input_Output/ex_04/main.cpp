#include "../../../std_lib_facilities.h"

int main() {
    string str;
    vector<string> svec {"0x43", "0123", "65", "1"};

    int number;

    for(const auto& str : svec) {
        if(str.size() < 2) {
            cout << setw(6) << str << setw(25) << " demical converts to " << setw(3) << str << " demical\n";
        }
        else if(str.substr(0, 2) == "0x") {
            istringstream istr(str);
            istr >> hex >> number;
            cout << setw(6) << str << setw(25) << " hexademical converts to " << setw(3) << number << " demical\n";
        }
        else if(str[0] == '0') {
            istringstream istr(str);
            istr >> oct >> number;
            cout << setw(6) << str << setw(25) << " octal converts to " << setw(3) << number << " demical\n";
        }
        else {
            cout << setw(6) << str << setw(25) << " demical converts to " << setw(3) << str << " demical\n";
        }
    }
}