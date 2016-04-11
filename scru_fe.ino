/*
  Este Sketch esta desarrollado partiendo de los ejemplos del libro de EduBasica.
  Más Info:
  http://www.practicasconarduino.com/manualrapido/sensor_de_ultrasonidos.html
  http://www.practicasconarduino.com/manualrapido/programa7.html
*/


// SERVO
#include <Servo.h> 
 
Servo myservo;        // crea un objeto tipo servo para controlar el servo 
int pos = 0;          // variable para almacenar la posición del servo

// HC-SR04
int trigPin = 7;
int echoPin = 6;
long duration; // tiempo de ida/vuelta
int cm = 0; // Para almacenar el valor obtenido en cm valor=0
int DISTANCIA = 30; // cm

// MOTORES
int MAX = 255;
// MOTOR Derecho
int IN3 = 5;    // Input3 conectada al pin 5
int IN4 = 4;    // Input4 conectada al pin 4 
int ENB = 3;    // ENB conectada al pin 3 de Arduino

// MOTOR Izquierdo
int IN2 = 11;    // Input3 conectada al pin 5
int IN1 = 10;    // Input4 conectada al pin 4 
int ENA = 9;    // ENB conectada al pin 3 de Arduino

void setup() {

// Motores
  pinMode (ENB, OUTPUT); 
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT); 
  pinMode (IN2, OUTPUT);
  pinMode (IN1, OUTPUT);
// HC-SR04
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(8);
  pos = 120;
  myservo.write(pos);
}

void loop()

{
// Servo
pos = 60;
myservo.write(pos);
delay(120); // wait 120milliseconds for servo to reach position

//ponemos al trigger a low para activarlo después 

   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);

//Activar el módulo con un pulso de 10microsec.

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

//Esperamos la llegada de un pulso HIGH

duration = pulseIn(echoPin, HIGH);

 //tiempo de ida y vuelta, dividimos por 2

duration = duration / 2;

//La velocidad del sonido es de 340 m/s
//es decir, 29 microsegundos por centímetro

cm = duration/ 29;

delay(100);

if (cm < DISTANCIA) {
  // ATRAS
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite(ENB, MAX); // Velocidad

  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  analogWrite(ENA,MAX); // Velocidad
  
  delay(100);
  
  // -- GIRO --
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite(ENB,MAX); // Velocidad
  analogWrite(ENA,0); // Velocidad

  delay(100);

  analogWrite(ENB,0); // Velocidad
  analogWrite(ENA,0); // Velocidad

} else {
  // -- ADELANTE--
  // -- MOTOR DERECHO --
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  analogWrite(ENB,MAX); // Velocidad
  // -- MOTOR IZQUIERDO --
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  analogWrite(ENA,MAX); // Velocidad  
}

// Servo
pos = 180;
myservo.write(pos);
delay(240); // Esperamos que servo termine

}