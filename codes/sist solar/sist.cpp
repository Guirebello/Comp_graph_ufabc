#include <GL/glut.h>
#include <cmath>

float anguloSol = 0.0;
float anguloMercurio = 0.0;
float anguloVenus = 0.0;
float anguloTerra = 0.0;
float anguloMarte = 0.0;

float anguloMercurioRotacao = 0.0;
float anguloVenusRotacao = 0.0;
float anguloTerraRotacao = 0.0;
float anguloMarteRotacao = 0.0;

float camPosZ = -30.0;
float camPosY = 0.0;
float camPosX = 0.0;
float velocidadeOrbita = 1.0;
float velocidadeRotacao = 1.0;

void inicializa() {
 glClearColor(0.0, 0.0, 0.0, 1.0);
 glEnable(GL_DEPTH_TEST);
}

void desenhaEsfera(GLfloat raio){
    glutWireSphere(raio, 20, 20);
}

void drawOrbit(float radius) {
    int numSegments = 1000;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; ++i) {
        float angle = 2.0f * M_PI * float(i) / float(numSegments);
        float x = radius * cosf(angle);
        float z = radius * sinf(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //glTranslatef(camPosX, camPosY, camPosZ);

    // Set the camera position and orientation
    gluLookAt(camPosX, camPosY + 10.0, camPosZ,  // Eye position
              0.0, 0.0, 0.0,                   // Reference point
              0.0, 1.0, 0.0);                  // Up vector



    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF); // Set the stipple pattern (dashed line)
    // Draw orbits
    glColor3f(0.7, 0.7, 0.7); // Set orbit color to white
    drawOrbit(6.0);
    glColor3f(1.0, 0.5, 0.0); // Set orbit color to orange
    drawOrbit(9.0);
    glColor3f(0.0, 0.0, 1.0); // Set orbit color to blue
    drawOrbit(12.0);
    glColor3f(1.0, 0.0, 0.0); // Set orbit color to red
    drawOrbit(15.0);

    // Disable line stippling
    glDisable(GL_LINE_STIPPLE);

    //sol
    glPushMatrix();
        glRotatef(anguloSol, 0.0, 1.0, 0.0);
        glColor3f(1.0, 1.0, 0.0);
        desenhaEsfera(3.0);
    glPopMatrix();

    //mercurio
    glPushMatrix();
        glRotatef(anguloMercurio * velocidadeOrbita, 0.0, 1.0, 0.0);
        glTranslatef(6.0, 0.0, 0.0);
        glPushMatrix();
            glRotatef(anguloMercurioRotacao * velocidadeRotacao, 0.0, 1.0, 0.0);
            glColor3f(0.7, 0.7, 0.7);
            desenhaEsfera(0.3);
            glPopMatrix();
        glPopMatrix();

    //venus
    glPushMatrix();
        glRotatef(anguloVenus * velocidadeOrbita, 0.0, 1.0, 0.0);
        glTranslatef(9.0, 0.0, 0.0);
        glPushMatrix();
            glRotatef(anguloVenusRotacao * velocidadeRotacao, 0.0, 1.0, 0.0);
            glColor3f(1.0, 0.5, 0.0);
            desenhaEsfera(0.7);
            glPopMatrix();
        glPopMatrix();

    //terra
    glPushMatrix();
        glRotatef(anguloTerra * velocidadeOrbita, 0.0, 1.0, 0.0);
        glTranslatef(12.0, 0.0, 0.0);
        glPushMatrix();
            glRotatef(anguloTerraRotacao * velocidadeRotacao, 0.0, 1.0, 0.0);
            glColor3f(0.0, 0.0, 1.0);
            desenhaEsfera(1.0);
            glPopMatrix();
        glPopMatrix();

    //marte
    glPushMatrix();
        glRotatef(anguloMarte * velocidadeOrbita, 0.0, 1.0, 0.0);
        glTranslatef(15.0, 0.0, 0.0);
        glPushMatrix();
            glRotatef(anguloMarteRotacao * velocidadeRotacao, 0.0, 1.0, 0.0);
            glColor3f(1.0, 0.0, 0.0);
            desenhaEsfera(0.8);
            glPopMatrix();
        glPopMatrix();

    glutSwapBuffers();
}

void teclado (unsigned char tecla, int x, int y){
    switch (tecla){
        case 27:
            exit(0);
            break;

        case 'w':
            camPosZ += 1.0;
            break;
        case 's':
            camPosZ -= 1.0;
            break;
        case 'a':
            camPosX -= 1.0;
            break;
        case 'd':
            camPosX += 1.0;
            break;
        case 'q':
            camPosY += 1.0;
            break;
        case 'e':
            camPosY -= 1.0;
            break;
        case '1':
            velocidadeOrbita += 0.1;
            glutPostRedisplay();
            break;
        case '2':
            velocidadeOrbita -= 0.1;
            glutPostRedisplay();
            break;
        case '3':
            velocidadeRotacao += 0.1;
            glutPostRedisplay();
            break;
        case '4':
            velocidadeRotacao -= 0.1;
            glutPostRedisplay();
            break;
    }
}

void mouse (int botao, int estado, int x, int y){
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
        if (estado == GLUT_DOWN){
            camPosZ = -30.0;
        }
    }
}

void atualiza(int valor){
    anguloSol += 0.2;

    anguloMercurio += 1.5 * velocidadeOrbita;
    anguloMercurioRotacao += 5.0 * velocidadeRotacao;

    anguloVenus += 1.0 * velocidadeOrbita;
    anguloVenusRotacao += 5.0 * velocidadeRotacao;

    anguloTerra += 0.8 * velocidadeOrbita;
    anguloTerraRotacao += 5.0 * velocidadeRotacao;

    anguloMarte += 0.6 * velocidadeOrbita;
    anguloMarteRotacao += 5.0 * velocidadeRotacao;


    glutPostRedisplay();
    glutTimerFunc(16, atualiza, 0);
}

void reshape(int largura, int altura) {
 glViewport(0, 0, largura, altura);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

 gluPerspective(65.0, (float)largura / (float)altura, 1.0, 50.0);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
}
 
int main(int argc, char** argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(800, 600);
 glutCreateWindow("Sistema Solar");

 inicializa();

 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutKeyboardFunc(teclado);
glutMouseFunc(mouse);

 glutTimerFunc(16, atualiza, 0);
 
 glutMainLoop();

 return 0;
}