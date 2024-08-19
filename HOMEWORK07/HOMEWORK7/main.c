//
//  main.c
//  HOMEWORK7

#include <stdio.h>

int findMax(int stones[2][7]);

void initalizeGame(int stones[2][7]){
    int n = 0;
    printf("please enter the stone number ");
    scanf("%d",&n);
    for (int i = 0; i < 2; i++) {
        for (int j = 0 ; j < 7; j++) {
            stones[i][j] = n;
        }
        stones[i][6] = 0;
    }
}

void duplicateArray(int mainArr[2][7],int destinationArr[2][7]){
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 7; j++) {
            destinationArr[i][j] = mainArr[i][j];
        }
    }
}



int isOver(int stones[2][7]){
    int sum1 = stones[1][0] + stones[1][1] + stones[1][2] + stones[1][3] + stones[1][4] + stones[1][5] ;
    int sum2 = stones[0][0] + stones[0][1] + stones[0][2] + stones[0][3] + stones[0][4] + stones[0][5] ;
    
    if (sum1 == 0 || sum2 == 0) {
        return 1;
    }
    return 0;
}

void printBoard(int stones[2][7]){
    printf("+----+----+----+----+----+----+----+----+\n");
    printf("|    | %02d | %02d | %02d | %02d | %02d | %02d |    |\n",stones[1][5],stones[1][4],stones[1][3],stones[1][2],stones[1][1],stones[1][0]);
    printf("| %02d |----|----|----|----|----|----| %02d |\n",stones[1][6],stones[0][6]);
    printf("|    | %02d | %02d | %02d | %02d | %02d | %02d |    |\n",stones[0][0],stones[0][1],stones[0][2],stones[0][3],stones[0][4],stones[0][5]);
    printf("+----+----+----+----+----+----+----+----+\n");
}

void movee(int stones[2][7],int selectedHole, int isComp,int row){
    int SHnumber = stones[row][selectedHole], controlFlag, isRepeat = 0, isSelectCup = 0;

    if (stones[row][selectedHole] == 1){
        stones[row][selectedHole] = 0;
        stones[row][selectedHole + 1] += 1;
        if (isComp && row == 1 && selectedHole + 1 == 6 ) {
            isSelectCup = 1;
        }else if (!isComp && row == 0 && selectedHole + 1 == 6){
            isSelectCup = 1;
        }

    }else{
        stones[row][selectedHole] = 0;
        for (int i = 0; i < SHnumber; ) {
            selectedHole++;
            controlFlag = 0;
            if (selectedHole % 6 == 0 ) {
                if (i == SHnumber - 1){
                    isSelectCup = 1;
                }
                if (row == 1 ) {
                    if (isComp) {
                        stones[row][selectedHole] += 1;
                        i++;
                    }
                    row = 0;
                    selectedHole = 0;
                    if (i < SHnumber){
                        controlFlag = 1;
                        stones[row][selectedHole] += 1;
//                        i++;
                    }
                }else {
                    if (!isComp){
                        stones[row][selectedHole] += 1;
                        i++;
                    }
                    row = 1;
                    selectedHole = 0;
                    if (i < SHnumber){
                        controlFlag = 1;
                        stones[row][selectedHole] += 1;
//                        i++;
                    }
                }
            }
            
            
            
            if (i == SHnumber -1 && stones[row][selectedHole]){
                isRepeat = 1;  // control the last cup is empty
            }
            if (isComp && row == 1 && selectedHole == 6 && i == SHnumber - 1) {
                isSelectCup = 1;
            }else if (!isComp && row == 0 && selectedHole == 6 && i == SHnumber - 1){
                isSelectCup = 1;
            }
            
            if(!controlFlag){
                stones[row][selectedHole] += 1;
                i++;
            }
            else
                i++;

        }
    }

    if (isRepeat) {
//        printBoard(stones);
        movee(stones, selectedHole, isComp, row);
    }
    if (isSelectCup){
        printBoard(stones);
        if (isComp) {
            printf("turn comp again\n");
            selectedHole = findMax(stones);
            printf("the comp play with %d. cup\n",selectedHole);
            movee(stones, selectedHole, isComp, isComp);
        }else{
            
            while (1) {
                
                printf("please select a cup again ");
                scanf("%d",&selectedHole);
                if (selectedHole < 7 && 0 < selectedHole) {
                    if (stones[0][selectedHole - 1] == 0) printf("you can not chose this cup\n");
                    else break;
                }else printf("invalid selection\n");
            }
            movee(stones, selectedHole - 1, 0,0);
            
        }
    }
}

int findMax(int stones[2][7]){
    
    int max = 0,maxIndice = 0;
    int j;
    
    for (j = 0; j < 6; j++) {
        if (stones[1][j] > max){
            max = stones[1][j];
            maxIndice = j;
        }
    }
    
    return maxIndice;
}



void gamePlay(int stones[2][7]){
        
    int selectedHole;
    int isComp = 0;
    
    while (1) {
        if (isOver(stones)){
            if (stones[1][6] > stones[0][6]) {
                printf("the comp  won this game");
            }else if (stones[1][6] == stones[0][6]){
                printf("no one won the game . except friendship ");
            }else{
                printf("the user won this game.");
            }
            break;
        }
        
        if(!isComp){
            while (1) {
                printf("please select a cup \n");
                scanf("%d",&selectedHole);
                if (selectedHole < 7 && 0 < selectedHole) {
                    if (stones[0][selectedHole - 1] == 0) printf("you can not chose this cup\n");
                    else break;
                }else printf("invalid selection\n");
            }
            movee(stones, selectedHole - 1, 0,0);
        }

        
        
        else {
            printf("turn comp\n");
            selectedHole = findMax(stones);
            printf("the comp play with %d. cup\n",selectedHole);
            movee(stones, selectedHole, isComp, isComp);
            
        }
        isComp = !isComp;
        printBoard(stones);
            
    }
}
    
int main(void) {
        
    int stones[2][7];
    
    initalizeGame(stones);
    printBoard(stones);
    gamePlay(stones);
        
    return 0;
}



//   4 4 4 4 4 4
// 10            10
//   0 5 5 5 5 4

