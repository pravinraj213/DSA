#include <stdio.h>
#include <stdlib.h>

// Node structure for polynomial term
struct Node {
    int coeff;
    int power;
    struct Node* next;
};

// Create a new polynomial term
struct Node* createNode(int c, int p) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = c;
    newNode->power = p;
    newNode->next = NULL;
    return newNode;
}

// Insert a term at the end of the polynomial and return updated head
struct Node* insertTerm(struct Node* head, int c, int p) {
    struct Node* newNode = createNode(c, p);
    if (head == NULL)
        return newNode;

    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    return head;
}

// Display the polynomial
void display(struct Node* poly) {
    while (poly != NULL) {
        if (poly->coeff == 0) {
            poly = poly->next;
            continue;
        }

        if (poly->power == 0)
            printf("%d", poly->coeff);
        else if (poly->power == 1)
            printf("%dx", poly->coeff);
        else
            printf("%dx^%d", poly->coeff, poly->power);

        if (poly->next != NULL)
            printf(" + ");
        poly = poly->next;
    }
    printf("\n");
}

// Add or subtract two polynomials (sign = 1 for addition, -1 for subtraction)
struct Node* operatePoly(struct Node* p1, struct Node* p2, int sign) {
    struct Node* result = NULL;

    while (p1 != NULL && p2 != NULL) {
        if (p1->power > p2->power) {
            result = insertTerm(result, p1->coeff, p1->power);
            p1 = p1->next;
        } else if (p2->power > p1->power) {
            result = insertTerm(result, sign * p2->coeff, p2->power);
            p2 = p2->next;
        } else {
            int sum = p1->coeff + sign * p2->coeff;
            result = insertTerm(result, sum, p1->power);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        result = insertTerm(result, p1->coeff, p1->power);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        result = insertTerm(result, sign * p2->coeff, p2->power);
        p2 = p2->next;
    }

    return result;
}

// Main function to demonstrate polynomial addition and subtraction
int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* sum = NULL;
    struct Node* diff = NULL;

    // Polynomial 1: 3x^3 + 2x^2 + 1
    poly1 = insertTerm(poly1, 3, 3);
    poly1 = insertTerm(poly1, 2, 2);
    poly1 = insertTerm(poly1, 1, 0);

    // Polynomial 2: 2x^2 + 4x + 5
    poly2 = insertTerm(poly2, 2, 2);
    poly2 = insertTerm(poly2, 4, 1);
    poly2 = insertTerm(poly2, 5, 0);

    printf("Polynomial 1: ");
    display(poly1);

    printf("Polynomial 2: ");
    display(poly2);

    // Perform addition and subtraction
    sum = operatePoly(poly1, poly2, 1);
    diff = operatePoly(poly1, poly2, -1);

    printf("Sum: ");
    display(sum);

    printf("Difference: ");
    display(diff);

    return 0;
}

/*
Expected Output:
-----------------
Polynomial 1: 3x^3 + 2x^2 + 1
Polynomial 2: 2x^2 + 4x + 5
Sum: 3x^3 + 4x^2 + 4x + 6
Difference: 3x^3 + 0x^2 + -4x + -4
*/
