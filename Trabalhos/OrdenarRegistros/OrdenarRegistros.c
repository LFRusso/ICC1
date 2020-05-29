#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// OBS: A COMENTAR

struct registro
{
    char *name;
    int year;
};

// Leitura de linha do arquivo
char *readLine(FILE *input)
{
    char *str = (char *)malloc(sizeof(char));
    char ch;

    ch = getc(input);
    while (ch != '\n' && ch != EOF)
    {
        // Condição feita por conta do carriage return em algumas linhas dos arquivos de entrada
        if (ch != 13)
        {
            str = realloc(str, strlen(str) * sizeof(char) + sizeof(char) + 1);
            strncat(str, &ch, 1);
        }
        ch = getc(input);
    }
    // Finalizando string
    strncat(str, "\0", 1);

    return str;
}

char *getName(char *str)
{
    char *name;
    int idx = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        idx = str[i] == 32 && i != strlen(str) - 1 ? i : idx;
    }

    name = (char *)malloc(sizeof(char) * (idx) + 1);
    for (int i = 0; i < idx; i++)
    {
        name[i] = str[i];
    }
    name[idx] = '\0';

    return name;
}

int toInt(char *str)
{
    int int_str = 0;
    int signal;
    int no_order = strlen(str);

    signal = str[0] == '-' ? -1 : 1;

    if (signal == 1)
    {
        for (int i = 0; i < no_order; i++)
        {
            // Subtraindo valor na tabela ascii do caractere '1'
            int_str += (str[i] - 48) * pow(10, no_order - i - 1);
        }
    }
    else
    {
        for (int i = 1; i < no_order; i++)
        {
            // Subtraindo valor na tabela ascii do caractere '1'
            int_str += (str[i] - 48) * pow(10, no_order - i - 1);
        }
    }

    return signal * int_str;
}

int getYear(char *str)
{
    char *year;
    int int_year;
    int idx = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        idx = str[i] == 32 && i != strlen(str) - 1 ? i : idx;
    }

    year = (char *)malloc(sizeof(char) * (strlen(str) - idx) + 1);
    for (int i = idx + 1; i <= strlen(str) && str[i] != 32; i++)
    {
        year[i - (idx + 1)] = str[i];
    }
    year[strlen(str) - idx] = '\0';

    int_year = toInt(year);

    return int_year;
}

int compare_words(const void *a, const void *b)
{
    struct registro *registroA = (struct registro *)a;
    struct registro *registroB = (struct registro *)b;

    return -strcmp(registroB->name, registroA->name);
}

int compare_int(const void *a, const void *b)
{
    struct registro *registroA = (struct registro *)a;
    struct registro *registroB = (struct registro *)b;

    return -(registroB->year - registroA->year);
}

void sort(struct registro *registros, int mode, int no_elements)
{
    switch (mode)
    {
    case 1:
        qsort(registros, no_elements, sizeof(struct registro), compare_words);
        break;

    case 2:
        qsort(registros, no_elements, sizeof(struct registro), compare_int);
        break;

    default:
        break;
    }

    return;
}

int main()
{
    struct registro *registros = (struct registro *)malloc(10000 * sizeof(struct registro));
    char *str = (char *)malloc(sizeof(char));
    int mode;
    int i = 0;

    scanf("%d", &mode);
    getc(stdin);

    str = readLine(stdin);
    for (; str[0] != 0; i++)
    {
        registros[i].name = getName(str);
        registros[i].year = getYear(str);

        str = readLine(stdin);
    }
    sort(registros, mode, i);

    for (int j = 0; j < i; j++)
    {
        printf("%d\t%s\n", registros[j].year, registros[j].name);
    }

    free(str);
    free(registros);
    return 0;
}
