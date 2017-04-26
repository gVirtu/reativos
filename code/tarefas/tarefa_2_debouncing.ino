/**
  Tarefa 2: Arduino com LED e 2 Botões
  Trio: Adrianno Sampaio, Yago Tomé e Giancarlo França
**/
const int buttonPin[2] = {2, 4};     // Saídas dos botões
const int ledPin =  13;      // saída do LED
const int buttonCount = 2; // Numero de botões
const unsigned long debouncingThres = 300;

int buttonState[2]; // Variáveis que guardam o estado dos botões: HIGH, LOW
int lastButtonState[2]; // Contém o último estado dos botões
unsigned long buttonPressedTime[2];
int delayTime = 1000; // Tempo no qual o LED fica aceso ou apagado
unsigned long currentTime;
unsigned long blinkState = 0;

void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin[0], INPUT);
  pinMode(buttonPin[1], INPUT);
  Serial.begin(115200); // inicializando a porta serial para Debug

  for(int i=0; i<buttonCount; ++i) {
    buttonPressedTime[i] = -1;
  }
}

// Verifica se um botão foi pressionado no momento atual
bool pressed(int ind) { 
  return buttonState[ind] == LOW && lastButtonState[ind] == HIGH && millis()-buttonPressedTime[ind] > debouncingThres;
}

//verifica se o botão foi solto no momento atual
bool released(int ind) {
  return buttonState[ind] == HIGH && lastButtonState[ind] == LOW && millis()-buttonPressedTime[ind] > debouncingThres;
}

void loop() {
  
  int i;
  for(i=0; i<buttonCount; ++i) {
    buttonState[i] = digitalRead(buttonPin[i]);
  }

  if (pressed(0))  { // Diminui o intervalo no qual o LED acende e apaga (aumenta a velocidade)
        delayTime = max(delayTime-100, 51);
        currentTime = millis();
        if (abs(currentTime - buttonPressedTime[1]) <= 500) { // se o segundo botão foi pressionado há menos de 500 ms do primeiro botão então acende o LED para sempre
            digitalWrite(LED_BUILTIN, HIGH);
            while(1);
        }
        //Serial.println("clic");
        buttonPressedTime[0] = currentTime;
  } /*else if (released(0)) { // zera o tempo entre o primeiro botão pressionado e o segundo
        buttonPressedTime = 0;
  }*/

  if (pressed(1))  { // Aumenta o intervalo de tempo no qual o LED está aceso (diminui a velocidade)
        delayTime = min(delayTime+100, 2000);
        currentTime = millis();
        if (abs(currentTime - buttonPressedTime[0]) <= 500) { // se o segundo botão foi pressionado há menos de 500 ms do primeiro botão então acende o LED para sempre
            digitalWrite(LED_BUILTIN, HIGH);
            while(1);
        }
        buttonPressedTime[1] = currentTime;
  } /*else if (released(1)) { // zera o tempo entre o primeiro botão pressionado e o segundo
        buttonPressedTime[1] = 0;
  }*/
  
    
  blinkState = (millis() / delayTime) % 2;
  digitalWrite(LED_BUILTIN, blinkState);   // desliga/liga o LED

  for(i=0; i<buttonCount; ++i) { // altera o estado anterior dos botões para o estado atual
    lastButtonState[i] = buttonState[i];
  }
}
