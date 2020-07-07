#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <locale.h>

struct file_header{
    char* signature;        // (2 bytes)                                   
    int file_size;          // (4 bytes) Size of the file in bytes
    int reserved;           // (4 bytes) must be 0
    int displacement;       // (4 bytes) must be 14+40+4*(4*NumberofColors) = 1078  (number of colors is 256)
};

struct bitmap_header{
    int size;               // (4 bytes)
    int img_width;          // (4 bytes)
    int img_height;         // (4 bytes)
    short planes;           // (2 bytes) must be 1
    short bit_per_pixel;    // (2 bytes) will be 8 in our case
    int compression;        // (4 bytes) no compression = 0
    int img_size;           // (4 bytes) equal to file_size
    int pixel_meter_h;      // (4 bytes)
    int pixel_meter_v;      // (4 bytes)
    int n_colors;           // (4 bytes)
    int n_used_colors;      // (4 bytes)
};

struct palette{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char reserved;
};

// Recebe uma string e um padrão e checa ocorrência
int checkPattern(char* str, char* pattern){
    regex_t regex;
    int status;

    regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB);
    status = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    
    if(status != 0){
        return 0;
    }
    return 1;
}

// Função readline para obter entradas
char *readline(FILE *input){
    char *str = calloc(1, sizeof(char));
    char ch;

    ch = getc(input);
    while (ch != '\n' && ch != '\r' && ch != EOF)
    {
        str = realloc(str, (strlen(str)+1)*sizeof(char) + sizeof(char));
        strncat(str, &ch, 1);
        ch = getc(input);
    }
    // Finalizando string
    strncat(str, "\0", 1);

    return str;
}

// Lendo cabeçalho do arquivo
struct file_header getFileHeader(FILE* file){
    struct file_header file_header;
    file_header.signature = calloc(3, sizeof(char));
    fread(file_header.signature, sizeof(char), 2, file);
    fread(&file_header.file_size, sizeof(int), 1, file);
    fread(&file_header.reserved, sizeof(int), 1, file);
    fread(&file_header.displacement, sizeof(int), 1, file);

    return file_header;
}

// Lendo cabeçalho do bitmap
struct bitmap_header getBitmapHeader(FILE* file){
    struct bitmap_header bitmap_header;
    fread(&bitmap_header.size, sizeof(int), 1, file);
    fread(&bitmap_header.img_width, sizeof(int), 1, file);
    fread(&bitmap_header.img_height, sizeof(int), 1, file);
    fread(&bitmap_header.planes, sizeof(short), 1, file);
    fread(&bitmap_header.bit_per_pixel, sizeof(short), 1, file);
    fread(&bitmap_header.compression, sizeof(int), 1, file);
    fread(&bitmap_header.img_size, sizeof(int), 1, file);
    fread(&bitmap_header.pixel_meter_h, sizeof(int), 1, file);
    fread(&bitmap_header.pixel_meter_v, sizeof(int), 1, file);
    fread(&bitmap_header.n_colors, sizeof(int), 1, file);
    fread(&bitmap_header.n_used_colors, sizeof(int), 1, file);
   
    return bitmap_header;
}

// Lendo paleta de cores
struct palette* getPalette(FILE* img){
    struct palette* palette = calloc(256, sizeof(struct palette));
    for(int i=0; i<256; i++){
        fread(&palette[i].B, sizeof(char), 1, img);
        fread(&palette[i].G, sizeof(char), 1, img);
        fread(&palette[i].R, sizeof(char), 1, img);
        fread(&palette[i].reserved, sizeof(char), 1, img);
    }

    return palette;
}


// Lendo área de dados da imagem
unsigned char** getImgMatrix(FILE* file, int width, int height){
    unsigned char** img_matrix = calloc(height, sizeof(char*));
    // Atualizando largura a ser lida levando em conta o lixo
    width = width % 4 ? width + 4 -  width % 4 : width;

    for(int i=height-1; i>=0; i--){
        img_matrix[i] = calloc(width, sizeof(char));
        for(int j=0; j<width; j++){
            fread(&img_matrix[i][j], sizeof(char), 1, file);
        }
    }

    return img_matrix;
}

