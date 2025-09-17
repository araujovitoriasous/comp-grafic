// Rotação de triângulo e recorte usando algoritmo de Liang-Barsky
// Triângulo original: A(0,0), B(0,1), C(0.5,1)
// Rotação: 60° em torno de (0.5, 0.5)
// Retângulo delimitador: (0,0) a (1,1)

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>

// Estrutura para pontos
struct Point {
    float x, y;
    Point(float x = 0, float y = 0) : x(x), y(y) {}
};

// Pontos originais do triângulo
Point A(0.0f, 0.0f);
Point B(0.0f, 1.0f);
Point C(0.5f, 1.0f);

// Centro de rotação
Point center(0.5f, 0.5f);

// Ângulo de rotação
const float ROTATION_ANGLE = 60.0f;
const float ANGLE_RAD = ROTATION_ANGLE * M_PI / 180.0f;

// Pontos após rotação
Point A_rotated, B_rotated, C_rotated;

// Retângulo delimitador
const float X_MIN = 0.0f, X_MAX = 1.0f;
const float Y_MIN = 0.0f, Y_MAX = 1.0f;

// Função para aplicar rotação em torno de um ponto
Point rotatePoint(const Point& p, const Point& center, float angle) {
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    
    // Translada para a origem
    float x_rel = p.x - center.x;
    float y_rel = p.y - center.y;
    
    // Aplica rotação
    float x_rot = x_rel * cos_a - y_rel * sin_a;
    float y_rot = x_rel * sin_a + y_rel * cos_a;
    
    // Translada de volta
    return Point(x_rot + center.x, y_rot + center.y);
}

// Algoritmo de Liang-Barsky para recorte de linha
bool liangBarsky(const Point& p1, const Point& p2, Point& clipped1, Point& clipped2) {
    float x1 = p1.x, y1 = p1.y;
    float x2 = p2.x, y2 = p2.y;
    
    float dx = x2 - x1;
    float dy = y2 - y1;
    
    float p[4] = {-dx, dx, -dy, dy};
    float q[4] = {x1 - X_MIN, X_MAX - x1, y1 - Y_MIN, Y_MAX - y1};
    
    float t1 = 0.0f, t2 = 1.0f;
    
    for (int i = 0; i < 4; i++) {
        if (p[i] == 0) {
            if (q[i] < 0) return false; // Linha paralela fora da janela
        } else {
            float t = q[i] / p[i];
            if (p[i] < 0) {
                if (t > t1) t1 = t;
            } else {
                if (t < t2) t2 = t;
            }
        }
    }
    
    if (t1 > t2) return false; // Linha completamente fora
    
    clipped1.x = x1 + t1 * dx;
    clipped1.y = y1 + t1 * dy;
    clipped2.x = x1 + t2 * dx;
    clipped2.y = y1 + t2 * dy;
    
    return true;
}

// Função para desenhar uma linha
void drawLine(const Point& p1, const Point& p2) {
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

// Função para desenhar um ponto
void drawPoint(const Point& p, float size = 0.02f) {
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Desenha o retângulo delimitador
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(X_MIN, Y_MIN);
    glVertex2f(X_MAX, Y_MIN);
    glVertex2f(X_MAX, Y_MAX);
    glVertex2f(X_MIN, Y_MAX);
    glEnd();
    
    // Desenha o triângulo original (pontilhado)
    glColor3f(0.7f, 0.7f, 0.7f);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA); // Padrão pontilhado
    drawLine(A, B);
    drawLine(B, C);
    drawLine(A, C);
    glDisable(GL_LINE_STIPPLE);
    
    // Desenha os pontos originais
    glColor3f(0.5f, 0.5f, 0.5f);
    drawPoint(A);
    drawPoint(B);
    drawPoint(C);
    
    // Aplica rotação aos pontos
    A_rotated = rotatePoint(A, center, ANGLE_RAD);
    B_rotated = rotatePoint(B, center, ANGLE_RAD);
    C_rotated = rotatePoint(C, center, ANGLE_RAD);
    
    // Desenha o triângulo rotacionado (linha contínua)
    glColor3f(1.0f, 0.0f, 0.0f);
    drawLine(A_rotated, B_rotated);
    drawLine(B_rotated, C_rotated);
    drawLine(A_rotated, C_rotated);
    
    // Desenha os pontos rotacionados
    glColor3f(1.0f, 0.0f, 0.0f);
    drawPoint(A_rotated);
    drawPoint(B_rotated);
    drawPoint(C_rotated);
    
    // Aplica algoritmo de Liang-Barsky e desenha segmentos visíveis
    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(3.0f);
    
    Point clipped1, clipped2;
    
    // Aresta A'B'
    if (liangBarsky(A_rotated, B_rotated, clipped1, clipped2)) {
        drawLine(clipped1, clipped2);
        printf("Aresta A'B': (%.3f, %.3f) a (%.3f, %.3f)\n", 
               clipped1.x, clipped1.y, clipped2.x, clipped2.y);
    } else {
        printf("Aresta A'B': completamente fora da janela\n");
    }
    
    // Aresta B'C'
    if (liangBarsky(B_rotated, C_rotated, clipped1, clipped2)) {
        drawLine(clipped1, clipped2);
        printf("Aresta B'C': (%.3f, %.3f) a (%.3f, %.3f)\n", 
               clipped1.x, clipped1.y, clipped2.x, clipped2.y);
    } else {
        printf("Aresta B'C': completamente fora da janela\n");
    }
    
    // Aresta A'C'
    if (liangBarsky(A_rotated, C_rotated, clipped1, clipped2)) {
        drawLine(clipped1, clipped2);
        printf("Aresta A'C': (%.3f, %.3f) a (%.3f, %.3f)\n", 
               clipped1.x, clipped1.y, clipped2.x, clipped2.y);
    } else {
        printf("Aresta A'C': completamente fora da janela\n");
    }
    
    glLineWidth(1.0f);
    glFlush();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.2, 1.2, -0.2, 1.2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    printf("=== ROTAÇÃO E RECORTE DE TRIÂNGULO ===\n");
    printf("Pontos originais:\n");
    printf("A = (%.1f, %.1f)\n", A.x, A.y);
    printf("B = (%.1f, %.1f)\n", B.x, B.y);
    printf("C = (%.1f, %.1f)\n", C.x, C.y);
    printf("Centro de rotação: (%.1f, %.1f)\n", center.x, center.y);
    printf("Ângulo de rotação: %.0f°\n", ROTATION_ANGLE);
    printf("Retângulo delimitador: (%.1f, %.1f) a (%.1f, %.1f)\n", 
           X_MIN, Y_MIN, X_MAX, Y_MAX);
    printf("\n");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotação e Recorte - Liang-Barsky");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
