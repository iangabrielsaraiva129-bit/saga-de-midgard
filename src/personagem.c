#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personagem.h"
#include "interface.h"
#include "util.h"

/* devolve o nome da classe como texto */
char *nomeClasse(ClassePersonagem classe) {
    switch (classe) {
        case GUERREIRO: return "Guerreiro";
        case ARQUEIRO:  return "Arqueiro";
        default:        return "Runista";
    }
}

/* mostra o menu e devolve a classe escolhida */
ClassePersonagem escolherPersonagem(void) {
    exibirMenuPersonagens();
    return (ClassePersonagem) (lerOpcao(1, 3) - 1);
}

/* pergunta o nome do heroi; se so apertar ENTER vira "Exilado" */
void escolherNome(Personagem *p) {
    char nome[30];

    printf("Como se chama, exilado? ");
    if (fgets(nome, sizeof(nome), stdin) == NULL)
        exit(0);
    if (strchr(nome, '\n') == NULL)
        limparBuffer();
    nome[strcspn(nome, "\n")] = '\0';
    if (strlen(nome) > 0)
        strcpy(p->nome, nome);
    else
        strcpy(p->nome, "Exilado");
}

/* preenche os atributos iniciais de acordo com a classe */
void criarPersonagem(Personagem *p, ClassePersonagem classe) {
    p->classe = classe;
    p->xp = 0;
    p->nivel = 1;
    switch (classe) {
        case GUERREIRO:
            strcpy(p->nome, "Guerreiro");
            p->vidaMax = 120; p->forca = 12; p->defesa = 10; p->agilidade = 8; p->inteligencia = 4;
            strcpy(p->arma, "Machado de Gelo"); p->bonusArma = 3;
            strcpy(p->armadura, "Couro Rustico"); p->bonusArmadura = 2;
            strcpy(p->habilidade, "Furia Gelada");
            break;
        case ARQUEIRO:
            strcpy(p->nome, "Arqueiro");
            p->vidaMax = 105; p->forca = 8; p->defesa = 8; p->agilidade = 14; p->inteligencia = 6;
            strcpy(p->arma, "Arco de Freixo"); p->bonusArma = 4;
            strcpy(p->armadura, "Capa de Pele de Lobo"); p->bonusArmadura = 1;
            strcpy(p->habilidade, "Flecha Certeira");
            break;
        case RUNISTA:
            strcpy(p->nome, "Runista");
            p->vidaMax = 100; p->forca = 5; p->defesa = 8; p->agilidade = 8; p->inteligencia = 14;
            strcpy(p->arma, "Cajado de Runas"); p->bonusArma = 4;
            strcpy(p->armadura, "Manto Runico"); p->bonusArmadura = 1;
            strcpy(p->habilidade, "Runa da Vida");
            break;
    }
    p->vida = p->vidaMax;
}

/* tira vida do heroi, sem deixar ficar negativa */
void receberDano(Personagem *p, int dano) {
    p->vida -= dano;
    if (p->vida < 0)
        p->vida = 0;
}

/* devolve vida ao heroi, sem passar da vida maxima */
void curar(Personagem *p, int valor) {
    p->vida += valor;
    if (p->vida > p->vidaMax)
        p->vida = p->vidaMax;
}

/* soma o XP e sobe de nivel enquanto tiver XP suficiente */
void ganharXP(Personagem *p, int xp) {
    p->xp += xp;
    printf("Voce ganha %d de XP.\n", xp);
    while (p->xp >= p->nivel * 50) {
        p->xp -= p->nivel * 50;
        p->nivel++;
        p->vidaMax += 10;
        curar(p, 10);
        p->forca++;
        p->defesa++;
        printf("Subiu para o nivel %d!\n", p->nivel);
    }
}

/* sorteia um atributo e aumenta (ou a vida maxima) */
void aplicarBonusAleatorio(Personagem *p) {
    switch (rand() % 5) {
    case 0: p->forca++;        printf("Bonus: forca +1\n"); break;
    case 1: p->defesa++;       printf("Bonus: defesa +1\n"); break;
    case 2: p->agilidade++;    printf("Bonus: agilidade +1\n"); break;
    case 3: p->inteligencia++; printf("Bonus: inteligencia +1\n"); break;
    case 4: p->vidaMax += 5;   printf("Bonus: vida maxima +5\n"); break;
    }
}
