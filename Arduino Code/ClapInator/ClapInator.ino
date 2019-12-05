const int ledpin = D3;  //  Led/ Relay pin
const int soundPin = D4;  //  Microphone Sensor Detection Module output digital pin

unsigned long startTime = 0;  //  Save the time of the first clap for each sicale
unsigned long secondClapDelayMin = 300; //  Minimum time to wait for the second clap
unsigned long secondClapDelayMax = 1000; //  Maximum time to wait for the second clap
unsigned long idleRestartTime = secondClapDelayMax + 500;  //  How much time to wait before reset to first clap logic
unsigned long timePased;  //  Save how much time passed between the first and second claps


void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(ledpin, OUTPUT);
  pinMode(soundPin, INPUT);
}

void loop() {
  clapFunction();
}


//  Main clap logic
void clapFunction(){
  if(startTime == 0){
    if(digitalSpeeker()){
      Serial.println("In");
      startTime = millis();
      Serial.println(startTime);
      delay(50);
    }
  }
  else {
    timePased = millis() - startTime;
    
    if(digitalSpeeker()){
      Serial.println("Time passed: " + String(timePased));
        if (timePased >= secondClapDelayMin && timePased <= secondClapDelayMax){
          digitalWrite(ledpin, !digitalRead(ledpin));
          delay(50);
        }
        else {
          if ( timePased >= secondClapDelayMin ) {
            Serial.println("Clap before min time");
          }
          else {
            Serial.println("Clap after max time");
          }
          startTime = 0;
        }
    }
    else if ( timePased > idleRestartTime ) {
      Serial.println("Reset");
      startTime = 0;
    }
  }
}

//  Return true if device read sound above his thrash value
bool digitalSpeeker(){  
  return digitalRead(soundPin) > 0;
}
