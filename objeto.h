#ifndef OBJETO_H
#define OBJETO_H
#include <stdbool.h>
#define BUFSIZE 512

// Identificador de objetos
enum {OBJ_CUBE = 1, OBJ_SPHERE = 2};

typedef struct {
    int id;         // Identificador único do objeto
    int type;       // Tipo de objeto (1 = cubo, 2 = esfera)
    float x, y, z;  // Coordenadas do objeto
    float color[4]; // Cor do objeto
    float colorOG[4];
    float sizeOrRadius; // Tamanho ou raio do objeto
    int isSelected; // Indica se o objeto está selecionado (1 = sim, 0 = não)
    int movido; // 0 = nao movido, 1 = movido
    float x_inicial;
    float z_inicial;
} Object;

extern Object objects[12]; // Declaração de um array de objetos
extern int objectCount;    // Declaração do número de objetos
// Variáveis de controle de seleção e arraste


void addObject(float x, float y, float z, float r, float g, float b, float sizeOrRadius, int type, int movido);
void translateSelectedObject(float dx, float dy, float dz);


#endif
