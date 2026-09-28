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
       return;
     }
    table[idx] = key;
   
}

void search(int key){
       int idx = key%size;
       if(table[idx]!=-1){
            if(table[idx]!=key){
                  int temp = key +1;
                  while(table[temp%size]!=key){
                     temp +=1;
                  }
             idx = temp%size;
              
           }
           
            printf("%d is present at index %d\n",table[idx],idx);
       }
       else{
          printf("Key is not present\n");
        }
} 
void Delete(int key){
       int idx = key%size;
       
       if(table[idx]!=-1){
            if(table[idx]!=key){
                  int temp = key +1;
                  while(table[temp%size]!=key){
                     temp +=1;
                  }
             table[temp%size] = -1;
              
           }
           else{
             table[idx] = -1;
           }
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

     printf("Enter the Table size:");
     scanf("%d",&size);
               
     // initialising hash table with -1
     for(int i =0;i<size;i++){
        table[i] = -1;
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
                int m;
                printf("Enter number of IDs you want to manage or store:");
                scanf("%d",&m);
                printf("Enter the Employee IDs: ");
                int key;
                for(int i =0;i<m;i++){
                  scanf("%d",&key);
                  insert(key);
                }
                printf("Key inserted successfully!\n");
                
                break;
          case 2:
               // int keys;
                printf("Enter key you want to search:");
                scanf("%d",&key);
                search(key);
                break;
          case 3:
              //  int keys;
                printf("Enter key you want to delete:");
                scanf("%d",&key);
                Delete(key);
                break;
         case 4:
                printf("Hash table is:\n");
                display();
                break; 
         default:
                printf("enter right choice\n");
    
    }
    }while(choice);
 
    return 0;   
}            
     
     
     
     
