#include <iostream>

using namespace std;

class My {
   private:
    int data = 0;

   public:
    explicit My(int i = 0) : data(i) {
        cout << "My ctor\n";
    }
    ~My() {
        cout << "My dtor\n";
    }
    int& get() {
        return data;
    }
    friend ostream& operator<<(ostream& os, const My& dt);
};

ostream& operator<<(ostream& os, const My& m) {
    os << m.data;
    return os;
}

template <typename T>
class unique_ptr {
public :
    unique_ptr(T* p) : ptr(p) {

    }
    ~unique_ptr() {
        delete ptr;
    }

    T& operator*() {
        return *ptr;
    }
    T* operator->() {
        return ptr;
    }

    void release() {
        delete ptr;
        ptr = nullptr;
    }
private:
    T* ptr;
};

int main() {
    {
        unique_ptr<My> ptr (new My(1));

        cout << *ptr << endl;

        *ptr = My(2);

        cout << *ptr << endl;

        cout << ptr->get() << endl;

        ptr->get() = 3;

        cout << ptr->get() << endl;

        ptr.release();
    }

    return 0;
}