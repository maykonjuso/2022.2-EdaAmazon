#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Substitui quebra de linha pelo caractere nulo
void remover(char *str)
{
    int comprimento = strlen(str);
    if (str[comprimento - 1] == '\n')
    {
        str[comprimento - 1] = '\0';
    }
}

// Função para contar quantidade de linhas do arquivo csv
int contarLinhas(char *nome)
{
    // Criando ponteiro para ler o arquivo
    FILE *fp = fopen(nome, "r");

    // Avisar caso ocorra algum erro na abertura do arquivo
    if (fp == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
        return 1;
    }

    char c;
    int count = 0;

    // Percorre o arquivo até encontrar o caractere EOF
    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        // Incrementa o contador caso o seja uma quebra de linha
        if (c == '\n')
            count = count + 1;
    }

    // Fecha o ponteiro
    fclose(fp);

    // Retorna a quantidade de linhas
    return count;
}

int main()
{
    // Inicia o contador
    clock_t start_time = clock();

    // Declara uma struct com duas linhas (valor e categoria)
    typedef struct
    {
        double valor;
        char categoria[100];
    } VENDA;

    // Chama a função contarLinhas para salvar a quantidade de linhas do arquivo na variável tamLinhas
    int tamLinhas = contarLinhas("dadosAmostra.csv");

    // Abertura dos arquivos
    FILE *fp, *fsaida;
    fp = fopen("dadosAmostra.csv", "r");
    fsaida = fopen("dadosSaidaAmostra.csv", "w");

    if (fp == NULL)
    {
        // Condição caso não seja possível abrir o arquivo
        printf("Não foi possível abrir o arquivo\n");
        return 1;
    }

    // Alocando memória dinamicamente para o vetor de vendas
    VENDA *vendas = (VENDA *)malloc(tamLinhas * sizeof(VENDA));

    // Lê o arquivo linha por linha
    char linha[100];
    int tam = 0;

    // Preencher struct vendas com os dados do csv
    while (fgets(linha, sizeof(linha), fp))
    {
        // Divide a linha em tokens usando ";" como delimitador
        char *valor_str = strtok(linha, ";");
        char *categoria = strtok(NULL, ";");

        remover(categoria);

        strcpy(vendas[tam].categoria, categoria);

        double valorDouble = atof(valor_str);
        vendas[tam].valor = valorDouble;
        tam++;
    }

    // Usando selectionSort para ordenar arquivos

    // Percorre toda extensão do vetor
    for (int i = 0; i < tamLinhas - 1; i++)
    {
        // Armazena uma posição i do vetor em min
        int min = i;

        // O laço será percorrido a partir do proximo valor de i
        for (int j = i + 1; j < tamLinhas; j++)
        {
            // Essa linha compara a posição J com min, e atualiza o valor
            if (vendas[j].valor < vendas[min].valor)
            {
                min = j;
            }
        }
        // armazena a posição atual temporariamente
        VENDA tmp = vendas[i];
        // Adiciona a posição menor na posição do vetor
        vendas[i] = vendas[min];
        // Adiciona a variavel temporaria que havia o valor menor
        vendas[min] = tmp;
    }

    for (int i = tamLinhas - 1; i >= 0; i--)
    {
        // Preenche o arquivo de saída com o vetor ordenado
        fprintf(fsaida, "%.2lf %s\n", vendas[i].valor, vendas[i].categoria);

        // Printa no console - temporário (comentado para não alterar o tempo de processamento)
        printf("%.2lf %s\n", vendas[i].valor, vendas[i].categoria);
    }

    // Encerra arquivos e desaloca a memória alocada em malloc
    fclose(fp);
    fclose(fsaida);
    free(vendas);

    // Final da contagem
    clock_t end_time = clock();

    // Calculo do tempo
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Exibe o tempo de processamento
    printf("Tempo de processamento: %.2f segundos", elapsed_time);

    return 0;
}