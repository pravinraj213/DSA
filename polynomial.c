#include <stdio.h>
#include <stdlib.h>

// Node structure for polynomial term
struct Node {
    int coeff;
    int power;
    struct Node* next;
};

// Create new node
struct Node* createNode(int c, int p) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->coeff = c;
    temp->power = p;
    temp->next = NULL;
    return temp;
}

// Insert term at end (assumes input polynomials sorted by power desc)
void insertTerm(struct Node** poly, int c, int p) {
    struct Node* newNode = createNode(c, p);
    if (*poly == NULL) {
        *poly = newNode;
    } else {
        struct Node* temp = *poly;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
}

// Add two polynomials
struct Node* addPoly(struct Node* p1, struct Node* p2) {
    struct Node* result = NULL;
    while (p1 != NULL && p2 != NULL) {
        if (p1->power > p2->power) {
            insertTerm(&result, p1->coeff, p1->power);
            p1 = p1->next;
        } else if (p2->power > p1->power) {
            insertTerm(&result, p2->coeff, p2->power);
            p2 = p2->next;
        } else {
            int sum = p1->coeff + p2->coeff;
            if (sum != 0) insertTerm(&result, sum, p1->power);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    // Add remaining terms
    while (p1 != NULL) {
        insertTerm(&result, p1->coeff, p1->power);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        insertTerm(&result, p2->coeff, p2->power);
        p2 = p2->next;
    }
    return result;
}

// Display polynomial
void displayPoly(struct Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->power);
        if (poly->next != NULL) printf(" + ");
        poly = poly->next;
    }
    printf("\n");
}

int main() {
    struct Node *poly1 = NULL, *poly2 = NULL, *sum = NULL;

    // Polynomial 1: 3x^4 + 2x^3 + x^1
    insertTerm(&poly1, 3, 4);
    insertTerm(&poly1, 2, 3);
    insertTerm(&poly1, 1, 1);

    // Polynomial 2: 4x^3 + 2x^2 + 1
    insertTerm(&poly2, 4, 3);
    insertTerm(&poly2, 2, 2);
    insertTerm(&poly2, 1, 0);

    printf("Polynomial 1: ");
    displayPoly(poly1);

    printf("Polynomial 2: ");
    displayPoly(poly2);

    sum = addPoly(poly1, poly2);

    printf("Sum: ");
    displayPoly(sum);

    return 0;
}
