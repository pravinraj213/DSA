#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int power;
    struct Node* next;
};

struct Node* createNode(int c, int p) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = c;
    newNode->power = p;
    newNode->next = NULL;
    return newNode;
}

void insertTerm(struct Node** poly, int c, int p) {
    struct Node* newNode = createNode(c, p);
    if (*poly == NULL) {
        *poly = newNode;
    } else {
        struct Node* temp = *poly;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void display(struct Node* poly) {
    while (poly != NULL) {
        if (poly->power == 0) {
            // Just print the coefficient
            printf("%d", poly->coeff);
        } else if (poly->power == 1) {
            // Print with 'x' only
            if (poly->coeff == 1)
                printf("x");
            else
                printf("%dx", poly->coeff);
        } else {
            // General case
            if (poly->coeff == 1)
                printf("x^%d", poly->power);
            else
                printf("%dx^%d", poly->coeff, poly->power);
        }
        if (poly->next != NULL)
            printf(" + ");
        poly = poly->next;
    }
    printf("\n");
}

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
            if (sum != 0)
                insertTerm(&result, sum, p1->power);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
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

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* sum = NULL;

    // Example polynomial 1: 3x^3 + 2x^2 + 1
    insertTerm(&poly1, 3, 3);
    insertTerm(&poly1, 2, 2);
    insertTerm(&poly1, 1, 0);

    // Example polynomial 2: 5x^2 + 4x + 2
    insertTerm(&poly2, 5, 2);
    insertTerm(&poly2, 4, 1);
    insertTerm(&poly2, 2, 0);

    printf("Polynomial 1: ");
    display(poly1);

    printf("Polynomial 2: ");
    display(poly2);

    sum = addPoly(poly1, poly2);

    printf("Sum: ");
    display(sum);

    return 0;
}

// Output:
// Polynomial 1: 3x^3 + 2x^2 + 1
// Polynomial 2: 5x^2 + 4x + 2
// Sum: 3x^3 + 7x^2 + 4x + 3
