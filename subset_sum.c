#include<stdio.h>
#include<stdlib.h>

int res[30];
int size = 0;
bool flag = false;
void printfun(int res[30]){
       for(int j =0;j<size;j++){
          printf("%d ",res[j]);
        }
        printf("\n");
}

void solve(int arr[],int target,int csum,int i,int n){
       
        if(csum == target){
           printfun(res);
           flag = true;
           return;
        }
        if(i>=n){
            return ;
        }
      
        
        if(arr[i]+csum<=target){
            res[size]= arr[i];
            size++;
            solve(arr,target,csum+arr[i],i+1,n);
            size--;
        }
        solve(arr,target,csum,i+1,n);
        
        return ;
}
        


int main(){
      int n ;
      printf("Enter the size of set:");
      scanf("%d",&n);
      int arr[n];
      printf("Enter the element of set:");
      for(int i =0;i<n;i++){
         scanf("%d",&arr[i]);
      }
      
      int target;
      printf("Enter the value of target sum:");
      scanf("%d",&target);
      
      printf("The subset with given sum is:\n");
      solve(arr,target,0,0,n);
      if(!flag){
          printf("!Subset not found with target sum\n");
       }
      return 0;
}
