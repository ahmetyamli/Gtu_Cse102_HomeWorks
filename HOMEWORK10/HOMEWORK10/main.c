////
////  main.c
////  HOMEWORK10
////
////  Created by Ahmet on 15.05.2024.
////
//
//#include <stdio.h>
//#include <string.h>
//#include <math.h>
//
//#define file_path "/Users/ahmet/Desktop/School/Cse102/HOMEWORK10/HOMEWORK10/input.asm"
//
///* MARK: - struct declaration */
//
//
//typedef enum {
//    ADD, ADDI, ADDM, AND, ANDI, ANDM, OR, ORI, ORM, SUB, SUBI, SUBM,
//    INC, DEC, SHL, SHR, BRE, BRN, J, NOR, LDA, STR, SWP, LESS, GRT, PRI,
//    PRII, PRIM, LDAI, EXIT, NUM_OPCODES
//} Opcode;
//
//typedef enum{
//    G,
//    T,
//    U,
//    
//} OpType;
//
//typedef struct {
//    Opcode code;
//    const char *name;
//    const char *opcode;
//    OpType optype;
//} InstructionInfo;
//
//const InstructionInfo instructionSet[NUM_OPCODES] = {
//    {ADD, "ADD", "00000001",G},
//    {ADDI,  "ADDI",  "00000010",T},
//    {ADDM, "ADDM", "00000011",U},
//    {AND,  "AND",  "00000100",G},
//    {ANDI,  "ANDI",  "00000101",T},
//    {ANDM,  "ANDM",  "00000110",U},
//    {OR,  "OR",  "00000111",G},
//    {ORI,  "ORI",  "00001000",T},
//    {ORM,  "ORM",  "00001001",U},
//    {SUB,  "SUB",  "00001010",G},
//    {SUBI,   "SUBI",   "00001011",T},
//    {SUBM,  "SUBM",  "00001100",U},
//    {INC,  "INC",  "00001101",T},
//    {DEC,  "DEC",  "00001110",T},
//    {SHL,  "SHL",  "00001111",T},
//    {SHR,  "SHR",  "00010000",T},
//    {BRE,   "BRE",   "00010001",G},
//    {BRN,  "BRN",  "00010010",G},
//    {J, "J", "00010011",G},
//    {NOR,  "NOR",  "00010100",G},
//    {LDA, "LDA", "00010101",U},
//    {STR,  "STR",  "00010110",U},
//    {SWP, "SWP", "00010111",G},
//    {LESS, "LESS", "00011000",G},
//    {GRT, "GRT", "00011001",G},
//    {PRI, "PRI", "00011010",G},
//    {PRII, "PRII", "00011011",T},
//    {PRIM, "PRIM", "00011100",U},
//    {LDAI, "LDAI", "00011101\0",T},
//    {EXIT, "EXIT", "00011110"},
//    
//};
//
//
//typedef struct {
//    int line; // 8 bit opcode + '\0' for string termination
//    char register1[9];
//} MemoryCell;
//
///* MARK: - func declaration */
//
//int binary_to_decimal(const char *binary);
//void decimal_to_binary(int decimal, char *binary);
//void read_file(void);
//void get_instruciton_with_opcode(Opcode opcode);
//int read_file_find_size(void);
//void fetch_instruction(MemoryCell memory[], int size);
//void copy_arr(char arr[], char destination[], int size);
//int yetAnotherAtoi(char *str);
///* MARK: - main func */
//
//int main(int argc, const char * argv[]) {
//    
//    int size = read_file_find_size();
//    char A[9],B[9];
//    decimal_to_binary(size + 2, A);
//    decimal_to_binary(size + 3, B);
//    int x = yetAnotherAtoi("230");
//    printf("--%d--\n",x / 10);
//    printf("A -> %d...%s\n",size + 2,A);
//    printf("B -> %d...%s\n",size + 3,B);
//    
//    MemoryCell memory[size + 10];
//    //    get_instruciton_with_opcode(LDAI);
//    fetch_instruction(memory, size);
//    
//    return 0;
//}
//
///* MARK: - funcs */
//
//int read_file_find_size(void){
//    FILE *file = fopen(file_path, "r");
//    int size = 0;
//    char c = '\0';
//    while (c != EOF) {
//        c = getc(file);
//        if (c != '\xff') {
//            printf("%c",c);
//        }
//        if (c == '\n') size++;
//        
//    }
//    printf("size -> %d\n",size);
//    fclose(file);
//    return 3 * size;
//    
//}
//
//void decimal_to_binary(int decimal, char *binary) {
//    int index = 0,i;
//    while (decimal > 0) {
//        binary[index++] = (decimal % 2) + '0';
//        decimal /= 2;
//    }
//    //    binary[index] = '\0';
//    while (index < 8) {
//        binary[index] = '0';
//        index++;
//    }
//    binary[8] = '\0';
//    /* Reverse the binary string to get the correct representation */
//    size_t len = strlen(binary);
//    for ( i = 0; i < len / 2; i++) {
//        char temp = binary[i];
//        binary[i] = binary[len - 1 - i];
//        binary[len - 1 - i] = temp;
//    }
//    
//    /* If the binary string is empty, it means the number was 0 */
//    if (index == 0) {
//        strcpy(binary, "0");
//    }
//}
//
//int binary_to_decimal(const char *binary) {
//    int decimal = 0,i;
//    size_t length = strlen(binary);
//    for (i = 0; i < length; i++) {
//        if (binary[length - 1 - i] == '1') {
//            decimal += (int)pow(2, i);
//        }
//    }
//    return decimal;
//}
//
//void get_instruciton_with_opcode(Opcode opcode){
//    int i;
//    for (i = 0; i < NUM_OPCODES; i++) {
//        if (instructionSet[i].code == opcode){
//            printf("type -> %u\n",instructionSet[i].optype);
//            printf("name -> %s\n",instructionSet[i].name);
//            printf("code -> %u\n",instructionSet[i].code);
//            printf("opcode -> %s\n",instructionSet[i].opcode);
//        }
//    }
//}
//
//void fetch_instruction(MemoryCell memory[], int size){
//    FILE *file = fopen(file_path, "r");
//    InstructionInfo lineInfo;
//    int i = 0, j = 0;
//    char opCodeName[5], c = '\0';
//    char registerA[8], registerB[8];
//    
//    decimal_to_binary(size + 2, registerA);
//    decimal_to_binary(size + 3, registerB);
//    
//    while (c != ' ' && c != EOF) {
//        c = fgetc(file);
//        opCodeName[i] = c;
//        i++;
//    }
//    if (i == 3 ) opCodeName[3] = '\0';
//    i = 0;
//    opCodeName[4] = '\0';
//    printf("opCccc -> %s\n",opCodeName);
//    
//    for (i = 0; i < NUM_OPCODES; i++) {
//        if (strcmp(opCodeName, instructionSet[i].name) == 0) {
//            lineInfo = instructionSet[i];
//            break;
//        }
//    }i = 0;
//    memory[j].line = j + 1;
//    strcpy(memory[j].register1, lineInfo.opcode);
//    printf("---%s----\n",memory[j].register1);
//    printf("%lu",strlen(memory[j].register1));
//    j++;
//    c = fgetc(file);
//    if (lineInfo.optype == G) {
//        if (lineInfo.code == PRI) {
//            if (c == 'A'){
//                strcpy(memory[j].register1, registerA);
//                j++;
//            }else{
//                strcpy(memory[j].register1, registerB);
//                j++;
//            }
//            strcpy(memory[j].register1, "00000000");
//            j++;
//        }else{
//            if (c == 'A'){
//                strcpy(memory[j].register1, registerA);
//                j++;
//            }else{
//                strcpy(memory[j].register1, registerB);
//                j++;
//            }
//            
//            fgetc(file);
//            c = fgetc(file);
//            
//            if (c == 'A'){
//                strcpy(memory[j].register1, registerA);
//                j++;
//            }else{
//                strcpy(memory[j].register1, registerB);
//                j++;
//            }
//
//        }
//    }else if (lineInfo.optype == T){
//        
//        printf("type t");
//    }else if (lineInfo.optype == U){
//        printf("type d");
//    }
//    printf("flocse=%d",fclose(file));
////    if(fclose(file) != 0)
////    {
////        perror("debug test1");
////        return;
////    }
////    
//    printf("---%s----\n",memory[j - 1].register1);
//    printf("%lu",strlen(memory[j - 1].register1));
//}
//
//int yetAnotherAtoi(char *str)
//{
// int res = 0; // Initialize result
//
// for (int i = 0; str[i] != '\0'; ++i) {
//     if (str[i]> '9' || str[i]<'0')
//         return -1;
//     res = res*10 + str[i] - '0';
// }
//
// // return result.
// return res;
//}
////void fetch_instruction(MemoryCell memory[], int size){
////    FILE *file = fopen(file_path, "r");
////    InstructionInfo lineInfo;
////    int i = 0, j = 0;
////    char opCodeName[5], c = '\0';
////    char A[8],B[8];
////    decimal_to_binary(size + 2, A);
////    decimal_to_binary(size + 3, B);
////
////    while (c != EOF) {
////        i = 0;
////        while (c != ' ' && c != EOF) {
////            c = fgetc(file);
////            opCodeName[i] = c;
////            i++;
////        }
////        if (i == 3 ) opCodeName[3] = '\0';
////        opCodeName[4] = '\0';
////            printf("opCccc -> %s\n",opCodeName);
////        for (i = 0; i < NUM_OPCODES; i++) {
////            if (strcmp(opCodeName, instructionSet[i].name) == 0) {
////                lineInfo = instructionSet[i];
////                break;
////            }
////        }
////        i = 0;
////
////        memory[j].line = j + 1;
//////        memory[j]->register1 = lineInfo.opcode;
////        strcpy(memory[j].register1, lineInfo.opcode);
//////        copy_arr(memory[j]->register1, lineInfo.opcode, 9);
////        if (lineInfo.optype == G) {
////            c = fgetc(file);
////            if (c == 'A'){
////                strcpy(memory[j + 1].register1, A);
////            }
////            else strcpy(memory[j + 1].register1, B);
////            c = fgetc(file);
////            if (c == 'A') strcpy(memory[j + 1].register1, A);
////            else strcpy(memory[j + 1].register1, B);
////        }
////        printf("------\n");
////        get_instruciton_with_opcode(lineInfo.code);
////        while (c != '\n' && c != EOF) {
////           c = fgetc(file);
////        }
////        j += 3;
////    }
////}
//
//
#include <stdio.h>
#include <string.h>
#include <math.h>
///Users/ahmet/Desktop/School/Cse102/HOMEWORK10/HOMEWORK10/
#define file_path "/Users/ahmet/Desktop/HOMEWORK10/input.txt"
 
