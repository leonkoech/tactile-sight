
#include <stdint.h>


const int trigger = 18;
const int echo = 5;
const int vibration = 21;

// sound speed in cm/ micro second
#define SOUND_SPEED 0.034
#define SREG (*((volatile uint8_t *)0x5F))


long duration;
float distanceCm;

int motorState = LOW;

// function definition (prototype)
boolean check_distance(float distance);

<<<<<<< HEAD:detector-vibrator.ino
void genericDelay(unsigned int time_ms);

 void delay_1ms();
=======
// time (milliseconds) since last update
unsigned long previousMillis = 0;

const long scanInterval = 500; // (delay in milliseconds)
long vibrateInterval = 1000;
long vibrateMult = 1;
>>>>>>> 850f845ba78770838a410438bc1e2b29a659ce57:detector-vibrator/detector-vibrator.ino

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(vibration, OUTPUT);

}

void loop() {
  // unsigned long currentMillis = millis();
  
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);

  distanceCm = duration * SOUND_SPEED/2;
  float currentDistance = distanceCm;

  if(check_distance(distanceCm)){
    // motorState = HIGH;
    delay(distanceCm *5);
    digitalWrite(vibration, HIGH);
    Serial.println(distanceCm);
  }
  else{
    // motorState = LOW;
    digitalWrite(vibration, LOW);
  }
  
  Serial.print("distance cm: ");
  Serial.println(distanceCm);
<<<<<<< HEAD:detector-vibrator.ino

}

 void delay_1ms(){

  uint8_t oldSREG = SREG;
  cli();
  TCNT2 = 0x06;
  TCCR2A = 0x00;
  TCCR2B = 0x04;
  while((TIFR2 & 0x01) == 0); 
  TCCR2B = 0x00;
  TIFR2 = 0x1;
  SREG = oldSREG;
}

void genericDelay(unsigned int time_ms){
  for(unsigned long counter=0; counter < time_ms; counter++){
    delay_1ms();
  }
}

boolean check_distance(float distance){
  return distance>3 && distance<30;
=======
  
  delay(scanInterval);
}

boolean check_distance(float distance){
  return distance>3 && distance<20;
>>>>>>> 850f845ba78770838a410438bc1e2b29a659ce57:detector-vibrator/detector-vibrator.ino
}
