#define FILTER_COUNTS 3
const int PROBE_ONE = 1;
const int PROBE_TWO = 2;

const int SPEAKER_PIN = 7;
const int LED_PIN = 9;
const int LED_PIN_TWO = 13;

int cache_ONE [FILTER_COUNTS];
int cache_TWO [FILTER_COUNTS];

unsigned int THERM_ONE_THRESHOLD = 370;

unsigned int THERM_TWO_THRESHOLD = 400;

short addr_ONE = 0;
short addr_TWO = 0;



unsigned long cricketDelta = 200;
unsigned long nextChirp = 0;
boolean isOn = false;
unsigned long nextOff = 0;

unsigned long cricketDelta_TWO = 200;
unsigned long nextChirp_TWO = 0;
boolean isOn_TWO = false;
unsigned long nextOff_TWO = 0;

//Delta Timing + General UI

const unsigned long delta = 100;
unsigned long nextTime = 0;

#define BLINK_DURATION 200

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_TWO, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  for (int i = 0; i < FILTER_COUNTS; i++) {
    address_average_ONE(analogRead(PROBE_ONE));
    address_average_TWO(analogRead(PROBE_TWO));
  }
}

void loop() {

//  int value = analogRead(TEMP_PIN);
//
//  //Serial.println(value);
//
//  if(value > 70){
//    digitalWrite(13, HIGH);
//  }
//  else{
//    digitalWrite(13, LOW);
//  }
  
  //delay(100);
  
  // put your main code here, to run repeatedly:
  unsigned long time = millis();
  if (time > nextTime) {
    
//    Serial.println(analogRead(TEMP_PIN));
    nextTime += delta;

    address_average_ONE(analogRead(PROBE_ONE));
    address_average_TWO(analogRead(PROBE_TWO));

    float avgone = getAvg_ONE();
    float avgtwo = getAvg_TWO();

    
    
    //Cheap code to fire a speaker
    if(avgone > THERM_ONE_THRESHOLD || avgtwo > THERM_TWO_THRESHOLD){
      digitalWrite(SPEAKER_PIN, HIGH);
    }
    else{
      digitalWrite(SPEAKER_PIN, LOW);
    }

    
    Serial.print("ONE ");
    Serial.print(avgone);
    Serial.print("  TWO ");
    Serial.println(avgtwo);
  }
  
  if (time > nextChirp) {
    cricketDelta = 600000/(4*getAvg_ONE()-30);
    nextChirp+= cricketDelta;
//    Serial.print("nextchirp: ");
//    Serial.println(nextChirp);
    if (cricketDelta < 200) {
//      Serial.print("nextchirp: ");
//      Serial.println(nextChirp);
    } else {
      isOn = true;
      digitalWrite(LED_PIN, HIGH);
      nextOff = time + BLINK_DURATION;
    }
  }

    if (time > nextChirp_TWO) {
    cricketDelta_TWO = 600000/(4*getAvg_TWO()-30);
    nextChirp_TWO += cricketDelta_TWO;
    //Serial.print("nextchirp_TWO: ");
    //Serial.println(nextChirp_TWO);
    if (cricketDelta_TWO < 200) {
//      Serial.print("nextchirp: ");
//      Serial.println(nextChirp);
    } else {
      //Serial.println("BLINK ON TWO");
      isOn_TWO = true;
      digitalWrite(LED_PIN_TWO, HIGH);
      nextOff_TWO = time + BLINK_DURATION;
    }
  }
  
  if (isOn_TWO) {
    if (time > nextOff_TWO) {
      isOn_TWO = false;
      //Serial.println("BLINK OFF TWO");
      digitalWrite(LED_PIN_TWO, LOW);
    }
  }

   if (isOn) {
    if (time > nextOff) {
      isOn = false;
      //Serial.println("BLINK OFF ONE");
      digitalWrite(LED_PIN, LOW);
    }
  }
  
}

void address_average_ONE(short value){

  if(addr_ONE > FILTER_COUNTS-1){
    addr_ONE = 0;  
  }
  
  cache_ONE[addr_ONE] = value;
  addr_ONE++;
  
}

void address_average_TWO(short value){

  if(addr_TWO > FILTER_COUNTS-1){
    addr_TWO = 0;  
  }
  
  cache_TWO[addr_TWO] = value;
  addr_TWO++;
  
}

float getAvg_ONE(){
  float sum = 0;
  for (int i = 0; i < FILTER_COUNTS; ++i) {
    sum += (float)cache_ONE[i];
  }
  //float temp = (1.1*((sum/FILTER_COUNTS)/1024))*100-50;
  float temp = (sum/FILTER_COUNTS);
  return temp;
}

float getAvg_TWO(){
  float sum = 0;
  for (int i = 0; i < FILTER_COUNTS; ++i) {
    sum += (float)cache_TWO[i];
  }
  //float temp = (1.1*((sum/FILTER_COUNTS)/1024))*100-50;
  float temp = (sum/FILTER_COUNTS);
  return temp;
}
