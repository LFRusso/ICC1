#include "search.h"


/*
*
*/
int getOffset(int query, insertion_info* inserts, int no_inserts){
    for(int i=0; i<no_inserts; i++){
        if(inserts[i].index == query){
            return inserts[i].position;
        }
    }
    return -1;
}

void answerQuery(char* regfile_name, int offset, register_field* fields, int no_fields){
    FILE* regfile = fopen(regfile_name, "r");
    fseek(regfile, offset, 0);
    
    char* char_data;
    int int_data;
    float float_data;
    double double_data;

    for(int i=0; i<no_fields; i++){
        printf("%s: ", fields[i].name);
        switch(fields[i].type){
            case 0:
                char_data = calloc(fields[i].size, sizeof(char));
                fread(char_data, fields[i].size, sizeof(char), regfile);
                printf("%s\n", char_data);
                free(char_data);
                break;

            case 1:
                fread(&int_data, 1, fields[i].size, regfile);
                printf("%d\n", int_data);
                break;

            case 2:
                fread(&float_data, 1, fields[i].size, regfile);
                printf("%.2f\n", float_data);
                break;

            case 3:
                fread(&double_data, 1, fields[i].size, regfile);
                printf("%.2f\n", double_data);
                break;
            
            default:
                break;
        }
    }
    printf("\n");

    fclose(regfile);
    return;
}

/*
*
*/
void search(char* query, char* regfile_name, register_field* fields, int no_fields){
    char* filename = getFilename(regfile_name);
    insertion_info* inserts = calloc(1, sizeof(register_field));
    int offset;
    int no_inserts=0;

    idxread(filename, &inserts, &no_inserts);
    
    offset = getOffset(atoi(query), inserts, no_inserts);
    if(offset != -1){
        answerQuery(regfile_name, offset, fields, no_fields);
    }
    
    free(inserts);
    free(filename);
    return;
}
