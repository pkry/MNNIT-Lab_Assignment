#include<stdio.h>
#include<stdlib.h>

#define n 5

void printSolution(int color[],char subject[][30]){
    printf("Valid assignment found:\n");
    for(int i =0;i<n;i++){
        printf("%s -> slot %d\n",subject[i],color[i]);
     }
}

bool isSafe(int v,int graph[][n],int color[] ,int c){
      for(int i =0;i<n;i++){
          if(graph[v][i] == 1 && color[i] == c){
             return false;
           }
       }
       return true;
}


bool graphColoringUtil(int graph[][n],int m,int color[],int v){
         if(v==n){
           return true;
          }
         
         for(int c= 1;c<=m;c++){
            if(isSafe(v,graph,color,c)){
                color[v] = c;
                if(graphColoringUtil(graph,m,color,v+1) == true){
                    return true;
                }
                color[v] = 0;
            }
        }
        return false;
 }
            

void graphColoring(int graph[][n],int m,char subject[][30]){
     int color[n] ={0};
     
     if(graphColoringUtil(graph,m,color,0)==false){
         printf("Not possible\n");
         return ;
     }
     
     printSolution(color,subject);
     return ;
}


int main(){
      
      char subject[n][30];
      printf("Enter the subjects:\n");
      for(int i =0;i<n;i++){
         scanf("%s",subject[i]);
       }
      
      int graph[n][n];
      for(int i =0;i<n;i++){
          for(int j =0;j<n;j++){
             graph[i][j] = 0;
           }
       }
       
      int c1;
      printf("How many conflict?:");
      scanf("%d",&c1);
      printf("Enter the conflict pair:\n");
      for(int i =0;i<c1;i++){
          int u,v;
          scanf("%d %d",&u,&v);
          graph[u][v] = 1;
          graph[v][u] = 1;
      }
      
      int maxSlot;
      printf("Enter the maximum slot:");
      scanf("%d",&maxSlot);
      
      graphColoring(graph,maxSlot,subject);
      return 0;
 }
