#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/* le um numero entre min e max e pergunta de novo se estiver errado */
int lerOpcao(int min, int max) {
    int op, lido;
    while (1) {
        printf("Sua escolha: ");
        lido = scanf("%d", &op);
        if (lido == EOF)
            exit(0);
        limparBuffer();
        if (lido == 0) {
            printf("Digite um numero: \n");
        } else if (op < min || op > max) {
            printf("Opcao invalida. Escolha de %d a %d.\n", min, max);
        } else {
            return op;
        }
    }
}

/* joga fora o que sobrou na linha digitada (inclusive o ENTER) */
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* espera o jogador apertar ENTER */
void pausar(void) {
    printf("\n(pressione ENTER para continuar)");
    getchar();
}

/* sorteia um numero de 1 ate o numero de lados */
int rolarDado(int lados) {
    return rand() % lados + 1;
}
