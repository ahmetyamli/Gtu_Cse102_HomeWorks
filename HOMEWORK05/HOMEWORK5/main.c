#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define AllNewsId "all_news_id.txt"
#define New "%d.txt"
#define ReadedNews "readed_news_id.txt"

void print_menu(void){
    printf("*******************Daily Press*******************\n");
    printf("Today's news are listed for you\n");
}

int isRead(int id){
    FILE* file;
    int readedId;
    
    file = fopen(ReadedNews, "r");
    
    if (file == NULL){
        printf("File could not open ! \n");
        fclose(file);
    }
    
    while (fscanf(file, "%d",&readedId) == 1) {
        if (readedId == id) {
            return 1;
        }
    }
    return 0;
}

int count_news(void){
    FILE * file;
    int count = 0, id;
    file = fopen(AllNewsId, "r");
    
    if (file == NULL){
        printf("File could not open ! \n");
        
    }
    
    while (fscanf(file, "%d",&id) == 1) {
        count++;
    }
    fclose(file);
    return count;
}

int print_news(int newsId,int isTitle){
    FILE * file;
    char c = '\0';
    
    file = fopen(AllNewsId, "r");
    if (file == NULL){
        printf("File could not open ! \n");
        return -1;
    }
    
    
    char filename[20];
    sprintf(filename, "news/"New, newsId);
    
    file = fopen(filename, "r");
    if (file == NULL){
        printf("File could not open ! \n");
        fclose(file);
        return -1;
    }
    if (isTitle) {
        printf("Title of %d. news: ", newsId);
        
        while (!feof(file) && (c = fgetc(file)) != '\n') {
            printf("%c", c);
        }
        printf("\n");
    }else{
        while (!feof(file) && (c = fgetc(file))) {
            if (c == '#') {
                c = fgetc(file);
                c = fgetc(file);
            }
            printf("%c", c);
        }
        printf("\n");
    }
    
    fclose(file);
    return 0;
}

int calc_secret_number(int newId){
    FILE * file;
    char c = '\0';
    char filename[20];
    
    double total = 0;
    int number = 0;
    
    sprintf(filename, "news/"New, newId);
    
    file = fopen(filename, "r");
    if (file == NULL){
        printf("File could not open ! \n");
        fclose(file);
        return -1;
    }
    
    
    
    while (!feof(file) && (c = fgetc(file))) {
        if (c == '#') {
            
            
            fscanf(file, "%d",&number);
            printf("%d", number);
            number = pow(number, 3) - pow(number, 2) + 2;
            number = pow(number, 2);
            total += number;
            
        }
        if (!(c == EOF)) {
            printf("%c", c);
        }
        
    }
    
    
    printf("\nExperiment Key  %.2f \n",total);
    fclose(file);
    return 0;
}

void menu_a(void){
    FILE *file;
    int newId;
    int yes_no = 1;
    
    printf("which news do you want to read? \n");
    scanf("%d",&newId);
    
    if (isRead(newId)) {
        printf("This new is readed. Do you want to read again? Yes(1)/No(0)");
        scanf("%d",&yes_no);
    }else{
        file = fopen(ReadedNews, "a");
        
        if (file == NULL){
            printf("File could not open ! \n");
            fclose(file);
        }
        
        fprintf(file, "%d\n", newId);
        fclose(file);
    }
    
    if (yes_no) {
        print_news(newId, 0);
    }
    
}

int menu_b(void){
    FILE* file;
    int isEmpty = 1,id,yes_no;
    
    printf("Readed news are listed below\n");
    
    
    file = fopen(ReadedNews, "r");
    
    if (file == NULL){
        printf("File could not open ! \n");
        fclose(file);
    }
    
    while (fscanf(file, "%d",&id) == 1) {
        printf("%d. news is readed \n",id);
        isEmpty = 0;
    }
    if (isEmpty){
        printf("no news read\n");
    }
    
    printf("Do you want to contunie? Yes(1)/No(0)");
    scanf("%d",&yes_no);
    
    
    fclose(file);
    
    return !yes_no;
    
}

void menu_c(void){
    int newsIdForCalculate;
    printf("Which news would you like to decrypt?");
    scanf("%d",&newsIdForCalculate);
    calc_secret_number(newsIdForCalculate);
}

void menu(void){
    int countNew = count_news();
    char user_selection = '\0';
    
    for (int i = 1; i <= countNew; i++) {
        print_news(i,1);
    }
    
    while (user_selection != 'e') {
        
        printf("What do you want to do?\na.Read a new\nb.List the readed news\nc.Get decrypted information from the news \n");
        scanf(" %c",&user_selection);
        switch (user_selection) {
            case 'a':
                menu_a();
                break;
            case 'b':
                if(menu_b())user_selection = 'e';
                break;
            case 'c':
                menu_c();
                break;
            case 'e':
                
                break;
            default:
                printf("invalid selection try again");
                break;
        }
    }
    printf("Good byeee...");
    
    
}

int main(void) {
    menu();
    return 0;
}

