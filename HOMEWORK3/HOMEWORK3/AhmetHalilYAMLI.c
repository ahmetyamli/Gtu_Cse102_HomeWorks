//
//  main.c
//  HOMEWORK3
//
//  Created by Ahmet on 16.03.2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define BOARD_SİZE 16*16
char board[BOARD_SİZE];
int field1Indices[8] = {7*16 + 8 , 7*16 + 9 , 7*16 + 10 , 8*16 + 8,  8*16 + 10, 9*16 + 8, 9*16 + 9, 9*16 + 10  };
int field2Indices[24] = {
    5*16 + 6, 5*16 + 7, 5*16 + 8, 5*16 + 9, 5*16 + 10, 5*16 + 11, 5*16 + 12,
    11*16 + 6, 11*16 + 7, 11*16 + 8, 11*16 + 9, 11*16 + 10, 11*16 + 11, 11*16 + 12,
    6*16 + 6, 6*16 +12,
    7*16 + 6, 7*16 +12,
    8*16 + 6, 8*16 +12,
    9*16 + 6, 9*16 +12,
    10*16 + 6, 10*16 +12,
};
int field2SelectedIndices[24];
int field1SelectedIndices[4];

int playerLocation = 8*16 + 9;
int totalECTS = 0;
int cont = 1;


int isWall1(int position){
    if ((position > 6*16 + 7 && position < 6*16 + 11) || (position > 10*16 + 7 && position < 10*16 + 11)){
        return 1;
    }else {
        for (int i = 6; i <= 10; i++) {
            if (position == i*16 + 7 || position == i*16 + 11){
                return 1;
            }
        }
        return 0;
    }
}

int isWall2(int position){
    if ((position > 4*16 + 5 && position < 4*16 + 13) || (position > 12*16 + 4 && position < 12*16 + 14)){
        return 1;
    }else {
        for (int i = 4; i <= 12; i++) {
            if (position == i*16 + 5 || position == i*16 + 13){
                return 1;
            }
        }
        return 0;
    }
}

int isInField1(int position){
    for (int i = 0; i < 8; i++) {
        if (position == field1Indices[i]) return 1;
    }
    return 0;
}


int isInField2(int position){
    for (int i = 0; i < 24; i++) {
        if (position == field2Indices[i]) return 1;
    }
    return 0;
}

