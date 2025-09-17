# Documento Explicativo Detalhado - Lista 2
## Cálculos Matemáticos e Implementações em OpenGL

---

## Q1 - Sistema Solar (Órbitas da Terra e Lua)

### Problema
Simular as órbitas da Terra e da Lua ao redor do Sol em animação 2D.

### Cálculos Matemáticos

#### 1. Posicionamento Orbital
**Terra orbitando o Sol:**
```
x_terra = EARTH_ORBIT_RADIUS * cos(earthAngle)
y_terra = EARTH_ORBIT_RADIUS * sin(earthAngle)
```

**Lua orbitando a Terra:**
```
x_lua = x_terra + MOON_ORBIT_RADIUS * cos(moonAngle)
y_lua = y_terra + MOON_ORBIT_RADIUS * sin(moonAngle)
```

#### 2. Parâmetros do Sistema
- **Raio do Sol**: 0.1 unidades
- **Raio da Terra**: 0.05 unidades  
- **Raio da Lua**: 0.02 unidades
- **Raio da órbita da Terra**: 0.6 unidades
- **Raio da órbita da Lua**: 0.15 unidades
- **Velocidade da Terra**: 1°/frame
- **Velocidade da Lua**: 3°/frame (3x mais rápida)

#### 3. Animação Temporal
```cpp
earthAngle += earthSpeed;  // Incrementa ângulo da Terra
moonAngle += moonSpeed;    // Incrementa ângulo da Lua

// Normalização para evitar overflow
if (earthAngle >= 360.0f) earthAngle -= 360.0f;
if (moonAngle >= 360.0f) moonAngle -= 360.0f;
```

#### 4. Desenho de Círculos
```cpp
// Usando GL_TRIANGLE_FAN para círculos preenchidos
for (int i = 0; i <= 360; i += 5) {
    float angle = i * M_PI / 180.0f;
    float x = radius * cos(angle);
    float y = radius * sin(angle);
    glVertex2f(x, y);
}
```

---

## Q2 - Análise de Matrizes na Pilha OpenGL

### Problema
Analisar a evolução das matrizes na pilha durante execução de código com `glPushMatrix()` e `glPopMatrix()`.

### Cálculos Matemáticos

#### 1. Matrizes de Transformação

**Matriz de Translação T1 = T2:**
```
T = [1  0  0.5]
    [0  1  0.5]
    [0  0  1  ]
```

**Matriz de Rotação R (45°):**
```
R = [cos(45°)  -sin(45°)  0]   [0.707  -0.707  0]
    [sin(45°)   cos(45°)  0] = [0.707   0.707  0]
    [0          0         1]   [0       0      1]
```

#### 2. Composição de Matrizes

**Para o segundo quadrado:**
```
T2R = T2 * R = [0.707  -0.707  0.5]
               [0.707   0.707  0.5]
               [0       0      1  ]
```

#### 3. Evolução da Pilha

| Operação | Pilha | Topo | Descrição |
|----------|-------|------|-----------|
| Inicial | [I] | I | Matriz identidade |
| PushMatrix | [I, I] | I | Salva identidade |
| T1 | [I, T1] | T1 | Aplica translação |
| PopMatrix | [I] | I | Restaura identidade |
| PushMatrix | [I, I] | I | Salva identidade |
| T2 | [I, T2] | T2 | Aplica translação |
| R | [I, T2R] | T2R | Aplica rotação |
| PopMatrix | [I] | I | Restaura identidade |

---

## Q3 - Versão Reescrita sem Push/Pop

### Problema
Reescrever o código mantendo o mesmo comportamento sem usar `glPushMatrix()` e `glPopMatrix()`.

### Solução Matemática

#### 1. Substituição de Push/Pop por LoadIdentity
**Código Original:**
```cpp
glPushMatrix();
glTranslatef(0.5, 0.5, 0);
glRectf(-0.25, -0.25, 0.25, 0.25);
glPopMatrix();
```

**Código Reescrito:**
```cpp
glLoadIdentity();
glTranslatef(0.5, 0.5, 0);
glRectf(-0.25, -0.25, 0.25, 0.25);
```

#### 2. Equivalência Matemática
- **Original**: Pilha varia `[I] → [I,I] → [I,T1] → [I]`
- **Reescrito**: Pilha constante `[I]` no início de cada bloco
- **Resultado**: Mesmo comportamento visual

#### 3. Vantagens da Versão Reescrita
- Pilha constante (sem variação de tamanho)
- Menos operações de pilha
- Funcionalmente equivalente
- Mais flexível para modificações

---

## Q4 - Paralelogramo e Losango

### Problema
Desenhar paralelogramo com lados iguais e ângulo interno de 30°, depois transformar em losango.

### Cálculos Matemáticos

#### 1. Paralelogramo - Método 1 (Cisalhamento)

**Matriz de Cisalhamento Horizontal:**
```
S = [1     0   0]
    [tan(30°) 1   0]
    [0     0   1]
```

