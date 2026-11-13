#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "tipos.h"

char *nomeClasse(ClassePersonagem classe);
ClassePersonagem escolherPersonagem(void);
void escolherNome(Personagem *p);
void criarPersonagem(Personagem *p, ClassePersonagem classe);
void receberDano(Personagem *p, int dano);
void curar(Personagem *p, int valor);
void ganharXP(Personagem *p, int xp);
void aplicarBonusAleatorio(Personagem *p);

#endif
