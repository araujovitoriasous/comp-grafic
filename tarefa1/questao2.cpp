// Questao 2: Tela em branco; clique esquerdo desenha ponto preto tamanho 50;
// clique direito limpa a tela.

#include <GLUT/glut.h>
#include <vector>
#include <utility>

void init();
void display();
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);

int larguraJanela = 800;
int alturaJanela = 600;
std::vector<std::pair<int, int>> pontos;

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(50.0f);

    glBegin(GL_POINTS);
    for (const auto& ponto : pontos) {
        glVertex2i(ponto.first, ponto.second);
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) {
        h = 1;
    }

    larguraJanela = w;
    alturaJanela = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, static_cast<double>(w), static_cast<double>(h), 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN) {
        return;
    }

    if (button == GLUT_LEFT_BUTTON) {
        pontos.push_back(std::make_pair(x, y));
    } else if (button == GLUT_RIGHT_BUTTON) {
        pontos.clear();
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(larguraJanela, alturaJanela);
    glutCreateWindow("Questao 2 - Pontos com Mouse");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
