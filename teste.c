#include <stdio.h>
#include "Site.h"

int main(){
    Graph *g = Graph_alloc();

    graph_lerArquivo(g, "listSites.txt");

    Graph_calcularImportancia(g);

    printf("\n==== Estrutura Grafo ===\n");
    Graph_print(g);

    imprimirImportancia(g);
}