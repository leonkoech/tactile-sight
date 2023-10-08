
#include <stdint.h>


const int trigger = 18;
const int echo = 5;
const int vibration = 21;

// sound speed in cm/ micro second
#define SOUND_SPEED 0.034
#define SREG (*((volatile uint8_t *)0x5F))



long duration;
float distanceCm;

// function definition (prototype)
boolean check_distance(float distance);

void genericDelay(unsigned int time_ms);

 void delay_1ms();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(vibration, OUTPUT);

}

void loop() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);

  distanceCm = duration * SOUND_SPEED/2;

  if(check_distance(distanceCm)){
    digitalWrite(vibration, HIGH);
  }
  else{
    digitalWrite(vibration, LOW);
  }

  Serial.print("distance cm: ");
  Serial.println(distanceCm);

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
}
