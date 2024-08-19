//
//  main.c
//  HOMEWORK6
//
//  Created by Ahmet on 2.04.2024.
//

#include <stdio.h>

int find_size(int arr[]){
    
    for (int i = 0; ; i++) {
        if (arr[i] == -1 )return i;
    }
    return 0;
}

void duplicate_array(int main_arr[], int destination_arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (main_arr[i] != -1)
            destination_arr[i] = main_arr[i];
    }
}

int find_repeat_times(int arr[], int number, int size){
    int repeat = 0;
    for (int i = 0 ; i < size; i++) {
        if (arr[i] == number) repeat++;
    }
    return repeat;
}



int find_max_number(int arr[],int size){
    int max;
    max = arr[0];
    
    for (int i = 0; i < size; i++) {
        if (arr[i] > max){
            max = arr[i];
        }
    }
    
    return max;
}

void sortArray(int arr[],int size){
    int temp;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j] && arr[j] != -1){
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void find_repeated_numbers(int mainArr[],int arr[], int a ,int b,int size){
    int repeat;
    int count = 0;
    for (int i = a, j = 0; i <= b; i++,j++) {
        repeat = find_repeat_times(mainArr, i, size);
        arr[j] = repeat;
        count++;
    }
    for (count; count <= size; count++) {
        arr[count] = -1;
    }
    
}



void print_histogram(int arr[],int size){
    int max;
    
    max = find_max_number(arr, size);
    int max2 = find_max_number(arr, size);
    for (int i = 0; i < max2  ; i++) {
        
        
        for (int j = 0; j < size; j++) {
            if (arr[j] == max){
                printf("*");
                arr[j] -= 1;
            }else printf(" ");
        }
        printf("\n");
        max -= 1;
        
    }
}

void fill_interval_numbers(int mainArr[], int destinationArr[], int a, int b, int size){
    int count = 0, i;
    for (i = 0; i < size; i++) {
        if (mainArr[i] >= a && b >= mainArr[i]){
            destinationArr[count] = mainArr[i];
            count++;
        }
    }
    for (count; count < size; count++) {
        destinationArr[count] = -1;
    }
}

float calc_average(int arr[],int size){
    int total = 0, count = 0;
    
    for (int i = 0; i < size; i++) {
        
            total += arr[i];
            count++;
    }
    
    return (float)total/count;
}

float calc_median(int arr[],int size){

    if (size % 2 != 0)
           return arr[size / 2];
       
       
    return (arr[(size - 1) / 2] + arr[(size + 1)  / 2]) / 2.0;
    
}

void calc_mode(int repeated_number[],int valueA,int valueB){
    
    int max_repeat = find_max_number(repeated_number, valueB - valueA + 1);
    for (int i = 0 ; i <= valueB - valueA + 1 ; i++) {
        if (repeated_number[i] == max_repeat) printf("%d ",i + valueA);
    }
    
}

int main(void) {
    int number_array[] = {3, 8, 9, 9, 5, 2, 4, 7, 4, 8, 9, 10, 2, 4, 5, -1};
//    int number_array[] = {
//             45,  46,  47,  48,  49,  50,  133,  52,  53,  54,  55,  111,  57,  58,  59,  60,
//             61,  62,  63,  64,  65,  66,  55,  55,  69,  70,  55,  45,  73,  55,  75,  76,
//             77,  78,  79,  80,  81,  82,  55,  55,  85,  86,  87,  88,  89,  90,  91,  92,
//             93,  193, 95,   133,  76,  191,  55, 100, 101, 102, 76, 104, 105, 106, 107, 108,
//            120, 110, 111, 112, 113, 114, 115, 116, 117, 118, 163, 120, 121, 122, 193, 124,
//            125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140,
//            141, 193, 133, 144, 145, 146, 147, 148, 149, 150, 151, 193, 153, 154, 155, 156,
//            157, 158, 111, 160, 120, 162, 163, 128, 165, 166, 167, 168, 169, 170, 171, 172,
//            173, 174, 175, 176, 177, 111, 179, 180, 181, 111, 120, 184, 133, 186, 187, 188,
//            125, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 125, 201, 202, 203, 173,
//            205,  61, 128, 173,  76, 111, 133, 45, -1};
    int interval_numbers[find_size(number_array) + 1]; // This array holds numbers in the range selected by the user
    
    //    int number_array[] = {1,1, 2,2,2, 3, 4, 6, 7, 8, 9, 10,10,10,10, 11, 12, 13, 14, -1};
    
    int valueA,valueB,is_add = 0,size;
    float average = 0, median= 0,mode = 0;
    
    printf("Enter A and B values: ");
    scanf("%d %d",&valueA,&valueB);
    
    size = valueB - valueA + 2;
    int repeated_number[size]; // this array holds the number of repetitions of the numbers in the other array
    
    find_repeated_numbers(number_array, repeated_number, valueA, valueB, find_size(number_array)+1);
    fill_interval_numbers(number_array, interval_numbers, valueA, valueB, find_size(number_array) + 1);
    print_histogram(repeated_number,size);
    sortArray(interval_numbers, find_size(number_array) + 1);
    
    printf("would you like to add new number? (press 1 for yes, press 0 for no)");
    scanf("%d",&is_add);
    
    if (is_add) {
        int add_number,size2 = find_size(number_array);
        int new_array[size2 + 6];
        duplicate_array(number_array, new_array, size2);
        for (int i = 0; i < 5; i++) {
            printf("give me a number ");
            scanf("%d",&add_number);
            new_array[size2 + i] = add_number;
            if (add_number == -1)break;
        }
        new_array[size2 + 5] = -1;
        
        find_repeated_numbers(new_array, repeated_number, valueA, valueB, find_size(new_array) );
        fill_interval_numbers(new_array, interval_numbers, valueA, valueB, find_size(new_array) + 1);
        sortArray(interval_numbers, find_size(new_array) + 1);
        print_histogram(repeated_number,size);
        
        average = calc_average(interval_numbers, find_size(interval_numbers));
        median = calc_median(interval_numbers, find_size(interval_numbers));
        
        find_repeated_numbers(new_array, repeated_number, valueA, valueB, find_size(new_array) );

        printf("Average -> %.2f\n",average);
        printf("Median -> %.2f\n",median);
        printf("Mode ->");
        
        calc_mode(repeated_number, valueA, valueB);
//        int max_repeat = find_max_number(repeated_number, valueB - valueA + 1);
//        for (int i = 0 ; i <= valueB - valueA + 1 ; i++) {
//            if (repeated_number[i] == max_repeat) printf("% d",i + valueA);
//        }
        
    }else{
        average = calc_average(interval_numbers, find_size(interval_numbers));
        median = calc_median(interval_numbers, find_size(interval_numbers));
        find_repeated_numbers(number_array, repeated_number, valueA, valueB, find_size(number_array));
        
        printf("Average -> %.2f\n",average);
        printf("Median -> %.2f\n",median);
        printf("Mode -> ");
        
        calc_mode(repeated_number, valueA, valueB);
    }
    
    printf("\n");
    
    
    
    
    
    
    return 0;
}

