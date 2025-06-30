#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX  100

typedef struct lligada {
    int valor;              // o valor que este nó guarda
    struct lligada *prox;   // ponteiro para o próximo nó
} *LInt;

// exemplo visual : [5] -> [10] -> [15] -> NULL

// 1 - Calcular o comprimento da lista ligada

int length (LInt l) {
    int cont = 0;     
    LInt atual = l;    

    while (atual != NULL) { 
        cont = cont + 1;     
        atual = atual->prox;
    }

    return cont;    
}

// 2 - Libertar o espaço ocupado por uma lista 

void freeL (LInt l) {
    LInt atual = l;
    LInt tmp;

    while (atual != NULL) {
        tmp = atual;
        atual = atual->prox;
        free (tmp);
    }
}

// 3 - imprimir todos os elementos de uma lista

void imprimeL (LInt l) {
    while (l != NULL) {
        printf("%d\n", l->valor);
        l = l->prox;
    }
}

// 4 - inverter uma lista (sem criar uma nova lista)

LInt reverseL (LInt l) {
    LInt anterior = NULL;
    LInt atual = l;
    LInt seguinte;

    while (atual != NULL) {
        seguinte = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = seguinte;
    }

    return anterior;
}


// 5 - inserir ordenadamente um elemento numa lista ordenada

void insertOrd(LInt *l, int x) {
    LInt novo = malloc(sizeof(struct lligada));
    novo->valor = x;
    novo->prox = NULL;

    while (*l != NULL && (*l)->valor < x) {
        l = &((*l)->prox);
    }

    novo->prox = *l;
    *l = novo;
}

// 6 - remover um elemento de uma lista ordenada. Retorna 1 caso o elemento a remover não exista, 0 no outro caso

int removeOneOrd(LInt *l, int x) {
    LInt *p = l;

    while (*p != NULL && (*p)->valor < x) {
        p = &(*p)->prox;
    }

    if (*p != NULL && (*p)->valor == x) {
        LInt tmp = *p;          
        *p = (*p)->prox;        
        free(tmp);              
        return 0;               
    } else {
        return 1;               
    }
}

// 7 - juntar duas listas ordenadas (a e b) numa única lista ordenada (*r)

void merge (LInt *r, LInt a, LInt b) {
    LInt *p = r;

    while (a != NULL && b != NULL) {
        if (a->valor < b->valor) {
            *p = a;
            a = a->prox;
        } else {
            *p = b;
            b = b->prox;
        }
        p = &(*p)->prox;
    }
        *p = (a != NULL) ? a : b;
}

// 8 - partir a lista em duas (retornando os endereços dos primeiros elementos da lista em *mx e *Mx): uma com os elementos de l menores do que x e a outra com os restantes

void splitQS (LInt l, int x, LInt *mx, LInt *Mx) {
    LInt *pMenor = mx;
    LInt *pMaior = Mx;

    while (l != NULL) {
        if (l->valor < x) {
            *pMenor = l;
            pMenor = &(*pMenor)->prox;
        } else {
            *pMaior = l;
            pMaior = &(*pMaior)->prox;
        }
        l = l->prox;
    }

    *pMenor = NULL;
    *pMaior = NULL;
}

// 9 - partir uma lista não vazia *l a meio

LInt parteAmeio (LInt *l) {
    int len = length(*l);
    int meio = len / 2;

    if (meio == 0) return NULL; 

    LInt atual = *l;
    for (int i = 1; i < meio; i++) {
        atual = atual->prox;
    }

    LInt segunda = atual->prox; 
    atual->prox = NULL;         
    LInt primeira = *l;         
    *l = segunda;               

    return primeira;
}

// 10 - remover todas as ocorrências de um dado inteiro de uma lista, retornando o número de células removidas.

int removeAll (LInt *l, int x) {
    LInt *p = l;
    int cont = 0;

    while (*p != NULL) {
        if ((*p)->valor == x) {
            LInt tmp = *p;
            *p = (*p)->prox;
            free(tmp);
            cont++;
        } 
        else
            p = &(*p)->prox;
    }

    return cont;
}


