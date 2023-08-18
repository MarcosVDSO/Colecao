#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#ifndef _GCOFO_C_
#define _GCOFO_C_
#include "gcofo.h"


typedef struct _gcofo_ {
int numItens;
int maxItens;
int cur;
void **item; // int *item;
} GCofo;

typedef struct _aluno_ {
    char nome[30];
    int numero;
    float nota;

} Aluno;


GCofo *gcofCreate(int maxItens) {
    GCofo *gc;
    if (maxItens >0 ) {
        gc = (GCofo *) malloc (sizeof (GCofo ));
        if (gc!= NULL ) {
            gc->item = ( void * *) malloc(sizeof (void * )* maxItens);
            if (gc->item != NULL ) {
                gc->numItens= 0;
                gc->maxItens = maxItens;    
                gc->cur = -1;
                return gc;
            }
            free (gc);
        }
    }
    return NULL ;
}/* fim de gcofCreate */


int gcofDestroy(GCofo *gc ) {
    if ( gc != NULL ) {
        if ( gc->numItens == 0 ) {
        free(gc->item);
        free(gc);
        return TRUE ;
    }
}
    return FALSE;
} /* fim de gcofDestroy */

int gcofInsert(GCofo *gc, void *item ) {
    if ( gc != NULL ) {
        if ( gc->numItens < gc->maxItens) {
            gc->item[gc->numItens] = item;
            gc->numItens++;
            return TRUE;
        }
    }
    return FALSE;
} /* fim de colInserir */

void* gcofGetFirst(GCofo *gc) {
    void* elm;
    if(gc!=NULL) {
        if(gc->numItens>0) {
            elm = gc->item[0];
            gc->cur = 0;
            return elm;
        }
    }
    return NULL;

}

void *gcofGetNext (GCofo *gc) {
    void* elm;
    if(gc!=NULL) {
        if(gc->numItens>0 && gc->cur<gc->numItens-1) {
            gc->cur++;
            elm = gc->item[gc->cur];
            return elm;
        }
    }
    return NULL;
} 

void* gcofQuery (GCofo *gc, void* chave, int(*cmp)(void*, void*)) {
    if (gc == NULL)
        return NULL;

    if (gc->numItens <= 0) // coleção deve ter algo
        return NULL;

    for (int i = 0; i < gc->numItens; i++) {
         // Retorna o objeto se a função retornou TRUE
        if (cmp (gc->item[i], chave) == TRUE) {
            return gc->item[i];
        }
    }
    return NULL;
}

/*
void *gcofQuery( GCofo *gc, void *key, int (*cmp) (void *, void *) ) {
    int i; int data; int stat;
    if ( gc != NULL) {
        if (gc->numItens > 0 ) {
            i = 0;
            stat = cmp(gc->item[i] , key);
            while ( i < gc->numItens && stat != TRUE) {
                i++;
                stat = cmp(gc->item[i] , key);
            }
            if (gc->item[i] == key) {
                return gc->item[i];
            }
        }
    return NULL;
    }
}
*/
/*void *gcofRemove(GCofo *gc, void *key, int (*cmp)(void *, void *) ) {
    int i, j, stat;
    void *data;
    if ( gc != NULL) {
        if (gc->numItens > 0 ) {
            i = 0; stat = cmp (key, gc->item[i]);
            while ( i < gc->numItens && stat != TRUE) {
                i++;
                stat = cmp (key, gc->item[i]);
            }
            if (stat == TRUE) {
                data = gc->item[i];
                for (j=i; j< gc->numItens; j++) {
                    gc->item[j] = gc->item[j+1];
                }
                gc->numItens--;
                return data;
            }
        }
    }
    return NULL;
}
*/

void* gcofRemove (GCofo *gc, void* chave) {
    void* data;
    if (gc == NULL)
        return NULL;

    // Deve ter algo dentro da coleção pra poder tirar
    if (gc->numItens <= 0) {
        return NULL;
    }

    // Procura o primeiro valor com a chave, exclui ele da coleção e retorna ele
    for (int i = 0; i < gc->numItens; i++) {
        // Procura algum item dentro da coleção com essa chave
        if (gc->item[i] == chave) {
            // Salva ela pra retornar depois
            data = gc->item[i];
            // Pega tudo o que tem depois e reorganiza
            for (int j = i; j < gc->numItens; j++) {
                gc->item[j] = gc->item[j+1];
            }
            // Diminui a quantidade de itens do vetor
            gc->numItens--;
            return data;
        }
    }
}
int QueryAlunoNota( void *al, void *nota) {
    Aluno *pa; float *pnota;
    pa = (Aluno *) al;
    pnota = (float *) nota;
    if ( pa->nota == *pnota) {
        return TRUE;
    } 
    else {
        return FALSE;
    }
}

int QueryAlunoNome( void *al, void *nome) {
    Aluno *pa; char *pnome;
    pa = (Aluno *) al;
    pnome = (char *) nome;
    if ( strcmp(pa->nome, pnome) == FALSE) {
    return TRUE;
    } 
    else {
    return FALSE;
    }
}

int QueryAlunoNumero(void *al, void *numero) {
    Aluno *pa; int *pnumero;
    pa = (Aluno *) al;
    pnumero = (int *) numero;
    if(pa->numero == *pnumero) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

void* gcofEsvaziar (GCofo *gc) {
    if (gc == NULL)
        return NULL;
    
    if (gc->numItens <= 0)
        return NULL;

    while (gc->numItens != 0) {
        gcofRemove(gc, gc->item[0]);
    }
}




#endif
  