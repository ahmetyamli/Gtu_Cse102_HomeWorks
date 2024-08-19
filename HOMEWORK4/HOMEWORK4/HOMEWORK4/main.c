//
//  main.c
//  HOMEWORK4
//
//  Created by Ahmet on 20.03.2024.
//

#include <stdio.h>
#define file1 "first1.txt"
#define file2 "second1.txt"

//GLOBAL
double midAverage102 = 0;
double finalAverage102 = 0;
double midAverage108 = 0;
double finalAverage108 = 0;
int personNumber = 0;
int numberStudent102 = 0;
int numberStudent108 = 0;
int numberInstructor = 0;

void goToLine(FILE *file, int line_number) {
    
    rewind(file);
    
    int lineCounter = 1;

    
    char character;
    while ((character = fgetc(file)) != EOF) {
        if (lineCounter == line_number - 1) {
            while (fgetc(file) != '\n') {
//                printf("1");
                if (fgetc(file) == EOF)break;
            }
            break;
        }

        // Check for end of line
        if (character == '\n') {
            lineCounter++;
        }
    }

}

void readFirsttxt(void){
    FILE *file;
    int StudentID, midTerm1, midTerm2, final, courseId, Codeofclasses, department , counter = 0;
    double totalMid = 0,totalFİnal = 0;
    
    file = fopen(file1, "r");
    if (file == NULL) {
        printf("Dosya açılamadı!\n");
        
    }
    int i = 1;
    while (fscanf(file, "%d;%d;%d;%d;%d", &StudentID, &midTerm1, &midTerm2, &final, &courseId) == 5) {
//        printf("%d Veri 1: %d, Veri 2: %d, Veri 3: %d, Veri 4: %d, Veri 5: %d\n",i, StudentID, midTerm1, midTerm2, final, courseId);
        totalMid += (midTerm1 + midTerm2) / 2;
        totalFİnal += final;
        i++;
        counter++;
    }
    midAverage102 = totalMid / counter;
    finalAverage102 = totalFİnal / counter;
    numberStudent102 = counter;
    counter = 0;
    totalMid = 0;
    totalFİnal = 0;
    
    goToLine(file, i);

    while (fscanf(file, "%d;%d;%d;%d", &StudentID, &midTerm1, &final, &courseId) == 4) {
//        printf("%d Veri 1: %d, Veri 2: %d, Veri 3: %d, Veri 4: %d, Veri 5: %d\n",i, StudentID, midTerm1, midTerm2, final, courseId);
        totalMid += midTerm1;
        totalFİnal += final;
        i++;
        counter++;
    }
    goToLine(file, i);
    
    numberStudent108 = counter;
    midAverage108 = totalMid / counter;
    finalAverage108 = totalFİnal / counter;
    counter = 0;
    totalMid = 0;
    totalFİnal = 0;
    
    while (fscanf(file, "%d;%d;%d", &StudentID, &Codeofclasses, &department ) == 3){
//        printf("%d Veri 1: %d, Veri 2: %d, Veri 3: %d\n",i, StudentID, Codeofclasses, department);
        i++;
        counter++;
    }
    numberInstructor = counter;
    personNumber = i;
    
    fclose(file);
    
}

int getRow(int studentID){
    FILE *file;
    int veri1, veri2, veri3, veri4, veri5;
    
    
    file = fopen(file1, "r");
    if (file == NULL) {
        printf("Dosya açılamadı!\n");
        
    }
    
    int i = 1;
    while (1){
        if (i == personNumber) break;
        fscanf(file, "%d;%d;%d;%d;%d", &veri1, &veri2, &veri3, &veri4, &veri5);
        if (veri1 == studentID)
            return i;
        i++;
    }

    fclose(file);
    
    return 0;
}

double calculateGPA(double Midterm,double Final, int is102){
    double midAverage = is102 ? midAverage102 : midAverage108;
    double finalAverage = is102 ? finalAverage102 : finalAverage108;
//    printf("")
//    printf("midAverage -> %f \nfinalAverage -> %f \nMidterm -> %f \nFinal -> %f",midAverage,finalAverage, Midterm , Final);
    if ((Midterm < 40 && Midterm < midAverage) && (Final < 40 && Final < finalAverage)) {
//        printf("\nhere1\n");
        return 1.0;
    }else if ((Midterm > 40 && Midterm < midAverage) && (Final > 40 && Final < finalAverage)){
//        printf("\nhere2\n");
        return 2.5;
    }else if ((Midterm > 40 && Midterm < midAverage) && (Final > 40 && Final > finalAverage)){
//        printf("\nhere3\n");
        return 3.0;
    }else if ((Midterm > 40 && Midterm > midAverage) && (90 > Final) && (Final > finalAverage)){
//        printf("\nhere4\n");
        return 3.5;
    }else if ((Midterm > 90) && (Final > 90)){
//        printf("\nhere5\n");
        return 4.0;
    }
//    printf("\nhere6\n");
    return 0.0;
}

