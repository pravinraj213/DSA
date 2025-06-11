// Reversing an Array
#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
  
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
  
    for (int i = 0; i < n/2; i++){
        int temp = arr[i];
        arr[i] = arr[n-i-1];
        arr[n-i-1] = temp;
    }
  
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
}

// Anagram
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char s1[100], s2[100];
    scanf("%s", s1);
    scanf("%s", s2);

    if (strlen(s1) != strlen(s2)){
        printf("Not anagram\n");
        return 0;
    }

    int hash[26] = {0};
    int len = strlen(s1);

    for (int i = 0; i < len; i++){
        hash[tolower(s1[i]) - 'a']++;
        hash[tolower(s2[i]) - 'a']--;
    }

    for (int i = 0; i < 26; i++){
        if (hash[i] != 0){
            printf("Not anagram\n");
            return 0;
        }
    }

    printf("Anagram\n");
    return 0;
}

// Find Duplicates
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    int hash[1000] = {0};  // assuming values ≤ 999

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        hash[arr[i]]++;
    }

    for (int i = 0; i < 1000; i++) {
        if (hash[i] > 1) {
            printf("%d is a repetition!\n", i);
        }
    }

    return 0;
}

// Kth Missing Positive Number
