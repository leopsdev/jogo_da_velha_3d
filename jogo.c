#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "objeto.h"
#include "jogo_da_velha.h"
#include <float.h>
#define BUFSIZE 512


// Variáveis de controle de câmera
float cameraDistance = 5.0f; // Distância da câmera
float cameraAngleX = 0.75f, cameraAngleY = 0.75f; // Ângulos de rotação
int isDragging = 0; // Estado de arrastar o mouse
int lastMouseX, lastMouseY; // Última posição do mouse
int objetoSelecionado = 0; // 0 para não; 1 para cubo; 2 para esfera
int contagemRounds = 0;
bool isDraggingObject = false;
int selectedObjectIndex = -1; // Índice do objeto atualmente selecionado

// Variáveis de controle do jogo
float tabuleiro[TAM][TAM][TAM+1];
int jogadorAtual = 1;
int jogoAtivo = 1;
int empate = 0;
float x, y;

void jogoDaVelha(float tabuleiro[TAM][TAM][TAM+1], int jogoAtivo, int* jogadorAtual, float* x, float* y){
    if (jogoAtivo == 1) {
        realizarJogada(tabuleiro, jogadorAtual, x, y);

        if (verificarVencedor(tabuleiro, *jogadorAtual)) {
            jogoAtivo = 0;
        }

        if (verificarEmpate(tabuleiro)) {
            jogoAtivo = 0;
            empate = 1;
        }

        *jogadorAtual = (*jogadorAtual == 1) ? 2 : 1;

        if(jogoAtivo == 0 || empate == 1) glutLeaveMainLoop();
    }
}

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


void selectObject(int mouseX, int mouseY) {
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    winX = (float)mouseX;
    winY = (float)viewport[3] - (float)mouseY;
    glReadPixels(mouseX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    // Lógica de seleção baseada na distância
    float closestDistance = FLT_MAX; // Inicializa com a maior distância possível
    int closestIndex = -1;

    for (int i = 0; i < objectCount; i++) {
        float dx = objects[i].x - posX;
        float dy = objects[i].y - posY;
        float dz = objects[i].z - posZ;
        float distance = sqrt(dx * dx + dy * dy + dz * dz);

        if (distance < closestDistance) {
            closestDistance = distance;
            closestIndex = i;
        }
    }

    // Atualiza o objeto selecionado
    for (int i = 0; i < objectCount; i++) {
        objects[i].isSelected = 0; // Desmarca todos os objetos
    }

    if (closestIndex != -1 && objects[closestIndex].movido == 0) {
        
        if (objects[closestIndex].type == OBJ_SPHERE && contagemRounds%2 == 0 || objects[closestIndex].type == OBJ_CUBE && contagemRounds%2 != 0)
        {
            objects[closestIndex].isSelected = 1; // Marca o objeto mais próximo como selecionado
        } else {
            printf("Não é o turno desse jogador!\n");
        }
        
    } else {
        printf("Nenhum objeto selecionado.\n");
    }
}

// Atualizar a posição do objeto arrastado
void moveSelectedObject(float x, float y, float z) {
    if (selectedObjectIndex >= 0 && selectedObjectIndex < objectCount) {
        objects[selectedObjectIndex].x = x;
        objects[selectedObjectIndex].y = y;
        objects[selectedObjectIndex].z = z;
    }
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
    gluLookAt(cameraDistance * sin(cameraAngleY) * cos(cameraAngleX),
              cameraDistance * sin(cameraAngleX),                    
              cameraDistance * cos(cameraAngleY) * cos(cameraAngleX), 
              0.75, 0.0, 0.75, 
              0.0, 1.0, 0.0); 
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
    } if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN)
        {
            selectObject(x, y); // Chama a função de seleção ao clicar com o botão esquerdo
        }
        if(state == GLUT_UP){
            int ind = -1;
            for(int i = 0; i < objectCount; i++){
                if(objects[i].isSelected == 1){
                    ind = i;
                    break;
                }
            }

            if(ind != -1) jogoDaVelha(tabuleiro, jogoAtivo, &jogadorAtual, &objects[ind].x, &objects[ind].z);
            objects[ind].movido = 1;
            ind = -1;
        
        }
    }
}

