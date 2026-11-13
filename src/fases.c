#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fases.h"
#include "combate.h"
#include "personagem.h"
#include "interface.h"
#include "util.h"

/* monta as 3 fases com historia, missao e monstros (a dificuldade cresce com o fator) */
void criarFases(Fase fases[]) {
    char nomes[NUM_FASES][30] = {"Floresta Congelada", "Lago dos Mortos", "Montanha do Trono"};
    char descricoes[NUM_FASES][400] = {
        "Os pinheiros estao cobertos de gelo e os mortos andam entre eles.\n"
        "Um troll guarda a unica saida da floresta e nenhum viajante voltou para contar.\n"
        "Alem dela fica o Lago dos Mortos, de onde dizem que o frio nasce.",
        "O lago virou um tumulo de gelo e as almas dos afogados vagam sobre ele.\n"
        "Sob a superficie, algo enorme se move: Jormungandr, a serpente que cerca o mundo.\n"
        "So depois dela se enxerga a montanha onde Baldur espera.",
        "No alto da montanha fica o trono de Baldur, o deus que nenhuma arma consegue ferir.\n"
        "Gigantes de gelo e guerreiros eternos guardam o caminho.\n"
        "Aqui termina a jornada: derrotar Baldur e a unica chance de acabar com o inverno."
    };
    char missoes[NUM_FASES][100] = {"Derrotar o Troll da Montanha", "Derrotar Jormungandr", "Derrotar Baldur"};
    double fatores[NUM_FASES] = {1.0, 1.3, 1.6};
    char nomesMonstro[NUM_FASES][NUM_MONSTROS][30] = {
        {"Draugr", "Lobo Gelado", "Troll da Montanha"},
        {"Anao Sombrio", "Valquiria Caida", "Jormungandr"},
        {"Gigante de Gelo", "Guerreiro Eterno", "Baldur"}
    };
    char descMonstro[NUM_FASES][NUM_MONSTROS][100] = {
        {"Guerreiro morto que se recusa a descansar.", "Lobo de pelo branco que caca em bando.", "Gigante de pedra que bloqueia a saida da floresta."},
        {"Ferreiro corrompido que ataca das sombras.", "Guerreira alada que perdeu a honra.", "Serpente colossal que cerca o mundo."},
        {"Gigante de gelo que nunca sente o frio.", "Soldado de Baldur que nao conhece a derrota.", "Deus imortal que nenhuma arma consegue ferir."}
    };
    /* vida, ataque, defesa, xp */
    int valores[NUM_FASES][NUM_MONSTROS][4] = {
        {{25, 4, 3, 20}, {30, 5, 4, 30}, {55, 7, 5, 60}},
        {{30, 6, 5, 35}, {38, 7, 6, 45}, {70, 9, 7, 80}},
        {{36, 7, 7, 50}, {42, 8, 8, 55}, {75, 10, 9, 150}}
    };
    int i, j;

    for (i = 0; i < NUM_FASES; i++) {
        strcpy(fases[i].nome, nomes[i]);
        strcpy(fases[i].descricao, descricoes[i]);
        strcpy(fases[i].missao, missoes[i]);
        fases[i].fator = fatores[i];
        for (j = 0; j < NUM_MONSTROS; j++) {
            Monstro *m = &fases[i].monstros[j];
            strcpy(m->nome, nomesMonstro[i][j]);
            strcpy(m->descricao, descMonstro[i][j]);
            m->vida = (int) ceil(valores[i][j][0] * fatores[i]);
            m->ataque = (int) ceil(valores[i][j][1] * fatores[i]);
            m->defesa = valores[i][j][2];
            m->xpRecompensa = valores[i][j][3];
        }
    }
}

/* devolve 1 se o heroi venceu a fase */
int jogarFase(Personagem *p, Fase *f, int numFase) {
    TipoCasa tabuleiro[TAM_TABULEIRO] = {
        CASA_VAZIA, CASA_COMBATE, CASA_COMBATE, CASA_TESOURO, CASA_COMBATE, CASA_CURA,
        CASA_ARMADILHA, CASA_COMBATE, CASA_VAZIA, CASA_TESOURO, CASA_VAZIA, CASA_MISSAO
    };
    int pos = 0, dado, venceu = 0;

    printf("\nFASE %d - %s\n\n%s\n\nMissao: %s\n", numFase, f->nome, f->descricao, f->missao);
    pausar();

    while (!venceu && p->vida > 0) {
        mostrarPersonagem(p); /* status atualizado a cada lance */
        printf("Casa %d de %d\n[1] Rolar dado\n", pos + 1, TAM_TABULEIRO);
        lerOpcao(1, 1);
        dado = rolarDado(6);
        pos += dado;
        if (pos > TAM_TABULEIRO - 1)
            pos = TAM_TABULEIRO - 1;
        printf("Dado: %d. Voce chega na casa %d.\n", dado, pos + 1);
        venceu = executarEvento(p, f, numFase, tabuleiro[pos]);
    }
    return venceu;
}

/* devolve 1 se o chefe foi derrotado */
int executarEvento(Personagem *p, Fase *f, int numFase, TipoCasa tipo) {
    switch (tipo) {
    case CASA_VAZIA:
        printf("Apenas neve e silencio.\n");
        break;
    case CASA_COMBATE:
        combate(p, f->monstros[rand() % 2]); /* chefe so na ultima casa */
        break;
    case CASA_TESOURO:
        printf("Voce encontra um tesouro!\n");
        if (rand() % 2 == 0) ganharXP(p, 30);
        else aplicarBonusAleatorio(p);
        break;
    case CASA_CURA:
        curar(p, p->vidaMax * 40 / 100);
        printf("Uma fonte sagrada. Vida: %d/%d\n", p->vida, p->vidaMax);
        break;
    case CASA_ARMADILHA:
        receberDano(p, 5 + 3 * numFase);
        printf("Armadilha! Voce perde %d de vida.\n", 5 + 3 * numFase);
        break;
    case CASA_MISSAO:
        printf("O chefe da fase te espera!\n");
        return combate(p, f->monstros[2]);
    }
    return 0;
}
