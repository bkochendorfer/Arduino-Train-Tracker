//CTA Train Tracker
int ledcolor = 0;
int a = 10000; //this sets how long the stays one color for
int red = 11; //this sets the red led pin
int green = 12; //this sets the green led pin
int blue = 13; //this sets the blue led pin
int starttime = 1; // set up time 
int endtime = 1; // set up end time
char msg = ' '; //declaring message

void setup() { //this sets the output pins
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  Serial.print("Serial open\n");
}

void loop() {
    // While there is data coming in assign it to a variable
  while (Serial.available()>0) {
    msg=Serial.read();
    Serial.println(msg);
  }
  
  if (msg=='1'){  
    digitalWrite(blue, HIGH);
    delay(a);
    digitalWrite(blue, LOW);
  }  
  else if (msg=='2'){
    starttime = millis();
    endtime = starttime;
    while ((endtime - starttime) <= 10000){ 
     analogWrite(red, 100);
     digitalWrite(green, HIGH);
     digitalWrite(blue, HIGH);
     analogWrite(red, 0);
     digitalWrite(green, LOW);
     digitalWrite(blue, LOW);
     digitalWrite(blue, HIGH);
     digitalWrite(red, HIGH);
     digitalWrite(green, HIGH);
     buzz(4, 2500, 500); // buzz the buzzer on pin 4 at 2500Hz for 1000 milliseconds
     endtime = millis();
    }
    delay(a);
    analogWrite(red, 0);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
  }  
  msg = ' ';
}

void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
 for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait againf or the calculated delay value
  }
}
