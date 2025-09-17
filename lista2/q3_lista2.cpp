// Versão reescrita sem glPushMatrix/glPopMatrix
// Mantém o mesmo comportamento visual usando apenas glTranslatef e glRotatef

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <math.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // VERSÃO ORIGINAL - Primeiro quadrado, depois segundo
    glColor3f(1.0, 0.0, 0.0); // Vermelho para o primeiro quadrado
    
    // PRIMEIRO QUADRADO - Apenas translação
    glLoadIdentity();                    // Reseta para matriz identidade
    glTranslatef(0.5, 0.5, 0);          // Aplica translação T1
    glRectf(-0.25, -0.25, 0.25, 0.25);  // Desenha quadrado
    
    // SEGUNDO QUADRADO - Translação + rotação
    glColor3f(0.0, 0.0, 1.0);           // Azul para o segundo quadrado
    glLoadIdentity();                    // Reseta para matriz identidade
    glTranslatef(0.5, 0.5, 0);          // Aplica translação T2
    glRotatef(45.0, 0, 0, 1);           // Aplica rotação R
    glRectf(-0.25, -0.25, 0.25, 0.25);  // Desenha quadrado rotacionado
    
    glFlush();
}

void displayInverted() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // VERSÃO COM ORDEM INVERTIDA - Segundo quadrado, depois primeiro
    glColor3f(0.0, 0.0, 1.0); // Azul para o segundo quadrado
    
    // SEGUNDO QUADRADO - Translação + rotação
    glLoadIdentity();                    // Reseta para matriz identidade
    glTranslatef(0.5, 0.5, 0);          // Aplica translação T2
    glRotatef(45.0, 0, 0, 1);           // Aplica rotação R
    glRectf(-0.25, -0.25, 0.25, 0.25);  // Desenha quadrado rotacionado
    
    // PRIMEIRO QUADRADO - Apenas translação
    glColor3f(1.0, 0.0, 0.0);           // Vermelho para o primeiro quadrado
    glLoadIdentity();                    // Reseta para matriz identidade
    glTranslatef(0.5, 0.5, 0);          // Aplica translação T1
    glRectf(-0.25, -0.25, 0.25, 0.25);  // Desenha quadrado
    
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == '1') {
        glutDisplayFunc(display);
        glutPostRedisplay();
    } else if (key == '2') {
        glutDisplayFunc(displayInverted);
        glutPostRedisplay();
    }
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
    glutCreateWindow("Versão Reescrita - Tecla 1: Original, Tecla 2: Invertida");
    
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    
    return 0;
}
