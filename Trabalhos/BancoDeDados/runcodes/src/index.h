// Cria o arquivo index
#ifndef _INDEX_H_
#define _INDEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builder.h"

char* getFilename(char* regfile_name);

void idxread(char* filename, insertion_info** inserts, int* no_inserts);

insertion_info* idx(char* regfile_name, insertion_info* inserts, int* no_inserts);

#endif
