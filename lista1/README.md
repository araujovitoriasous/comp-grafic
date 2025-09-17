# Lista 1 - Computação Gráfica
## Desenho de Sol Amarelo com OpenGL

---

## 📁 Arquivos da Lista

### Códigos Fonte (C++)
- **`sol_amarelo.cpp`** - Sol com redimensionamento proporcional
- **`sol_amarelo_fixo.cpp`** - Sol com tamanho fixo independente do redimensionamento

### Executáveis
- **`sol_amarelo`** - Executável da versão padrão
- **`sol_amarelo_fixo`** - Executável da versão com tamanho fixo

### Documentação
- **`documento_explicativo_lista1.md`** - Documento principal com todos os cálculos
- **`formulas_matematicas.md`** - Referência rápida de fórmulas
- **`README.md`** - Este arquivo (índice geral)

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
- macOS com Xcode Command Line Tools
- Compilador g++

### Compilação
```bash
# Versão padrão (redimensionamento proporcional)
g++ -o sol_amarelo sol_amarelo.cpp -framework GLUT -framework OpenGL

# Versão com tamanho fixo
g++ -o sol_amarelo_fixo sol_amarelo_fixo.cpp -framework GLUT -framework OpenGL

# Ou compilar ambas de uma vez
g++ -o sol_amarelo sol_amarelo.cpp -framework GLUT -framework OpenGL
g++ -o sol_amarelo_fixo sol_amarelo_fixo.cpp -framework GLUT -framework OpenGL
```

### Execução
```bash
# Versão padrão
./sol_amarelo

# Versão com tamanho fixo
./sol_amarelo_fixo
```

---

## 🎨 Descrição dos Programas

### Sol Amarelo (Versão Padrão)
- **Comportamento**: Redimensionamento proporcional
- **Características**: 
  - Sol sempre visível na janela
  - Mantém proporção quadrada
  - Cresce/diminui com o redimensionamento
- **Uso**: Ideal para visualização em diferentes tamanhos de tela

### Sol Amarelo Fixo (Versão com Tamanho Fixo)
- **Comportamento**: Tamanho fixo em pixels
- **Características**:
  - Sol sempre do mesmo tamanho
  - Posicionado no canto inferior esquerdo
  - Independente do redimensionamento
- **Uso**: Ideal para interfaces com elementos de tamanho constante

---

## 🧮 Conceitos Matemáticos Aplicados

### Geometria Circular
- **Coordenadas polares**: `x = r*cos(θ)`, `y = r*sin(θ)`
- **Distribuição angular**: 360° dividido uniformemente
- **Cálculo de perímetro**: `2πr`

### Trigonometria
- **Conversão graus ↔ radianos**: `radianos = graus * π/180`
- **Funções seno e cosseno**: Para posicionamento circular
- **Vetores perpendiculares**: Para largura dos raios

### Transformações 2D
- **Translação**: Posicionamento no canto inferior esquerdo
- **Escala**: Tamanho fixo independente do redimensionamento
- **Projeção ortogonal**: Sistema de coordenadas normalizado

### Sistemas de Coordenadas
- **Coordenadas normalizadas**: Range [-1, 1]
- **Ajuste de aspecto**: Manutenção de proporções
- **Viewport**: Área de desenho na janela

---

## 🔧 Parâmetros do Sol

### Dimensões
- **Raio do círculo central**: 0.3 unidades
- **Comprimento dos raios**: 0.4 unidades
- **Largura dos raios**: 0.08 unidades
- **Número de raios**: 15 raios

### Cálculos Automáticos
- **Ângulo entre raios**: 360° / 15 = 24°
- **Número de triângulos do círculo**: 360° / 5° = 72 triângulos
- **Raio total**: 0.3 + 0.4 = 0.7 unidades
- **Diâmetro total**: 1.4 unidades

### Cores
- **Sol**: Amarelo (R=1, G=1, B=0)
- **Fundo**: Azul escuro (R=0.1, G=0.1, B=0.3)

---

## 📊 Análise de Performance

### Complexidade Computacional
- **Círculo central**: O(n) onde n = 72 segmentos
- **Raios**: O(m) onde m = 15 raios
- **Total**: O(n + m) = O(87) operações por frame

### Otimizações Implementadas
1. **Cache de valores trigonométricos**: Cálculos feitos uma vez por raio
2. **Uso de GL_TRIANGLE_FAN**: Eficiente para círculos
3. **Uso de GL_TRIANGLES**: Eficiente para raios individuais
4. **Constantes em tempo de compilação**: Valores pré-calculados

### Recursos Utilizados
- **Triângulos**: 87 triângulos total
- **Vértices**: 118 vértices total
- **Primitivas OpenGL**: GL_TRIANGLE_FAN, GL_TRIANGLES

