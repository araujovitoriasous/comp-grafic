// Questao 1: Desenha uma casa simples com OpenGL.
// Ao pressionar espaco, a tela escurece.
// Se o fundo estiver escuro e o usuario pressionar qualquer tecla, o fundo torna-se branco.

#include <GLUT/glut.h>

void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

bool telaEscura = false;

void init() {
    glClearColor(0.7f, 0.85f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawHouse() {
    // Corpo da casa (quadrado marrom)
    glColor3f(0.8f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, -0.5f);
    glVertex2f(0.4f, -0.5f);
    glVertex2f(0.4f, 0.1f);
    glVertex2f(-0.4f, 0.1f);
    glEnd();

    // Telhado (triangulo vermelho)
    glColor3f(0.9f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, 0.1f);
    glVertex2f(0.5f, 0.1f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    // Porta (retangulo marrom escuro)
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1f, -0.5f);
    glVertex2f(0.1f, -0.5f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(-0.1f, -0.1f);
    glEnd();

    // Janela esquerda (quadrado azul claro)
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.35f, -0.05f);
    glVertex2f(-0.15f, -0.05f);
    glVertex2f(-0.15f, 0.05f);
    glVertex2f(-0.35f, 0.05f);
    glEnd();

    // Janela direita (quadrado azul claro)
    glBegin(GL_QUADS);
    glVertex2f(0.15f, -0.05f);
    glVertex2f(0.35f, -0.05f);
    glVertex2f(0.35f, 0.05f);
    glVertex2f(0.15f, 0.05f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawHouse();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) {
        h = 1;
    }

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    (void)x;
    (void)y;

    if (key == ' ') {
        telaEscura = true;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    } else if (telaEscura) {
        telaEscura = false;
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Questao 1 - Casa");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
