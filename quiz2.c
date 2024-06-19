#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
typedef struct node
{
    int x, y;
    unsigned distance;
    struct node *next;
    struct node *prev;
}node;

unsigned N=0;
unsigned a[MAX][MAX];

void append(node **head, unsigned value, int x, int y)
{
    node *newnode;
    node *last;
    if(*head == NULL)
    {
        newnode = (node *)malloc(sizeof(node));
        newnode->distance = value;
        newnode->x = x;
        newnode->y = y;
        newnode->next = NULL;
        newnode->prev = NULL;
        *head = newnode;
        
        return;
    }
    last = *head;
    while(last->next != NULL)
    {
        last = last->next;
    }
    newnode = (node *)malloc(sizeof(node));
    newnode->distance = value;
    newnode->x = x;
    newnode->y = y;
    newnode->next = NULL;
    newnode->prev = last;
    last->next = newnode;



}
int getN(char *file)
{
    FILE *in = fopen(file, "r");
    if(in == NULL)
    {
        perror("Error in opening input file");
        exit(EXIT_FAILURE);
    }
    char line[MAX];
    int count = 0;
    while(fgets(line, MAX, in))
    {   
        count ++;
    }
    N = atoi(line);
    fclose(in);
    return N;
}

void getMatrix(int n, char *file)
{
    FILE *in = fopen(file, "r");
    if(in == NULL)
    {
        perror("Error in opening input file");
        exit(EXIT_FAILURE);
    }
    char line[MAX];
    for(int i=0; i<n; i++)
    {
        fgets(line, MAX, in);
        char *token = strtok(line, " ");
        a[i][0] = atoi(token);
        for(int j=1; j<n; j++)
        {
            token = strtok(NULL, " ");
            a[i][j] = atoi(token);
        }
    }
    fclose(in);
}

node* makeList(node *head)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(a[i][j] != 0)
            {
                append(&head, a[i][j], i, j);
            }
            
        }
    }
    return head;
}
void make_circularList(node *head)
{
    node *temp = head;
    while(temp->next!=NULL)
    {
        temp = temp->next;
    }
    temp->next = head;
    head->prev = temp;
}

void display(struct node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    
    node* current = head;

    do {
        printf("(%d, %d)-%d->",current->x, current->y, current->distance);
        current = current->next;
    } while (current->next != head);
    
    printf("(%d, %d)-%d->(%d, %d)",current->x, current->y, current->distance, head->x, head->y);
    	
    printf("\n");
}

void chooseHead(node *head)
{
    printf("Type the coordinates of the node you want to start with: ");
    int i, j;
    scanf("%d %d", &i, &j);
    node *temp = head;
    if(temp->x == i && temp->y == j)
    {
        display(temp);
        return;
    }
    else{
        do
        {
            temp = temp->next;
        } while (temp->x!=i && temp->y !=j && temp!=head);
        
    }
    display(temp);
}
int main(int argc, char **argv)
{
    printf("this is the number N %d \n", getN(argv[1])); //debugging purposes only
    getMatrix(N, argv[1]);
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            printf("%d ", a[i][j]); //debugging purposes only
        }
        putchar('\n');
    }

    node *head = NULL;
    head = makeList(head);
    make_circularList(head);
    display(head); //debugging purposes only
    chooseHead(head);
    return 0;
}