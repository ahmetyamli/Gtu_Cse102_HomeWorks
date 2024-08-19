//
//  main.c
//  HOMEWORK8
//
//  Created by Ahmet on 24.04.2024.
//

#include <stdio.h>
#include <string.h>
///Users/ahmet/Desktop/School/Cse102/HOMEWORK8/HOMEWORK8
#define file1 "input1.txt"
#define input2 "input2.txt"

int MAX_ROW_COUNT = 100;
int MAX_COL_COUNT = 100;

int findCount(FILE* file){ /* to find number of row in txt file*/
    int count = 1;
    char c = '\0' ;
    file = fopen(file1, "r");
    
    while (c != EOF) { /*Increments its value by one as it reads the /n character*/
        c = fgetc(file);
        if (c == '\n') count++;
    }
    fclose(file);
    
    return count;
}

void fix_bugs(char arr[]){  /*replaces the /r character causing the error after retrieval from the txt file*/
    int i = 0;
    for (i = 0; i < 30; i++) {
        if (arr[i] == '\r')
            arr[i] = '\0';
    }
}


void readTxt1(FILE* file, char listOfPeople[][4][30],int age[], int count){ /* read the file. while reading file the func find the num of colm and rows and fill the array*/
    file = fopen(file1, "r");
    
    int i = 0;
    
    char c;
    
    while (i < count) {
        
        if (fscanf(file, "%[^,]",listOfPeople[i][0]) == 1){
        }
        c = fgetc(file);
        if (c == ',') c = fgetc(file);
        if (fscanf(file, "%[^,]",listOfPeople[i][1]) == 1){

        }
        c = fgetc(file);

        if (fscanf(file, "%d",&age[i]) == 1){

        }
        c =  fgetc(file);
        if (c == ',') c = fgetc(file);
        if (fscanf(file, "%[^,^\n]",listOfPeople[i][2]) == 1){

        }
        c = fgetc(file);

        if (c == ','){
            fgetc(file);
            if (fscanf(file, "%[^\n]",listOfPeople[i][3]) == 1){

            }else {
                listOfPeople[i][3][0] = '\0';
            }
            c = fgetc(file);
        }else
            listOfPeople[i][3][0] = '\0';
        fix_bugs(listOfPeople[i][2]); /*for replace the '\n' */
        fix_bugs(listOfPeople[i][3]); /*for replace the '\n' */
        i++;
    }

}

void printAllPeople(char listOfPeople[][4][30],int ages[], int count) { /* print all people in the array*/
    int i = 0;
    printf("%-19s %-20s %-20s %-19s %-19s\n", "name", "surname", "age", "branch1", "branch2");
    for (i = 0; i < count; i++) {
        printf("%-20s",listOfPeople[i][0]);
        printf("%-20s",listOfPeople[i][1]);
        printf("%-20d",ages[i]);
        printf("%-20s",listOfPeople[i][2]);
        printf("%-20s",listOfPeople[i][3]);
        printf("\n");
        
    }
}

int isSameBranch(const char *sentence, const char *search) {/* check if there is a word in the sentence */
    char *sentence_copy = strdup(sentence);
    char *sentence_words = strtok(sentence_copy, " ");

    while (sentence_words != NULL) {
        if (strcmp(sentence_words, search) == 0) {

            return 1;
        }
        sentence_words = strtok(NULL, " ");
    }

    return 0;
}

void print_special_branch(char listOfPeople[][4][30],int ages[], int count, char branch[]){ /*Shows  individuals with the branch 'SCIENCE'*/
        int i = 0;
        for (i = 0; i < count; i++) {
            if (isSameBranch(listOfPeople[i][2], branch) || isSameBranch(listOfPeople[i][3], branch)) {
                
                printf("%-20s",listOfPeople[i][0]);
                printf("%-20s",listOfPeople[i][1]);
                printf("%-20d",ages[i]);
                printf("%-20s",listOfPeople[i][2]);
                printf("%-20s",listOfPeople[i][3]);
                
                printf("\n");
            }
        }
}

void show_computer_scientist(char listOfPeople[][4][30],int ages[], int count){
    int i = 0;
    char branch1[] = "COMPUTER";
    char branch2[] = "MATHEMATICS";
    for (i = 0; i < count; i++) {
        if (isSameBranch(listOfPeople[i][2], branch2) && !isSameBranch(listOfPeople[i][3], branch1)) {
            
            printf("%-20s",listOfPeople[i][0]);
            printf("%-20s",listOfPeople[i][1]);
            printf("%-20d",ages[i]);
            printf("%-20s",listOfPeople[i][2]);
            printf("%-20s",listOfPeople[i][3]);
            
            printf("\n");
        }
    }
}

