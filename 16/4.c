#include <stdio.h>
#include <stdlib.h>


#define MAX(A, B) ((A) > (B) ? (A) : (B))

unsigned int
mpow(unsigned int n) {
    int res = 0, cur = 0;
    while ((1 << cur) <= n) {
        if (n % (1 << cur) == 0) {
            res = cur;
        }
    }
    return res;
}

int
main(void)
{
    unsigned int *szs = calloc(1, sizeof(*szs));
    unsigned int cap = 1, size = 0;
    unsigned int tmp;
    unsigned int align = 0;
    while ((scanf("%u", &tmp)) == 1) {
        if (size == cap) {
            cap <<= 1;
            printf("ok\n");
            szs = realloc(szs, cap * sizeof(*szs));
        }
        szs[size++] = tmp;
        align = MAX(align, mpow(tmp));
    }
    unsigned int res = 0;
    for (int i = 0; i < size; ++i) {
        if (szs[i] % align == 0) {
            res += szs[i];
        } else {
            res += (szs[i] + align - 1) / align * align;
        }
    }
    printf("%u %u\n", res == 0 ? 1 : res, align == 0 ? 1 : align);


    return 0;
}