---

## 🎯 Objetivos de Aprendizagem

### Conceituais
- Compreender geometria circular e trigonometria
- Entender sistemas de coordenadas em OpenGL
- Dominar transformações 2D básicas

### Práticos
- Implementar desenhos geométricos complexos
- Manipular sistemas de coordenadas
- Otimizar código gráfico

### Técnicos
- Usar primitivas OpenGL eficientemente
- Implementar diferentes comportamentos de redimensionamento
- Aplicar conceitos de performance em gráficos

---

## 🔍 Diferenças entre as Versões

| Aspecto | Versão Padrão | Versão Fixa |
|---------|---------------|-------------|
| **Redimensionamento** | Proporcional | Tamanho fixo |
| **Posicionamento** | Centro da tela | Canto inferior esquerdo |
| **Comportamento** | Cresce/diminui | Sempre mesmo tamanho |
| **Uso** | Visualização geral | Interface com elementos fixos |
| **Código adicional** | Apenas reshape() | reshape() + transformações |

### Código Específico da Versão Fixa
```cpp
// Posicionamento no canto inferior esquerdo
glTranslatef(-1.0f + FIXED_SIZE/2, -1.0f + FIXED_SIZE/2, 0.0f);

// Escala fixa
glScalef(FIXED_SIZE, FIXED_SIZE, 1.0f);
```

---

## 📖 Como Usar a Documentação

### Para Estudar
1. Leia `documento_explicativo_lista1.md` para entender os cálculos
2. Consulte `formulas_matematicas.md` para fórmulas específicas
3. Execute os programas para ver os resultados visuais

### Para Implementar
1. Use as fórmulas como referência
2. Adapte os parâmetros para suas necessidades
3. Teste com diferentes valores de NUM_RAYS, SUN_RADIUS, etc.

### Para Debugar
1. Verifique os cálculos matemáticos
2. Compare com os resultados esperados
3. Use printf para valores intermediários

---

## 🔧 Dicas de Desenvolvimento

### Compilação
- Use `-Wall` para warnings: `g++ -Wall -o programa arquivo.cpp`
- Use `-g` para debug: `g++ -g -o programa arquivo.cpp`

### Modificações Possíveis
- **Alterar número de raios**: Mude `NUM_RAYS`
- **Modificar tamanhos**: Ajuste `SUN_RADIUS`, `RAY_LENGTH`, `RAY_WIDTH`
- **Mudar cores**: Modifique `glColor3f()` e `glClearColor()`
- **Adicionar animação**: Use `glutTimerFunc()` para rotação

### Debugging
- Adicione `printf` para valores de ângulos e coordenadas
- Verifique se as coordenadas estão no range [-1, 1]
- Teste com diferentes tamanhos de janela

---

## 🎨 Extensões Possíveis

### Melhorias Visuais
- **Gradiente de cores**: Do amarelo para laranja
- **Sombra**: Adicionar sombra projetada
- **Animação**: Rotação dos raios
- **Efeitos**: Brilho ou halo ao redor do sol

### Funcionalidades
- **Interação**: Clique para mudar cores
- **Controles**: Teclas para ajustar parâmetros
- **Salvamento**: Exportar imagem
- **Múltiplos sóis**: Desenhar vários sóis

### Otimizações
- **Display Lists**: Para reutilizar geometria
- **VBOs**: Vertex Buffer Objects para performance
- **Shaders**: Para efeitos visuais avançados

---

## 📝 Notas Importantes

### Compatibilidade
- Códigos testados em macOS com OpenGL/GLUT
- Para Linux: instale `freeglut3-dev`
- Para Windows: use Visual Studio com OpenGL

### Limitações
- Algumas funções OpenGL são deprecated no macOS
- Use `#define GL_SILENCE_DEPRECATION` para suprimir warnings
- Para produção, considere usar OpenGL moderno (3.3+)

### Boas Práticas
- Sempre limpe o buffer antes de desenhar
- Use `glFlush()` para forçar atualização
- Mantenha proporções adequadas para diferentes resoluções

---

## 📞 Suporte

Para dúvidas sobre:
- **Matemática**: Consulte `formulas_matematicas.md`
- **Implementação**: Veja os códigos comentados
- **Conceitos**: Leia `documento_explicativo_lista1.md`

---

**Desenvolvido para fins educacionais em Computação Gráfica**

### Resumo Executivo
A Lista 1 demonstra conceitos fundamentais de geometria computacional e OpenGL através do desenho de um sol amarelo. Os dois programas mostram diferentes abordagens para o mesmo problema visual, ensinando sobre sistemas de coordenadas, transformações 2D e otimização de código gráfico.