void switchArray(char firstArr[], char secondArr[]){ /* this func using for switch two array*/
    char temp[30];
    int i = 0;
    for (i = 0; i < 30; i++) {
        temp[i] = firstArr[i];
        firstArr[i] = secondArr[i];
        secondArr[i] = temp[i];
    }
}

void sort_people_by_age(char listOfPeople[][4][30],int ages[], int count ){
    int i = 0;
    int j = 0;
    int k = 0;
    
    int tempAge = 0;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            if (ages[j] < ages[i]) {
                tempAge = ages[i];
                ages[i] = ages[j];
                ages[j] = tempAge;
                
                for (k = 0; k < 4; k++) {
                    
                    switchArray(listOfPeople[i][k], listOfPeople[j][k]);
                }
                
            }
        }
    }
}

void sort_people_by_branch(char listOfPeople[][4][30],int ages[], int count ){
    int i = 0;
    int j = 0;
    int k = 0;
    int cmpr1 = 0,cmpr2 = 0;
    
    
    int tempAge = 0;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            cmpr1 = strcmp(&listOfPeople[i][2][0], &listOfPeople[j][2][0]); /* compare branch1*/
            cmpr2 = strcmp(&listOfPeople[i][3][0], &listOfPeople[j][3][0]); /* compare branch2*/
            if ( cmpr1 > 0 ) { /* first check the branch1*/
                tempAge = ages[i];
                ages[i] = ages[j];
                ages[j] = tempAge;
                
                for (k = 0; k < 4; k++) {
                    
                    switchArray(listOfPeople[i][k], listOfPeople[j][k]);
                }
            }else if (cmpr2 > 0 && cmpr1 == 0){/*then check the branch2*/
                tempAge = ages[i];
                ages[i] = ages[j];
                ages[j] = tempAge;
                
                for (k = 0; k < 4; k++) {
                    
                    switchArray(listOfPeople[i][k], listOfPeople[j][k]);
                }
            }else if (cmpr1 == 0 && cmpr2 == 0 && ages[i] > ages[j]){ /* then sort by number*/
                tempAge = ages[i];
                ages[i] = ages[j];
                ages[j] = tempAge;
                
                for (k = 0; k < 4; k++) {
                    
                    switchArray(listOfPeople[i][k], listOfPeople[j][k]);
                }
            }
        }
    }
}

void print_menu(void){/* print the menu*/
    printf("*-*-*-*    MENU    *-*-*-*\n");
    printf("1. Sort and display all individuals by age\n");
    printf("2. Sort and display  individuals in the branch by age\n");
    printf("3. Show  individuals with the branch 'SCIENCE'\n");
    printf("4. Show  computer scientist who are not mathematicians\n");
    printf("5. EXİT \n");
}

//-MARK: -PART2-

void fix_bugs2(char arr[]){ /*replaces the /r character causing the error after retrieval from the txt file*/
    int i = 0;
    for (i = 0; i < 100; i++) {
        if (arr[i] == '\r' || arr[i] == '\n' )
            arr[i] = '\0';
    }
}

void readTxt2(char strs[][MAX_COL_COUNT], int* rows, int* cols) { /* read the file. while reading file the func find the num of colm and rows and fill the array*/
    FILE* file = fopen(input2, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    *rows = 0;
    *cols = 0;
    int row = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            if (*cols > 0) {
                (*rows)++;
                row = 0;
                *cols = 0;
            }
        } else {
            if (row >= *cols) {
                (*cols)++;
            }
            if (*rows < MAX_ROW_COUNT && *cols < MAX_COL_COUNT) {
                strs[*rows][row++] = ch;
            }
        }
    }
    fclose(file);
    int i ;
    for (i = 0; i < row; i++) {
        fix_bugs2(strs[i]); /* fix each array*/
    }
}

