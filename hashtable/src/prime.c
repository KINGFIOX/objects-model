#include <math.h>

#include "prime.h"

/**
 * @brief 暴力搜索是不是prime
 * 
 * @param x 
 * @return int 
 */
int is_prime(const int x)
{
    if (x < 2) {
        return -1;
    } else if (x < 4) {
        return 1;
    }

    if (x % 2 == 0) {
        return 0;
    }

    for (int i = 3; i <= floor(sqrt((double)x)); i += 2) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief 寻找下一个prime
 * 
 * @param x 
 * @return int 
 */
int next_prime(int x)
{
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}