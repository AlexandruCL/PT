#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxsonglength 100
#define maxartistlength 100
#define max_entries 3000

typedef struct{
    char song[maxsonglength];
    char artist[maxartistlength];
    int realaseyear;
}SongInfo;

int main(int argc, char *argv[]){
    if(argc!=3){
        printf("Usage: %s <file-path><year>\n", argv[0]);
        return 1;
    }
    char *filepath = argv[1];
    int target_year=atoi(argv[2]);
    FILE *file = fopen(filepath,"r");
    if(file==NULL){
        perror("Error oppening the csv file");
        exit(1);
    }
    SongInfo songs[max_entries];
    int num_songs=0;
    char line[maxsonglength+maxartistlength+10];
    while (fgets(line,sizeof(line),file)){
        char *token=strtok(line,",");

        if(token==NULL) continue;  

        strcpy(songs[num_songs].song,token);

        token=strtok(NULL,",");

        if(token==NULL) continue;  

        strcpy(songs[num_songs].artist,token);

        token=strtok(NULL,",");

        if(token==NULL) continue;

        songs[num_songs].realaseyear=atoi(token);
        if(atoi(token)==target_year){
 
            printf("<%s> by <%s> released in <%d>\n",songs[num_songs].song,songs[num_songs].artist,songs[num_songs].realaseyear);
        }

        num_songs++;

        if(num_songs>=max_entries){
            printf("Exceeded max nr of entries.\n");
            break;
        }
    }
    fclose(file);
    return 0;
}