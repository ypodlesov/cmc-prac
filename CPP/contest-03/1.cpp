#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace numbers {
    class complex {
      public:
        complex(double re = 0.0, double im = 0.0) : re_{re}, im_{im} {}
        explicit complex(std::string);
        double re() const noexcept { return re_; }
        double im() const noexcept { return im_; }
        double abs2() const { return re_ * re_ + im_ * im_; }
        double abs() const { return sqrt(abs2()); }
        complex &operator +=(complex z);
        complex &operator -=(complex z);
        complex &operator *=(complex z);
        complex &operator /=(complex z);
        friend complex operator ~(complex z) { return complex(z.re(), -z.im()); }
        friend complex operator -(complex z) { return complex(-z.re(), -z.im()); }
        std::string to_string() const;

      private:
        double re_{}, im_{};
    };
};


numbers::complex::complex(::std::string s) {
    ::std::string re_str, im_str;
    auto i = s.begin() + 1;
    for (; i < s.end() - 1 && *i != ','; ++i) {
        re_str.push_back(*i);
    }
    for (++i; i < s.end() - 1; ++i) {
        im_str.push_back(*i);
    }
    re_ = stod(re_str);
    im_ = stod(im_str);
}

numbers::complex & numbers::complex::operator +=(numbers::complex z) {
    re_ += z.re();
    im_ += z.im();
    return *this;
}
numbers::complex & numbers::complex::operator -=(numbers::complex z) {
    re_ -= z.re();
    im_ -= z.im();
    return *this;
}

numbers::complex & numbers::complex::operator *=(numbers::complex z) {
    re_ = re_ * z.re() - im_ * z.im();
    im_ = re_ * z.im() + im_ * z.re();
    return *this;
}

numbers::complex & numbers::complex::operator /=(numbers::complex z) {
    re_ = (re_ * z.re() + im_ * z.im()) / z.abs2();
    im_ = (z.re() * im_ - re_ * z.im()) / z.abs2();
    return *this;
}

inline numbers::complex operator +(numbers::complex a, numbers::complex b) {
    a += b;
    return a;
}

inline numbers::complex operator -(numbers::complex a, numbers::complex b) {
    a -= b;
    return a;
}

inline numbers::complex operator *(numbers::complex a, numbers::complex b) {
    a *= b;
    return a;
}

inline numbers::complex operator /(numbers::complex a, numbers::complex b) {
    a /= b;
    return a;
}

std::string numbers::complex::to_string() const {
    std::ostringstream stream;
    stream << std::setprecision(10) << '(' << re_ << ',' << im_ << ')';
    return stream.str();
}

int main() {
    numbers::complex c{"(1,2)"};
    std::cout << c.to_string() << std::endl;
}

