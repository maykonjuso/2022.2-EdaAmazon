#include <stdio.h>
#include <string.h>stdlib
#include <stdlib.h>

void remover(char *str)
{
    int comprimento = strlen(str);
    if (str[comprimento - 1] == '\n')
    {
        str[comprimento - 1] = '\0';
    }
}

int contarLinhas(char *nome)
{
    FILE *fp = fopen(nome, "r");
    if (fp == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
        return 1;
    }

    char c;
    int count = 0;

    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    }

    fclose(fp);
    return count;
}

int main(int argc, char **argv)
{
    typedef struct
    {
        char categoria[100];
        double valor;
    } venda;

    int tamLinhas = contarLinhas("DADOS.csv");
    // Abrir o arquivo .csv

    FILE *fp = fopen("DADOS.csv", "r");

    if (fp == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
        return 1;
    }

    // Lê o arquivo linha por linha
    venda vendas[tamLinhas];
    char linha[100];
    int tam = 0;

    while (fgets(linha, sizeof(linha), fp))
    {
        char *categoria = strtok(linha, ";");
        char *valor_str = strtok(NULL, ";");
        // Divide a linha em tokens usando ";" como delimitador
        remover(valor_str);

        strcpy(vendas[tam].categoria, categoria);

        double valorDouble = atof(valor_str);
        vendas[tam].valor = valorDouble;
        tam++;
    }

    //SelectionSort
    for (int i = 0; i < tamLinhas - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < tamLinhas; j++)
        {
            if ((strcmp(vendas[j].categoria, vendas[min].categoria) < 0) || (strcmp(vendas[j].categoria, vendas[min].categoria) == 0 && vendas[j].valor < vendas[min].valor))
            {
                min = j;
            }
        }
        venda tmp = vendas[i];
        vendas[i] = vendas[min];
        vendas[min] = tmp;
    }

    for (int i = tamLinhas - 1; i >= 0; i--)
    {
        printf("%s %.2lf\n", vendas[i].categoria, vendas[i].valor);
    }
    fclose(fp);
    return 0;
}