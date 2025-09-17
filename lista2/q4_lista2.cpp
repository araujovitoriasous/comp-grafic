// Desenho de paralelogramo e losango usando glRect* e transformações
// Paralelogramo: lados iguais, ângulo interno de 30°
// Losango: transformação do paralelogramo

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <math.h>

// Parâmetros do paralelogramo
const float SIDE_LENGTH = 0.4f;        // Comprimento dos lados
const float ANGLE_30_DEG = 30.0f;      // Ângulo interno de 30°
const float ANGLE_RAD = ANGLE_30_DEG * M_PI / 180.0f;

// Função para desenhar um retângulo básico
void drawBasicRect() {
    glRectf(-SIDE_LENGTH/2, -SIDE_LENGTH/4, SIDE_LENGTH/2, SIDE_LENGTH/4);
}

// Função para desenhar paralelogramo usando glRect* com transformações
void drawParallelogram() {
    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho para o paralelogramo
    
    // Salva a matriz atual
    glPushMatrix();
    
    // Aplica cisalhamento horizontal para criar o paralelogramo
    // O cisalhamento é calculado baseado no ângulo de 30°
    float shear = tan(ANGLE_RAD);
    
    // Aplica transformação de cisalhamento usando glMultMatrix
    float shearMatrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        shear, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    glMultMatrixf(shearMatrix);
    drawBasicRect();
    
    // Restaura a matriz
    glPopMatrix();
}

// Função para desenhar losango a partir do paralelogramo
void drawRhombus() {
    glColor3f(0.0f, 0.0f, 1.0f); // Azul para o losango
    
    // Salva a matriz atual
    glPushMatrix();
    
    // Aplica as mesmas transformações do paralelogramo
    float shear = tan(ANGLE_RAD);
    float shearMatrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        shear, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    glMultMatrixf(shearMatrix);
    
    // Aplica rotação de 30° para criar o losango
    glRotatef(ANGLE_30_DEG, 0.0f, 0.0f, 1.0f);
    
    drawBasicRect();
    
    // Restaura a matriz
    glPopMatrix();
}

// Função para desenhar paralelogramo alternativo usando apenas glRect*
void drawParallelogramAlternative() {
    glColor3f(0.0f, 1.0f, 0.0f); // Verde para o paralelogramo alternativo
    
    // Salva a matriz atual
    glPushMatrix();
    
    // Aplica rotação de 30° primeiro
    glRotatef(ANGLE_30_DEG, 0.0f, 0.0f, 1.0f);
    
    // Aplica escala para compensar a deformação
    float scaleY = 1.0f / cos(ANGLE_RAD);
    glScalef(1.0f, scaleY, 1.0f);
    
    drawBasicRect();
    
    // Restaura a matriz
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Desenha o paralelogramo usando cisalhamento
    glPushMatrix();
    glTranslatef(-0.3f, 0.0f, 0.0f);
    drawParallelogram();
    glPopMatrix();
    
    // Desenha o losango
    glPushMatrix();
    glTranslatef(0.3f, 0.0f, 0.0f);
    drawRhombus();
    glPopMatrix();
    
    // Desenha o paralelogramo alternativo
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f);
    drawParallelogramAlternative();
    glPopMatrix();
    
    glFlush();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Paralelogramo e Losango - glRect* com Transformações");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