// 11 - remover os valores repetidos de uma lista (deixando apenas a primeira ocorrência)

int removeDups(LInt *l) {
    int cont = 0;
    LInt atual = *l;

    while (atual != NULL){ 
        LInt *p = &atual->prox;
    
        while (*p != NULL) {
            if (((*p)->valor) == atual->valor) {
                LInt tmp = *p;
                *p = (*p)->prox;
                free(tmp);
                cont++;
            } else 
                p = &(*p)->prox;
        }
        atual = atual->prox; 
    }
    return cont;
}

// 12 - remover (a primeira ocorrência) o maior elemento de uma lista não vazia, retornando o valor desse elemento

int removeMaiorL(LInt *l) {
    int max = (*l)->valor;
    LInt *p = l;
    LInt *pMax = l;

    while (*p != NULL) {
        if ((*p)->valor > max) {
            max = (*p)->valor;
            pMax = p;
        }
        p = &(*p)->prox;
    }

    LInt tmp = *pMax;
    *pMax = (*pMax)->prox;
    free(tmp);

    return max;
}

// 13 - remover o úlltimo elemento de uma lista não vazia (libertando o correspondente espaço)

void init (LInt *l) {
    if (*l == NULL) return;

    if ((*l)->prox == NULL) {
        free(*l);
        *l = NULL;
        return;
    }    

    LInt p = *l;
    while (p->prox->prox != NULL)
        p = p->prox;

    free (p->prox);
    p->prox = NULL;
}

// 14 - acrescentar um elemento no fim da lista

void appendL (LInt *l, int x) {
    LInt novo = malloc(sizeof(struct lligada));
    novo->valor = x;
    novo->prox = NULL;

    if (*l == NULL) {
        *l = novo;
        return;
    }

    LInt p = *l;
    while (p->prox != NULL)
        p = p->prox;
    p->prox = novo;
}

// 15 -  acrescentar a lista b à lista *a

void concatL (LInt *a, LInt b) {
    if ((*a) == NULL) {
        (*a) = b;
        return;
    }

    LInt p = *a;
    while (p->prox != NULL) 
        p = p->prox;

    p->prox = b;
}

// 16 - criar uma nova lista ligada com os elementos pela ordem em que aparecem na lista argumento

LInt cloneL (LInt l) {
    if (l == NULL) return NULL; 

    LInt novo = malloc(sizeof(struct lligada));
    novo->valor = l->valor;
    novo->prox = NULL;

    LInt head = novo; 
    l = l->prox;       

    while (l != NULL) {
        LInt novoNodo = malloc(sizeof(struct lligada));
        novoNodo->valor = l->valor;
        novoNodo->prox = NULL;

        novo->prox = novoNodo; 
        novo = novoNodo;     
        l = l->prox;        
    }

    return head;
}

// 17 - criar uma nova lista ligada com os elementos por ordem inversa

LInt cloneRev (LInt l) {
    LInt nova = NULL;

    while (l != NULL) {
        LInt novo = malloc(sizeof(struct lligada));
        novo->valor = l->valor;
    
    novo->prox = nova;
    nova = novo;

    l = l->prox;
    }

    return nova;
}

// 18 - calcula qual o maior valor armazenado numa lista não vazia

int maximo (LInt l) {
    int max = l->valor;
    l = l->prox;

    while (l != NULL) {
        if (max < l->valor) 
            max = l->valor;
        l = l->prox;
    }

    return max;
}

// 19 - dado um inteiro n e uma lista ligada de inteiros l, apaga de l todos os nodos para além do n-ésimo (libertando o respectivo espaço). 
// Se a lista tiver n ou menos nodos, a função não altera a lista. A função deve retornar o comprimento final da lista.

int take (int n, LInt *l) {
    int cont = 0;
    LInt p = *l;

    if (n <= 0) {
        while (*l != NULL) {
            LInt tmp = *l;
            *l = (*l)->prox;
            free(tmp);
        }
        return 0;
    }

    while (p != NULL && cont < n - 1) {
        p = p->prox;
        cont++;
    }

    if (p == NULL) return cont;

    LInt tmp = p->prox;
    p->prox = NULL;

    while (tmp != NULL) {
        LInt next = tmp->prox;
        free(tmp);
        tmp = next;
    }

    return n;
}