void initialize_game(void){
    srand((unsigned int)time(NULL));
    
    int controlIndices[8] = {9,9,9,9,9,9,9,9};
    for (int i = 0; i < 4; ) {
        int index = rand() % 8;
        if (controlIndices[index] == 9){
            field1SelectedIndices[i] = field1Indices[index];
            controlIndices[index] = 0;
            i++;
        }
    }
    
    //    int field2SelectedIndices[24];
    int controlIndices2[24] = {25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25};
    int numberOfTwo ;
    while (1) {
        numberOfTwo = rand() % 24;
        if (numberOfTwo > 3 ) break;
    }
    for (int i = 0; i < numberOfTwo; ) {
        int index = rand() % 24;
        if (controlIndices2[index] == 25){
            field2SelectedIndices[i] = field2Indices[index];
            controlIndices2[index] = 0;
            i++;
        }
    }
    
    for (int i = 0; i <= BOARD_SİZE; i++) {
        board[i] = '.';
        if (isWall1(i) ||   isWall2(i)){
            board[i] = '#';
        }else if ( i == BOARD_SİZE ){
            board[i ] = 'X';
        }else if (i == playerLocation){
            board[i] = 'P';
        }else if (isInField1(i)){
            for (int j = 0; j < 4; j++) {
                if (i == field1SelectedIndices[j]) board[i] = '1';
            }
        }else if (isInField2(i)){
            //            board[i] = '2';
            for (int j = 0; j < numberOfTwo; j++) {
                if (i == field2SelectedIndices[j]) board[i] = '2';
            }
        }
    }
    
    
}
void printBoard(void){
    
    for (int i = 1; i < BOARD_SİZE + 1; i++) {
        printf("%c",board[i]);
        printf(" ");
        if (i % 16 == 0) printf("\n");
    }
}
void movePlayer(char moveDirection){
    
    switch (moveDirection) {
            
        case 'a':
            if ((playerLocation % 16) != 1){
                if (isWall1(playerLocation -1)){
                    if (totalECTS >= 32){
                        playerLocation -= 1;
                        if (isWall1(playerLocation +1) || isWall2(playerLocation +1)) board[playerLocation +1] = '#';
                        else board[playerLocation +1] = '.';
                    }else printf("\nyou have not collected enough ECTS\n");
                }else if(isWall2(playerLocation -1)){
                    if (totalECTS >= 64){
                        playerLocation -= 1;
                        if (isWall1(playerLocation +1) || isWall2(playerLocation +1)) board[playerLocation +1] = '#';
                        else board[playerLocation +1] = '.';
                    }else printf("\nyou have not collected enough ECTS\n");
                }else{
                    playerLocation -=1;
                    if (isWall1(playerLocation +1) || isWall2(playerLocation +1)) board[playerLocation +1] = '#';
                    else board[playerLocation +1] = '.';
                    if (board[playerLocation] == '1'){
                        totalECTS += 8;
                    }else if (board[playerLocation] == '2'){
                        totalECTS += 16;
                    }
                }
                board[playerLocation] = 'P';
            }
            break;
            
        case 's':
            if (playerLocation < 241){
                if (isWall1(playerLocation +16)){
                    if (totalECTS >= 32){
                        playerLocation += 16;
                        if (isWall1(playerLocation -16) || isWall2(playerLocation -16)) board[playerLocation -16] = '#';
                        else board[playerLocation -16] = '.';
                        
                    }else printf("\nyou have not collected enough ECTS\n");
                    
                }else if(isWall2(playerLocation +16)){
                    if (totalECTS >= 64){
                        playerLocation += 16;
                        if (isWall1(playerLocation -16) || isWall2(playerLocation -16)) board[playerLocation -16] = '#';
                        else board[playerLocation -16] = '.';
                    }else printf("\nyou have not collected enough ECTS\n");
                }else{
                    playerLocation +=16;
                    if (isWall1(playerLocation -16) || isWall2(playerLocation -16)) board[playerLocation -16] = '#';
                    else board[playerLocation -16] = '.';
                    if (board[playerLocation] == 'X'){
                        cont = 0;
                    }else if (board[playerLocation] == '1'){
                        totalECTS += 8;
                        
                        field1SelectedIndices[playerLocation] = 16*17;
                    }else if (board[playerLocation] == '2'){
                        totalECTS += 16;
                    }
                }
                board[playerLocation] = 'P';
            }
            break;
            
            
        case 'd':
            if (( playerLocation % 16) != 0){
                if (isWall1(playerLocation +1)){
                    if (totalECTS >= 32){
                        playerLocation += 1;
                        if (isWall1(playerLocation -1) || isWall2(playerLocation -1)) board[playerLocation -1] = '#';
                        else board[playerLocation -1] = '.';
                    }else printf("\nyou have not collected enough ECTS\n");
                }else if(isWall2(playerLocation +1)){
                    if (totalECTS >= 64){
                        playerLocation += 1;
                        if (isWall1(playerLocation -1) || isWall2(playerLocation -1)) board[playerLocation -1] = '#';
                        else board[playerLocation -1] = '.';
                    }else printf("\nyou have not collected enough ECTS\n");
                }else{
                    playerLocation +=1;
                    if (isWall1(playerLocation -1) || isWall2(playerLocation -1)) board[playerLocation -1] = '#';
                    else board[playerLocation -1] = '.';
                    if (board[playerLocation] == 'X'){
                        cont = 0;
                    }else if (board[playerLocation] == '1'){
                        totalECTS += 8;
                        
                    }else if (board[playerLocation] == '2'){
                        totalECTS += 16;
                    }
                }
                board[playerLocation] = 'P';
            }
            
            break;
            
        case 'w':
            if (playerLocation > 16){
                if (isWall1(playerLocation -16)){
                    if (totalECTS >= 32){
                        playerLocation -= 16;
                        if (isWall1(playerLocation +16) || isWall2(playerLocation +16)) board[playerLocation +16] = '#';
                        else board[playerLocation +16] = '.';
                        board[playerLocation] = 'P';
                    }else printf("\nyou have not collected enough ECTS\n");
                    
                }else if(isWall2(playerLocation -16)){
                    if (totalECTS >= 64){
                        playerLocation -= 16;
                        if (isWall1(playerLocation +16) || isWall2(playerLocation +16)) board[playerLocation +16] = '#';
                        else board[playerLocation +16] = '.';
                        board[playerLocation] = 'P';
                    }else printf("\nyou have not collected enough ECTS\n");
                    
                }else{
                    playerLocation -=16;
                    if (isWall1(playerLocation +16) || isWall2(playerLocation +16)) board[playerLocation +16] = '#';
                    else board[playerLocation +16] = '.';
                    if (board[playerLocation] == '1'){
                        totalECTS += 8;
                        
                    }else if (board[playerLocation] == '2'){
                        totalECTS += 16;
                    }
                }
                board[playerLocation] = 'P';
            }
            
            break;
            
        default:
            break;
    }
}

int main(void) {
    initialize_game();
    char move = 'l';
    int totalMove = 0;
    
    printBoard();
    while (cont != 0) {
        printf("Total ETCS = %d \n",totalECTS);
        printf("\nEnter your move: \n");
        scanf(" %c",&move);
        totalMove++;
        movePlayer(move);
        printBoard();
        
    }
    printf("Congratulations! You've completed the game.\n");
    printf("Total ECTS: %d\nTotal Moves: %d\n", totalECTS, totalMove);
    
    return 0;
}
