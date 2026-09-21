#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Student{
      
      int rollNo;
      char name[50];
      int mark;
      struct Student* left;
      struct Student* right;
};

// create new node
struct Student* createNode(int rollNo,char name[],int mark){
    struct Student* newNode =(struct Student*)malloc(sizeof(struct Student));

    newNode->rollNo = rollNo;
    strcpy(newNode->name, name);
    newNode->mark = mark;

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// add node in tree

struct Student* insert(struct Student* root,int rollNo,char name[],int mark){
    if (root == NULL) {
        return createNode(rollNo, name, mark);
    }

    if (rollNo < root->rollNo) {
        root->left = insert(root->left, rollNo, name, mark);
    }
    else if (rollNo > root->rollNo) {
        root->right = insert(root->right, rollNo, name, mark);
    }
    else {
        printf("Roll Number already exists!\n");
    }

    return root;
} 

// search

struct Student* search(struct Student *root, int rollNo) {
    if (root == NULL || root->rollNo == rollNo) {
        return root;
    }

    if (rollNo < root->rollNo) {
        return search(root->left, rollNo);
    }

    return search(root->right, rollNo);
}

// find minNode

struct Student* minNode(struct Student* root){
         if(root == NULL){
            return NULL;
          }
         else if(root->left==NULL){
            return root;
         }
         else{
           return minNode(root->left);
          }
}
         

// delete

struct Student* deleteNode(struct Student *root, int rollNo) {
    if (root == NULL) {
        return root;
    }

    if (rollNo < root->rollNo) {
        root->left = deleteNode(root->left, rollNo);
    }
    else if (rollNo > root->rollNo) {
        root->right = deleteNode(root->right, rollNo);
    }
    else{
         // if root has no child
         if(root->left == NULL || root->right == NULL){
              free(root);
              return NULL;
          }
          
          // root has only left child
          else if(root->right == NULL){
               struct Student* temp = root->left;
               free(root);
               return temp;
           }
           
           // root has only right child
           else if(root->left == NULL){
                 
              struct Student* temp = root->right;
               free(root);
               return temp;
            }
            
            // root has both child
            else{
               struct Student* temp = minNode(root->right);
              
              root->rollNo = temp->rollNo;
              strcpy(root->name, temp->name);
              root->mark = temp->mark;

              root->right = deleteNode(root->right, temp->rollNo);
        }
    }

    return root;
}

// display students

// inorder

void inorder(struct Student* root){
       if(root== NULL){
          return ;
       }
       inorder(root->left);
       printf("Name: %s , RollNo. %d, Mark:%d",root->name,root->rollNo,root->mark);
       inorder(root->right);
}

// preorder

void preorder(struct Student* root){
       if(root== NULL){
          return ;
       }
       
       printf("Name: %s , RollNo. %d, Mark:%d",root->name,root->rollNo,root->mark);
       preorder(root->left);
       preorder(root->right);     
}

// postorder

void postorder(struct Student* root){
       if(root== NULL){
          return ;
       }
       
       printf("Name: %s , RollNo. %d, Mark:%d",root->name,root->rollNo,root->mark);
       postorder(root->right);
       postorder(root->left);     
}

// highest mark student

void findHighestMark(struct Student* root,struct Student* highest){
        if(root==NULL){
           return ;
        }
        if(highest == NULL || root->mark > highest->mark){
             highest = root;
         }
         findHighestMark(root->left,highest);
         findHighestMark(root->right,highest);
}

int main(){
      int rollNo;
      char name[50];
      int mark;
      struct Student* root = NULL;
      struct Student* student;
      struct Student* highest = NULL;
      
      int choice;
      do{
      printf("Enter the choice No. available choices are:\n");
      printf("1. insert");
      printf("2. delete");
      printf("3. search");
      printf("4. inorder traverse");
      printf("5. preorder traverse");
      printf("6. postorder traverse");
      printf("7. student with highest mark");
      
      scanf("%d",&choice);
      
      switch(choice){
         case 1:
             printf("Enter RollNo.: ");
             scanf("%d",&rollNo);
             printf("Enter Name: ");
             scanf("%s",name);
             printf("Enter Mark: ");
             scanf("%d",&mark);
             root = insert(root,rollNo,name,mark);
             printf("successfully inserted");
             break;
             
         case 2:
              printf("Enter rollNo of student to delete: ");
              scanf("%d",&rollNo);
              student = search(root,rollNo);
              if (student != NULL) {
                    root = deleteNode(root, rollNo);
                    printf("Student record deleted successfully.\n");
               }
               else {
                    printf("Student with Roll Number %d not found.\n",
                           rollNo);
                }
               break;
               
         case 3:
               printf("Enter rollNo to search: ");
               scanf("%d",&rollNo);
               student = search(root,rollNo);
               if(student != NULL){
                   printf("Name: %s, RollNo: %d, Mark: %d",student->name,student->rollNo,student->mark);
               }
               else{
                  printf("Not found");
                }
                break;
           
           case 4:
                  inorder(root);
                   break;
           case 5:
                  preorder(root);
                  break;
           case 6:
                  postorder(root);
                  break;
           case 7:
                  findHighestMark(root,highest);
                  if(highest!=NULL){
                     printf("Toper student Name: %s,RollNo: %d, Mark: %d",highest->name,highest->rollNo,highest->mark);
                  }
                  else{
                    printf("first give data");
                  }
                  break;
            default:
                printf("enter write choice");
      } 
      }while(choice!=8);
      
      return 0;
 }
             
      










