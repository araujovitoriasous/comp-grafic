# Relatório do Trabalho de Computação Gráfica

**Nome:** Vitoria Araujo Lima de Sousa

**Matrícula:** 20231001026

## Instruções de Compilação e Execução

### Pré-requisitos
- Sistema Operacional: macOS
- Compilador: `g++` (clang)
- Bibliotecas: OpenGL e GLUT
- `stb_image.h`: Incluído no diretório do projeto.

### Compilação
Para compilar o projeto, abra o terminal no diretório do projeto e execute o comando `make`:

```bash
make
```

Isso irá gerar um executável chamado `renderer`.

### Execução
Para executar o programa, passe o caminho do arquivo `.obj` como argumento:

```bash
./renderer cubo.obj
```

Outros modelos disponíveis:
```bash
./renderer bunny.obj
./renderer teapot.obj
```

## Modelos Utilizados

O programa foi testado com sucesso com os seguintes modelos, que foram adaptados para incluir coordenadas de textura e materiais:

1.  **Cubo (cubo.obj)**: Modelo básico.
2.  **Bule de Chá (teapot.obj)**: Modelo clássico de Utah.
3.  **Coelho de Stanford (bunny.obj)**: Modelo de alta densidade.
4.  **Caixa de Cornell (cornell_box.obj)**: Cena clássica de teste de iluminação.

Todos os modelos utilizam o arquivo de material `box.mtl` e a textura `test_texture.png` (um gradiente de cores).

## Recursos Implementados

- **Carregamento de OBJ**: Suporte a vértices (`v`), coordenadas de textura (`vt`), normais (`vn`) e faces (`f`).
- **Materiais (MTL)**: Leitura de arquivos `.mtl` e aplicação de texturas difusas (`map_Kd`).
- **Renderização**: Utilização de OpenGL (Pipeline Fixo).
- **Interação**: Rotação do objeto com o mouse (Arcball).
- **Câmera Automática**: Centralização e zoom automático baseado no tamanho do modelo.

## Bibliotecas Externas

- **stb_image.h**: Biblioteca single-header de domínio público utilizada para carregar arquivos de imagem.

## Observações

- Os modelos foram processados para garantir que possuam coordenadas de textura (mapeamento planar) para demonstração da funcionalidade de texturização.
