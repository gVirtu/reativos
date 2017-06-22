# Projeto Final de Sistemas Reativos #

### Integrantes
 - Adrianno Sampaio
 - Giancarlo França

### Descrição do Projeto

O projeto consiste na criação de um pequeno jogo *top down* de ação que consistirá em um cenário com obstáculos estáticos (alinhados a uma grade) e um jogador que poderá se movimentar horizontalmente e verticalmente no plano de forma livre usando as teclas do teclado. 

Espalhados pelo cenário estarão vários inimigos que tentarão alcançar o jogador, andando lentamente. Para isso, usaremos um algoritmo de pathfinding a ser decidido (provavelmente derivado de A*) que iremos adaptar para não comprometer a reatividade do jogo.

O jogador também será capaz de eliminar os inimigos atirando projéteis que irão na direção do cursor do mouse, ao clicar na tela.

#### Extra, caso o tempo permita:

 - Obstáculos gerados aleatoriamente
 - Integração com Arduino
 - Mais variedade de gameplay
 - Sprites e Animações
  
### Divisão de Tarefas
 - Adrianno Sampaio
   * Controle do jogador
   * Sistema de colisões jogador v. bloco
   * Controle de câmera

- Giancarlo França
   * Adaptação do algoritmo de pathfinding
   * Sistema de colisões inimigo v. bloco
   * Criação do cenário