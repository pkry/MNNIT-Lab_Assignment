#include<stdio.h>

int main(){
    int n;
    int relation[100][100];
    int reflexive = 1;
    int symmetric = 1;

    printf("Enter the number of elemens in the set: ");
    scanf("%d",&n);
    printf("Enter the relation matrix of(%d X %d):",n,n);

    for(int i =0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&relation[i][j]);
        }
    }

    // check for reflexive
        for (int i = 0; i < n; i++) {
        if (relation[i][i] != 1) {
            reflexive = 0;
            break;
        }
    }

    // Check Symmetry
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (relation[i][j] != relation[j][i]) {
                symmetric = 0;
                break;
            }
        }

        if (symmetric == 0)
            break;
    }

        // Display results
    if (reflexive)
        printf("Reflexive\n");
    else
        printf("Not Reflexive\n");

    if (symmetric)
        printf("Symmetric\n");
    else
        printf("Not Symmetric\n");

    return 0;

}