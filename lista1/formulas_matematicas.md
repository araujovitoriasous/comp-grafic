# Fórmulas Matemáticas - Lista 1
## Referência Rápida para Desenho de Sol Amarelo

---

## 1. Trigonometria Básica

### Conversão Graus ↔ Radianos
```
radianos = graus * π/180
graus = radianos * 180/π
```

### Valores Importantes
```
π ≈ 3.14159
π/2 ≈ 1.5708
π/4 ≈ 0.7854
π/6 ≈ 0.5236
π/12 ≈ 0.2618
```

### Funções Trigonométricas
```
sin(0°) = 0          cos(0°) = 1
sin(30°) = 0.5       cos(30°) = √3/2 ≈ 0.866
sin(45°) = √2/2 ≈ 0.707  cos(45°) = √2/2 ≈ 0.707
sin(60°) = √3/2 ≈ 0.866  cos(60°) = 0.5
sin(90°) = 1         cos(90°) = 0
```

---

## 2. Geometria Circular

### Coordenadas de Ponto na Circunferência
```
x = r * cos(θ)
y = r * sin(θ)
```

### Distância do Centro
```
r = √(x² + y²)
```

### Ângulo de um Ponto
```
θ = atan2(y, x)
```

### Perímetro da Circunferência
```
perímetro = 2πr
```

### Área do Círculo
```
área = πr²
```

---

## 3. Distribuição Angular Uniforme

### Ângulo entre Elementos
```
ângulo_entre = 360° / número_elementos
```

### Ângulo do Elemento i
```
ângulo_i = (360° / número_elementos) * i
```

### Exemplo: 15 Raios
```
ângulo_entre_raios = 360° / 15 = 24°
raio_0 = 0°
raio_1 = 24°
raio_2 = 48°
...
raio_14 = 336°
```

---

## 4. Vetores Perpendiculares

### Vetor Perpendicular (90° no sentido anti-horário)
```
perp_x = -sin(θ) * magnitude
perp_y = cos(θ) * magnitude
```

### Vetor Perpendicular (90° no sentido horário)
```
perp_x = sin(θ) * magnitude
perp_y = -cos(θ) * magnitude
```

### Normalização de Vetor
```
magnitude = √(x² + y²)
x_normalizado = x / magnitude
y_normalizado = y / magnitude
```

---

## 5. Geometria de Triângulos

### Área de Triângulo (fórmula de Heron)
```
s = (a + b + c) / 2
área = √(s * (s-a) * (s-b) * (s-c))
```

### Área de Triângulo (coordenadas)
```
área = |(x1(y2-y3) + x2(y3-y1) + x3(y1-y2)) / 2|
```

### Centroide de Triângulo
```
centro_x = (x1 + x2 + x3) / 3
centro_y = (y1 + y2 + y3) / 3
```

---

## 6. Transformações 2D

### Translação
```
x' = x + tx
y' = y + ty
```

### Escala
```
x' = x * sx
y' = y * sy
```

### Rotação em torno da Origem
```
x' = x*cos(θ) - y*sin(θ)
y' = x*sin(θ) + y*cos(θ)
```

### Rotação em torno de Ponto (cx, cy)
```
x' = cx + (x-cx)*cos(θ) - (y-cy)*sin(θ)
y' = cy + (x-cx)*sin(θ) + (y-cy)*cos(θ)
```

---

## 7. Sistemas de Coordenadas

### Coordenadas Normalizadas OpenGL
```
Range X: [-1, 1]
Range Y: [-1, 1]
Range Z: [-1, 1]
```

### Conversão de Aspecto
```
aspect = largura / altura

Se largura ≤ altura:
    glOrtho(-1, 1, -1/aspect, 1/aspect, -1, 1)

Se altura < largura:
    glOrtho(-1*aspect, 1*aspect, -1, 1, -1, 1)
```

### Posicionamento no Canto Inferior Esquerdo
```
offset_x = -1.0 + tamanho/2
offset_y = -1.0 + tamanho/2
```

---

## 8. Cálculos de Performance

### Número de Triângulos para Círculo
```
triângulos = 360° / incremento_angular
```

### Número de Vértices para Círculo
```
vértices = triângulos + 1  // +1 para o centro
```

### Exemplo: Incremento de 5°
```
triângulos = 360° / 5° = 72
vértices = 72 + 1 = 73
```

