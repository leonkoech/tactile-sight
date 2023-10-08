
const int trigger = 18;
const int echo = 5;
const int vibration = 21;

// sound speed in cm/ micro second
#define SOUND_SPEED 0.034

long duration;
float distanceCm;

int motorState = LOW;

// function definition (prototype)
boolean check_distance(float distance);

// time (milliseconds) since last update
unsigned long previousMillis = 0;

const long scanInterval = 500; // (delay in milliseconds)
long vibrateInterval = 1000;
long vibrateMult = 1;

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
  
  delay(scanInterval);
}

boolean check_distance(float distance){
  return distance>3 && distance<20;
}
