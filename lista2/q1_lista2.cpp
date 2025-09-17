// Programa que simula as órbitas da Terra e da Lua ao redor do Sol
// Define para silenciar warnings de funções OpenGL deprecadas no macOS
#define GL_SILENCE_DEPRECATION
// Inclui a biblioteca GLUT para OpenGL no macOS
#include <GLUT/glut.h>
// Inclui a biblioteca matemática para funções como cos() e sin()
#include <math.h>

// Declaração das funções
void init();
void display();
void reshape(int w, int h);
void timer(int value);

// Parâmetros dos astros
const float SUN_RADIUS = 0.1f;      // Raio do Sol
const float EARTH_RADIUS = 0.05f;   // Raio da Terra
const float MOON_RADIUS = 0.02f;    // Raio da Lua

// Parâmetros das órbitas
const float EARTH_ORBIT_RADIUS = 0.6f;  // Raio da órbita da Terra
const float MOON_ORBIT_RADIUS = 0.15f;  // Raio da órbita da Lua

// Variáveis de animação
float earthAngle = 0.0f;    // Ângulo atual da Terra
float moonAngle = 0.0f;     // Ângulo atual da Lua
float earthSpeed = 1.0f;    // Velocidade da Terra (graus por frame)
float moonSpeed = 3.0f;     // Velocidade da Lua (graus por frame)

void init() {
    // Define a cor de fundo (espaço sideral - preto)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Define o sistema de visualização ortogonal
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawDisk(float radius, float r, float g, float b) {
    // Define a cor do disco
    glColor3f(r, g, b);
    
    // Desenha um círculo preenchido usando GL_TRIANGLE_FAN
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);  // Centro do círculo
    
    // Cria um círculo com muitos triângulos para suavidade
    for (int i = 0; i <= 360; i += 5) {
        float angle = i * M_PI / 180.0f;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawSun() {
    // Desenha o Sol no centro (amarelo)
    drawDisk(SUN_RADIUS, 1.0f, 1.0f, 0.0f);
}

void drawEarth() {
    // Calcula a posição da Terra na órbita
    float earthX = EARTH_ORBIT_RADIUS * cos(earthAngle * M_PI / 180.0f);
    float earthY = EARTH_ORBIT_RADIUS * sin(earthAngle * M_PI / 180.0f);
    
    // Salva a matriz atual
    glPushMatrix();
    
    // Move para a posição da Terra
    glTranslatef(earthX, earthY, 0.0f);
    
    // Desenha a Terra (azul)
    drawDisk(EARTH_RADIUS, 0.0f, 0.5f, 1.0f);
    
    // Restaura a matriz
    glPopMatrix();
}

void drawMoon() {
    // Calcula a posição da Terra na órbita
    float earthX = EARTH_ORBIT_RADIUS * cos(earthAngle * M_PI / 180.0f);
    float earthY = EARTH_ORBIT_RADIUS * sin(earthAngle * M_PI / 180.0f);
    
    // Calcula a posição da Lua em relação à Terra
    float moonX = earthX + MOON_ORBIT_RADIUS * cos(moonAngle * M_PI / 180.0f);
    float moonY = earthY + MOON_ORBIT_RADIUS * sin(moonAngle * M_PI / 180.0f);
    
    // Salva a matriz atual
    glPushMatrix();
    
    // Move para a posição da Lua
    glTranslatef(moonX, moonY, 0.0f);
    
    // Desenha a Lua (cinza claro)
    drawDisk(MOON_RADIUS, 0.8f, 0.8f, 0.8f);
    
    // Restaura a matriz
    glPopMatrix();
}

void display() {
    // Limpa a janela
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Desenha o Sol no centro
    drawSun();
    
    // Desenha a Terra orbitando o Sol
    drawEarth();
    
    // Desenha a Lua orbitando a Terra
    drawMoon();
    
    // Força o desenho na tela
    glFlush();
}

void timer(int value) {
    // Atualiza os ângulos para criar a animação
    earthAngle += earthSpeed;
    moonAngle += moonSpeed;
    
    // Normaliza os ângulos para evitar overflow
    if (earthAngle >= 360.0f) earthAngle -= 360.0f;
    if (moonAngle >= 360.0f) moonAngle -= 360.0f;
    
    // Redesenha a cena
    glutPostRedisplay();
    
    // Agenda a próxima atualização (16ms = ~60 FPS)
    glutTimerFunc(16, timer, 0);
}

void reshape(int w, int h) {
    // Define a área de desenho
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Calcula a proporção da janela
    float aspect = (float)w / (float)h;
    
    // Mantém o desenho quadrado
    if (w <= h) {
        glOrtho(-1.0, 1.0, -1.0/aspect, 1.0/aspect, -1.0, 1.0);
    } else {
        glOrtho(-1.0*aspect, 1.0*aspect, -1.0, 1.0, -1.0, 1.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    // Inicializa a biblioteca GLUT
    glutInit(&argc, argv);
    
    // Define o modo de display
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // Define o tamanho e posição da janela
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    
    // Cria a janela
    glutCreateWindow("Sistema Solar - Terra e Lua");
    
    // Inicializa o OpenGL
    init();
    
    // Define as funções de callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, timer, 0);  // Inicia a animação
    
    // Inicia o loop principal
    glutMainLoop();
    
    return 0;
}
