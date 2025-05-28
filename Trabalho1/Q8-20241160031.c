#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char match[3][3];

void inicializar() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            match[i][j] = ' ';
}


void imprimirTabuleiro() {
    printf("\n   1   2   3\n\n");
    printf("A  %c | %c | %c \n", match[0][0], match[0][1], match[0][2]);
    printf("  ---|---|---\n");
    printf("B  %c | %c | %c \n", match[1][0], match[1][1], match[1][2]);
    printf("  ---|---|---\n");
    printf("C  %c | %c | %c \n\n", match[2][0], match[2][1], match[2][2]);
}


int checkVitoria(char x) {
    for (int i = 0; i < 3; i++) {
        if (match[i][0] == x && match[i][1] == x && match[i][2] == x) return 1;
        if (match[0][i] == x && match[1][i] == x && match[2][i] == x) return 1;
    }
    if (match[0][0] == x && match[1][1] == x && match[2][2] == x) return 1;
    if (match[0][2] == x && match[1][1] == x && match[2][0] == x) return 1;

    return 0;
}


int checkEmpate() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (match[i][j] == ' ')
                return 0;
    return 1;
}


int converter(char linha, int coluna, int* lin, int* col) {
    linha = toupper(linha);
    if (linha < 'A' || linha > 'C' || coluna < 1 || coluna > 3) {
        return 0;
    }
    *lin = linha - 'A';
    *col = coluna - 1;
    return 1;
}

int main() {
    int jogador = 1;
    char x;
    char linha;
    int coluna;
    int lin, col;
    int fim_match = 0;

    inicializar();

    while (!fim_match) {
        imprimirTabuleiro();

        x = (jogador % 2 == 1) ? 'X' : 'O';
        printf("Jogador %d (%c), digite sua jogada (ex: A1, B3): ", jogador, x);
        scanf(" %c%d", &linha, &coluna);

        if (!converter(linha, coluna, &lin, &col)) {
            printf("Entrada invalida! Tente novamente.\n\n");
            continue;
        }

        if (match[lin][col] != ' ') {
            printf("Posição ja ocupada! Tente novamente.\n\n");
            continue;
        }

        match[lin][col] = x;

        if (checkVitoria(x)) {
            imprimirTabuleiro();
            printf("Parabens! Jogador %d venceu!\n", jogador);
            fim_match = 1;
        } else if (checkEmpate()) {
            imprimirTabuleiro();
            printf("Empate!\n");
            fim_match = 1;
        } else {
            jogador = (jogador == 1) ? 2 : 1;
        }
    }

    return 0;
}
