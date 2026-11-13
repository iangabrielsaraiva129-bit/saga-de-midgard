#ifndef TIPOS_H
#define TIPOS_H

/* tamanhos usados no jogo */
enum { NUM_FASES = 3, NUM_MONSTROS = 3, TAM_TABULEIRO = 12 };

typedef enum { GUERREIRO, ARQUEIRO, RUNISTA } ClassePersonagem;
typedef enum { CASA_VAZIA, CASA_COMBATE, CASA_TESOURO, CASA_CURA, CASA_ARMADILHA, CASA_MISSAO } TipoCasa;
typedef enum { ACAO_ATACAR = 1, ACAO_DEFENDER, ACAO_HABILIDADE, ACAO_FUGIR } AcaoCombate;

typedef struct {
    char nome[30];
    ClassePersonagem classe;
    int vida, vidaMax, forca, defesa, agilidade, inteligencia, xp, nivel;
    char arma[30];
    int bonusArma;
    char armadura[30];
    int bonusArmadura;
    char habilidade[30];
} Personagem;

typedef struct {
    char nome[30];
    char descricao[100];
    int vida, ataque, defesa, xpRecompensa;
} Monstro;

typedef struct {
    char nome[30];
    char descricao[400];
    char missao[100];
    double fator;
    Monstro monstros[NUM_MONSTROS];
} Fase;

#endif
