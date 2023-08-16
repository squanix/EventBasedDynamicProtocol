#include "common.h"
#include "EventDynamic.h"
#include <string.h>

const int ch_MAX = 62;

/*
    Fisher Yates configuration
*/
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomize (int arr[], int n)
{

    for (int i = n - 1; i > 0; i--)
    {

        int j = random() % (i + 1);       // Better to know how the R key is crated

        swap(&arr[i], &arr[j]);
    }
}

int powers(int base, int exp)
{
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

String RandomString(int ch)
{
    char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C',
                          'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                          'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                          'U', 'V', 'W', 'X', 'Y', 'Z' , '0', '1', '2', '3',
                          '4', '5', '6', '7', '8', '9'  };
    String result = "";
    for (int i = 0; i<ch; i++)
        result = result + alpha[random() % ch_MAX];

    return result;
}

int computedPR(int seed, int qprime, int prime, int n)
{
    int Y = powers(seed,qprime);
    Y = Y % prime;
    int T = powers(Y, (qprime * n));
    return ( T * (qprime * (prime - n)) ) % (Y * prime);
}

int computedEV(int seed, int prime, int qprime, int n, int m)
{
    int PR = computedPR(seed, qprime, prime, n);
    int lengthPR = String(PR).length();
    lengthPR = m - lengthPR;
    String rc = RandomString(lengthPR);
    String Ev = rc + String(lengthPR);
    int R = random();                                               // This is must be secret and saved some point on flash
    return 1;
}