// Aplica o filtro desejado na paleta de cores da imagem
struct palette* applyFilter(struct palette* palette_old, int mode){
    struct palette* palette_new = calloc(256, sizeof(struct palette));
    
    switch(mode){
        case 1:
            // Invertendo cores
            for(int i=0; i<256; i++){
                palette_new[i].R = 255 - palette_old[i].R;
                palette_new[i].G = 255 - palette_old[i].G;
                palette_new[i].B = 255 - palette_old[i].B;
            }
            break;

        case 2:
            // Converte cores para escala de cinza
            for(int new_color, i=0; i<256; i++){
                new_color = (int) (palette_old[i].R + palette_old[i].G + palette_old[i].B)/3;
                palette_new[i].R = (unsigned char)new_color;
                palette_new[i].G = (unsigned char)new_color;
                palette_new[i].B = (unsigned char)new_color;
            }
            break;
    }

    return palette_new;
}

// Salvando a imagem em um arquivo
void saveImg(char* img_name, struct file_header file_header, struct bitmap_header bitmap_header, struct palette* palette, unsigned char** img_matrix){
    FILE* file = fopen(img_name, "w+");
    int width, height;
    height = bitmap_header.img_height;
    width = bitmap_header.img_width % 4 ? bitmap_header.img_width + 4 - bitmap_header.img_width % 4 : bitmap_header.img_width;

    // Salvando cabeçalho do arquivo
    fwrite(file_header.signature, sizeof(char), 2, file);
    fwrite(&file_header.file_size, sizeof(int), 1, file);
    fwrite(&file_header.reserved, sizeof(int), 1, file);
    fwrite(&file_header.displacement, sizeof(int), 1, file);


    // Salvando cabeçalho do mapa de bits
    fwrite(&bitmap_header.size, sizeof(int), 1, file);
    fwrite(&bitmap_header.img_width, sizeof(int), 1, file);
    fwrite(&bitmap_header.img_height, sizeof(int), 1, file);
    fwrite(&bitmap_header.planes, sizeof(short), 1, file);
    fwrite(&bitmap_header.bit_per_pixel, sizeof(short), 1, file);
    fwrite(&bitmap_header.compression, sizeof(int), 1, file);
    fwrite(&bitmap_header.img_size, sizeof(int), 1, file);
    fwrite(&bitmap_header.pixel_meter_h, sizeof(int), 1, file);
    fwrite(&bitmap_header.pixel_meter_v, sizeof(int), 1, file);
    fwrite(&bitmap_header.n_colors, sizeof(int), 1, file);
    fwrite(&bitmap_header.n_used_colors, sizeof(int), 1, file);
   
    // Salvando paleta de cores
    for(int i=0; i<256; i++){
        fwrite(&palette[i].B, sizeof(char), 1, file);
        fwrite(&palette[i].G, sizeof(char), 1, file);
        fwrite(&palette[i].R, sizeof(char), 1, file);
        fwrite(&palette[i].reserved, sizeof(char), 1, file);
    }
    
    // Salvando matriz das cores
    for(int i=height-1; i>=0; i--){
        for(int j=0; j<width; j++){
            fwrite(&img_matrix[i][j], sizeof(char), 1, file);
        }
    }

    fclose(file);
    printf("%s\n", img_name);
}