// 20 - dado um inteiro n e uma lista ligada de inteiros l, apaga de l os n primeiros elementos da lista (libertando o respectivo espaço). Se a lista tiver n ou menos nodos, a função liberta a totalidade da lista.
// A função deve retornar o número de elementos removidos.

int drop(int n, LInt *l) {
    int removidos = 0;

    while (*l != NULL && removidos < n) {
        LInt tmp = *l;
        *l = (*l)->prox;
        free(tmp);
        removidos++;
    }

    return removidos;
}

// 21 - dada uma lista circular dá como resultado o endereço do elemento da lista que está N posições à frente

LInt Nforward(LInt l, int N) {
    for (int i = 0; i < N; i++) {
        l = l->prox;
    }

    return l;
}

 // 22 - preencher o array v com os elementos da lista

int listToArray (LInt l, int v[], int N) {
    int i = 0;

    while  (i < N && l != NULL) {
        v[i] = l->valor;
        l = l->prox;
        i++;
    }

    return i;
}

// 23 - construir uma lista com os elementos de um array, pela mesma ordem em que aparecem no array

LInt arrayToList (int v[], int N) {
    if (N == 0) return NULL;

    LInt novo = malloc(sizeof(struct lligada));
    novo->valor = (*v);
    novo->prox = arrayToList(v+1, N-1);

    return novo;
}

// 24 - dada uma lista de inteiros, constrói uma nova lista de inteiros contendo as somas acumuladas da lista original (que deverá permanecer inalterada)

LInt somasAcL(LInt l) {
    LInt head = NULL, *last = &head;
    int soma = 0;

    while (l != NULL) {
        soma += l->valor;

        LInt novo = malloc(sizeof(struct lligada));
        novo->valor = soma;
        novo->prox = NULL;

        *last = novo;
        last = &novo->prox;

        l = l->prox;
    }

    return head;
}

// 26 - dada uma lista ordenada de inteiros, elimina dessa lista todos os valores repetidos assegurando que o espaço de memória correspondente aos nós removidos é correctamente libertado

LInt rotateL(LInt l) {
    if (l == NULL || l->prox == NULL)
        return l;

    LInt primeiro = l;
    LInt novoInicio = l->prox;

    LInt p = novoInicio;
    while (p->prox != NULL)
        p = p->prox;

    p->prox = primeiro;
    primeiro->prox = NULL;

    return novoInicio;
}

// 27 - partir uma lista l em duas: na lista l ficam apenas os elementos das posições ímpares; na lista resultante ficam os restantes elementos

LInt parte(LInt l) {
    if (l == NULL || l->prox == NULL)
        return NULL;

    LInt pares = l->prox;
    LInt impar = l;
    LInt par = pares;

    while (par != NULL && par->prox != NULL) {
        impar->prox = par->prox;
        impar = impar->prox;
        par->prox = impar->prox;
        par = par->prox;
    }

    impar->prox = NULL;

    return pares;
}

// Árvores binárias

typedef struct nodo {
int valor;
struct nodo *esq, *dir;
} *ABin;

/*
exemplo visual:

     5
    / \
   3   7
*/

// 28 - calcular a altura de uma árvore binária

int altura(ABin a) {
    if (a == NULL)
        return 0;

    else
        return 1 + (altura (a->esq) > altura (a->dir) ? altura (a->esq) : altura (a->dir));
}

// 29 - criar uma cópia de uma árvore

ABin cloneAB(ABin a) {
    if (a == NULL)
        return NULL;

    ABin novo = malloc(sizeof(struct nodo));
    novo->valor = a->valor;
    novo->esq = cloneAB(a->esq);
    novo->dir = cloneAB(a->dir);

    return novo;
}

// 30 - inverter uma árvore (sem criar uma nova árvore)

void mirror(ABin *a) {
    if (a == NULL)
        return;

    mirror(&(*a)->esq);
    mirror(&(*a)->dir);

    ABin tmp = (*a)->esq;
    (*a)->esq = (*a)->dir;
    (*a)->dir = tmp;
}

