#define FILTER_COUNTS 4
const int TEMP_PIN = 1;
const int LED_PIN = 13;
int cache [FILTER_COUNTS];
const unsigned long delta = 250;
unsigned long nextTime = 0;
short addr = 0;
unsigned long cricketDelta = 0;
unsigned long nextChirp = 0;
boolean isOn = false;
unsigned long nextOff = 0;
#define BLINK_DURATION 200

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(LED_PIN, OUTPUT);
//  for (int i = 0; i < FILTER_COUNTS; i++) {
//    address_average(analogRead(TEMP_PIN));
//  }
}

void loop() {

  int value = analogRead(TEMP_PIN);

  Serial.println(value);

  if(value > 70){
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }
  
  delay(100);
  
  // put your main code here, to run repeatedly:
//  unsigned long time = millis();
//  if (time > nextTime) {
//    
////    Serial.println(analogRead(TEMP_PIN));
//    nextTime += delta;
//
//    address_average(analogRead(TEMP_PIN));
//    Serial.print(" ");
//    Serial.println(getAvg());
//  }
//  if (time > nextChirp) {
//    cricketDelta = 60000/(7*getAvg()-30);
//    nextChirp+= cricketDelta;
//    if (cricketDelta < 200) {
//      Serial.println(cricketDelta);
//    } else {
//      isOn = true;
//      digitalWrite(LED_PIN, HIGH);
//      nextOff = time + BLINK_DURATION;
//    }
//  }
//  if (isOn) {
//    if (time > nextOff) {
//      isOn = false;
//      digitalWrite(LED_PIN, LOW);
//    }
//  }
}

void address_average(short value){

  if(addr > FILTER_COUNTS-1){
    addr = 0;  
  }
  
  cache[addr] = value;
  addr++;
  
}

float getAvg(){
  float sum = 0;
  for (int i = 0; i < FILTER_COUNTS; ++i) {
    sum += (float)cache[i];
  }
  float temp = (1.1*((sum/FILTER_COUNTS)/1024))*100-50;
  return temp;
}
