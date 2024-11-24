#include "jogo_da_velha.h"

void inicializarTabuleiro(float tabuleiro[TAM][TAM][TAM+1]);
void exibirTabuleiro(float tabuleiro[TAM][TAM][TAM+1]);
void realizarJogada(float tabuleiro[TAM][TAM][TAM+1], int* jogador, float* x, float* y, float x_inicial, float z_inicial);
bool verificarVencedor(float tabuleiro[TAM][TAM][TAM+1], float simbolo);
bool verificarEmpate(float tabuleiro[TAM][TAM][TAM+1]);

void inicializarTabuleiro(float tabuleiro[TAM][TAM][TAM+1]) {
    float aux_x = PONTO_INICIAL_X;
    float aux_y = PONTO_INICIAL_Y;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j][0] = aux_x;
            tabuleiro[i][j][1] = 0.0;
            tabuleiro[i][j][2] = aux_y;
            tabuleiro[i][j][3] = 0.0;
            
            aux_y += LADO;
        }
        aux_x += LADO; 
        aux_y = PONTO_INICIAL_Y;
    }
}

void realizarJogada(float tabuleiro[TAM][TAM][TAM+1], int* jogador, float* x, float* z, float x_inicial, float z_inicial) {
    int pos_tab_x = -1, pos_tab_z = -1;
    
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (i + 1 <= TAM - 1 && j + 1 <= TAM - 1) {
                if (*x >= tabuleiro[i][j][0] && *x <= tabuleiro[i + 1][j][0] && *z >= tabuleiro[i][j][2] && *z <= tabuleiro[i][j + 1][2]) {
                    pos_tab_x = i;
                    pos_tab_z = j;
                    break;
                }
            } else {
                if (*x >= tabuleiro[i][j][0] && *x <= tabuleiro[i][j][0] + LADO && *z >= tabuleiro[i][j][2] && *z <= tabuleiro[i][j][2] + LADO) {
                    pos_tab_x = i;
                    pos_tab_z = j;
                    break;
                }
            }
        }
        if (pos_tab_z != -1 || pos_tab_x != -1) break;
    }

    if ((int)tabuleiro[pos_tab_x][pos_tab_z][3] == 0) {
        // Atualizar a jogada
        *x = PONTO_INICIAL_X + pos_tab_x * LADO + LADO / 2;
        *z = PONTO_INICIAL_Y + pos_tab_z * LADO + LADO / 2;

        tabuleiro[pos_tab_x][pos_tab_z][3] = *jogador;
    }
    else{
        *x = x_inicial;
        *z = z_inicial;
    }
}

bool verificarVencedor(float tabuleiro[TAM][TAM][TAM+1], float simbolo) {
    for (int i = 0; i < TAM; i++) {
        bool venceu = true;
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j][3] != simbolo) {
                venceu = false;
                break;
            }
        }
        if (venceu) return true;
    }

    for (int j = 0; j < TAM; j++) {
        bool venceu = true;
        for (int i = 0; i < TAM; i++) {
            if (tabuleiro[i][j][3] != simbolo) {
                venceu = false;
                break;
            }
        }
        if (venceu) return true;
    }

    bool venceuDiagonal = true;
    for (int i = 0; i < TAM; i++) {
        if (tabuleiro[i][i][3] != simbolo) {
            venceuDiagonal = false;
            break;
        }
    }
    if (venceuDiagonal) return true;

    venceuDiagonal = true;
    for (int i = 0; i < TAM; i++) {
        if (tabuleiro[i][TAM - 1 - i][3] != simbolo) {
            venceuDiagonal = false;
            break;
        }
    }
    return venceuDiagonal;
}

bool verificarEmpate(float tabuleiro[TAM][TAM][TAM+1]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j][3] == 0.0) {
                return false;
            }
        }
    }
    return true;
}