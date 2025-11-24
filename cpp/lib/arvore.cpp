#include <cstddef>
#include <cstdlib>
#include "arvore.h"

Arvore* cria_arv_vazia (void) {
   return NULL;
}

Arvore* arv_constroi (char c, Arvore* e, Arvore* d) {
  Arvore* a = (Arvore*)malloc(sizeof(Arvore));
  a->info = c;
  a->esq = e;
  a->dir = d;
  return a;
}

int verifica_arv_vazia (Arvore* a) {
  return (a == NULL);
}

Arvore* arv_libera (Arvore* a) {
  if (!verifica_arv_vazia(a)) {
    arv_libera (a->esq);
    arv_libera (a->dir);
    free(a);
  }
  return NULL;
}
