#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef  struct node
{
    uint32_t number;
    double number_count;
    struct node* next;
}node;

double numberOfNodes = 0;

node *insert(node *head, uint32_t value)
{
    node *newnode;
    node *current;
    node *prev = NULL;
    

    if(head == NULL)
    {
        newnode = (node*)malloc(sizeof(node));
        if(newnode == NULL)
        {
            perror("Error in allocating memory for a newn node /n");
            exit(EXIT_FAILURE);
        }
        newnode->next = NULL;
        newnode->number_count = 1;
        newnode->number = value;
        head = newnode;
        return head;
    }
    current = head;
    while(current != NULL && current->number < value)
    {
        prev = current;
        current = current->next;
    }

    if(current != NULL && current->number == value)
    {
        current->number_count++;
        return head;
    }
    newnode = (node*)malloc(sizeof(node));
    if(newnode == NULL)
        {
            perror("Error in allocating memory for a newn node /n");
            exit(EXIT_FAILURE);
        }
    newnode->number  = value;
    newnode->number_count = 1;

    if(prev == NULL)
    {
        newnode->next = head;
        head = newnode;
    }
    else{
        newnode->next = current;
        prev->next = newnode;
    }
    return head;

}
void print_percentage(node *head, char *file)
{
    FILE *output = fopen(file, "w");
    if(output == NULL)
    {
        perror("Error in opening the output file \n");
        exit(EXIT_FAILURE);
    }

    while(head != NULL)
    {
        double percentage = (head->number_count / numberOfNodes)*100;
        fprintf(output, "%u : %.0lf : %.4lf%% \n", head->number, head->number_count, percentage);
        head = head->next;
    }
    fclose(output);
}

void freeList(node *head)
{
    node *temp;
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("Not enough arguments given \n");
        exit(EXIT_FAILURE);
    }
    FILE *input = fopen(argv[1], "rb");
    if(input == NULL)
    {
        perror("Error in opening the file \n");
        exit(EXIT_FAILURE);
    }
    node *head = NULL;
    uint32_t x;
    
    while(fread(&x, sizeof(uint32_t), 1, input) == 1)
    {
        head = insert(head, x);
        numberOfNodes++;       
    }
    fclose(input);

    print_percentage(head, argv[2]);
    freeList(head);
    return 0;

    
}