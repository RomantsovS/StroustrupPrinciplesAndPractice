#include <iostream>
#include <list>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include <numeric>

using namespace std;

template <typename Iterator, typename T>
bool bin_search(Iterator begin, Iterator end, T val) {
    while(true) {
        if(begin == end)
            return false;

        auto mid = next(begin, distance(begin, end) / 2);
        if(*mid == val)
            return true;
        else if(*mid < val) {
            begin = ++mid;
        } else {
            end = mid;
        }
    }
    return false;
}

int main() {
    {
        vector<int> ivec(100'000'000);
        iota(ivec.begin(), ivec.end(), 0);


        auto start = chrono::steady_clock::now();
        auto iter = bin_search(ivec.begin(), ivec.end(), -3);
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << iter << ' '
        << chrono::duration_cast<chrono::microseconds>(diff).count() << endl;
    }

    {
        vector<int> ivec(100'000'000);
        iota(ivec.begin(), ivec.end(), 0);


        auto start = chrono::steady_clock::now();
        auto iter = binary_search(ivec.begin(), ivec.end(), -3);
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << iter << ' '
        << chrono::duration_cast<chrono::microseconds>(diff).count() << endl;
    }

    {
        list<int> ivec(1'000'000);
        iota(ivec.begin(), ivec.end(), 0);


        auto start = chrono::steady_clock::now();
        auto iter = bin_search(ivec.begin(), ivec.end(), 3);
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << iter << ' '
        << chrono::duration_cast<chrono::microseconds>(diff).count() << endl;
    }

    {
        list<int> ivec(1'000'000);
        iota(ivec.begin(), ivec.end(), 0);


        auto start = chrono::steady_clock::now();
        auto iter = binary_search(ivec.begin(), ivec.end(), 3);
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << iter << ' '
        << chrono::duration_cast<chrono::microseconds>(diff).count() << endl;
    }

    return 0;
}