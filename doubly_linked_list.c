#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev, *next;
};

struct Node* head = NULL;

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(int data) {
    struct Node* newNode = createNode(data);
    newNode->next = head;
    if (head) head->prev = newNode;
    head = newNode;
}

void insertAtEnd(int data) {
    struct Node* newNode = createNode(data);
    if (!head) {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

void insertAtPosition(int data, int pos) {
    if (pos == 1) {
        insertAtBeginning(data);
        return;
    }
    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++)
        temp = temp->next;
    if (temp == NULL) return;
    struct Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next)
        temp->next->prev = newNode;
    temp->next = newNode;
}

void deleteFromBeginning() {
    if (!head) return;
    struct Node* temp = head;
    head = head->next;
    if (head) head->prev = NULL;
    free(temp);
}

void deleteFromEnd() {
    if (!head) return;
    if (!head->next) {
        free(head);
        head = NULL;
        return;
    }
    struct Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->prev->next = NULL;
    free(temp);
}

void deleteFromPosition(int pos) {
    if (!head) return;
    if (pos == 1) {
        deleteFromBeginning();
        return;
    }
    struct Node* temp = head;
    for (int i = 1; i < pos && temp != NULL; i++)
        temp = temp->next;
    if (temp == NULL) return;
    if (temp->prev) temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    free(temp);
}

void displayForward() {
    struct Node* temp = head;
    while (temp) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    // Insert 10 at beginning: List = 10
    insertAtBeginning(10);
    // Insert 20 at end: List = 10 <-> 20
    insertAtEnd(20);
    // Insert 15 at position 2: List = 10 <-> 15 <-> 20
    insertAtPosition(15, 2);
    printf("List after insertions:\n");
    displayForward();  // Output: 10 <-> 15 <-> 20 <-> NULL

    // Delete from beginning: removes 10, List = 15 <-> 20
    deleteFromBeginning();
    // Delete from end: removes 20, List = 15
    deleteFromEnd();
    // Insert 25 at end: List = 15 <-> 25
    insertAtEnd(25);
    // Insert 30 at end: List = 15 <-> 25 <-> 30
    insertAtEnd(30);
    // Delete node at position 2: removes 25, List = 15 <-> 30
    deleteFromPosition(2);

    printf("List after deletions:\n");
    displayForward();  // Output: 15 <-> 30 <-> NULL

    return 0;
}
