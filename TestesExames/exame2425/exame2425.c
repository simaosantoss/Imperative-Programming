#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int inf,sup;
} Intervalo;

// Exercicio 1

int procuraX(Intervalo c[], int N, int x) {
    int low = 0;
    int high = N-1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (x >= c[mid].inf && x <= c[mid].sup)
            return 1;

        else if (x > c[mid].sup) 
            low = mid + 1;

        else
            high = mid - 1;
    }
    return 0;
}

// Exercicio 2

int insereIntervalo(Intervalo c[], int N, Intervalo novo) {
    int i = N - 1;

    while (i >= 0 && c[i].inf > novo.inf) {
        c[i+1] = c[i];
        i--;
    }

    c[i+1] = novo;

    return N + 1;
}

// Exercicio 3

void inverte (char s[], int inicio, int fim) {
    while (inicio < fim) {
        char tmp = s[inicio];
        s[inicio] = s[fim];
        s[fim] = tmp;
        inicio++;
        fim--;
    }
}

void InvertePal (char s[]) {
    int inicio;
    int i = 0;

    while (s[i] != '\0') {

        while (s[i] != '\0' && s[i] == ' ')
            i++;

        inicio = i;

        while (s[i] != '\0' && s[i] != ' ')
            i++;

        if (inicio < i)
            inverte (s, inicio, i-1);
    }
}

// Exercicio 4

typedef struct no {
    int valor;
    struct no *prox;
} *LInt;

int listToArray(LInt l, int v[], int N) {
    int i = 0;

    while (l != NULL && i < N) {
        v[i] = l->valor;
        l = l->prox;
        i++;
    }

    return i;
}

// Exercicio 5

void removeNaoCrescente(LInt *l) {
    while (*l != NULL && (*l)->prox != NULL) {

        if ((*l)->valor > (*l)->prox->valor) {
            LInt tmp = *l;
            *l = tmp->prox;
            free(tmp);
        }

        else
            l = &(*l)->prox;
    }
}

// Exercicio 6

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

void auxFolhaMaisProfunda(ABin a, int nivel, int *maxNivel, ABin *folha) {
    if (a == NULL) return;

    if (a->esq == NULL && a->dir == NULL) {
        if (nivel > *maxNivel) {
            *maxNivel = nivel;
            *folha = a;
        }
    }

    auxFolhaMaisProfunda(a->esq, nivel + 1, maxNivel, folha);
    auxFolhaMaisProfunda(a->dir, nivel + 1, maxNivel, folha);
}

ABin folhaMaisProfunda(ABin a) {
    ABin folha = NULL;
    int maxNivel = -1;

    auxFolhaMaisProfunda(a, 0, &maxNivel, &folha);

    return folha;
}
