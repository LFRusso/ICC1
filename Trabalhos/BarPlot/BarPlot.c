#include <stdio.h>
#include <string.h>

int main(){
    int bars;
    int data_size;
    int input;

    scanf("%d %d", &bars, &data_size);
    
    int dataset[bars];
    memset(dataset, 0, bars * sizeof(int));

    for(int i =0; i<data_size; i++){
        scanf("%d", &input);
        dataset[input]++;
    }
    for (int i=0; i<bars; i++){
        printf("%d", i);
        printf(" - ");
        for(int j=0; j<dataset[i]; j++){
            printf("#");
        }
        printf("\n");
    }

    return 0;
}
