#ifndef COMBATE_H
#define COMBATE_H

#include "tipos.h"

int calcularAtaque(Personagem *p);
int calcularDano(int ataque, int defesa);
void danoNoMonstro(Monstro *m, int dano);
int combate(Personagem *p, Monstro m);

#endif
