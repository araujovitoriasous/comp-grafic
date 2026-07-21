# Tarefa 1 - Computação Gráfica

Dois programas OpenGL/GLUT desenvolvidos para macOS.

## Requisitos

- macOS com Xcode Command Line Tools instalado
- OpenGL e GLUT (já incluídos no macOS)

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
