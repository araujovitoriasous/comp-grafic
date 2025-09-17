// Braço robótico com 2 elos - Cinemática e Transformações
// Sistemas de referência: F0, F1, F2
// Comprimentos: L1, L2
// Ângulos: α (F0→F1), β (F1→F2)

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>

// Parâmetros do braço robótico
const float L1 = 0.4f;  // Comprimento do primeiro elo
const float L2 = 0.3f;  // Comprimento do segundo elo
const float ALPHA = 60.0f;   // Ângulo α em graus
const float BETA = -30.0f;   // Ângulo β em graus

// Conversão para radianos
const float ALPHA_RAD = ALPHA * M_PI / 180.0f;
const float BETA_RAD = BETA * M_PI / 180.0f;

// Estrutura para matrizes 3x3 (homogêneas)
struct Matrix3x3 {
    float m[3][3];
    
    Matrix3x3() {
        // Inicializa como matriz identidade
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }
    
    void print(const char* name) {
        printf("\n%s:\n", name);
        for (int i = 0; i < 3; i++) {
            printf("[");
            for (int j = 0; j < 3; j++) {
                printf("%8.3f", m[i][j]);
                if (j < 2) printf(", ");
            }
            printf("]\n");
        }
    }
};

// Função para criar matriz de rotação
Matrix3x3 rotationMatrix(float angle) {
    Matrix3x3 R;
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    
    R.m[0][0] = cos_a;  R.m[0][1] = -sin_a;
    R.m[1][0] = sin_a;  R.m[1][1] = cos_a;
    
    return R;
}

// Função para criar matriz de translação
Matrix3x3 translationMatrix(float tx, float ty) {
    Matrix3x3 T;
    T.m[0][2] = tx;
    T.m[1][2] = ty;
    return T;
}

// Função para multiplicar matrizes
Matrix3x3 multiplyMatrices(const Matrix3x3& A, const Matrix3x3& B) {
    Matrix3x3 C;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            C.m[i][j] = 0.0f;
            for (int k = 0; k < 3; k++) {
                C.m[i][j] += A.m[i][k] * B.m[k][j];
            }
        }
    }
    return C;
}

// Função para aplicar transformação a um ponto
void transformPoint(const Matrix3x3& M, float x, float y, float& x_out, float& y_out) {
    x_out = M.m[0][0] * x + M.m[0][1] * y + M.m[0][2];
    y_out = M.m[1][0] * x + M.m[1][1] * y + M.m[1][2];
}

// Função para desenhar sistema de coordenadas
void drawCoordinateSystem(float x, float y, float scale = 0.1f, const char* label = "") {
    // Eixos X e Y
    glBegin(GL_LINES);
    // Eixo X (vermelho)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(x, y);
    glVertex2f(x + scale, y);
    // Eixo Y (verde)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(x, y);
    glVertex2f(x, y + scale);
    glEnd();
    
    // Label
    if (label[0] != '\0') {
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(x + scale/2, y + scale/2);
        for (int i = 0; label[i] != '\0'; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, label[i]);
        }
    }
}

// Função para desenhar elo do braço
void drawArmSegment(float x1, float y1, float x2, float y2, float width = 0.02f) {
    glLineWidth(3.0f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glLineWidth(1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Calcula as matrizes de transformação
    
    // F0 → F1: Rotação de α
    Matrix3x3 T01 = rotationMatrix(ALPHA_RAD);
    
    // F0 → F2: Rotação de α + translação de L1 + rotação de β
    Matrix3x3 T02 = multiplyMatrices(
        multiplyMatrices(
            rotationMatrix(ALPHA_RAD + BETA_RAD),
            translationMatrix(L1 * cos(ALPHA_RAD), L1 * sin(ALPHA_RAD))
        ),
        rotationMatrix(ALPHA_RAD)
    );
    
    // Simplificando: F0 → F2 = Rotação(α) * Translação(L1) * Rotação(β)
    Matrix3x3 T02_simple = multiplyMatrices(
        multiplyMatrices(
            rotationMatrix(ALPHA_RAD),
            translationMatrix(L1, 0)
        ),
        rotationMatrix(BETA_RAD)
    );
    
    // Calcula as origens dos sistemas de referência
    float F1_x, F1_y, F2_x, F2_y;
    
    // Origem de F1 em coordenadas de F0
    transformPoint(T01, 0, 0, F1_x, F1_y);
    
    // Origem de F2 em coordenadas de F0
    transformPoint(T02_simple, 0, 0, F2_x, F2_y);
    
    // Desenha o braço robótico
    
    // Sistema F0 (origem)
    drawCoordinateSystem(0, 0, 0.15f, "F0");
    
    // Primeiro elo (F0 → F1)
    float F1_end_x = L1 * cos(ALPHA_RAD);
    float F1_end_y = L1 * sin(ALPHA_RAD);
    drawArmSegment(0, 0, F1_end_x, F1_end_y);
    
    // Sistema F1
    drawCoordinateSystem(F1_end_x, F1_end_y, 0.12f, "F1");
    
    // Segundo elo (F1 → F2)
    float F2_end_x = F1_end_x + L2 * cos(ALPHA_RAD + BETA_RAD);
    float F2_end_y = F1_end_y + L2 * sin(ALPHA_RAD + BETA_RAD);
    drawArmSegment(F1_end_x, F1_end_y, F2_end_x, F2_end_y);
    
    // Sistema F2
    drawCoordinateSystem(F2_end_x, F2_end_y, 0.1f, "F2");
    
    // Desenha pontos de junção
    glColor3f(1.0f, 1.0f, 0.0f);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glVertex2f(0, 0);           // F0
    glVertex2f(F1_end_x, F1_end_y);  // F1
    glVertex2f(F2_end_x, F2_end_y);  // F2
    glEnd();
    
    glFlush();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5, 1.0, -0.5, 0.8, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void printCalculations() {
    printf("=== BRAÇO ROBÓTICO - CINEMÁTICA ===\n");
    printf("Parâmetros:\n");
    printf("L1 = %.1f\n", L1);
    printf("L2 = %.1f\n", L2);
    printf("α = %.0f°\n", ALPHA);
    printf("β = %.0f°\n", BETA);
    printf("\n");
    
    // Matrizes de transformação
    Matrix3x3 T01 = rotationMatrix(ALPHA_RAD);
    T01.print("T01 (F0 → F1)");
    
    Matrix3x3 T12 = multiplyMatrices(
        translationMatrix(L1, 0),
        rotationMatrix(BETA_RAD)
    );
    T12.print("T12 (F1 → F2)");
    
    Matrix3x3 T02 = multiplyMatrices(T01, T12);
    T02.print("T02 (F0 → F2)");
    
    // Origens dos sistemas
    float F1_x = L1 * cos(ALPHA_RAD);
    float F1_y = L1 * sin(ALPHA_RAD);
    
    float F2_x = F1_x + L2 * cos(ALPHA_RAD + BETA_RAD);
    float F2_y = F1_y + L2 * sin(ALPHA_RAD + BETA_RAD);
    
    printf("\nOrigens dos sistemas de referência:\n");
    printf("F1 em coordenadas de F0: (%.3f, %.3f)\n", F1_x, F1_y);
    printf("F2 em coordenadas de F0: (%.3f, %.3f)\n", F2_x, F2_y);
    
    printf("\nComposição das transformações:\n");
    printf("F0 → F1: Rotação(α)\n");
    printf("F0 → F2: Rotação(α) * Translação(L1) * Rotação(β)\n");
}

int main(int argc, char** argv) {
    printCalculations();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Braço Robótico - Cinemática");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
