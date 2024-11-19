#include "objeto.h"
#include <stdio.h>
#include <math.h>

Object objects[12];   // Inicialização do array de objetos
int objectCount = 0;  // Inicialização do contador de objetos

void addObject(float x, float y, float z, float r, float g, float b, float sizeOrRadius, int type) {
    if (objectCount >= 12) {
        printf("Limite de objetos atingido!\n");
        return;
    }
    objects[objectCount].id = objectCount;
    objects[objectCount].x = x;
    objects[objectCount].y = y;
    objects[objectCount].z = z;
    objects[objectCount].color[0] = r;
    objects[objectCount].color[1] = g;
    objects[objectCount].color[2] = b;
    objects[objectCount].color[3] = 1.0f;
    objects[objectCount].sizeOrRadius = sizeOrRadius;
    objects[objectCount].type = type;
    objects[objectCount].isSelected = 0; // Inicialmente não selecionado
    objectCount++;
}

void selectObject(float mouseX, float mouseY) {
    for (int i = 0; i < objectCount; i++) {
        if (fabs(mouseX - objects[i].x) < 0.2f && fabs(mouseY - objects[i].y) < 0.2f) {
            objects[i].isSelected = 1; // Marca o objeto como selecionado
            objects->color[0] = 0.0f;
            objects->color[1] = 0.0f;
            objects->color[2] = 1.0f;
            printf("Objeto %d selecionado\n", objects[i].id);
        } else {
            objects[i].isSelected = 0; // Desmarca os outros objetos
        }
    }
}

void translateSelectedObject(float dx, float dy, float dz) {
    for (int i = 0; i < objectCount; i++) {
        if (objects[i].isSelected) {
            objects[i].x += dx;
            objects[i].y += dy;
            objects[i].z += dz;
            printf("Objeto %d transladado para (%f, %f, %f)\n", 
                   objects[i].id, objects[i].x, objects[i].y, objects[i].z);
        }
    }
}
