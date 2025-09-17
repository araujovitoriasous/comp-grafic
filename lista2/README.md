# Lista 2 - Computação Gráfica
## Documentação Completa com Cálculos Matemáticos

---

## 📁 Arquivos da Lista

### Códigos Fonte (C++)
- **`q1_lista2.cpp`** - Sistema Solar (Órbitas da Terra e Lua)
- **`q2_lista2.cpp`** - Análise de Matrizes na Pilha OpenGL
- **`q3_lista2.cpp`** - Versão Reescrita sem Push/Pop
- **`q4_lista2.cpp`** - Paralelogramo e Losango
- **`q5_lista2.cpp`** - Rotação e Recorte (Liang-Barsky)
- **`q6_lista2.cpp`** - Braço Robótico (Cinemática)

### Documentação
- **`documento_explicativo_lista2.md`** - Documento principal com todos os cálculos
- **`formulas_matematicas.md`** - Referência rápida de fórmulas
- **`README.md`** - Este arquivo (índice geral)

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
- macOS com Xcode Command Line Tools
- Compilador g++

### Compilação
```bash
# Para cada questão individual:
g++ -o sistema_solar q1_lista2.cpp -framework GLUT -framework OpenGL
g++ -o analise_matrizes q2_lista2.cpp -framework GLUT -framework OpenGL
g++ -o versao_reescrita q3_lista2.cpp -framework GLUT -framework OpenGL
g++ -o paralelogramo_losango q4_lista2.cpp -framework GLUT -framework OpenGL
g++ -o rotacao_recorte q5_lista2.cpp -framework GLUT -framework OpenGL
g++ -o braco_robotico q6_lista2.cpp -framework GLUT -framework OpenGL

# Ou compilar todos de uma vez:
for file in q*.cpp; do
    name=$(basename "$file" .cpp)
    g++ -o "$name" "$file" -framework GLUT -framework OpenGL
done
```

### Execução
```bash
./sistema_solar
./analise_matrizes
./versao_reescrita
./paralelogramo_losango
./rotacao_recorte
./braco_robotico
```

---

## 📚 Resumo das Questões

### Q1 - Sistema Solar
- **Conceito**: Animação de órbitas planetárias
- **Matemática**: Trigonometria, coordenadas polares
- **OpenGL**: `glutTimerFunc`, `GL_TRIANGLE_FAN`
- **Resultado**: Terra e Lua orbitando o Sol

### Q2 - Análise de Matrizes
- **Conceito**: Evolução da pilha de matrizes OpenGL
- **Matemática**: Álgebra linear, composição de matrizes
- **OpenGL**: `glPushMatrix`, `glPopMatrix`, `glTranslatef`, `glRotatef`
- **Resultado**: Análise passo a passo das transformações

### Q3 - Versão Reescrita
- **Conceito**: Equivalência funcional sem push/pop
- **Matemática**: Equivalência de transformações
- **OpenGL**: `glLoadIdentity` como substituto
- **Resultado**: Mesmo comportamento visual

### Q4 - Paralelogramo e Losango
- **Conceito**: Transformações geométricas
- **Matemática**: Cisalhamento, rotação, escala
- **OpenGL**: `glMultMatrixf`, `glRotatef`, `glScalef`
- **Resultado**: Formas geométricas com ângulo de 30°

### Q5 - Rotação e Recorte
- **Conceito**: Algoritmo de recorte de linhas
- **Matemática**: Rotação em torno de ponto, Liang-Barsky
- **OpenGL**: Visualização de resultados
- **Resultado**: Segmentos visíveis após rotação e recorte

### Q6 - Braço Robótico
- **Conceito**: Cinemática de robôs
- **Matemática**: Transformações homogêneas, composição
- **OpenGL**: Visualização de sistemas de coordenadas
- **Resultado**: Cinemática completa de braço com 2 elos

---

## 🧮 Conceitos Matemáticos Aplicados

### Geometria Analítica
- Coordenadas cartesianas e polares
- Distâncias e ângulos
- Transformações geométricas

### Trigonometria
- Seno, cosseno, tangente
- Conversão graus ↔ radianos
- Identidades trigonométricas

### Álgebra Linear
- Matrizes de transformação
- Multiplicação de matrizes
- Transformações homogêneas

### Algoritmos Computacionais
- Liang-Barsky para recorte
- Animação temporal
- Interpolação linear

### Cinemática
- Transformações de coordenadas
- Composição de movimentos
- Sistemas de referência

---

## 🎯 Objetivos de Aprendizagem

### Conceituais
- Compreender transformações geométricas
- Entender cinemática de robôs
- Dominar algoritmos de recorte

### Práticos
- Implementar animações em OpenGL
- Manipular matrizes de transformação
- Aplicar algoritmos computacionais

### Técnicos
- Usar funções OpenGL avançadas
- Otimizar código gráfico
- Debuggar transformações

---

## 📖 Como Usar a Documentação

### Para Estudar
1. Leia `documento_explicativo_lista2.md` para entender os cálculos
2. Consulte `formulas_matematicas.md` para fórmulas específicas
3. Execute os programas para ver os resultados visuais

### Para Implementar
1. Use as fórmulas como referência
2. Adapte os códigos para suas necessidades
3. Teste com diferentes parâmetros

### Para Debugar
1. Verifique os cálculos matemáticos
2. Compare com os resultados esperados
3. Use printf para valores intermediários

---

## 🔧 Dicas de Desenvolvimento

### Compilação
- Use `-Wall` para warnings: `g++ -Wall -o programa arquivo.cpp`
- Use `-g` para debug: `g++ -g -o programa arquivo.cpp`

### Debugging
- Adicione `printf` para valores intermediários
- Use `glGetFloatv(GL_MODELVIEW_MATRIX, matrix)` para inspecionar matrizes
- Verifique se as coordenadas estão no range correto

### Otimização
- Cache valores trigonométricos calculados
- Evite cálculos repetitivos em loops
- Use `const` para valores que não mudam

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

### Extensões Possíveis
- Adicionar mais planetas ao sistema solar
- Implementar outros algoritmos de recorte
- Criar braços robóticos com mais elos
- Adicionar interação do usuário

---

## 📞 Suporte

Para dúvidas sobre:
- **Matemática**: Consulte `formulas_matematicas.md`
- **Implementação**: Veja os códigos comentados
- **Conceitos**: Leia `documento_explicativo_lista2.md`

---

**Desenvolvido para fins educacionais em Computação Gráfica**
