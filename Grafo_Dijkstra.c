#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 6

typedef struct {
    int NumVertices;
    int **Mat;
} TipoGrafo;

void Caminho_mais_curto(TipoGrafo *grafo, int origem, int destino) {
    int i, vert, NovaDist, min;
    int *M, *L, *A, *caminho;

    M = (int *)malloc(grafo->NumVertices * sizeof(int));
    L = (int *)malloc(grafo->NumVertices * sizeof(int));
    A = (int *)malloc(grafo->NumVertices * sizeof(int));
    caminho = (int *)malloc(grafo->NumVertices * sizeof(int));

    // Inicializando variáveis
    for (i = 0; i < grafo->NumVertices; i++) {
        M[i] = 0;        // false - determinar se um vértice já foi visitado
        A[i] = -1;       // determinar o caminho mais curto entre origem e destino
        L[i] = INT_MAX;  // infinito determina o comprimento do caminho mais curto
    }

    vert = origem;
    L[vert] = 0;

    while (vert != destino && vert != -1) { // não terminou ou caminho inexistente
        for (i = 0; i < grafo->NumVertices; i++) { // percorre vértices adjacentes de vert
            if (grafo->Mat[vert][i] && !M[i]) {    // se existe aresta e ela não foi visitada
                NovaDist = L[vert] + grafo->Mat[vert][i];
                if (NovaDist < L[i]) {
                    L[i] = NovaDist;  // atualiza menor distância
                    A[i] = vert;      // atualiza caminho
                }
            }
        }
        M[vert] = 1;      // toda a lista de adjacentes de vert já foi analisada
        min = INT_MAX;    // infinito
        vert = -1;        // valor inválido
        for (i = 0; i < grafo->NumVertices; i++) { // encontra próximo vértice do caminho
            if (!M[i] && L[i] < min) { // escolhe o vértice cuja aresta possui o menor peso
                min = L[i]; // atualiza min
                vert = i;   // atualiza vert
            }
        }
    } // fim while

    // Listar o caminho mais curto entre origem e destino
    if (vert == destino) { // encontrou um caminho
        printf("Caminho mais curto entre %d e %d tem comprimento %d: ", origem, destino, L[destino]);

        int k = 0;
        caminho[k] = destino;
        while (A[destino] != -1) {
            destino = A[destino];
            caminho[++k] = destino;
        }

        for (i = k; i >= 0; i--) {
            printf("%d ", caminho[i]);
        }
    } else {
        printf("Não existe caminho entre %d e %d", origem, destino);
    }

    free(M);
    free(L);
    free(A);
    free(caminho);
}

int main() {
    int Matriz[V][V] = {
        {0, 1, 4, 0, 0, 0},
        {1, 0, 4, 2, 7, 0},
        {4, 4, 0, 3, 5, 0},
        {0, 2, 3, 0, 4, 6},
        {0, 7, 5, 4, 0, 7},
        {0, 0, 0, 6, 7, 0}
    };

    TipoGrafo grafo;
    grafo.NumVertices = V;
    grafo.Mat = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        grafo.Mat[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            grafo.Mat[i][j] = Matriz[i][j];
        }
    }

    int origem = 0; // Defina a origem desejada
    int destino = 4; // Defina o destino desejado
    Caminho_mais_curto(&grafo, origem, destino);

    for (int i = 0; i < V; i++) {
        free(grafo.Mat[i]);
    }
    free(grafo.Mat);

    return 0;
}
