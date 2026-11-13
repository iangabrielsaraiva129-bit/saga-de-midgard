#include <stdio.h>
#include "combate.h"
#include "personagem.h"
#include "interface.h"
#include "util.h"

/* d20 + atributo da classe + bonus da arma */
int calcularAtaque(Personagem *p) {
    int atributo = p->forca;
    if (p->classe == ARQUEIRO)
        atributo = p->agilidade;
    else if (p->classe == RUNISTA)
        atributo = p->inteligencia;
    return rolarDado(20) + atributo + p->bonusArma;
}

/* ataque menos defesa, e nunca menos que 1 */
int calcularDano(int ataque, int defesa) {
    int dano = ataque - defesa;
    return dano < 1 ? 1 : dano;
}

/* tira vida do monstro, sem deixar ficar negativa */
void danoNoMonstro(Monstro *m, int dano) {
    m->vida -= dano;
    if (m->vida < 0)
        m->vida = 0;
}

/* recebe uma copia do monstro; devolve 1 se venceu */
int combate(Personagem *p, Monstro m) {
    int acao, dano, defendendo, usouHabilidade = 0;

    printf("\n%s aparece!\n", m.nome);
    while (m.vida > 0 && p->vida > 0) {
        mostrarPersonagem(p);
        mostrarMonstro(&m);
        printf("\n[1] Atacar [2] Defender [3] Habilidade [4] Fugir\n");
        acao = lerOpcao(1, 4);
        if (acao == ACAO_HABILIDADE && usouHabilidade) {
            printf("Habilidade ja usada neste combate.\n");
            continue;
        }
        defendendo = 0;
        dano = 0;
        switch (acao) {
        case ACAO_ATACAR:
            dano = calcularDano(calcularAtaque(p), m.defesa);
            break;
        case ACAO_DEFENDER:
            defendendo = 1;
            printf("Voce ergue a guarda.\n");
            break;
        case ACAO_HABILIDADE:
            usouHabilidade = 1;
            printf("%s!\n", p->habilidade);
            if (p->classe == GUERREIRO)
                dano = calcularDano(calcularAtaque(p), m.defesa) * 2;
            else if (p->classe == ARQUEIRO)
                dano = calcularAtaque(p); /* ignora a defesa */
            else
                curar(p, p->inteligencia * 2);
            break;
        case ACAO_FUGIR:
            if (rolarDado(6) >= 4) {
                printf("Voce fugiu!\n");
                return 0;
            }
            printf("Nao conseguiu fugir.\n");
            break;
        }
        if (dano > 0) {
            danoNoMonstro(&m, dano);
            printf("Voce causa %d de dano.\n", dano);
        }
        if (m.vida <= 0)
            break;

        /* turno do monstro */
        dano = calcularDano(rolarDado(20) + m.ataque, p->defesa + p->bonusArmadura);
        if (defendendo)
            dano = calcularDano(dano / 2, 0); /* metade, minimo 1 */
        receberDano(p, dano);
        printf("%s causa %d de dano.\n", m.nome, dano);
    }

    if (p->vida <= 0) {
        printf("Voce foi derrotado por %s.\n", m.nome);
        return 0;
    }
    printf("%s foi derrotado!\n", m.nome);
    ganharXP(p, m.xpRecompensa);
    aplicarBonusAleatorio(p);
    return 1;
}