---

## 9. Cálculos de Área

### Área do Círculo Central
```
área_círculo = π * raio²
área_círculo = π * 0.3² = π * 0.09 ≈ 0.283
```

### Área de um Raio Triangular
```
área_raio = (comprimento * largura) / 2
área_raio = (0.4 * 0.08) / 2 = 0.032 / 2 = 0.016
```

### Área Total dos Raios
```
área_total_raios = número_raios * área_raio
área_total_raios = 15 * 0.016 = 0.24
```

### Área Total do Sol
```
área_total = área_círculo + área_total_raios
área_total = 0.283 + 0.24 = 0.523
```

---

## 10. Modelo de Cores RGB

### Cor Amarela
```
R = 1.0 (máximo)
G = 1.0 (máximo)
B = 0.0 (mínimo)
```

### Cor Azul Escura
```
R = 0.1 (muito baixo)
G = 0.1 (muito baixo)
B = 0.3 (baixo)
```

### Conversão RGB para HSV
```
V = max(R, G, B)
S = (V - min(R, G, B)) / V
H = função_complexa(R, G, B)
```

---

## 11. Otimizações Computacionais

### Cache de Valores Trigonométricos
```cpp
// Calcular uma vez por raio
float cos_angle = cos(angle);
float sin_angle = sin(angle);

// Usar múltiplas vezes
start_x = SUN_RADIUS * cos_angle;
start_y = SUN_RADIUS * sin_angle;
end_x = (SUN_RADIUS + RAY_LENGTH) * cos_angle;
end_y = (SUN_RADIUS + RAY_LENGTH) * sin_angle;
perp_x = -sin_angle * RAY_WIDTH;
perp_y = cos_angle * RAY_WIDTH;
```

### Evitar Cálculos Repetitivos
```cpp
// Calcular uma vez
float angle_increment = 360.0f / NUM_RAYS;

// Usar em loop
for (int i = 0; i < NUM_RAYS; i++) {
    float angle = angle_increment * i * M_PI / 180.0f;
    // ...
}
```

---

## 12. Validação de Parâmetros

### Verificação de Raios
```
0 < NUM_RAYS < 360
```

### Verificação de Dimensões
```
SUN_RADIUS > 0
RAY_LENGTH > 0
RAY_WIDTH > 0
```

### Verificação de Incremento Angular
```
incremento_angular > 0
incremento_angular ≤ 360
```

---

## 13. Fórmulas de Interpolação

### Interpolação Linear
```
valor = valor_inicial + t * (valor_final - valor_inicial)
onde t ∈ [0, 1]
```

### Interpolação Circular
```
x = centro_x + raio * cos(θ_inicial + t * (θ_final - θ_inicial))
y = centro_y + raio * sin(θ_inicial + t * (θ_final - θ_inicial))
```

---

## 14. Cálculos de Distância

### Distância Euclidiana
```
d = √((x2-x1)² + (y2-y1)²)
```

### Distância ao Quadrado (para comparações)
```
d² = (x2-x1)² + (y2-y1)²
```

### Distância de Ponto a Linha
```
d = |ax + by + c| / √(a² + b²)
```

---

## 15. Fórmulas de Precisão

### Comparação de Ponto Flutuante
```
if (fabs(valor1 - valor2) < epsilon)
    valores_são_iguais = true
```

### Epsilon Recomendado
```
epsilon = 1e-6  // Para coordenadas normalizadas
```

### Arredondamento
```
valor_arredondado = floor(valor + 0.5)
```

---

## Resumo de Uso na Lista 1

### Fórmulas Mais Utilizadas
1. **Coordenadas circulares** (item 2)
2. **Distribuição angular uniforme** (item 3)
3. **Vetores perpendiculares** (item 4)
4. **Transformações 2D** (item 6)
5. **Sistemas de coordenadas** (item 7)

### Parâmetros Específicos
- **SUN_RADIUS**: 0.3
- **RAY_LENGTH**: 0.4
- **RAY_WIDTH**: 0.08
- **NUM_RAYS**: 15
- **Incremento angular**: 5°

### Otimizações Aplicadas
- Cache de valores trigonométricos
- Cálculos em tempo de compilação
- Uso eficiente de primitivas OpenGL

Estas fórmulas formam a base matemática para o desenho do sol amarelo na Lista 1.
