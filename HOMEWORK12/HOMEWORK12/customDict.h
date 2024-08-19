
#ifndef customDict_h
#define customDict_h

#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

typedef union Value {
    int i;
    float f;
    double d;
    char c;
}Value;


typedef struct Item {
    char *key;
    Value value;
    char type;
}Item;


typedef struct CustomDict {
    Item *items;
    int capacity;
    int size;
}CustomDict;

struct CustomDict* create_dict(void );
void add_item(struct CustomDict* dict, char* key, union Value* value,char type);
void delete_item(struct CustomDict* dict, char* key);
void set_value(struct CustomDict* dict, char* key, union Value* value);
union Value* search_item(struct CustomDict* dict, char* key);
void sort_dict(struct CustomDict* dict);
void print_dict(struct CustomDict* dict);
void free_dict(struct CustomDict* dict);
int read_csv(int file_info[100],CustomDict *dicts,const char* filename, const int size);
void read_csv_find_size(int file_info[100],const char* filename, int* total_size);

void read_csv_find_size(int file_info[100],const char* filename, int* total_size){
    FILE* file = fopen(filename, "r") ;
    
    int i = 0;
    int k = 0;
    
    if (!file) {
        printf("the file did not open");
        return;
    }
    char c = '\0' ;
    
    for (k = 0; k < 100; k++) {
        file_info[k] = 0;
    }
    
    while (c != EOF) {
        if (c == ',') {
            file_info[i] += 1;
            
        }
        if(c == '\n'){
            file_info[i] += 1;
            i++;
            
        }
        
        c = fgetc(file);
        if (c == EOF){
            file_info[i] += 1;
        }
    }

    *total_size = i;
    
    fclose(file);
}

void print_info(int file_info[100]){
    int k;
    for (k = 0; k < 100; k++) {
        printf("%d ",file_info[k]);
        printf("\n");
    }
}



int read_csv(int file_info[100],CustomDict *dicts,const char* filename, const int size){
    FILE* file = fopen(filename, "r") ;
    int i = 0,j = 0, k = 0;
    if (!file) {
        printf("the file did not open");
        return 0;
    }

    char c = '\0' ;
    char key[20];
    while (file_info[i] != 0 && c != EOF) {
        c = fgetc(file);
        int ivalue[12] ;
        float fvalue[12];
        double dvalue[12];
        char cvalue[12];
        char valueTemp[12];
        long int lenght = 0;
        Value val;
        switch (c) {
            case 'i':
                
                while (c != ',') {
                    c = fgetc(file);
                }
                c = fgetc(file);
                while (c != ',') {
                    c = fgetc(file);
                    key[j] = c;
                    j++;
                }
                key[j - 1] = '\0';
                lenght = strlen(key);
                c = fgetc(file);
                k = 0;
                j = 0;
                while (k != file_info[i] - 2) {
                    while (c != ',' && c != '\n' && c != '\r') {
                        c = fgetc(file);
                        valueTemp[j] = c;
                        j++;
                    }
                    j = 0;
                    c = fgetc(file);
                    ivalue[k] = atoi(valueTemp);
                    val.i = ivalue[k];
                    sprintf(key + lenght, "%d",k);
                    add_item(dicts, key, &val,'i');
                    k++;
                    
                }
                
                
                break;
            case 'c':
                while (c != ',') {
                    c = fgetc(file);
                }
                c = fgetc(file);
                while (c != ',') {
                    c = fgetc(file);
                    key[j] = c;
                    j++;
                }
                key[j - 1] = '\0';
                lenght = strlen(key);
                c = fgetc(file);
                k = 0;
                j = 0;
                while (k != file_info[i] - 2) {
                    while (c != ',' && c != '\n' && c != '\r') {
                        c = fgetc(file);
                        valueTemp[j] = c;
                        j++;
                    }
                    j = 0;
                    c = fgetc(file);
                    cvalue[k] = valueTemp[0];
                    val.c = cvalue[k];
                    sprintf(key + lenght, "%d",k);
                    add_item(dicts, key, &val, 'c');

                    k++;
                    
                }
                cvalue[k] = '\0';
               
                break;
            case 'f':
                while (c != ',') {
                    c = fgetc(file);
                }
                c = fgetc(file);
                while (c != ',') {
                    c = fgetc(file);
                    key[j] = c;
                    j++;
                }
                key[j - 1] = '\0';
                lenght = strlen(key);
                c = fgetc(file);
                k = 0;
                j = 0;
                while (k != file_info[i] - 2) {
                    while (c != ',' && c != '\n' && c != '\r') {
                        c = fgetc(file);
                        valueTemp[j] = c;
                        j++;
                    }
                    j = 0;
                    c = fgetc(file);
                    fvalue[k] = atof(valueTemp);
                    val.f = fvalue[k];
                    sprintf(key + lenght, "%d",k);
                    add_item(dicts, key, &val, 'f');

                    k++;
                    
                }
                break;
            case 'd':
                while (c != ',') {
                    c = fgetc(file);
                }
                c = fgetc(file);
                while (c != ',') {
                    c = fgetc(file);
                    key[j] = c;
                    j++;
                }
                key[j - 1] = '\0';
                lenght = strlen(key);
                c = fgetc(file);
                k = 0;
                j = 0;
                while (k != file_info[i] - 2) {
                    while (c != ',' && c != '\n' && c != '\r' && c != EOF) {
                        c = fgetc(file);
                        valueTemp[j] = c;
                        j++;
                    }
                    j = 0;
                    c = fgetc(file);
                    dvalue[k] = (double)atof(valueTemp);
                    val.d = dvalue[k];
                    sprintf(key + lenght, "%d",k);
                    add_item(dicts, key, &val,'d');

                    k++;
                    
                }
                break;
                
            default:
                break;
        }
        i++;
    }
    
    fclose(file);
    return 1;
}

