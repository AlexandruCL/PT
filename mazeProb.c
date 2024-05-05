#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 1000

int line, col;
char **maze = NULL;
int dx[] = { 0, 1, 0, -1};
int dy[] = {-1, 0, 1,  0};
FILE* input;
FILE* output;
 
void readMaze(FILE* input, int* startX, int* startY)
{
    char c;
    unsigned i = 0, j = 0;
    maze = malloc(line * sizeof(char*));
    for(unsigned k = 0; k < line; k++)
        *(maze + k) = malloc(col * sizeof(char));
    while(!feof(input))
    {
        c = fgetc(input);
        if(c == '#' || c == ' ' || c == 'S' || c == 'E')
        {
            *((*(maze+i))+j) = c;
            if(c == 'S')
            {
                *startX = i;
                *startY = j;
            }
            j++;
            if(j >= col) 
            {
                j = 0;
                i++;
            }
        }
    }
}
 
int valid(int i, int j, int k)
{    
    return (i + dy[k]) >= 0 && (i + dy[k]) < line &&
           (j + dx[k]) >= 0 && (j + dx[k]) < col &&
           (maze[i + dy[k]][j + dx[k]] == ' ' || maze[i + dy[k]][j + dx[k]] == 'E');
}
 
 
void printMaze(FILE* output)
{
    for(unsigned i = 0; i < line; i++)
    {
        for(unsigned j = 0; j < col; j++)
            fprintf(output, "%c", maze[i][j]);
        fprintf(output, "\n");
    }
}
 
void move(int i, int j)
{
    if(maze[i][j] == 'E')
    {
        printf("E FOUND");
        printMaze(output);
        exit(0);
    }
 
    maze[i][j] = '.';
    for(unsigned k = 0; k < 4; k++)
        if(valid(i, j, k))
            move(i + dy[k], j + dx[k]);
    maze[i][j] = ' ';
}
 
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./mazeSolver inputFileName outputFileName\n");
        return 1;
    }
    input = fopen(argv[1], "r");
    if(!input)
    {
        printf("Error opening the input file.\n");
        return 2;
    }
    output = fopen(argv[2], "w");
    if(!output)
    {
        printf("Error opening the output file.\n");
        return 2;
    }
 
    int starti, startj;
    char buf[MAX_SIZE];
    fgets(buf, MAX_SIZE, input);
    col = strlen(buf) - 1; // -1 to exclude /n
    if(col > MAX_SIZE)
    {
        printf("Maze is too large - too many columns.\n");
        return 3;
    }
    fseek(input, 0, SEEK_END);
    line = ftell(input) / col;
    if(line > MAX_SIZE)
    {
        printf("Maze is too large - too many lines.\n");
        return 3;
    }
    fseek(input, 0, SEEK_SET);
    readMaze(input, &starti, &startj);
    printf("%d %d\n", starti, startj);
    move(starti, startj);
 
    for(int i = 0; i < line; i++)
        free(*(maze+i));
    free(maze);
    fclose(input);
    fclose(output);
    return 0;
}