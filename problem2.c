#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 20

int maze[MAX][MAX];
int visited[MAX][MAX];
int n;
int rowDir[] = {1,0,0,-1};
int colDir[] = {0,-1,1,0};
char direction[] = {'D','L','R','U'};

int isValid(int row, int col)
{
    return (row >= 0 && row < n && col >= 0 && col < n
            && maze[row][col] == 1 &&
            visited[row][col] == 0);
}

void findPath(int row, int col,char path[],int pathLength){

         if(row == n-1 && col == n-1){
             path[pathLength] = '\0';
             printf("%s\n",path);
             return ;
          }
          
          int i ;
          visited[row][col] = 1;
          for (i = 0; i < 4; i++){
            int newRow = row + rowDir[i];
            int newCol = col + colDir[i];

            if (isValid(newRow, newCol)){
                  path[pathLength] = direction[i];

                findPath(newRow, newCol, path, pathLength + 1);
                path[pathLength] = '\0';
             }
          }

      
       visited[row][col] = 0;
}



int main(){
    
   

    printf("Enter the size of maze: ");
    scanf("%d", &n);
    char path[n];

    printf("Enter the maze (1 = open, 0 = blocked):\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &maze[i][j]);
            visited[i][j] = 0;
        }
    }

    /* Check starting and ending cells */
    if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0)
    {
        printf("No path exists.\n");
        return 0;
    }

    printf("Possible paths:\n");
    findPath(0, 0, path, 0);

    return 0;
}     