/* MARK: - struct declaration */
 
 
typedef enum {
    ADD, ADDI, ADDM, AND, ANDI, ANDM, OR, ORI, ORM, SUB, SUBI, SUBM,
    INC, DEC, SHL, SHR, BRE, BRN, J, NOR, LDA, STR, SWP, LESS, GRT, PRI,
    PRII, PRIM, LDAI, EXIT, NUM_OPCODES
} Opcode;
 
typedef enum{
    G,
    T,
    U,
    E,
    
} OpType;
 
typedef struct {
    Opcode code;
    const char *name;
    const char *opcode;
    OpType optype;
} InstructionInfo;
 
const InstructionInfo instructionSet[NUM_OPCODES] = {
    {ADD, "ADD", "00000001",G},
    {ADDI,  "ADDI",  "00000010",T},
    {ADDM, "ADDM", "00000011",U},
    {AND,  "AND",  "00000100",G},
    {ANDI,  "ANDI",  "00000101",T},
    {ANDM,  "ANDM",  "00000110",U},
    {OR,  "OR",  "00000111",G},
    {ORI,  "ORI",  "00001000",T},
    {ORM,  "ORM",  "00001001",U},
    {SUB,  "SUB",  "00001010",G},
    {SUBI,   "SUBI",   "00001011",T},
    {SUBM,  "SUBM",  "00001100",U},
    {INC,  "INC",  "00001101",T},
    {DEC,  "DEC",  "00001110",T},
    {SHL,  "SHL",  "00001111",T},
    {SHR,  "SHR",  "00010000",T},
    {BRE,   "BRE",   "00010001",G},
    {BRN,  "BRN",  "00010010",G},
    {J, "J", "00010011",G},
    {NOR,  "NOR",  "00010100",G},
    {LDA, "LDA", "00010101",U},
    {STR,  "STR",  "00010110",U},
    {SWP, "SWP", "00010111",G},
    {LESS, "LESS", "00011000",G},
    {GRT, "GRT", "00011001",G},
    {PRI, "PRI", "00011010",G},
    {PRII, "PRII", "00011011",T},
    {PRIM, "PRIM", "00011100",U},
    {LDAI, "LDAI", "00011101\0",T},
    {EXIT, "EXIT", "00011110",E},
    
};
 
 
typedef struct {
    int line;
    char register1[9];
} MemoryCell;
 