char GPAtoChar(double grade){
    if (grade == 1) return 'F';
    else if (grade == 2.5) return 'D';
    else if (grade == 3) return 'C';
    else if (grade == 3.5) return 'B';
    else if (grade == 4) return 'A';
    else return 'N';
    
    
}

char firstInital(FILE * id_fp, int id){
    int row = getRow(id);
    char c;
    
    id_fp = fopen(file2, "r");
    if (id_fp == NULL) {
        printf("Dosya açılamadı!\n");
        
    }
    
    for (int i = 0; i <  row -1;) {
        c = fgetc(id_fp);
        if (c == '\n') i++;
    }
    while (c != ';') {
        c = fgetc(id_fp);
        
    }
    c = fgetc(id_fp);
    fclose(id_fp);
    return c;
    
    
}

char last_initial(FILE * id_fp, int id){
    int row = getRow(id);
    char c;
    char cNext = '_';
    char returnC;
    
    id_fp = fopen(file2, "r");
    if (id_fp == NULL) {
        printf("Dosya açılamadı!\n");
        
    }
    
    for (int i = 0; i < row - 1;) {
        c = fgetc(id_fp);
        if (c == '\n') i++;
    }
    
    while (c != ';') {
        c = fgetc(id_fp);
    }
    c = fgetc(id_fp);
    while (c != ';') {
        c = fgetc(id_fp);
    }
    while (1) {
        c = fgetc(id_fp);
//        printf("\nc-> %c \n",c);
        if (c == ';'){
            returnC = cNext;
            break;
        }
        else if (cNext == ';') {
            returnC = c;
            break;
        }
        cNext = fgetc(id_fp);
//        printf("\n cNext-> %c \n",cNext);
        if (c == ';'){
            returnC = cNext;
            break;
        }
        else if (cNext == ';') {
            returnC = c;
            break;
        }
    }
    fclose(id_fp);
    
    return returnC;
}

int get_id_fi(FILE * id_fp, char first_initial){
    int id;
    char c;
    
    id_fp = fopen(file2, "r");
    if (id_fp == NULL) {
        printf("Dosya açılamadı!\n");
        
    }

    for (int i = 0; i < personNumber; i++) {
        fscanf(id_fp, "%d;",&id);
//        printf("i -> %d\n",i);
        printf("id -> %d\n",id);
        if (fgetc(id_fp) == first_initial){
            break;
        }
            while (c != '\n') {
                c = fgetc(id_fp);
                
            }
            c = fgetc(id_fp);
        printf("c in here -> %c\n",c);
    }

    
    fclose(id_fp);
    return id;
}


int get_id_li(FILE * id_fp, char last_inital){
    //220015001;cristopher;mullins;student;100
    int id = -1;
    char c;
    char cNext;
    char lastChar = '\0';
    
    id_fp = fopen(file2, "r");
    if (id_fp == NULL) {
        printf("Dosya açılamadı!\n");
        
    }

    for (int i = 0; i < personNumber; i++) {
        fscanf(id_fp, " %d;",&id);
        printf("\nİD -> %d \n",id);
        printf("i in here -> %d\n",i);

        while (c != ';') {
            c = fgetc(id_fp);
            printf("%c",c);
            
        }

        printf("\n%cccc\n",c);
        cNext = '\0';
        c = '\0';
        while (1) {
            c = fgetc(id_fp);
            printf("\nc-> %c \n",c);
            if (c == ';'){
                lastChar = cNext;
                break;
            }
            else if (cNext == ';') {
                lastChar = c;
                break;
            }
            cNext = fgetc(id_fp);
            printf("\n cNext-> %c \n",cNext);
            if (c == ';'){
                lastChar = cNext;
                break;
            }
            else if (cNext == ';') {
                lastChar = c;
                break;
            }
            
        }
        printf("\nlastChar -> %c \n",lastChar);
        printf("\n-----------\n");
        if (lastChar == last_inital){
            break;
        }
        
            while (c != '\n') {
                
                c = fgetc(id_fp);
                if ( c == EOF) {
                    break;
                }
            }
    }

    fclose(id_fp);
    return id;
}

