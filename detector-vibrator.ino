
const int trigger = 18;
const int echo = 5;
const int vibration = 21;

// sound speed in cm/ micro second
#define SOUND_SPEED 0.034


long duration;
float distanceCm;

// function definition (prototype)
boolean check_distance(float distance);

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

  delay(1000);
}

boolean check_distance(float distance){
  return distance>3 && distance<200;
}
