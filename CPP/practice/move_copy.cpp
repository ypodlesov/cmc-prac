#include <iostream>
#include <vector>

template <typename T>
class Ptr {
  private:
    T *a_{nullptr};

  public:
    Ptr(T *p = nullptr) : a_{p} {
        //std::cout << "Constructor" << std::endl;
    }
    Ptr(const Ptr &other) { 
        std::cout << "Copy constructor (const Ptr &)" << std::endl;
        a_ = new T{*(other.a_)}; 
    }
    Ptr(Ptr &&other) {
        std::cout << "Move constructor (Ptr &&)" << std::endl;
        swap(other);
    }
    void swap(Ptr &other) {
        std::swap(a_, other.a_);
    }
    Ptr & operator =(const Ptr &p) {
        std::cout << "Copy assign (const Ptr &)" << std::endl;
        if (this == &p) {
            return *this;
        }
        a_ = new T;
        *a_ = *p.a_;
        return *this;
    }
    /*Ptr & operator =(Ptr &&p) {
        std::cout << "Move assign (Ptr &&)" << std::endl;
        if (this == &p) {
            return *this;
        }   
        delete a_;
        a_ = nullptr;
        swap(p);
        return *this;
    }*/
    ~Ptr() { 
        //std::cout << "Destructor" << std::endl;
        delete a_; 
    }
    T * a() { return a_; }
};

class A {
  public:
    A() {
        std::cout << "A constructed" << std::endl;
    }
    ~A() {
        std::cout << "A destructed" << std::endl;
    }
};

Ptr<A> create() {
    Ptr<A> p(new A);
    return p;
}

int main() {
    
    Ptr<A> p1(Ptr<A>(new A)); 
    Ptr<A> p2(std::move(p1)); 

}
