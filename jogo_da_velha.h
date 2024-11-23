#ifndef JOGO_DA_VELHA_H
#define JOGO_DA_VELHA_H
#define TAM 3
#define PONTO_INICIAL_X 0.0
#define PONTO_INICIAL_Y 0.0
#define LADO 0.5

#include <stdbool.h>
#include <stdio.h> 

void inicializarTabuleiro(float tabuleiro[TAM][TAM][TAM+1]);
void realizarJogada(float tabuleiro[TAM][TAM][TAM+1], int* jogador, float* x, float* z);
void exibirTabuleiro(float tabuleiro[TAM][TAM][TAM+1]);
void exibirTabuleiro(float tabuleiro[TAM][TAM][TAM+1]);
bool verificarVencedor(float tabuleiro[TAM][TAM][TAM+1], float simbolo);
bool verificarEmpate(float tabuleiro[TAM][TAM][TAM+1]);

#endif