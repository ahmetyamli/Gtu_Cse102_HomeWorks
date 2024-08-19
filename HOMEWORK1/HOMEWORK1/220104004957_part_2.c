//
//  test.c
//  HOMEWORK1
//
//  Created by Ahmet on 1.03.2024.


#include <stdio.h>

char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']', '{', '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';', '"', '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int calculateKey(long studentId){
    int sum = 0;
        while (studentId > 0) {
            sum += studentId % 10;
            studentId /= 10;
        }
    if (sum > 10){
        return calculateKey(sum);
    }else{
        return sum % 10;
    }
}

int findIndex(char* start, char findC){
    
    for (int i = 0; i < 61 ; i++, start++) {
        if (findC == *start){
            return i;
        }
    }
    return 0;
}
int main(void) {
    
    long studentID = 220104004957;
    int key;
    char* startAlphabet = &alphabet[0];
    
    int encryptedIndex = 0;
    
    
    key = calculateKey(studentID);

    
    char c ;
    
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n'){
            printf("%c", c);
        }else if (c == '@'){
            /*There is 22characters as comment.*/
            c = getchar();
            printf("/*There is ");
            while (c != '\n') {
                int decryptedIndex = (61 + findIndex(startAlphabet, c)) - key;
//                printf("decrpted index -> %d . %d,,,",decryptedIndex, decryptedIndex %61);
                 printf("%c", alphabet[decryptedIndex % 61]);
//                printf("%c",c);
                c = getchar();
            }
            printf(" characters as comment.*/ \n");
        }else{
            encryptedIndex = findIndex(startAlphabet, c) - key;
             printf("%c", alphabet[encryptedIndex % 61]);
        }

    }

    return 0;
}
//gcc main2.c -o main2 && ./main2 < encrypted_text.txt > decrypted_text.txt
