#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Site.h"
#include "List.h"

// Cores ANSI para o terminal
#define RESET   "\x1b[0m"
#define BOLD    "\x1b[1m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define CYAN    "\x1b[36m"
#define RED     "\x1b[31m"

Site *Site_alloc(char *nome, char palavras[][30], int qtdPalavras){
    Site *s = malloc(sizeof(Site));
    if(s == NULL){
        printf("Erro ao alocar memória para Site.\n");
        exit(1);
    }

    //copiar nome do site
    strncpy(s->nome, nome, 50);

    //copiar palavras chave do site
    s->qtdPalavras = qtdPalavras;
    for(int i = 0; i < qtdPalavras; i++){
        strncpy(s->palavras[i], palavras[i], 30);
    }

    //importancia
    s->importancia = 0;

    return s;
}

void Graph_insertSite(Graph *g, Site *site){
    if(g == NULL || site == NULL){
        printf("Erro: grafo ou site inválido.\n");;
        return;
    }

    Graph_insertVertex(g, (void*)site);
}

void Site_print(Site *s){
    printf("Site: %s\n", s->nome);
    printf("Importância: %d\n", s->importancia);
    printf("Palavras-chave (%d): ", s->qtdPalavras);

    for(int i = 0; i < s->qtdPalavras; i++){
        printf("%s ", s->palavras[i]);
    }

    printf("\n");
}

//função de comparação para localizar um site no grafo
int Site_cmp(void *a, void *b){
    Site *s1 = (Site*) a;
    Site *s2 = (Site*) b;

    return strcmp(s1->nome, s2->nome);
}

void Graph_insertLink(Graph *g, Site *origem, Site *destino, int peso){
    if(g == NULL || origem == NULL || destino == NULL){
        printf("Erro: parâmetros inválidos.\n");
        return;
    }

    Vertex *v1 = Graph_findByValue(g, origem, Site_cmp);
    Vertex *v2 = Graph_findByValue(g, destino, Site_cmp);

    if(v1 == NULL || v2 == NULL){
        printf("Erro: site de origem ou destino não encontrado no grafo.");
        return;
    }

    int *p = malloc(sizeof(int));
    *p = peso;
    Graph_insertEdge(g, v1->label, v2->label, p);
}

void Graph_calcularImportancia(Graph *g){
    if (!g) return;

    //zera a importância de todos os sites primeiro
    Vertex *v = g->first;
    while (v) {
        Site *s = (Site*) v->value;
        s->importancia = 0;
        v = v->next;
    }

    //percorre o grafo somando pesos nos destinos
    v = g->first;
    while (v) {
        //para cada vértice, percorre suas arestas (links de saída)
        Edge *e = v->first;
        while (e) {
            //e->head é o vértice de destino
            //e->value é o peso
            
            Vertex *destino = e->head;
            int *peso = (int*) e->value;

            if (destino && peso) {
                Site *siteDestino = (Site*) destino->value;
                
                //soma dos pesos das arestas que CHEGAM
                siteDestino->importancia += *peso;
            }
            e = e->next;
        }
        v = v->next;
    }

}

void imprimirImportancia(Graph *g) {
    Vertex *v = g->first;

    printf("\n=== Importância dos Sites ===\n");
    while (v) {
        Site *s = (Site*) v->value;
        printf("%s -> importância = %d\n", s->nome, s->importancia);
        v = v->next;
    }
}

void graph_lerArquivo(Graph *g, const char *nomeArquivo){
    FILE *f = fopen(nomeArquivo, "r");
    if(f == NULL){
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    int qtdSites;
    fscanf(f, "%d", &qtdSites);

    Site *sites[qtdSites];

    for(int i = 0; i < qtdSites; i++){

        char nome[50];
        int qtdpalavras;
        char palavras[15][30];

        fscanf(f, "%s %d", nome, &qtdpalavras);

        for (int j = 0; j < qtdpalavras; j++) {
            fscanf(f, "%29s", palavras[j]);
        }

        sites[i] = Site_alloc(nome, palavras, qtdpalavras);
        Graph_insertSite(g, sites[i]);
    }

    //leitura de arestas
    int qtdArestas;
    fscanf(f, "%d", &qtdArestas);

    for(int i = 0; i < qtdArestas; i++){

        char origem[50], destino[50];
        int peso;
        fscanf(f, "%s %s %d", origem, destino, &peso);

        Site sOrigemTemp, sDestinoTemp;
        strcpy(sOrigemTemp.nome, origem);
        strcpy(sDestinoTemp.nome, destino);

        Vertex *vOrigem = Graph_findByValue(g, &sOrigemTemp, Site_cmp);
        Vertex *vDestino = Graph_findByValue(g, &sDestinoTemp, Site_cmp);

        if(vOrigem && vDestino){
            int *p = malloc(sizeof(int));
            *p = peso;

            Graph_insertEdge(g, vOrigem->label, vDestino->label, p);
        }
    }

    fclose(f);
}

List *buscarSitesPorPalavra(Graph *g, char *termo) {
    List *resultados = List_alloc();
    
    if (!g || !termo) return resultados;

    //acessando a estrutura interna do grafo
    Vertex *v = g->first; 

    while (v) {
        Site *s = (Site*) v->value;
        
        //verifica se a palavra está na lista de palavras-chave do site
        for (int i = 0; i < s->qtdPalavras; i++) {
            if (strcmp(s->palavras[i], termo) == 0) {
                List_insert(resultados, s);
                break; //se palavra encontrada, não precisa verificar as outras deste site
            }
        }
        
        v = v->next;
    }

    return resultados;
}

// --- ORDENAÇÃO E EXIBIÇÃO COLORIDA ---

// Definição das estruturas internas da Lista (necessário para a ordenação)

void Site_print_colorido(Site *s) {
    printf(BLUE "--------------------------------------------------\n" RESET);
    printf(BOLD CYAN " Site: " RESET YELLOW "%-15s" RESET, s->nome);
    printf(BOLD CYAN " | Relevancia: " RESET GREEN "[ %d ]\n" RESET, s->importancia);
    printf(CYAN " Palavras-chave: " RESET);
    
    for(int i = 0; i < s->qtdPalavras; i++){
        printf("%s%s", s->palavras[i], (i < s->qtdPalavras - 1) ? ", " : "");
    }
    printf("\n");
}

void ordenarSites(List *sitesEncontrados) {
    if (sitesEncontrados == NULL || sitesEncontrados->length < 2) return;

    int trocou;
    Node *ptr1;
    Node *lptr = NULL;

    do {
        trocou = 0;
        ptr1 = sitesEncontrados->first;
        while (ptr1->next != lptr) {
            Site *s1 = (Site*)ptr1->value;
            Site *s2 = (Site*)ptr1->next->value;
            if (s1->importancia < s2->importancia) {
                void *temp = ptr1->value;
                ptr1->value = ptr1->next->value;
                ptr1->next->value = temp;
                trocou = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (trocou);
}

void exibirResultados(List *sitesOrdenados) {
    if (sitesOrdenados == NULL || sitesOrdenados->length == 0) {
        printf(RED "\n[!] Não encontramos resultados para essa busca.\n" RESET);
        return;
    }

    printf(BOLD YELLOW "\n>>> RESULTADOS DA BUSCA (Ordenados por Importancia) <<<\n" RESET);
    
    List_print(sitesOrdenados, (void (*)(void*))Site_print_colorido);
    printf(BLUE "--------------------------------------------------\n" RESET);
}
