#include <iostream>

using namespace std;

int strcmp(const char* s1, const char* s2) {
    while(*s1 && *s2) {
        if(*s1 < *s2)
            return -1;
        else if(*s1 > *s2)
            return 1;
        ++s1;
        ++s2;
    }

    if(!*s1 && !*s2)
        return 0;
    else if(!*s2)
        return 1;
    else    
        return -1;
}

int main() {
    const char* ch1 = "text";
    const char ch2[] = "text";

    cout << strcmp(ch1, ch2) << endl;

    const char* ch3 = "tex";
    const char ch4[] = "text";

    cout << strcmp(ch3, ch4) << endl;

    const char* ch5 = "text";
    const char ch6[] = "te";

    cout << strcmp(ch5, ch6) << endl;

    const char* ch7 = "";
    const char ch8[] = "text";

    cout << strcmp(ch7, ch8) << endl;

    const char* ch9 = "a";
    const char ch10[] = "b";

    cout << strcmp(ch9, ch10) << endl;

    return 0;
}