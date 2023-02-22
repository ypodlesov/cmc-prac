#include <iostream>

class Sum
{
    int a{}, b{};
public:
    Sum(int a, int b)
    {
        this->a = a;
        this->b = b;
    }
    Sum(Sum a, int b)
    {
        this->a = a.get();
        this->b = b;
    }
    int 
    get() const
    {
        return this->a + this->b;
    }    
};

using std::cin, std::cout, std::endl;

// int
// main()
// {
//     int a, b, c;
//     cin >> a >> b >> c;
//     cout << Sum(Sum(a, b), c).get() << endl;

//     return 0;
// }