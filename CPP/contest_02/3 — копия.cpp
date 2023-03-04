class C
{
public:
    C() {};
    C(const C, const C) {};
    C(const C, int n) {};
    C(double d) {};
    friend C operator + (int, const C);
    friend int operator ~ (const C);
    friend C operator & (const C);
    friend C operator ++ (const C);
    friend int operator * (const C, C []);

};

C operator + (int a, const C c)
{
    return c;
}
int operator ~ (const C c)
{
    return 0;
}

C operator & (const C c)
{
    return c;
}

C operator ++ (const C)
{
    C c;
    return c;
}
int operator * (const C c1, C c[])
{
    return 0;
}


// C func1(const C &v1, int v2)
// {
//     return C(v2 + v1, ~v1);
// }
//
// void func2(const C *p1, double p2)
// {
//     C v1 = p2;
//     C v2[2][2];
//     C v3 = func1(func1(func1(&p1[3], p2), ~p1[2]), ++v1 * v2[1]);
// }
