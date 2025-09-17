//Use seus conhecimentos adquiridos em OpenGL e faca um programa cuja saıda grafica seja uma figura regular
//que lembre um sol amarelo com fundo escuro. Na abertura da janela, a figura deve estar completamente
//visıvel no display.

// Inclui a biblioteca GLUT para OpenGL no macOS
#include <GLUT/glut.h>
// Inclui a biblioteca matemática para funções como cos() e sin()
#include <math.h>

// Declaração das funções que serão implementadas
void init();        // Função para inicializar o OpenGL
void display();     // Função para desenhar o sol
void reshape(int w, int h);  // Função para redimensionar a janela

// Parâmetros do sol - constantes que definem as características visuais
const int NUM_RAYS = 15;     // Número de raios do sol (15 extremidades)
const float SUN_RADIUS = 0.3f;  // Raio do círculo central do sol
const float RAY_LENGTH = 0.4f;  // Comprimento dos raios (distância da ponta ao centro)
const float RAY_WIDTH = 0.08f;  // Largura dos raios (aumentada para se encostarem)

void init() {
    // Define a cor de fundo escura (azul escuro) - valores RGB + alpha
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    
    // Define o sistema de visualização - tipo de projeção ortogonal
    glMatrixMode(GL_PROJECTION);  // Seleciona a matriz de projeção
    glLoadIdentity();             // Carrega a matriz identidade (limpa transformações)
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // Cria sistema de coordenadas normalizado
    
    // Define a matriz de modelo para o centro da tela
    glMatrixMode(GL_MODELVIEW);   // Seleciona a matriz de modelo/visualização
    glLoadIdentity();             // Carrega a matriz identidade (limpa transformações)
}

void drawSun() {
    // Desenha o círculo central do sol (amarelo)
    glColor3f(1.0f, 1.0f, 0.0f);  // Define cor amarela (R=1, G=1, B=0)
    
    glBegin(GL_TRIANGLE_FAN);     // Inicia desenho de triângulos em leque
    glVertex2f(0.0f, 0.0f);      // Define o centro do círculo (vértice central)
    
    // Cria um círculo com muitos triângulos para suavidade
    for (int i = 0; i <= 360; i += 5) {  // Loop de 0 a 360 graus, incrementando de 5 em 5
        float angle = i * M_PI / 180.0f;  // Converte graus para radianos
        float x = SUN_RADIUS * cos(angle); // Calcula coordenada X do ponto na circunferência
        float y = SUN_RADIUS * sin(angle); // Calcula coordenada Y do ponto na circunferência
        glVertex2f(x, y);                 // Define vértice do triângulo na circunferência
    }
    glEnd();  // Finaliza o desenho do círculo
    
    // Desenha os raios do sol (triangulares)
    glColor3f(1.0f, 1.0f, 0.0f);  // Define cor amarela para os raios
    
    for (int i = 0; i < NUM_RAYS; i++) {  // Loop para desenhar cada raio
        float angle = (360.0f / NUM_RAYS) * i * M_PI / 180.0f;  // Calcula ângulo do raio atual
        
        // Calcula as posições dos vértices do raio triangular
        float start_x = SUN_RADIUS * cos(angle);  // Coordenada X do início do raio (na borda do círculo)
        float start_y = SUN_RADIUS * sin(angle);  // Coordenada Y do início do raio (na borda do círculo)
        float end_x = (SUN_RADIUS + RAY_LENGTH) * cos(angle);  // Coordenada X da ponta do raio
        float end_y = (SUN_RADIUS + RAY_LENGTH) * sin(angle);  // Coordenada Y da ponta do raio
        
        // Calcula a direção perpendicular para a largura da base do triângulo
        float perp_x = -sin(angle) * RAY_WIDTH;  // Componente X perpendicular (para largura)
        float perp_y = cos(angle) * RAY_WIDTH;   // Componente Y perpendicular (para largura)
        
        // Desenha o raio como um triângulo
        glBegin(GL_TRIANGLES);  // Inicia desenho de triângulos
        glVertex2f(start_x + perp_x, start_y + perp_y);  // Vértice da base (lado direito)
        glVertex2f(start_x - perp_x, start_y - perp_y);  // Vértice da base (lado esquerdo)
        glVertex2f(end_x, end_y);                        // Ponto do triângulo (ponta do raio)
        glEnd();  // Finaliza o desenho do triângulo
    }
}

void display() {
    // Limpa a janela com a cor de fundo definida em glClearColor()
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Desenha o sol (círculo + raios triangulares)
    drawSun();
    
    // Força o desenho na tela (envia comandos para o buffer de vídeo)
    glFlush();
}

void reshape(int w, int h) {
    // Mantém a proporção da janela - define a área de desenho
    glViewport(0, 0, w, h);  // Define viewport (área de desenho) com nova largura e altura
    
    glMatrixMode(GL_PROJECTION);  // Seleciona matriz de projeção
    glLoadIdentity();             // Carrega matriz identidade (limpa transformações)
    
    // Calcula a proporção da janela (largura/altura)
    float aspect = (float)w / (float)h;
    
    if (w <= h) {
        // Largura menor, estica a altura para manter proporção quadrada
        glOrtho(-1.0, 1.0, -1.0/aspect, 1.0/aspect, -1.0, 1.0);
    } else {
        // Altura menor, estica a largura para manter proporção quadrada
        glOrtho(-1.0*aspect, 1.0*aspect, -1.0, 1.0, -1.0, 1.0);
    }
    
    glMatrixMode(GL_MODELVIEW);  // Volta para matriz de modelo/visualização
}

int main(int argc, char** argv) {
    // Inicializa a biblioteca GLUT com argumentos da linha de comando
    glutInit(&argc, argv);
    
    // Define o modo de display (buffer simples + RGB)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // Define o tamanho da janela (800x800 pixels)
    glutInitWindowSize(800, 800);
    // Define a posição inicial da janela (100, 100 pixels da borda superior esquerda)
    glutInitWindowPosition(100, 100);
    
    // Cria a janela com o título especificado
    glutCreateWindow("Sol Amarelo - OpenGL");
    
    // Inicializa o OpenGL (configurações de cor, projeção, etc.)
    init();
    
    // Define as funções de callback (chamadas automáticas)
    glutDisplayFunc(display);   // Função chamada para redesenhar a janela
    glutReshapeFunc(reshape);   // Função chamada quando a janela é redimensionada
    
    // Inicia o loop principal do GLUT (fica executando até fechar a janela)
    glutMainLoop();
    
    return 0;  // Retorna 0 indicando execução bem-sucedida
}
