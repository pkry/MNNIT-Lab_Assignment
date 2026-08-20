#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node *top = NULL;

int size(){
    int count = 0;
    struct node* temp = top;
    while(temp!=NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

int is_empty(){
    return top==NULL;
}

void push(int value){
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if(newNode==NULL){
        printf("memory alocation failed:\n");
        return ;
    }
    newNode->data = value;
    newNode->next = top;
    top = newNode;
    printf("value is added in stack\n");
    return ;
}

void top_element(){
    
    if (is_empty())
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Top element: %d\n", top->data);
}

void pop()
{
    if (is_empty())
    {
        printf("Stack Underflow! Stack is empty.\n");
        return;
    }

    struct node *temp = top;
    int value = top->data;

    top = top->next;
    free(temp);

    printf("Popped element: %d\n", value);
}

int main(){
    int choice;
    int value;
    while(1){
        printf("===Choices available===\n");
        printf("1. Size\n");
        printf("2. Is Empty\n");
        printf("3. Push\n");
        printf("4. Top\n");
        printf("5. Pop\n");
        printf("6. Exit\n");
        printf("===========\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Size of stack: %d\n", size());
                break;

            case 2:
                if (is_empty())
                    printf("Stack is empty.\n");
                else
                    printf("Stack is not empty.\n");
                break;

            case 3:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;

            case 4:
                top_element();
                break;

            case 5:
                pop();
                break;

            case 6:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}