double average_grade(FILE * info_fp, int id){

    
    int row = getRow(id);
    char c = '*';
    int StudentID, midTerm1, midTerm2,midTerm, final, courseId;
    double GPA = 0;
    
    info_fp = fopen(file1, "r");
    if (info_fp == NULL) {
        printf("Dosya açılamadı!\n");
        
    }
    goToLine(info_fp, row);
    
    if (row <= numberStudent102) {
        fscanf(info_fp, "%d;%d;%d;%d;%d", &StudentID, &midTerm1, &midTerm2, &final, &courseId);
        midTerm = (midTerm1 + midTerm2) / 2;
        GPA = calculateGPA(midTerm, final, 1);
        printf("\n102\nGPA->>%c\n",GPAtoChar(GPA));
//        printf("row -> %d Veri 1: %d, Veri 2: %d, Veri 3: %d, Veri 4: %d, Veri 5: %d\n",row, StudentID, midTerm1, midTerm2, final, courseId);
    } else {
        fscanf(info_fp, "%d;%d;%d;%d", &StudentID, &midTerm, &final, &courseId);
        GPA = calculateGPA(midTerm, final, 0);
        printf("\n102\nGPA->>%c\n",GPAtoChar(GPA));
    }
    
    printf("GPA -> %.1f",GPA);

    fclose(info_fp);
    
    return GPA;
    
}

void menu_p(FILE *file){
    int StudentID, midTerm1, midTerm2, final, courseId,GPA, statu, midTerm;
    file = fopen(file1, "r");
    if (file == NULL) {
        printf("Dosya açılamadı!\n");
        
    }
    
    while (fscanf(file, "%d;%d;%d;%d;%d", &StudentID, &midTerm1, &midTerm2, &final, &courseId) == 5) {
        printf("StudentID -> %d, Statu ->",StudentID);
        midTerm = (midTerm1 + midTerm2) / 2;
        GPA = calculateGPA(midTerm, final, 1);
        
        if (GPA < 2) printf(" Fail\n");
        else printf(" Success\n");
    }
    goToLine(file, numberStudent102 );
    
    while (fscanf(file, "%d;%d;%d;%d", &StudentID, &midTerm, &final, &courseId) == 4) {
//        printf(" Veri 1: %d, Veri 2: %d, Veri 3: %d, Veri 4: %d, Veri 5: %d\n", StudentID, midTerm1, midTerm2, final, courseId);
        GPA = calculateGPA(midTerm, final, 0);
        printf("StudentID -> %d, Statu ->",StudentID);
        if (GPA < 2) printf(" Fail\n");
        else printf(" Success\n");
      
    }
    fclose(file);
    
}

void menu_n(FILE * id_fp){
    FILE* file;
    int id;
    char c;
    char c2;
    char first_initial;
    int row;
    int StudentID,midTerm,mid1,mid2,final,department,GPA;
    
    printf("please enter the first letter of the first name:");
    scanf(" %c",&first_initial);
    
    id_fp = fopen(file2, "r");
    if (id_fp == NULL) {
        printf("Dosya açılamadı!\n");
        
    }

    for (int i = 0; i < personNumber ; i++) {
        goToLine(id_fp, i);
        fscanf(id_fp, "%d;",&id);
        
        
        if (fgetc(id_fp) == first_initial){
//            id = id + 200000000;
            printf("id -> %d",id);
            row = getRow(id);
            printf("row -> %d",row);
            
            file = fopen(file1, "r");
            
            
            printf("id -> %d\n",id);
            if (file == NULL) {
                printf("Dosya açılamadı!\n");
                
            }
            goToLine(file, row ) ;

//            printf("here1 row->  %d\n",row);
            if(fscanf(file, " %d;%d;%d;%d;%d", &StudentID, &mid1, &mid2, &final, &department ) == 5){
//                printf("here2");
                printf("StudentID -> %d, Statu ->",StudentID);
                midTerm = (mid1 + mid2) / 2;
                GPA = calculateGPA(midTerm, final, 1);
                
                if (GPA < 2) printf(" Fail\n");
                else printf(" Success\n");
                
            }else if(fscanf(file, "%d;%d;%d;%d", &StudentID, &mid1, &final, &department ) == 4){
                goToLine(file, row - 1);
                fscanf(file, "%d;%d;%d;%d", &StudentID, &mid1, &final, &department );
                GPA = calculateGPA(mid1, final, 1);
                printf("StudentID -> %d, Statu ->",StudentID);
                if (GPA < 2) printf(" Fail\n");
                else printf(" Success\n");
            }
            printf("file1 closing\n");
            fclose(file);


        }
  


    }
    
    
    fclose(id_fp);
    
}

void menu_g(FILE *file){
    int id;
    printf("please enter id to calculate GPA");
    scanf("%d",&id);
    
    average_grade(file, id);
}