// 31 - criar uma lista ligada de inteiros a partir de uma travessia inorder de uma árvore binária

void inorder(ABin a, LInt *l) {
    if (a == NULL) return;

    inorder(a->esq, l);

    LInt novo = malloc(sizeof(struct lligada));
    novo->valor = a->valor;
    novo->prox = NULL;
    *l = novo;

    l = &novo->prox;

    inorder(a->dir, l);
}

// 32 - criar uma lista ligada de inteiros a partir de uma travessia preorder de uma árvore binária

void preorder(ABin a, LInt *l) {
    if (a == NULL) return;

    LInt novo = malloc(sizeof(struct lligada));
    novo->valor = a->valor;
    novo->prox = NULL;
    *l = novo;

    l = &novo->prox;

    preorder(a->esq, l);

    preorder(a->dir, l);
}

// 33 - criar uma lista ligada de inteiros a partir de uma travessia posorder de uma árvore binária

void posorder(ABin a, LInt *l) {
    if (a == NULL) return;

    posorder(a->esq, l);

    posorder(a->dir, l);

    LInt novo = malloc(sizeof(struct lligada));
    novo->valor = a->valor;
    novo->prox = NULL;
    *l = novo;
    l = &novo->prox;
}

// 34 - calcular o nível (menor) a que um elemento está numa árvore binária (-1 caso não exista)

int depth(ABin a, int x) {
    if (a == NULL) return -1;
    if (a->valor == x) return 0;

    int d = depth(a->esq, x);
    if (d >= 0) return 1 + d;

    d = depth(a->dir, x);
    if (d >= 0) return 1 + d;

    return -1;
}

// 35 - libertar toda a memória da árvore binária a e retornar o número de nós que foram libertados

int freeAB(ABin a) {
    if (a == NULL)
        return 0;

    int esq = freeAB(a->esq);
    int dir = freeAB(a->dir);

    free(a);

    return 1 + esq + dir;
}

// 36 - remover (libertando o espaço respetivo) todos os elementos da árvore *a que estão a uma profundidade superior a l, retornando o número de elementos removidos.

int pruneAB(ABin *a, int l) {
    if (*a == NULL)
        return 0;

    if (l <= 0) {
        int removidos = freeAB(*a);
        *a = NULL;
        return removidos;
    }

    int esq = pruneAB(&(*a)->esq, l - 1);
    int dir = pruneAB(&(*a)->dir, l - 1);

    return esq + dir;
}

// 37 - testar se duas árvores são iguais (têm os mesmos elementos e a mesma forma)

int iguaisAB(ABin a, ABin b) {
    if (a == NULL && b == NULL)
        return 1;

    if (a == NULL || b == NULL)
        return 0;

    return (a->valor == b->valor) &&
           iguaisAB(a->esq, b->esq) &&
           iguaisAB(a->dir, b->dir);
}

// 38 - construir uma lista com os valores dos elementos que estão armazenados na árvore ao nível n (assuma que a raiz da árvore está ao nível 1)

LInt nivelL(ABin a, int n) {
    if (a == NULL)
        return NULL;

    if (n == 1) {
        LInt novo = malloc(sizeof(struct lligada));
        novo->valor = a->valor;
        novo->prox = NULL;
        return novo;
    }

    LInt esq = nivelL(a->esq, n - 1);
    LInt dir = nivelL(a->dir, n - 1);

    if (esq == NULL) return dir;

    LInt p = esq;
    while (p->prox != NULL)
        p = p->prox;

    p->prox = dir;

    return esq;
}

// 39 - preencher o vetor v com os elementos de a que se encontram no nível n. Considere que a raiz da árvore se encontra no nível 1.
// A função deverá retornar o número de posições preenchidas do array.

int nivelV(ABin a, int n, int v[]) {
    if (a == NULL) return 0;

    if (n == 1) {
        v[0] = a->valor;
        return 1;
    }

    int esq = nivelV(a->esq, n - 1, v);
    int dir = nivelV(a->dir, n - 1, v + esq);

    return esq + dir;
}

