#ifndef FASES_H
#define FASES_H

#include "tipos.h"

void criarFases(Fase fases[]);
int jogarFase(Personagem *p, Fase *f, int numFase);
int executarEvento(Personagem *p, Fase *f, int numFase, TipoCasa tipo);

#endif
