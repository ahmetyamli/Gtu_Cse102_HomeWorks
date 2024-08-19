//
//  main.c
//  HOMEWORK9
//
//  Created by Ahmet on 2.05.2024.
//


#include <stdio.h>
#define File "init.txt"
#define Final_File "final.txt"

typedef struct {
    char map[100][100];
    int width; /*This stores number of rows (size of dimension X) the map.*/
    int height; /*This stores number of columns (size of dimension Y) of the map.*/
    int flower_x; /*This is the X coordinate of the rare flower.*/
    int flower_y; /*This is the Y coordinate of the rare flower.*/
    int number_of_flowers;
}Forest;
    
typedef struct {
    int coord_x; /*The X coordinate of the botanist.*/
    int coord_y; /*The Y coordinate of the botanist.*/
    int water_bottle_size; /*This is the volume of water bottle size.*/
}Botanist;

void fixComma(Forest *forest){
    int i, j;
    for (i = 0; i < forest->width; i++) {
        for (j = 0; j < forest->height; j++) {
            if (forest->map[i][j] == ',') {
                forest->map[i][j] = ' ';
            }
        }
    }
}

void init_game(Forest *forest, Botanist *botanist){
    FILE* file = fopen(File, "r");
    int i, j; /*variable for loop*/
    int number_of_flowers = 0;
    
    fscanf(file, "%d,%d",&forest->width,&forest->height);
    fscanf(file, "%d,%d,%d",&botanist->coord_x,&botanist->coord_y,&botanist->water_bottle_size);
    
    printf("%d,%d",forest->width,forest->height);
    printf("\n%d,%d,%d\n",botanist->coord_x,botanist->coord_y,botanist->water_bottle_size);
    
    for (i = 0; i < forest->width; i++) {
        for (j = 0; j < forest->height; j++) {
            fscanf(file, " %c,",&forest->map[i][j]);
        }
        forest->map[i][forest->height] = '\0';
        
    }

    
    fixComma(forest);
    
    for (i = 0; i < forest->width; i++) {
        for (j = 0; j < forest->height; j++) {
            
            printf("%c ",forest->map[i][j]);
            if (forest->map[i][j] == 'X') {
                number_of_flowers++;
            }
            
        }
        printf("\n");
        
    }
    forest->number_of_flowers = number_of_flowers;
    fclose(file);
}


void display_forest(Forest forest, Botanist botanist, int foundedFlowers){
    int i,j;
    for (i = 0; i < forest.width; i++) {
        for (j = 0; j < forest.height; j++) {
            if (i == botanist.coord_x && j == botanist.coord_y) {
                forest.map[i][j] = 'B';
            }
            printf("%c ",forest.map[i][j]) ;
        }
        printf("\n");
        
    }
    printf("collected flower number -> %d\n",foundedFlowers);
    printf("not used bottle number -> %d\n",botanist.water_bottle_size);
}

void search(Forest *forest, Botanist *botanist, char userSelection, int numberOfFlowers, int foundedFlowers){
    if (foundedFlowers == numberOfFlowers) {
        return ;
    }else{
        char userSelection = '\0';
        int whileFlag = 1;
        while (whileFlag) {
            printf("\nplease enter the move: ");
            scanf(" %c",&userSelection);
            switch (userSelection) {
                case 'd':
                    if (forest->map[botanist->coord_x][botanist->coord_y + 1] != 'T' && botanist->coord_y != 9) {
                        
                        forest->map[botanist->coord_x][botanist->coord_y] = '-';
                        botanist->coord_y += 1;
                        if (forest->map[botanist->coord_x][botanist->coord_y ] == 'X') {
                            foundedFlowers += 1;
                            botanist->water_bottle_size--;
                            printf( "I've found it!\n");
                        }
                        display_forest(*forest, *botanist,foundedFlowers);
                    }else printf("you cannot move here\n");
                    whileFlag = 0;
                    break;
                case 'a':
                    if (forest->map[botanist->coord_x][botanist->coord_y - 1] != 'T' && botanist->coord_y != 0) {
                        forest->map[botanist->coord_x][botanist->coord_y] = '-';
                        botanist->coord_y -= 1;
                        if (forest->map[botanist->coord_x][botanist->coord_y] == 'X') {
                            foundedFlowers += 1;
                            botanist->water_bottle_size--;
                            printf( "I've found it!\n");
                        }
                        display_forest(*forest, *botanist,foundedFlowers);
                    }else printf("you cannot move here\n");
                    whileFlag = 0;
                    break;
                case 's':
                    if (forest->map[botanist->coord_x + 1][botanist->coord_y ] != 'T') {
                        forest->map[botanist->coord_x][botanist->coord_y] = '-';
                        botanist->coord_x += 1;
                        if (forest->map[botanist->coord_x][botanist->coord_y] == 'X') {
                            foundedFlowers += 1;
                            botanist->water_bottle_size--;
                            printf( "I've found it!\n");
                        }
                        display_forest(*forest, *botanist,foundedFlowers);
                    }else printf("you cannot move here\n");
                    whileFlag = 0;
                    break;
                case 'w':
                    if (forest->map[botanist->coord_x - 1][botanist->coord_y ] != 'T') {
                        forest->map[botanist->coord_x][botanist->coord_y] = '-';
                        botanist->coord_x -= 1;
                        if (forest->map[botanist->coord_x][botanist->coord_y] == 'X') {
                            foundedFlowers += 1;
                            botanist->water_bottle_size--;
                            printf( "I've found it!\n");
                        }
                        display_forest(*forest, *botanist,foundedFlowers);
                    }else printf("you cannot move here\n");
                    whileFlag = 0;
                    break;
                default:
                    printf("invalid selection \n");
                    break;
            }
        }
        return search(forest, botanist, userSelection, numberOfFlowers, foundedFlowers);
        
    }
    
}

void write_to_file(Forest forest, Botanist botanist){
    FILE* file = fopen(Final_File, "w");
    int i,j;
    
    fprintf(file, "%d,%d \n",forest.width,forest.height);
    fprintf(file, "%d,%d,%d \n",botanist.coord_x,botanist.coord_y,botanist.water_bottle_size);
    
    for (i = 0; i < forest.width; i++) {
        for (j = 0; j < forest.height; j++) {
            if (i == botanist.coord_x && j == botanist.coord_y) {
                forest.map[i][j] = 'B';
            }
            fprintf(file, "%c ",forest.map[i][j]);
        }
        fprintf(file, "\n");
    }
}

int main(int argc, const char * argv[]) {
    
    Forest forest;
    Botanist botanist;
    init_game(&forest, &botanist);
    

    search(&forest, &botanist, '\0', forest.number_of_flowers, 0);
    write_to_file(forest,botanist);
    return 0;
}