void search_p1(char strs[][MAX_COL_COUNT],char pattern[], int num_rows,int num_cols){
    int i,j, /*variable for loop*/
    k = 0, /*variable for pattern indice */
    x,y; /*variable to hold inital coordination*/
    for (i = 0; i <= num_rows; i++) {
        for (j = 0; j < num_cols ; j++) {
            if (strs[i][j] == pattern[0]) {
                x = i; /* hold initial coordination to write or come back here later*/
                y = j; /* hold initial coordination to write or come back here later*/
                while (strs[i][j] == pattern[k]) {
                    
                    j++; /*keep checking horizontally*/
                    k++; /*increment the index of the checked word*/
                }
                if (pattern[k] == '\0'){ /* prints the start coordination if the pattern reaches the last character*/
                    printf("P1 @ (%d,%d)\n",x + 1,y + 1);
                }else{ /*come back the inital coordination*/
                    
                    j = y;
                }
                k = 0;
            }
        }
    }
}

void search_p2(char strs[][MAX_COL_COUNT],char pattern[], int num_rows,int num_cols){
    int i,j, /*variable for loop*/
    k = 0, /*variable for pattern indice */
    x,y; /*variable to hold inital coordination*/
    for (i = 0; i <= num_rows; i++) {
        for (j = 0; j < num_cols ; j++) {
            if (strs[i][j] == pattern[0]) {
                x = i; /* hold initial coordination to write or come back here later*/
                y = j; /* hold initial coordination to write or come back here later*/
                while (strs[i][j] == pattern[k]) {
                    
                    i++; /*keep checking vertically*/
                    k++; /*increment the index of the checked word*/
                }
                if (pattern[k] == '\0'){
                    printf("P2 @ (%d,%d)\n",x + 1,y + 1);
                    i = x;
                }else{
                    
                    i = x;
                }
                k = 0;
            }
        }
    }
}

void search_p3(char strs[][MAX_COL_COUNT],char pattern[], int num_rows,int num_cols){
    int i,j, /*variable for loop*/
    k = 0, /*variable for pattern indice */
    x,y; /*variable to hold inital coordination*/
    for (i = 0; i <= num_rows; i++) {
        for (j = 0; j < num_cols ; j++) {
            if (strs[i][j] == pattern[0]) {
                x = i; /* hold initial coordination to write or come back here later*/
                y = j; /* hold initial coordination to write or come back here later*/
                while (strs[i][j] == pattern[k]) {
                    
                    i++; /*keep cross-checking*/
                    j++; /*keep cross-checking*/
                    k++; /*increment the index of the checked word*/
                }
                if (pattern[k] == '\0'){
                    printf("P3 @ (%d,%d)\n",x + 1,y + 1);
                    i = x;
                    j = y;
                }else{
                    j = y;
                    i = x;
                }
                k = 0;
            }
        }
    }
}

int main(void){
    FILE* file = NULL;
    int count = findCount(file); /*f find number of row*/
    int userSelection = 0;
    
    /*TODO: change user selection*/
    

    
    char listOfPeople[count][4][30];
    int ages[count]; /* an array to hold ages*/
    readTxt1(file, listOfPeople,ages,count);
    /*TODO: open readtxt1 */
    char specialBranch[30] = "SCIENCE";

    
    
    while (userSelection != 5) {
        print_menu();
        printf("Choice ");
        scanf("%d",&userSelection);
        switch (userSelection) {
            case 1:
                sort_people_by_age(listOfPeople,ages,count);
                printAllPeople(listOfPeople, ages, count);
                break;
            case 2:
                sort_people_by_age(listOfPeople, ages, count);
                sort_people_by_branch(listOfPeople, ages, count);
                printAllPeople(listOfPeople, ages, count);
                break;
            case 3:
                sort_people_by_age(listOfPeople, ages, count);
                print_special_branch(listOfPeople, ages, count, specialBranch);
                break;
            case 4:
                show_computer_scientist(listOfPeople, ages, count);
                break;
            case 5:
                
                break;
                
            default:
                printf("invalid selection. pleease select again \n");
                break;
        }
    }
    
    char strs[MAX_ROW_COUNT][MAX_COL_COUNT];
    int rows, cols;
    readTxt2(strs,&rows, &cols); /* read txt , store the data in strs and find the rows and cols */

    int i = 0;
    int j =0;
//    for ( i = 0 ; i <= rows; i++) {
//        for ( j =0 ; j < cols; j++) {
//            printf("satır-> %d, sütun -> %d, %c \n",i,j,strs[i][j]);
//        }
//    }
    char pattern[] = "***++++***++++***";
    char pattern2[] = "+*+*+";
    char pattern3[] = "+++++";
    search_p1(strs,pattern, rows, cols );
    search_p2(strs,pattern2,rows,cols);
    search_p3(strs,pattern3,rows,cols);

    return 1;
}
