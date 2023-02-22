#include <iostream>

using std::cin, std::cout, std::endl;

class A
{
    int n{};
    bool flag{};
public:
    A() 
    {
        cin >> this->n;
    }
    A(A &a) 
    {
        flag = true;
        cin >> n;
        n += a.n;
    }
    ~A() 
    {
        if (flag) cout << this->n << endl;
        // cout << this->n << endl;
    }
};

// int
// main()
// {
//     A a, b(a);


//     return 0;
// }