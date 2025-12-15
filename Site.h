#include "Graph.h"

typedef struct{
    char nome[50];
    char palavras[15][30];
    int qtdPalavras;
    int importancia;
}Site;

void  Graph_inserSite(Graph *g, Site *site); 
Site *Site_create(char *nome, char palavras[][30], int qtdPalavras);
void  Site_print(Site *s);
int   Site_cmp(void *a, void *b);
void  Graph_insertLink(Graph *g, Site *origem, Site *destino, int p);
void  Graph_calcularImportancia(Graph *g);
void  graph_lerArquivo(Graph *g, const char *nomeArquivo);