#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
   int pipe1[2],pipe2[2];
   
   int n ;
   printf("Enter the size of array:");
   scanf("%d",&n);
   int arr[n];
   printf("Enter the element of the array:");
   for(int i =0;i<n;i++){
      scanf("%d",&arr[i]);
   }
   
   pid_t pid;
   
   int sum =0,maximum;
   float avg;
   
   if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        return 1;
    }
   
   pid = fork();
   
   if(pid<0){
     printf("process creation failed");
     return 1;
   }
   if(pid>0){
     //parent process
     close(pipe1[0]);
     close(pipe2[1]);
     
     write(pipe1[1], &n, sizeof(n));
     write(pipe1[1], arr, sizeof(arr));
     
     close(pipe1[1]);
     
     read(pipe2[0],&sum,sizeof(sum));
     read(pipe2[0],&maximum,sizeof(maximum));
     read(pipe2[0],&avg,sizeof(avg));
     
     close(pipe2[0]);
     
     //display
     printf("Parent process:\n");
     printf("Recieved result from child:");
     
     printf("\nSum = %d", sum);
     printf("\nAverage = %.2f", avg);
     printf("\nMaximum = %d\n", maximum);

     wait(NULL);
   }
   else{
      //child process
      printf("Chile process:");
      int size;
      int data[1000];
      
      close(pipe1[1]);
      close(pipe2[0]);
      
      read(pipe1[0],&size,sizeof(size));
      read(pipe1[0],&data,size*sizeof(int));
      
      close(pipe1[0]);
      
      sum = 0;
      maximum = data[0];
      
      for(int i =0;i<size;i++){
        sum = sum + data[i];
        if(data[i]>maximum){
           maximum = data[i];
        }
      }
      
      avg = (float)sum/size;
      
     printf("\nRecieved array:");
     for(int i =0;i<n;i++){
        printf("%d, ",arr[i]);
     }
      
     printf("\nSum = %d", sum);
     printf("\nAverage = %.2f", avg);
     printf("\nMaximum = %d\n\n", maximum);
      
      write(pipe2[1], &sum, sizeof(sum));
      write(pipe2[1], &maximum, sizeof(maximum));
      write(pipe2[1], &avg, sizeof(avg));
      

      close(pipe2[1]);

      exit(0);
   }
   
   return 0;
}
      
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
      
