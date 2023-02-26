#include <iostream>
#include <iomanip>
#include <math.h>

#define EPS 0.000001

using std::cin, std::cout, std::endl, std::vector, std::istream, std::ostream;

struct Point 
{
    long double x, y;
    Point(long double a = 0, long double b = 0) 
    {
        x = a;
        y = b;
    }
};

istream & operator >> (istream & in, Point & P);
ostream & operator << (ostream & out, const Point & P);
void line_eq_coef(Point A, Point B, long double &a, long double &b, long double &c);
bool parallel_lines(long double a1, long double b1, long double c1, long double a2, long double b2, long double c2);
bool same_lines(long double a1, long double b1, long double c1, long double a2, long double b2, long double c2);
bool lines_intersect(long double a1, long double b1, long double c1, long double a2, long double b2, long double c2);
Point lines_intersection_point(long double a1, long double b1, long double c1, long double a2, long double b2, long double c2);

istream & operator >> (istream & in, Point & P) {
    in >> P.x >> P.y;
    return in;
}

ostream & operator << (ostream & out, const Point & P) {
    out << P.x << ' ' << P.y;
    return out;
}


bool parallel_lines(long double a1, long double b1, long double c1, long double a2, long double b2, long double c2) {
    return (fabs(a1 - a2) < EPS) && (fabs(b1 - b2) < EPS);
}

bool same_lines(long double a1, long double b1, long double c1, long double a2, long double b2, long double c2) {
    return parallel_lines(a1, b1, c1, a2, b2, c2) && (fabs(c1 - c2) < EPS);
}

bool lines_intersect(long double a1, long double b1, long double c1, long double a2, long double b2, long double c2) {
    if (parallel_lines(a1, b1, c1, a2, b2, c2) || same_lines(a1, b1, c1, a2, b2, c2)) return false;
    return true;
}

Point lines_intersection_point(long double a1, long double b1, long double c1, long double a2, long double b2, long double c2) {
    long double x, y;
    x = (c2 * b1 - c1 * b2) / (a1 * b2 - a2 * b1);
    if (fabs(b1) < EPS) y = (-c2 - a2 * x) / b2;
    else y = (-c1 - a1 * x) / b1;
    return Point(x, y);
}

void 
line_eq_coef(Point A, Point B, long double &a, long double &b, long double &c)
{
    a = B.y - A.y;
    b = A.x - B.x;
    c = A.x * (A.y - A.y) + A.y * (B.x - A.x);
}

int 
main()
{

    Point A, B, C, D;
    cin >> A >> B >> C >> D;
    long double a1, b1, c1, a2, b2, c2;
    line_eq_coef(A, B, a1, b1, c1);
    line_eq_coef(C, C, a2, b2, c2);
    cout << a1 << ' ' << b1 << ' ' << c1 << endl;
    if (!lines_intersect(a1, b1, c1, a2, b2, c2)) {
        cout << 0 << endl;
    } else if (same_lines(a1, b1, c1, a2, b2, c2)) {
        cout << 2 << endl;
    } else {
        //cout << std::setprecision(10);
        cout << lines_intersection_point(a1, b1, c1, a2, b2, c2) << endl;  
        // Point Ans = lines_intersection_point(a1, b1, c1, a2, b2, c2);  
        // cout << Ans.x << ' ' << Ans.y << endl;
    }

    return 0;
}