# Documento Explicativo Detalhado - Lista 1
## Cálculos Matemáticos e Implementações em OpenGL

---

## Visão Geral da Lista 1

A Lista 1 contém dois programas relacionados ao desenho de um sol amarelo usando OpenGL:

1. **`sol_amarelo.cpp`** - Sol com redimensionamento proporcional
2. **`sol_amarelo_fixo.cpp`** - Sol com tamanho fixo independente do redimensionamento

Ambos os programas implementam um sol com círculo central e raios triangulares, mas diferem no comportamento durante o redimensionamento da janela.

---

## Sol Amarelo - Análise Matemática

### Problema
Desenhar uma figura regular que lembre um sol amarelo com fundo escuro, completamente visível na abertura da janela.

### Componentes do Sol

#### 1. Círculo Central
- **Raio**: 0.3 unidades
- **Cor**: Amarelo (R=1, G=1, B=0)
- **Método**: `GL_TRIANGLE_FAN` com 72 triângulos (360°/5°)

#### 2. Raios Triangulares
- **Número**: 15 raios
- **Comprimento**: 0.4 unidades
- **Largura**: 0.08 unidades
- **Distribuição**: Uniforme em 360°

### Cálculos Matemáticos

#### 1. Desenho do Círculo Central

**Parâmetros:**
```cpp
const float SUN_RADIUS = 0.3f;
const int NUM_SEGMENTS = 72; // 360° / 5° = 72 segmentos
```

**Fórmula para pontos da circunferência:**
```
x = SUN_RADIUS * cos(θ)
y = SUN_RADIUS * sin(θ)
```

**Implementação:**
```cpp
for (int i = 0; i <= 360; i += 5) {
    float angle = i * M_PI / 180.0f;  // Converte graus para radianos
    float x = SUN_RADIUS * cos(angle);
    float y = SUN_RADIUS * sin(angle);
    glVertex2f(x, y);
}
```

**Cálculo do número de triângulos:**
```
Número de triângulos = 360° / incremento_angular
Número de triângulos = 360° / 5° = 72 triângulos
```

#### 2. Desenho dos Raios Triangulares

**Parâmetros:**
```cpp
const int NUM_RAYS = 15;
const float RAY_LENGTH = 0.4f;
const float RAY_WIDTH = 0.08f;
```

**Distribuição angular dos raios:**
```
Ângulo entre raios = 360° / NUM_RAYS
Ângulo entre raios = 360° / 15 = 24°
```

**Posicionamento de cada raio:**
```
raio_angle = (360.0f / NUM_RAYS) * i
raio_angle = 24° * i, onde i = 0, 1, 2, ..., 14
```

**Cálculo das coordenadas dos vértices:**

**Ponto inicial (na borda do círculo):**
```
start_x = SUN_RADIUS * cos(angle)
start_y = SUN_RADIUS * sin(angle)
```

**Ponto final (ponta do raio):**
```
end_x = (SUN_RADIUS + RAY_LENGTH) * cos(angle)
end_y = (SUN_RADIUS + RAY_LENGTH) * sin(angle)
```

**Vetor perpendicular para largura:**
```
perp_x = -sin(angle) * RAY_WIDTH
perp_y = cos(angle) * RAY_WIDTH
```

**Vértices do triângulo:**
```
Vértice 1: (start_x + perp_x, start_y + perp_y)  // Lado direito
Vértice 2: (start_x - perp_x, start_y - perp_y)  // Lado esquerdo
Vértice 3: (end_x, end_y)                        // Ponta
```

#### 3. Exemplo de Cálculo para um Raio

**Para o primeiro raio (i = 0):**
```
angle = (360.0f / 15) * 0 = 0°
angle_rad = 0 * π/180 = 0 radianos

start_x = 0.3 * cos(0) = 0.3 * 1 = 0.3
start_y = 0.3 * sin(0) = 0.3 * 0 = 0

end_x = (0.3 + 0.4) * cos(0) = 0.7 * 1 = 0.7
end_y = (0.3 + 0.4) * sin(0) = 0.7 * 0 = 0

perp_x = -sin(0) * 0.08 = 0 * 0.08 = 0
perp_y = cos(0) * 0.08 = 1 * 0.08 = 0.08

Vértices:
V1: (0.3 + 0, 0 + 0.08) = (0.3, 0.08)
V2: (0.3 - 0, 0 - 0.08) = (0.3, -0.08)
V3: (0.7, 0)
```