void menu_c(FILE *file){
    int given_course_id;
    char c ;
    
    printf("please enter the  ID:");
    scanf("%d",&given_course_id);
    
    
    int StudentID, midTerm1, midTerm2, final, courseId, Codeofclasses, department,midTerm,GPA;
    double totalMid = 0,totalFİnal = 0;
    
    file = fopen(file1, "r");
    if (file == NULL) {
        printf("Dosya açılamadı!\n");
        
    }
    if (given_course_id == 102) {
        while (fscanf(file, "%d;%d;%d;%d;%d", &StudentID, &midTerm1, &midTerm2, &final, &courseId) == 5) {
            printf("StudentID -> %d, Statu ->",StudentID);
            midTerm = (midTerm1 + midTerm2) / 2;
            GPA = calculateGPA(midTerm, final, 1);
            
            if (GPA < 2) printf(" Fail\n");
            else printf(" Success\n");
        }
        
     
    }else{
        goToLine(file, numberStudent102 + 1);
        ;

        while (fscanf(file, "%d;%d;%d;%d", &StudentID, &midTerm1, &final, &courseId) == 4) {
            GPA = calculateGPA(midTerm, final, 1);
            printf("StudentID -> %d, Statu ->",StudentID);
            if (GPA < 2) printf(" Fail\n");
            else printf(" Success\n");
            
            
        }
    }
    

    
    
    
}


void menu_t (FILE *file){
    int id, row,StudentID,Codeofclasses,department;
    
    printf("please enter the ID ");
    scanf("%d",&id);
    
    row = getRow(id);
    
    file = fopen(file1, "r");
    if (file == NULL) {
        printf("Dosya açılamadı!\n");
        
    }
    goToLine(file, row - 1);
    
    if(fscanf(file, "%d;%d;%d", &StudentID, &Codeofclasses, &department ) == 3){
        printf("student ID -> %d code of class -> %d\n",StudentID,Codeofclasses);
    }
    
}

void menu_d(FILE *file){
    
    char c;
    char given_c ;

    printf("please enter inital char role:");
    scanf(" %c",&given_c);

    int id;
    
    
    file = fopen(file2, "r");
    if (file == NULL) {
        printf("Dosya açılamadı!\n");
        
    }

    for (int i = 0; i < personNumber; i++) {
        goToLine(file, i + 1);
        fscanf(file, "%d;",&id);
        printf("id -> %d\n",id);
        printf("c in here -> %c\n",c);
        if (fgetc(file) == given_c){
            printf("id ->%d\n",id);
        }
            while (c != '\n') {
                if (c == EOF)break;
                c = fgetc(file);
                
            }
        
    }

    
    fclose(file);
    
    
    
}

void menu_l(FILE *file){
    int id, row,StudentID,mid1,mid2,final,department;
    
    printf("please enter the ID ");
    scanf("%d",&id);
    
    row = getRow(id);
    
    file = fopen(file1, "r");
    if (file == NULL) {
        printf("Dosya açılamadı!\n");
        
    }
    goToLine(file, row);
    
    if(fscanf(file, "%d;%d;%d;%d;%d", &StudentID, &mid1, &mid2, &final, &department ) == 5){
        printf("student ID -> %d code of class -> %d\n",StudentID,department);
    }else if(fscanf(file, "%d;%d;%d;%d", &StudentID, &mid1, &final, &department ) == 4){
        printf("student ID -> %d code of class -> %d\n",StudentID,department);
    }else printf("the ıd is not student");
}

void printMenu(){
    printf("p: Print all the users pass or fail.\n");
    printf("n: Print only the user with a specific first initial.\n");
    printf("g: Calculate the GPA of a given student.\n");
    printf("c: Print whether each user passed or failed the same class\n");
    printf("t: Print the number of classes for the instructor.\n");
    printf("d: Print the department of all persons according to the role.\n");
    printf("l: Print the course_id of a given student.\n");
    printf("e: Quit the program\n");
    
}

int main(void) {
    FILE *file;

    char userSelection = '\0';

    readFirsttxt();

//    printMenu();
    while (userSelection != 'e') {
        printMenu();
        printf("select\n");
        scanf(" %c",&userSelection);
        
        switch (userSelection) {
            case 'p':
                menu_p(file);
                break;
            case 'n':
                menu_n(file);
                break;
            case 'g':
                menu_g(file);
                break;
            case 'c':
                menu_c(file);
                break;
            case 't':
                menu_t(file);
                break;
            case 'd':
                menu_d(file);
                break;
            case 'l':
                menu_l(file);
                break;
            case 'e':
                break;
                
            default:
                printf("invalid selection. Please try again");
                break;
        }
    }
    
    return 1;
}

