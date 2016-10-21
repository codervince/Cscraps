#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* sum elements in array of length n, use index increment inc
   note: for inc > 1, array elements are accessed non-consecutively
   beware: choose inc such that GCD(N, inc) = 0. N is the array size.
 */
double sum(  // add up all values in array
        double *array,  // array
        int n,          // array size
        int inc)        // index increment
{
    double res = 0;
    int index = 0;
    for (int i = 0; i < n; i++) {
        index = (index + inc) % n;
        res += array[index];
    }
    return res;
}

int main() {
    const int N = 50 * 1000 * 1000; // array size
    const int INC[] = { 1, 3, 15485867 };

    // create and initialize array
    double *array = malloc(N * sizeof (double));
    for (int i = 0; i < N; i++) array[i] = i;
    double element_sum = 0.5 * N * (N - 1);

    // baseline ... processor time for increment = 1
    printf("Establish baseline ...\n");
    const int AVG = 10;
    double exec_for_inc_1 = 0;
    for (int i=0;  i<AVG;  i++) {
        clock_t start = clock();
        double s = sum(array, N, 1);
        exec_for_inc_1 += ((double)(clock()-start))/CLOCKS_PER_SEC;
    }
    exec_for_inc_1 /= AVG;

    // repeat to make sure result is consistent
    for (int r = 0; r < 2; r++) {
        for (int i = 0;  i <sizeof(INC)/sizeof(int); i++) {
            // clock measures processor time in units CLOCKS_PER_SEC
            clock_t start = clock();
            double s = sum(array, N, INC[i]);
            double exec_time = ((double)(clock()-start))/CLOCKS_PER_SEC;
            // check if we are getting the correct sum ...
            if (s != element_sum) printf("INCORRECT RESULT: %g != %g ", s, element_sum);
            printf("%4.1f X time for increment %9d\n", exec_time/exec_for_inc_1, INC[i]);
        }
        printf("\n");
    }
}
