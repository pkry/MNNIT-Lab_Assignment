#include<stdio.h>
#include<stdlib.h>

int table[30];
int size;


void insert(int key){
    int idx = key%size;
    if(table[idx]!=-1){
       int temp = key +1;
       while(table[temp%size]!=-1){
             temp +=1;
       }
       table[temp%size] = key;
     }
    table[idx] = key;
    printf("Key inserted successfully!\n");
}

void search(int key){
       int idx = key%size;
       if(table[idx]!=-1){
            printf("%d is present at index %d\n",table[idx],idx);
       }
       else{
          printf("Key is not present\n");
        }
} 
void Delete(int key){
       int idx = key%size;
       if(table[idx]!=-1){
            table[idx] = -1;
            printf("key is deleted successfully\n");
       }
       else{
          printf("Key is not present\n");
        }
} 

void display(){
    printf("index     key\n");
    for(int i =0;i<size;i++){
       printf("%d     %d\n",i,table[i]);
     }
}

int main(){
 //    int size;  // hash table size
     printf("Enter the Table size:");
     scanf("%d",&size);
     int m;
     printf("Enter number of IDs you want to manage or store:");
     scanf("%d",&m);
     int key[m];
     printf("Enter the Employee IDs: ");
     for(int i =0;i<m;i++){
         scanf("%d",&key[i]);
     }
     
 //     int table[size]; // hash table
     
     // initialising hash table with -1
     for(int i =0;i<size;i++){
        table[i] = -1;
     }
     
     // inserting key in table
     for(int i =0;i<m;i++){
           insert(key[i]);
     }
     
     int choice;
     do{
     
     printf("Choice avialble:\n");
     printf("1 insert\n");
     printf("2 search\n");
     printf("3 delete\n");
     printf("4 display\n");
     
     
     printf("Enter your choice:");
     scanf("%d",&choice);
     switch(choice){
          case 1:
                int keys;
                printf("Enter key you want to insert:");
                scanf("%d",&keys);
                insert(keys);
                break;
          case 2:
               // int keys;
                printf("Enter key you want to search:");
                scanf("%d",&keys);
                search(keys);
                break;
          case 3:
              //  int keys;
                printf("Enter key you want to delete:");
                scanf("%d",&keys);
                Delete(keys);
                break;
         case 4:
                printf("Hash table is:\n");
                display();
                break; 
         default:
                printf("enter right choice");
    
    }
    }while(choice);
 
    return 0;   
}            
     
     
     
     
