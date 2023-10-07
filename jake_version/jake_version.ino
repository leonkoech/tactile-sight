const int trigger = 17; // OUTPUT to sensor //18
const int echo = 16; // INPUT from sensor //5
const int vibration = 5; // OUTPUT to buzzer //21
const int BUZZ_TIME = 300;
const int k = 20;
const int MAX_DISTANCE = 150;
const int MIN_DISTANCE = 2;

#define SOUND_SPEED 0.034

long duration;
float distanceCm = 0;
unsigned long time_now = 0;
int period = 1000;

float calculate_frequency(float distance);
bool check_distance(float distance);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(vibration, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Get current time, for measurement purposes in loop
  time_now = millis();

  // Make buzzer do buzz for .2 seconds
  if (check_distance(distanceCm)) {
    digitalWrite(vibration, HIGH);
    delay(BUZZ_TIME);
    digitalWrite(vibration, LOW);
  }
  else{
    digitalWrite(vibration, LOW);
  }

  // Do distance check
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW); 

  duration = pulseIn(echo, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  period = calculate_frequency(distanceCm);

  Serial.print(distanceCm);
  Serial.print('\t');
  Serial.println(period);
  // For the set period that it should delay on, wait.
  // While waiting, check if distance has decreased
  float temp_period;
  while (millis() < time_now + period) {

    digitalWrite(trigger, LOW);
    delayMicroseconds(2);

    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW); 

    duration = pulseIn(echo, HIGH);
    distanceCm = duration * SOUND_SPEED/2;
    temp_period = calculate_frequency(distanceCm);

    // If current period is less than old period, replace it
    if (temp_period < period) {
      period = temp_period;
    }

    delay(100);

  } // End of while loop


}

float calculate_frequency(float distance) {
  if (check_distance(distance)) {
    return k * distance;
  }
  return 5000;
}

bool check_distance(float distance){
  return distance > MIN_DISTANCE && distance < MAX_DISTANCE;
}


