#include <stdio.h>
#include <stdlib.h>

// Define Node structure
struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;  // Global head pointer

// Display the linked list
void display() {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Insert at beginning
void insertAtBeginning(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

// Insert at end
void insertAtEnd(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

// Insert at a specific position (1-based index)
void insertAtPosition(int data, int position) {
    if (position < 1) {
        printf("Invalid position!\n");
        return;
    }

    if (position == 1) {
        insertAtBeginning(data);
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;

    struct Node* temp = head;
    for (int i = 1; i < position - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Delete from beginning
void deleteFromBeginning() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node* temp = head;
    head = head->next;
    free(temp);
}

// Delete from end
void deleteFromEnd() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }

    struct Node* temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;
}

// Delete from a specific position (1-based index)
void deleteFromPosition(int position) {
    if (head == NULL || position < 1) {
        printf("Invalid position or empty list!\n");
        return;
    }

    if (position == 1) {
        deleteFromBeginning();
        return;
    }

    struct Node* temp = head;
    for (int i = 1; i < position - 1 && temp->next != NULL; i++)
        temp = temp->next;

    if (temp->next == NULL) {
        printf("Position out of range!\n");
        return;
    }

    struct Node* toDelete = temp->next;
    temp->next = temp->next->next;
    free(toDelete);
}

// Reverse the linked list
void reverse() {
    struct Node *prev = NULL, *curr = head, *next = NULL;

    while (curr != NULL) {
        next = curr->next;     // Save next
        curr->next = prev;     // Reverse link
        prev = curr;
        curr = next;
    }

    head = prev;
}

// Main function to test operations
int main() {
    insertAtBeginning(30);
    insertAtBeginning(20);
    insertAtBeginning(10);
    printf("After inserting at beginning:\n");
    display();

    insertAtEnd(40);
    insertAtEnd(50);
    printf("After inserting at end:\n");
    display();

    insertAtPosition(25, 3);
    printf("After inserting 25 at position 3:\n");
    display();

    deleteFromBeginning();
    printf("After deleting from beginning:\n");
    display();

    deleteFromEnd();
    printf("After deleting from end:\n");
    display();

    deleteFromPosition(3);
    printf("After deleting from position 3:\n");
    display();

    reverse();
    printf("After reversing the list:\n");
    display();

    return 0;
}
