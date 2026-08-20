#include<stdio.h>

void findCombinations(int arr[], int n, int target, int index, int combination[], int size, int *found){
       if(target==0){
          *found = 1;
          for(int i=0;i<size;i++){
            printf("%d",combination[i]);
            if(i<size-1){
                printf(",");
            }
          }
          printf("\n");
          return;
       }
       for(int i=index;i<n;i++){
            if(arr[i]>target) break;
            combination[size] = arr[i];
            findCombinations(arr,n,target-arr[i],i,combination,size+1,found);
       }
}


int main(){
    int n ;
    printf("Enter the size of array: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enetr the input array: ");
    for(int i =0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    int x;
    printf("Enter  the value of target:");
    scanf("%d",&x);

    // sort the input array

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    int combination[x + 1];
    int found = 0;

    findCombinations(arr, n, x, 0, combination, 0, &found);

    if (!found)
        printf("Empty\n");

    return 0;
   
}