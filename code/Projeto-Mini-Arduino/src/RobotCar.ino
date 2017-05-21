/**
  Projeto Mini Arduino
  Trio: Adrianno Sampaio, Yago Tomé e Giancarlo França
**/

#include "lib/AFMotor.cpp"
#include "lib/Ultrasonic.cpp"
#include "lib/pitches.h"
#include <Servo.h> 
#define BUZZER 19

#define MOTOR_SPD 250
#define MOTOR_LOFFSET -49
#define MOTOR_ROFFSET 0
#define MOTOR_LFORWARD BACKWARD
#define MOTOR_LBACKWARD FORWARD
#define MOTOR_RFORWARD FORWARD
#define MOTOR_RBACKWARD BACKWARD
#define DISTANCIA_MIN 20
#define DISTANCIA_ITERATIONS 5
#define SERVO_DELAY 1000
#define TURN_DELAY 400

#define E_EMFRENTE 0
#define E_OLHAESQ 1
#define E_OLHADIR 2
#define E_VIRA 3
#define E_OLHAFRENTE 4
#define E_FERROU 5
#define mudaEstado(A) estado = A; timestampEstado = millis(); Serial.print("Estou no estado "); Serial.println(#A)

AF_DCMotor motorR(2);
AF_DCMotor motorL(1);
Servo servo;
int estado = E_EMFRENTE;
unsigned long timestampEstado;
float obstaculoEsq, obstaculoDir;
float obstaculoFrente;

Ultrasonic ultrasonic(15, 14);

void setup() {
  Serial.begin(9600);
  pinMode(19, OUTPUT);
  // turn on servo
  servo.attach(9);

  motorR.run(RELEASE);
  motorL.run(RELEASE);
  delay(1000);
  alteraVelocidade(MOTOR_SPD);
  motorL.run(MOTOR_LFORWARD);
  motorR.run(MOTOR_RFORWARD);

  servo.write(90);
}

int melody[] = {
  NOTE_A5, NOTE_A5, NOTE_F5, NOTE_D5,
  NOTE_D5, NOTE_G5, NOTE_G5, NOTE_G5,
  NOTE_B5, NOTE_B5, NOTE_C6, NOTE_D6,
  NOTE_C6, NOTE_C6, NOTE_C6, NOTE_A5,
  NOTE_F5, NOTE_A5, NOTE_A5, NOTE_A5,
  NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  8, 8, 8, 4, 
  4, 4, 4, 8,
  8, 8, 8, 8,
  8, 8, 8, 4,
  4, 4, 4, 8,
  8, 8, 8, 8
};

const int melodyLength = 24;

void playSong(int* songPitches, int* songNoteDuration, int songLength) {
  //FONTE: https://www.arduino.cc/en/Tutorial/toneMelody
  // iterate over the notes of the melody:
  for (int i = 0; i < songLength; ++i) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / songNoteDuration[i];
    tone(BUZZER, songPitches[i], noteDuration);
    Serial.print("Tocando uma nota ");
    Serial.println(songPitches[i]);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = (noteDuration * 1.30);
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER);
  }
}

float distanciaObstaculo() { //em CM
  float tot = 0;
  for(int i=0; i<DISTANCIA_ITERATIONS; ++i) {
    tot += ultrasonic.Ranging(CM);
  }
  return tot / (float) DISTANCIA_ITERATIONS;
}

void alteraVelocidade(int velocidade) {
  motorR.setSpeed(velocidade + MOTOR_ROFFSET);
  motorL.setSpeed(velocidade + MOTOR_LOFFSET);
}

void viraEsquerda() {
  motorL.run(MOTOR_LBACKWARD);
  motorR.run(MOTOR_RFORWARD);
}

void viraDireita() {
  motorR.run(MOTOR_RBACKWARD);
  motorL.run(MOTOR_LFORWARD);
}

void loop() {
  switch(estado) {
    case E_EMFRENTE:
       obstaculoFrente = distanciaObstaculo();
       Serial.print("Em frente, obstaculo em ");
       Serial.print(obstaculoFrente);
       Serial.println(" cm");
       if (obstaculoFrente < DISTANCIA_MIN) {
          motorL.run(RELEASE);
          motorR.run(RELEASE);
          servo.write(180);
          mudaEstado(E_OLHAESQ);
       }
    break;

    case E_OLHAESQ:
       if (millis() - timestampEstado > SERVO_DELAY) {
          obstaculoEsq = distanciaObstaculo();
          Serial.print("A esquerda, obstaculo em ");
          Serial.print(obstaculoEsq);
          Serial.println(" cm");
          servo.write(0);
          mudaEstado(E_OLHADIR);
       }
    break;

    case E_OLHADIR:
       if (millis() - timestampEstado > SERVO_DELAY) {
          obstaculoDir = distanciaObstaculo();
          Serial.print("A direita, obstaculo em ");
          Serial.print(obstaculoDir);
          Serial.println(" cm");
          float obstaculoMax = max(obstaculoEsq, obstaculoDir);
          if (obstaculoMax < DISTANCIA_MIN) {
            mudaEstado(E_FERROU);
          } else {
            alteraVelocidade(MOTOR_SPD);
            if (obstaculoEsq < obstaculoDir) {
              Serial.println("Partiu virar direita");
              viraDireita();
            } else {
              Serial.println("Partiu virar esquerda");
              viraEsquerda();
            }
            mudaEstado(E_VIRA);
          }
       }
    break;

    case E_VIRA:
      if (millis() - timestampEstado > TURN_DELAY) {
        servo.write(90);
        motorL.run(RELEASE);
        motorR.run(RELEASE);
        estado = mudaEstado(E_OLHAFRENTE);
      }
    break;

    case E_OLHAFRENTE:
      if (millis() - timestampEstado > SERVO_DELAY) {
        motorL.run(MOTOR_LFORWARD);
        motorR.run(MOTOR_RFORWARD);
        //alteraVelocidade(MOTOR_SPD);
        estado = mudaEstado(E_EMFRENTE);
      }
    break;

    case E_FERROU:
      Serial.println("vish");
      while(1) {
        playSong(melody, noteDurations, melodyLength);
      } //morreu
    break;
  }
  delay(16);
}
