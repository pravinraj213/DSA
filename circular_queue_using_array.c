#include <stdio.h>
#define SIZE 5

int cqueue[SIZE];
int front = -1, rear = -1;

// Enqueue Operation
void enqueue(int value) {
    if ((front == 0 && rear == SIZE - 1) || (rear + 1) % SIZE == front) {
        printf("Queue Overflow\\n");
    } else {
        if (front == -1) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % SIZE;
        }
        cqueue[rear] = value;
    }
}

// Dequeue Operation
int dequeue() {
    if (front == -1) {
        printf("Queue Underflow\\n");
        return -1;
    } else {
        int temp = cqueue[front];
        if (front == rear) {
            front = rear = -1;  // Reset queue when only one element was present
        } else {
            front = (front + 1) % SIZE;
        }
        return temp;
    }
}

// Display Operation
void display() {
    if (front == -1) {
        printf("Queue is empty\\n");
    } else {
        printf("Circular Queue elements: ");
        int i = front;
        while (1) {
            printf("%d ", cqueue[i]);
            if (i == rear)
                break;
            i = (i + 1) % SIZE;
        }
        printf("\\n");
    }
}

// Main Function
int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    display();

    dequeue();
    dequeue();
    display();

    enqueue(50);
    enqueue(60);
    display();

    return 0;
}
