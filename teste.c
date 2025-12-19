#include <stdio.h>
#include <stdlib.h>
#include "Site.h"
#include "List.h"
//#include "Graph.h"

int main() {
    Graph *g = Graph_alloc();

    // Limpa a tela
    system("clear || cls");

    printf("\x1b[1;33mCarregando base de dados...\x1b[0m\n");
    graph_lerArquivo(g, "listSites.txt");

    // Cálculo da Pessoa 2
    Graph_calcularImportancia(g);

    printf("\n\x1b[1;34m==========================================\n");
    printf("        BUSCADOR GOOGLE DA UVA          \n");
    printf("==========================================\x1b[0m\n");
    
    char termo[30];
    printf("\nO que voce deseja encontrar? ");
    scanf("%29s", termo);

    // Busca da Pessoa 2
    List *resultados = buscarSitesPorPalavra(g, termo);

    // Ordenação e Exibição da Pessoa 3 (Você)
    ordenarSites(resultados);exibirResultados(resultados);

    // Limpeza
    List_free(resultados);
    return 0;
}
