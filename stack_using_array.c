#include <stdio.h>
#define MAX 100

int stack[MAX];
int top = -1;

// Push Operation
void push(int value) {
    if (top == MAX - 1) {
        printf("Stack Overflow\\n");
    } else {
        top++;
        stack[top] = value;
    }
}

// Pop Operation
int pop() {
    if (top == -1) {
        printf("Stack Underflow\\n");
        return -1;
    } else {
        return stack[top--];
    }
}

// Peek Operation (view top element)
int peek() {
    if (top == -1) {
        printf("Stack is empty\\n");
        return -1;
    } else {
        return stack[top];
    }
}

// Display Operation
void display() {
    if (top == -1) {
        printf("Stack is empty\\n");
    } else {
        printf("Stack elements: ");
        for (int i = top; i >= 0; i--) {
            printf("%d ", stack[i]);
        }
        printf("\\n");
    }
}

// Main function to test the stack
int main() {
    push(10);
    push(20);
    push(30);
    display();

    printf("Popped element: %d\\n", pop());
    display();

    printf("Top element: %d\\n", peek());

    return 0;
}
