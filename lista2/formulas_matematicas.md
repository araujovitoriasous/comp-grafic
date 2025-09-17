# Fórmulas Matemáticas - Lista 2
## Referência Rápida para Cálculos

---

## 1. Trigonometria Básica

### Valores Importantes
```
sin(30°) = 0.5          cos(30°) = √3/2 ≈ 0.866
sin(45°) = √2/2 ≈ 0.707 cos(45°) = √2/2 ≈ 0.707
sin(60°) = √3/2 ≈ 0.866 cos(60°) = 0.5
tan(30°) = 1/√3 ≈ 0.577 tan(45°) = 1
```

### Conversão Graus ↔ Radianos
```
radianos = graus * π/180
graus = radianos * 180/π
```

---

## 2. Transformações Geométricas

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

### Cisalhamento Horizontal
```
x' = x + y*sh
y' = y
```

---

## 3. Matrizes de Transformação Homogêneas

### Matriz de Rotação
```
R(θ) = [cos(θ)  -sin(θ)  0]
       [sin(θ)   cos(θ)  0]
       [0        0       1]
```

### Matriz de Translação
```
T(tx,ty) = [1  0  tx]
           [0  1  ty]
           [0  0  1 ]
```

### Matriz de Escala
```
S(sx,sy) = [sx  0   0]
           [0   sy  0]
           [0   0   1]
```

### Matriz de Cisalhamento
```
H(sh) = [1  sh  0]
        [0  1   0]
        [0  0   1]
```

---

## 4. Composição de Transformações

### Ordem Importante
```
T2 * T1 = "Aplica T1 primeiro, depois T2"
```

### Exemplos Comuns
```
Rotação + Translação: T(tx,ty) * R(θ)
Translação + Rotação: R(θ) * T(tx,ty)
```

---

## 5. Cinemática de Robôs

### Transformação Composta (2 Elos)
```
T02 = R(α) * T(L1,0) * R(β)
```

### Posição Final
```
x = L1*cos(α) + L2*cos(α+β)
y = L1*sin(α) + L2*sin(α+β)
```

---

## 6. Algoritmo de Liang-Barsky

### Parâmetros da Linha
```
dx = x2 - x1
dy = y2 - y1
```

### Parâmetros de Recorte
```
p[0] = -dx    q[0] = x1 - X_MIN
p[1] = dx     q[1] = X_MAX - x1
p[2] = -dy    q[2] = y1 - Y_MIN
p[3] = dy     q[3] = Y_MAX - y1
```

### Parâmetros t
```
t1 = max(0, q[i]/p[i] para p[i] < 0)
t2 = min(1, q[i]/p[i] para p[i] > 0)
```

### Condição de Visibilidade
```
Se t1 ≤ t2: linha é visível
Se t1 > t2: linha está completamente fora
```

### Pontos Recortados
```
x_clipped = x1 + t * dx
y_clipped = y1 + t * dy
```

---

## 7. Geometria de Círculos

### Equação Paramétrica
```
x = cx + r * cos(θ)
y = cy + r * sin(θ)
```

### Para Desenho com Triângulos
```
Para i = 0 até 360, incremento de 5:
    θ = i * π/180
    x = r * cos(θ)
    y = r * sin(θ)
```

---

## 8. Propriedades de Paralelogramos

### Ângulos Internos
```
Ângulo agudo + Ângulo obtuso = 180°
```

### Cisalhamento para Ângulo α
```
shear_factor = tan(α)
```

### Escala de Compensação
```
scale_factor = 1/cos(α)
```

---

## 9. Coordenadas Polares ↔ Cartesianas

### Para Polar → Cartesiana
```
x = r * cos(θ)
y = r * sin(θ)
```

### Para Cartesiana → Polar
```
r = √(x² + y²)
θ = atan2(y, x)
```

---

## 10. Normalização de Ângulos

### Para Evitar Overflow
```
if (angle >= 360°) angle -= 360°
if (angle < 0°) angle += 360°
```

### Para Radianos
```
if (angle >= 2π) angle -= 2π
if (angle < 0) angle += 2π
```

---

## 11. Fórmulas de Distância

### Distância Euclidiana
```
d = √((x2-x1)² + (y2-y1)²)
```

### Distância Manhattan
```
d = |x2-x1| + |y2-y1|
```

---

## 12. Interpolação Linear

### Entre Dois Pontos
```
x = x1 + t*(x2-x1)
y = y1 + t*(y2-y1)
onde t ∈ [0,1]
```

### Para Animação
```
valor_atual = valor_inicial + progresso*(valor_final-valor_inicial)
```

---

## 13. Verificação de Colisão

### Ponto dentro de Retângulo
```
if (x >= X_MIN && x <= X_MAX && y >= Y_MIN && y <= Y_MAX)
    ponto_está_dentro = true
```

### Linha intersecta Retângulo
```
Use algoritmo de Liang-Barsky
```

---

## 14. Otimizações Computacionais

### Cache de Valores Trigonométricos
```
cos_angle = cos(angle)  // Calcular uma vez
sin_angle = sin(angle)  // Calcular uma vez
```

### Evitar Cálculos Repetitivos
```
dx = x2 - x1  // Calcular uma vez
dy = y2 - y1  // Calcular uma vez
```

---

## 15. Precisão Numérica

### Comparação de Ponto Flutuante
```
if (fabs(valor1 - valor2) < epsilon)
    valores_são_iguais = true
```

### Epsilon Recomendado
```
epsilon = 1e-6  // Para coordenadas normalizadas
```

---

## Resumo de Uso

1. **Q1**: Fórmulas 7, 10, 12
2. **Q2**: Fórmulas 3, 4
3. **Q3**: Fórmulas 3, 4
4. **Q4**: Fórmulas 2, 3, 8
5. **Q5**: Fórmulas 2, 6, 13
6. **Q6**: Fórmulas 3, 4, 5

Estas fórmulas formam a base matemática para todos os cálculos implementados nos programas da Lista 2.
