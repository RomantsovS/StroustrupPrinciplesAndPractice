#include "../../../std_lib_facilities.h"

int main() {
    int birth_year = 8;

    cout << 10 << '\t' << 16 << '\t' << 8 << endl;
    cout << birth_year << '\t';
    cout << hex << birth_year << '\t';
    cout << oct << birth_year << '\t' << endl;

    cout << dec << 31 << endl;

    int a, b, c, d;
    cin >> a >> oct >> b >> hex >> c >> d;
    cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

    double doub = 1234567.89;
    cout << fixed << doub << endl;
    cout << scientific << doub << endl;

    getchar();
}