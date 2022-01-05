#include <iostream>
#include <memory>

using namespace std;

template<typename T, typename A = allocator<T>> class vector {
    A alloc;
    // read “for all types T” (just like in math)
    int sz;
    // the size
    T* elem;
    // a pointer to the elements
    int space;
    // size + free space
   public:
    vector() : sz{0}, elem{nullptr}, space{0} {}
    explicit vector(int s) : sz{s}, elem{alloc.allocate(s)}, space{s} {
        for(int i = 0; i < sz; ++i) {
            alloc.construct(&elem[i], T());
        }
    }
    vector(const vector&);
    vector& operator=(const vector&);
    vector(vector&&);
    vector& operator=(vector&&);
    ~vector() {
        for(int i = 0; i < sz; ++i) {
            alloc.destroy(&elem[i]);
        }
        alloc.deallocate(elem, space);
    }
    T& operator[](int n) { return elem[n]; }
    const T& operator[](int n) const { return elem[n]; }

    T& at(int n) {
        if (n < 0 || sz <= n) throw out_of_range();
        return elem[n];
    }

    int size() const { return sz; }
    int capacity() const { return space; }

    void resize(int newsize, T val = T()) {
        reserve(newsize);
        for (int i = sz; i < newsize; ++i)
            alloc.construct(&elem[i], val);  // construct
        for (int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]);
        sz = newsize;
    }

    void push_back(const T& val) {
        if (space == 0)
            reserve(8);
        else if (sz == space)
            reserve(2 * space);
        alloc.construct(&elem[sz], val);
        ++sz;
    }

    void reserve(int newalloc) {
        if (newalloc <= space) return;
        T* p = alloc.allocate(newalloc);
        for (int i = 0; i < sz; ++i) alloc.construct(&p[i], elem[i]);
        for (int i = 0; i < sz; ++i) alloc.destroy(&elem[i]);
        alloc.deallocate(elem, space);
        elem = p;
        space = newalloc;
    }
};

class My {
   private:
    int data = 0;

   public:
    explicit My(int i = 0) : data(i) { cout << "My ctor\n"; }
    ~My() { cout << "My dtor\n"; }
    friend ostream& operator<<(ostream& os, const My& dt);
};

ostream& operator<<(ostream& os, const My& m) {
    os << m.data;
    return os;
}

int main() {
    vector<double> vd(5);

    cout << vd[0] << endl;

    {
        vector<My> vm(3);

        cout << vm[0] << endl;
    }

    {
        vector<My> vm(1);

        vm.resize(2, My(2));

        cout << vm[0] << endl;
    }

    return 0;
}