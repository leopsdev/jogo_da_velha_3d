#include "jogo_da_velha.h"



void inicializarTabuleiro(float tabuleiro[TAM][TAM][TAM+1]);
void exibirTabuleiro(float tabuleiro[TAM][TAM][TAM+1]);
void realizarJogada(float tabuleiro[TAM][TAM][TAM+1], int jogador, float* x, float* y);
bool verificarVencedor(float tabuleiro[TAM][TAM][TAM+1], float simbolo);
bool verificarEmpate(float tabuleiro[TAM][TAM][TAM+1]);

// int main() {
//     float tabuleiro[TAM][TAM][TAM+1];
//     int jogadorAtual = 1;
//     bool jogoAtivo = true;
//     float x, y;

//     inicializarTabuleiro(tabuleiro);

//     while (jogoAtivo) {
//         exibirTabuleiro(tabuleiro);
//         printf("\nJogador %d, insira as coordenadas (x y): ", jogadorAtual);
//         scanf("%f %f", &x, &y);

//         realizarJogada(tabuleiro, jogadorAtual, &x, &y);

//         if (verificarVencedor(tabuleiro, jogadorAtual)) {
//             exibirTabuleiro(tabuleiro);
//             printf("\nJogador %d venceu!\n", jogadorAtual);
//             jogoAtivo = false;
//             break;
//         }

//         if (verificarEmpate(tabuleiro)) {
//             exibirTabuleiro(tabuleiro);
//             printf("\nO jogo terminou em empate!\n");
//             jogoAtivo = false;
//             break;
//         }

//         jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
//     }

//     return 0;
// }

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

void realizarJogada(float tabuleiro[TAM][TAM][TAM+1], int jogador, float* x, float* z) {
    int pos_tab_x = -1, pos_tab_z = -1;
    
    while (true) {
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

        // Verificar se a posição está ocupada
        if ((int)tabuleiro[pos_tab_x][pos_tab_z][3] != 0) {
            printf("Posição já ocupada! Insira novas coordenadas (x y): ");
            scanf("%f %f", x, z);
            pos_tab_x = -1;
            pos_tab_z = -1;
        } else {
            break;
        }
    }

    // Atualizar a jogada
    *x = PONTO_INICIAL_X + pos_tab_x * LADO + LADO / 2;
    *z = PONTO_INICIAL_Y + pos_tab_z * LADO + LADO / 2;

    tabuleiro[pos_tab_x][pos_tab_z][3] = jogador;
}


void exibirTabuleiro(float tabuleiro[TAM][TAM][TAM+1]) {
    for (int i = 0; i < TAM; i++) for (int j = 0; j < TAM; j++) printf(" %f ", tabuleiro[i][j][3]);
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