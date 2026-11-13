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

    srand((unsigned) time(NULL));
    printf("\n           SAGA DE MIDGARD\n\n");
    printf("O Fimbulvetr chegou. O inverno eterno cobriu os nove reinos.\n");
    printf("O sol nao nasce. Os rios viraram pedra. Os homens morrem de frio.\n");
    printf("Voce e um guerreiro exilado, sem cla e sem nome nas sagas.\n");
    printf("Dizem que o Visco Sagrado pode quebrar o inverno.\n");
    printf("Mas ele esta com Baldur, o deus que nenhuma arma consegue ferir.\n");
    printf("Atravesse Midgard. Reuna os objetos sagrados. Enfrente os guardioes.\n");

    criarPersonagem(&heroi, escolherPersonagem());
    escolherNome(&heroi);
    criarFases(fases);
    for (i = 0; i < NUM_FASES && vivo; i++)
        vivo = jogarFase(&heroi, &fases[i], i + 1);

    if (vivo)
        printf("\nVITORIA! Baldur caiu e o inverno eterno acabou.\n");
    else
        printf("\nGAME OVER. Midgard continua congelada.\n");
    printf("\nResumo do heroi:");
    mostrarPersonagem(&heroi);
    return 0;
}
