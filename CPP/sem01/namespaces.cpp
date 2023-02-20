#include <iostream>

namespace A
{
    int c;
    namespace D
    {
        int a;
    }
    inline namespace E
    {
        int a;
    }
}

namespace B
{
    int a, b;
}

namespace A
{
    int b;
}

using namespace A;
inline namespace C 
{
    int a;
}

int
main(int argc, char **argv) 
{
    //int a;
    //namespace C = A;
    //using C::a;
    //std::cin >> a >> B::a >> A::b;
    //std::cout << a << std::endl;
    std::cin >> A::a >> A::E::a;
    std::cout << A::a << ' ' << A::E::a << std::endl;

    return 0;
}
