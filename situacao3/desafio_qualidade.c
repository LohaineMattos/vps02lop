#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_PRODUTOS 100

typedef struct {
    int numero_de_serie;
    int resistencia;
    int durabilidade;
} Produto;

int main() {
    setlocale(LC_ALL, "");
    FILE *arquivo;
    Produto produtos[MAX_PRODUTOS];
    int i, n_produtos = 0;
    float media_resistencia, media_durabilidade;
    int max_resistencia, min_resistencia, max_durabilidade, min_durabilidade;
    int indice_max_resistencia, indice_min_resistencia, indice_max_durabilidade, indice_min_durabilidade;

    arquivo = fopen("parametros.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
    fscanf(arquivo, "%*s;%*s;%*s");
    while (fscanf(arquivo, "%d;%d;%d", &produtos[n_produtos].numero_de_serie, &produtos[n_produtos].resistencia, &produtos[n_produtos].durabilidade)!= EOF) {
        n_produtos++;
    }
    fclose(arquivo);

    media_resistencia = 0;
    media_durabilidade = 0;
    for (i = 0; i < n_produtos; i++) {
        media_resistencia += produtos[i].resistencia;
        media_durabilidade += produtos[i].durabilidade;
    }
    media_resistencia /= n_produtos;
    media_durabilidade /= n_produtos;


    max_resistencia = produtos[0].resistencia;
    min_resistencia = produtos[0].resistencia;
    max_durabilidade = produtos[0].durabilidade;
    min_durabilidade = produtos[0].durabilidade;
    indice_max_resistencia = 0;
    indice_min_resistencia = 0;
    indice_max_durabilidade = 0;
    indice_min_durabilidade = 0;
    for (i = 1; i < n_produtos; i++) {
        if (produtos[i].resistencia > max_resistencia) {
            max_resistencia = produtos[i].resistencia;
            indice_max_resistencia = i;
        }
        if (produtos[i].resistencia < min_resistencia) {
            min_resistencia = produtos[i].resistencia;
            indice_min_resistencia = i;
        }
        if (produtos[i].durabilidade > max_durabilidade) {
            max_durabilidade = produtos[i].durabilidade;
            indice_max_durabilidade = i;
        }
        if (produtos[i].durabilidade < min_durabilidade) {
            min_durabilidade = produtos[i].durabilidade;
            indice_min_durabilidade = i;
        }
    }
	
	FILE *md;
	md = fopen("qualidade.md", "w");

	fprintf(md,"# AN?LISE DE QUALIDADE\n");
    fprintf(md,"*M?dia de resist?ncia:* %.2f\n", media_resistencia);
    fprintf(md,"*M?dia de durabilidade:* %.2f\n", media_durabilidade);
    fprintf(md,"*Produto com maior resist?ncia:* %d (%d)\n", max_resistencia, produtos[indice_max_resistencia].numero_de_serie);
    fprintf(md,"*Produto com menor resist?ncia:* %d (%d)\n", min_resistencia, produtos[indice_min_resistencia].numero_de_serie);
    fprintf(md,"*Produto com maior durabilidade:* %d (%d)\n", max_durabilidade, produtos[indice_max_durabilidade].numero_de_serie);
    fprintf(md,"*Produto com menor durabilidade:* %d (%d)\n", min_durabilidade, produtos[indice_min_durabilidade].numero_de_serie);

    int acima_media_resistencia = 0, abaixo_media_resistencia = 0;
    int acima_media_durabilidade = 0, abaixo_media_durabilidade = 0;
    for (i = 0; i < n_produtos; i++) {
        if (produtos[i].resistencia > media_resistencia) {
            acima_media_resistencia++;
        } else {
            abaixo_media_resistencia++;
        }
        if (produtos[i].durabilidade > media_durabilidade) {
            acima_media_durabilidade++;
        } else {
            abaixo_media_durabilidade++;
        }
    }
    fprintf(md, "*Produtos acima da m?dia de resist?ncia:* %d\n", acima_media_resistencia);
    fprintf(md," *Produtos abaixo da m?dia de resist?ncia:* %d\n", abaixo_media_resistencia);
    fprintf(md, "*Produtos acima da m?dia de durabilidade:* %d\n", acima_media_durabilidade);
    fprintf(md,"*Produtos abaixo da m?dia de durabilidade:* %d\n", abaixo_media_durabilidade);
    
    printf("Arquivo MD alterado com sucesso.\n");
    return 0;
}
