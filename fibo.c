#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

uint64_t *fibo;

uint64_t calcFibo(int nr) {
    if (nr == 0) {
        return 0;
    }
    if (nr == 1) {
        return 1;
    }
    if (fibo[nr] == 0) {
        fibo[nr] = calcFibo(nr - 1) + calcFibo(nr - 2);
    }
    return fibo[nr];
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Invalid number of elements\n");
        return -1;
    }
    fibo = (uint64_t *)malloc(sizeof(uint64_t) * (n + 1));
    if (fibo == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    for (int i = 0; i <= n; i++) {
        fibo[i] = 0;
    }
    uint64_t result = calcFibo(n);
    for(int i = 0; i <= n; i++) {
        printf("fibo[%d] = %" PRIu64 "\n", i, fibo[i]);
    }
    printf("Result: %" PRIu64 "\n", result);
    free(fibo);
    return 0;
}