// 40. Preencher o array v com os elementos da árvore segundo uma travessia inorder. Preencher no máximo N elementos e retornar o número de elementos preenchidos.

int dumpAbin (ABin a, int v[], int N) {
    int e, d;

    if (a != NULL && N > 0) {
        e = dumpAbin(a->esq,v,N);

        if (e < N) {
            v[e] = a->valor;
            return 1 + e + dumpAbin(a->dir, v+e+1, N-e-1);
        }

        else return N;
    }

    else return 0;
}

// 41. Calcular a árvore das somas acumuladas de uma árvore de inteiros. Manter a mesma forma da árvore original e, em cada nodo, conter a soma dos elementos da subárvore que aí se inicia.

ABin somasAcA(ABin a) {
    if (a == NULL) return NULL;

    ABin novo = malloc(sizeof(struct nodo));
    novo->esq = somasAcA(a->esq);
    novo->dir = somasAcA(a->dir);

    int somaEsq = (novo->esq) ? novo->esq->valor : 0;
    int somaDir = (novo->dir) ? novo->dir->valor : 0;

    novo->valor = a->valor + somaEsq + somaDir;

    return novo;
}

// 42. Contar quantos nodos da árvore binária de inteiros são folhas, i.e., não têm descendentes.

int contaFolhas(ABin a) {
    if (a == NULL)
        return 0;

    if (a->esq == NULL && a->dir == NULL)
        return 1;

    return contaFolhas(a->esq) + contaFolhas(a->dir);
}

// 43. Criar uma nova árvore com o efeito de espelho (inversão) da árvore original.

ABin cloneMirror(ABin a) {
    if (a == NULL)
        return NULL;

    ABin novo = malloc(sizeof(struct nodo));
    novo->valor = a->valor;

    novo->esq = cloneMirror(a->dir);  // troca
    novo->dir = cloneMirror(a->esq);  // troca

    return novo;
}

// 44. Adicionar um elemento a uma árvore binária de procura. Retornar 1 se o elemento já existir ou 0 caso contrário. Implementar sem recursividade.

int addOrd(ABin *a, int x) {
    while (*a != NULL) {
        if (x == (*a)->valor)
            return 1; 

        else if (x < (*a)->valor)
            a = &((*a)->esq);  

        else
            a = &((*a)->dir);  
    }

    *a = malloc(sizeof(struct nodo));
    (*a)->valor = x;
    (*a)->esq = NULL;
    (*a)->dir = NULL;

    return 0; 
}

// 45. Testar se um elemento pertence a uma árvore binária de procura. Implementar sem recursividade.

int lookupAB(ABin a, int x) {
    while (a != NULL) {
        if (x == a->valor)
            return 1; 

        else if (x < a->valor)
            a = a->esq;

        else
            a = a->dir;
    }

    return 0;  
}

// 46. Calcular o nível a que um elemento se encontra numa árvore binária de procura (-1 se não existir). Assumir que a raiz está ao nível 1.

int depthOrd(ABin a, int x) {
    int nivel = 1;

    while (a != NULL) {
        if (x == a->valor)
            return nivel;

        else if (x < a->valor)
            a = a->esq;

        else
            a = a->dir;

        nivel++;
    }

    return -1;
}

// 47. Calcular o maior elemento de uma árvore binária de procura não vazia. Implementar sem recursividade.

int maiorAB(ABin a) {
    while (a->dir != NULL)
        a = a->dir;

    return a->valor;
}

// 48. Remover o maior elemento de uma árvore binária de procura.

void removeMaiorA(ABin *a) {
    if ((*a)->dir == NULL) {
        ABin tmp = *a;
        *a = (*a)->esq; 
        free(tmp);
    } else {
        removeMaiorA(&(*a)->dir);
    }
}

// 49. Contar quantos elementos de uma árvore binária de procura são maiores do que um dado inteiro.

int quantosMaiores(ABin a, int x) {
    if (a == NULL)
        return 0;

    if (a->valor <= x)
        return quantosMaiores(a->dir, x);  

    else
        return 1 + quantosMaiores(a->esq, x) + quantosMaiores(a->dir, x);
}

