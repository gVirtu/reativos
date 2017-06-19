/*
 * Sistemas Reativos - UERJ
 * Tarefa 03
 * 
 * Grupo:
 *  Adrianno Sampaio
 *  Giancarlo França
 *  Yago Tomé
 */

#include "xtea.c.h"

#define LED 13
//#define DEBUG

#define ENCR 1
#define DECR 0

#define B_PIN 2

uint32_t key[] = { 1, 2, 3, 4 };
uint32_t v[2];
const uint32_t vsize = 100; //Tamanho simulado do vetor

unsigned long int t0, tf, tm; //Medidas de tempo

int counter = 0; //Contador de pares (des)criptografados
unsigned long int testCounter = 0; //Para cálculo da média
int state = ENCR; 

int buttonState = LOW;
int lastButtonState = LOW;
int led = LOW;

// Verifica se um botão foi pressionado no momento atual
bool pressed() { 
  return buttonState == LOW && lastButtonState == HIGH;
}

void setup () {
    pinMode(LED, OUTPUT);
    pinMode(B_PIN, INPUT);
    Serial.begin(9600);
    v[0] = 10;
    v[1] = 20;
    t0 = millis();
    digitalWrite(LED, led=!led);
}

void loop () {
    buttonState = digitalRead(B_PIN);

    #ifdef DEBUG
    Serial.print("------------------- State = ");
    Serial.println(state);
    Serial.print("------------------- Counter ");
    Serial.println(counter);
    
    Serial.println("antes: ");
      Serial.print(v[0]);
      Serial.print(" ");
      Serial.println(v[1]);
    #endif

    if(state == ENCR){
      #ifdef DEBUG
      Serial.println("durante: ");
      #endif
      
      encipher(32, v, key);
      
      #ifdef DEBUG
      Serial.print(v[0]);
      Serial.print(" ");
      Serial.println(v[1]);
      #endif
    }
    else {
      #ifdef DEBUG
      Serial.println("depois: ");
      #endif
      
      decipher(32, v, key);
      
      #ifdef DEBUG
      Serial.print(v[0]);
      Serial.print(" ");
      Serial.println(v[1]);
      #endif
   }
  
  if(++counter == vsize )
  {
    //LED ligado para criptografia, desligado para descriptografia
    digitalWrite(LED, led=!led);
    if(state == DECR)
    {
      //Fim do experimento
      tf = millis();
      tm += tf-t0;
      ++testCounter;
      //  Serial.println(tf-t0);         // Tempo a cada par
      t0 = millis();
    }    
    
    #ifdef DEBUG
    Serial.print("------------------- Counter ");
    Serial.println(counter);
    
    Serial.print("------------------ IF --------------------- ");
    Serial.print("------------------- State = ");
    Serial.println(state);

    Serial.print("------------------- vsize ");
    Serial.println(vsize);
    #endif
    state = !state;
    counter = 0;
  }

  //Reação ao pressionamento do botão
  if(pressed())
  {
    digitalWrite(LED, HIGH);
    Serial.println("-------------------");
    Serial.print("Tamanho: ");
    Serial.println(vsize);
    Serial.print("Testes realizados: ");
    Serial.println(testCounter);
    if (testCounter) {
      Serial.print("Tempo médio de execução: ");
      Serial.println(((double) tm )/testCounter);
    } else {
      Serial.println("Nenhum resultado.");
    }
    while(1);
  }

    lastButtonState = buttonState;
}
