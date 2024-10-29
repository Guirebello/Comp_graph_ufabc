#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

// Variáveis de controle do catavento
float rotationAngle = 0.0f;
float posX = 0.0f, posY = 0.0f;
float scaleFactor = 1.0f;
float rotationSpeed = 1.0f;
bool isRotating = true;

// Cores para as hélices
float colors[4][3] = {
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 0.0f}
};

// Função para desenhar o catavento
void drawWindmill() {
    glPushMatrix();
    
    // Aplica transformações de escala e posição
    glTranslatef(posX, posY, 0.0f);
    glScalef(scaleFactor, scaleFactor, 1.0f);

    // Desenha a haste
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, -0.5f);
        glVertex2f(0.05f, -0.5f);
        glVertex2f(0.05f, 0.0f);
        glVertex2f(-0.05f, 0.0f);
    glEnd();

    // Desenha as hélices com rotação
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i < 4; i++) {
        glColor3fv(colors[i]);
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.2f, 0.1f);
            glVertex2f(0.2f, -0.1f);
        glEnd();
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    }

    glPopMatrix();
}

// Função para atualizar a tela
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawWindmill();
    glutSwapBuffers();
}

// Função para atualizar a rotação continuamente
void update(int value) {
    if (isRotating) rotationAngle += rotationSpeed;
    if (rotationAngle >= 360.0f) rotationAngle -= 360.0f;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Aproximadamente 60 FPS
}

// Função de teclado
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'r': rotationAngle += rotationSpeed; break;
        case 'l': rotationAngle -= rotationSpeed; break;
        case 'p': isRotating = !isRotating; break;
        case '+': scaleFactor += 0.1f; break;
        case '-': if (scaleFactor > 0.2f) scaleFactor -= 0.1f; break;
        case 'c': for (int i = 0; i < 4; i++) { colors[i][0] = (rand() % 100) / 100.0f; colors[i][1] = (rand() % 100) / 100.0f; colors[i][2] = (rand() % 100) / 100.0f; } break;
        case '1': rotationSpeed = 0.5f; break;
        case '2': rotationSpeed = 1.0f; break;
        case '3': rotationSpeed = 2.0f; break;
    }
    glutPostRedisplay();
}

// Função de teclas especiais
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: posY += 0.1f; break;
        case GLUT_KEY_DOWN: posY -= 0.1f; break;
        case GLUT_KEY_LEFT: posX -= 0.1f; break;
        case GLUT_KEY_RIGHT: posX += 0.1f; break;
    }
    glutPostRedisplay();
}

// Função de clique do mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Armazena a cor do último triângulo
        float tempColor[3] = {colors[3][0], colors[3][1], colors[3][2]};
        
        // Desloca as cores para o próximo triângulo
        for (int i = 3; i > 0; i--) {
            colors[i][0] = colors[i - 1][0];
            colors[i][1] = colors[i - 1][1];
            colors[i][2] = colors[i - 1][2];
        }

        // Atribui a cor do último triângulo ao primeiro
        colors[0][0] = tempColor[0];
        colors[0][1] = tempColor[1];
        colors[0][2] = tempColor[2];
    }
    
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        posX = 0.0f;
        posY = 0.0f;
        scaleFactor = 1.0f;
        rotationAngle = 0.0f;
        rotationSpeed = 1.0f;
    }
    glutPostRedisplay();
}

// Inicializa o OpenGL
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Fundo branco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    srand(time(0)); // Semente para cores aleatórias
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Catavento Interativo 2D");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutTimerFunc(16, update, 0);
    
    glutMainLoop();
    return 0;
}
