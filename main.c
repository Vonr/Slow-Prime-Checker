#include <stdio.h>
#include <time.h>

unsigned long long big_sqrt(unsigned long long A) {
    unsigned long long MIN = 0;
    unsigned long long MAX = ((unsigned long long) 1) << 32; // multiply llu of 1 by 32-bit int of 2 pow 32 to get llu of 9,223,372,036,854,775,807

    while(1) {
        if (MAX <= MIN + 1)
             return MIN;

        unsigned long long SQT = MIN + (MAX - MIN) / 2;
        unsigned long long SQ = SQT * SQT; // multiply is faster than square

        if (SQ == A) 
             return SQT;

        if (SQ > A)
             MAX = SQT;
        else
             MIN = SQT;
    }
}

int main() { 
    unsigned long long LOOP, NUMBER;
    unsigned short IS_PRIME = 1;
    while (1) {
        printf( "Enter a number: ");
        scanf("%llu", &NUMBER);
        getchar();

        clock_t BEGIN = clock();
        /** 
         * Simple primality rules. 1 is not a prime, 
         * 2 and 3 are primes, 
         * all other primes follow the expression  6k (+/-) 1
         **/
        IS_PRIME = NUMBER != 1 && (NUMBER <= 3 || (NUMBER % 6 == 1 || NUMBER % 6 == 5));

        /**
         * Looping math with 6k (+/-) 1 logic to speed up algo.
         **/
        if (IS_PRIME)  {
            unsigned short MODE = 0;
            for (LOOP = 3; LOOP <= big_sqrt(NUMBER);) {
                if (NUMBER % LOOP == 0) {
                    IS_PRIME = 0;
                    break;
                }
                LOOP += 2 * (1 + (MODE == 2));
                MODE += 1 - 2 * (MODE == 2);
            }
        }

        if (IS_PRIME) printf("\n%llu is a prime number.\n", NUMBER);
        else printf("\n%llu is not a prime number.\n", NUMBER);
        printf("It took %lf seconds to check if %llu was a prime number.\n\n", (double)(clock() - BEGIN) / CLOCKS_PER_SEC, NUMBER);
    }
    return 0;
}