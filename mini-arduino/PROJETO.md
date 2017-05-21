# Projeto Mini-Arduino #

### Integrantes
 - Adrianno Sampaio
 - Giancarlo França
 - Yago Tomé

### Descrição do Projeto

O projeto consiste na criação de um carro de duas rodas com direção automatizada com base em dados obtidos através de quatro sensores de distância: um frontal, no centro; dois para visão periférica, a ~45° para cada um dos lados; e um na parte traseira.

O carro seguirá em frente sempre que possível, utilizando os sensores de visão periférica para auxiliar no julgamento do melhor sentido para rotacionar caso seja detectado algum obstáculo.

Se ambos os sensores laterais sinalizarem uma colisão iminente ao mesmo tempo (em um intervalo de X ms), o carro se movimentará em ré até que seja possível rotacionar para um dos lados. Se o sensor de distância traseiro detectar um obstáculo próximo durante o movimento em ré, o carro irá parar e acionar uma buzina para sinalizar que está preso.

#### Extra, caso o tempo permita:

Além disso ele acelerará durante uma trajetória linear sem obstrução, e possuirá dois discos encoder que serão utilizados para estimar a velocidade através da rotação das rodas, que poderá será exibida em uma tela LCD, ou display de 7 segmentos ou em uma escala de leds.

### Componentes utilizados
 - 1 Arduino UNO
 - 1 shield de motor
 - 4 sensores de distância
 - 4 protoboards pequenas (ou 1 grande e 1 pequena caso não seja possível)
 - 1 kit carro
 - 1 Buzina
 - (*opcional*) 1 Tela LCD/display de 7 segmentos/4 Leds 

### Comportamento

#### Estado inicial

 1. Caso não haja nenhum obstáculo obstruindo o sensor frontal, ele anda para frente. 
 2. Se apenas o sensor frontal detectar um obstáculo, então o carro irá desviar para a direita. 
 3. Se o sensor frontal e apenas um dos sensores laterais detectarem obstrução o carro desviará para o lado oposto.
 4. Se os 3 sensores forem obstruídos simultaneamente o carro entrará no estado de ré

[sugestão]: # (Velocidade e a distância mínima aumentam proporcionalmente ao tempo sem obstrução)

[condição_removida]: # (Se o sensor esquerdo detectar um obstáculo, o carro desviará para a direita)
[condição_removida]: # (Se o sensor direito detectar um obstáculo, o carro desviará para a esquerda)

#### Estado de ré

 1. Enquanto o carro estiver no estado de ré ele irá tocar a buzina de forma intermitente
 2. Se os dois sensores de distância laterais detectarem obstrução o carro andará para trás
 3. Caso um dos sensores de distância lateral não detecte mais uma obstrução, o carro irá desviar para o lado desse sensor (aprox. 90 graus?) e retornar ao estado inicial
 4. Se o sensor de contato traseiro for acionado o carro entrará no estado encurralado


#### Estado encurralado

[condição_removida]: # (Nesse estado os sensores laterais estarão obrigatoriamente obstruídos)

 1. Enquanto o carro estiver nesse estado, ele irá tocar a buzina continuamente
  
[condição_removida]: # (Se o sensor frontal detectar uma obstrução à uma distância muito pequena ele irá parar de tocar a buzina e entrará no estado de transporte)

[estado_removida]: # (#### Estado de transporte)

[condição_removida]: # (Nesse estado o sensor frontal estará obrigatoriamente obstruído por um objeto à uma distância muito pequena (Ex.: obstruir o sensor com a mão)
[condição_removida]: # (Estado utilizado para permitir a retirada do carro do local sem saída e o reposicionamento do mesmo em uma superfície segura)
[condição_removida]: # (Se o sensor frontal for desobstruído:)
[condição_removida]: # (Se pelo menos um dos laterais também estiver desobstruído, então o carro retorna ao estado inicial)
[condição_removida]: # (Se nenhum dos laterais estiver desobstruído:)
[condição_removida]: # (Se o sensor frontal não detectar obstrução, então o carro retorna ao estado de ré)
[condição_removida]: # (Se o sensor de contado detectar colisão, então o carro retorna ao estado encurralado)

