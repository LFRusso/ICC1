#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builder.h"
#include "index.h"

void search(char* query, char* regfile_name, register_field* fields, int no_fields);

#endif