struct CustomDict* create_dict(void) {
    struct CustomDict *dict = (struct CustomDict*) malloc(sizeof(struct CustomDict));
    dict->items = NULL;
    dict->capacity = 0;
    dict->size = 0;
    return dict;
}


void add_item(struct CustomDict* dict, char* key, union Value* value,char type) {
    if (dict->size == dict->capacity) {
        dict->capacity = dict->capacity == 0 ? 1 : dict->capacity * 2;
        dict->items = (struct Item*) realloc(dict->items, dict->capacity * sizeof(struct Item));
    }
    int i;
    for ( i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            dict->items[i].value = *value;
            return;
        }
    }

    dict->items[dict->size].key = strdup(key);
    dict->items[dict->size].value = *value;
    dict->items[dict->size].type = type;
    dict->size++;
}


void delete_item(struct CustomDict* dict, char* key) {
    int i,j;
    for ( i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            free(dict->items[i].key);
            for ( j = i; j < dict->size - 1; j++) {
                dict->items[j] = dict->items[j + 1];
            }
            dict->size--;
            return;
        }
    }
}

// Sözlükteki bir öğenin değerini günceller
void set_value(struct CustomDict* dict, char* key, union Value* value) {
    int i;
    for ( i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            dict->items[i].value = *value;
            return;
        }
    }
}


union Value* search_item(struct CustomDict* dict, char* key) {
    int i;
    for ( i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            return &dict->items[i].value;
        }
    }
    return NULL;
}


void sort_dict(struct CustomDict* dict) {
    int i,j;
    for ( i = 0; i < dict->size - 1; i++) {
        for ( j = i + 1; j < dict->size; j++) {
            if (strcmp(dict->items[i].key, dict->items[j].key) > 0) {
                struct Item temp = dict->items[i];
                dict->items[i] = dict->items[j];
                dict->items[j] = temp;
            }
        }
    }
}


void print_dict(struct CustomDict* dict) {
    int i;
    for ( i = 0; i < dict->size; i++) {
        printf("Key: %s ", dict->items[i].key);
        switch (dict->items[i].type) {
            case 'i':
                printf(" %d\n",dict->items[i].value.i);
                break;
            case 'f':
                printf(" %f\n",dict->items[i].value.f);
                break;
            case 'c':
                printf(" %c\n",dict->items[i].value.c);
                break;
            case 'd':
                printf(" %lf\n",dict->items[i].value.d);
                break;
                
            default:
                break;
        }

    }
    printf("%d item was founded \n",i);
}


void free_dict(struct CustomDict* dict) {
    int i;
    for ( i = 0; i < dict->size; i++) {
        free(dict->items[i].key);
    }
    free(dict->items);
    free(dict);
}

#endif
