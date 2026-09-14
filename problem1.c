#include<stdio.h>
#include<stdlib.h>
int count = 0;
int isSafe(int arr[][10],int row,int col,int n){

           for(int i =0;i<row;i++){
                if(arr[i][col]){
                    return 0;
                 }
            }
            
            int i =row-1,j = col-1;
            while(i>=0 && j>=0){
                  if(arr[i][j]){
                    return 0;
                  }
                  i--;
                  j--;
            }
            
            i = row-1;
            j = col+1;
            while(i>=0 && j<n){
                 if(arr[i][j]){
                    return 0;
                  }
                  i--;
                  j++;
             }
         return 1;
}



void solve(int arr[][10],int n,int row,int q,int total){
          if(row>=n){
          if(q==total){
             count = count+1;
             printf("[%d].\n",count);
             for(int i =0;i<n;i++){
                for(int j =0;j<n;j++){
                   printf("%d ",arr[i][j]);
                 }
                 printf("\n");
              }
              printf("\n");
             
          }
           return ;
        }
       if((n-row+q)<total) return ;
       solve(arr,n,row+1,q,total);
       for(int i = 0; i < n; i++){
        
          if(isSafe(arr, row, i,n)){
                arr[row][i] = 1;
                solve(arr,n,row + 1,q+1,total);
            
            // backtrack
            arr[row][i] = 0; 
        }
    }
}
int main(){

      int n ;
      printf("Enter the size of chess board: ");
      scanf("%d",&n);
      int arr[n][10];
      for(int i =0;i<n;i++){
           for(int j =0;j<10;j++){
               arr[i][j] = 0;
           }
      }
      int q;
      printf("Enter the number queens :");
      scanf("%d",&q);
      solve(arr,n,0,0,q);
      
      return 0;
}
