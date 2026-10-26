#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid1, pid2, pid3;

    // Create two pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        return 1;
    }

    // Process 1: Read file and filter numbers
    pid1 = fork();

    if (pid1 == 0) {
        int num;
        int arr[100];
        int count = 0;
        FILE *fp = fopen("input.txt", "r");

        if (fp == NULL) {
            perror("input.txt");
            exit(1);
        }

        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);

        while (fscanf(fp, "%d", &num) == 1) {
            if (num > 20) {
                arr[count++] = num;
            }
        }
        printf("Process 1:");
        printf("\n");
        for(int i =0;i<count;i++){
              printf("%d ",arr[i]);
        }
        printf("\n");
        write(pipe1[1], arr, sizeof(arr));
        write(pipe1[1], &count, sizeof(count));
        fclose(fp);
        close(pipe1[1]);
        exit(0);
    }

    // Process 2: Sort numbers
    pid2 = fork();

    if (pid2 == 0) {
        int arr[100],size;

        close(pipe1[1]);
        close(pipe2[0]);

       read(pipe1[0], arr, sizeof(arr));
       read(pipe1[0],&size, sizeof(size));

        close(pipe1[0]);

        // Sort in ascending order
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        
        printf("Process2:");
        printf("\n");
        printf("sorted data:");
        for(int i =0;i<size;i++){
              printf("%d ",arr[i]);
        }
        printf("\n");
        
        // Send sorted numbers to Process 3
        for (int i = 0; i < size; i++) {
            write(pipe2[1], &arr[i], sizeof(arr[i]));
        }

        close(pipe2[1]);
        exit(0);
    }

    // Process 3: Display sorted numbers
    pid3 = fork();

    if (pid3 == 0) {
        int num;

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[1]);

        printf("Process 3:");
        printf("\n");
        printf("Final output: ");

        while (read(pipe2[0], &num, sizeof(num)) == sizeof(num)) {
            printf("%d ", num);
        }

        printf("\n");

        close(pipe2[0]);
        exit(0);
    }

    // Parent closes all pipe ends
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    // Wait for all child processes
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 1);
    waitpid(pid3, NULL, 2);

    return 0;
}