/* MARK: - func declaration */
 
int binary_to_decimal(const char *binary);
void decimal_to_binary(int decimal, char *binary);
void read_file(void);
void get_instruciton_with_opcode(Opcode opcode);
int read_file_find_size(void);
void fetch_instruction(MemoryCell memory[],MemoryCell memoryCopy[], int size);
void copy_arr(char arr[], char destination[], int size);
int yetAnotherAtoi(char *str);
void printMemory(MemoryCell memory[], int size);
void execute_memory(MemoryCell memory[], int size);
/* MARK: - main func */
 
int main(int argc, const char * argv[]) {
    
    int size = read_file_find_size();
    
    int x = yetAnotherAtoi("230");
    printf("--%d--\n",x / 10);
    
    MemoryCell memory[size + 10];
    MemoryCell memoryCopy[size + 10];
    
    fetch_instruction(memory,memoryCopy, size);
    printMemory(memoryCopy,size);
    execute_memory(memoryCopy, size);
    return 0;
}
 
/* MARK: - funcs */
 
int read_file_find_size(void){
    FILE *file = fopen(file_path, "r");
    int size = 0;
    char c = '\0';
    while (c != EOF) {
        c = getc(file);
        if (c != '\xff') {
            printf("%c",c);
        }
        if (c == '\n') size++;
        
    }
    printf("size -> %d\n",size);
    fclose(file);
    return 3 * size;
    
}
 
