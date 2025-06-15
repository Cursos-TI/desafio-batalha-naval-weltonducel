#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10
#define NAVIO 3
#define AGUA 0

// Função para verificar se a posição está dentro dos limites
int dentroDoTabuleiro(int linha, int coluna) {
    return linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM;
}

// Verifica se é possível posicionar o navio sem sobreposição
int podePosicionar(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, int direcao, int diagonal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;
        if (diagonal == 1) {          // Diagonal principal
            l = linha + i;
            c = coluna + i;
        } else if (diagonal == 2) {   // Diagonal secundária
            l = linha + i;
            c = coluna - i;
        } else {
            if (direcao == 0) c = coluna + i;  // Horizontal
            else l = linha + i;                // Vertical
        }

        if (!dentroDoTabuleiro(l, c) || tabuleiro[l][c] != AGUA)
            return 0;
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, int direcao, int diagonal) {
    for (int i = 0; i < tamanho; i++) {
        int l = linha, c = coluna;
        if (diagonal == 1) {
            l = linha + i;
            c = coluna + i;
        } else if (diagonal == 2) {
            l = linha + i;
            c = coluna - i;
        } else {
            if (direcao == 0) c = coluna + i;
            else l = linha + i;
        }
        tabuleiro[l][c] = NAVIO;
    }
}

// Função para tentar colocar todos os navios
int posicionarNavios(int tabuleiro[TAM][TAM], int tentativas) {
    int naviosColocados = 0;

    // Tentativa de posicionar 2 navios horizontais/verticais
    int posicoesHorizVert[][4] = {
        {1, 2, 4, 0},   // Linha, Coluna, Tamanho, Direção (0=horizontal, 1=vertical)
        {5, 5, 3, 1}
    };

    for (int i = 0; i < 2; i++) {
        int l = posicoesHorizVert[i][0];
        int c = posicoesHorizVert[i][1];
        int tamanho = posicoesHorizVert[i][2];
        int direcao = posicoesHorizVert[i][3];
        if (podePosicionar(tabuleiro, l, c, tamanho, direcao, 0)) {
            posicionarNavio(tabuleiro, l, c, tamanho, direcao, 0);
            naviosColocados++;
        }
    }

    // Tentativa de posicionar 2 navios diagonais
    int posicoesDiagonais[][4] = {
        {0, 0, 3, 1},   // Diagonal principal
        {0, 9, 3, 2}    // Diagonal secundária
    };

    for (int i = 0; i < 2; i++) {
        int l = posicoesDiagonais[i][0];
        int c = posicoesDiagonais[i][1];
        int tamanho = posicoesDiagonais[i][2];
        int tipoDiagonal = posicoesDiagonais[i][3];
        if (podePosicionar(tabuleiro, l, c, tamanho, 0, tipoDiagonal)) {
            posicionarNavio(tabuleiro, l, c, tamanho, 0, tipoDiagonal);
            naviosColocados++;
        }
    }

    return naviosColocados;
}

int main() {
    int tabuleiro[TAM][TAM] = {0};
    
    // Inicializa o número de tentativas e navios colocados
    int tentativas = 0;
    int naviosColocados = 0;

    // Tentativas para posicionar todos os navios
    while (naviosColocados < 4 && tentativas < 100) {
        naviosColocados = posicionarNavios(tabuleiro, tentativas);
        tentativas++;
    }

    // Verifica se conseguimos posicionar todos os navios
    if (naviosColocados < 4) {
        printf("Erro: Não foi possível posicionar todos os navios após %d tentativas.\n", tentativas);
        return 1;
    }

    // Exibe o tabuleiro
    printf("Tabuleiro Batalha Naval:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
