// Análise da evolução das matrizes na pilha OpenGL
// Demonstração do trecho de código da aula 4

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <math.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Desenha os quadrados para demonstração visual
    glColor3f(1.0, 0.0, 0.0); // Vermelho para o primeiro quadrado
    
    // PRIMEIRO BLOCO - Quadrado sem rotação
    glPushMatrix();                    // Salva matriz identidade
    glTranslatef(0.5, 0.5, 0);        // Aplica translação T1
    glRectf(-0.25, -0.25, 0.25, 0.25); // Desenha quadrado
    glPopMatrix();                     // Restaura matriz identidade
    
    // SEGUNDO BLOCO - Quadrado com rotação
    glColor3f(0.0, 0.0, 1.0);         // Azul para o segundo quadrado
    glPushMatrix();                    // Salva matriz identidade
    glTranslatef(0.5, 0.5, 0);        // Aplica translação T2
    glRotatef(45.0, 0, 0, 1);         // Aplica rotação R
    glRectf(-0.25, -0.25, 0.25, 0.25); // Desenha quadrado rotacionado
    glPopMatrix();                     // Restaura matriz identidade
    
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Análise de Matrizes OpenGL");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