// 50. Construir uma árvore binária de procura a partir de uma lista ligada ordenada.

ABin buildTree(LInt *l, int n) {
    if (n <= 0) return NULL;

    ABin left = buildTree(l, n / 2); 

    ABin root = malloc(sizeof(struct nodo));
    root->valor = (*l)->valor;
    root->esq = left;

    *l = (*l)->prox;  

    root->dir = buildTree(l, n - n / 2 - 1);  

    return root;
}

void listToBTree(LInt l, ABin *a) {
    int len = 0;
    LInt temp = l;

    while (temp) {
        len++;
        temp = temp->prox;
    }

    *a = buildTree(&l, len);
}

// 51. Testar se uma árvore binária é de procura.

int todosValidos(ABin a, int x, int maior) {
    if (a == NULL) return 1; 

    if (maior && a->valor <= x) return 0;

    if (!maior && a->valor >= x) return 0;

    return todosValidos(a->esq, x, maior) && todosValidos(a->dir, x, maior);
}

int deProcura(ABin a) {
    if (a == NULL) return 1; 

    int esquerdaValida = todosValidos(a->esq, a->valor, 0) && deProcura(a->esq);
    int direitaValida  = todosValidos(a->dir, a->valor, 1) && deProcura(a->dir);

    return esquerdaValida && direitaValida;
}

/* ========= helpers ========= */
static LInt newNode(int x){LInt n=malloc(sizeof(struct lligada));n->valor=x;n->prox=NULL;return n;}
static ABin newAB  (int x){ABin n=malloc(sizeof(struct nodo   ));n->valor=x;n->esq=n->dir=NULL;return n;}

// lê uma linha e devolve lista com os inteiros encontrados
static LInt buildListPrompt(void){
    char buf[512];
    printf("Lista (ex: 1 2 3 4 ou [1,2,3,4]): ");
    int c=getchar(); if(c!='\n') ungetc(c,stdin);
    if(!fgets(buf,sizeof buf,stdin)) return NULL;
    LInt h=NULL,*last=&h; char *p=buf;
    while(*p){
        while(*p && !isdigit(*p) && *p!='-') p++;
        if(!*p) break;
        int v=strtol(p,&p,10);
        *last=newNode(v); last=&(*last)->prox;
    }
    return h;
}
static void showList(LInt l){ putchar('['); while(l){ printf("%d%s",l->valor,l->prox?",":""); l=l->prox;} puts("]"); }
static void gfreeL(LInt l){ while(l){LInt t=l; l=l->prox; free(t);} }

// lê inteiros até 0 – devolve BST usando addOrd()
static ABin buildBST(void){
    puts("Valores BST (0 termina):"); ABin a=NULL; int x;
    while(scanf("%d",&x)==1 && x!=0) addOrd(&a,x);
    return a;
}
static void inorderPrint(ABin a){ if(!a) return; inorderPrint(a->esq); printf("%d ",a->valor); inorderPrint(a->dir);} 
static void gfreeAB(ABin a){ if(!a) return; gfreeAB(a->esq); gfreeAB(a->dir); free(a);} 

