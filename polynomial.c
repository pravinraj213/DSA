#include <stdio.h>
#include <stdlib.h>

// Node to represent a term in the polynomial
struct Node {
    int coeff;
    int power;
    struct Node* next;
};

// Function to create a new term node
struct Node* createNode(int coeff, int power) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->power = power;
    newNode->next = NULL;
    return newNode;
}

// Insert term in decreasing order of power
void insertTerm(struct Node** poly, int coeff, int power) {
    struct Node* newNode = createNode(coeff, power);

    // First node or insert before head
    if (*poly == NULL || power > (*poly)->power) {
        newNode->next = *poly;
        *poly = newNode;
    }
    else {
        struct Node* temp = *poly;
        while (temp->next != NULL && temp->next->power > power)
            temp = temp->next;

        // If power already exists, add coefficients
        if (temp->next != NULL && temp->next->power == power) {
            temp->next->coeff += coeff;
            free(newNode);
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}

// Display polynomial
void display(struct Node* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }

    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->power);
        if (poly->next != NULL && poly->next->coeff >= 0)
            printf(" + ");
        poly = poly->next;
    }
    printf("\n");
}

// Add two polynomials and return the result
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->power > poly2->power) {
            insertTerm(&result, poly1->coeff, poly1->power);
            poly1 = poly1->next;
        }
        else if (poly1->power < poly2->power) {
            insertTerm(&result, poly2->coeff, poly2->power);
            poly2 = poly2->next;
        }
        else {
            insertTerm(&result, poly1->coeff + poly2->coeff, poly1->power);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    // Add remaining terms
    while (poly1 != NULL) {
        insertTerm(&result, poly1->coeff, poly1->power);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insertTerm(&result, poly2->coeff, poly2->power);
        poly2 = poly2->next;
    }

    return result;
}

// Main function to demonstrate operations
int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* sum = NULL;

    // Polynomial 1: 3x^4 + 2x^3 + x
    insertTerm(&poly1, 3, 4);
    insertTerm(&poly1, 2, 3);
    insertTerm(&poly1, 1, 1);

    // Polynomial 2: 4x^3 + 2x^2 + 1
    insertTerm(&poly2, 4, 3);
    insertTerm(&poly2, 2, 2);
    insertTerm(&poly2, 1, 0);

    printf("Polynomial 1: ");
    display(poly1);

    printf("Polynomial 2: ");
    display(poly2);

    sum = addPolynomials(poly1, poly2);

    printf("Sum: ");
    display(sum);

    return 0;
}