int main(){
    char* img_name;
    FILE* img;
    int mode;
    unsigned char** img_matrix;
    struct file_header file_header;
    struct bitmap_header bitmap_header;
    struct palette* palette_old;
    struct palette* palette_new;

    // Obtendo nome do arquivo e modo do filto
    img_name = readline(stdin);
    scanf("%d", &mode);

    // Checando se arquivo está no formato apropriado
    if(!checkPattern(img_name, ".bmp$")){
        printf("Arquivo nao eh do formato BMP\n");
        exit(1);
    }
    
    img = fopen(img_name, "r");
    if(!img){
        printf("Erro no arquivo\n");
        free(img_name);
        exit(1);
    }       
    
    file_header = getFileHeader(img);
    // Checando se asssinatura condiz com o formato BMP
    if(strcmp(file_header.signature, "BM")){
        printf("Arquivo nao eh do formato BMP\n");
        exit(1);
    }
    bitmap_header = getBitmapHeader(img);
    palette_old = getPalette(img);
    img_matrix = getImgMatrix(img, bitmap_header.img_width, bitmap_header.img_height);
    
    palette_new = applyFilter(palette_old, mode);

    
    switch(mode){
        case 1:
            img_name = realloc(img_name, strlen(img_name) + strlen("Negativo") + sizeof(char));
            img_name = strtok(img_name, ".");
            img_name = strcat(img_name, "Negativo.bmp\0");
            break;

        case 2:
            img_name = realloc(img_name, strlen(img_name) + strlen("PretoBranco") + sizeof(char));
            img_name = strtok(img_name, ".");
            img_name = strcat(img_name, "PretoBranco.bmp\0");
            break;
    }
    

    // Imprimindo cabeçalho do arquivo
    printf("CABECALHO:\n");
    printf("Iniciais: %s\n", file_header.signature);
    printf("Tamanho do arquivo: %d\n", file_header.file_size);    
    printf("Reservado: %d\n", file_header.reserved);    
    printf("Deslocamento, em bytes, para o inicio da area de dados: %d\n", file_header.displacement);

    // Imprimindo cameçalho do bitmap
    printf("Tamanho em bytes do segundo cabecalho: %d\n", bitmap_header.size);
    printf("Resolucao: %d x %d\n", bitmap_header.img_width, bitmap_header.img_height);
    printf("Numero de planos: %d\n", bitmap_header.planes);
    printf("Bits por pixel: %d\n", bitmap_header.bit_per_pixel);
    printf("Compressao usada: %d\n", bitmap_header.compression);
    printf("Tamanho imagem: %d\n", bitmap_header.img_size);
    printf("Resolucao horizontal: %d pixel por metro\n", bitmap_header.pixel_meter_h);
    printf("Resolucao Vertical: %d pixel por metro\n", bitmap_header.pixel_meter_v);
    printf("Numero de cores usadas: %d\n", bitmap_header.n_colors);
    printf("Numero de cores importantes: %d\n", bitmap_header.n_used_colors);

    // Imprimindo paleta original
    printf("PALETA ORIGINAL:\n");
    for(int i=0; i<256; i++){
        printf("Paleta[%d]: R:%d G:%d B:%d\n", i, palette_old[i].R, palette_old[i].G, palette_old[i].B);
    } 
    
    // Imprimindo paleta após aplicação do filtro
    printf("PALETA NOVA:\n");
    for(int i=0; i<256; i++){
        printf("Paleta[%d]: R:%d G:%d B:%d\n", i, palette_new[i].R, palette_new[i].G, palette_new[i].B);
    } 
    
    long long int sum;
    for(int i=0; i<bitmap_header.img_height; i++){
        sum = 0;
        for(int j=0; j<bitmap_header.img_width; j++){
            sum += img_matrix[i][j];
        }
        sum = bitmap_header.img_width % 4 ? sum - (4 - bitmap_header.img_width % 4) : sum;
        printf("Soma linha %d: %lld\n", i, sum);
    }  

    // Salvando imagem com o filtro
    saveImg(img_name, file_header, bitmap_header, palette_new, img_matrix);

    fclose(img); 
    // Liberando memória
    for(int i=0; i<bitmap_header.img_height; i++){
        free(img_matrix[i]);
    }  
    free(img_matrix);
    free(palette_old);
    free(palette_new);
    free(file_header.signature);
    free(img_name);
    return 0;
}
