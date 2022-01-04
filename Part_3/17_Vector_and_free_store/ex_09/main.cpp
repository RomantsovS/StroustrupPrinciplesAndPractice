#include <iostream>

using namespace std;

void foo(int i) {
    if(i == 0)
        return;
    int i3;
    cout << "i3 " << i << ' ' << &i3 << ' ' << i3 << endl;
    i3 = 777;
    foo(i - 1);
}

int main() {
    int i1, i2;

    cout << "i1 " << &i1 << endl;
    cout << "i2 " << &i2 << endl;

    foo(5);

    foo(5);

    int i4;

    cout << "i4 " << &i4 << endl;

    int* ip = new int;
    int* iparr = new int[4];

    cout << "ip " << ip << endl;
    cout << "iparr " << iparr << endl;

    return 0;
}