void decimal_to_binary(int decimal, char *binary) {
    int index = 0,i;
    while (decimal > 0) {
        binary[index++] = (decimal % 2) + '0';
        decimal /= 2;
    }
    //    binary[index] = '\0';
    while (index < 8) {
        binary[index] = '0';
        index++;
    }
    binary[8] = '\0';
    /* Reverse the binary string to get the correct representation */
    size_t len = strlen(binary);
    for ( i = 0; i < len / 2; i++) {
        char temp = binary[i];
        binary[i] = binary[len - 1 - i];
        binary[len - 1 - i] = temp;
    }
    
    /* If the binary string is empty, it means the number was 0 */
    if (index == 0) {
        strcpy(binary, "0");
    }
}
 
int binary_to_decimal(const char *binary) {
    int decimal = 0,i;
    size_t length = strlen(binary);
    for (i = 0; i < length; i++) {
        if (binary[length - 1 - i] == '1') {
            decimal += (int)pow(2, i);
        }
    }
    return decimal;
}
 
void get_instruciton_with_opcode(Opcode opcode){
    int i;
    for (i = 0; i < NUM_OPCODES; i++) {
        if (instructionSet[i].code == opcode){
            printf("type -> %u\n",instructionSet[i].optype);
            printf("name -> %s\n",instructionSet[i].name);
            printf("code -> %u\n",instructionSet[i].code);
            printf("opcode -> %s\n",instructionSet[i].opcode);
        }
    }
}
 
