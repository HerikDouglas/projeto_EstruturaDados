# Projeto - Estrutura de Dados (Grafo de Sites)
**Docente:** 
  - Prof. Dr. Paulo Regis Menezes Sousa

**Discentes:**
  - Herik Douglas Oliveira Reinaldo
  - Pedro Matheus dos Santos Souza

## Visão Geral 

Este projeto foi desenvolvido no contexto da disciplina de Estrutura de Dados e tem como objetivo aplicar conceitos fundamentais de grafos utilizando a linguagem C.
O sistema modela um conjunto de sites como vértices e suas relações como arestas, permitindo inserção, comparação, impressão e operações básicas de análise.

A implementação prioriza modularidade, clareza de código e boas práticas de versionamento com Git/GitHub, viabilizando o trabalho colaborativo em equipe.

## Objetivos 
- Utilizar estrutura e implementações para utilização de grafos feitas em aula
- Modelar campos do tipo Site com atributos relevantes
- Integrar lista de sites ao grafo
- Aplicação dos conceitos de ponteiros, TADs e modularização
- Praticar colaboração em equipe via GitHub
- Ter layout intuitivo ao usuário por meio do uso de cores no terminal

## Estrutura do projeto
```
├── Graph.c
├── Graph.h
├── List.c
├── List.h
├── Site.c
├── Site.h
├── teste.c
├── listSites.txt
└── README.md
```
Os arquivos do projeto estão organizados na raiz do repositório, concentrando os módulos principais (grafo, lista e site) e os arquivos de teste, visando simplicidade e clareza no desenvolvimento acadêmico.

## Descriçao dos arquivos
- **Graph.h / Graph.c**: Definição e implementação do TAD Grafo, feitos em aula.
- **Site.h / Site.c**: Definição da estrutura `Site` e funções associadas.
- **teste.c**: Função principal responsável por testar e integrar os módulos.
- **listSites.txt**:  Arquivo contendo o nome dos sites, palavras chave e relação com pesos entre sites.
- **README.md**: Documentação do projeto

## Estrutura `Site`
Cada site é representado por uma estrutura contendo:

- Nome do site
- Lista de palavras-chave
- Quantidade de palavras-chave
- Grau de importância

Essa estrutura é utilizada como vértice no grafo.

## Funcionalidades Implementadas
- `Void Graph_insertSite(Graph *g, Site *site)`
- `Site *Site_alloc(char *nome, char palavras[][30], int qtdPalavras);`
- `void  Site_print(Site *s)`
- `int   Site_cmp(void *a, void *b)`
- `void  Graph_insertLink(Graph *g, Site *origem, Site *destino, int p);`
- `void  Graph_calcularImportancia(Graph *g);`
- `void  imprimirImportancia(Graph *g);`
- `void  graph_lerArquivo(Graph *g, const char *nomeArquivo);`
- `List *buscarSitesPorPalavra(Graph *g, char *termo);`

## Compilação e Execução
**Compilação Manual**
```
gcc *.c -o executavel
```
**Execução**
```
./executavel
```

## Tecnologias Utilizadas
- Linguagem C
- Git e GitHub
- Compilador GCC

## Organização da Equipe
- **HERIK:** Modelagem dos Sites + Carga de Dados + Conexão ao Grafo
- **PEDRO MATHEUS:** Cálculo da Importância + Busca de Palavras
- **JOÃO ALISON:** Ordenação + Exibição + Programa Principal (teste.c)

## Observações Finais

Este projeto contribuiu para consolidar o aprendizado prático sobre estruturas de dados, com ênfase na implementação e utilização de grafos. 
A sua construção contribui diretamente para o entendimento de como diferentes Tipos Abstratos de Dados (TADs), como listas e grafos que foram utilizados, 
podem ser integrados para formar estruturas mais complexas, reforçando conceitos de modularização, uso de ponteiros e organização do código.

Além disso, o desenvolvimento colaborativo por meio do GitHub proporcionou experiência prática em controle de versão, trabalho em equipe e integração de contribuições, aproximando os participantes de práticas adotadas em ambientes profissionais de desenvolvimento de software. 
Dessa forma, o projeto prepara os integrantes para desafios mais avançados em programação.

#

**Universidade Estadual Vale do Acaraú - UVA**  
**Centro de Ciências Exatas e Tecnnologia - CCET**  
**Bacharelado em Ciências da Computação**  
**Disciplina de Estrutura de Dados**
