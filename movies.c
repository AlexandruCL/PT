#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Movie {
    int year;
    char title[100];
    double budget;
    struct Movie *next;
} Movie;

Movie *createMovie(int year, const char *title, double budget) {
    Movie *newMovie = (Movie *)malloc(sizeof(Movie));
    if (newMovie == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newMovie->year = year;
    strcpy(newMovie->title, title);
    newMovie->budget = budget;
    newMovie->next = NULL;
    return newMovie;
}

void insertSorted(Movie **head, Movie *newMovie) {
    Movie *current;
    if (*head == NULL || ((*head)->year > newMovie->year) || ((*head)->year == newMovie->year && strcmp((*head)->title, newMovie->title) > 0)) {
        newMovie->next = *head;
        *head = newMovie;
    } else {
        current = *head;
        while (current->next != NULL && (current->next->year < newMovie->year || (current->next->year == newMovie->year && strcmp(current->next->title, newMovie->title) < 0))) {
            current = current->next;
        }
        newMovie->next = current->next;
        current->next = newMovie;
    }
}

void printList(Movie *head) {
    printf("Release Year | Title                                          | Budget\n");
    printf("----------------------------------------------\n");
    while (head != NULL) {
        printf("%12d | %-30s | %.2f\n", head->year, head->title, head->budget);
        head = head->next;
    }
}

void freeList(Movie *head) {
    Movie *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    char line[256];
    Movie *head = NULL;

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        int year;
        char title[100];
        double budget;
    // year,imdb,title,test,clean_test,binary,budget,domgross,intgross,code,budget_2013$,domgross_2013$,intgross_2013$,period code,decade code
        if (sscanf(line, "%d,%*[^,],%99[^,],%*[^,],%*[^,],%*[^,],%lf,%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,]", &year, title, &budget) == 3) {
            Movie *newMovie = createMovie(year, title, budget);
            insertSorted(&head, newMovie);
        } else {
            printf("Invalid format in line: %s", line);
        }
    }

    fclose(file);

    printList(head);

    freeList(head);

    return 0;
}
