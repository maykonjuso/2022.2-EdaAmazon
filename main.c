#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
        char categoria[50];
        double valor;
    } venda;

    int tamLinhas = contarLinhas("dadosAmostra.csv");

    // Abrir o arquivo .csv

    FILE *fp, *fsaida;
    fp = fopen("dadosAmostra.csv", "r");
    fsaida = fopen("dadosSaidaAmostra.csv", "w");

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
        char *valor_str = strtok(linha, ";");
        char *categoria = strtok(NULL, ";");
        // Divide a linha em tokens usando ";" como delimitador
        remover(categoria);

        strcpy(vendas[tam].categoria, categoria);

        double valorDouble = atof(valor_str);
        vendas[tam].valor = valorDouble;
        tam++;
    }

    // SelectionSort
    for (int i = 0; i < tamLinhas - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < tamLinhas; j++)
        {
            if (vendas[j].valor < vendas[min].valor)
            {
                min = j;
            }
        }
        venda tmp = vendas[i];
        vendas[i] = vendas[min];
        vendas[min] = tmp;
    }

    // inicio da contagem
    clock_t start_time = clock();

    for (int i = tamLinhas - 1; i >= 0; i--)
    {
        // gera e preenche o arquivo de saída
        fprintf(fsaida, "%.2lf %s\n", vendas[i].valor, vendas[i].categoria);

        // printa no console - temporário
        printf("%.2lf %s\n", vendas[i].valor, vendas[i].categoria);
    }

    fclose(fp);
    fclose(fsaida);

    // final da contagem
    clock_t end_time = clock();
    // calculo do tempo
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Tempo de processamento: %.2f segundos", elapsed_time);

    return 0;
}
