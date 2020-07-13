#include "index.h"

/*
*
*/
char* getFilename(char* regfile_name){
    char* index_name;
    char* temp = calloc(strlen(regfile_name)+1, sizeof(char));
    strcpy(temp, regfile_name);
    temp = strtok(temp, ".");
    
    index_name = calloc(strlen(temp)+strlen(".idx") + 1, sizeof(char));
    strcpy(index_name, temp);
    index_name = strncat(index_name, ".idx", strlen(".idx"));
    free(temp);
    return index_name;
}

/*
*
*/
void idxread(char* filename, insertion_info** inserts, int* no_inserts){
    int key, position;
    FILE* file = fopen(filename, "r");

    for(int i=*no_inserts; fread(&key, 1, sizeof(int), file) && fread(&position, 1, sizeof(int), file); i++){
        *inserts = realloc(*inserts, sizeof(insertion_info) * i + sizeof(insertion_info));
        (*inserts + i)->index = key;
        (*inserts + i)->position = position;
        *no_inserts += 1;
    }
    
    fclose(file);
    return;
}

void idxwrite(char* filename, insertion_info* inserts, int no_inserts){
    FILE* file = fopen(filename, "w+");
    
    for(int i=0; i<no_inserts; i++){
        fwrite(&inserts[i].index, 1, sizeof(int), file);
        fwrite(&inserts[i].position, 1, sizeof(int), file);
    }

    fclose(file);
    return;
}

int compare(const void *a, const void *b){
    insertion_info* insertionA = (insertion_info*)a;
    insertion_info* insertionB = (insertion_info*)b;

    return (insertionA->index - insertionB->index);
}

/*
*
*/
insertion_info* idx(char* regfile_name, insertion_info* inserts, int* no_inserts){
    char* filename;
    filename =getFilename(regfile_name);
    FILE* idx = fopen(filename, "rb");
    
    // Se o idx já está definido, primeiro carrego ele todo para a memória
    if(idx){
        fclose(idx);
        idxread(filename, &inserts, &(*no_inserts));
    }

    // Ordenando e escrevendo dados para o .idx
    qsort(inserts, *no_inserts, sizeof(insertion_info), compare);
    idxwrite(filename, inserts, *no_inserts);

    // Limpando inserts da memória
    *no_inserts = 0;
    free(inserts);
    inserts = calloc(1, sizeof(insertion_info));
    
    free(filename);
    return inserts;
}
