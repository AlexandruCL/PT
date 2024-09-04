#include <stdio.h>

int n = 9;
int solutie(int k);
void afisare(int k);
int valid(int k);
int v[10]; // Adjusted the size to be able to handle up to `n` elements

void back(int k) {
    int i;
    for(i = 1; i <= n; i++) {
        v[k] = i;
        if(valid(k)) {
            if(solutie(k))
                afisare(k);
            else
                back(k + 1);
        }
    }
}

int solutie(int k) {
    return (k == 4); // We want exactly 5 elements (index 0 to 4)
}

int valid(int k) {
    int pare = 0, impare = 0;
    int i;

    for(i = 0; i <= k; i++) {
        if(v[i] == v[k] && i != k) // Check for duplicates
            return 0;
        if(v[i] % 2 == 0)
            pare++;
        else
            impare++;
    }

    if(pare > 3 || impare > 3)
        return 0;

    return 1;
}

void afisare(int k) {
    for(int i = 0; i <= k; i++) // Corrected loop to include `k`
        printf("%d ", v[i]);
    printf("\n"); // Add newline for better readability
}

int main() {
    back(0); // Start with k = 0
    return 0;
}
