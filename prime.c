#include "task.h"
/*PART A*/
bool isPrime(unsigned int num) {
    if (num <= 1) {
        return false;  // Numbers less than or equal to 1 are not prime
    }

    if (num == 2 || num == 3) {
        return true;  // 2 and 3 are prime numbers
    }

    if (num % 2 == 0) {
        return false;  // Even numbers (except 2) are not prime
    }

    for (unsigned int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) {
            return false;  // If num is divisible by i, it is not prime
        }
    }

    return true;  // num is not divisible by any numbers, so it is prime
}