**Para o segundo raio (i = 1):**
```
angle = (360.0f / 15) * 1 = 24°
angle_rad = 24 * π/180 ≈ 0.419 radianos

start_x = 0.3 * cos(0.419) ≈ 0.3 * 0.914 ≈ 0.274
start_y = 0.3 * sin(0.419) ≈ 0.3 * 0.407 ≈ 0.122

end_x = 0.7 * cos(0.419) ≈ 0.7 * 0.914 ≈ 0.640
end_y = 0.7 * sin(0.419) ≈ 0.7 * 0.407 ≈ 0.285

perp_x = -sin(0.419) * 0.08 ≈ -0.407 * 0.08 ≈ -0.033
perp_y = cos(0.419) * 0.08 ≈ 0.914 * 0.08 ≈ 0.073

Vértices:
V1: (0.274 + (-0.033), 0.122 + 0.073) = (0.241, 0.195)
V2: (0.274 - (-0.033), 0.122 - 0.073) = (0.307, 0.049)
V3: (0.640, 0.285)
```

---

## Diferenças entre as Versões

### Sol Amarelo (Versão Padrão)

#### Sistema de Coordenadas
- **Projeção**: Ortogonal normalizada (-1 a 1)
- **Comportamento**: Redimensionamento proporcional
- **Aspecto**: Mantém proporção quadrada

#### Cálculo de Aspecto
```cpp
float aspect = (float)w / (float)h;

if (w <= h) {
    // Largura menor - ajusta altura
    glOrtho(-1.0, 1.0, -1.0/aspect, 1.0/aspect, -1.0, 1.0);
} else {
    // Altura menor - ajusta largura
    glOrtho(-1.0*aspect, 1.0*aspect, -1.0, 1.0, -1.0, 1.0);
}
```

**Exemplo de cálculo:**
```
Janela 800x600:
aspect = 800/600 = 1.333
w > h, então:
glOrtho(-1.0*1.333, 1.0*1.333, -1.0, 1.0, -1.0, 1.0)
glOrtho(-1.333, 1.333, -1.0, 1.0, -1.0, 1.0)
```

### Sol Amarelo Fixo (Versão com Tamanho Fixo)

#### Sistema de Coordenadas
- **Projeção**: Ortogonal com ajuste de aspecto
- **Comportamento**: Tamanho fixo em pixels
- **Posicionamento**: Canto inferior esquerdo

#### Parâmetros de Tamanho Fixo
```cpp
const float FIXED_SIZE = 0.8f;  // Tamanho fixo do desenho
```

#### Transformações Aplicadas
```cpp
// 1. Ajuste de aspecto (igual à versão padrão)
glOrtho(-1.0*aspect, 1.0*aspect, -1.0, 1.0, -1.0, 1.0);

// 2. Posicionamento no canto inferior esquerdo
glTranslatef(-1.0f + FIXED_SIZE/2, -1.0f + FIXED_SIZE/2, 0.0f);

// 3. Escala fixa
glScalef(FIXED_SIZE, FIXED_SIZE, 1.0f);
```

#### Cálculo das Transformações

**Posicionamento:**
```
offset_x = -1.0f + FIXED_SIZE/2 = -1.0 + 0.8/2 = -1.0 + 0.4 = -0.6
offset_y = -1.0f + FIXED_SIZE/2 = -1.0 + 0.8/2 = -1.0 + 0.4 = -0.6
```

**Escala:**
```
scale_x = FIXED_SIZE = 0.8
scale_y = FIXED_SIZE = 0.8
```

**Resultado:**
- O sol é desenhado em uma área de 0.8×0.8 unidades
- Posicionado no canto inferior esquerdo
- Mantém tamanho constante independente do redimensionamento

---

## Análise de Performance

### Complexidade Computacional

#### Desenho do Círculo
- **Triângulos**: 72 triângulos
- **Vértices**: 73 vértices (1 centro + 72 circunferência)
- **Complexidade**: O(n) onde n = número de segmentos

#### Desenho dos Raios
- **Triângulos**: 15 triângulos
- **Vértices**: 45 vértices (3 por raio)
- **Complexidade**: O(m) onde m = número de raios

#### Total
- **Triângulos**: 87 triângulos
- **Vértices**: 118 vértices
- **Complexidade**: O(n + m) = O(72 + 15) = O(87)

### Otimizações Implementadas