/* ============================ */
int main(void){
  int op; printf("Exercício (1-51): "); if(scanf("%d",&op)!=1) return 0;

  switch(op){
  /* --- LISTAS --- */
  case 1:{LInt l=buildListPrompt(); printf("length = %d\n", length(l)); gfreeL(l); break;}
  case 2:{LInt l=buildListPrompt(); gfreeL(l); puts("lista libertada"); break;}
  case 3:{LInt l=buildListPrompt(); imprimeL(l); gfreeL(l); break;}
  case 4:{LInt l=buildListPrompt(); l=reverseL(l); showList(l); gfreeL(l); break;}
  case 5:{LInt l=buildListPrompt(); int x; printf("x = "); scanf("%d",&x); insertOrd(&l,x); showList(l); gfreeL(l); break;}
  case 6:{LInt l=buildListPrompt(); int x; printf("x = "); scanf("%d",&x); printf("ret=%d\n",removeOneOrd(&l,x)); showList(l); gfreeL(l); break;}
  case 7:{puts("Lista A"); LInt a=buildListPrompt(); puts("Lista B"); LInt b=buildListPrompt(); LInt r=NULL; merge(&r,a,b); showList(r); gfreeL(r); break;}
  case 8:{LInt l=buildListPrompt(); int x; printf("x = "); scanf("%d",&x); LInt m=NULL,M=NULL; splitQS(l,x,&m,&M); printf("<x "); showList(m); printf(">=x "); showList(M); gfreeL(m); gfreeL(M); break;}
  case 9:{LInt l=buildListPrompt(); LInt p=parteAmeio(&l); printf("1ª "); showList(p); printf("2ª "); showList(l); gfreeL(p); gfreeL(l); break;}
  case 10:{LInt l=buildListPrompt(); int x; printf("x = "); scanf("%d",&x); printf("rem=%d\n",removeAll(&l,x)); showList(l); gfreeL(l); break;}
  case 11:{LInt l=buildListPrompt(); printf("rem=%d\n",removeDups(&l)); showList(l); gfreeL(l); break;}
  case 12:{LInt l=buildListPrompt(); printf("max=%d\n",removeMaiorL(&l)); showList(l); gfreeL(l); break;}
  case 13:{LInt l=buildListPrompt(); init(&l); showList(l); gfreeL(l); break;}
  case 14:{LInt l=buildListPrompt(); int x; printf("x append = "); scanf("%d",&x); appendL(&l,x); showList(l); gfreeL(l); break;}
  case 15:{puts("A"); LInt a=buildListPrompt(); puts("B"); LInt b=buildListPrompt(); concatL(&a,b); showList(a); gfreeL(a); break;}
  case 16:{LInt l=buildListPrompt(); LInt c=cloneL(l); showList(c); gfreeL(c); gfreeL(l); break;}
  case 17:{LInt l=buildListPrompt(); LInt c=cloneRev(l); showList(c); gfreeL(c); gfreeL(l); break;}
  case 18:{LInt l=buildListPrompt(); printf("max=%d\n",maximo(l)); gfreeL(l); break;}
  case 19:{LInt l=buildListPrompt(); int k; printf("k = "); scanf("%d",&k); printf("ret=%d\n",take(k,&l)); showList(l); gfreeL(l); break;}
  case 20:{LInt l=buildListPrompt(); int k; printf("k = "); scanf("%d",&k); printf("ret=%d\n",drop(k,&l)); showList(l); gfreeL(l); break;}
  case 21:{LInt l=buildListPrompt(); int k; printf("N = "); scanf("%d",&k); if(!l){puts("lista vazia"); break;} LInt p=Nforward(l,k%length(l)); printf("valor=%d\n",p->valor); gfreeL(l); break;}
  case 22:{LInt l=buildListPrompt(); int N; printf("array len = "); scanf("%d",&N); int v[128]; int m=listToArray(l,v,N); printf("copiados=%d => ",m); for(int i=0;i<m;i++) printf("%d ",v[i]); puts(""); gfreeL(l); break;}
  case 23:{puts("Array -> termine com 0"); int v[128],n=0,x; while(scanf("%d",&x)==1 && x!=0) v[n++]=x; LInt l=arrayToList(v,n); showList(l); gfreeL(l); break;}
  case 24:{LInt l=buildListPrompt(); LInt s=somasAcL(l); showList(s); gfreeL(s); gfreeL(l); break;}
  case 25:{puts("(reservado)"); break;}
  case 26:{LInt l=buildListPrompt(); l=rotateL(l); showList(l); gfreeL(l); break;}
  case 27:{LInt l=buildListPrompt(); LInt pares=parte(l); printf("imp "); showList(l); printf("par "); showList(pares); gfreeL(l); gfreeL(pares); break;}

  /* --- ÁRVORES --- */
  case 28:{ABin a=buildBST(); printf("alt=%d\n",altura(a)); gfreeAB(a); break;}
  case 29:{ABin a=buildBST(); ABin c=cloneAB(a); inorderPrint(c); puts(""); gfreeAB(a); gfreeAB(c); break;}
  case 30:{ABin a=buildBST(); mirror(&a); inorderPrint(a); puts(""); gfreeAB(a); break;}
  case 31:{ABin a=buildBST(); LInt l=NULL; inorder(a,&l); showList(l); gfreeL(l); gfreeAB(a); break;}
  case 32:{ABin a=buildBST(); LInt l=NULL; preorder(a,&l); showList(l); gfreeL(l); gfreeAB(a); break;}
  case 33:{ABin a=buildBST(); LInt l=NULL; posorder(a,&l); showList(l); gfreeL(l); gfreeAB(a); break;}
  case 34:{ABin a=buildBST(); int x; printf("x = "); scanf("%d",&x); printf("depth=%d\n",depth(a,x)); gfreeAB(a); break;}
  case 35:{ABin a=buildBST(); printf("free=%d\n",freeAB(a)); break;}
  case 36:{ABin a=buildBST(); int l; printf("profundidade = "); scanf("%d",&l); printf("rem=%d\n",pruneAB(&a,l)); gfreeAB(a); break;}
  case 37:{puts("Árvore A"); ABin a=buildBST(); puts("Árvore B"); ABin b=buildBST(); printf("iguais? %s\n", iguaisAB(a,b)?"sim":"não"); gfreeAB(a); gfreeAB(b); break;}
  case 38:{ABin a=buildBST(); int n; printf("nível = "); scanf("%d",&n); LInt l=nivelL(a,n); showList(l); gfreeL(l); gfreeAB(a); break;}
  case 39:{ABin a=buildBST(); int n; printf("nível = "); scanf("%d",&n); int v[128]; int k=nivelV(a,n,v); for(int i=0;i<k;i++) printf("%d ",v[i]); puts(""); gfreeAB(a); break;}
  case 40:{ABin a=buildBST(); int N; printf("máx = "); scanf("%d",&N); int v[128]; int k=dumpAbin(a,v,N); for(int i=0;i<k;i++) printf("%d ",v[i]); puts(""); gfreeAB(a); break;}
  case 41:{ABin a=buildBST(); ABin s=somasAcA(a); inorderPrint(s); puts(""); gfreeAB(a); gfreeAB(s); break;}
  case 42:{ABin a=buildBST(); printf("folhas=%d\n",contaFolhas(a)); gfreeAB(a); break;}
  case 43:{ABin a=buildBST(); ABin m=cloneMirror(a); inorderPrint(m); puts(""); gfreeAB(a); gfreeAB(m); break;}
  case 44:{ABin a=NULL; printf("Valores (0 termina): "); int x; while(scanf("%d",&x)==1 && x){ printf("ret=%d\n",addOrd(&a,x)); } inorderPrint(a); puts(""); gfreeAB(a); break;}
  case 45:{ABin a=buildBST(); int x; printf("x = "); scanf("%d",&x); printf("existe? %s\n",lookupAB(a,x)?"sim":"não"); gfreeAB(a); break;}
  case 46:{ABin a=buildBST(); int x; printf("x = "); scanf("%d",&x); printf("depthOrd=%d\n",depthOrd(a,x)); gfreeAB(a); break;}
  case 47:{ABin a=buildBST(); printf("maior=%d\n",maiorAB(a)); gfreeAB(a); break;}
  case 48:{ABin a=buildBST(); removeMaiorA(&a); inorderPrint(a); puts(""); gfreeAB(a); break;}
  case 49:{ABin a=buildBST(); int x; printf("x = "); scanf("%d",&x); printf("maiores=%d\n",quantosMaiores(a,x)); gfreeAB(a); break;}
  case 50:{LInt l=buildListPrompt(); ABin a=NULL; listToBTree(l,&a); inorderPrint(a); puts(""); gfreeAB(a); gfreeL(l); break;}
  case 51:{ABin a=buildBST(); printf("deProcura? %s\n",deProcura(a)?"sim":"não"); gfreeAB(a); break;}

  default: puts("opção inválida");
  }
  return 0;
}


