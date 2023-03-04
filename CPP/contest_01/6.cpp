#include <iostream>
#include <cmath>
#include <ios>
#include <iomanip>

constexpr double kEps = 1e-6;

class Point {
  public:
    double x() const noexcept { return x_; }
    double y() const noexcept { return y_; }
    void x(double val) noexcept { x_ = val; }
    void y(double val) noexcept { y_ = val; }
    Point() noexcept = default;
    Point (double x, double y) noexcept : x_{x}, y_{y} {}

  private:
    double x_{}, y_{};
};

std::istream& operator>>(std::istream &is, Point &p) {
    double x, y;
    is >> x >> y;
    p.x(x), p.y(y);
    return is;
}

std::ostream& operator<<(std::ostream &os, const Point &p) {
    os << std::fixed << std::setprecision(5);
    os << p.x() << ' ' << p.y();
    return os;
}

class Line {
  public:
    Line (const Point &p1, const Point &p2) { 
        a_ = p1.y() - p2.y();
        b_ = p2.x() - p1.x();
        c_ = p2.x() * p1.y() - p1.x() * p2.y();
    }    
    double a() const noexcept { return a_; }
    double b() const noexcept { return b_; }
    double c() const noexcept { return c_; }

  private:
    double a_{}, b_{}, c_{};
};

bool AreEqual(const double a, const double b) {
    return abs(a - b) < kEps;
}

bool AreSame(const Line &l1, const Line &l2) {
    return (AreEqual(l1.a(), l2.a()) && AreEqual(l1.b(), l2.b()) 
                                     && AreEqual(l1.c(), l2.c()));
}

bool AreIntersecting(const Line &l1, const Line &l2) {
    return (!AreEqual((l1.a() * l2.b() - l1.b() * l2.a()), 0.0));
}

Point IntersectionPoint(const Line &l1, const Line &l2) {
    double det = l1.a() * l2.b() - l1.b() * l2.a();
    return Point((l1.b() * l2.c() - l1.c() * l2.b()) / det, (l1.c() * l2.a() - l1.a() * l2.c()) / det);
}

int main() {

    Point a, b, c, d;
    std::cin >> a >> b >> c >> d;
    Line l1(a, b);
    Line l2(c, d);
    if (AreSame(l1, l2)) {
        std::cout << 2 << std::endl;
    } else if (AreIntersecting(l1, l2)) {
        std::cout << 1 << ' ' << IntersectionPoint(l1, l2) << std::endl;
    } else {
        std::cout << 0 << std::endl;
    }

}