void fetch_instruction(MemoryCell memory[],MemoryCell memoryCopy[], int size){
    FILE *file = fopen(file_path, "r");
    InstructionInfo lineInfo;
    int i = 0, j = 0;
    char opCodeName[5], c = '\0';
    char stringInt[5];
 
    char registerA[9], registerB[9];
    char memoryA[9], memoryB[9];
    char stringToBinary[8];
    
    decimal_to_binary(size + 2, registerA);
    decimal_to_binary(size + 3, registerB);
    
    while (c != EOF)
    {
        decimal_to_binary(size + 4, memoryA);
        decimal_to_binary(size + 5, memoryB);
        for (i = 0; i < 5; i++) {
            opCodeName[i] = '\0';
        }i = 0;
        while (c != ' ' && c != EOF)
    {
        c = fgetc(file);
        opCodeName[i] = c;
        i++;
    }

        opCodeName[i - 1] = '\0';
    i = 0;
    opCodeName[4] = '\0';
   
    
    for (i = 0; i < NUM_OPCODES; i++) {
        if (strcmp(opCodeName, instructionSet[i].name) == 0) {
            lineInfo = instructionSet[i];
            break;
        }
    }i = 0;
        printf("----------\n");
    printf("opCode name -> %s\n",opCodeName);
 
    printf("lineinfo name -> %s\n",lineInfo.name);
    memory[j].line = j + 1;
    strcpy(memory[j].register1, lineInfo.opcode);

    j++;
    c = fgetc(file);

    if (lineInfo.optype == G) {
        if (lineInfo.code == PRI) {
            if (c == 'A'){
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerA);
                j++;
            }else{
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerB);
                j++;
            }
            strcpy(memory[j].register1, "00000000\0");
            j++;
        }else{
            if (c == 'A'){
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerA);
                j++;
            }else{
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerB);
                j++;
            }
            
            fgetc(file);
            c = fgetc(file);
            
            if (c == 'A'){
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerA);
                j++;
            }else{
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerB);
                j++;
            }
 
        }
        
        printf("type g\n");
    }else if (lineInfo.optype == T){
    
        
        if (lineInfo.code == INC || lineInfo.code == DEC)
        {
            if (c == 'A'){
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerA);
                j++;
            }else{
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerB);
                j++;
            }
            memory[j].line = j + 1;
            strcpy(memory[j].register1, "00000000");
                j++;
        while (c != '\n' && c != EOF) {
          c = fgetc(file);
        }
        }else if (lineInfo.code == PRII){
            i = 0 ;
            c = fgetc(file);
            while (c != ' ' && c != EOF && c != '\n')
            {
                
                stringInt[i] = c;
                 i++;
                 c = fgetc(file);
            }
            stringInt[i] = '\0';
            int x = yetAnotherAtoi(stringInt);
            decimal_to_binary(x,stringToBinary);
            memory[j].line = j + 1;
            strcpy(memory[j].register1, stringToBinary);
            j++;
            memory[j].line = j + 1;
            strcpy(memory[j].register1, "00000000");
            j++;
 
 
        }else{
            if (c == 'A'){
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerA);
                j++;
            }else{
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerB);
                j++;
            }
            c = fgetc(file);
            c = fgetc(file);
            
            i = 0;
            while (c != ' ' && c != '\n' && c != EOF )
            {
                stringInt[i] = c;
                 i++;
                 c = fgetc(file);
            }
             stringInt[i] = '\0';
            int x = yetAnotherAtoi(stringInt);
            decimal_to_binary(x,stringToBinary);
            memory[j].line = j + 1;
            strcpy(memory[j].register1, stringToBinary);
            j++;
            
        }
         printf("type t\n");
    }else if (lineInfo.optype == U){
        if(lineInfo.code == PRIM){
            c = fgetc(file);
            c = fgetc(file);
            if (c == 'A')
            {
                memory[j].line = j + 1;
                strcpy(memory[j].register1, memoryA);
                j++;
            }else{
                memory[j].line = j + 1;
                strcpy(memory[j].register1, memoryB);
                j++;
            }
            
        }else {
            if (c == 'A')
            {
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerA);
                j++;
            }else{
                memory[j].line = j + 1;
                strcpy(memory[j].register1, registerB);
                j++;
            }
            fgetc(file);
            fgetc(file);
            fgetc(file);
            c = fgetc(file);
            if (c == 'A')
            {
                memory[j].line = j + 1;
                strcpy(memory[j].register1, memoryA);
                j++;
            }else{
                memory[j].line = j + 1;
                strcpy(memory[j].register1, memoryB);
                j++;
            }
        }
        printf("type u\n");
    }else if ( lineInfo.optype == E){
        memory[j].line = j + 1;
        strcpy(memory[j].register1, memoryA);
        j++;
        memory[j].line = j + 1;
        strcpy(memory[j].register1, memoryA);
        j++;
        break;
    }
    while (c != EOF && c != '\n')
    {
        c = fgetc(file);
    }
        printf("j in hereeee -> %d\n",j);
        printf("%s\n",memory[j-3].register1);
        printf("%s\n",memory[j-2].register1);
        printf("%s\n",memory[j-1].register1);
        
        memoryCopy[j-1] = memory[j - 1];
        memoryCopy[j-2] = memory[j - 2];
        memoryCopy[j-3] = memory[j - 3];
    }
