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

struct Node* insertTerm(struct Node* poly, int c, int p) {
    struct Node* newNode = createNode(c, p);
    if (!poly) return newNode;
    struct Node* temp = poly;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    return poly;
}

struct Node* polyOperation(struct Node* p1, struct Node* p2, int sign) {
    struct Node* result = NULL;
    while (p1 && p2) {
        if (p1->power > p2->power) {
            result = insertTerm(result, p1->coeff, p1->power);
            p1 = p1->next;
        } else if (p2->power > p1->power) {
            result = insertTerm(result, sign * p2->coeff, p2->power);
            p2 = p2->next;
        } else {
            int sum = p1->coeff + sign * p2->coeff;
            if (sum != 0)
                result = insertTerm(result, sum, p1->power);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while (p1) {
        result = insertTerm(result, p1->coeff, p1->power);
        p1 = p1->next;
    }
    while (p2) {
        result = insertTerm(result, sign * p2->coeff, p2->power);
        p2 = p2->next;
    }
    return result;
}

// Display polynomial without '+' before first positive term
void display(struct Node* poly) {
    int first = 1; // flag for first term
    while (poly) {
        if (poly->coeff > 0 && !first) printf("+");
        printf("%dx^%d ", poly->coeff, poly->power);
        poly = poly->next;
        first = 0;
    }
    printf("\n");
}

int main() {
    struct Node *p1 = NULL, *p2 = NULL, *sum = NULL, *diff = NULL;

    p1 = insertTerm(p1, 3, 3);
    p1 = insertTerm(p1, 2, 2);
    p1 = insertTerm(p1, 1, 0);

    p2 = insertTerm(p2, 5, 2);
    p2 = insertTerm(p2, 4, 1);
    p2 = insertTerm(p2, 2, 0);

    printf("Poly 1: ");
    display(p1);

    printf("Poly 2: ");
    display(p2);

    sum = polyOperation(p1, p2, 1);
    diff = polyOperation(p1, p2, -1);

    printf("Sum: ");
    display(sum);

    printf("Difference: ");
    display(diff);

    return 0;
}

/*
Output:
Poly 1: 3x^3 2x^2 1x^0 
Poly 2: 5x^2 4x^1 2x^0 
Sum: 3x^3 7x^2 4x^1 3x^0 
Difference: 3x^3 -3x^2 -4x^1 -1x^0 
*/