1. **Cache de valores trigonométricos**: Cálculos feitos uma vez por raio
2. **Uso de GL_TRIANGLE_FAN**: Eficiente para círculos
3. **Uso de GL_TRIANGLES**: Eficiente para raios individuais
4. **Cálculos em tempo de compilação**: Constantes definidas como `const`

---

## Geometria do Sol

### Dimensões Totais

**Raio total (incluindo raios):**
```
raio_total = SUN_RADIUS + RAY_LENGTH
raio_total = 0.3 + 0.4 = 0.7 unidades
```

**Diâmetro total:**
```
diâmetro_total = 2 * raio_total = 2 * 0.7 = 1.4 unidades
```

### Área de Cobertura

**Área do círculo central:**
```
área_círculo = π * SUN_RADIUS²
área_círculo = π * 0.3² = π * 0.09 ≈ 0.283 unidades²
```

**Área de um raio:**
```
área_raio = (RAY_LENGTH * RAY_WIDTH) / 2
área_raio = (0.4 * 0.08) / 2 = 0.032 / 2 = 0.016 unidades²
```

**Área total dos raios:**
```
área_total_raios = NUM_RAYS * área_raio
área_total_raios = 15 * 0.016 = 0.24 unidades²
```

**Área total do sol:**
```
área_total = área_círculo + área_total_raios
área_total = 0.283 + 0.24 = 0.523 unidades²
```

---

## Sistema de Cores

### Modelo RGB

**Cor do sol:**
```cpp
glColor3f(1.0f, 1.0f, 0.0f);  // Amarelo
```
- **R (Red)**: 1.0 (máximo)
- **G (Green)**: 1.0 (máximo)
- **B (Blue)**: 0.0 (mínimo)

**Cor de fundo:**
```cpp
glClearColor(0.1f, 0.1f, 0.3f, 1.0f);  // Azul escuro
```
- **R (Red)**: 0.1 (muito baixo)
- **G (Green)**: 0.1 (muito baixo)
- **B (Blue)**: 0.3 (baixo)
- **A (Alpha)**: 1.0 (opaco)

### Contraste
- **Contraste**: Alto contraste entre amarelo e azul escuro
- **Visibilidade**: Excelente visibilidade do sol contra o fundo
- **Estética**: Combinação clássica de cores complementares

---

## Implementação OpenGL

### Funções Principais

#### `init()`
- Configura cor de fundo
- Define projeção ortogonal
- Inicializa matriz de modelo

#### `display()`
- Limpa buffer de cor
- Desenha o sol
- Força atualização da tela

#### `reshape(int w, int h)`
- Ajusta viewport
- Recalcula projeção
- Mantém proporções

#### `drawSun()`
- Desenha círculo central
- Desenha raios triangulares
- Aplica cores

### Primitivas OpenGL Utilizadas

1. **`GL_TRIANGLE_FAN`**: Para círculo central
2. **`GL_TRIANGLES`**: Para raios individuais
3. **`glVertex2f()`**: Para definir vértices
4. **`glColor3f()`**: Para definir cores

---

## Resumo Matemático

### Fórmulas Principais

#### Coordenadas Circulares
```
x = r * cos(θ)
y = r * sin(θ)
```

#### Distribuição Angular
```
ângulo_raio = (360° / NUM_RAYS) * i
```

#### Vetor Perpendicular
```
perp_x = -sin(θ) * largura
perp_y = cos(θ) * largura
```

#### Transformação de Escala Fixa
```
nova_x = (x - offset_x) * escala + offset_x
nova_y = (y - offset_y) * escala + offset_y
```

### Parâmetros Otimizados

- **72 segmentos**: Equilíbrio entre suavidade e performance
- **15 raios**: Distribuição visualmente agradável
- **5° de incremento**: Suavidade adequada para círculo
- **24° entre raios**: Distribuição uniforme

---

## Conclusão

A Lista 1 demonstra conceitos fundamentais de:

1. **Geometria Computacional**: Cálculo de coordenadas circulares
2. **Trigonometria**: Uso de seno e cosseno para posicionamento
3. **Transformações 2D**: Translação e escala
4. **Sistemas de Coordenadas**: Projeção ortogonal e ajuste de aspecto
5. **Otimização**: Uso eficiente de primitivas OpenGL

Os dois programas mostram diferentes abordagens para o mesmo problema visual, demonstrando a flexibilidade do OpenGL em lidar com diferentes requisitos de redimensionamento e posicionamento.
