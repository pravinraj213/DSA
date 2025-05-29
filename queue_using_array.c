#include <stdio.h>
#define MAX 100

int queue[MAX];
int front = -1, rear = -1;

// Enqueue Operation
void enqueue(int value) {
    if (rear == MAX - 1) {
        printf("Queue Overflow\\n");
    } else {
        if (front == -1) front = 0;
        rear++;
        queue[rear] = value;
    }
}

// Dequeue Operation
int dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue Underflow\\n");
        return -1;
    } else {
        int temp = queue[front];
        front++;
        return temp;
    }
}

// Display Operation
void display() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\\n");
    } else {
        printf("Queue elements: ");
        for (int i = front; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
        printf("\\n");
    }
}

// Main Function
int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();

    printf("Dequeued: %d\\n", dequeue());
    display();

    return 0;
}
