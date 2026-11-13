#include <stdio.h>
#include "interface.h"
#include "personagem.h"

/* mostra a ficha do heroi na tela */
void mostrarPersonagem(Personagem *p) {
    printf("-----------------------------------------------------------");
    printf("\n%s, o %s\n", p->nome, nomeClasse(p->classe));
    printf("Nivel: %d   XP: %d/%d\n", p->nivel, p->xp, p->nivel * 50);
    printf("Vida: %d/%d\n", p->vida, p->vidaMax);
    printf("Forca: %d   Defesa: %d   Agilidade: %d   Inteligencia: %d\n",
           p->forca, p->defesa, p->agilidade, p->inteligencia);
    printf("Arma: %s (+%d)   Armadura: %s (+%d)\n",
           p->arma, p->bonusArma, p->armadura, p->bonusArmadura);
    printf("Habilidade: %s\n", p->habilidade);
    printf("-----------------------------------------------------------\n");
}

/* mostra o nome, a descricao e os atributos do monstro */
void mostrarMonstro(Monstro *m) {
    printf("\n======== STATUS DO MONSTRO ===============");
    printf("\n%s - %s\n", m->nome, m->descricao);
    printf("Vida %d | Ataque %d | Defesa %d\n", m->vida, m->ataque, m->defesa);
}

/* mostra as 3 classes para o jogador escolher */
void exibirMenuPersonagens(void) {
    printf("\nEscolha quem vai enfrentar o inverno:\n\n");
    printf("[1] Guerreiro - Vida 120 | For 12 | Def 10 | Agi 8  | Int 4\n");
    printf("    Machado de Gelo (+3), Couro Rustico (+2). Habilidade: Furia Gelada\n");
    printf("[2] Arqueiro  - Vida 105 | For 8  | Def 8  | Agi 14 | Int 6\n");
    printf("    Arco de Freixo (+4), Capa de Pele de Lobo (+1). Habilidade: Flecha Certeira\n");
    printf("[3] Runista   - Vida 100 | For 5  | Def 8  | Agi 8  | Int 14\n");
    printf("    Cajado de Runas (+4), Manto Runico (+1). Habilidade: Runa da Vida\n\n");
}
