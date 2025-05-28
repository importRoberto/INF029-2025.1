#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 10
#define MAX_NAVIOS 7

// Configuração dos navios
const int TAM_NAVIOS[MAX_NAVIOS] = {4, 3, 1, 1, 1, 2, 2}; // 1x4, 1x3, 3x1, 2x2

char tabuleiro1[TAM][TAM];
char tabuleiro2[TAM][TAM];
char tiros1[TAM][TAM];
char tiros2[TAM][TAM];

void inicializarTabuleiros() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro1[i][j] = ' ';
            tabuleiro2[i][j] = ' ';
            tiros1[i][j] = ' ';
            tiros2[i][j] = ' ';
        }
    }
}

void imprimirTabuleiro(char tabuleiro[TAM][TAM], int ocultarNavios) {
    printf("   ");
    for (int i = 0; i < TAM; i++) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < TAM; i++) {
        printf("%c  ", 'A' + i);
        for (int j = 0; j < TAM; j++) {
            char c = tabuleiro[i][j];
            if (ocultarNavios && c == 'N')
                printf("  ");
            else
                printf("%c ", c);
        }
        printf("\n");
    }
}

int verificarEspaco(char tabuleiro[TAM][TAM], int x, int y, int tamanho, char direcao) {
    if (direcao == 'H') {
        if (y + tamanho > TAM) return 0;
        for (int i = 0; i < tamanho; i++)
            if (tabuleiro[x][y + i] != ' ') return 0;
    } else {
        if (x + tamanho > TAM) return 0;
        for (int i = 0; i < tamanho; i++)
            if (tabuleiro[x + i][y] != ' ') return 0;
    }
    return 1;
}

void posicionarNavio(char tabuleiro[TAM][TAM], int tamanho) {
    int x, y;
    char linha, direcao;
    do {
        printf("Posicione navio de tamanho %d (ex: A0 H): ", tamanho);
        scanf(" %c%d %c", &linha, &y, &direcao);
        x = toupper(linha) - 'A';
        direcao = toupper(direcao);
    } while (x < 0 || x >= TAM || y < 0 || y >= TAM ||
             (direcao != 'H' && direcao != 'V') ||
             !verificarEspaco(tabuleiro, x, y, tamanho, direcao));

    for (int i = 0; i < tamanho; i++) {
        if (direcao == 'H') tabuleiro[x][y + i] = 'N';
        else tabuleiro[x + i][y] = 'N';
    }
}

int atacar(char tabuleiro[TAM][TAM], char tiros[TAM][TAM], int jogador) {
    int x, y;
    char linha;
    do {
        printf("Jogador %d, digite coordenada de ataque (ex: A0): ", jogador);
        scanf(" %c%d", &linha, &y);
        x = toupper(linha) - 'A';
    } while (x < 0 || x >= TAM || y < 0 || y >= TAM || tiros[x][y] != ' ');

    if (tabuleiro[x][y] == 'N') {
        printf("Acertou um navio!\n");
        tiros[x][y] = '0';
        tabuleiro[x][y] = '0';
        return 1;
    } else {
        printf("Errou o tiro.\n");
        tiros[x][y] = 'X';
        return 0;
    }
}

int contarAcertos(char tabuleiro[TAM][TAM]) {
    int acertos = 0;
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tabuleiro[i][j] == '0')
                acertos++;
    return acertos;
}

int totalPecas() {
    int total = 0;
    for (int i = 0; i < MAX_NAVIOS; i++)
        total += TAM_NAVIOS[i];
    return total;
}

int main() {
    inicializarTabuleiros();
    printf("--- Jogador 1, posicione seus navios ---\n");
    for (int i = 0; i < MAX_NAVIOS; i++) {
        imprimirTabuleiro(tabuleiro1, 0);
        posicionarNavio(tabuleiro1, TAM_NAVIOS[i]);
    }

    printf("\n--- Jogador 2, posicione seus navios ---\n");
    for (int i = 0; i < MAX_NAVIOS; i++) {
        imprimirTabuleiro(tabuleiro2, 0);
        posicionarNavio(tabuleiro2, TAM_NAVIOS[i]);
    }

    int turno = 1;
    int max_acertos = totalPecas();
    while (1) {
        printf("\n---------------------------\n");
        printf("Tabuleiro do Jogador 1:\n");
        imprimirTabuleiro(tabuleiro1, 0);
        printf("Seus tiros no inimigo:\n");
        imprimirTabuleiro(tiros1, 0);

        printf("\nTabuleiro do Jogador 2:\n");
        imprimirTabuleiro(tabuleiro2, 0);
        printf("Seus tiros no inimigo:\n");
        imprimirTabuleiro(tiros2, 0);

        if (turno == 1) {
            if (atacar(tabuleiro2, tiros1, 1) && contarAcertos(tabuleiro2) == max_acertos) {
                printf("\nJogador 1 venceu!\n");
                break;
            }
            turno = 2;
        } else {
            if (atacar(tabuleiro1, tiros2, 2) && contarAcertos(tabuleiro1) == max_acertos) {
                printf("\nJogador 2 venceu!\n");
                break;
            }
            turno = 1;
        }
    }

    return 0;
}
