#include <GL/glut.h>
int ombro = 0, cotovelo = 0;

void inicializa() {
 glClearColor(0.0, 0.0, 0.0, 1.0);
 glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -5.0);

    glPushMatrix();
        glTranslatef(-1.0, 0.0, 0.0);
        glRotatef((float)ombro, 0.0, 0.0, 1.0);
        glTranslatef(1.0, 0.0, 0.0);
    
    glPushMatrix();
        glScalef(2.0, 0.4, 1.0);
        glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((float)cotovelo, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void teclado(unsigned char tecla, int x, int y){
    switch(tecla){
        case 'o':
            ombro = (ombro + 5) % 360;
            glutPostRedisplay();
            break;
        case 'O':
            ombro = (ombro - 5) % 360;
            glutPostRedisplay();
            break;
        case 'c':
            cotovelo = (cotovelo + 5) % 360;
            glutPostRedisplay();
            break;
        case 'C':
            cotovelo = (cotovelo - 5) % 360;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
    }
}

void reshape(int largura, int altura) {
 glViewport(0, 0, largura, altura);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

 gluPerspective(65.0, (float)largura / (float)altura, 1.0, 20.0);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
}
 
int main(int argc, char** argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(800, 600);
 glutCreateWindow("Modelos Hierarquicos");

 inicializa();

 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutKeyboardFunc(teclado);
 
 glutMainLoop();

 return 0;
}