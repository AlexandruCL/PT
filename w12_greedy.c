#include <stdio.h>
#define N 5
#define INT_MAX 10000000

int NextCityToFind(int CurrentC, int VisitedC[N], int m[N][N]){

    int MinimumDistance= INT_MAX;
    int NextC=-1;

    for(int i=0;i<N;i++){
        if(!VisitedC[i] && m[CurrentC][i]<MinimumDistance && m[CurrentC][i]){
            MinimumDistance=m[CurrentC][i];
            NextC=i;
        }
    }
    return NextC;
}
int main()
{
    int m[N][N]={
        {0,174,315,634,544},
        {174,0,152,0,595},
        {315,152,0,393,0},
        {634,544,393,0,0},
        {544,595,0,388,0}
    };
    int StartingC;
    printf("Select a city:\n Timisoara-0\n Oradea-1\n Cluj-Napoca-2\n Iasi-3\n Bucuresti-4\nType here the number coresponding to the city: ");

    scanf("%d",&StartingC);
    int VisitedC[N]={0};
    int TotalDistance=0;
    int Trip[N+1];
    VisitedC[StartingC]=1;
    Trip[0]=StartingC;
    for(int i=1;i<N;i++){
        int NextC=NextCityToFind(StartingC,VisitedC,m);
        if(NextC==-1){
            printf("We cannot make a complete trip\n");
            return -1;
        }
        VisitedC[NextC]=1;
        TotalDistance=TotalDistance+m[StartingC][NextC];
        Trip[i]=NextC;
        StartingC=NextC;
    }
    //TotalDistance=TotalDistance+m[StartingC][Trip[0]];
    Trip[N]=Trip[0];
    printf("TRIP: ");
    for(int j=0;j<N;j++){
        printf("%d-",Trip[j]);
    }
    printf("\n");
    printf("Total Distance: %d",TotalDistance);
    printf("\n");


    return 0;
}