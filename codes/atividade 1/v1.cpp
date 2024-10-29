#include <GL/glut.h>
#include <math.h>
float xPos = 0.0, yPos = 0.0;

#define PI 3.14159265358979323846

void inicializa() {
glClearColor(1.0, 1.0, 1.0, 1.0); // Fundo branco
}

void desenhaHaste(float x, float y, float largura, float altura) {
glBegin(GL_QUADS);
glVertex2f(x - largura / 2, y); // Canto inferior esquerdo
glVertex2f(x + largura / 2, y); // Canto inferior direito
glVertex2f(x + largura / 2, y + altura); // Canto superior direito
glVertex2f(x - largura / 2, y + altura); // Canto superior esquerdo
glEnd();
}

void desenhaCirculo(float x, float y, float raio) {
glBegin(GL_TRIANGLE_FAN);
glVertex2f(x, y); // Centro do círculo
for (int i = 0; i <= 360; i += 5) {
float angulo = i * PI / 180.0f; // Converter para radianos
glVertex2f(x + cos(angulo) * raio, y + sin(angulo) * raio);
}
glEnd();
}

void desenhaHélice(float x, float y, float raio) {
float largura = 0.8f * raio; // Largura das pás, ajustada para 10% do raio
float altura = 2.0f * raio; // Altura das pás, ajustada para 90% do raio
float recuo = 0.1f * raio; // Recuo para a base do triângulo
int numHélices = 4; // Número de hélices
float angulo;

for (int i = 0; i < numHélices; ++i) {
angulo = i * (360.0f / numHélices); // Calcula o ângulo para cada hélice

// Salva a matriz de estado atual
glPushMatrix();

// Translada para a posição do círculo
glTranslatef(x, y, 0.0f);
// Aplica a rotação
glRotatef(angulo, 0.0f, 0.0f, 1.0f);

// Desenha a hélice como um triângulo
glBegin(GL_TRIANGLES);
// Pás da hélice
glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
glVertex2f(0.0f, -raio); // Ponto superior (na borda do círculo)
glVertex2f(-largura, -altura + recuo); // Ponto esquerdo da base
glVertex2f(largura, -altura + recuo); // Ponto direito da base
glEnd();

// Restaura a matriz anterior
glPopMatrix();
}
}

void desenhaCataVento(float x, float y, float larguraHaste, float alturaHaste, float raioCirculo) {
// Desenhar a haste
desenhaHaste(x, y, larguraHaste, alturaHaste);

// Desenhar o círculo no topo da haste
desenhaCirculo(x, y + alturaHaste, raioCirculo);

// Desenhar as hélices do cata-vento
desenhaHélice(x, y + alturaHaste, raioCirculo); // Hélice colorida
}

void display() {
glClear(GL_COLOR_BUFFER_BIT);
desenhaCataVento(xPos, yPos, 10.0f, 100.0f, 20.0f); // Desenhe o cata-vento
glFlush();
}

void reshape(int width, int height) {
glViewport(0, 0, width, height);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-250, 250, -250, 250); // Ajuste o sistema de coordenadas
glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(500, 500);
glutCreateWindow("Cata-Vento com Hélices na Borda do Círculo");
inicializa();
glutReshapeFunc(reshape); // Adiciona a função reshape
glutDisplayFunc(display);
glutMainLoop();
return 0;
}

