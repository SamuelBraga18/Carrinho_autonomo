#include <HCSR04.h>

//pinos dos sensores
#define pinoTrig1 7
#define pinoEcho1 8
#define pinoTrig2 3
#define pinoEcho2 4

//leds
#define led1 11
#define led2 12

//pinos do driver
#define IN1 6
#define IN2 5
#define IN3 9
#define IN4 10

//objetos dos sensores
HCSR04 sensor1(pinoTrig1, pinoEcho1);
HCSR04 sensor2(pinoTrig2, pinoEcho2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  //estado inicial
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  float distancia1 = ler_distancia(pinoTrig1, pinoEcho1);
  delay(10);
  float distancia2 = ler_distancia(pinoTrig2, pinoEcho2);
  delay(10);


  if(distancia1 >= 20 and distancia2 >= 20){ 
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }else if(distancia1 < 20){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(700);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }else if(distancia2 < 20){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(700);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }else if(distancia1 < 20 and distancia2 < 20){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(700);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(400);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

  pisca_alerta();
  
}

void pisca_alerta(){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  delay(200);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  delay(200);
}

float ler_distancia(int trigPin, int echoPin){
  float distancia;
  long duracao;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH, 30000);

  //converte a distancia para centimetros
  distancia = duracao * 0.0343/2;

  //caso não encontre nada, converte para -1
  if(duracao == 0) return -1;
  return distancia;
}
