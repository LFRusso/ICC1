// Recebe e trata entradas do usuário
#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builder.h"
#include "insert.h"
#include "index.h"
#include "search.h"

void handleInput(char* regfile_name, register_field* fields, int no_fields);

#endif
