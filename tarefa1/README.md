# Tarefa 1 - Computação Gráfica

Dois programas OpenGL/GLUT desenvolvidos e testados no **macOS**, com adaptações para rodar também no **Linux** e **Windows**.

## Compatibilidade

| Sistema | Suporte |
|---------|---------|
| macOS | Desenvolvido e testado aqui |
| Linux | Adaptado (requer FreeGLUT) |
| Windows | Adaptado (requer FreeGLUT via MinGW) |

O Makefile detecta o sistema operacional automaticamente e aplica os flags e includes corretos para cada plataforma.

## Requisitos por plataforma

**macOS**
- Xcode Command Line Tools (`xcode-select --install`)
- OpenGL e GLUT já incluídos no sistema

**Linux**
```bash
sudo apt install freeglut3-dev
```

**Windows (MinGW)**
- MinGW com g++
- FreeGLUT instalado e configurado no PATH

## Compilação

Para compilar ambas as questões:

```bash
make
```

Para compilar individualmente:

```bash
make questao1
make questao2
```

Para limpar os binários:

```bash
make clean
```

## Questão 1 — Casa com fundo alternável

Desenha uma casa simples (corpo roxo, telhado vermelho, porta e janela) sobre fundo branco.

### Rodar

```bash
./questao1
```

### Controles

| Tecla | Ação |
|-------|------|
| `Espaço` | Escurece o fundo (preto) |
| Qualquer outra tecla (com fundo preto) | Volta o fundo para branco |

---

## Questão 2 — Desenho com mouse

Tela branca onde o usuário desenha pontos pretos clicando com o mouse.

### Rodar

```bash
./questao2
```

### Controles

| Ação | Resultado |
|------|-----------|
| Clique esquerdo | Desenha um ponto preto (tamanho 50) na posição clicada |
| Clique direito | Limpa a tela |
