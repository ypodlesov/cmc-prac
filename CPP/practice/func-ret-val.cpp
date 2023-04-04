#include <iostream>

class A {
  public:
    A() {
        std::cout << "A()" << std::endl;
    }
    A(const A &other) {
        a_ = other.a_;
        std::cout << "A(const A &)" << std::endl;
    }
    int a() {
        return a_;
    }

  private:
    int a_{};

};

A f1(A a) {
    std::cout << "A f1(A a)" << std::endl;
    return a;
}

A & f2(A &a) {
    std::cout << "A f2(A &a)" << std::endl;
    return a;
}

int main() {
    A a1{};
    f1(a1);
    f2(a1);
    //[[maybe_unused]] A a3(f2(a2));
}





