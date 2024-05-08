#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

//suma ponderata este maxima (in comparatie cu celelalte sume ponderate)
int calculateWeightedSum(int* numbers, int* weights, int size) {
    int maxSum = 0;
    int currentSum = 0;

    for (int i = 0; i < size; i++) {
        currentSum += numbers[i] * weights[i];

        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }

    return maxSum;
}
void printMaxWeightedSum(FILE *file, FILE *outputFile, int* numbers, int* weights, int size) {
    int maxSum = calculateWeightedSum(numbers, weights, size);
    int currentSum = 0;
    char phoneNumber[13];

    while (fgets(phoneNumber, sizeof(phoneNumber), file)) {
        currentSum = 0;

        for (int i = 0; i < size; i++) {
            currentSum += (phoneNumber[i + 4] - '0') * weights[i];
        }

        if (currentSum == maxSum) {
            fprintf(outputFile, "%s", phoneNumber);
        }
    }
}
void generatePhoneNumbers(FILE *file, int prefix, int digits) {
    if (digits == 0) {
        fprintf(file, "0722%06d\n", prefix);
        return;
    }

    for (int i = 0; i <= 9; i++) {
        generatePhoneNumbers(file, prefix * 10 + i, digits - 1);
    }
}

void printDivisibleByThree(FILE *file, FILE *outputFile) {
    char phoneNumber[13];
    while (fgets(phoneNumber, sizeof(phoneNumber), file)) {
        int lastThreeDigits = atoi(phoneNumber + 7);
        if (lastThreeDigits % 3 == 0 && strcmp(phoneNumber, "0722000000\n") != 0) {
            fprintf(outputFile, "%s", phoneNumber);
        }
    }
}

int main() {
    // Function declarations
    void generatePhoneNumbers(FILE *file, int prefix, int digits);
    void printDivisibleByThree(FILE *file, FILE *outputFile);
    void printMaxWeightedSum(FILE *file, FILE *outputFile, int* numbers, int* weights, int size);
    FILE *file = fopen("phone_numbers.txt", "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    FILE *file2 = fopen("phone_numbers_divisible_by_three.txt", "w");
    if(file2 == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    generatePhoneNumbers(file, 0, 6);
    fclose(file);

    file = fopen("phone_numbers.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    printDivisibleByThree(file, file2);
    fclose(file);
    fclose(file2);

    FILE *file3 = fopen("phone_numbers_max_weighted_sum.txt", "w");
    if (file3 == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    file = fopen("phone_numbers.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    int numbers[] = {1, 2, 3, 4, 5};
    int weights[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    printMaxWeightedSum(file, file3, numbers, weights, size);
    fclose(file);
    fclose(file3);
    printf("Phone numbers generated successfully.\n");
    return 0;
}
