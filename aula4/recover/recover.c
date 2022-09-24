#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define N 64

// definindo tipos a serem usados
typedef uint8_t BYTE;
typedef char *string;

int main(int argc, char *argv[])
{

    // verificando se é possivel abrir o cartao sd indicado
    BYTE cluster[N];
    if (argc != 2)
    {
        printf("use ./recover infile\n");
        return 1;
    }
    FILE *sd = fopen(argv[1], "r");
    if (sd == NULL)
    {
        printf("not found...\n");
        return 2;
    }

    // lendo os dados
    int count = 0;
    FILE *img;
    while (fread(cluster, sizeof(BYTE), N, sd) == N)
    {
        // escrevendo dados das fotos
        if (cluster[0] != 0xFF || cluster[1] != 0xD8 || cluster[2] != 0xFF || (cluster[3] & 0xE0) != 0xE0)
        {
            if (count != 0)
            {
                fwrite(cluster, sizeof(BYTE), N, img);
            }
        }
        else
        {
            // criando arquivo .jpg e escrevendo cabeçalho
            if (count != 0)
            {
                fclose(img);
            }
            string filename = malloc(8);
            sprintf(filename, "%03d.jpg", count);
            img = fopen(filename, "w");
            fwrite(cluster, sizeof(BYTE), N, img);
            free(filename);
            count++;
        }
    }

    // fechando arquivo
    fclose(sd);
    return 0;
}