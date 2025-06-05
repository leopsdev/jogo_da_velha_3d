# Jogo da Velha 3D com OpenGL 🎮✨

## 📄 Descrição do Projeto
Este é um projeto de um Jogo da Velha (Tic-Tac-Toe) em 3D desenvolvido usando a biblioteca OpenGL (GLUT/freeGLUT). Os jogadores interagem com o tabuleiro arrastando e soltando peças (cubos para o Jogador 1 e esferas para o Jogador 2) em um ambiente tridimensional, com funcionalidades de câmera interativa (zoom e rotação) e iluminação.
O jogo oferece uma experiência visual imersiva e permite que dois jogadores se enfrentem no clássico jogo da velha, com detecção de vitória e empate, além de um sistema de reinício automático após o término da partida.

## 🌟 Recursos Principais
- Tabuleiro 3D Interativo: Um tabuleiro de 3x3 renderizado em 3D.
- Peças Personalizadas: Jogador 1 usa cubos (vermelhos) e Jogador 2 usa esferas (verdes).
- Seleção e Movimentação de Objetos: Os jogadores podem clicar e arrastar suas peças para as posições desejadas no tabuleiro.
- Câmera Dinâmica: Controle de câmera com zoom (botão direito do mouse) e rotação (botão do meio do mouse) para uma melhor visualização.
- Detecção de Vitórias e Empates: O jogo verifica automaticamente as condições de vitória e empate.
- Reinício Automático: Após o término de uma partida (vitória ou empate), o jogo reinicia após uma contagem regressiva.
- Iluminação: Um ambiente iluminado para dar profundidade e realismo aos objetos 3D.
- Decorações: O cenário inclui objetos decorativos como cones, esferas e tetraedros.

## 🛠️ Tecnologias Utilizadas
- C: Linguagem de programação principal.
- OpenGL: Biblioteca gráfica para renderização 3D.
- GLUT / freeGLUT: Toolkit para gerenciar janelas e interações com o sistema (mouse, teclado).
- Math.h: Para operações matemáticas como sqrt e sin/cos para a câmera.
- Unistd.h: Para a função sleep no reinício do jogo.
## 🚀 Como Executar o Projeto
Para compilar e executar este projeto, você precisará ter o compilador GCC e as bibliotecas OpenGL (GLUT/freeGLUT) instaladas em seu sistema.

Pré-requisitos
Compilador GCC
Bibliotecas OpenGL (GLUT/freeGLUT):
No Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install libglut-dev freeglut3-dev
```
No Fedora:
```bash

sudo dnf install freeglut-devel
```
No macOS (Homebrew):
Bash
```bash
brew install freeglut
```
No Windows: Você pode precisar instalar um ambiente de desenvolvimento como o MinGW ou configurar o Visual Studio com suporte a OpenGL.
Compilação e Execução
Clone o repositório (se aplicável):

```bash

git clone <URL_DO_SEU_REPOSITORIO>
cd <nome_do_seu_repositorio>
```
Compile os arquivos:
Considerando que você tem os arquivos main.c, jogo_da_velha.c, objeto.c e seus respectivos .h (e assumindo que você precisa linkar com GL, GLU, glut, m):

```bash
gcc main.c jogo_da_velha.c objeto.c -o jogo_da_velha_3d -lGL -lGLU -lglut -lm
```
-o jogo_da_velha_3d: Define o nome do executável.

-lGL: Liga com a biblioteca OpenGL.

-lGLU: Liga com a biblioteca OpenGL Utility.

-lglut: Liga com a biblioteca GLUT (ou freeGLUT).

-lm: Liga com a biblioteca matemática (necessário para sqrt, sin, cos).

Execute o jogo:

```bash
./jogo_da_velha_3d
```
## 🕹️ Como Jogar

- Início do Jogo: O Jogador 1 (cubos vermelhos) começa.
- Seleção da Peça: Clique com o botão esquerdo do mouse em uma das suas peças (cubos ou esferas, dependendo da sua vez) na área de "reserva" para selecioná-la. A peça selecionada ficará ciano.
- Movimentação: Com a peça selecionada, arraste o mouse para movê-la sobre o tabuleiro.
- Realizar Jogada: Solte o botão esquerdo do mouse sobre um dos espaços vazios do tabuleiro para fixar a peça.
- Importante: Certifique-se de que a peça está dentro dos limites do tabuleiro (x > 0.0 && z > 0.0 && x < 1.5 && z < 1.5) ao soltar.
- Passar a Vez: Aperte a tecla espaço para passar a vez para o próximo jogador.
- Reiniciar: Pressione a tecla R para reiniciar o jogo a qualquer momento.
- Sair: Pressione a tecla X para fechar o jogo.
Controles da Câmera
- Zoom: Mantenha o botão direito do mouse pressionado e arraste o mouse verticalmente.
- Rotação: Mantenha o botão do meio do mouse pressionado e arraste o mouse para girar a câmera ao redor do tabuleiro.
