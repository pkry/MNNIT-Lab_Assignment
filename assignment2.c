#include<stdio.h>


void reverse(int arr[],int st,int end){
    while(st<end){
        int temp = arr[st];
        arr[st] = arr[end];
        arr[end] = temp;
        st++;
        end--;
    }
}



void rotateArray(int arr[],int n,int d){
     d =d%n;
     reverse(arr,0,d-1);
     reverse(arr,d,n-1);
     reverse(arr,0,n-1);
}


void printarray(int arr[],int n){
    for(int i=0;i<n;i++){
        printf("%d",arr[i]);
    }
    printf("\n");
}


int main(){
    int n;
    printf("Enetr the size of array: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enetr the array element: ");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int d;
    printf("Enetr the distance of left rotation: ");
    scanf("%d",&d);
    printf("The original array is: ");
    printarray(arr,n);
    rotateArray(arr,n,d);
    printf("The rotated array is: ");
    printarray(arr,n);
    return 0;
}