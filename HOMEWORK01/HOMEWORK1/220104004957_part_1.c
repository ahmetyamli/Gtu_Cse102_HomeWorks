//
//  main.c
//  HOMEWORK1
//
//  Created by Ahmet on 1.03.2024.
//



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

char intToAlphabet(int a){
    if( a == 0)
        return '0';
    else if (a == 1)
        return  '1';
    else if (a == 2)
        return  '2';
    else if (a == 3)
        return  '3';
    else if (a == 4)
        return  '4';
    else if (a == 5)
        return  '5';
    else if (a == 6)
        return  '6';
    else if (a == 7)
        return  '7';
    else if (a == 8)
        return  '8';
    else
        return  '9';
}



void encryptInteger(int sayi, int key, char* startAlphabet) {
    int temp = sayi;
    int numberDigit = 0;

    while (temp != 0) {
        temp /= 10;
        numberDigit++;
    }

    temp = sayi;

    for (int i = numberDigit; i > 0; i--) {
        int bolum = 1;
        for (int j = 1; j < i; j++) {
            bolum *= 10;
        }

        int basamak = temp / bolum;
        int sifrelenmisBasamak = (findIndex(startAlphabet, intToAlphabet(basamak)) + key) % 61;
        printf("%c", alphabet[sifrelenmisBasamak]);
        temp %= bolum;
    }
}





int main(void) {
    
    long studentID = 220104004957;
    int key;
    char* startAlphabet = &alphabet[0];
    
    int encryptedIndex = 0, commentLenght = 0;
    
    
    key = calculateKey(studentID);
//    printf("key->%d",key);
    
    char c , nextChar;
    
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n'){
            printf("%c", c);
        }else if (c == '/'){
            nextChar = getchar();
            if (nextChar  == '*'){
                c = getchar();
                while (c != '*') {
                    
                    if (c == ' '){
                        c = getchar();
                    }else if (c == '\n'){
                        c = getchar();
                    }else {
                        commentLenght += 1;
                        c = getchar();
                    }
                    
                }
                printf("@");
                encryptInteger(commentLenght, key, startAlphabet);
                commentLenght = 0;
                c = getchar();
            }
        }else{
            encryptedIndex = findIndex(startAlphabet, c) + key;
             printf("%c", alphabet[encryptedIndex % 61]);
        }

    }

    return 0;
}
//gcc main.c -o main && ./main < text.txt > encrypted_text.txt
