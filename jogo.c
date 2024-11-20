#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include "objeto.h"

// Variáveis de controle de câmera
float cameraDistance = 5.0f; // Distância da câmera
float cameraAngleX = 0.0f, cameraAngleY = 0.0f; // Ângulos de rotação
int isDragging = 0; // Estado de arrastar o mouse
int lastMouseX, lastMouseY; // Última posição do mouse

void drawCube(float x, float y, float z, float size, float r, float g, float b) {
    glPushMatrix(); // Salva a matriz atual
    glLoadName(OBJ_CUBE);
    glTranslatef(x, y, z); // Translada para a posição desejada
    float obj_kd[4] = {r, g, b, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, obj_kd);
    glutSolidCube(size); // Desenha um cubo sólido com o tamanho especificado
    glPopMatrix(); // Restaura a matriz original
}

void drawSphere(float x, float y, float z, float radius, float r, float g, float b) {
    glPushMatrix(); // Salva a matriz atual
    glLoadName(OBJ_SPHERE);
    glTranslatef(x, y, z); // Translada para a posição desejada
    float obj_kd[4] = {r, g, b, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, obj_kd);
    glutSolidSphere(radius, 20, 20); // Desenha uma esfera sólida
    glPopMatrix(); // Restaura a matriz original
}

void drawObjects() {
    for (int i = 0; i < objectCount; i++) {
        if (objects[i].type == 1) {
            drawCube(objects[i].x, objects[i].y, objects[i].z, objects[i].sizeOrRadius, objects[i].color[0], objects[i].color[1], objects[i].color[2]);
        } else if (objects[i].type == 2) {
            drawSphere(objects[i].x, objects[i].y, objects[i].z, objects[i].sizeOrRadius, objects[i].color[0], objects[i].color[1], objects[i].color[2]);
        }
    }
}


void updateCamera() {
    glLoadIdentity();
    gluLookAt(cameraDistance * sin(cameraAngleY) * cos(cameraAngleX), // Posição X da câmera
              cameraDistance * sin(cameraAngleX),                    // Posição Y da câmera
              cameraDistance * cos(cameraAngleY) * cos(cameraAngleX), // Posição Z da câmera
              0.0, 0.0, 0.0, // Ponto para onde a câmera aponta
              0.0, 1.0, 0.0); // Vetor "up"
}

void reshape(int width, int height) {
    if (height == 0) height = 1; // Evita divisão por zero

    float aspect = (float)width / (float)height; // Calcula a proporção da janela

    // Configura o viewport para cobrir toda a janela
    glViewport(0, 0, width, height);

    // Configura a projeção para manter a proporção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    updateCamera(); // Atualiza a posição da câmera
}

void mouseControl(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON) { // Clique direito para zoom
        if (state == GLUT_DOWN) {
            isDragging = 1;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            isDragging = 0;
        }
    } else if (button == GLUT_MIDDLE_BUTTON) { // Clique do meio para rotação
        if (state == GLUT_DOWN) {
            isDragging = 2;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            isDragging = 0;
        }
    } else if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            lastMouseX = x;
            lastMouseY = y;
            selectObject(lastMouseX, lastMouseY);
        }
    }
}

void mouseMotion(int x, int y) {
    if (isDragging == 1) { // Controle de zoom
        cameraDistance += (y - lastMouseY) * 0.05f; // Ajuste a velocidade se necessário
        lastMouseY = y;
    } else if (isDragging == 2) { // Controle de rotação
        cameraAngleX += (y - lastMouseY) * 0.005f;
        cameraAngleY += (x - lastMouseX) * 0.005f;
        lastMouseX = x;
        lastMouseY = y;
    }
    updateCamera();
    glutPostRedisplay(); // Redesenha a tela
}
void lighting() {
    float position[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);  //aparencia mais realista
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);  //um ponto muito expecifico

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);

    float global_ambient[4] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // fundo branco
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(  2.0, 1.0, -5.0, 
                0.0, 0.0, 0.0, 
                0.0, 1.0, 0.0);

    addObject(1.4, 0.1, 1.3, 1.0f, 0.0f, 0.0f, 0.2f, 1);
    addObject(1.1, 0.1, 1.3, 1.0f, 0.0f, 0.0f, 0.2f, 1);
    addObject(0.8, 0.1, 1.3, 1.0f, 0.0f, 0.0f, 0.2f, 1);
    addObject(0.5, 0.1, 1.3, 1.0f, 0.0f, 0.0f, 0.2f, 1);
    addObject(0.2, 0.1, 1.3, 1.0f, 0.0f, 0.0f, 0.2f, 1);
    addObject(-1.4, 0.1, 1.3, 0.0f, 1.0f, 0.0f, 0.12f, 2);
    addObject(-1.1, 0.1, 1.3, 0.0f, 1.0f, 0.0f, 0.12f, 2);
    addObject(-0.8, 0.1, 1.3, 0.0f, 1.0f, 0.0f, 0.12f, 2);
    addObject(-0.5, 0.1, 1.3, 0.0f, 1.0f, 0.0f, 0.12f, 2);
    addObject(-0.2, 0.1, 1.3, 0.0f, 1.0f, 0.0f, 0.12f, 2);
    
    lighting();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Configura material do tabuleiro
    float kd[4] = {0.8f, 0.5f, 0.2f, 0.0f};
    float ks[4] = {0.5f, 0.5f, 0.5f, 0.5f};
    float ns = 50.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    // Desenha o plano (tabuleiro)
    glBegin(GL_QUADS);
        glVertex3f(-1.7f, 0.0f, -1.7f);
        glVertex3f(1.7f, 0.0f, -1.7f);
        glVertex3f(1.7f, 0.0f, 1.7f);
        glVertex3f(-1.7f, 0.0f, 1.7f);
    glEnd();

    // Desenha as linhas do tabuleiro
    glDisable(GL_LIGHTING); // Desativa a iluminação para as linhas
    glColor3f(1.0f, 1.0f, 1.0f); // Define a cor branca para as linhas


    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glVertex3f(-1.0f, 0.01f, -0.33f);
        glVertex3f(1.0f, 0.01f, -0.33f);
        glVertex3f(-1.0f, 0.01f, 0.33f);
        glVertex3f(1.0f, 0.01f, 0.33f);
        glVertex3f(-0.33f, 0.01f, -1.0f);
        glVertex3f(-0.33f, 0.01f, 1.0f);
        glVertex3f(0.33f, 0.01f, -1.0f);
        glVertex3f(0.33f, 0.01f, 1.0f);
    glEnd();

    glEnable(GL_LIGHTING); // Reativa a iluminação

    // Desenha objetos
    drawObjects();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tabuleiro 3D - Jogo da Velha");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseControl);
    glutMotionFunc(mouseMotion);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
