/*
	Tarefa 2 - 19/04/2017
	Giancarlo França
	Feita com Adrianno Sampaio e Yago Tomé
 */

// Identificando os botões e o LED
const int buttonPin[2] = {2, 4};     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int buttonCount = 2;

// Marcadores de estado
int buttonState[2];         			// Se o i-ésimo botão está apertado atualmente
int lastButtonState[2];         		// Qual foi o último estado registrado antes do atual para esse botão
int delayTime = 1000;					// Intervalo atual entre cada piscada do LED
unsigned long currentTime;				// Momento atual (retorno da função millis)
unsigned long buttonPressedTime = -1; 	// Momento em que o último botão (que ainda não foi soltado) foi pressionado
unsigned long blinkState = 0;			// Estado atual da LED

void setup() {
  // Inicializa o LED como output e ambos os botões para input (opcionalmente configura a comunicação serial para debug)
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin[0], INPUT);
  pinMode(buttonPin[1], INPUT);
  //Serial.begin(115200);
}

bool pressed(int ind) {
  return buttonState[ind] == LOW && lastButtonState[ind] == HIGH;
}

bool released(int ind) {
  return buttonState[ind] == HIGH && lastButtonState[ind] == LOW;
}

void loop() {
  int i;
  //Leitura do estado dos botões
  for(i=0; i<buttonCount; ++i) {
    buttonState[i] = digitalRead(buttonPin[i]);
  }

  //Botão de aceleração da velocidade do piscar do LED
  currentTime = millis();
  if (pressed(0))  {
        delayTime = max(delayTime-100, 51);
        if (abs(currentTime - buttonPressedTime) <= 500) {
            //Serial.println("Opa parou");
            digitalWrite(LED_BUILTIN, HIGH); 
            while(1); //Trava no estado aceso
        }
        buttonPressedTime = currentTime;
  } else if (released(0)) {
        buttonPressedTime = 0; //Para impedir que um mesmo botão possa ser pressionado duas vezes para parar o LED
  }

  //Botão de desaceleração da velocidade do piscar do LED
  if (pressed(1))  {
        delayTime = min(delayTime+100, 2000);
        if (abs(currentTime - buttonPressedTime) <= 500) {
            //Serial.println("Opa parou 2");
            digitalWrite(LED_BUILTIN, HIGH);
            while(1);
        }
        buttonPressedTime = currentTime;
  } else if (released(1)) {
        buttonPressedTime = 0;
  }
  
    
  //LED piscando
  blinkState = (currentTime / delayTime) % 2;
  digitalWrite(LED_BUILTIN, blinkState);

  //Armazena o 'estado anterior' dos botões, para as checagens nas funções pressed e released.
  for(i=0; i<buttonCount; ++i) {
    lastButtonState[i] = buttonState[i];
  }
}
