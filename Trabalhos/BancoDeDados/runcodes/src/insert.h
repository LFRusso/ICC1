// Recebe dados do insert do usuário e cadastra no .reg
#ifndef _INSERT_H_
#define _INSERT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builder.h"
#include "inputhandler.h"

insertion_info insert(char* regfile_name, char* insertion, register_field* fields, int no_fields);

#endif