void keyboard(int key) {
    switch (key) {
        case ' ':
            contagemRounds++;
            break;
    }
    glutPostRedisplay();
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
    // Atualiza a posição do objeto selecionado
    for (int i = 0; i < objectCount; i++) {
        if (objects[i].isSelected && isDragging == 0) {
            GLint viewport[4];
            GLdouble modelview[16], projection[16];
            GLfloat winX, winY, winZ;
            GLdouble posX, posY, posZ;

            glGetIntegerv(GL_VIEWPORT, viewport);
            glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
            glGetDoublev(GL_PROJECTION_MATRIX, projection);

            winX = (float)x;
            winY = (float)viewport[3] - (float)y;
            glReadPixels(x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

            gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

            // Atualiza a posição do objeto selecionado
            objects[i].x = posX;
            objects[i].z = posZ; // Atualiza apenas X e Z para movimento no plano
            break;
        }
    }
    
    updateCamera();
    glutPostRedisplay(); // Redesenha a tela
}

void lighting() {
    float position[4] = {0.75f, 0.75f, 0.75f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);  //aparencia mais realista
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);  //um ponto muito expecifico

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);

    float global_ambient[4] = {0.5f, 0.5f, 0.5f, 1.0f};
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
                0.75, 0.0, 0.75, 
                0.0, 1.0, 0.0);

    addObject(1.4, 0.1, 2.0, 1.0f, 0.0f, 0.0f, 0.2f, 1,0 );
    addObject(1.4, 0.1, -0.5, 0.0f, 1.0f, 0.0f, 0.12f, 2, 0);
    addObject(1.1, 0.1, 2.0, 1.0f, 0.0f, 0.0f, 0.2f, 1,0);
    addObject(1.1, 0.1, -0.5, 0.0f, 1.0f, 0.0f, 0.12f, 2, 0);
    addObject(0.8, 0.1, 2.0, 1.0f, 0.0f, 0.0f, 0.2f, 1, 0);
    addObject(0.8, 0.1, -0.5, 0.0f, 1.0f, 0.0f, 0.12f, 2 ,0);
    addObject(0.5, 0.1, 2.0, 1.0f, 0.0f, 0.0f, 0.2f, 1,0);
    addObject(0.5, 0.1, -0.5, 0.0f, 1.0f, 0.0f, 0.12f, 2,0);
    addObject(0.2, 0.1, 2.0, 1.0f, 0.0f, 0.0f, 0.2f, 1, 0);
    addObject(0.2, 0.1, -0.5, 0.0f, 1.0f, 0.0f, 0.12f, 2,0);
    
    lighting();

    inicializarTabuleiro(tabuleiro);
}

void drawEspacos(float tabuleiro[TAM][TAM][TAM+1]) {
    // Configura material do tabuleiro
    float kd[4] = {0.5f, 0.6f, 0.8f, 0.0f};
    float ks[4] = {0.0f, 0.5f, 0.5f, 0.5f};
    float ns = 50.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);


    //tabuleiro[0][0][3] == quadrante mais a esquerda
    // Desenha o plano (tabuleiro)

    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (tabuleiro[j][i][3] == 0)
            {
                glBegin(GL_QUADS);
                    glVertex3f(0.1f + (j*0.5), 0.01f, 0.1f + (i*0.5));
                    glVertex3f(0.1f + (j*0.5), 0.01f, 0.4f + (i*0.5));
                    glVertex3f(0.4f + (j*0.5), 0.01f, 0.4f + (i*0.5));
                    glVertex3f(0.4f + (j*0.5), 0.01f, 0.1f + (i*0.5));
                glEnd();
            }
        }
    }
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
        glVertex3f(-0.95f, 0.0f, -0.95f);
        glVertex3f(2.45f, 0.0f, -0.95f);
        glVertex3f(2.45f, 0.0f, 2.45f);
        glVertex3f(-0.95f, 0.0f, 2.45f);
    glEnd();

    // Desenha as linhas do tabuleiro
    //glDisable(GL_LIGHTING); // Desativa a iluminação para as linhas
    //glColor3f(1.0f, 1.0f, 1.0f); // Define a cor branca para as linhas

    if (objetoSelecionado =! 0)
    {
        // função de desenhar espaços disponiveis
    }

    float kdd[4] = {1.0f, 1.0f, 1.0f, 0.0f};
    float kss[4] = {1.0f, 1.0f, 1.0f, 0.5f};
    float nss = 50.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kdd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, kss);
    glMaterialf(GL_FRONT, GL_SHININESS, nss);
    

    glLineWidth(4.0f);
    glBegin(GL_LINES);
        glVertex3f(0.0f, 0.01f, 0.5f); // linhas horizontais
        glVertex3f(1.5f, 0.01f, 0.5f);
        glVertex3f(0.0f, 0.01f, 1.0f);
        glVertex3f(1.5f, 0.01f, 1.0f);

        glVertex3f(0.5f, 0.01f, 0.0f); // linhas verticais
        glVertex3f(0.5f, 0.01f, 1.5f);
        glVertex3f(1.0f, 0.01f, 0.0f);
        glVertex3f(1.0f, 0.01f, 1.5f);
    glEnd();

    //glEnable(GL_LIGHTING); // Reativa a iluminação

    // Desenha objetos
    
    drawObjects();
    drawEspacos(tabuleiro);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tabuleiro 3D - Jogo da Velha");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseControl);
    glutMotionFunc(mouseMotion);
    
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}