//    memory[size + 2].register1
    strcpy(memory[size + 2].register1, registerA);
    strcpy(memory[size + 3].register1, registerB);
    strcpy(memory[size + 4].register1, memoryA);
    strcpy(memory[size + 5].register1, memoryB);
    strcpy(memory[size + 6].register1, "00000001");
  
    fclose(file);
 
}
 
int yetAnotherAtoi(char *str){
int res = 0;
    int i;
for ( i = 0; str[i] != '\0'; ++i) {
     if (str[i]> '9' || str[i]<'0')
         return -1;
     res = res*10 + str[i] - '0';
}
 

return res;
}

void printMemory(MemoryCell memory[],int size){
    int i = 0;
        printf("\n------------------\n");
 
    for (i =0 ; i < size + 10; i++)
    {
         printf("%d \n",memory[i].line);
        printf("%s\n",memory[i].register1);
    }
    printf("*************\n");
}

void execute_memory(MemoryCell memory[], int size){
    int i = 0, j = 0;
    InstructionInfo lineInfo;
    for (i = 0; i < size ; i += 3) {
        
        for (j = 0; j < NUM_OPCODES; j++) {
            if (strcmp(memory[i].register1, instructionSet[i].opcode) == 0) {
                lineInfo = instructionSet[i];
                break;
            }
        }j = 0;
        
        switch (lineInfo.code) {
            case ADD:
                
                break;
            case ADDI:
                
                break;
            case ADDM:
                
                break;
            case AND:
                
                break;
            case ANDI:
                
                break;
            case ANDM:
                
                break;
            case OR:
                
                break;
            case ORI:
                
                break;
            case ORM:
                
                break;
            case SUB:
                
                break;
            case SUBI:
                
                break;
            case SUBM:
                
                break;
            case INC:
                
                break;
            case DEC:
                
                break;
            case SHL:
                
                break;
            case SHR:
                
                break;
            case BRE:
                
                break;
            case BRN:
                
                break;
            case J:
                
                break;
            case NOR:
                
                break;
            case LDA:
                
                break;
            case STR:
                
                break;
            case SWP:
                
                break;
            case LESS:
                
                break;
            case GRT:
                
                break;
            case PRI:
                
                break;
            case PRII:
                
                break;
            case PRIM:
                
                break;
            case LDAI:
                
                break;
            case EXIT:
                
                break;
            
            default:
                break;
        }
    }
}

//{ADD, "ADD", "00000001",G},
//{ADDI,  "ADDI",  "00000010",T},
//{ADDM, "ADDM", "00000011",U},
//{AND,  "AND",  "00000100",G},
//{ANDI,  "ANDI",  "00000101",T},
//{ANDM,  "ANDM",  "00000110",U},
//{OR,  "OR",  "00000111",G},
//{ORI,  "ORI",  "00001000",T},
//{ORM,  "ORM",  "00001001",U},
//{SUB,  "SUB",  "00001010",G},
//{SUBI,   "SUBI",   "00001011",T},
//{SUBM,  "SUBM",  "00001100",U},
//{INC,  "INC",  "00001101",T},
//{DEC,  "DEC",  "00001110",T},
//{SHL,  "SHL",  "00001111",T},
//{SHR,  "SHR",  "00010000",T},
//{BRE,   "BRE",   "00010001",G},
//{BRN,  "BRN",  "00010010",G},
//{J, "J", "00010011",G},
//{NOR,  "NOR",  "00010100",G},
//{LDA, "LDA", "00010101",U},
//{STR,  "STR",  "00010110",U},
//{SWP, "SWP", "00010111",G},
//{LESS, "LESS", "00011000",G},
//{GRT, "GRT", "00011001",G},
//{PRI, "PRI", "00011010",G},
//{PRII, "PRII", "00011011",T},
//{PRIM, "PRIM", "00011100",U},
//{LDAI, "LDAI", "00011101\0",T},
//{EXIT, "EXIT", "00011110"},
