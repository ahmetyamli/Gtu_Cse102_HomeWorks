//
//  main.c
//  HOMEWORK2
//
//  Created by Ahmet on 7.03.2024.
//

#include <stdio.h>



#include <stdio.h>

int main(void) {
    FILE* file;
    
    int
    x,
    y,
    class,
    
    xMin = 0,
    xMax = 0,
    yMin = 0,
    yMax = 0,
    xMinCode0 = 0,
    xMinCode1  = 0,
    xMaxCode0 = 0,
    xMaxCode1 = 0,
    yMinCode0 = 0,
    yMinCode1 = 0,
    yMaxCode0= 0,
    yMaxCode1 = 0,
    
    bestError = -1,
    error = 0,
    
    seperatorY,
    seperatorX,
    bestSepX,
    bestSepY,
    
    R1_Total1,
    R2_Total1,
    R3_Total1,
    R4_Total1,
    
    R1_Total0,
    R2_Total0,
    R3_Total0,
    R4_Total0,
    
   BestR1,
   BestR2,
   BestR3,
   BestR4,
    
    menuItem;
    
    file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fscanf(file, "%d %d %d", &x, &y, &class) == 3) {
            if (class == 0) {
                if (xMinCode0 == 0 || x < xMinCode0) xMinCode0 = x;
                if (xMaxCode0 == 0 || x > xMaxCode0) xMaxCode0 = x;
                if (yMinCode0 == 0 || y < yMinCode0) yMinCode0 = y;
                if (yMaxCode0 == 0 || y > yMaxCode0) yMaxCode0 = y;
            } else if (class == 1) {
                if (xMinCode1 == 0 || x < xMinCode1) xMinCode1 = x;
                if (xMaxCode1 == 0 || x > xMaxCode1) xMaxCode1 = x;
                if (yMinCode1 == 0 || y < yMinCode1) yMinCode1 = y;
                if (yMaxCode1 == 0 || y > yMaxCode1) yMaxCode1 = y;
            }
        
        }
    if (xMaxCode0 > xMaxCode1) xMax = xMaxCode0;
    else xMax = xMaxCode1;
    
    if (xMinCode0 > xMinCode1) xMax = xMinCode1;
    else xMin = xMinCode0;
    
    if (yMaxCode0 > yMaxCode1) yMax = yMaxCode0;
    else yMax = yMaxCode1;
    
    if (yMinCode0 > yMinCode1) yMax = yMinCode1;
    else yMin = yMinCode0;
    

    fclose(file);

    printf("Class 0: X in [%d %d], Y in [%d %d]\n",xMinCode0,xMaxCode0,yMinCode0,yMaxCode0);
    printf("Class 1: X in [%d %d], Y in [%d %d]\n",xMinCode1,xMaxCode1,yMinCode1,yMaxCode1);
    while (1) {
        printf("1. Explore Data\n");
        printf("2. Train Model\n");
        printf("3. Test Model\n");
        printf("4. Exit\n");

        printf("Please enter a module from the list: ");
        scanf("%d", &menuItem);

        switch (menuItem) {
            case 1:
                file = fopen("data.txt", "r");
                if (file == NULL) {
                    printf("Error opening file.\n");
                    return 1;
                }

                while (fscanf(file, "%d", &x) == 1) {
                    fscanf(file, "%d", &y);
                    fscanf(file, "%d", &class);
                    printf("%d %d %d \n",x,y,class);
                    
                }

                fclose(file);
                break;

            case 2:

                file = fopen("data.txt", "r");
                if (file == NULL) {
                    printf("Error opening file.\n");
                    return 1;
                }

              
                R1_Total1 = 0;
                R2_Total1 = 0;
                R3_Total1 = 0;
                R4_Total1 = 0;
                
                R1_Total0 = 0;
                R2_Total0 = 0;
                R3_Total0 = 0;
                R4_Total0 = 0;
                
                    for (seperatorX = xMin; seperatorX <= xMax; seperatorX++) {


                        for (seperatorY = yMin; seperatorY <= yMax; seperatorY++) {
                            while (fscanf(file, "%d %d %d", &x, &y, &class) == 3) {
    
                                    if (x <= seperatorX && y > seperatorY){
                                        if (class == 1) R1_Total1 += 1;
                                        else R1_Total0 += 1;
                                    }else if (x > seperatorX && y > seperatorY){
                                        if (class == 1) R2_Total1 += 1;
                                        else R2_Total0 += 1;
                                    }else if (x <= seperatorX && y <= seperatorY){
                                        if (class == 1) R3_Total1 += 1;
                                        else R3_Total0 += 1;
                                    }else if (x > seperatorX && y <= seperatorY){
                                        if (class == 1) R4_Total1 += 1;
                                        else R4_Total0 += 1;
                                    }
                                
                            }
                            //I compared the total 1s and 0s. the larger one is the ideal code, while the smaller one is accepted as the margin of error.
                            if (R1_Total0 >= R1_Total1){

                                error += R1_Total1;
                            }else{

                                error += R1_Total0;
                            }
                            if (R2_Total0 >= R2_Total1){

                                error += R2_Total1;
                            }else{

                                error += R2_Total0;
                            }
                            if (R3_Total0 >= R3_Total1){

                                error += R3_Total1;
                            }else{

                                error += R3_Total0;
                            }
                            if (R4_Total0 >= R4_Total1){

                                error += R4_Total1;
                            }else{

                                error += R4_Total0;
                            }
                            
                            if (bestError == -1 || error < bestError) {
                                                       bestError = error;
                                                       bestSepX = seperatorX;
                                                       bestSepY = seperatorY;
                                
                                if (R1_Total0 >= R1_Total1) BestR1 = 0;
                                else BestR1 = 1;
                                
                                if (R2_Total0 >= R2_Total1) BestR2 = 0;
                                else BestR2 = 1;
                               
                                if (R3_Total0 >= R3_Total1) BestR3 = 0;
                                else BestR3 = 1;
                                
                                if (R4_Total0 >= R4_Total1) BestR4 = 0;
                                else BestR4 = 1;
                                
                                                   }
                            
                            R1_Total1 = 0;
                            R2_Total1 = 0;
                            R3_Total1 = 0;
                            R4_Total1 = 0;
                            
                            R1_Total0 = 0;
                            R2_Total0 = 0;
                            R3_Total0 = 0;
                            R4_Total0 = 0;
                            error = 0;
                            
                            fseek(file, 0, SEEK_SET);
                            
                        }
                    }
                


                fclose(file);
                
                printf("bestSepxX -> %d\n",bestSepX);
                printf("bestSepY -> %d\n",bestSepY);
                printf("bestR1 -> %d\n",BestR1);
                printf("bestR2 -> %d\n",BestR2);
                printf("bestR3 -> %d\n",BestR3);
                printf("bestR4 -> %d\n",BestR4);
                printf("xMax -> %d\n",xMax);
                printf("xMin -> %d\n",xMin);
                printf("yMax -> %d\n",yMax);
                printf("yMin -> %d\n",yMin);
                printf("bestError -> %d\n",bestError);
               
                break;
            case 3:
                file = fopen("test1.txt", "r");
                if (file == NULL) {
                    printf("Error opening file.\n");
                    return 1;
                }
                int error3 = 0,count = 0;
                float successRate;
                
                while (fscanf(file, "%d %d %d", &x, &y, &class) == 3) {

                        if (x <= bestSepX && y > bestSepY){

                            if (class == BestR1){
                            }else error3 += 1;
                            
                        }else if (x > bestSepX && y > bestSepY){

                            if (class == BestR2){
                            }else error3 += 1;
                        }else if (x <= bestSepX && y <= bestSepY){

                            if (class == BestR3){
                            }else error3 += 1;
                        }else if (x > bestSepX && y <= bestSepY){

                            if (class == BestR4){
                            }else error3 += 1;
                        }
                    
                    count += 1;
                    
                }
                printf("error -> %d, count -> %d \n",error3,count);
                
                successRate = ((count - error3) * 100) / count;
                printf("success rate -> %.2f\n", successRate);
                
                
                break;

            case 4:
                printf("Exiting program.\n");
                return 1;

            default:
                printf("Wrong selection. Please enter a valid option.\n");
                break;
        }
    }

    return 1;
}
