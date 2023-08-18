#ifndef _GCOFO_H_
#define _GCOFO_H_
typedef struct _gcofo_ GCofo;
typedef struct _aluno_ Aluno;
#ifdef _GCOFO_C_



GCofo *gcofCreate( int max_itens );

int gcofInsert(GCofo *gc, void *item );

//void *gcofRemove(GCofo *c, void *key, int (*cmp)(void *, void *) );

void *gcofQuery( GCofo *c, void *key, int (*cmp) (void *, void *) );

//void *gcofGetFirst(GCofo *gc);

//void *gcofGetNext (GCofo *gc);

int gcofDestroy (GCofo *gc);

int QueryAlunoNota( void *al, void *nota);

int QueryAlunoNome( void *al, void *nome);

int QueryAlunoNumero(void *al, void *numero);

void* gcofRemove (GCofo *gc, void* chave);
void* gcofEsvaziar (GCofo *col);

#else
extern GCofo *gcofCreate( int max_itens );
extern int gcofInsert(GCofo *gc, void *item );
//extern void *gcofRemove(GCofo *gc, void *key, int (*cmp)(void *, void *) );
extern void *gcofQuery( GCofo *gc, void *key, int (*cmp) (void *, void *) );
//extern void * gcofGetFirst(GCofo *gc);
//extern void * gcofGetNext (GCofo *gc);
extern int gcofDestroy (GCofo *gc);
extern int QueryAlunoNota( void *al, void *nota);
extern int QueryAlunoNome( void *al, void *nome);
extern int QueryAlunoNumero(void *al, void *numero);
extern void* gcofRemove (GCofo *gc, void* chave);
extern void* gcofEsvaziar (GCofo *gc);
#endif
#endif


//https://github.com/uotlaf/colecoes_ed