**Para α = 30°:**
```
tan(30°) = 1/√3 ≈ 0.577

S = [1.000  0.000  0]
    [0.577  1.000  0]
    [0.000  0.000  1]
```

#### 2. Paralelogramo - Método 2 (Rotação + Escala)

**Sequência de transformações:**
1. Rotação de 30°
2. Escala vertical para compensar deformação

**Escala de compensação:**
```
scaleY = 1/cos(30°) = 2/√3 ≈ 1.155
```

#### 3. Losango (Transformação do Paralelogramo)

**Composição:**
```
Losango = Cisalhamento(30°) * Rotação(30°)
```

**Matriz resultante:**
```
L = [cos(30°)  -sin(30°)  0] * [1.000  0.000  0]
    [sin(30°)   cos(30°)  0]   [0.577  1.000  0]
    [0          0         1]   [0.000  0.000  1]

L = [0.866  -0.500  0]
    [0.500   0.866  0]
    [0       0      1]
```

#### 4. Propriedades Geométricas
- **Paralelogramo**: Ângulos internos de 30° e 150°
- **Losango**: Mesmas dimensões, ângulos de 30° e 150°
- **Área**: Mantida constante durante transformações

---

## Q5 - Rotação e Recorte (Liang-Barsky)

### Problema
Rotacionar triângulo A(0,0), B(0,1), C(0.5,1) por 60° em torno de (0.5,0.5) e recortar contra retângulo (0,0) a (1,1).

### Cálculos Matemáticos

#### 1. Rotação em torno de Ponto

**Fórmula geral:**
```
x' = cx + (x - cx) * cos(θ) - (y - cy) * sin(θ)
y' = cy + (x - cx) * sin(θ) + (y - cy) * cos(θ)
```

**Para θ = 60°, centro = (0.5, 0.5):**
- cos(60°) = 0.5
- sin(60°) = √3/2 ≈ 0.866

**Ponto A(0,0):**
```
x_rel = 0 - 0.5 = -0.5
y_rel = 0 - 0.5 = -0.5
x' = 0.5 + (-0.5) * 0.5 - (-0.5) * 0.866 = 0.683
y' = 0.5 + (-0.5) * 0.866 + (-0.5) * 0.5 = -0.183
A' = (0.683, -0.183)
```

**Ponto B(0,1):**
```
x_rel = 0 - 0.5 = -0.5
y_rel = 1 - 0.5 = 0.5
x' = 0.5 + (-0.5) * 0.5 - 0.5 * 0.866 = -0.183
y' = 0.5 + (-0.5) * 0.866 + 0.5 * 0.5 = 0.317
B' = (-0.183, 0.317)
```

**Ponto C(0.5,1):**
```
x_rel = 0.5 - 0.5 = 0
y_rel = 1 - 0.5 = 0.5
x' = 0.5 + 0 * 0.5 - 0.5 * 0.866 = 0.067
y' = 0.5 + 0 * 0.866 + 0.5 * 0.5 = 0.75
C' = (0.067, 0.75)
```

#### 2. Algoritmo de Liang-Barsky

**Parâmetros do retângulo:** X_MIN=0, X_MAX=1, Y_MIN=0, Y_MAX=1

**Para cada aresta, calcular:**
```
dx = x2 - x1
dy = y2 - y1
p[4] = {-dx, dx, -dy, dy}
q[4] = {x1-X_MIN, X_MAX-x1, y1-Y_MIN, Y_MAX-y1}
```

**Aresta A'B': (0.683, -0.183) a (-0.183, 0.317)**
```
dx = -0.183 - 0.683 = -0.866
dy = 0.317 - (-0.183) = 0.5
p = {0.866, -0.866, -0.5, 0.5}
q = {0.683, 0.317, -0.183, 1.183}

t1 = max(0, q[0]/p[0], q[2]/p[2]) = max(0, 0.789, 0.366) = 0.789
t2 = min(1, q[1]/p[1], q[3]/p[3]) = min(1, -0.366, 2.366) = -0.366

Como t1 > t2: aresta completamente fora da janela
```

**Aresta B'C': (-0.183, 0.317) a (0.067, 0.75)**
```
dx = 0.067 - (-0.183) = 0.25
dy = 0.75 - 0.317 = 0.433
p = {-0.25, 0.25, -0.433, 0.433}
q = {-0.183, 1.183, 0.317, 0.683}

t1 = max(0, 0.732, -0.732) = 0.732
t2 = min(1, 4.732, 1.577) = 1

Segmento visível: t1 a t2
Ponto inicial: (-0.000, 0.634)
Ponto final: (0.067, 0.75)
```

**Aresta A'C': (0.683, -0.183) a (0.067, 0.75)**
```
dx = 0.067 - 0.683 = -0.616
dy = 0.75 - (-0.183) = 0.933
p = {0.616, -0.616, -0.933, 0.933}
q = {0.683, 0.317, -0.183, 1.183}

t1 = max(0, 1.109, 0.196) = 1.109
t2 = min(1, -0.515, 1.268) = -0.515

Como t1 > t2: aresta completamente fora da janela
```

