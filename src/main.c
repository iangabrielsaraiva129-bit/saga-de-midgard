#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tipos.h"
#include "interface.h"
#include "personagem.h"
#include "fases.h"

int main() {
    Personagem heroi;
    Fase fases[NUM_FASES];
    int i, vivo = 1;

    /* muda a semente do sorteio a cada partida */
    srand((unsigned) time(NULL));

    /* historia de abertura */
    printf("\n           SAGA DE MIDGARD\n\n");
    printf("O Fimbulvetr chegou. O inverno eterno cobriu os nove reinos.\n");
    printf("O sol nao nasce. Os rios viraram pedra. Os homens morrem de frio.\n");
    printf("Voce e um guerreiro exilado, sem cla e sem nome nas sagas.\n");
    printf("Dizem que o Visco Sagrado pode quebrar o inverno.\n");
    printf("Mas ele esta com Baldur, o deus que nenhuma arma consegue ferir.\n");
    printf("Atravesse Midgard, enfrente os guardioes e derrote Baldur.\n");

    /* escolha da classe, do nome e montagem das 3 fases */
    criarPersonagem(&heroi, escolherPersonagem());
    escolherNome(&heroi);
    criarFases(fases);

    /* joga uma fase por vez; para se o heroi morrer */
    for (i = 0; i < NUM_FASES && vivo; i++)
        vivo = jogarFase(&heroi, &fases[i], i + 1);

    /* final do jogo */
    if (vivo)
        printf("\nVITORIA! Baldur caiu e o inverno eterno acabou.\n");
    else
        printf("\nGAME OVER. Midgard continua congelada.\n");
    printf("\nResumo do heroi:");
    mostrarPersonagem(&heroi);
    return 0;
}
