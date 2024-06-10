#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    int matricula;
    char funcionario[50];
    char data[12];
    char origem[50];
    char destino[50];
    int distancia;
    float preco;
    float total;
} Viagem;

Viagem viagens[50];
int totalViagens = 0, i;

void carregaDados()
{
    FILE *arq;
    char linha[100];
    arq = fopen("viagens.csv", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    else
    {
        fgets(linha, 100, arq); // Ignorar a primeira linha
        while (fgets(linha, 100, arq) != NULL)
        {
            viagens[totalViagens].matricula = atoi(strtok(linha, ";"));
            strcpy(viagens[totalViagens].funcionario, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].data, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].origem, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].destino, strtok(NULL, ";"));
            viagens[totalViagens].distancia = atoi(strtok(NULL, ";"));
            viagens[totalViagens].preco = atof(strtok(NULL, ";"));
            viagens[totalViagens].total = 0; // Inicialize o total como zero
            totalViagens++;
        }
    }
    fclose(arq);
}

float calcularReembolso(float preco, int distancia)
{
    // Calcula o valor total do reembolso
    return (preco * distancia) / 3.0;
}

void calcularTotais()
{
    for(i = 0; i < totalViagens; i++)
    {
        // Calcula o total do reembolso para cada viagem
        viagens[i].total = calcularReembolso(viagens[i].preco, viagens[i].distancia);
    }
}

void mostrarDados()
{
    printf("Viagens ACME:\n");
    printf("Matricula\tFuncionario\tData\tOrigem\tDestino\tDist�ncia\tPre�o\tTotal\n");
    for(i = 0; i < totalViagens; i++)
    {
        printf("%d\t%s\t%s\t%s\t%s\t%d\t%.2f\t%.2f\n", viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem, viagens[i].destino, viagens[i].distancia, viagens[i].preco, viagens[i].total);
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    calcularTotais(); // Calcular os totais ap�s carregar os dados
    mostrarDados();
    return 0;
}