#### 3. Resultado Final
Apenas a **aresta B'C'** é visível: segmento de (-0.000, 0.634) a (0.067, 0.75)

---

## Q6 - Braço Robótico (Cinemática)

### Problema
Braço robótico com 2 elos: L1=0.4, L2=0.3, α=60°, β=-30°. Calcular matrizes de transformação e origens dos sistemas.

### Cálculos Matemáticos

#### 1. Matrizes de Transformação Homogêneas

**T01 (F0 → F1) - Rotação de α:**
```
T01 = R(α) = [cos(60°)  -sin(60°)  0]   [0.500  -0.866  0]
             [sin(60°)   cos(60°)  0] = [0.866   0.500  0]
             [0          0         1]   [0       0      1]
```

**T12 (F1 → F2) - Translação(L1) * Rotação(β):**
```
T12 = T(L1,0) * R(β) = [cos(-30°)  -sin(-30°)  L1*cos(-30°)]
                       [sin(-30°)   cos(-30°)  L1*sin(-30°)]
                       [0           0          1           ]

T12 = [0.866   0.500  0.346]
      [-0.500  0.866  -0.200]
      [0       0      1     ]
```

**T02 (F0 → F2) - Composição:**
```
T02 = T01 * T12 = [cos(α+β)  -sin(α+β)  L1*cos(α)]
                  [sin(α+β)   cos(α+β)  L1*sin(α)]
                  [0          0         1        ]

T02 = [0.866  -0.500  0.200]
      [0.500   0.866  0.346]
      [0       0      1     ]
```

#### 2. Origens dos Sistemas de Referência

**Origem de F1 em coordenadas de F0:**
```
F1_x = L1 * cos(α) = 0.4 * cos(60°) = 0.4 * 0.5 = 0.200
F1_y = L1 * sin(α) = 0.4 * sin(60°) = 0.4 * 0.866 = 0.346
F1 = (0.200, 0.346)
```

**Origem de F2 em coordenadas de F0:**
```
F2_x = L1*cos(α) + L2*cos(α+β) = 0.4*cos(60°) + 0.3*cos(30°)
F2_x = 0.4*0.5 + 0.3*0.866 = 0.200 + 0.260 = 0.460

F2_y = L1*sin(α) + L2*sin(α+β) = 0.4*sin(60°) + 0.3*sin(30°)
F2_y = 0.4*0.866 + 0.3*0.5 = 0.346 + 0.150 = 0.496
F2 = (0.460, 0.496)
```

#### 3. Composição das Transformações

**Para F0 → F1:**
```
T01 = R(α)
```

**Para F0 → F2:**
```
T02 = R(α) * T(L1,0) * R(β)
```

#### 4. Verificação Matemática

**Usando matrizes de transformação:**

**Origem de F1:**
```
[F1_x]   [0.500  -0.866  0] [0]   [0.200]
[F1_y] = [0.866   0.500  0] [0] = [0.346]
[1   ]   [0       0      1] [1]   [1    ]
```

**Origem de F2:**
```
[F2_x]   [0.866  -0.500  0.200] [0]   [0.460]
[F2_y] = [0.500   0.866  0.346] [0] = [0.496]
[1   ]   [0       0      1     ] [1]   [1    ]
```

---

## Resumo Geral

### Conceitos Matemáticos Aplicados

1. **Geometria Analítica**: Coordenadas cartesianas, distâncias, ângulos
2. **Trigonometria**: Seno, cosseno, tangente para rotações e posicionamento
3. **Álgebra Linear**: Matrizes de transformação, multiplicação de matrizes
4. **Cinemática**: Transformações homogêneas, composição de movimentos
5. **Algoritmos Computacionais**: Liang-Barsky para recorte, animação temporal

### Implementações OpenGL

1. **Q1**: Animação com `glutTimerFunc`, desenho de círculos com `GL_TRIANGLE_FAN`
2. **Q2**: Manipulação de pilha de matrizes com `glPushMatrix`/`glPopMatrix`
3. **Q3**: Substituição por `glLoadIdentity` mantendo equivalência funcional
4. **Q4**: Transformações geométricas com `glMultMatrixf`, `glRotatef`, `glScalef`
5. **Q5**: Algoritmo de recorte implementado com cálculos paramétricos
6. **Q6**: Cinemática de robôs com matrizes homogêneas e visualização

### Resultados Principais

- **Q1**: Sistema solar animado com órbitas circulares
- **Q2**: Análise completa da evolução das matrizes na pilha
- **Q3**: Versão equivalente sem operações de pilha
- **Q4**: Paralelogramo e losango com transformações geométricas
- **Q5**: Recorte de triângulo rotacionado usando Liang-Barsky
- **Q6**: Cinemática completa de braço robótico com 2 elos

Todos os programas demonstram aplicações práticas de matemática computacional em gráficos 3D/2D usando OpenGL.
