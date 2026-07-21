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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawHouse() {
    // Corpo da casa (roxo)
    glColor3f(0.5f, 0.0f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, -0.5f);
    glVertex2f(0.4f, -0.5f);
    glVertex2f(0.4f, 0.1f);
    glVertex2f(-0.4f, 0.1f);
    glEnd();

    // Telhado (triangulo vermelho)
    glColor3f(0.9f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, 0.1f);
    glVertex2f(0.5f, 0.1f);
    glVertex2f(0.0f, 0.55f);
    glEnd();

    // Porta (branca, lado esquerdo do centro)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.22f, -0.5f);
    glVertex2f(-0.02f, -0.5f);
    glVertex2f(-0.02f, -0.1f);
    glVertex2f(-0.22f, -0.1f);
    glEnd();

    // Janela com grade (lado direito), fundo branco
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.08f, -0.22f);
    glVertex2f(0.35f, -0.22f);
    glVertex2f(0.35f, 0.05f);
    glVertex2f(0.08f, 0.05f);
    glEnd();

    // Grade da janela - linha vertical
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(0.215f, -0.22f);
    glVertex2f(0.215f, 0.05f);
    // linha horizontal
    glVertex2f(0.08f, -0.085f);
    glVertex2f(0.35f, -0.085f);
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
    glutInitWindowSize(800, 700);
    glutCreateWindow("Questao 1 - Casa");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
