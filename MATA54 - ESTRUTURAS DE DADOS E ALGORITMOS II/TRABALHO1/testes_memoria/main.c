#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../linearHashing.c"

int totalPages(linearHashing *unit) {
    int r = 0;
    int nlists = (1 << unit->l) * unit->m + unit->N;

    for (int i = 0; i < nlists; i++) {
        int size = listSize(unit->lists[i]);
        r += size;
    }
    return r;
}

// A utility function to swap to integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// A function to generate a random permutation of arr[]
void randomize(int arr[], int n) {
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand(time(NULL));

    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n - 1; i > 0; i--) {
        // Pick a random index from 0 to i
        int j = rand() % (i + 1);

        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}

int test(int size, int m, int page_size, float alpha_max) {
    int in[size];

    for (int i = 0; i < size; i++) {
        in[i] = i;
    }
    randomize(in, size);

    float alpha_min = 0.2; // Anything, we don't care about it here :D

    linearHashing *unit = NewlinearHashing(m, alpha_max, alpha_min, page_size);
    searchResponse result;

    for (int i = 0; i < size; i++) {
        Insert(unit, in[i]);
    }

    int t = totalPages(unit);
    FreelinearHashing(unit);

    return t;
}

int main() {
    for (int n = 10; n <= 1000000; n *= 10) {
        for (float alpha_max = 0.1; alpha_max <= 1.0; alpha_max += 0.1) {
            for (int p = 2; p <= 128; p *= 2) {
                int t = test(n, 2, p, alpha_max); 
                printf("%-8d %.1f %-3d %-8d %.2f\n", n, alpha_max, p, t, (float)n / (p*t));    // Qtd de chaves, alpha max, tam. de pagina, paginas criadas e uso real.
            }
        }
    }
}