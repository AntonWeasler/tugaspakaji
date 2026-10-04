#include <stdio.h>
#include <omp.h>

int main(void)
{
    enum { N = 8 };
    double result[N];
    double serial[N];
    int owner[N];

    for (int i = 0; i < N; ++i) {
        double total = 0.0;
        int work = 100000 * (i + 1);

        for (int k = 1; k <= work; ++k) {
            total += 1.0 / k;
        }

        serial[i] = total;
    }

    #pragma omp parallel default(none) shared(result, owner)
    {
        #pragma omp single
        {
            for (int i = 0; i < N; ++i) {
                #pragma omp task default(none) firstprivate(i) shared(result, owner)
                {
                    double total = 0.0;
                    int work = 100000 * (i + 1);

                    for (int k = 1; k <= work; ++k) {
                        total += 1.0 / k;
                    }

                    result[i] = total;
                    owner[i] = omp_get_thread_num();
                }
            }

            #pragma omp taskwait
        }
    }

    int errors = 0;

    for (int i = 0; i < N; ++i) {
        if (result[i] != serial[i]) {
            errors++;
        }

        printf("task=%d thread=%d parallel=%.8f serial=%.8f\n",
               i, owner[i], result[i], serial[i]);
    }

    printf("errors=%d\n", errors);

    return errors != 0;
}


