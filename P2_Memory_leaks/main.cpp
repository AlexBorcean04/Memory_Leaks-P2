#include <iostream>
#include <string.h>

using namespace std;

struct A {
    char* s;

    A(const char* p) {
        s = new char[strlen(p) + 1];
        strcpy(s, p);
        cout << "type-conversion ctor(" << p << ")" << endl;
    }

    A() : s(nullptr) {
        cout << "default ctor" << endl;
    }

    A(const A& o) {
        if (o.s) {
            s = new char[strlen(o.s) + 1];
            strcpy(s, o.s);
        } else {
            s = nullptr;
        }
        cout << "copy ctor" << endl;
    }

    A(A&& o) noexcept : s(o.s) {
        o.s = nullptr;
        cout << "move ctor" << endl;
    }

    ~A() {
        if (s) {
            cout << s << " dtor" << endl;
            delete[] s;
        }
    }

    A& operator=(const A& other) {
        if (this != &other) {
            delete[] s;
            s = new char[strlen(other.s) + 1];
            strcpy(s, other.s);
        }
        return *this;
    }

    A& operator=(A&& other) noexcept {
        if (this != &other) {
            delete[] s;
            s = other.s;
            other.s = nullptr;
        }
        return *this;
    }
};

A f(A a) {
    return a;
}

int main() {

    {
        A b{"Wednesday"};
        A c("Thursday");
        A d = A("Friday");
    }

    {
        A a = "Tuesday";
        A c = f("Monday");
    }
}
