#include <stdio.h>
#include "Site.h"
#include "List.h"

// Função auxiliar para imprimir a lista de resultados da busca
void print_site_callback(void *item) {
    Site *s = (Site*)item;
    printf("- %s (Imp: %d)\n", s->nome, s->importancia);
}

int main(){
    Graph *g = Graph_alloc();

    printf("1. Carregando Grafo...\n");
    graph_lerArquivo(g, "listSites.txt");

    printf("2. Calculando Importancia...\n");
    Graph_calcularImportancia(g); 

    imprimirImportancia(g);

    printf("\n3. Testando Busca por Palavra 'computador'...\n");
    List *resultados = buscarSitesPorPalavra(g, "computador");
    
    printf("Sites encontrados com 'computador': %d\n", List_getLength(resultados));
    List_print(resultados, print_site_callback);

    List_free(resultados);
    Graph_free(g);
    return 0;
}
