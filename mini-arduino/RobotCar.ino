/**
  Projeto Mini Arduino
  Trio: Adrianno Sampaio, Yago Tomé e Giancarlo França
**/

#include "lib/AFMotor.cpp"
#include "lib/Ultrasonic.cpp"
#include <Servo.h> 
#define MOTOR_SPD 250
#define MOTOR_LOFFSET 0
#define MOTOR_ROFFSET 0
#define DISTANCIA_MIN 20
#define SERVO_DELAY 900
#define TURN_DELAY 684

#define E_EMFRENTE 0
#define E_OLHAESQ 1
#define E_OLHADIR 2
#define E_VIRA 3
#define E_OLHAFRENTE 4
#define E_FERROU 5
#define mudaEstado(A) estado = A; timestampEstado = millis(); Serial.print("Estou no estado "); Serial.println(#A)

AF_DCMotor motorR(1);
AF_DCMotor motorL(2);
Servo servo;
int estado = E_EMFRENTE;
unsigned long timestampEstado;
float obstaculoEsq, obstaculoDir;
float obstaculoFrente;

Ultrasonic ultrasonic(15, 14);

void setup() {
  //Serial.begin(9600);
  
  // turn on servo
  servo.attach(9);

  // turn on motor #1
  motorR.setSpeed(MOTOR_SPD);
  motorR.run(RELEASE);
  // turn on motor #2
  motorL.setSpeed(MOTOR_SPD);
  motorL.run(RELEASE);
  delay(1000);
  motorL.run(BACKWARD);
  motorR.run(BACKWARD);

  servo.write(90);
}

float distanciaObstaculo() { //em CM
  long microsec = ultrasonic.timing();

  return ultrasonic.convert(microsec, Ultrasonic::CM);
}

void alteraVelocidade(int velocidade) {
  motorR.setSpeed(velocidade + MOTOR_ROFFSET);
  motorL.setSpeed(velocidade + MOTOR_LOFFSET);
}

void viraEsquerda() {
  motorL.run(BACKWARD);
  motorR.run(FORWARD);
}

void viraDireita() {
  motorR.run(BACKWARD);
  motorL.run(FORWARD);
}

int i;

void loop() {
  switch(estado) {
    case E_EMFRENTE:
       obstaculoFrente = distanciaObstaculo();
       Serial.print("Em frente, obstaculo em ");
       Serial.print(obstaculoFrente);
       Serial.println(" cm");
       if (obstaculoFrente < DISTANCIA_MIN) {
          alteraVelocidade(0);
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
        alteraVelocidade(0);
        motorL.run(BACKWARD);
        motorR.run(BACKWARD);
        estado = mudaEstado(E_OLHAFRENTE);
      }
    break;

    case E_OLHAFRENTE:
      if (millis() - timestampEstado > SERVO_DELAY) {
        alteraVelocidade(MOTOR_SPD);
        estado = mudaEstado(E_EMFRENTE);
      }
    break;

    case E_FERROU:
      Serial.println("vish");
      while(1); //morreu
    break;
  }

  
  /*
  
  motorR.run(FORWARD);
  motorL.run(FORWARD);
  for (i=0; i<255; i++) {
    servo.write(i);
    motorR.setSpeed(i);  
//    motorL.setSpeed(i); 
    delay(3);
 }
 
  for (i=255; i!=0; i--) {
    servo.write(i-255);
    motorR.setSpeed(i);  
//    motorL.setSpeed(i); 
    delay(3);
 }

 for (i=0; i<255; i++) {
    servo.write(i);
//    motorR.setSpeed(i);  
    motorL.setSpeed(i); 
    delay(3);
 }
 
  for (i=255; i!=0; i--) {
    servo.write(i-255);
//    motorR.setSpeed(i);  
    motorL.setSpeed(i); 
    delay(3);
 }
 
  motorR.run(BACKWARD);
  motorL.run(BACKWARD);
  for (i=0; i<255; i++) {
    servo.write(i);
    motorR.setSpeed(i);  
//    motorL.setSpeed(i); 
    delay(3);
 }
 
  for (i=255; i!=0; i--) {
    servo.write(i-255);
    motorR.setSpeed(i);  
//    motorL.setSpeed(i); 
    delay(3);
 }

 for (i=0; i<255; i++) {
    servo.write(i);
//    motorR.setSpeed(i);  
    motorL.setSpeed(i); 
    delay(3);
 }
 
  for (i=255; i!=0; i--) {
    servo.write(i-255);
//    motorR.setSpeed(i);  
    motorL.setSpeed(i); 
    delay(3);
 }*/
}
