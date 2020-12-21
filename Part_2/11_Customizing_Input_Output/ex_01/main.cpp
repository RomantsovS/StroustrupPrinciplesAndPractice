#include "../../../std_lib_facilities.h"

int main() {
    ifstream ist("in.txt");

    ofstream ost("out.txt");

    string str;
    while(getline(ist, str)) {
        for(auto& ch : str) {
            ch = tolower(ch);
        }
        ost << str << endl;
    }
}