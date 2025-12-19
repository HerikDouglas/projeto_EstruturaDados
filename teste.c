#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Biblioteca para a função sleep no Linux
//#include <windows.h> Se for usar em um computador com Windows (Code::Blocks ou Dev-C++), e use Sleep(2000)
#include "Site.h"
// #include "List.h"
//#include "Graph.h"

int main() {
    Graph *g = Graph_alloc();

    system("clear || cls");

    printf("\x1b[1;33mCarregando base de dados...\x1b[0m\n");
    sleep(2);
    graph_lerArquivo(g, "listSites.txt");
    printf("\x1b[1;32mConcluido!\x1b[0m\n");
    sleep(1);

    Graph_calcularImportancia(g);

    printf("\n\x1b[1;34m==========================================\n");
    printf("        BUSCADOR GOOGLE DA UVA          \n");
    printf("==========================================\x1b[0m\n");
    
    char termo[30];
    printf("\nO que você deseja encontrar? ");
    scanf("%29s", termo);

    printf("\n\x1b[1;36mBuscando por '%s' no servidor...\x1b[0m\n", termo);
    sleep(2);

    List *resultados = buscarSitesPorPalavra(g, termo);
    ordenarSites(resultados);
    exibirResultados(resultados);

    List_free(resultados);
    return 0;
}
