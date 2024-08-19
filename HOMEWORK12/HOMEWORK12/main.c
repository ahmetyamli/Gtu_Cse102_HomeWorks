
#include <stdio.h>
#include <string.h>
#include "customDict.h"
#define File_Path "data.csv"





int main(void) {
    struct CustomDict* dict = create_dict();
    int totalsize ;
    int file_info[100];
    
    
    
    read_csv_find_size(file_info, File_Path, &totalsize);
    read_csv(file_info, dict, File_Path,totalsize);
    print_dict(dict);
    union Value* search_result = search_item(dict, "count2");
    if (search_result) {
            printf("Found value for 'count2': %d\n", search_result->i);
        } else {
            printf("Key not found\n");
        }
    printf("------------\n");
    sort_dict(dict);
    print_dict(dict);
    
    delete_item(dict, "size3");
    printf("------------\n");
    print_dict(dict);
    Value val1;
    val1.i = 111;
    set_value(dict, "size2", &val1);
    print_dict(dict);
    
    return 0;
}
